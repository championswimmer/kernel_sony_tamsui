/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 * Copyright(C) 2011-2012 Foxconn International Holdings, Ltd. All rights reserved.
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

#include <linux/debugfs.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <mach/camera.h>
#include <media/msm_camera.h>
#include "s5k5cag_2nd.h"

/* 16bit address - 8 bit context register structure */
#define Q8	0x00000100
#define Q10	0x00000400

/* MCLK */
#define S5K5CAG_2ND_MASTER_CLK_RATE 24000000

/* AF Total steps parameters */
#define S5K5CAG_2ND_TOTAL_STEPS_NEAR_TO_FAR	32

#define S5K5CAG_2ND_REG_PREV_FRAME_LEN_1	30
#define S5K5CAG_2ND_REG_PREV_FRAME_LEN_2	31
#define S5K5CAG_2ND_REG_PREV_LINE_LEN_1	32
#define S5K5CAG_2ND_REG_PREV_LINE_LEN_2	33

#define S5K5CAG_2ND_REG_SNAP_FRAME_LEN_1	14
#define S5K5CAG_2ND_REG_SNAP_FRAME_LEN_2	15
#define  S5K5CAG_2ND_REG_SNAP_LINE_LEN_1	16
#define S5K5CAG_2ND_REG_SNAP_LINE_LEN_2	17
//MTD-SW3-MM-UW-camframe timeout-00+{	
static const struct msm_camera_sensor_info *s5k5cag_2nd_info;
static struct platform_device *dev0;
//MTD-SW3-MM-UW-camframe timeout-00+}
struct s5k5cag_2nd_work_t {
	struct work_struct work;
};

static struct s5k5cag_2nd_work_t *s5k5cag_2nd_sensorw;
//static struct s5k5cag_2nd_work_t *s5k5cag_2nd_af_sensorw;
//static struct i2c_client *s5k5cag_2nd_af_client;
static struct i2c_client *s5k5cag_2nd_client;

struct s5k5cag_2nd_ctrl_t {
	const struct  msm_camera_sensor_info *sensordata;

	uint32_t sensormode;
	uint32_t fps_divider;/* init to 1 * 0x00000400 */
	uint32_t pict_fps_divider;/* init to 1 * 0x00000400 */
	uint16_t fps;

	uint16_t curr_lens_pos;
	uint16_t curr_step_pos;
	uint16_t my_reg_gain;
	uint32_t my_reg_line_count;
	uint16_t total_lines_per_frame;

	enum s5k5cag_2nd_resolution_t prev_res;
	enum s5k5cag_2nd_resolution_t pict_res;
	enum s5k5cag_2nd_resolution_t curr_res;
};

static bool CSI_CONFIG;
static bool STARTUP;
static struct s5k5cag_2nd_ctrl_t *s5k5cag_2nd_ctrl;

static DECLARE_WAIT_QUEUE_HEAD(s5k5cag_2nd_wait_queue);
static DECLARE_WAIT_QUEUE_HEAD(s5k5cag_2nd_af_wait_queue);
DEFINE_MUTEX(s5k5cag_2nd_mut);

static uint16_t prev_line_length_pck;
static uint16_t prev_frame_length_lines;
static uint16_t snap_line_length_pck;
static uint16_t snap_frame_length_lines;
/* FIH-SW3-MM-URI-Add WB-00+ */
#ifdef CONFIG_FIH_BRIGHTNESS
static int16_t s5k5cag_2nd_brightness = 0;
#endif
#ifdef CONFIG_FIH_WB
static int16_t s5k5cag_2nd_wb = 0;
#endif
#ifdef CONFIG_FIH_METRY
static int16_t s5k5cag_2nd_meter = 0;
#endif
#ifdef CONFIG_FIH_SCENE
static int16_t s5k5cag_2nd_scene = 0;
#endif
/* FIH-SW3-MM-URI-Add WB-00- */
static int s5k5cag_2nd_i2c_rxdata(unsigned short saddr,
		unsigned char *rxdata, int length)
{
	struct i2c_msg msgs[] = {
		/*{
			.addr  = saddr,
			.flags = 0,
			.len   = 1,
			.buf   = rxdata,
		},
		{
			.addr  = saddr,
			.flags = I2C_M_RD,
			.len   = 1,
			.buf   = rxdata,
		},*/
		{
			.addr   = saddr,
			.flags = 0,
			.len   = 2,
			.buf   = rxdata,
		},
		{
			.addr   = saddr,
			.flags = I2C_M_RD,
			.len   = length,
			.buf   = rxdata,
		},
	};
		
	if (i2c_transfer(s5k5cag_2nd_client->adapter, msgs, 2) < 0) {
		CDBG("s5k5cag_2nd_i2c_rxdata faild 0x%x\n", saddr);
		return -EIO;
	}
	return 0;
}

static int32_t s5k5cag_2nd_i2c_txdata(unsigned short saddr,
		unsigned char *txdata, int length)
{
	struct i2c_msg msg[] = {
		{
			.addr = saddr,
			.flags = 0,
			.len = length,
			.buf = txdata,
		},
	};
	if (i2c_transfer(s5k5cag_2nd_client->adapter, msg, 1) < 0) {
		CDBG("s5k5cag_2nd_i2c_txdata faild 0x%x\n", saddr);
		return -EIO;
	}

	return 0;
}

