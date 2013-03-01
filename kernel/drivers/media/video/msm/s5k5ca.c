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
#include "s5k5ca.h"

//#define CAMERA_DBG
/*=============================================================
	SENSOR REGISTER DEFINES
==============================================================*/
#define S5K5CA_Q8				0x00000100
#define S5K5CA_Q8Shift				8
#define S5K5CA_Q10				0x00000400
#define S5K5CA_Q10Shift				10

/* Omnivision8810 product ID register address */
#define	S5K5CA_PIDH_REG				0x0000
#define	S5K5CA_PIDL_REG				0x0001
/* Omnivision8810 product ID */
#define	S5K5CA_PID				0x97
/* Omnivision8810 version */
#define	S5K5CA_VER				0x26
/* Time in milisecs for waiting for the sensor to reset */
#define	S5K5CA_RESET_DELAY_MSECS		66
#define	S5K5CA_DEFAULT_CLOCK_RATE		24000000
/* Registers*/
#define	S5K5CA_GAIN				0x3000
#define	S5K5CA_AEC_MSB				0x3002
#define	S5K5CA_AEC_LSB				0x3003

/* Color bar pattern selection */
#define S5K5CA_COLOR_BAR_PATTERN_SEL_REG	0x600
/* Color bar enabling control */
#define S5K5CA_COLOR_BAR_ENABLE_REG		0x601
/* Time in milisecs for waiting for the sensor to reset*/
#define S5K5CA_RESET_DELAY_MSECS		66
/* I2C Address of the Sensor */
/*============================================================================
		DATA DECLARATIONS
============================================================================*/
#define S5K5CA_FULL_SIZE_DUMMY_PIXELS		0
#define S5K5CA_FULL_SIZE_DUMMY_LINES		0
#define S5K5CA_QTR_SIZE_DUMMY_PIXELS		0
#define S5K5CA_QTR_SIZE_DUMMY_LINES		0

#define S5K5CA_FULL_SIZE_WIDTH			2048//480//1024//320
#define S5K5CA_FULL_SIZE_HEIGHT			1536//320//768//240

#define S5K5CA_QTR_SIZE_WIDTH			640//480//1024//320
#define S5K5CA_QTR_SIZE_HEIGHT			480//320//768//240

#define S5K5CA_HRZ_FULL_BLK_PIXELS		0
#define S5K5CA_VER_FULL_BLK_LINES		0
#define S5K5CA_HRZ_QTR_BLK_PIXELS		0
#define S5K5CA_VER_QTR_BLK_LINES		0

#define S5K5CA_MSB_MASK			0xFF00
#define S5K5CA_LSB_MASK			0x00FF

struct s5k5ca_work_t {
	struct work_struct work;
};
static struct s5k5ca_work_t *s5k5ca_sensorw;
static struct i2c_client *s5k5ca_client;
struct s5k5ca_ctrl_t {
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
	enum s5k5ca_resolution_t prev_res;
	enum s5k5ca_resolution_t pict_res;
	enum s5k5ca_resolution_t curr_res;
	enum s5k5ca_test_mode_t  set_test;
	unsigned short imgaddr;
};
static struct s5k5ca_ctrl_t *s5k5ca_ctrl;
static int8_t config_not_set = 1;
static int8_t scene_mode = 0;
/*-- Petershih -fix ATS00152283 reset the white balance setting --*/
static int8_t wb_mode = 0;
/*-- Petershih -fix ATS00152283 reset the white balance setting --*/
static DECLARE_WAIT_QUEUE_HEAD(s5k5ca_wait_queue);
DEFINE_MUTEX(s5k5ca_mut);

/*=============================================================*/
static int s5k5ca_i2c_rxdata(unsigned short saddr,
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

	if (i2c_transfer(s5k5ca_client->adapter, msgs, 2) < 0) {
		CDBG("s5k5ca_i2c_rxdata failed!\n");
		return -EIO;
	}

	return 0;
}

static int32_t s5k5ca_i2c_txdata(unsigned short saddr,
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

	if (i2c_transfer(s5k5ca_client->adapter, msg, 1) < 0) {
		CDBG("s5k5ca_i2c_txdata faild 0x%x\n", s5k5ca_client->addr);
		return -EIO;
	}

	return 0;
}

static int32_t s5k5ca_i2c_read(unsigned short raddr,
				unsigned short *rdata, int rlen)
{
	int32_t rc = 0;
	unsigned char buf[2];

	if (!rdata)
		return -EIO;

	buf[0] = (raddr & S5K5CA_MSB_MASK) >> 8;
	buf[1] = (raddr & S5K5CA_LSB_MASK);

	rc = s5k5ca_i2c_rxdata(s5k5ca_client->addr, buf, rlen);

	if (rc < 0) {
		CDBG("s5k5ca_i2c_read 0x%x failed!\n", raddr);
		return rc;
	}

	*rdata = (rlen == 2 ? buf[0] << 8 | buf[1] : buf[0]);
	return rc;
}

