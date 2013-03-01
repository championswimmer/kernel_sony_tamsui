/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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

#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>
#include <mach/camera.h>
#include "mt9p111.h"

/*=============================================================
	SENSOR REGISTER DEFINES
==============================================================*/
#define MT9P111_Q8				0x00000100
#define MT9P111_Q8Shift				8
#define MT9P111_Q10				0x00000400
#define MT9P111_Q10Shift				10

/* Omnivision8810 product ID register address */
#define	MT9P111_PIDH_REG				0x0000
#define	MT9P111_PIDL_REG				0x0001
/* Omnivision8810 product ID */
#define	MT9P111_PID				0x97
/* Omnivision8810 version */
#define	MT9P111_VER				0x26
/* Time in milisecs for waiting for the sensor to reset */
#define	MT9P111_RESET_DELAY_MSECS		66
#define	MT9P111_DEFAULT_CLOCK_RATE		24000000
/* Registers*/
#define	MT9P111_GAIN				0x3000
#define	MT9P111_AEC_MSB				0x3002
#define	MT9P111_AEC_LSB				0x3003

/* Color bar pattern selection */
#define MT9P111_COLOR_BAR_PATTERN_SEL_REG	0x600
/* Color bar enabling control */
#define MT9P111_COLOR_BAR_ENABLE_REG		0x601
/* Time in milisecs for waiting for the sensor to reset*/
#define MT9P111_RESET_DELAY_MSECS		66
/* I2C Address of the Sensor */
/*============================================================================
		DATA DECLARATIONS
============================================================================*/
#define MT9P111_FULL_SIZE_DUMMY_PIXELS		0
#define MT9P111_FULL_SIZE_DUMMY_LINES		0
#define MT9P111_QTR_SIZE_DUMMY_PIXELS		0
#define MT9P111_QTR_SIZE_DUMMY_LINES		0

#define MT9P111_FULL_SIZE_WIDTH			2048//480//1024//320
#define MT9P111_FULL_SIZE_HEIGHT			1536//320//768//240

#define MT9P111_QTR_SIZE_WIDTH			480//1024//320
#define MT9P111_QTR_SIZE_HEIGHT			320//768//240

#define MT9P111_HRZ_FULL_BLK_PIXELS		0
#define MT9P111_VER_FULL_BLK_LINES		0
#define MT9P111_HRZ_QTR_BLK_PIXELS		0
#define MT9P111_VER_QTR_BLK_LINES		0

#define MT9P111_MSB_MASK			0xFF00
#define MT9P111_LSB_MASK			0x00FF