static int32_t s5k5cag_2nd_i2c_read(unsigned short raddr,
		unsigned short *rdata, int rlen)
{
	int32_t rc = 0;
	unsigned char buf[2];

	if (!rdata)
		return -EIO;

	memset(buf, 0, sizeof(buf));
	buf[0] = (raddr & 0xFF00) >> 8;
	buf[1] = (raddr & 0x00FF);
	rc = s5k5cag_2nd_i2c_rxdata(s5k5cag_2nd_client->addr, buf, rlen);
	if (rc < 0) {
		printk("s5k5cag_2nd_i2c_read 0x%x failed!\n", raddr);
		return rc;
	}
	//*rdata = buf[0] << 8 | buf[1];
	*rdata = (rlen == 2 ? buf[0] << 8 | buf[1] : buf[0]);
	printk("s5k5cag_2nd_i2c_read 0x%x val = 0x%x!\n", raddr, *rdata);

	return rc;
}

static int32_t s5k5cag_2nd_i2c_write_b_sensor(unsigned short waddr, unsigned short bdata)
{
	int32_t rc = -EFAULT;
	unsigned char buf[4];

	memset(buf, 0, sizeof(buf));
	buf[0] = (waddr & 0xFF00) >> 8;
	buf[1] = (waddr & 0x00FF);

	buf[2] = (bdata & 0xFF00) >> 8;
	buf[3] = (bdata & 0x00FF);
	//printk("i2c_write_b addr = 0x%x, val = 0x%x\n", waddr, bdata);
	rc = s5k5cag_2nd_i2c_txdata(s5k5cag_2nd_client->addr, buf, 4);
	if (rc < 0) {
		printk("i2c_write_b failed, addr = 0x%x, val = 0x%x!\n",
				waddr, bdata);
	}
	return rc;
}

static int32_t s5k5cag_2nd_i2c_write_b_table(struct s5k5cag_2nd_i2c_reg_conf const
		*reg_conf_tbl, int num)
{
	int i;
	int32_t rc = -EIO;

	for (i = 0; i < num; i++) {
		rc = s5k5cag_2nd_i2c_write_b_sensor(reg_conf_tbl->waddr,
				reg_conf_tbl->wdata);
		if (rc < 0)
			break;
		reg_conf_tbl++;
	}
	return rc;
}

static void s5k5cag_2nd_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
	/* input fps is preview fps in Q8 format */
	uint32_t divider, d1, d2;

	d1 = (prev_frame_length_lines * 0x00000400) / snap_frame_length_lines;
	d2 = (prev_line_length_pck * 0x00000400) / snap_line_length_pck;
	divider = (d1 * d2) / 0x400;

	/*Verify PCLK settings and frame sizes.*/
	*pfps = (uint16_t) (fps * divider / 0x400);
}

static uint16_t s5k5cag_2nd_get_prev_lines_pf(void)
{
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE)
		return prev_frame_length_lines;
	else
		return snap_frame_length_lines;
}

static uint16_t s5k5cag_2nd_get_prev_pixels_pl(void)
{
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE)
		return prev_line_length_pck;
	else
		return snap_line_length_pck;
}

static uint16_t s5k5cag_2nd_get_pict_lines_pf(void)
{
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE)
		return prev_frame_length_lines;
	else
		return snap_frame_length_lines;
}

static uint16_t s5k5cag_2nd_get_pict_pixels_pl(void)
{
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE)
		return prev_line_length_pck;
	else
		return snap_line_length_pck;
}

static uint32_t s5k5cag_2nd_get_pict_max_exp_lc(void)
{
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE)
		return prev_frame_length_lines;
	else
		return snap_frame_length_lines;
}

//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*{
int s5k5cag_2nd_enter_standby(void)
{
    int rc = 0;

    printk ("s5k5cag_2nd_enter_standby: E \n");
    
    rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_pwd, "CAM_3M_PWD", LOW);
    if (rc < 0)
        return rc;
    
    cam_msleep(100);//Frame time base on 10FPS

    rc = fih_disable_mclk(s5k5cag_2nd_info->mclk, S5K5CAG_2ND_MASTER_CLK_RATE);
    if (rc < 0)
        return rc;
    
    cam_msleep(150);// 100ms + 50ms
    printk ("s5k5cag_2nd_enter_standby: X \n");
    return rc;
}

int s5k5cag_2nd_exit_standby(void)
{
    int rc = 0;
    printk ("s5k5cag_2nd_exit_standby: E \n");

    rc = fih_enable_mclk(s5k5cag_2nd_info->mclk, S5K5CAG_2ND_MASTER_CLK_RATE);
    if (rc < 0)
        return rc;
    
    cam_msleep(1);//0 MCLK cycles
    
    rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_pwd, "CAM_3M_PWD", HIGH);
    if (rc < 0)
        return rc;

    cam_msleep(26);// MAX: 5000us + 21000us

    printk ("s5k5cag_2nd_exit_standby: X \n");
    return rc;
}
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*}

/* FIH-SW3-MM-SL-ModifyGPIODefine-01*{ */
/* FIH-SW3-MM-SL-ModifyGPIODefine-00*{ */
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*{
int s5k5cag_2nd_power_on(const struct msm_camera_sensor_info *data)
{
    int rc = 0;
    printk ("s5k5cag_2nd_power_on \n");  
	
    if(STARTUP == 0)// Normal power on sequence.
    {		
        printk ("s5k5cag_2nd_power_on: STARTUP = 0\n");

        // Init pwd and reset pins.
        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_pwd, "CAM_3M_PWD", LOW);
        if (rc < 0)
            return rc;

        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_reset, "CAM_3M_RESET", LOW);
        if (rc < 0)
            return rc;

        // Start power sequence.
        rc = fih_regulator_enable(s5k5cag_2nd_info->vreg_1v8, 1800000, "s5k5cag_2nd");
        if (rc)
            return rc;
        
        cam_msleep(1);// >500us.

        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->vreg_v2p8, "CAM_3M_V2p8", HIGH);
        if (rc < 0)
            return rc;

        //cam_msleep(0);// 0us.
        rc = fih_enable_mclk(s5k5cag_2nd_info->mclk, S5K5CAG_2ND_MASTER_CLK_RATE);
        if (rc < 0)
            return rc;

        cam_msleep(1);// 10us.
        
        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_pwd, "CAM_3M_PWD", HIGH);
        if (rc < 0)
            return rc;

        cam_msleep(1);// >15us
        
        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_reset, "CAM_3M_RESET", HIGH);
        if (rc < 0)
            return rc;

	    cam_msleep(1);// >100us
    }
    else// Exit HW standby.
    {  
        rc = s5k5cag_2nd_exit_standby();
    }
    return rc;
}

