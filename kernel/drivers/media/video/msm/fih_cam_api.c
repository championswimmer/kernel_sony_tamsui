/*
 * Copyright (C) 2011 FIH Co., Ltd.  All rights reserved.
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
 
#include "fih_cam_api.h"

#define CAM_MSB_MASK	0xFF00
#define CAM_LSB_MASK	0x00FF
#define CAM_MASK		0xFF

//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01+{
bool bMainCameraIsReset = false;
bool bFrontCameraIsReset = false;
//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01+}

/* FIH-SW3-MM-UW-modify MCLK config-00+*/
int fih_enable_mclk(int gpio_id, int clk_rate)
{
    int rc = 0;
    
    rc = gpio_tlmm_config(GPIO_CFG(gpio_id, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_4MA), GPIO_CFG_ENABLE);
    if (rc < 0) {
        pr_err("FIH_Disable_MCLK: msm_camio_clk_enable() failed !, rc = %d.\n", rc);
        goto error;
    }	
    
    rc = msm_camio_clk_enable(CAMIO_CAM_MCLK_CLK);
    if (rc < 0) {
        pr_err("FIH_Enable_MCLK: msm_camio_clk_enable() failed !, rc = %d.\n", rc);
        goto error;
    }	

    //void function
    msm_camio_clk_rate_set(clk_rate);

    printk ("FIH_Enable_MCLK: clk_rate = %d, End. \n", clk_rate);  

    rc = gpio_tlmm_config(GPIO_CFG(gpio_id, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_4MA), GPIO_CFG_ENABLE);
    if (rc < 0) {
        pr_err("FIH_Enable_MCLK: msm_camio_clk_enable() failed !, rc = %d.\n", rc);
        goto error;
    }	
    return rc;
    
error:
    pr_err("FIH_Enable_MCLK: failed !, rc = %d.\n", rc);
    return rc;
}
/* FIH-SW3-MM-UW-modify MCLK config-00-*/

int fih_disable_mclk(int gpio_id, int clk_rate)
{
    int rc = 0;

    rc = gpio_tlmm_config(GPIO_CFG(gpio_id, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_4MA), GPIO_CFG_ENABLE);
    if (rc < 0) {
        pr_err("FIH_Disable_MCLK: msm_camio_clk_enable() failed !, rc = %d.\n", rc);
        goto error;
    }	

    msm_camio_clk_disable(CAMIO_CAM_MCLK_CLK);
    if (rc < 0) {
        pr_err("FIH_Disable_MCLK: msm_camio_clk_disable() failed !, rc = %d.\n", rc);
        goto error;
    }	

    printk ("FIH_Disable_MCLK: clk_rate = %d, End. \n", clk_rate);    
    return rc;
    
error:
    pr_err("FIH_Disable_MCLK: failed !, rc = %d.\n", rc);
    return rc;
}

static int fih_i2c_rxdata(const struct i2c_client *client, unsigned char *rxdata, int length)
{
    struct i2c_msg msgs[] = 
    {
        {
            .addr  = client->addr,
            .flags = 0,
            .len   = 2,
            .buf   = rxdata,
        },
        {
            .addr  = client->addr,
            .flags = I2C_M_RD,
            .len   = length,
            .buf   = rxdata,
        },
    };

    if (i2c_transfer(client->adapter, msgs, 2) < 0) {
        pr_err("fih_i2c_rxdata() failed !\n");
        return -EIO;
    }
    return 0;
}

int32_t fih_i2c_read(const struct i2c_client *client, unsigned short raddr, unsigned short *rdata, enum fih_i2c_width width)
{
    int32_t rc = 0;
    unsigned char buf[2];

    if (!rdata)
        return -EIO;

    memset(buf, 0, sizeof(buf));

    switch (width) {
    case WORD_LEN: {//W_Addr : W_Data
        buf[0] = (raddr & CAM_MSB_MASK) >> 8;
        buf[1] = (raddr & CAM_LSB_MASK);

        rc = fih_i2c_rxdata(client, buf, 2);
        if (rc < 0) {
            pr_err("WORD_LEN: fih_i2c_read(0x%x) failed !\n", raddr);
            break;
        }

        *rdata = buf[0] << 8 | buf[1];
    }
    break;

    case BYTE_LEN: {//W_Addr : B_Data
        buf[0] = (raddr & CAM_MSB_MASK)>>8;
        buf[1] = (raddr & CAM_LSB_MASK);

        rc = fih_i2c_rxdata(client, buf, 2);
        if (rc < 0) {
            pr_err("BYTE_LEN: fih_i2c_read(0x%x) failed !\n", raddr);
            break;
        }

        *rdata = buf[0];
    }

    default:
        break;
    }

    if (rc < 0)
        pr_err("fih_i2c_read failed !\n");

    return rc;
}