struct mt9p111_work_t {
	struct work_struct work;
};
static struct mt9p111_work_t *mt9p111_sensorw;
static struct i2c_client *mt9p111_client;
struct mt9p111_ctrl_t {
	const struct  msm_camera_sensor_info *sensordata;
	uint32_t sensormode;
	uint32_t fps_divider;		/* init to 1 * 0x00000400 */
	uint32_t pict_fps_divider;	/* init to 1 * 0x00000400 */
	uint16_t fps;
	int16_t curr_lens_pos;
	uint16_t curr_step_pos;
	uint16_t my_reg_gain;
	uint32_t my_reg_line_count;
	uint16_t total_lines_per_frame;
	enum mt9p111_resolution_t prev_res;
	enum mt9p111_resolution_t pict_res;
	enum mt9p111_resolution_t curr_res;
	enum mt9p111_test_mode_t  set_test;
	unsigned short imgaddr;
};
static struct mt9p111_ctrl_t *mt9p111_ctrl;
static int8_t config_not_set = 1;
static DECLARE_WAIT_QUEUE_HEAD(mt9p111_wait_queue);
DEFINE_MUTEX(mt9p111_mut);
#if 0
/*=============================================================*/
static int mt9p111_i2c_rxdata(unsigned short saddr,
	unsigned char *rxdata, int length)
{
	struct i2c_msg msgs[] = {
	{
		.addr  = saddr,
		.flags = 0,
		.len   = 2,
		.buf   = rxdata,
	},
	{
		.addr  = saddr,
		.flags = I2C_M_RD,
		.len   = length,
		.buf   = rxdata,
	},
	};

	if (i2c_transfer(mt9p111_client->adapter, msgs, 2) < 0) {
		CDBG("mt9p111_i2c_rxdata failed!\n");
		return -EIO;
	}

	return 0;
}
#endif
static int32_t mt9p111_i2c_txdata(unsigned short saddr,
				unsigned char *txdata, int length)
{
	struct i2c_msg msg[] = {
		{
		 .addr = saddr ,
		 .flags = 0,
		 .len = length,
		 .buf = txdata,
		 },
	};

	if (i2c_transfer(mt9p111_client->adapter, msg, 1) < 0) {
		pr_emerg("mt9p111_i2c_txdata faild 0x%x\n", mt9p111_client->addr);
		return -EIO;
	}

	return 0;
}
#if 0
static int32_t mt9p111_i2c_read(unsigned short raddr,
				unsigned short *rdata, int rlen)
{
	int32_t rc = 0;
	unsigned char buf[2];

	if (!rdata)
		return -EIO;

	buf[0] = (raddr & MT9P111_MSB_MASK) >> 8;
	buf[1] = (raddr & MT9P111_LSB_MASK);

	rc = mt9p111_i2c_rxdata(mt9p111_client->addr, buf, rlen);

	if (rc < 0) {
		CDBG("mt9p111_i2c_read 0x%x failed!\n", raddr);
		return rc;
	}

	*rdata = (rlen == 2 ? buf[0] << 8 | buf[1] : buf[0]);
	return rc;
}
#endif
static int32_t mt9p111_i2c_write_b(unsigned short saddr,
	unsigned short waddr, uint16_t bdata,uint16_t  type)
{
	int32_t rc = -EFAULT;
	unsigned char buf[4];
      if(type==16)
      	{
			buf[0] = (waddr & 0xFF00)>>8;
			buf[1] = (waddr & 0x00FF);
			buf[2] = (bdata & 0xFF00)>>8;
			buf[3] = (bdata & 0x00FF);

	pr_emerg("i2c_write_b addr -4byte= 0x%x, val = 0x%x\n", waddr, bdata);
	rc = mt9p111_i2c_txdata(saddr, buf, 4);
      	}
      else if(type==8)
      	{
			buf[0] = (waddr & 0xFF00)>>8;
			buf[1] = (waddr & 0x00FF);
			buf[2] = (bdata & 0x00FF);

	pr_emerg("i2c_write_b addr-3byte = 0x%x, val = 0x%x\n", waddr, bdata);
	rc = mt9p111_i2c_txdata(saddr, buf, 3);
      	}	
	else
	{
                     buf[0] = (waddr & 0xFF00)>>8;
			buf[1] = (waddr & 0x00FF);
			buf[2] = (bdata & 0xFF00)>>8;
			buf[3] = (bdata & 0x00FF);

	CDBG("i2c_write_b addr -else-4byte= 0x%x, val = 0x%x\n", waddr, bdata);
	rc = mt9p111_i2c_txdata(saddr, buf, 4);




	}
	
	if (rc < 0) {
		pr_emerg("i2c_write_b failed, addr = 0x%x, val = 0x%x!\n",
			 waddr, bdata);
	}

	return rc;
}
#if 0
static void mt9p111_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
	uint32_t divider;	/*Q10 */
	uint32_t d1;
	uint32_t d2;
	uint16_t snapshot_height, preview_height, preview_width, snapshot_width;
pr_emerg("Peter-mt9p111_get_pict_fps() prev_res:%d pict_res:%d",mt9p111_ctrl->prev_res,mt9p111_ctrl->pict_res);
	if (mt9p111_ctrl->prev_res == QTR_SIZE) {
		preview_width = mt9p111_QTR_SIZE_WIDTH +
			MT9P111_HRZ_QTR_BLK_PIXELS ;
		preview_height = MT9P111_QTR_SIZE_HEIGHT +
			MT9P111_VER_QTR_BLK_LINES ;
	} else {
		/* full size resolution used for preview. */
		preview_width = MT9P111_FULL_SIZE_WIDTH +
			MT9P111_HRZ_FULL_BLK_PIXELS ;
		preview_height = MT9P111_FULL_SIZE_HEIGHT +
			MT9P111_VER_FULL_BLK_LINES ;
	}
	if (mt9p111_ctrl->pict_res == QTR_SIZE) {
		snapshot_width  = MT9P111_QTR_SIZE_WIDTH +
			MT9P111_HRZ_QTR_BLK_PIXELS ;
		snapshot_height = MT9P111_QTR_SIZE_HEIGHT +
			MT9P111_VER_QTR_BLK_LINES ;
	} else {
		snapshot_width  = MT9P111_FULL_SIZE_WIDTH +
			MT9P111_HRZ_FULL_BLK_PIXELS;
		snapshot_height = MT9P111_FULL_SIZE_HEIGHT +
			MT9P111_VER_FULL_BLK_LINES;
	}

	d1 = (uint32_t)(((uint32_t)preview_height <<
		MT9P111_Q10Shift) /
		snapshot_height);

	d2 = (uint32_t)(((uint32_t)preview_width <<
		MT9P111_Q10Shift) /
		 snapshot_width);

	divider = (uint32_t) (d1 * d2) >> MT9P111_Q10Shift;
	*pfps = (uint16_t)((uint32_t)(fps * divider) >> MT9P111_Q10Shift);