int s5k5cag_2nd_power_off(void)
{
    int rc = 0;
    printk("s5k5cag_2nd_power_off \n");     
    if (STARTUP == 0)//Normal power off sequence.
    {	
        printk("s5k5cag_2nd_power_off: STARTUP = 0\n");

        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_reset, "CAM_3M_RESET", LOW);
        if (rc < 0)
            return rc;
        
        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->sensor_pwd, "CAM_3M_PWD", LOW);
        if (rc < 0)
            return rc;

        rc = fih_disable_mclk(s5k5cag_2nd_info->mclk, S5K5CAG_2ND_MASTER_CLK_RATE);
        if (rc < 0)
            return rc;

        cam_msleep(1);// >50us
        
        rc = fih_regulator_disable(s5k5cag_2nd_info->vreg_1v8, "s5k5cag_2nd");
        if (rc)
            return rc;

        cam_msleep(1);// 0us

        rc = fih_set_gpio_output_value(s5k5cag_2nd_info->vreg_v2p8, "CAM_3M_V2p8", LOW);
        if (rc < 0)
            return rc;
    }
    else//Enter HW standby.
    {
        rc = s5k5cag_2nd_enter_standby();
    }
    return rc;
}

int s5k5cag_2nd_suspend(struct platform_device *pdev, pm_message_t state)
{    
    int rc = 0;
    printk("s5k5cag_2nd_suspend \n");

    rc = s5k5cag_2nd_exit_standby();
    if (rc < 0)
        return rc;
    cam_msleep(10);

    STARTUP = 0;
	s5k5cag_2nd_power_off();
 
    return rc;
}
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*}
/* FIH-SW3-MM-SL-ModifyGPIODefine-00*} */
/* FIH-SW3-MM-SL-ModifyGPIODefine-01*} */

int s5k5cag_2nd_resume(struct platform_device *pdev)
{
     printk ("s5k5cag_2nd_resume \n");  
     STARTUP  = 0;
	 
     return 0;
}

/* FIH-SW3-MM-URI-Set FPS-00+ */
static int32_t s5k5cag_2nd_set_fps(uint16_t fps)
{
	int32_t rc = 0;
       printk ("s5k5cag_2nd_set_fps ------- value =%d\n", fps); 
	if(fps <=15){   
		s5k5cag_2nd_i2c_write_b_sensor(0x002A, 0x0288);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0341);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0341);
	}
	else{
		s5k5cag_2nd_i2c_write_b_sensor(0x002A, 0x0288);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x029A);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x014D);	
	}
	s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_settings,
	s5k5cag_2nd_regs.reg_size);	
	
	return rc;
}
/* FIH-SW3-MM-URI-Set FPS-00- */

