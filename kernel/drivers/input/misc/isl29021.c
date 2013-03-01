/* Proximity-sensor
 *
 * Copyright (c) 2011-2014, HuizeWeng@Arimacomm Crop. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include <mach/oem_rapi_client.h>
#include <mach/vreg.h>
#include <linux/proximity_common.h>

#define debug 0

#define ISL29021_INTERRUPT 17

#define ISL29021_DRIVER_NAME "isl29021"

#define THRESHOLD_LEVEL 700
#define THRESHOLD_RANGE (THRESHOLD_LEVEL << 1)

DEFINE_MUTEX(Isl29021_global_lock);

enum{
	PROXIMITY_REG_COMMANDI		= 0x00,
	PROXIMITY_REG_COMMANDII		= 0x01,
	PROXIMITY_REG_DATA_LSB		= 0x02,
	PROXIMITY_REG_DATA_MSB		= 0x03,
	PROXIMITY_REG_INT_LT_LSB	= 0x04,
	PROXIMITY_REG_INT_LT_MSB	= 0x05,
	PROXIMITY_REG_INT_HT_LSB	= 0x06,
	PROXIMITY_REG_INT_HT_MSB	= 0x07,
};

/* ---------------------------------------------------------------------------------------- *
   Input device interface
 * ---------------------------------------------------------------------------------------- */

static int isl29021_rpc(int threshold, uint32_t event)
{
	struct oem_rapi_client_streaming_func_arg arg;
	struct oem_rapi_client_streaming_func_ret ret;	
	char* input;
	char* output;
	int out_len;
	int result;

	struct msm_rpc_client *mrc;

	input = kzalloc(Buff_Size, GFP_KERNEL);
	output = kzalloc(Buff_Size, GFP_KERNEL);

	switch(event){
		case OEM_RAPI_CLIENT_EVENT_PROXIMITY_THRESHOLD_SET :
			snprintf(input, Buff_Size, "%d", threshold);
		case OEM_RAPI_CLIENT_EVENT_PROXIMITY_THRESHOLD_GET :
			arg.event = event;
			break;
		default :
			kfree(input);
			kfree(output);
			return -999;
	}
	arg.cb_func = NULL;
	arg.handle = (void *)0;
	arg.in_len = strlen(input) + 1;
	arg.input = input;
	arg.output_valid = 1;
	arg.out_len_valid = 1;
	arg.output_size = Buff_Size;

	ret.output = output;
	ret.out_len = &out_len;

	mrc = oem_rapi_client_init();
	oem_rapi_client_streaming_function(mrc, &arg, &ret);
	oem_rapi_client_close();

	result = (int) simple_strtol(ret.output, NULL, 10);

	kfree(input);
	kfree(output);

	return result;
}

static int isl29021_resetThreshold(int threshold)
{
	Proximity* data = i2c_get_clientdata(this_client);
	int result = 0;

	mutex_lock(&data->mutex);
	result = isl29021_rpc(threshold, OEM_RAPI_CLIENT_EVENT_PROXIMITY_THRESHOLD_SET);
	data->sdata.Threshold_L = (result >= THRESHOLD_LEVEL) ? (result - (THRESHOLD_LEVEL >> 2)) : data->sdata.Threshold_L;
	data->sdata.Threshold_H = (result >= THRESHOLD_LEVEL) ? result : data->sdata.Threshold_H;
	#if debug
	printk("readThreshold ==========> LOW %d, HIGH %d \n", data->sdata.Threshold_L, data->sdata.Threshold_H);
	#endif
	mutex_unlock(&data->mutex);
	
	return result;
}

static int isl29021_readThreshold(void)
{
	Proximity* data = i2c_get_clientdata(this_client);
	int result = isl29021_rpc(0, OEM_RAPI_CLIENT_EVENT_PROXIMITY_THRESHOLD_GET);
	if(result == -5){
		/**
		* Do reset. 
		* It means that proximity threshold hasn't been setted yet.
		*/
		result = isl29021_resetThreshold(DEFAULT_THRESHOLD);
	}

	mutex_lock(&data->mutex);
	data->sdata.Threshold_L = (result >= THRESHOLD_LEVEL) ? (result - (THRESHOLD_LEVEL >> 2)) : data->sdata.Threshold_L;
	data->sdata.Threshold_H = (result >= THRESHOLD_LEVEL) ? result : data->sdata.Threshold_H;
	mutex_unlock(&data->mutex);
	return result;
}

