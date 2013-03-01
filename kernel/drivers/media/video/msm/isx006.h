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

#ifndef ISX006_H
#define ISX006_H
#include <linux/types.h>
#include <mach/board.h>
#include "fih_cam_api.h"

/* FIH-SW3-MM-UW-flash tuning-04+*/
#define offset_size    1002
extern struct isx006_reg isx006_regs;
extern int16_t x_8[offset_size];
/* FIH-SW3-MM-UW-flash tuning-04-*/

enum isx006_device_status {
	STS_POWER_DOWN = 0,
	STS_PRE_SLEEP  = 1,
	STS_SLEEP      = 2,
	STS_ACTIVE     = 3,
       STS_UNKNOWN    = 4
};

enum isx006_mode {
	MONITOR_MODE      = 0,
	HALF_RELEASE_MODE = 1,
	CAPTURE_MODE      = 2,
	MOVIE_MODE        = 3,
       UNKNOWN_MODE      = 4
};

/* FIH-SW3-MM-UW-write OTP setting-00+*/
enum isx006_SHD {
	SHD_MIN = 1,
	SHD_TYP = 2,
	SHD_MAX = 3,
};
/* FIH-SW3-MM-UW-write OTP setting-00-*/

//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
enum isx006_moni_af_mode {
	MONI_AF_SAF      = 0,
	MONI_AF_CAF      = 1,
	MONI_AF_MF       = 2,
	MONI_AF_OFF      = 3,
    MONI_AF_UNKNOWN  = 4
};

/* FIH-SW3-MM-UW-cancel AF-00+*/
//Need sync enum isp3a_af_mode_t in camera.h
enum isx006_af_mode{
  AF_MODE_UNCHANGED = -1,
  AF_MODE_NORMAL    =  0,//Normal (scan from near to infinity)
  AF_MODE_MACRO,         //Macro (scan from close to near)
  AF_MODE_AUTO,          //Full (scan from close to infinity
  AF_MODE_CAF,           //Full (scan from close to infinity
  AF_MODE_INFINITY,      //Infinity (scan from far to infinity)
  AF_MODE_OFF,           //Fixed infinity (the focus is set to infinity and no scan)
  AF_MODE_POLLING, 
  AF_MODE_GET_STATE, 
  AF_MODE_MAX
};
/* FIH-SW3-MM-UW-cancel AF-00-*/
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}

/*MM-UW-support AF+++*/
enum isx006_AF_result {
	AF_NG      = 0,
	AF_OK = 1,
	AF_During      = 2,
	AF_UNKNOWN      = 3
};
/*MM-UW-support AF---*/

/* FIH-SW3-MM-UW-fix capture fail-00+*/
enum isx006_AF_state {
	AF_Load = 0,
	AF_Init = 1,
	AF_Init_HpMv = 2,
	AF_Idle = 3,
       AF_SAF_MvHome = 4,
	AF_SAF_Idle = 5,
	AF_SAF_MvNext = 6,
	AF_SAF_Lock = 7,
};
/* FIH-SW3-MM-UW-fix capture fail-00-*/

/* FIH-SW3-MM-UW-add reduce_red_eye-00+*/
enum led_mode {
	LED_MODE_OFF = 0,
	LED_MODE_AUTO = 1,
	LED_MODE_ON = 2,
	LED_MODE_TORCH = 3,
	LED_MODE_RED_EYE = 4
};
/* FIH-SW3-MM-UW-add reduce_red_eye-00-*/

struct isx006_i2c_reg_conf {
	unsigned short waddr;
	unsigned short wdata;
	enum fih_i2c_width width;
	unsigned short mdelay_time;
};

enum isx006_test_mode_t {
	TEST_OFF,
	TEST_1,
	TEST_2,
	TEST_3
};

enum isx006_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};
enum isx006_setting {
	RES_PREVIEW,
	RES_CAPTURE
};
enum isx006_reg_update {
	/* Sensor egisters that need to be updated during initialization */
	REG_INIT,
	/* Sensor egisters that needs periodic I2C writes */
	UPDATE_PERIODIC,
	/* All the sensor Registers will be updated */
	UPDATE_ALL,
	/* Not valid update */
	UPDATE_INVALID
};

enum isx006_reg_pll {
	E013_VT_PIX_CLK_DIV,
	E013_VT_SYS_CLK_DIV,
	E013_PRE_PLL_CLK_DIV,
	E013_PLL_MULTIPLIER,
	E013_OP_PIX_CLK_DIV,
	E013_OP_SYS_CLK_DIV
};

enum isx006_reg_mode {
	E013_X_ADDR_START,
	E013_X_ADDR_END,
	E013_Y_ADDR_START,
	E013_Y_ADDR_END,
	E013_X_OUTPUT_SIZE,
	E013_Y_OUTPUT_SIZE,
	E013_DATAPATH_SELECT,
	E013_READ_MODE,
	E013_ANALOG_CONTROL5,
	E013_DAC_LD_4_5,
	E013_SCALING_MODE,
	E013_SCALE_M,
	E013_LINE_LENGTH_PCK,
	E013_FRAME_LENGTH_LINES,
	E013_COARSE_INTEGRATION_TIME,
	E013_FINE_INTEGRATION_TIME,
	E013_FINE_CORRECTION
};