pr_emerg("Peter-mt9p111_get_pict_fps() *pfps:%d",*pfps);
}
static uint16_t mt9p111_get_prev_lines_pf(void)
{
pr_emerg("Peter-mt9p111_get_prev_lines_pf() prev_res:%d",mt9p111_ctrl->prev_res);
	if (mt9p111_ctrl->prev_res == QTR_SIZE)
		return mt9p111_QTR_SIZE_HEIGHT + MT9P111_VER_QTR_BLK_LINES;
	else
		return MT9P111_FULL_SIZE_HEIGHT + MT9P111_VER_FULL_BLK_LINES;
}

static uint16_t mt9p111_get_prev_pixels_pl(void)
{
pr_emerg("Peter-mt9p111_get_prev_pixels_pl() prev_res:%d",mt9p111_ctrl->prev_res);
	if (mt9p111_ctrl->prev_res == QTR_SIZE)
		return MT9P111_QTR_SIZE_WIDTH + MT9P111_HRZ_QTR_BLK_PIXELS;
	else
		return MT9P111_FULL_SIZE_WIDTH + MT9P111_HRZ_FULL_BLK_PIXELS;
}

static uint16_t mt9p111_get_pict_lines_pf(void)
{
pr_emerg("Peter-mt9p111_get_pict_lines_pf() pict_res:%d",mt9p111_ctrl->pict_res);
	if (mt9p111_ctrl->pict_res == QTR_SIZE)
		return MT9P111_QTR_SIZE_HEIGHT + MT9P111_VER_QTR_BLK_LINES;
	else
		return MT9P111_FULL_SIZE_HEIGHT + MT9P111_VER_FULL_BLK_LINES;
}

static uint16_t mt9p111_get_pict_pixels_pl(void)
{
pr_emerg("Peter-mt9p111_get_pict_pixels_pl() pict_res:%d",mt9p111_ctrl->pict_res);
	if (mt9p111_ctrl->pict_res == QTR_SIZE)
		return MT9P111_QTR_SIZE_WIDTH + MT9P111_HRZ_QTR_BLK_PIXELS;
	else
		return MT9P111_FULL_SIZE_WIDTH + MT9P111_HRZ_FULL_BLK_PIXELS;
}

static uint32_t mt9p111_get_pict_max_exp_lc(void)
{
pr_emerg("Peter-mt9p111_get_pict_max_exp_lc() pict_res:%d",mt9p111_ctrl->pict_res);
	if (mt9p111_ctrl->pict_res == QTR_SIZE)
		return (MT9P111_QTR_SIZE_HEIGHT + MT9P111_VER_QTR_BLK_LINES)*24;
	else
		return (MT9P111_FULL_SIZE_HEIGHT + MT9P111_VER_FULL_BLK_LINES)*24;
}

static int32_t mt9p111_set_fps(struct fps_cfg	*fps)
{
	int32_t rc = 0;
pr_emerg("Peter-mt9p111_set_fps() fps_div:%d f_mult:%d",fps->fps_div,fps->f_mult);
	CDBG("%s: fps->fps_div = %d\n", __func__, fps->fps_div);
	/* TODO: Passing of fps_divider from user space has issues. */
	/* mt9p111_ctrl->fps_divider = fps->fps_div; */
	mt9p111_ctrl->fps_divider = 1 * 0x400;
	CDBG("%s: mt9p111_ctrl->fps_divider = %d\n", __func__,
		mt9p111_ctrl->fps_divider);
	mt9p111_ctrl->pict_fps_divider = fps->pict_fps_div;
	mt9p111_ctrl->fps = fps->f_mult;
	return rc;
}

