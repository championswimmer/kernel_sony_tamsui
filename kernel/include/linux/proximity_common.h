/*
 * Copyright (C) 2012 Arima Communications Crop.
 * Author: Huize Weng <huizeweng@arimacomm.com.tw>
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

#ifndef _PROXIMITY_COMMOM_H_
#define _PROXIMITY_COMMOM_H_

#include <linux/types.h>
#include <linux/sensors_mctl.h>

#define Buff_Lenght 12
#define Buff_Size (Buff_Lenght * sizeof(char))

#define DEFAULT_THRESHOLD 0XFFFF
#define I2CERROR_TRANSACTION -9999

enum{
	PROXIMITY_STATE_FALSE		= 0,
	PROXIMITY_STATE_TRUE		= 1,
	PROXIMITY_STATE_UNKNOWN		= 0xFF,
};

typedef struct Proximity{
	struct input_dev*		input;
	struct mutex			mutex;
	struct delayed_work 	dw;
	ProximityInfor			sdata;
	bool					enabled;
	bool					suspend;
}Proximity;

// It needs to reset memory
static struct i2c_client* this_client = NULL;
static struct workqueue_struct* Proximity_WorkQueue = NULL;
static u8 i2cData[2];
static bool i2cIsFine = false;
static bool need2Reset = false;
static bool need2ChangeState = false;
static u8 Proxmity_sensor_opened = 0;
static unsigned long SleepTime = 0;

#endif