struct isx006_reg {
    /*const struct isx006_i2c_reg_conf *reg_mipi;
    const unsigned short reg_mipi_size;
    const struct isx006_i2c_reg_conf *rec_settings;
    const unsigned short rec_size;
    const struct isx006_i2c_reg_conf *reg_pll_p;
    const unsigned short reg_pll_p_size;
    const struct isx006_i2c_reg_conf *reg_pll_s;
    const unsigned short reg_pll_s_size;
    const struct isx006_i2c_reg_conf *reg_prev;
    const unsigned short reg_prev_size;
    const struct isx006_i2c_reg_conf *reg_snap;
    const unsigned short reg_snap_size;*/
    const struct isx006_i2c_reg_conf*reg_init;
    const unsigned short  reg_init_size;
    /* FIH-SW3-MM-URI-isx006 sensor setting-00+ */
    const struct isx006_i2c_reg_conf*reg_preload2;
    const unsigned short  reg_preload2_size;
    const struct isx006_i2c_reg_conf*reg_preload3;
    const unsigned short  reg_preload3_size;
    /* FIH-SW3-MM-URI-isx006 sensor setting-00- */
    /* FIH-SW3-MM-UW-read vendor id-00+*/
    const struct isx006_i2c_reg_conf*reg_preload2_2nd;
    const unsigned short  reg_preload2_2nd_size;
    const struct isx006_i2c_reg_conf*reg_preload3_2nd;
    const unsigned short  reg_preload3_2nd_size;

    const struct isx006_i2c_reg_conf*reg_preload3_reload;
    const unsigned short  reg_preload3_reload_size;
    
    /* FIH-SW3-MM-UW-read vendor id-00-*/
    const struct isx006_i2c_reg_conf *reg_arm_go;
    const unsigned short reg_arn_go_size;
    const struct isx006_i2c_reg_conf *reg_settings;
    const unsigned short reg_size;
    const struct isx006_i2c_reg_conf *reg_T_P;
    const unsigned short reg_T_P_size;
    const struct isx006_i2c_reg_conf *reg_analog;
    const unsigned short reg_analog_size;
    const struct isx006_i2c_reg_conf *reg_3a;
    const unsigned short reg_3a_size;
    const struct isx006_i2c_reg_conf *reg_clk;
    const unsigned short reg_clk_size;
    const struct isx006_i2c_reg_conf *reg_fps;
    const unsigned short reg_fps_size;
    const struct isx006_i2c_reg_conf *reg_prev;
    const unsigned short reg_prev_size;
    const struct isx006_i2c_reg_conf *reg_snap;
    const unsigned short reg_snap_size;
    const struct isx006_i2c_reg_conf *reg_prev_to_snap;
    const unsigned short reg_prev_to_snap_size;
    const struct isx006_i2c_reg_conf *reg_snap_to_prev;
    const unsigned short reg_snap_to_prev_size;

    const struct isx006_i2c_reg_conf *reg_sopt_meter;
    const unsigned short reg_sopt_meter_size;
    const struct isx006_i2c_reg_conf *reg_center_meter;
    const unsigned short reg_center_meter_size;
    const struct isx006_i2c_reg_conf *reg_multi_meter;
    const unsigned short reg_multi_meter_size;

    const struct isx006_i2c_reg_conf *reg_sport;
    const unsigned short reg_sport_size;
    const struct isx006_i2c_reg_conf *reg_bench_snow;
    const unsigned short reg_bench_snow_size;
    const struct isx006_i2c_reg_conf *reg_night;
    const unsigned short reg_night_size;
    const struct isx006_i2c_reg_conf *reg_night_off;
    const unsigned short reg_night_off_size;
    const struct isx006_i2c_reg_conf *reg_auto_scene;
    const unsigned short reg_auto_scene_size;
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
    const struct isx006_i2c_reg_conf *reg_landscape;
    const unsigned short reg_landscape_size;
    const struct isx006_i2c_reg_conf *reg_document;
    const unsigned short reg_document_size;
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}
    /* FIH-SW3-MM-UW-write OTP setting-00+*/
    const struct isx006_i2c_reg_conf *reg_SHD_MAX;
    const unsigned short reg_SHD_MAX_size;
    const struct isx006_i2c_reg_conf *reg_SHD_MIN;
    const unsigned short reg_SHD_MIN_size;
    const struct isx006_i2c_reg_conf *reg_SHD_TYP;
    const unsigned short reg_SHD_TYP_size;
    /* FIH-SW3-MM-UW-write OTP setting-00-*/

    const struct isx006_i2c_reg_conf *reg_SHD_MAX_2nd;
    const unsigned short reg_SHD_MAX_2nd_size;
    const struct isx006_i2c_reg_conf *reg_SHD_MIN_2nd;
    const unsigned short reg_SHD_MIN_2nd_size;
    const struct isx006_i2c_reg_conf *reg_SHD_TYP_2nd;
    const unsigned short reg_SHD_TYP_2nd_size;
};
#endif /* ISX006_H */