static void isl29021_setThreshold(u16 LOW, u16 HIGH)
{
	u8 tmp[4] = {LOW & 0XFF, LOW >> 8, HIGH & 0XFF, HIGH >> 8};
	i2c_smbus_write_i2c_block_data(this_client, PROXIMITY_REG_INT_LT_LSB, 4, tmp);
}

static int isl29021_enable(void)
{
	Proximity* data = i2c_get_clientdata(this_client);
	#if debug
	pr_info("ISL29021: %s ++\n", __func__);
	#endif
	
	mutex_lock(&data->mutex);
	if(data->enabled == false){
		//enable sensor
		data->sdata.Value = -1;
		data->sdata.State = PROXIMITY_STATE_UNKNOWN;
		isl29021_setThreshold(0, 65535);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDII, 0xA0);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDI, 0xE0);
		data->enabled = true;
		input_report_abs(data->input, ABS_DISTANCE, DEFAULT_THRESHOLD);
		input_sync(data->input);
		i2cIsFine = true;
		need2Reset = false;
		need2ChangeState = false;
	}
	mutex_unlock(&data->mutex);

	return 0;
}

static int isl29021_disable(void)
{
	Proximity* data = i2c_get_clientdata(this_client);
	#if debug
	pr_info("ISL29021: %s\n", __func__);
	#endif

	mutex_lock(&data->mutex);
	if(data->enabled == true){
		data->enabled = false;
		data->sdata.Value = -1;
		data->sdata.State = PROXIMITY_STATE_UNKNOWN;
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDII, 0x00);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDI, 0x00);
		i2cIsFine = true;
		need2Reset = false;
		need2ChangeState = false;
	}
	mutex_unlock(&data->mutex);

	return 0;
}

static int isl29021_open(struct inode* inode, struct file* file)
{
	int rc = 0;
	#if debug
	pr_info("ISL29021: %s\n", __func__);
	#endif

	mutex_lock(&Isl29021_global_lock);
	if(Proxmity_sensor_opened){
		pr_err("%s: already opened\n", __func__);
		rc = -EBUSY;
	}
	Proxmity_sensor_opened = 1;
	mutex_unlock(&Isl29021_global_lock);
	
	return rc;
}

static int isl29021_release(struct inode* inode, struct file* file)
{
	#if debug
	pr_info("ISL29021: %s\n", __func__);
	#endif
	mutex_lock(&Isl29021_global_lock);
	Proxmity_sensor_opened = 0;
	mutex_unlock(&Isl29021_global_lock);
	return 0;
}

static ssize_t isl29021_read(struct file* f, char* str, size_t length, loff_t* f_pos)
{
	Proximity* data = i2c_get_clientdata(this_client);
	int error = 0;
	#if debug
	pr_info("ISL29021: %s\n", __func__);
	#endif

	mutex_lock(&Isl29021_global_lock);
	if(data->enabled && !data->suspend){
		error = copy_to_user(str, (char *)&(data->sdata), sizeof(ProximityInfor));
	}else{
		ProximityInfor pi = {
			.Value			= -1,
			.State			= PROXIMITY_STATE_UNKNOWN,
			.Threshold_L	= DEFAULT_THRESHOLD,
			.Threshold_H	= DEFAULT_THRESHOLD,
		};
		error = copy_to_user(str, &pi, sizeof(ProximityInfor));
	}
	mutex_unlock(&Isl29021_global_lock);

	return error;
}