static int32_t s5k5ca_i2c_write_b(unsigned short saddr,
	unsigned short waddr, uint16_t bdata)
{
	int32_t rc = -EFAULT;
	unsigned char buf[4];

			buf[0] = (waddr & 0xFF00)>>8;
			buf[1] = (waddr & 0x00FF);
			buf[2] = (bdata & 0xFF00)>>8;
			buf[3] = (bdata & 0x00FF);

	CDBG("i2c_write_b addr = 0x%x, val = 0x%xd\n", waddr, bdata);
	rc = s5k5ca_i2c_txdata(saddr, buf, 4);

	if (rc < 0) {
		CDBG("i2c_write_b failed, addr = 0x%x, val = 0x%x!\n",
			 waddr, bdata);
	}

	return rc;
}
#if 0
static void s5k5ca_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
	uint32_t divider;	/*Q10 */
	uint32_t d1;
	uint32_t d2;
	uint16_t snapshot_height, preview_height, preview_width, snapshot_width;
pr_emerg("Peter-s5k5ca_get_pict_fps() prev_res:%d pict_res:%d",s5k5ca_ctrl->prev_res,s5k5ca_ctrl->pict_res);
	if (s5k5ca_ctrl->prev_res == QTR_SIZE) {
		preview_width = S5K5CA_QTR_SIZE_WIDTH +
			S5K5CA_HRZ_QTR_BLK_PIXELS ;
		preview_height = S5K5CA_QTR_SIZE_HEIGHT +
			S5K5CA_VER_QTR_BLK_LINES ;
	} else {
		/* full size resolution used for preview. */
		preview_width = S5K5CA_FULL_SIZE_WIDTH +
			S5K5CA_HRZ_FULL_BLK_PIXELS ;
		preview_height = S5K5CA_FULL_SIZE_HEIGHT +
			S5K5CA_VER_FULL_BLK_LINES ;
	}
	if (s5k5ca_ctrl->pict_res == QTR_SIZE) {
		snapshot_width  = S5K5CA_QTR_SIZE_WIDTH +
			S5K5CA_HRZ_QTR_BLK_PIXELS ;
		snapshot_height = S5K5CA_QTR_SIZE_HEIGHT +
			S5K5CA_VER_QTR_BLK_LINES ;
	} else {
		snapshot_width  = S5K5CA_FULL_SIZE_WIDTH +
			S5K5CA_HRZ_FULL_BLK_PIXELS;
		snapshot_height = S5K5CA_FULL_SIZE_HEIGHT +
			S5K5CA_VER_FULL_BLK_LINES;
	}

	d1 = (uint32_t)(((uint32_t)preview_height <<
		S5K5CA_Q10Shift) /
		snapshot_height);

	d2 = (uint32_t)(((uint32_t)preview_width <<
		S5K5CA_Q10Shift) /
		 snapshot_width);

	divider = (uint32_t) (d1 * d2) >> S5K5CA_Q10Shift;
	*pfps = (uint16_t)((uint32_t)(fps * divider) >> S5K5CA_Q10Shift);
pr_emerg("Peter-s5k5ca_get_pict_fps() *pfps:%d",*pfps);
}
static uint16_t s5k5ca_get_prev_lines_pf(void)
{
pr_emerg("Peter-s5k5ca_get_prev_lines_pf() prev_res:%d",s5k5ca_ctrl->prev_res);
	if (s5k5ca_ctrl->prev_res == QTR_SIZE)
		return s5k5ca_QTR_SIZE_HEIGHT + S5K5CA_VER_QTR_BLK_LINES;
	else
		return S5K5CA_FULL_SIZE_HEIGHT + S5K5CA_VER_FULL_BLK_LINES;
}

static uint16_t s5k5ca_get_prev_pixels_pl(void)
{
pr_emerg("Peter-s5k5ca_get_prev_pixels_pl() prev_res:%d",s5k5ca_ctrl->prev_res);
	if (s5k5ca_ctrl->prev_res == QTR_SIZE)
		return S5K5CA_QTR_SIZE_WIDTH + S5K5CA_HRZ_QTR_BLK_PIXELS;
	else
		return S5K5CA_FULL_SIZE_WIDTH + S5K5CA_HRZ_FULL_BLK_PIXELS;
}

static uint16_t s5k5ca_get_pict_lines_pf(void)
{
pr_emerg("Peter-s5k5ca_get_pict_lines_pf() pict_res:%d",s5k5ca_ctrl->pict_res);
	if (s5k5ca_ctrl->pict_res == QTR_SIZE)
		return S5K5CA_QTR_SIZE_HEIGHT + S5K5CA_VER_QTR_BLK_LINES;
	else
		return S5K5CA_FULL_SIZE_HEIGHT + S5K5CA_VER_FULL_BLK_LINES;
}

static uint16_t s5k5ca_get_pict_pixels_pl(void)
{
pr_emerg("Peter-s5k5ca_get_pict_pixels_pl() pict_res:%d",s5k5ca_ctrl->pict_res);
	if (s5k5ca_ctrl->pict_res == QTR_SIZE)
		return S5K5CA_QTR_SIZE_WIDTH + S5K5CA_HRZ_QTR_BLK_PIXELS;
	else
		return S5K5CA_FULL_SIZE_WIDTH + S5K5CA_HRZ_FULL_BLK_PIXELS;
}