static int32_t mt9p111_write_exp_gain(uint16_t gain, uint32_t line)
{
	static uint16_t max_legal_gain = 0x00FF;
	uint8_t gain_msb, gain_lsb;
	uint8_t intg_time_msb, intg_time_lsb;
	uint8_t mt9p111_offset = 6;
	uint8_t line_length_pck_msb, line_length_pck_lsb;
	uint16_t line_length_pck, frame_length_lines;
	uint32_t line_length_ratio = 1 << MT9P111_Q8Shift;
	int32_t rc = -1;
pr_emerg("Peter-mt9p111_write_exp_gain() sensormode:%d",mt9p111_ctrl->sensormode);
	CDBG("%s: gain = %d	line = %d", __func__, gain, line);

	if (mt9p111_ctrl->sensormode != SENSOR_SNAPSHOT_MODE) {
		if (mt9p111_ctrl->curr_res == QTR_SIZE) {
			frame_length_lines = MT9P111_QTR_SIZE_HEIGHT +
			 MT9P111_VER_QTR_BLK_LINES;
			line_length_pck = MT9P111_QTR_SIZE_WIDTH	+
			 MT9P111_HRZ_QTR_BLK_PIXELS;
		} else {
			frame_length_lines = MT9P111_FULL_SIZE_HEIGHT +
				MT9P111_VER_FULL_BLK_LINES;
			line_length_pck = MT9P111_FULL_SIZE_WIDTH +
				MT9P111_HRZ_FULL_BLK_PIXELS;
		}
		if (line > (frame_length_lines - mt9p111_offset))
			mt9p111_ctrl->fps = (uint16_t) (((uint32_t)30 <<
				MT9P111_Q8Shift) *
				(frame_length_lines - mt9p111_offset) / line);
		else
			mt9p111_ctrl->fps = (uint16_t) ((uint32_t)30 <<
				MT9P111_Q8Shift);
	} else {
		frame_length_lines = MT9P111_FULL_SIZE_HEIGHT +
			MT9P111_VER_FULL_BLK_LINES;
		line_length_pck = MT9P111_FULL_SIZE_WIDTH +
			MT9P111_HRZ_FULL_BLK_PIXELS;
	}

	if (mt9p111_ctrl->sensormode != SENSOR_SNAPSHOT_MODE) {
		line = (uint32_t) (line * mt9p111_ctrl->fps_divider) >>
			MT9P111_Q10Shift;
	} else {
		line = (uint32_t) (line * mt9p111_ctrl->pict_fps_divider) >>
			MT9P111_Q10Shift;
	}

	/* calculate line_length_ratio */
	if (line > (frame_length_lines - mt9p111_offset)) {
		line_length_ratio = (line << mt9p111_Q8Shift) /
			(frame_length_lines - mt9p111_offset);
		line = frame_length_lines - mt9p111_offset;
	} else
		line_length_ratio = (uint32_t)1 << MT9P111_Q8Shift;

	if (gain > max_legal_gain) {
		/* range:	0	to 224 */
		gain = max_legal_gain;
	}
	/* update	gain registers */
	gain_msb = (uint8_t) ((gain & 0xFF00) >> 8);
	gain_lsb = (uint8_t) (gain & 0x00FF);
	/* linear	AFR	horizontal stretch */
	line_length_pck = (uint16_t) ((line_length_pck *
		line_length_ratio) >> MT9P111_Q8Shift);
	line_length_pck_msb = (uint8_t) ((line_length_pck & 0xFF00) >> 8);
	line_length_pck_lsb = (uint8_t) (line_length_pck & 0x00FF);
	/* update	line count registers */
	intg_time_msb = (uint8_t) ((line & 0xFF00) >> 8);
	intg_time_lsb = (uint8_t) (line	& 0x00FF);
#if 0
	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x104, 0x1);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x204, gain_msb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x205, gain_lsb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x342,
		line_length_pck_msb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x343,
		line_length_pck_lsb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x0202, intg_time_msb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x0203, intg_time_lsb);
	if (rc < 0)
		return rc;

	rc = mt9p111_i2c_write_b(mt9p111_client->addr, 0x104, 0x0);
	if (rc < 0)
		return rc;
#endif
	return rc;
}

static int32_t mt9p111_set_pict_exp_gain(uint16_t gain, uint32_t line)
{
	int32_t rc = 0;
	rc = mt9p111_write_exp_gain(gain, line);
pr_emerg("Peter-mt9p111_set_pict_exp_gain() gain:%d line:%d rc:%d",gain,line,rc);
	return rc;
}
#endif

