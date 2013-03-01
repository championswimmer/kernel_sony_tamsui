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

#ifndef _ACCELEROMETER_COMMOM_H_
#define _ACCELEROMETER_COMMOM_H_

#include <linux/types.h>
#include <linux/sensors_mctl.h>

#define Buff_Lenght 21
#define Buff_Size (Buff_Lenght * sizeof(char))

#define FILTER_SIZE		4
#define FILTER_INDEX	(FILTER_SIZE - 1)
#define FILTER_SIZEBIT	2

typedef struct AccelerometerData{
	int X;
	int Y;
	int Z;
}AccelerometerData;

typedef struct Accelerometer{
	struct input_dev*		input;
	struct mutex			mutex;
	struct delayed_work		dw;
	AccelerometerData		sdata;
	AccelerometerAxisOffset	odata;
	bool					enabled;
	bool					suspend;
}Accelerometer;

// It needs to reset memory
static int Accelerometer_sensor_opened = 0;
static struct i2c_client* this_client = NULL;
static struct workqueue_struct* Accelerometer_WorkQueue = NULL;
static unsigned long SleepTime = 0;
static u8 i2cData[6];
static u8 queueIndex = 0;
static u8 ignoreCount = 0;
static AccelerometerData rawData;
static AccelerometerData averageData;
static AccelerometerData queueData[FILTER_SIZE];

#endif