/* FIH-SW3-MM-URI-Add WB-00+ */
#ifdef CONFIG_FIH_BRIGHTNESS
static long s5k5cag_2nd_set_brightness(int brightness) 
{
	long rc = 0;

	s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
	s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x020C);
	
	switch (brightness) {
	case 6: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x007f);
		printk ("s5k5cag_2nd_set_brightness = 2");
	}
			break;
	case 5: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x005f);
		printk ("s5k5cag_2nd_set_brightness = 1.66");
	}
			break;
	case 4: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x004f);
		printk ("s5k5cag_2nd_set_brightness = 1.33");
	}
			break;
	case 3: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x003f);
		printk ("s5k5cag_2nd_set_brightness = 1");
	}
			break;
	case 2: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x002f);
		printk ("s5k5cag_2nd_set_brightness = 0.66");
	}
			break;
      case 1: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x001f);
		printk ("s5k5cag_2nd_set_brightness = 0.33");
	}
			break;

	case 0: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0000);
		printk ("s5k5cag_2nd_set_brightness = 0");
	}
			break;
	case -1: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xffe1);
		printk ("s5k5cag_2nd_set_brightness = -0.33");
	}
			break;
	case -2: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xffd1);
		printk ("s5k5cag_2nd_set_brightness = -0.66");
	}
			break;
	case -3: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xffc1);
		printk ("s5k5cag_2nd_set_brightness = -1");
	}
			break;
	case -4: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xffb1);
		printk ("s5k5cag_2nd_set_brightness = -1.33");
	}
			break;
	case -5: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xffa1);
		printk ("s5k5cag_2nd_set_brightness = -1.66");
	}
			break;
	case -6: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0xff81);
		printk ("s5k5cag_2nd_set_brightness = -2");
	}
			break;
	default: {
		printk ("s5k5cag_2nd_set_brightness, wrong value setting\n");
		return -EINVAL;
		}
	}
	s5k5cag_2nd_brightness = brightness;

	return rc;
}
#endif
#ifdef CONFIG_FIH_WB
static long s5k5cag_2nd_set_wb(int wb) 
{
	long rc = 0;

	switch (wb) {
	case WB_AUTO: {
		s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x246E);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //AWB enalbe

		printk ("s5k5cag_2nd_set_wb = WB_AUTO\n");
	}
			break;
	case WB_INCANDESCENT: {
	       s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x246E);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0000); //AWB disable
		
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x04A0);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0400); //REG_SF_USER_Rgain		0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_RgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0400); //REG_SF_USER_Ggain	   	0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_GgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0940); //REG_SF_USER_Bgain		0100=x1 0200=x2	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_BgainChanged
		
		printk ("s5k5cag_2nd_set_wb = WB_INCANDESCENT\n");
	}
			break;
	case WB_FLUORESCENT: {
	       s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x246E);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0000); //AWB disable
		
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x04A0);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0575); //REG_SF_USER_Rgain		0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_RgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0400); //REG_SF_USER_Ggain	   	0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_GgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0800); //REG_SF_USER_Bgain		0100=x1 0200=x2	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_BgainChanged

		printk ("s5k5cag_2nd_set_wb = WB_FLUORESCENT\n");
	}
			break;
	case WB_DAYLIGHT: {
	       s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x246E);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0000); //AWB disable
		
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x04A0);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x05E0); //REG_SF_USER_Rgain		0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_RgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0400); //REG_SF_USER_Ggain	   	0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_GgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0530); //REG_SF_USER_Bgain		0100=x1 0200=x2	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_BgainChanged
		
		printk ("s5k5cag_2nd_set_wb = WB_DAYLIGHT\n");
	}
			break;
	case WB_CLOUDY_DAYLIGHT: {
	       s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0x7000);	
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x246E);
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0000); //AWB disable
		
		s5k5cag_2nd_i2c_write_b_sensor(0x002a, 0x04A0);	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0740); //REG_SF_USER_Rgain		0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_RgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0400); //REG_SF_USER_Ggain	   	0100=x1 0200=x2
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_GgainChanged
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0460); //REG_SF_USER_Bgain		0100=x1 0200=x2	
		s5k5cag_2nd_i2c_write_b_sensor(0x0F12, 0x0001); //REG_SF_USER_BgainChanged
		
		printk ("s5k5cag_2nd_set_wb = WB_CLOUDY_DAYLIGHT\n");
	}
			break;

	default: {
		printk ("s5k5cag_2nd_set_wb, wrong value setting\n");

		return -EINVAL;
		}
	}
	s5k5cag_2nd_wb = wb;

	return rc;
}
#endif
#ifdef CONFIG_FIH_METRY
static long s5k5cag_2nd_set_AE_meter(int meter) 
{
	long rc = 0;
	
	switch (meter) {
	case AE_AUTO: {
		//s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_multi_meter,
    			//	s5k5cag_2nd_regs.reg_multi_meter_size);
		
		printk ("s5k5cag_2nd_set_AE_meter: Auto\n");
	}
			break;
	case AE_CENTER: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_center_meter,
    				s5k5cag_2nd_regs.reg_center_meter_size);

		printk ("s5k5cag_2nd_set_AE_meter: Center\n");
	}
			break;
	case AE_MULTI: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_multi_meter,
    				s5k5cag_2nd_regs.reg_multi_meter_size);

		printk ("s5k5cag_2nd_set_AE_meter: Multi\n");
	}
			break;
	case AE_SPOT: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_sopt_meter,
    				s5k5cag_2nd_regs.reg_sopt_meter_size);

		printk ("s5k5cag_2nd_set_AE_meter: Spot\n");
	}
			break;

	default: {
		printk ("s5k5cag_2nd_set_AE_meter, wrong value setting\n");

		return -EINVAL;
		}
	}
	s5k5cag_2nd_meter = meter;

	return rc;
}
#endif
#ifdef CONFIG_FIH_SCENE
static long s5k5cag_2nd_set_scene(int scene) 
{
	long rc = 0;
	
	if(s5k5cag_2nd_scene == SCENE_NIGHT){
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_night_off_0,
    				s5k5cag_2nd_regs.reg_night_off_0_size);	
		msleep(10);
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_night_off_1,
    				s5k5cag_2nd_regs.reg_night_off_1_size);	
	}

   	if(s5k5cag_2nd_scene == SCENE_SPORT)
	s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_sport_off,
				s5k5cag_2nd_regs.reg_sport_off_size);	
	switch (scene) {
	case SCENE_AUTO: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_auto_scene,
    				s5k5cag_2nd_regs.reg_auto_scene_size);
		
		printk ("s5k5cag_2nd_set_scene auto\n");
	}
			break;
	case SCENE_SNOW: 
	case SCENE_BEACH: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_bench_snow,
    				s5k5cag_2nd_regs.reg_bench_snow_size);

		printk ("s5k5cag_2nd_set_scene snow_beach\n");
	}
			break;
	/* FIH-SW3-MM-UW-tuning0409-00+*/		
	case SCENE_NIGHT: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_night_0,
    				s5k5cag_2nd_regs.reg_night_0_size);
		msleep(10);

		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_night_1,
    				s5k5cag_2nd_regs.reg_night_1_size);

		printk ("s5k5cag_2nd_set_scene night\n");
	}
			break;
	/* FIH-SW3-MM-UW-tuning0409-00-*/		
	case SCENE_SPORT: {
		s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_sport,
    				s5k5cag_2nd_regs.reg_sport_size);

		printk ("s5k5cag_2nd_set_scene sport\n");
	}
			break;
	default: {
		printk ("s5k5cag_2nd_set_scene, wrong value setting\n");

		return -EINVAL;
		}
	}
	s5k5cag_2nd_scene = scene;

	return rc;
}
#endif
/* FIH-SW3-MM-URI-Add WB-00- */
static int32_t s5k5cag_2nd_write_exp_gain(uint16_t gain, uint32_t line)
{
	int32_t rc = 0;
	uint16_t max_legal_gain  = 0x0200;
	uint8_t gain_msb, gain_lsb;
	uint8_t intg_time_msb, intg_time_lsb;

	if (gain > max_legal_gain)
		gain = max_legal_gain;

	/* update gain registers */
	gain_msb = (uint8_t) ((gain & 0xFF00) >> 8);
	gain_lsb = (uint8_t) (gain & 0x00FF);

	intg_time_msb = (uint8_t) ((line & 0xFF00) >> 8);
	intg_time_lsb = (uint8_t) (line & 0x00FF);

	/*s5k5cag_2nd_group_hold_on();

	s5k5cag_2nd_i2c_write_b_sensor(0x0204, gain_msb); //Analogue Gain 
	s5k5cag_2nd_i2c_write_b_sensor(0x0205, gain_lsb);

	//Coarse Integration Time 
	s5k5cag_2nd_i2c_write_b_sensor(0x0202, intg_time_msb);
	s5k5cag_2nd_i2c_write_b_sensor(0x0203, intg_time_lsb);
	s5k5cag_2nd_group_hold_off()*/;

	return rc;
}