static int32_t fih_i2c_txdata(const struct i2c_client *client, unsigned char *txdata, int length)
{
	struct i2c_msg msg[] = {
		{
		 .addr = client->addr ,
		 .flags = 0,
		 .len = length,
		 .buf = txdata,
		 },
	};

	if (i2c_transfer(client->adapter, msg, 1) < 0) {
		//pr_err("fih_i2c_txdata faild 0x%x !\n", client->addr);
		return -EIO;
	}

	return 0;
}

int32_t fih_i2c_write(const struct i2c_client *client, unsigned short waddr, unsigned short wdata, enum fih_i2c_width width)
{
    int32_t rc = -EIO;
    unsigned char buf[4];
    int count = 0;
    unsigned short poll_val;

    memset(buf, 0, sizeof(buf));
    switch (width) {
    case WORD_LEN: {//W_Addr : W_Data
        buf[0] = (waddr & CAM_MSB_MASK)>>8;
        buf[1] = (waddr & CAM_LSB_MASK);
        buf[2] = (wdata & CAM_MSB_MASK)>>8;
        buf[3] = (wdata & CAM_LSB_MASK);

        rc = fih_i2c_txdata(client, buf, 4);
        if (rc < 0) {
            pr_err("WORD_LEN: fih_i2c_write(0x%x) failed, client->addr = 0x%x !\n", waddr, client->addr);
            break;
        }
    }
    break;

    case BYTE_LEN: {//W_Addr : B_Data
        buf[0] = (waddr & CAM_MSB_MASK)>>8;
        buf[1] = (waddr & CAM_LSB_MASK);
        buf[2] = (wdata & CAM_MASK);

        rc = fih_i2c_txdata(client, buf, 3);
        if (rc < 0) {
            pr_err("BYTE_LEN: fih_i2c_write(0x%x) failed, client->addr = 0x%x !\n", waddr, client->addr);
            break;
        }
    }
    break;

    case WORD_POLL: {//W_Addr : W_Data
    do {
            count++;
            cam_msleep(10);
            rc = fih_i2c_read(client, waddr, &poll_val, WORD_LEN);
            if (rc < 0) {
                pr_err("WORD_POLL: fih_i2c_write: Read Back(0x%x) failed, count = %d !\n", waddr, count);
                break;
            }
        } while( (poll_val != wdata) && (count <100) );
        printk("WORD_POLL: fih_i2c_write: raddr = 0x%x, rdata = 0x%x, count = %d.\n", waddr, poll_val, count);
    }
    break;

    case BYTE_POLL: {//W_Addr : B_Data
        do {
            count++;
            cam_msleep(10);
            rc = fih_i2c_read(client, waddr, &poll_val, BYTE_LEN);
            if (rc < 0) {
                pr_err("BYTE_POLL: fih_i2c_write: Read Back(0x%x) failed, count = %d !\n", waddr, count);
                break;
            }
        } while( (poll_val != wdata) && (count <100) );
        printk("BYTE_POLL: fih_i2c_write: raddr = 0x%x, rdata = 0x%x, count = %d.\n", waddr, poll_val, count);
    }
    break;

    default:
        break;
    }

    if (rc < 0)
        pr_err("i2c_write fih_i2c_write, addr = 0x%x, val = 0x%x !\n", waddr, wdata);

    return rc;
}

int32_t fih_i2c_no_ack_write(const struct i2c_client *client, unsigned short waddr, unsigned short wdata, enum fih_i2c_width width)
{
    int32_t rc = -EIO;
    unsigned char buf[4];

    memset(buf, 0, sizeof(buf));
    switch (width) {
    case WORD_LEN: {//W_Addr : W_Data
        buf[0] = (waddr & CAM_MSB_MASK)>>8;
        buf[1] = (waddr & CAM_LSB_MASK);
        buf[2] = (wdata & CAM_MSB_MASK)>>8;
        buf[3] = (wdata & CAM_LSB_MASK);

        rc = fih_i2c_txdata(client, buf, 4);
        if (rc < 0) {
            pr_err("WORD_LEN: fih_i2c_no_ack_write(0x%x) warning, client->addr = 0x%x !\n", waddr, client->addr);
            break;
        }
    }
    break;

    case BYTE_LEN: {//W_Addr : B_Data
        buf[0] = (waddr & CAM_MSB_MASK)>>8;
        buf[1] = (waddr & CAM_LSB_MASK);
        buf[2] = (wdata & CAM_MASK);

        rc = fih_i2c_txdata(client, buf, 3);
        if (rc < 0) {
            pr_err("BYTE_LEN: fih_i2c_no_ack_write(0x%x) warning, client->addr = 0x%x !\n", waddr, client->addr);
            break;
        }
    }
    break;

    default:
        break;
    }

    if (rc < 0)
        pr_err("fih_i2c_no_ack_write: Warning: addr = 0x%x, val = 0x%x !\n", waddr, wdata);

    return rc;
}