static ssize_t isl29021_write(struct file* f, const char* str, size_t length, loff_t* f_pos)
{
	Proximity* data = i2c_get_clientdata(this_client);
	int error = 0;
	#if debug
	pr_info("ISL29021: %s\n", __func__);
	#endif

	mutex_lock(&Isl29021_global_lock);
	if(data->enabled && !data->suspend){
		int result = -1;
		error = copy_from_user(&result, str, sizeof(int));
		error = isl29021_resetThreshold(result + THRESHOLD_LEVEL);
	}else{
		error = -1;
	}
	mutex_unlock(&Isl29021_global_lock);

	return error;
}

static long isl29021_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{
	int rc = 0;

	#if debug
	pr_info("%s cmd:%d, arg:%ld\n", __func__, _IOC_NR(cmd), arg);
	#endif

	mutex_lock(&Isl29021_global_lock);
	switch(cmd){
		case PROXIMITY_IOCTL_SET_STATE:
			rc = arg ? isl29021_enable() : isl29021_disable();
			break;
		case PROXIMITY_IOCTL_GET_DEVICE_INFOR:
		{
			struct device_infor infor = {
				.name		= "Proximity Sensor",
				.vendor		= "Intersil Americas Inc.",
				.maxRange	= 65535,
				.resolution	= 2500,//
				.power		= 100,// uA
			};
			rc = copy_to_user((unsigned long __user *)arg, (char *)&(infor), sizeof(struct device_infor));
			break;
		}
		default:
			pr_err("%s: invalid cmd %d\n", __func__, _IOC_NR(cmd));
			rc = -EINVAL;
	}
	mutex_unlock(&Isl29021_global_lock);

	return rc;
}

static struct file_operations isl29021_fops = {
	.owner			= THIS_MODULE,
	.read			= isl29021_read,
	.write			= isl29021_write,
	.open			= isl29021_open,
	.release		= isl29021_release,
	.unlocked_ioctl = isl29021_ioctl
};

struct miscdevice isl29021_misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "proximity",
	.fops	= &isl29021_fops
};

static irqreturn_t isl29021_irq(int irq, void* handle)
{
	Proximity* data = i2c_get_clientdata(this_client);

	#if debug
	pr_info("%s ++\n", __func__);
	#endif
	disable_irq_nosync(data->irq);
	queue_work(Proximity_WorkQueue, &data->work);
	#if debug
	pr_info("%s --\n", __func__);
	#endif

	return IRQ_HANDLED;
}

static void isl29021_work_func(struct work_struct* work)
{
	int tmp_Value = 0;
	u8 tmp_State = PROXIMITY_STATE_UNKNOWN;
	Proximity* data = i2c_get_clientdata(this_client);

	#if debug
	pr_info("ISL29021: %s ++\n", __func__);
	#endif

	mutex_lock(&data->mutex);
	memset(i2cData, 0, sizeof(i2cData));
	if(data->enabled && !data->suspend && 
		(i2cIsFine = (i2c_smbus_read_i2c_block_data(this_client, PROXIMITY_REG_DATA_LSB, 2, &i2cData[0]) == 2))){

		tmp_Value = (i2cData[1] << 8) | i2cData[0];

		if(data->sdata.State != PROXIMITY_STATE_TRUE){
			tmp_State = (tmp_Value > data->sdata.Threshold_H) ? PROXIMITY_STATE_TRUE : PROXIMITY_STATE_FALSE;
		}else{
			tmp_State = (tmp_Value > data->sdata.Threshold_L) ? PROXIMITY_STATE_TRUE : PROXIMITY_STATE_FALSE;
		}
		data->sdata.Value = tmp_Value;

		if(tmp_State != data->sdata.State){
			if(need2ChangeState == true){
				data->sdata.State = tmp_State;
				input_report_abs(data->input, ABS_DISTANCE, (tmp_State) ? 1 : 5000);
				input_sync(data->input);
			}
			need2ChangeState = !need2ChangeState;
		}else{
			need2ChangeState = false;
		}

		i2c_smbus_read_byte_data(this_client, PROXIMITY_REG_COMMANDI);
		#if debug
		pr_info("ISL29021: Proximity : %d\n", tmp_Value);
		#endif
	}else if(!i2cIsFine){
		// Varify i2c transaction, 
		// reset value and state if it is failure.
		data->sdata.Value = I2CERROR_TRANSACTION;
		data->sdata.State = PROXIMITY_STATE_UNKNOWN;
		pr_info("ISL29021: I2CERROR_TRANSACTION, try to reset chip \n");
	}
	mutex_unlock(&data->mutex);

	// Auto-calibrate
	if(!i2cIsFine || ((tmp_Value + THRESHOLD_RANGE) > data->sdata.Threshold_H)){
		need2Reset = false;
	}else{
		(need2Reset) ? isl29021_resetThreshold(tmp_Value + THRESHOLD_LEVEL) : 0;
		need2Reset = !need2Reset;
	}

	// Closed sensor
	if(data->enabled && !data->suspend){
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDII, 0x00);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDI, 0x00);
		msleep(90);
	}
	// Restart Sensor, 
	// it needs to check current state for avoiding async, so lock it.
	mutex_lock(&data->mutex);
	if(data->enabled && !data->suspend){
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDII, 0xA0);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDI, 0xE0);
	}
	mutex_unlock(&data->mutex);

	enable_irq(data->irq);
	#if debug
	pr_info("ISL29021: %s --\n", __func__);
	#endif
}