static uint32_t s5k5ca_get_pict_max_exp_lc(void)
{
pr_emerg("Peter-s5k5ca_get_pict_max_exp_lc() pict_res:%d",s5k5ca_ctrl->pict_res);
	if (s5k5ca_ctrl->pict_res == QTR_SIZE)
		return (S5K5CA_QTR_SIZE_HEIGHT + S5K5CA_VER_QTR_BLK_LINES)*24;
	else
		return (S5K5CA_FULL_SIZE_HEIGHT + S5K5CA_VER_FULL_BLK_LINES)*24;
}

static int32_t s5k5ca_set_fps(struct fps_cfg	*fps)
{
	int32_t rc = 0;
pr_emerg("Peter-s5k5ca_set_fps() fps_div:%d f_mult:%d",fps->fps_div,fps->f_mult);
	CDBG("%s: fps->fps_div = %d\n", __func__, fps->fps_div);
	/* TODO: Passing of fps_divider from user space has issues. */
	/* s5k5ca_ctrl->fps_divider = fps->fps_div; */
	s5k5ca_ctrl->fps_divider = 1 * 0x400;
	CDBG("%s: s5k5ca_ctrl->fps_divider = %d\n", __func__,
		s5k5ca_ctrl->fps_divider);
	s5k5ca_ctrl->pict_fps_divider = fps->pict_fps_div;
	s5k5ca_ctrl->fps = fps->f_mult;
	return rc;
}

static int32_t s5k5ca_write_exp_gain(uint16_t gain, uint32_t line)
{
	static uint16_t max_legal_gain = 0x00FF;
	uint8_t gain_msb, gain_lsb;
	uint8_t intg_time_msb, intg_time_lsb;
	uint8_t s5k5ca_offset = 6;
	uint8_t line_length_pck_msb, line_length_pck_lsb;
	uint16_t line_length_pck, frame_length_lines;
	uint32_t line_length_ratio = 1 << S5K5CA_Q8Shift;
	int32_t rc = -1;
pr_emerg("Peter-s5k5ca_write_exp_gain() sensormode:%d",s5k5ca_ctrl->sensormode);
	CDBG("%s: gain = %d	line = %d", __func__, gain, line);

	if (s5k5ca_ctrl->sensormode != SENSOR_SNAPSHOT_MODE) {
		if (s5k5ca_ctrl->curr_res == QTR_SIZE) {
			frame_length_lines = S5K5CA_QTR_SIZE_HEIGHT +
			 S5K5CA_VER_QTR_BLK_LINES;
			line_length_pck = S5K5CA_QTR_SIZE_WIDTH	+
			 S5K5CA_HRZ_QTR_BLK_PIXELS;
		} else {
			frame_length_lines = S5K5CA_FULL_SIZE_HEIGHT +
				S5K5CA_VER_FULL_BLK_LINES;
			line_length_pck = S5K5CA_FULL_SIZE_WIDTH +
				S5K5CA_HRZ_FULL_BLK_PIXELS;
		}
		if (line > (frame_length_lines - s5k5ca_offset))
			s5k5ca_ctrl->fps = (uint16_t) (((uint32_t)30 <<
				S5K5CA_Q8Shift) *
				(frame_length_lines - s5k5ca_offset) / line);
		else
			s5k5ca_ctrl->fps = (uint16_t) ((uint32_t)30 <<
				S5K5CA_Q8Shift);
	} else {
		frame_length_lines = S5K5CA_FULL_SIZE_HEIGHT +
			S5K5CA_VER_FULL_BLK_LINES;
		line_length_pck = S5K5CA_FULL_SIZE_WIDTH +
			S5K5CA_HRZ_FULL_BLK_PIXELS;
	}

	if (s5k5ca_ctrl->sensormode != SENSOR_SNAPSHOT_MODE) {
		line = (uint32_t) (line * s5k5ca_ctrl->fps_divider) >>
			S5K5CA_Q10Shift;
	} else {
		line = (uint32_t) (line * s5k5ca_ctrl->pict_fps_divider) >>
			S5K5CA_Q10Shift;
	}

	/* calculate line_length_ratio */
	if (line > (frame_length_lines - s5k5ca_offset)) {
		line_length_ratio = (line << s5k5ca_Q8Shift) /
			(frame_length_lines - s5k5ca_offset);
		line = frame_length_lines - s5k5ca_offset;
	} else
		line_length_ratio = (uint32_t)1 << S5K5CA_Q8Shift;

	if (gain > max_legal_gain) {
		/* range:	0	to 224 */
		gain = max_legal_gain;
	}
	/* update	gain registers */
	gain_msb = (uint8_t) ((gain & 0xFF00) >> 8);
	gain_lsb = (uint8_t) (gain & 0x00FF);
	/* linear	AFR	horizontal stretch */
	line_length_pck = (uint16_t) ((line_length_pck *
		line_length_ratio) >> S5K5CA_Q8Shift);
	line_length_pck_msb = (uint8_t) ((line_length_pck & 0xFF00) >> 8);
	line_length_pck_lsb = (uint8_t) (line_length_pck & 0x00FF);
	/* update	line count registers */
	intg_time_msb = (uint8_t) ((line & 0xFF00) >> 8);
	intg_time_lsb = (uint8_t) (line	& 0x00FF);
#if 0
	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x104, 0x1);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x204, gain_msb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x205, gain_lsb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x342,
		line_length_pck_msb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x343,
		line_length_pck_lsb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x0202, intg_time_msb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x0203, intg_time_lsb);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x104, 0x0);
	if (rc < 0)
		return rc;