int32_t fih_i2c_write_table(const struct i2c_client *client, struct fih_i2c_reg_conf const *reg_conf_tbl, int num_of_items_in_table)
{
    int i;
    int32_t rc = -EIO;

    for (i = 0; i < num_of_items_in_table; i++) {
        rc = fih_i2c_write(client, reg_conf_tbl->waddr, 
                                      reg_conf_tbl->wdata,reg_conf_tbl->width);

        if (rc < 0)
        {
            pr_err("fih_i2c_write_table: Write count %d, addr 0x%x, val 0x%x failed !\n", i, reg_conf_tbl->waddr, reg_conf_tbl->wdata);  
            break;
        }

        if (reg_conf_tbl->mdelay_time != 0)
        {      
            cam_msleep(reg_conf_tbl->mdelay_time);
        }
        reg_conf_tbl++;
    }

    return rc;
}

int fih_set_gpio_output_value(int gpio_id, const char *tag, int value)
{
    int rc = 0;

    rc = gpio_request(gpio_id, tag);
    if (rc < 0) {
        pr_err("fih_set_gpio_output_value: gpio_request (%d, %s) !.\n", gpio_id, tag);
	 goto request_fail;
    }	

    rc = gpio_direction_output(gpio_id, value);
    if (rc < 0) {
        pr_err("fih_set_gpio_output_value: gpio_direction_output (%d, %d) !.\n", gpio_id, value);
	 goto set_fail;
    }	

    gpio_free(gpio_id);//void function

    if (value)
        printk("fih_set_gpio_output_value: Pull high %s (%d) done.\n", tag, gpio_id);
    else
        printk("fih_set_gpio_output_value: Pull low %s (%d) done.\n", tag, gpio_id);   
    
    return rc;

set_fail:
    gpio_free(gpio_id);//void function
request_fail:
    pr_err("fih_set_gpio_output_value:  Failed !, rc = %d.\n", rc);
    return rc;
}

static struct regulator *regulator;
int fih_regulator_enable(const char *id, int voltage, const char *tag)
{
    int rc = 0;

    /* Voting for Regulator */
    regulator = regulator_get(NULL, id);
    if (IS_ERR(regulator)) {
        rc = PTR_ERR(regulator);
        pr_err("%s: could not get regulator: %d\n", __func__, rc);
        goto out;
    }
     
    /* Set the voltage level */
    rc = regulator_set_voltage(regulator, voltage, voltage);
    if (rc < 0) {
        pr_err("%s: could not set voltage: %d\n", __func__, rc);
        goto reg_free;
    }
    
    /* Enabling the regulator */
    rc = regulator_enable(regulator);
    if (rc) {
        pr_err("%s: could not enable regulator: %d\n", __func__, rc);
        goto reg_free;
    }

    printk("%s: regulator_is_enabled(%s) for %s success.\n", __func__, id, tag);
    return rc;

reg_free:
    regulator_put(regulator);
    regulator = NULL;
out:
    pr_err("%s: For %s fail !\n", __func__, tag); 
    return rc;
}

int fih_regulator_disable(const char *id, const char *tag)
{
    int rc = 0;
    
    /* Voting for 1.8V Regulator */
    regulator = regulator_get(NULL, id);
    if (IS_ERR(regulator)) {
        rc = PTR_ERR(regulator);
        pr_err("%s: could not get regulator: %d\n", __func__, rc);
        goto out;
    }

    if (regulator_is_enabled(regulator) == 0)
    {
        printk("%s: regulator(%s) is disable previously for %s.\n", __func__, id, tag);
        goto exit;
    }
    
    /* Releasing the 1.8V Regulator */
    if (!IS_ERR_OR_NULL(regulator)) {
        rc = regulator_disable(regulator);
        if (rc)
        {
            pr_err("%s: could not disable regulator: %d\n", __func__, rc);
            regulator_put(regulator);
            regulator = NULL;
            goto out;
        }
    }

    printk("%s: regulator_disable(%s) for %s success.\n", __func__, id, tag);
    
exit:
    regulator_put(regulator);
    regulator = NULL;
    return rc;
    
out:
    pr_err("%s: For %s fail !\n", __func__, tag); 
    return rc;
}