static int isl29021_suspend(struct i2c_client* client, pm_message_t state)
{
	Proximity* data = i2c_get_clientdata(client);
	#if debug
	pr_info("ISL29021: %s ++\n", __func__);
	#endif

	mutex_lock(&data->mutex);
	data->suspend = true;
	if(data->enabled){
		i2c_smbus_write_byte_data(client, PROXIMITY_REG_COMMANDII, 0x00);
		i2c_smbus_write_byte_data(client, PROXIMITY_REG_COMMANDI, 0x00);
		data->sdata.Value = -1;
		data->sdata.State = PROXIMITY_STATE_UNKNOWN;
		i2cIsFine = true;
		need2Reset = false;
		need2ChangeState = false;
	}
	mutex_unlock(&data->mutex);

	#if debug
	pr_info("ISL29021: %s --\n", __func__);
	#endif
	return 0;// It needs to return 0, non-zero means has falut.
}

static int isl29021_resume(struct i2c_client* client)
{
	Proximity* data = i2c_get_clientdata(client);
	#if debug
	pr_info("ISL29021: %s ++\n", __func__);
	#endif

	mutex_lock(&data->mutex);
	data->suspend = false;
	if(data->enabled){
		data->sdata.Value = -1;
		data->sdata.State = PROXIMITY_STATE_UNKNOWN;
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDII, 0xA0);
		i2c_smbus_write_byte_data(this_client, PROXIMITY_REG_COMMANDI, 0xE0);
		i2cIsFine = true;
		need2Reset = false;
		need2ChangeState = false;
	}
	mutex_unlock(&data->mutex);

	#if debug
	pr_info("ISL29021: %s --\n", __func__);
	#endif
	return 0;// It needs to return 0, non-zero means has falut.
}