static int32_t s5k5cag_2nd_set_pict_exp_gain(uint16_t gain, uint32_t line)
{
	int32_t rc = 0;

	rc = s5k5cag_2nd_write_exp_gain(gain, line);
	return rc;
}

/*MTD-SW3-MM-UW-camframe timeout-06+*/
/* FIH-SW3-MM-SL-AddFlagToPotects5k5cag_2nd_scene-00+{ */          
/*MTD-SW3-MM-UW-camframe timeout-05+*/
/*MTD-SW3-MM-UW-camframe timeout-04+*/
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*{
static int32_t s5k5cag_2nd_sensor_setting(int update_type, int rt)
{
    //unsigned short chipid = 0xFFFF;
    int32_t rc = 0;
    struct msm_camera_csi_params s5k5cag_2nd_csi_params;

    printk("s5k5cag_2nd_sensor_setting----E\n");
    if (update_type == REG_INIT) {
        printk("s5k5cag_2nd_sensor_setting----------INIT\n");
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_arm_go,
                                  s5k5cag_2nd_regs.reg_arn_go_size);
        cam_msleep(10);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_T_P,
                                  s5k5cag_2nd_regs.reg_T_P_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_analog,
                                  s5k5cag_2nd_regs.reg_analog_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_3a,
                                  s5k5cag_2nd_regs.reg_3a_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_clk,
                                  s5k5cag_2nd_regs.reg_clk_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_fps,
                                  s5k5cag_2nd_regs.reg_fps_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_prev,
                                  s5k5cag_2nd_regs.reg_prev_size);
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_settings,
                                  s5k5cag_2nd_regs.reg_size);	
        s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_snap,
                                  s5k5cag_2nd_regs.reg_snap_size);
        STARTUP = 1;
        cam_msleep(100);
    }
    else if (update_type == UPDATE_PERIODIC) 
    {       
        if ((rt == RES_PREVIEW) && (CSI_CONFIG == 0))
        {    
               /* stop streaming ----------------------------------------------------*/
                s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0xd000);
                s5k5cag_2nd_i2c_write_b_sensor(0xC100, 0x0000);//1=stream on , 0=stream off.
                printk("s5k5cag_2nd_sensor_setting: Stop streaming.\n");
                cam_msleep(100);
               /* stop streaming ----------------------------------------------------*/
        
                printk("s5k5cag_2nd_sensor_setting----------CSI config\n");
                msm_camio_vfe_clk_rate_set(192000000);
                s5k5cag_2nd_csi_params.data_format = CSI_8BIT;
                s5k5cag_2nd_csi_params.lane_cnt = 1;
                s5k5cag_2nd_csi_params.lane_assign = 0xe4;
                s5k5cag_2nd_csi_params.dpcm_scheme = 0;
                s5k5cag_2nd_csi_params.settle_cnt = 20;
                rc = msm_camio_csi_config(&s5k5cag_2nd_csi_params);
                cam_msleep(10);
                CSI_CONFIG = 1;

                /* start streaming ----------------------------------------------------*/ 
                s5k5cag_2nd_i2c_write_b_sensor(0x0028, 0xd000);
                s5k5cag_2nd_i2c_write_b_sensor(0xC100, 0x0001);//1=stream on , 0=stream off.
                printk("s5k5cag_2nd_sensor_setting: Start streaming.\n");
                /* start streaming ----------------------------------------------------*/
         }
       
        if (rt == RES_PREVIEW)
        {
                printk("s5k5cag_2nd_sensor_setting----------PREVIEW (delay 100ms)\n");
                s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_snap_to_prev,
                                          s5k5cag_2nd_regs.reg_snap_to_prev_size);

                cam_msleep(100);//Frame time base on 10 FPS
                #ifdef CONFIG_FIH_SCENE	       
                if(s5k5cag_2nd_scene == SCENE_NIGHT)
                        cam_msleep(150);//Frame time base on 4 FPS(100+150)
                #endif
        }
        else if(rt == RES_CAPTURE)
        {
                printk("s5k5cag_2nd_sensor_setting----------CAPTURE (delay 100ms)\n");
                s5k5cag_2nd_i2c_write_b_table(s5k5cag_2nd_regs.reg_prev_to_snap,
                                          s5k5cag_2nd_regs.reg_prev_to_snap_size);   

                #ifdef CONFIG_FIH_SCENE	       
                if(s5k5cag_2nd_scene == SCENE_NIGHT)
                        cam_msleep(250);//Frame time base on 4 FPS
                #endif
        }           
    }
    return rc;
}
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*}
/*MTD-SW3-MM-UW-camframe timeout-04-*/
/*MTD-SW3-MM-UW-camframe timeout-05-*/
/* FIH-SW3-MM-SL-AddFlagToPotects5k5cag_2nd_scene-00+} */
/*MTD-SW3-MM-UW-camframe timeout-06-*/

