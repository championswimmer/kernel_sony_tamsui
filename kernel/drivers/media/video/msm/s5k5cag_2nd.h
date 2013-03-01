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

#ifndef S5K5CAG_2ND_H
#define S5K5CAG_2ND_H
#include <linux/types.h>
#include <mach/board.h>
#include "fih_cam_api.h"

extern struct s5k5cag_2nd_reg s5k5cag_2nd_regs;

struct s5k5cag_2nd_i2c_reg_conf {
	unsigned short waddr;
	unsigned short wdata;
};

enum s5k5cag_2nd_test_mode_t {
	TEST_OFF,
	TEST_1,
	TEST_2,
	TEST_3
};

enum s5k5cag_2nd_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};
/*MTD-SW3-MM-UW-camframe timeout-02+*/
enum s5k5cag_2nd_setting {
	RES_PREVIEW,
	RES_CAPTURE,
	RES_SKIP
};
/*MTD-SW3-MM-UW-camframe timeout-02-*/
enum s5k5cag_2nd_reg_update {
	/* Sensor egisters that need to be updated during initialization */
	REG_INIT,
	/* Sensor egisters that needs periodic I2C writes */
	UPDATE_PERIODIC,
	/* All the sensor Registers will be updated */
	UPDATE_ALL,
	/* Not valid update */
	UPDATE_INVALID
};

enum s5k5cag_2nd_reg_pll {
	E013_VT_PIX_CLK_DIV,
	E013_VT_SYS_CLK_DIV,
	E013_PRE_PLL_CLK_DIV,
	E013_PLL_MULTIPLIER,
	E013_OP_PIX_CLK_DIV,
	E013_OP_SYS_CLK_DIV
};

enum s5k5cag_2nd_reg_mode {
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

struct s5k5cag_2nd_reg {
	/*const struct s5k5cag_2nd_i2c_reg_conf *reg_mipi;
	const unsigned short reg_mipi_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_settings;
	const unsigned short reg_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_pll_p;
	const unsigned short reg_pll_p_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_pll_s;
	const unsigned short reg_pll_s_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_prev;
	const unsigned short reg_prev_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_snap;
	const unsigned short reg_snap_size;*/
    
	const struct s5k5cag_2nd_i2c_reg_conf *reg_arm_go;
	const unsigned short reg_arn_go_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_settings;
	const unsigned short reg_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_T_P;
	const unsigned short reg_T_P_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_analog;
	const unsigned short reg_analog_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_3a;
	const unsigned short reg_3a_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_clk;
	const unsigned short reg_clk_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_fps;
	const unsigned short reg_fps_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_prev;
	const unsigned short reg_prev_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_snap;
	const unsigned short reg_snap_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_prev_to_snap;
	const unsigned short reg_prev_to_snap_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_snap_to_prev;
	const unsigned short reg_snap_to_prev_size;
	
	const struct s5k5cag_2nd_i2c_reg_conf *reg_sopt_meter;
	const unsigned short reg_sopt_meter_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_center_meter;
	const unsigned short reg_center_meter_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_multi_meter;
	const unsigned short reg_multi_meter_size;

	const struct s5k5cag_2nd_i2c_reg_conf *reg_sport;
	const unsigned short reg_sport_size;
       const struct s5k5cag_2nd_i2c_reg_conf *reg_sport_off;
	const unsigned short reg_sport_off_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_bench_snow;
	const unsigned short reg_bench_snow_size;
	/* FIH-SW3-MM-UW-tuning0409-00+*/
	const struct s5k5cag_2nd_i2c_reg_conf *reg_night_0;
	const unsigned short reg_night_0_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_night_1;
	const unsigned short reg_night_1_size;
	/* FIH-SW3-MM-UW-tuning0409-00-*/
	const struct s5k5cag_2nd_i2c_reg_conf *reg_night_off_0;
	const unsigned short reg_night_off_0_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_night_off_1;
	const unsigned short reg_night_off_1_size;
	const struct s5k5cag_2nd_i2c_reg_conf *reg_auto_scene;
	const unsigned short reg_auto_scene_size;
    
};
#endif /* S5K5CAG_2ND_H */