static int32_t mt9p111_set_wb(struct wb_info_cfg	*wb)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
pr_emerg("Peter-mt9p111_set_wb()blue:%d green:%d red:%d",wb->blue_gain,wb->green_gain,wb->red_gain);
#if 1
	j = (wb->red_gain-1)%MT9P111_WB_MAX;
	if(mt9p111_WB[j]!=NULL)
	{
		while(mt9p111_WB[j][i].reg_addr!=0)
		{
			rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_WB[j][i].reg_addr,mt9p111_WB[j][i].reg_val,mt9p111_WB[j][i].reg_type);
			if( rc != 0 )
				break;
			if(mt9p111_WB[j][i].timer!=0)
				msleep(mt9p111_WB[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}
static int32_t mt9p111_set_exposure_mode(struct exp_gain_cfg	*exposure)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
pr_emerg("Peter-mt9p111_set_exposure_mode()gain:%d ",exposure->gain);
#if 1
	j = (exposure->gain)%MT9P111_EXPOSURE_MAX;
	if(mt9p111_exposure[j]!=NULL)
	{
		while(mt9p111_exposure[j][i].reg_addr!=0)
		{
			rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_exposure[j][i].reg_addr,mt9p111_exposure[j][i].reg_val,mt9p111_exposure[j][i].reg_type);
			if( rc != 0 )
				break;
			if(mt9p111_exposure[j][i].timer!=0)
				msleep(mt9p111_exposure[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}

static int32_t mt9p111_set_brightness(struct exp_gain_cfg	*bright)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
pr_emerg("Peter-mt9p111_set_brightness()gain:%d ",bright->gain);
#if 1
	j = (bright->gain)%MT9P111_BRIGHTNESS_MAX;
	if(mt9p111_brightness[j]!=NULL)
	{
		while(mt9p111_brightness[j][i].reg_addr!=0)
		{
			rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_brightness[j][i].reg_addr,mt9p111_brightness[j][i].reg_val,mt9p111_brightness[j][i].reg_type);
			if( rc != 0 )
				break;
			if(mt9p111_brightness[j][i].timer!=0)
				msleep(mt9p111_brightness[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}
static int32_t mt9p111_set_effect(int8_t  effect)
{
	int32_t rc = 0;
	int8_t reg_num=0,effect_num=0;
#if 1	 
	pr_emerg("Peter-mt9p111_set_effect()effect:%d ",effect);

	effect_num=effect;

	if(mt9p111_effect[effect_num]!=NULL)
	{
		while(mt9p111_effect[effect_num][reg_num].reg_addr!=0)
		{
			rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_effect[effect_num][reg_num].reg_addr,mt9p111_effect[effect_num][reg_num].reg_val,mt9p111_effect[effect_num][reg_num].reg_type);
			if( rc != 0 )
				break;
			if(mt9p111_effect[effect_num][reg_num].timer!=0)
				msleep(mt9p111_effect[effect_num][reg_num].timer);
			reg_num++;
		}
	}
	return rc;
#else
       int32_t rc = 0;
	int8_t i=0;
	switch(effect)
	{
		case CAMERA_EFFECT_OFF:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_OFF ");
			while(MT9P111_effect_NONE[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_NONE[i].reg_addr,MT9P111_effect_NONE[i].reg_val,MT9P111_effect_NONE[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_NONE[i].timer!=0)
					msleep(MT9P111_effect_NONE[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_MONO:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_MONO ");
			while(MT9P111_effect_MONO[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_MONO[i].reg_addr,MT9P111_effect_MONO[i].reg_val,MT9P111_effect_MONO[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_MONO[i].timer!=0)
					msleep(MT9P111_effect_MONO[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_NEGATIVE:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_NEGATIVE ");
			while(MT9P111_effect_NEGATIVE[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_NEGATIVE[i].reg_addr,MT9P111_effect_NEGATIVE[i].reg_val,MT9P111_effect_NEGATIVE[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_NEGATIVE[i].timer!=0)
					msleep(MT9P111_effect_NEGATIVE[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_AQUA:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_AQUA ");
			while(MT9P111_effect_AQUA[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_AQUA[i].reg_addr,MT9P111_effect_AQUA[i].reg_val,MT9P111_effect_AQUA[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_AQUA[i].timer!=0)
					msleep(MT9P111_effect_AQUA[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_SEPIA:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_SEPIA ");
			while(MT9P111_effect_SEPIA[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_SEPIA[i].reg_addr,MT9P111_effect_SEPIA[i].reg_val,MT9P111_effect_SEPIA[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_SEPIA[i].timer!=0)
					msleep(MT9P111_effect_SEPIA[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_POSTERIZE:
			pr_emerg("Peter-mt9p111_set_effect() CAMERA_EFFECT_POSTERIZE ");
			while(MT9P111_effect_SKETCH[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_SKETCH[i].reg_addr,MT9P111_effect_SKETCH[i].reg_val,MT9P111_effect_SKETCH[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_SKETCH[i].timer!=0)
					msleep(MT9P111_effect_SKETCH[i].timer);
				i++;
			}
			break;

		default:
			pr_emerg("Peter-mt9p111_set_effect() default ");
			while(MT9P111_effect_NONE[i].reg_addr!=0)
			{
				rc=mt9p111_i2c_write_b(mt9p111_client->addr, MT9P111_effect_NONE[i].reg_addr,MT9P111_effect_NONE[i].reg_val,MT9P111_effect_NONE[i].reg_type);
				if( rc != 0 )
					break;
				if(MT9P111_effect_NONE[i].timer!=0)
					msleep(MT9P111_effect_NONE[i].timer);
				i++;
			}
			break;

	}	
	return rc;
#endif	
}
static int32_t initialize_mt9p111_registers(void)
{
	int32_t i;
	int32_t rc = 0;
pr_emerg("Peter-initialize_mt9p111_registers()");
	mt9p111_ctrl->sensormode = SENSOR_PREVIEW_MODE ;
	/* Configure sensor for Preview mode and Snapshot mode */
	CDBG("Initialize_mt9p111_registers\n");
	for (i = 0; i < mt9p111_array_length; i++) {
		rc = mt9p111_i2c_write_b(mt9p111_client->addr,
			mt9p111_init_settings_array[i].reg_addr,
			mt9p111_init_settings_array[i].reg_val,
			mt9p111_init_settings_array[i].reg_type
			);
	if (rc < 0)
	{
pr_emerg("Peter-initialize_mt9p111_registers() rc:%d i=%d",rc,i);
		return rc;
	}
	if(mt9p111_init_settings_array[i].timer != 0)
		msleep(mt9p111_init_settings_array[i].timer);
	pr_emerg("Peter-initialize_mt9p111_registers() delay:%d ",mt9p111_init_settings_array[i].timer);
	}
	msleep(100);
pr_emerg("Peter-initialize_mt9p111_registers() rc:%d i=%d",rc,i);
	return rc;
}

static int32_t mt9p111_video_config(int mode)
{
	int32_t rc = 0;
	int32_t i;
pr_emerg("Peter-mt9p111_video_config() mode:%d config_not_set:%d",mode,config_not_set);
	mt9p111_ctrl->sensormode = mode;

	if (config_not_set) {
		struct msm_camera_csi_params mt9p111_csi_params;

		/* sensor in standby */
//		mt9p111_i2c_write_b(mt9p111_client->addr, 0x100, 0);
//		msleep(5);
		/* Initialize Sensor registers */
		msm_camio_vfe_clk_rate_set(192000000);
		mt9p111_csi_params.data_format = CSI_8BIT;
		mt9p111_csi_params.lane_cnt = 1;
		mt9p111_csi_params.lane_assign = 0xe4;
		mt9p111_csi_params.dpcm_scheme = 0;
		mt9p111_csi_params.settle_cnt = 24;

		rc = msm_camio_csi_config(&mt9p111_csi_params);
pr_emerg("Peter-mt9p111_video_config() rc:%d ",rc);
		rc = initialize_mt9p111_registers();
		config_not_set = 0;
	}
	else
	{
		while(mt9p111_preview[i].reg_addr!=0)
		{
			pr_emerg("Peter-mt9p111_snapshot_config() reg_addr:%d",mt9p111_preview[i].reg_addr);
			rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_preview[i].reg_addr,mt9p111_preview[i].reg_val,mt9p111_preview[i].reg_type);
			if( rc != 0 )
				break;
			if(mt9p111_preview[i].timer!=0)
				msleep(mt9p111_preview[i].timer);
			i++;
		}
	}
	return rc;
}

static int32_t mt9p111_snapshot_config(int mode)
{
	int32_t rc = 0;
	int32_t i;
pr_emerg("Peter-mt9p111_snapshot_config() mode:%d",mode);
	mt9p111_ctrl->sensormode = mode;
	while(mt9p111_capture[i].reg_addr!=0)
	{
		pr_emerg("Peter-mt9p111_snapshot_config() reg_addr:%d",mt9p111_capture[i].reg_addr);
		rc=mt9p111_i2c_write_b(mt9p111_client->addr, mt9p111_capture[i].reg_addr,mt9p111_capture[i].reg_val,mt9p111_capture[i].reg_type);
		if( rc != 0 )
			break;
		if(mt9p111_capture[i].timer!=0)
			msleep(mt9p111_capture[i].timer);
		i++;
	}
	return rc;
}

static int32_t mt9p111_raw_snapshot_config(int mode)
{
	int32_t rc = 0;
pr_emerg("Peter-mt9p111_raw_snapshot_config() mode:%d",mode);
	mt9p111_ctrl->sensormode = mode;
	return rc;
}

static int32_t mt9p111_set_sensor_mode(int  mode,
			int  res)
{
	int32_t rc = 0;
pr_emerg("Peter-mt9p111_set_sensor_mode() mode:%d",mode);
	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc = mt9p111_video_config(mode);
		break;
	case SENSOR_SNAPSHOT_MODE:
		rc = mt9p111_snapshot_config(mode);
		break;
	case SENSOR_RAW_SNAPSHOT_MODE:
		rc = mt9p111_raw_snapshot_config(mode);
		break;
	default:
		rc = -EINVAL;
		break;
	}
pr_emerg("Peter-mt9p111_set_sensor_mode() rc:%d",rc);
	return rc;
}

static int mt9p111_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
	int32_t rc = 0;
//	uint16_t  chipidh=0;
	//		int value;
	pr_emerg("Peter-mt9p111_probe_init_sensor() RST:%d PWD:%d",data->sensor_reset,data->vcm_pwd);

	/* set PWDN pin to low*/
	gpio_set_value(27, 1);
	mdelay(10);
	/* set Reset pin to low*/
	gpio_set_value(26, 0);
	mdelay(100);
	/* set PWDN pin to high*/
	gpio_set_value(27, 0);
	mdelay(10);
	/* set Reset pin to high*/
	gpio_set_value(26, 1);
	mdelay(100);

	/* 3. Read sensor Model ID: */
	/* 4. Compare sensor ID to MT9P111 ID: */
	pr_emerg("Peter-mt9p111_probe_init_sensor() chipidh == MT9P111_PID ");
	msleep(MT9P111_RESET_DELAY_MSECS);
	CDBG("after delay\n");
	goto init_probe_done;

init_probe_done:
	pr_emerg("Peter-mt9p111_probe_init_sensor() rc:%x ",rc);
	printk(KERN_INFO " mt9p111_probe_init_sensor finishes\n");
	return rc;
}

int mt9p111_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t  rc;
pr_emerg("Peter-mt9p111_sensor_open_init()");

	CDBG("Calling mt9p111_sensor_open_init\n");
	mt9p111_ctrl = kzalloc(sizeof(struct mt9p111_ctrl_t), GFP_KERNEL);
	if (!mt9p111_ctrl) {
		CDBG("mt9p111_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}
	mt9p111_ctrl->curr_lens_pos = -1;
	mt9p111_ctrl->fps_divider = 1 << MT9P111_Q10Shift;
	mt9p111_ctrl->pict_fps_divider = 1 << MT9P111_Q10Shift;
	mt9p111_ctrl->set_test = TEST_OFF;
	mt9p111_ctrl->prev_res = QTR_SIZE;//FULL_SIZE;
	mt9p111_ctrl->pict_res = FULL_SIZE;
	mt9p111_ctrl->curr_res = INVALID_SIZE;
	config_not_set = 1;
	if (data)
		mt9p111_ctrl->sensordata = data;
	/* enable mclk first */
	msm_camio_clk_rate_set(MT9P111_DEFAULT_CLOCK_RATE);
	msleep(20);
	rc = mt9p111_probe_init_sensor(data);
	if (rc < 0)
		goto init_fail;

	mt9p111_ctrl->fps = (uint16_t)(30 << MT9P111_Q8Shift);
	/* generate test pattern */
	if (rc < 0)
		goto init_fail;
	else
		goto init_done;
	/* reset the driver state */
init_fail:
	CDBG(" init_fail\n");
	kfree(mt9p111_ctrl);
init_done:
	CDBG("init_done\n");
	return rc;
}

static int mt9p111_init_client(struct i2c_client *client)
{
pr_emerg("Peter-mt9p111_init_client()");
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&mt9p111_wait_queue);
	return 0;
}

static const struct i2c_device_id mt9p111_i2c_id[] = {
	{ "mt9p111", 0},
	{ }
};

static int mt9p111_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
pr_emerg("Peter-mt9p111_i2c_probe()");
	CDBG("mt9p111_probe called!\n");
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		CDBG("i2c_check_functionality failed\n");
		goto probe_failure;
	}
	mt9p111_sensorw = kzalloc(sizeof(struct mt9p111_work_t), GFP_KERNEL);
	if (!mt9p111_sensorw) {
		CDBG("kzalloc failed.\n");
		rc = -ENOMEM;
		goto probe_failure;
	}
	i2c_set_clientdata(client, mt9p111_sensorw);
	mt9p111_init_client(client);
	mt9p111_client = client;
	msleep(50);
	pr_emerg("mt9p111_probe successed! rc = %d\n", rc);
	return 0;
probe_failure:
	pr_emerg("mt9p111_probe failed! rc = %d\n", rc);
	return rc;
}

static int __exit mt9p111_remove(struct i2c_client *client)
{
	struct mt9p111_work_t_t *sensorw = i2c_get_clientdata(client);
pr_emerg("Peter-mt9p111_remove()");
	free_irq(client->irq, sensorw);
	mt9p111_client = NULL;
	kfree(sensorw);
	return 0;
}

static struct i2c_driver mt9p111_i2c_driver = {
	.id_table = mt9p111_i2c_id,
	.probe	= mt9p111_i2c_probe,
	.remove = __exit_p(mt9p111_i2c_remove),
	.driver = {
		.name = "mt9p111",
	},
};

int mt9p111_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cdata;
	int   rc = 0;

	if (copy_from_user(&cdata,
				(void *)argp,
				sizeof(struct sensor_cfg_data)))
		return -EFAULT;
	mutex_lock(&mt9p111_mut);
	CDBG("mt9p111_sensor_config: cfgtype = %d\n",
		cdata.cfgtype);
pr_emerg("Peter-mt9p111_sensor_config() cfgtype:%d",cdata.cfgtype);
	switch (cdata.cfgtype) {
	case CFG_GET_PICT_FPS:
#if 0
		mt9p111_get_pict_fps(cdata.cfg.gfps.prevfps,
				&(cdata.cfg.gfps.pictfps));
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
			break;
	case CFG_GET_PREV_L_PF:
#if 0
		cdata.cfg.prevl_pf = mt9p111_get_prev_lines_pf();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PREV_P_PL:
#if 0
		cdata.cfg.prevp_pl = mt9p111_get_prev_pixels_pl();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_L_PF:
#if 0
		cdata.cfg.pictl_pf = mt9p111_get_pict_lines_pf();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_P_PL:
#if 0
		cdata.cfg.pictp_pl =
				mt9p111_get_pict_pixels_pl();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_MAX_EXP_LC:
#if 0
		cdata.cfg.pict_max_exp_lc = mt9p111_get_pict_max_exp_lc();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_SET_FPS:
	case CFG_SET_PICT_FPS:
#if 0
		rc = mt9p111_set_fps(&(cdata.cfg.fps));
#endif
		break;
	case CFG_SET_EXP_GAIN:
#if 0
		rc = mt9p111_write_exp_gain(
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
#endif
		break;
	case CFG_SET_PICT_EXP_GAIN:
#if 0
		rc = mt9p111_set_pict_exp_gain(
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
#endif
		break;
	case CFG_SET_MODE:
		rc = mt9p111_set_sensor_mode(cdata.mode,
						cdata.rs);
		break;
		case CFG_SET_EFFECT:
		rc = mt9p111_set_effect(cdata.cfg.effect);
		break;
	case CFG_SET_WB:
		rc = mt9p111_set_wb(&(cdata.cfg.wb_info));
		break;
	case CFG_SET_EXPOSURE_MODE:
		rc = mt9p111_set_exposure_mode(&(cdata.cfg.exp_gain));
		break;
	case CFG_SET_BRIGHTNESS:
		rc = mt9p111_set_brightness(&(cdata.cfg.exp_gain));
		break;
	case CFG_PWR_DOWN:
	case CFG_MOVE_FOCUS:
	case CFG_SET_DEFAULT_FOCUS:
		rc = 0;
		break;
	
	default:
		rc = -EFAULT;
		break;
	}
pr_emerg("Peter-mt9p111_sensor_config() rc:%d",rc);
	mutex_unlock(&mt9p111_mut);
	return rc;
}

static int mt9p111_probe_init_done(const struct msm_camera_sensor_info *data)
{
pr_emerg("Peter-mt9p111_probe_init_done()");
	if (data->sensor_reset_enable) {
		gpio_direction_output(data->sensor_reset, 0);
		gpio_free(data->sensor_reset);
	}
	return 0;
}

static int mt9p111_sensor_release(void)
{
	int rc = -EBADF;
pr_emerg("Peter-mt9p111_sensor_release()");
	mutex_lock(&mt9p111_mut);

	/* set PWDN pin to low*/
	gpio_set_value(26, 0);
	mdelay(10);
	/* set PWDN pin to low*/
	gpio_set_value(27, 0);
	mdelay(10);
	
	gpio_direction_output(mt9p111_ctrl->sensordata->sensor_reset,
		0);
	gpio_free(mt9p111_ctrl->sensordata->sensor_reset);
	kfree(mt9p111_ctrl);
	mt9p111_ctrl = NULL;
	CDBG("mt9p111_release completed\n");
	mutex_unlock(&mt9p111_mut);
	return rc;
}

static int mt9p111_sensor_probe(const struct msm_camera_sensor_info *info,
		struct msm_sensor_ctrl *s)
{
	int rc = 0;

pr_emerg("Peter-mt9p111_sensor_probe()");
	rc = i2c_add_driver(&mt9p111_i2c_driver);
	if (rc < 0 || mt9p111_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_fail;
	}
	msm_camio_clk_rate_set(24000000);
	msleep(20);
	rc = mt9p111_probe_init_sensor(info);
	if (rc < 0)
		goto probe_fail;

	s->s_init = mt9p111_sensor_open_init;
	s->s_release = mt9p111_sensor_release;
	s->s_config  = mt9p111_sensor_config;
//	s->s_camera_type = BACK_CAMERA_2D;
	s->s_mount_angle = info->sensor_platform_info->mount_angle;
	mt9p111_probe_init_done(info);

	return rc;

probe_fail:
	CDBG("SENSOR PROBE FAILS!\n");
	return rc;
}

static int __mt9p111_probe(struct platform_device *pdev)
{
pr_emerg("Peter-__mt9p111_probe()");
	return msm_camera_drv_start(pdev, mt9p111_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = __mt9p111_probe,
	.driver = {
		.name = "msm_camera_mt9p111",
		.owner = THIS_MODULE,
	},
};

static int __init mt9p111_init(void)
{
pr_emerg("Peter-mt9p111_init()");
	return platform_driver_register(&msm_camera_driver);
}

module_init(mt9p111_init);
void mt9p111_exit(void)
{
pr_emerg("Peter-mt9p111_exit()");
	i2c_del_driver(&mt9p111_i2c_driver);
}

MODULE_DESCRIPTION("OMNI VGA Bayer sensor driver");
MODULE_LICENSE("GPL v2");