static int32_t s5k5cag_2nd_video_config(int mode)
{

	int32_t rc = 0;
	int rt;
	printk("s5k5cag_2nd_video_config---------------E\n");
	/* change sensor resolution if needed */
	if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE){
		rt = RES_PREVIEW;
	}
	else
		rt = RES_CAPTURE;
	if (s5k5cag_2nd_sensor_setting(UPDATE_PERIODIC, rt) < 0)
		return rc;

	s5k5cag_2nd_ctrl->curr_res = s5k5cag_2nd_ctrl->prev_res;
	s5k5cag_2nd_ctrl->sensormode = mode;
	return rc;
}

static int32_t s5k5cag_2nd_snapshot_config(int mode)
{
	int32_t rc = 0;
	int rt;
	printk("s5k5cag_2nd_snapshot_config---------------E\n");
	/*change sensor resolution if needed */
	if (s5k5cag_2nd_ctrl->curr_res != s5k5cag_2nd_ctrl->pict_res) {
		if (s5k5cag_2nd_ctrl->pict_res == QTR_SIZE)
			rt = RES_PREVIEW;
		else
			rt = RES_CAPTURE;
		if (s5k5cag_2nd_sensor_setting(UPDATE_PERIODIC, rt) < 0)
			return rc;
	}

	s5k5cag_2nd_ctrl->curr_res = s5k5cag_2nd_ctrl->pict_res;
	s5k5cag_2nd_ctrl->sensormode = mode;
	return rc;
}

static int32_t s5k5cag_2nd_raw_snapshot_config(int mode)
{
	int32_t rc = 0;
	int rt;

	/* change sensor resolution if needed */
	if (s5k5cag_2nd_ctrl->curr_res != s5k5cag_2nd_ctrl->pict_res) {
		if (s5k5cag_2nd_ctrl->pict_res == QTR_SIZE)
			rt = RES_PREVIEW;
		else
			rt = RES_CAPTURE;
		if (s5k5cag_2nd_sensor_setting(UPDATE_PERIODIC, rt) < 0)
			return rc;
	}

	s5k5cag_2nd_ctrl->curr_res = s5k5cag_2nd_ctrl->pict_res;
	s5k5cag_2nd_ctrl->sensormode = mode;
	return rc;
}

static int32_t s5k5cag_2nd_set_sensor_mode(int mode,
		int res)
{
	int32_t rc = 0;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc = s5k5cag_2nd_video_config(mode);
		break;
	case SENSOR_SNAPSHOT_MODE:
		rc = s5k5cag_2nd_snapshot_config(mode);
		break;
	case SENSOR_RAW_SNAPSHOT_MODE:
		rc = s5k5cag_2nd_raw_snapshot_config(mode);
		break;
	 /*MTD-SW3-MM-UW-camframe timeout-03+*/	
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*{
	case SENSOR_RESET_MODE:
		printk("SENSOR_RESET_MODE----------E\n");
		STARTUP = 0;	
		CSI_CONFIG = 0;
        
		/* power off & camio disable*/
		s5k5cag_2nd_power_off();
		cam_msleep(50);//Wait power off done.

		/* power on & camio enable*/
		s5k5cag_2nd_power_on(s5k5cag_2nd_info);	

        if (s5k5cag_2nd_sensor_setting(REG_INIT, RES_PREVIEW) < 0)
            return rc;
		
		/* CSI interface config*/	  
		if (s5k5cag_2nd_sensor_setting(UPDATE_PERIODIC, RES_PREVIEW) < 0)
			return rc;		

	       s5k5cag_2nd_ctrl->curr_res = s5k5cag_2nd_ctrl->prev_res;
	       s5k5cag_2nd_ctrl->sensormode = 0;
		printk("SENSOR_RESET_MODE----------X\n");	  
              break;
	/*MTD-SW3-MM-UW-camframe timeout-03-*/
	default:
		rc = -EINVAL;
		break;
	}
	return rc;
}

/*MM-UW-reduce boot time+01*/
static int s5k5cag_2nd_probe_init_done(const struct msm_camera_sensor_info *data)
{
	CDBG("probe done\n");
	
	s5k5cag_2nd_power_off();
	return 0;
}
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*}
/*MM-UW-reduce boot time-01*/

static int s5k5cag_2nd_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
	int32_t rc = 0;
	uint16_t regaddress = 0x0040;
	uint16_t chipid = 0xFFFF, version = 0xFFFF;

	printk("%s: %d\n", __func__, __LINE__);

	s5k5cag_2nd_i2c_write_b_sensor(0x002C, 0x0000);	

	s5k5cag_2nd_i2c_write_b_sensor(0x002E, 0x0042);
	s5k5cag_2nd_i2c_read(0x0F12, &version, 2);
	
	s5k5cag_2nd_i2c_write_b_sensor(0x002E, regaddress);
	s5k5cag_2nd_i2c_read(0x0F12, &chipid, 2);
	printk ("s5k5cag_2nd_probe_init_sensor: Sensor Chip ID = 0x%x\n",chipid);		

	if (chipid != 0x05CA) {
		rc = -ENODEV;
		printk ("s5k5cag_2nd_probe_init_sensor chip id not match--------------X\n");
		goto init_probe_fail;
	}else{
		printk ("s5k5cag_2nd_probe_init_sensor-------------chip id matched\n");
	}

	printk("ID: %d\n", chipid);

	goto init_probe_done;
init_probe_fail:
	printk("s5k5cag_2nd_probe_init_sensor fails\n");
	s5k5cag_2nd_probe_init_done(data);
init_probe_done:
	printk("s5k5cag_2nd_probe_init_sensor finishes\n");
	return rc;
}