static int isl29021_probe(struct i2c_client* client, const struct i2c_device_id* id)
{
	Proximity* Sensor_device = NULL;
	struct input_dev* input_dev = NULL;
	int err = 0;

	#if debug
	pr_info("ISL29021: %s ++\n", __func__);
	#endif

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)){
		return -EIO;
	}

	Sensor_device = kzalloc(sizeof(Proximity), GFP_KERNEL);

	input_dev = input_allocate_device();

	if(!Sensor_device || !input_dev){
		err = -ENOMEM;
		goto err_free_mem;
	}

	INIT_WORK(&Sensor_device->work, isl29021_work_func);
	i2c_set_clientdata(client, Sensor_device);

	err = gpio_request(ISL29021_INTERRUPT, "isl29021_sensor_init");
	if(err){
		goto err_free_data;
	}

	err = gpio_direction_input(ISL29021_INTERRUPT);
	
	if(err < 0){
		printk(KERN_ERR"ISL29021_SENSOR: failed to config the interrupt pin\n");
	}

	Sensor_device->irq = gpio_to_irq(ISL29021_INTERRUPT);

	err = request_irq(Sensor_device->irq, isl29021_irq, IRQF_TRIGGER_LOW, "ISL29021_SENSOR", Sensor_device);

	if(err < 0){
		dev_err(&client->dev, "irq %d busy?\n", Sensor_device->irq);
		goto err_free_mem;
	}

	gpio_tlmm_config(GPIO_CFG(ISL29021_INTERRUPT, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE);

	#if debug
	pr_info("ISL29021: isl29021_irq:request_irq finished\n");
	#endif

	input_dev->name = "proximity";
	input_dev->id.bustype = BUS_I2C;

	input_set_capability(input_dev, EV_ABS, ABS_MISC);
	input_set_abs_params(input_dev, ABS_DISTANCE, 0, 65535, 0, 0);
	input_set_drvdata(input_dev, Sensor_device);	

	err = input_register_device(input_dev);
	if(err){
		pr_err("ISL29021: input_register_device error\n");
		goto err_free_irq;
	}

	i2c_smbus_write_byte_data(client, PROXIMITY_REG_COMMANDII, 0x00);
	i2c_smbus_write_byte_data(client, PROXIMITY_REG_COMMANDI, 0x00);

	err = misc_register(&isl29021_misc);
    if(err < 0){
		pr_err("ISL29021: sensor_probe: Unable to register misc device: %s\n", input_dev->name);
		goto err;
	}
	
	Sensor_device->input 				= input_dev;
	Sensor_device->enabled 				= false;
	Sensor_device->suspend				= false;
	Sensor_device->sdata.Value			= -1;
	Sensor_device->sdata.State 			= PROXIMITY_STATE_UNKNOWN;
	Sensor_device->sdata.Threshold_L 	= DEFAULT_THRESHOLD;
	Sensor_device->sdata.Threshold_H	= DEFAULT_THRESHOLD;

	mutex_init(&Sensor_device->mutex);

	Proxmity_sensor_opened = 0;
	i2cIsFine = true;
	need2Reset = false;
	need2ChangeState = false;
	#if debug
	dev_info(&client->dev, "registered with irq (%d)\n", Sensor_device->irq);
	#endif

	#if debug
	pr_info("ISL29021: %s --\n", __func__);
	#endif

	this_client = client;
	Proximity_WorkQueue = create_singlethread_workqueue(input_dev->name);
	isl29021_readThreshold();// It needs to avoid deadlock.

	return 0;

 	err:
		misc_deregister(&isl29021_misc);
	err_free_irq:
		free_irq(Sensor_device->irq, Sensor_device);
 	err_free_mem:
		input_free_device(input_dev);
	err_free_data:
		kfree(Sensor_device);
	return err;
}

static int isl29021_remove(struct i2c_client* client)
{
	Proximity* data = i2c_get_clientdata(client);

	destroy_workqueue(Proximity_WorkQueue);
	free_irq(data->irq, data);
	input_unregister_device(data->input);
	misc_deregister(&isl29021_misc);
	kfree(data);

	return 0;
}

static void isl29021_shutdown(struct i2c_client* client)
{
	Proximity* data = i2c_get_clientdata(client);
	free_irq(data->irq, data);
	isl29021_disable();
}

static struct i2c_device_id isl29021_idtable[] = {
	{"isl29021", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, isl29021_idtable);

static struct i2c_driver isl29021_driver = {
	.driver = {
		.owner	= THIS_MODULE,
		.name	= ISL29021_DRIVER_NAME
	},
	.id_table	= isl29021_idtable,
	.probe		= isl29021_probe,
	.remove		= isl29021_remove,
	.suspend  	= isl29021_suspend,
	.resume   	= isl29021_resume,
	.shutdown	= isl29021_shutdown,
};

static int __init isl29021_init(void)
{
	return i2c_add_driver(&isl29021_driver);
}

static void __exit isl29021_exit(void)
{
	i2c_del_driver(&isl29021_driver);
}

module_init(isl29021_init);
module_exit(isl29021_exit);

MODULE_AUTHOR("HuizeWeng@Arimacomm");
MODULE_DESCRIPTION("Proxmity Sensor ISL29021");
MODULE_LICENSE("GPLv2");