#endif
	return rc;
}

static int32_t s5k5ca_set_pict_exp_gain(uint16_t gain, uint32_t line)
{
	int32_t rc = 0;
	rc = s5k5ca_write_exp_gain(gain, line);
pr_emerg("Peter-s5k5ca_set_pict_exp_gain() gain:%d line:%d rc:%d",gain,line,rc);
	return rc;
}
#endif

static int32_t s5k5ca_set_wb(struct wb_info_cfg	*wb)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_wb()blue:%d green:%d red:%d",wb->blue_gain,wb->green_gain,wb->red_gain);
	pr_emerg("Peter-s5k5ca_set_wb() addr:%x",s5k5ca_client->addr);
#endif
	wb_mode = j = (wb->red_gain-1)%S5K5CA_WB_MAX;
	if(s5k5ca_WB[j]!=NULL)
	{
		while(s5k5ca_WB[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_WB[j][i].reg_addr,s5k5ca_WB[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_WB[j][i].timer!=0)
				msleep(s5k5ca_WB[j][i].timer);
			i++;
		}
	}
	return rc;
}
static int32_t s5k5ca_set_scene(struct wb_info_cfg	*wb)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_scene()blue:%d green:%d red:%d",wb->blue_gain,wb->green_gain,wb->red_gain);
	pr_emerg("Peter-s5k5ca_set_scene() addr:%x",s5k5ca_client->addr);
