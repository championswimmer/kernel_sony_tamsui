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

#ifndef MT9V115_H
#define MT9V115_H
#include <linux/types.h>
#include <mach/board.h>
#include "fih_cam_api.h"//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02+

extern struct mt9v115_reg mt9v115_regs;


enum mt9v115_test_mode_t {
	TEST_OFF,
	TEST_1,
	TEST_2,
	TEST_3
};

enum mt9v115_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};

enum mt9v115_setting {
	RES_PREVIEW,
	RES_CAPTURE
};

enum mt9v115_reg_update {
	/* Sensor rgisters that need to be updated during initialization */
	REG_INIT,
	/* Sensor rgisters that needs periodic I2C writes */
	UPDATE_PERIODIC,
	/* All the sensor registers will be updated */
	UPDATE_ALL,
	/* Not valid update */
	UPDATE_INVALID
};

//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02+{
struct mt9v115_reg {
    //Camera init table
    const struct fih_i2c_reg_conf *reg_init_tbl;
    const unsigned short reg_init_tbl_size;
    //Camera sub init table
    const struct fih_i2c_reg_conf *reg_sub_init_tbl;//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+
    const unsigned short reg_sub_init_tbl_size;//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+
    //Camera start stream table
    const struct fih_i2c_reg_conf *reg_start_tbl;
    const unsigned short reg_start_tbl_size;
    //Camera stop stream table
    const struct fih_i2c_reg_conf *reg_stop_tbl;
    const unsigned short reg_stop_tbl_size;

	/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+{ */
	//Camera fps_15 setting table
	const struct fih_i2c_reg_conf *reg_fps_15_tbl;
    const unsigned short reg_fps_15_tbl_size;
	//Camera fps_30 setting table
	const struct fih_i2c_reg_conf *reg_fps_30_tbl;
    const unsigned short reg_fps_30_tbl_size;
	/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+} */	
};
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02+}

#endif /* MT9V115_H */