int s5k5cag_2nd_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t rc = 0;

	printk("%s: %d\n", __func__, __LINE__);
	printk("Calling s5k5cag_2nd_sensor_open_init\n");

	s5k5cag_2nd_ctrl = kzalloc(sizeof(struct s5k5cag_2nd_ctrl_t), GFP_KERNEL);
	if (!s5k5cag_2nd_ctrl) {
		CDBG("s5k5cag_2nd_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}
	s5k5cag_2nd_ctrl->fps_divider = 1 * 0x00000400;
	s5k5cag_2nd_ctrl->pict_fps_divider = 1 * 0x00000400;
	s5k5cag_2nd_ctrl->prev_res = QTR_SIZE;
	s5k5cag_2nd_ctrl->pict_res = FULL_SIZE;
       /* FIH-SW3-MM-URI-Fix Code Defect-00+ */
	//if (data)
	/* FIH-SW3-MM-URI-Fix Code Defect-00- */
		s5k5cag_2nd_ctrl->sensordata = data;

    prev_frame_length_lines = 640;
	prev_line_length_pck = 480;

	snap_frame_length_lines = 2048;//640;
	snap_line_length_pck = 1536;//;480;

	/* enable mclk first */
	s5k5cag_2nd_power_on(data);
	
	//rc = s5k5cag_2nd_probe_init_sensor(data);
	//if (rc < 0)
		//goto init_fail; 
	CSI_CONFIG = 0;	

	printk("s5k5cag_2nd_sensor_open_init: init settings\n");
	if(STARTUP == 0)
	{
		if (s5k5cag_2nd_ctrl->prev_res == QTR_SIZE){
			rc = s5k5cag_2nd_sensor_setting(REG_INIT, RES_PREVIEW);
		}
		else{
			printk("s5k5cag_2nd_sensor_open_init: capture settings\n");
			rc = s5k5cag_2nd_sensor_setting(REG_INIT, RES_CAPTURE);
		}
    }

	s5k5cag_2nd_ctrl->fps = 30 * Q8;
	if (rc < 0)
		goto init_fail;
	else
		goto init_done;
init_fail:
	printk("s5k5cag_2nd_sensor_open_init: init_fail\n");
	s5k5cag_2nd_probe_init_done(data);
init_done:
	printk("s5k5cag_2nd_sensor_open_init: init_done\n");
	return rc;
}

static int s5k5cag_2nd_init_client(struct i2c_client *client)
{
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&s5k5cag_2nd_wait_queue);
	return 0;
}

static const struct i2c_device_id s5k5cag_2nd_i2c_id[] = {
	{"s5k5cag_2nd", 0},
	{ }
};

static int s5k5cag_2nd_i2c_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	int rc = 0;
	CDBG("s5k5cag_2nd_probe called!\n");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		CDBG("i2c_check_functionality failed\n");
		goto probe_failure;
	}

	s5k5cag_2nd_sensorw = kzalloc(sizeof(struct s5k5cag_2nd_work_t), GFP_KERNEL);
	if (!s5k5cag_2nd_sensorw) {
		CDBG("kzalloc failed.\n");
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, s5k5cag_2nd_sensorw);
	s5k5cag_2nd_init_client(client);
	s5k5cag_2nd_client = client;

	CDBG("s5k5cag_2nd_probe successed! rc = %d\n", rc);
	return 0;

probe_failure:
	CDBG("s5k5cag_2nd_probe failed! rc = %d\n", rc);
	return rc;
}

static int __devexit s5k5cag_2nd_remove(struct i2c_client *client)
{
	struct s5k5cag_2nd_work_t *sensorw = i2c_get_clientdata(client);
	free_irq(client->irq, sensorw);
	s5k5cag_2nd_client = NULL;
	kfree(sensorw);
	return 0;
}

static struct i2c_driver s5k5cag_2nd_i2c_driver = {
	.id_table = s5k5cag_2nd_i2c_id,
	.probe  = s5k5cag_2nd_i2c_probe,
	.remove = __exit_p(s5k5cag_2nd_i2c_remove),
	.driver = {
		.name = "s5k5cag_2nd",
	},
};