#endif
	j = (wb->red_gain<S5K5CA_SCENE_MAX)?wb->red_gain:0;
	scene_mode = j;
	if(s5k5ca_scene[j]!=NULL)
	{
		while(s5k5ca_scene[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_scene[j][i].reg_addr,s5k5ca_scene[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_scene[j][i].timer!=0)
				msleep(s5k5ca_scene[j][i].timer);
			i++;
		}
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_scene():mode=%d,paramter number=%d, rc:%d",j,i,rc);
#endif
	}
	/*++ Petershih -fix ATS00152283 reset the white balance setting ++*/
	if(scene_mode <= 1)
	{
		i = 0;
		if(s5k5ca_WB[wb_mode]!=NULL)
		{
			while(s5k5ca_WB[wb_mode][i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_WB[wb_mode][i].reg_addr,s5k5ca_WB[wb_mode][i].reg_val);
				if( rc != 0 )
					break;
				if(s5k5ca_WB[wb_mode][i].timer!=0)
					msleep(s5k5ca_WB[wb_mode][i].timer);
				i++;
			}
		}
	}
	/*-- Petershih -fix ATS00152283 reset the white balance setting --*/
	return rc;
}
static int32_t s5k5ca_set_exposure_mode(struct exp_gain_cfg	*exposure)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_exposure_mode()gain:%d ",exposure->gain);
#endif
#if 1
	j = (exposure->gain)%S5K5CA_EXPOSURE_MAX;
	if(s5k5ca_exposure[j]!=NULL)
	{
		while(s5k5ca_exposure[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_exposure[j][i].reg_addr,s5k5ca_exposure[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_exposure[j][i].timer!=0)
				msleep(s5k5ca_exposure[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}

static int32_t s5k5ca_set_brightness(struct exp_gain_cfg	*bright)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_brightness()gain:%d ",bright->gain);
#endif
#if 1
	j = (bright->gain)%S5K5CA_BRIGHTNESS_MAX;
	if(s5k5ca_brightness[j]!=NULL)
	{
		while(s5k5ca_brightness[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_brightness[j][i].reg_addr,s5k5ca_brightness[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_brightness[j][i].timer!=0)
				msleep(s5k5ca_brightness[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}
static int32_t s5k5ca_set_iso(int8_t iso)
{
	int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_iso()iso:%d ",iso);
#endif
#if 1
	j = (iso)%S5K5CA_ISO_MAX;
	if(s5k5ca_iso[j]!=NULL)
	{
		while(s5k5ca_iso[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_iso[j][i].reg_addr,s5k5ca_iso[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_iso[j][i].timer!=0)
				msleep(s5k5ca_iso[j][i].timer);
			i++;
		}
	}
#endif
	return rc;
}
static int32_t s5k5ca_set_fps(struct fps_cfg	*fps)
{
       int32_t rc = 0;
	int8_t i=0,j=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_fps() fps_div:%d f_mult:%d pict_fps_div:%d fps_type:%d",fps->fps_div,fps->f_mult,fps->pict_fps_div,fps->fps_type);
#endif
#if 1
       if((fps->fps_type)>=16)
        j = 1;
	else 
	 j=0;	
	if(s5k5ca_fps[j]!=NULL)
	{
		while(s5k5ca_fps[j][i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_fps[j][i].reg_addr,s5k5ca_fps[j][i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_fps[j][i].timer!=0)
				msleep(s5k5ca_fps[j][i].timer);
			i++;
		}
	}
#endif
	return rc;

}
static int32_t s5k5ca_set_effect(int8_t  effect)
{
	int32_t rc = 0;
	int8_t i=0;
	 
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_effect()effect:%d ",effect);
#endif

	switch(effect)
	{
		case CAMERA_EFFECT_OFF:
			while(S5K5CA_effect_NONE[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_NONE[i].reg_addr,S5K5CA_effect_NONE[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_NONE[i].timer!=0)
					msleep(S5K5CA_effect_NONE[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_MONO:
			while(S5K5CA_effect_MONO[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_MONO[i].reg_addr,S5K5CA_effect_MONO[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_MONO[i].timer!=0)
					msleep(S5K5CA_effect_MONO[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_NEGATIVE:
			while(S5K5CA_effect_NEGATIVE[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_NEGATIVE[i].reg_addr,S5K5CA_effect_NEGATIVE[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_NEGATIVE[i].timer!=0)
					msleep(S5K5CA_effect_NEGATIVE[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_AQUA:
			while(S5K5CA_effect_AQUA[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_AQUA[i].reg_addr,S5K5CA_effect_AQUA[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_AQUA[i].timer!=0)
					msleep(S5K5CA_effect_AQUA[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_SEPIA:
			while(S5K5CA_effect_SEPIA[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_SEPIA[i].reg_addr,S5K5CA_effect_SEPIA[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_SEPIA[i].timer!=0)
					msleep(S5K5CA_effect_SEPIA[i].timer);
				i++;
			}
			break;
		case CAMERA_EFFECT_POSTERIZE:
			while(S5K5CA_effect_SKETCH[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_SKETCH[i].reg_addr,S5K5CA_effect_SKETCH[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_SKETCH[i].timer!=0)
					msleep(S5K5CA_effect_SKETCH[i].timer);
				i++;
			}
			break;

		default:
			while(S5K5CA_effect_NONE[i].reg_addr!=0)
			{
				rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, S5K5CA_effect_NONE[i].reg_addr,S5K5CA_effect_NONE[i].reg_val);
				if( rc != 0 )
					break;
				if(S5K5CA_effect_NONE[i].timer!=0)
					msleep(S5K5CA_effect_NONE[i].timer);
				i++;
			}
			break;

	}	
	return rc;
}
static int32_t initialize_s5k5ca_registers(void)
{
	int32_t i;
	int32_t rc = 0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-initialize_s5k5ca_registers()");
#endif
	s5k5ca_ctrl->sensormode = SENSOR_PREVIEW_MODE ;
	/* Configure sensor for Preview mode and Snapshot mode */
	CDBG("Initialize_s5k5ca_registers\n");
	while(s5k5ca_init_settings_array[i].reg_addr!=0)
	{
		rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_init_settings_array[i].reg_addr,s5k5ca_init_settings_array[i].reg_val);
		if( rc != 0 )
			break;
		if(s5k5ca_init_settings_array[i].timer!=0)
			msleep(s5k5ca_init_settings_array[i].timer);
		i++;
	}
#if 0	
	for (i = 0; i < s5k5ca_array_length; i++) {
		rc = s5k5ca_i2c_write_b(s5k5ca_client->addr,
			s5k5ca_init_settings_array[i].reg_addr,
			s5k5ca_init_settings_array[i].reg_val);
	if (rc < 0)
		return rc;
	if(s5k5ca_init_settings_array[i].timer != 0)
		msleep(s5k5ca_init_settings_array[i].timer);
	}
#endif
//	msleep(10);
#ifdef CAMERA_DBG
	pr_emerg("Peter-initialize_s5k5ca_registers() rc:%d",rc);
#endif
	return rc;
}

static int32_t s5k5ca_video_config(int mode)
{
	int32_t rc = 0;
	int32_t i=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_video_config() mode:%d config_not_set:%d",mode,config_not_set);
#endif
	s5k5ca_ctrl->sensormode = mode;

	if (config_not_set) {
		struct msm_camera_csi_params s5k5ca_csi_params;

		/* sensor in standby */
//		s5k5ca_i2c_write_b(s5k5ca_client->addr, 0x100, 0);
//		msleep(5);
		/* Initialize Sensor registers */
		msm_camio_vfe_clk_rate_set(192000000);
		s5k5ca_csi_params.data_format = CSI_8BIT;
		s5k5ca_csi_params.lane_cnt = 1;
		s5k5ca_csi_params.lane_assign = 0xe4;
		s5k5ca_csi_params.dpcm_scheme = 0;
		s5k5ca_csi_params.settle_cnt = 24;

		rc = msm_camio_csi_config(&s5k5ca_csi_params);
#ifdef CAMERA_DBG
		pr_emerg("Peter-s5k5ca_video_config() rc:%d ",rc);
#endif
		rc = initialize_s5k5ca_registers();
		config_not_set = 0;
	}
	else
	{
		while(s5k5ca_preview[i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_preview[i].reg_addr,s5k5ca_preview[i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_preview[i].timer!=0)
				msleep(s5k5ca_preview[i].timer);
			i++;
		}
	}
	return rc;
}

static int32_t s5k5ca_snapshot_config(int mode)
{
	int32_t rc = 0;
	int32_t i=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_snapshot_config() mode:%d",mode);
#endif
	s5k5ca_ctrl->sensormode = mode;
	if(scene_mode != 6)
	{
		while(s5k5ca_capture[i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_capture[i].reg_addr,s5k5ca_capture[i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_capture[i].timer!=0)
				msleep(s5k5ca_capture[i].timer);
			i++;
		}
	}
#if 1
	else
	{
		while(s5k5ca_capture_Night_Mode[i].reg_addr!=0)
		{
			rc=s5k5ca_i2c_write_b(s5k5ca_client->addr, s5k5ca_capture_Night_Mode[i].reg_addr,s5k5ca_capture_Night_Mode[i].reg_val);
			if( rc != 0 )
				break;
			if(s5k5ca_capture_Night_Mode[i].timer!=0)
				msleep(s5k5ca_capture_Night_Mode[i].timer);
			i++;
		}
	}
#endif		
	return rc;
}

static int32_t s5k5ca_raw_snapshot_config(int mode)
{
	int32_t rc = 0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_raw_snapshot_config() mode:%d",mode);
#endif		
	s5k5ca_ctrl->sensormode = mode;
	return rc;
}

static int32_t s5k5ca_set_sensor_mode(int  mode,
			int  res)
{
	int32_t rc = 0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_sensor_mode() mode:%d res:%d",mode,res);
#endif		
	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		rc = s5k5ca_video_config(mode);
		break;
	case SENSOR_SNAPSHOT_MODE:
		rc = s5k5ca_snapshot_config(mode);
		break;
	case SENSOR_RAW_SNAPSHOT_MODE:
		rc = s5k5ca_raw_snapshot_config(mode);
		break;
	default:
		rc = -EINVAL;
		break;
	}
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_set_sensor_mode() rc:%d",rc);
#endif		
	return rc;
}

static int s5k5ca_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
	int32_t rc = 0;
	uint16_t  chipidh=0;
//		int value;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_probe_init_sensor() RST:%d PWD:%d",data->sensor_reset,data->vcm_pwd);
#endif		

	/* set PWDN pin to high*/
	gpio_set_value(27, 1);
	msleep(10);
	/* set Reset pin to high*/
	gpio_set_value(26, 1);
	msleep(10);


	/* 3. Read sensor Model ID: */
	rc=s5k5ca_i2c_write_b(s5k5ca_client->addr,0xFCFC,0xD000);
        if(rc<0) goto init_probe_fail;
	rc=s5k5ca_i2c_write_b(s5k5ca_client->addr,0x002C,0x0000);
        if(rc<0) goto init_probe_fail;
        rc=s5k5ca_i2c_write_b(s5k5ca_client->addr,0x002E,0x0040);
        if(rc<0) goto init_probe_fail;
	rc=s5k5ca_i2c_read(0x0F12, 	&chipidh, 2);
	if (rc < 0)
		goto init_probe_fail;
	pr_emerg("Peter-s5k5ca_probe_init_sensor() chipidh:%x ",chipidh);
	CDBG("ks5k5ca model_id = 0x%x \n", chipidh);
	/* 4. Compare sensor ID to S5K5CA ID: */
	if (chipidh != 0x05ca) {
		pr_emerg("Peter-s5k5ca_probe_init_sensor() ENODEV:%x ",ENODEV);
		rc = -ENODEV;
		printk(KERN_INFO "Probeinit fail\n");
		goto init_probe_fail;
	}
	pr_emerg("Peter-s5k5ca_probe_init_sensor() chipidh == S5K5CA_PID ");
	CDBG("chipidh == S5K5CA_PID\n");
//	msleep(S5K5CA_RESET_DELAY_MSECS);
	CDBG("after delay\n");
	goto init_probe_done;

init_probe_fail:
	if (data->sensor_reset_enable) {
		gpio_direction_output(data->sensor_reset, 0);
		gpio_free(data->sensor_reset);
	}
init_probe_done:
	pr_emerg("Peter-s5k5ca_probe_init_sensor() rc:%x ",rc);
	printk(KERN_INFO " s5k5ca_probe_init_sensor finishes\n");
	return rc;
}

int s5k5ca_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t  rc=0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_sensor_open_init()");
#endif
	CDBG("Calling s5k5ca_sensor_open_init\n");
	s5k5ca_ctrl = kzalloc(sizeof(struct s5k5ca_ctrl_t), GFP_KERNEL);
	if (!s5k5ca_ctrl) {
		CDBG("s5k5ca_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}
	s5k5ca_ctrl->curr_lens_pos = -1;
	s5k5ca_ctrl->fps_divider = 1 << S5K5CA_Q10Shift;
	s5k5ca_ctrl->pict_fps_divider = 1 << S5K5CA_Q10Shift;
	s5k5ca_ctrl->set_test = TEST_OFF;
	s5k5ca_ctrl->prev_res = QTR_SIZE;//FULL_SIZE;
	s5k5ca_ctrl->pict_res = FULL_SIZE;
	s5k5ca_ctrl->curr_res = INVALID_SIZE;
	config_not_set = 1;
	scene_mode=0;
	if (data)
		s5k5ca_ctrl->sensordata = data;
	else
		goto init_fail;
	/* enable mclk first */
	msm_camio_clk_rate_set(S5K5CA_DEFAULT_CLOCK_RATE);
	msleep(10);
	rc = s5k5ca_probe_init_sensor(data);
	if (rc < 0)
		goto init_fail;

	s5k5ca_ctrl->fps = (uint16_t)(30 << S5K5CA_Q8Shift);
	/* generate test pattern */
	if (rc < 0)
		goto init_fail;
	else
		goto init_done;
	/* reset the driver state */
init_fail:
	CDBG(" init_fail\n");
	kfree(s5k5ca_ctrl);
init_done:
	CDBG("init_done\n");
	return rc;
}

static int s5k5ca_init_client(struct i2c_client *client)
{
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_init_client()");
#endif
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&s5k5ca_wait_queue);
	return 0;
}

static const struct i2c_device_id s5k5ca_i2c_id[] = {
	{ "s5k5ca", 0},
	{ }
};

static int s5k5ca_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_i2c_probe()");
#endif
	CDBG("s5k5ca_probe called!\n");
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		CDBG("i2c_check_functionality failed\n");
		goto probe_failure;
	}
	s5k5ca_sensorw = kzalloc(sizeof(struct s5k5ca_work_t), GFP_KERNEL);
	if (!s5k5ca_sensorw) {
		CDBG("kzalloc failed.\n");
		rc = -ENOMEM;
		goto probe_failure;
	}
	i2c_set_clientdata(client, s5k5ca_sensorw);
	s5k5ca_init_client(client);
	s5k5ca_client = client;
//	msleep(10);
	CDBG("s5k5ca_probe successed! rc = %d\n", rc);
	return 0;
probe_failure:
	CDBG("s5k5ca_probe failed! rc = %d\n", rc);
	return rc;
}

static int __exit s5k5ca_remove(struct i2c_client *client)
{
	struct s5k5ca_work_t_t *sensorw = i2c_get_clientdata(client);
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_remove()");
#endif
	free_irq(client->irq, sensorw);
	s5k5ca_client = NULL;
	kfree(sensorw);
	return 0;
}

static struct i2c_driver s5k5ca_i2c_driver = {
	.id_table = s5k5ca_i2c_id,
	.probe	= s5k5ca_i2c_probe,
	.remove = __exit_p(s5k5ca_i2c_remove),
	.driver = {
		.name = "s5k5ca",
	},
};

int s5k5ca_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cdata;
	int   rc = 0;

	if (copy_from_user(&cdata,
				(void *)argp,
				sizeof(struct sensor_cfg_data)))
		return -EFAULT;
	mutex_lock(&s5k5ca_mut);
	CDBG("s5k5ca_sensor_config: cfgtype = %d\n",
		cdata.cfgtype);
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_sensor_config() cfgtype:%d",cdata.cfgtype);
#endif
	switch (cdata.cfgtype) {
	case CFG_GET_PICT_FPS:
#if 0
		s5k5ca_get_pict_fps(cdata.cfg.gfps.prevfps,
				&(cdata.cfg.gfps.pictfps));
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
			break;
	case CFG_GET_PREV_L_PF:
#if 0
		cdata.cfg.prevl_pf = s5k5ca_get_prev_lines_pf();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PREV_P_PL:
#if 0
		cdata.cfg.prevp_pl = s5k5ca_get_prev_pixels_pl();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_L_PF:
#if 0
		cdata.cfg.pictl_pf = s5k5ca_get_pict_lines_pf();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_P_PL:
#if 0
		cdata.cfg.pictp_pl =
				s5k5ca_get_pict_pixels_pl();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_GET_PICT_MAX_EXP_LC:
#if 0
		cdata.cfg.pict_max_exp_lc = s5k5ca_get_pict_max_exp_lc();
		if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
			rc = -EFAULT;
#endif
		break;
	case CFG_SET_FPS:
		rc = s5k5ca_set_fps(&(cdata.cfg.fps));//Flea++
		break;
	case CFG_SET_PICT_FPS:
#if 0
		rc = s5k5ca_set_fps(&(cdata.cfg.fps));
#endif
		break;
	case CFG_SET_EXP_GAIN:
#if 0
		rc = s5k5ca_write_exp_gain(
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
#endif
		break;
	case CFG_SET_PICT_EXP_GAIN:
#if 0
		rc = s5k5ca_set_pict_exp_gain(
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
#endif
		break;
	case CFG_SET_MODE:
		rc = s5k5ca_set_sensor_mode(cdata.mode,
						cdata.rs);
		break;
		case CFG_SET_EFFECT:
		rc = s5k5ca_set_effect(cdata.cfg.effect);
		break;
	case CFG_SET_WB:
		rc = s5k5ca_set_wb(&(cdata.cfg.wb_info));
		break;
	case CFG_SET_EXPOSURE_MODE:
		rc = s5k5ca_set_exposure_mode(&(cdata.cfg.exp_gain));
		break;
	case CFG_SET_BRIGHTNESS:
		rc = s5k5ca_set_brightness(&(cdata.cfg.exp_gain));
		break;
	case CFG_SET_SCENE:
		rc = s5k5ca_set_scene(&(cdata.cfg.wb_info));
		break;
	case CFG_PWR_DOWN:
	case CFG_MOVE_FOCUS:
	case CFG_SET_DEFAULT_FOCUS:
		rc = 0;
		break;
	case CFG_SET_ISO:
		rc = s5k5ca_set_iso(cdata.cfg.iso);
		break;
	default:
		rc = -EFAULT;
		break;
	}
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_sensor_config() rc:%d",rc);
#endif
	mutex_unlock(&s5k5ca_mut);
	return rc;
}

static int s5k5ca_probe_init_done(const struct msm_camera_sensor_info *data)
{
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_probe_init_done()");
#endif
	if (data->sensor_reset_enable) {
		gpio_direction_output(data->sensor_reset, 0);
		gpio_free(data->sensor_reset);
	}
	return 0;
}

static int s5k5ca_sensor_release(void)
{
	int rc = -EBADF;
#ifdef CAMERA_DBG
	pr_emerg("Peter-s5k5ca_sensor_release()");
#endif
	mutex_lock(&s5k5ca_mut);

	/* set PWDN pin to low*/
	gpio_set_value(26, 0);
	msleep(10);
	/* set PWDN pin to low*/
	gpio_set_value(27, 0);
	msleep(10);
	
	kfree(s5k5ca_ctrl);
	s5k5ca_ctrl = NULL;
	CDBG("s5k5ca_release completed\n");
	mutex_unlock(&s5k5ca_mut);
	return rc;
}

static int s5k5ca_sensor_probe(const struct msm_camera_sensor_info *info,
		struct msm_sensor_ctrl *s)
{
	int rc = 0;
	int camera_id=0;

	pr_emerg("Peter-s5k5ca_sensor_probe()");

	rc = i2c_add_driver(&s5k5ca_i2c_driver);
	if (rc < 0 || s5k5ca_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_fail;
	}
	msm_camio_clk_rate_set(24000000);
	msleep(10);
	rc = s5k5ca_probe_init_sensor(info);
	if (rc < 0)
		goto probe_fail;

	//++ PeterShih 20120827 check the camera id and assign the camera initial setting 
	camera_id = gpio_get_value(13);
	pr_emerg("Peter-s5k5ca_sensor_probe() camera_id:%d",camera_id);
	s5k5ca_init_settings_array = (camera_id) ? s5k5ca_mcnex_init_array : s5k5ca_truly_init_array;
	//-- PeterShih 20120827 check the camera id and assign the camera initial setting 
	
	s->s_init = s5k5ca_sensor_open_init;
	s->s_release = s5k5ca_sensor_release;
	s->s_config  = s5k5ca_sensor_config;
//	s->s_camera_type = BACK_CAMERA_2D;
	s->s_mount_angle = info->sensor_platform_info->mount_angle;
/*++ PeterShih - 20120417 for camera HW version ++*/
	s->hw_version = 10 | camera_id;
/*-- PeterShih - 20120417 for camera HW version --*/
	s5k5ca_probe_init_done(info);

	return rc;

probe_fail:
	CDBG("SENSOR PROBE FAILS!\n");
	return rc;
}

static int __s5k5ca_probe(struct platform_device *pdev)
{
	pr_emerg("Peter-__s5k5ca_probe()");
	return msm_camera_drv_start(pdev, s5k5ca_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = __s5k5ca_probe,
	.driver = {
		.name = "msm_camera_s5k5ca",
		.owner = THIS_MODULE,
	},
};

static int __init s5k5ca_init(void)
{
	pr_emerg("Peter-s5k5ca_init()");
	/* set PWDN pin to low*/
	gpio_set_value(27, 0);
	/* set Reset pin to low*/
	gpio_set_value(26, 0);
	return platform_driver_register(&msm_camera_driver);
}

module_init(s5k5ca_init);
void s5k5ca_exit(void)
{
	pr_emerg("Peter-s5k5ca_exit()");
	i2c_del_driver(&s5k5ca_i2c_driver);
}

MODULE_DESCRIPTION("OMNI VGA Bayer sensor driver");
MODULE_LICENSE("GPL v2");