int s5k5cag_2nd_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cdata;
	long   rc = 0;
	if (copy_from_user(&cdata,
				(void *)argp,
				sizeof(struct sensor_cfg_data)))
		return -EFAULT;
	mutex_lock(&s5k5cag_2nd_mut);
	CDBG("s5k5cag_2nd_sensor_config: cfgtype = %d\n",
			cdata.cfgtype);
	switch (cdata.cfgtype) {
	case CFG_GET_PICT_FPS:
		s5k5cag_2nd_get_pict_fps(
			cdata.cfg.gfps.prevfps,
			&(cdata.cfg.gfps.pictfps));

		if (copy_to_user((void *)argp,
			&cdata,
			sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	case CFG_GET_PREV_L_PF:
		cdata.cfg.prevl_pf =
			s5k5cag_2nd_get_prev_lines_pf();

		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	case CFG_GET_PREV_P_PL:
		cdata.cfg.prevp_pl =
			s5k5cag_2nd_get_prev_pixels_pl();

		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	case CFG_GET_PICT_L_PF:
		cdata.cfg.pictl_pf =
			s5k5cag_2nd_get_pict_lines_pf();

		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	case CFG_GET_PICT_P_PL:
		cdata.cfg.pictp_pl =
			s5k5cag_2nd_get_pict_pixels_pl();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	case CFG_GET_PICT_MAX_EXP_LC:
		cdata.cfg.pict_max_exp_lc =
			s5k5cag_2nd_get_pict_max_exp_lc();

		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	/* FIH-SW3-MM-URI-Set FPS-00+ */	
	case CFG_SET_FPS:
	case CFG_SET_PICT_FPS:
		rc = s5k5cag_2nd_set_fps(cdata.cfg.v_fps);
		break;
	/* FIH-SW3-MM-URI-Set FPS-00- */	
	case CFG_SET_EXP_GAIN:
		rc = s5k5cag_2nd_write_exp_gain(cdata.cfg.exp_gain.gain,
				cdata.cfg.exp_gain.line);
		break;
	case CFG_SET_PICT_EXP_GAIN:
		rc = s5k5cag_2nd_set_pict_exp_gain(cdata.cfg.exp_gain.gain,
				cdata.cfg.exp_gain.line);
		break;
	case CFG_SET_MODE:
		rc = s5k5cag_2nd_set_sensor_mode(cdata.mode, cdata.rs);
		break;
	case CFG_PWR_DOWN:
		//rc = s5k5cag_2nd_power_down();
		break;
	case CFG_GET_AF_MAX_STEPS:
		cdata.max_steps = S5K5CAG_2ND_TOTAL_STEPS_NEAR_TO_FAR;
		if (copy_to_user((void *)argp,
					&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
		break;
	/* FIH-SW3-MM-URI-Add WB-00+ */
	#ifdef CONFIG_FIH_BRIGHTNESS
	case CFG_SET_BRIGHTNESS: 
		rc = s5k5cag_2nd_set_brightness(cdata.cfg.brightness);
		break;
	#endif	
	#ifdef CONFIG_FIH_WB	
	case CFG_SET_WB:
		rc = s5k5cag_2nd_set_wb(cdata.cfg.wb);
		break;
	#endif
	#ifdef CONFIG_FIH_METRY
	case CFG_SET_AE_METER: 
		rc = s5k5cag_2nd_set_AE_meter(cdata.cfg.meter);
		break;
	#endif	
	#ifdef CONFIG_FIH_SCENE
	case CFG_SET_SCENE:
		rc = s5k5cag_2nd_set_scene(cdata.cfg.scene);
		break;
	#endif	
	/* FIH-SW3-MM-URI-Add WB-00- */
	//case CFG_SET_EFFECT:
		//rc = s5k5cag_2nd_set_default_focus(cdata.cfg.effect);
		break;
	default:
		rc = -EFAULT;
		break;
	}
	mutex_unlock(&s5k5cag_2nd_mut);

	return rc;
}

//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*{
static int s5k5cag_2nd_sensor_release(void)
{
	int rc = -EBADF;
       printk ("s5k5cag_2nd_sensor_release \n");    
	mutex_lock(&s5k5cag_2nd_mut);

	s5k5cag_2nd_power_off();

	kfree(s5k5cag_2nd_ctrl);
	s5k5cag_2nd_ctrl = NULL;
	//MTD-SW3-MM-UW-camframe timeout-00+{	
	//MTD-SW3-MM-UW-camframe timeout-00+}	
	CDBG("s5k5cag_2nd_release completed\n");
	mutex_unlock(&s5k5cag_2nd_mut);
	
	return rc;
}

static int s5k5cag_2nd_sensor_probe(const struct msm_camera_sensor_info *info,
		struct msm_sensor_ctrl *s)
{
	int rc = 0;
	STARTUP = 0;
    CDBG("s5k5cag_2nd_sensor_probe \n");
    //MTD-SW3-MM-UW-camframe timeout-00+{	
	s5k5cag_2nd_info = info;   
    //MTD-SW3-MM-UW-camframe timeout-00+}
	rc = i2c_add_driver(&s5k5cag_2nd_i2c_driver);
	if (rc < 0 || s5k5cag_2nd_client == NULL) {
		rc = -ENOTSUPP;
		CDBG("I2C add driver failed");
		goto probe_fail_2;
	}

    // Re-config camera pins.
    gpio_tlmm_config(GPIO_CFG(s5k5cag_2nd_info->mclk, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
    gpio_tlmm_config(GPIO_CFG(s5k5cag_2nd_info->sensor_reset, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
    gpio_tlmm_config(GPIO_CFG(s5k5cag_2nd_info->sensor_pwd, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
    gpio_tlmm_config(GPIO_CFG(s5k5cag_2nd_info->vreg_v2p8, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
    
    s5k5cag_2nd_power_on(info);
	
	rc = s5k5cag_2nd_probe_init_sensor(info);
	if (rc < 0)
		goto probe_fail_1;

	s->s_init = s5k5cag_2nd_sensor_open_init;
	s->s_release = s5k5cag_2nd_sensor_release;
	s->s_config  = s5k5cag_2nd_sensor_config;
	//s->s_camera_type = BACK_CAMERA_2D;
	//s->s_mount_angle = 0;
	s->s_mount_angle = info->sensor_platform_info->mount_angle;
	s5k5cag_2nd_probe_init_done(info);
    CDBG("s5k5cag_2nd_sensor_probe: Success. \n");
	return rc;

probe_fail_2:
	i2c_del_driver(&s5k5cag_2nd_i2c_driver);
probe_fail_1:
	CDBG("s5k5cag_2nd_sensor_probe: SENSOR PROBE FAILS!\n");
	return rc;
}
//FIH-SW-MM-MC-FixCameraCamframeTimeoutIssue-00*}

static int __devinit s5k5cag_2nd_probe(struct platform_device *pdev)
{
	CDBG("s5k5cag_2nd_probe: +++++++++++++++\n");
	/*MTD-SW3-MM-UW-camframe timeout-02+*/	
	dev0 = pdev;
       /*MTD-SW3-MM-UW-camframe timeout-02+*/
	return msm_camera_drv_start(pdev, s5k5cag_2nd_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = s5k5cag_2nd_probe,
	.driver = {
		.name = "msm_camera_s5k5cag_2nd",
		.owner = THIS_MODULE,
	},
	.suspend = s5k5cag_2nd_suspend,
	.resume = s5k5cag_2nd_resume,
};

static int __init s5k5cag_2nd_init(void)
{
	return platform_driver_register(&msm_camera_driver);
}

module_init(s5k5cag_2nd_init);
MODULE_DESCRIPTION("Samsung 5 MP Bayer sensor driver");
MODULE_LICENSE("GPL v2");
