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

#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/delay.h>//For hr_msleep()
#include <mach/camera.h>
#include <linux/regulator/consumer.h>//For regulator API

#ifdef CONFIG_FIH_HR_MSLEEP
#define cam_msleep hr_msleep
#else
#define cam_msleep msleep
#endif

#define HIGH 1
#define LOW  0

enum fih_i2c_width {
	WORD_LEN,
	BYTE_LEN,
	WORD_POLL,
	BYTE_POLL
};

struct fih_i2c_reg_conf {
	unsigned short waddr;
	unsigned short wdata;
	enum fih_i2c_width width;
	unsigned short mdelay_time;
};

//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01+{
extern bool bMainCameraIsReset;
extern bool bFrontCameraIsReset;
//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01+}

/*===========================================================================
 * FUNCTION    - fih_enable_mclk -
 *
 * DESCRIPTION: Use to config camera MCLK pin and enable MCLK.
 *
 * PARAMETER:
 *   gpio_id  : MCLK pin number.
 *   clk_rate : Clock rate
 *==========================================================================*/
extern int fih_enable_mclk(int gpio_id, int clk_rate);

/*===========================================================================
 * FUNCTION    - fih_disable_mclk -
 *
 * DESCRIPTION: Use to config camera MCLK pin and disable MCLK.
 *
 * PARAMETER:
 *   gpio_id  : MCLK pin number.
 *   clk_rate : Clock rate
 *==========================================================================*/
extern int fih_disable_mclk(int gpio_id, int clk_rate);

/*===========================================================================
 * FUNCTION    - mt9v115_i2c_read -
 *
 * DESCRIPTION: Use to read I2C register.
 *
 * PARAMETER:
 *   client : I2C handle of slave device.
 *   raddr : Registry address.
 *   rdata : Save return value.
 *   width : Read length
 *==========================================================================*/
extern int32_t fih_i2c_read(const struct i2c_client *client, unsigned short raddr, unsigned short *rdata, enum fih_i2c_width width);

/*===========================================================================
 * FUNCTION    - fih_i2c_write -
 *
 * DESCRIPTION: Use to write I2C register.
 *
 * PARAMETER:
 *   client : I2C handle of slave device.
 *   waddr : Registry address.
 *   wdata : Write value.
 *   width : Read length
 *==========================================================================*/
extern int32_t fih_i2c_write(const struct i2c_client *client, unsigned short waddr, unsigned short wdata, enum fih_i2c_width width);
extern int32_t fih_i2c_no_ack_write(const struct i2c_client *client, unsigned short waddr, unsigned short wdata, enum fih_i2c_width width);

/*===========================================================================
 * FUNCTION    - fih_i2c_write_table -
 *
 * DESCRIPTION: Use to write I2C register table.
 *
 * PARAMETER:
 *   client : I2C handle of slave device.
 *   reg_conf_tbl : Registry array.
 *   num_of_items_in_table : Array size.
 *==========================================================================*/
extern int32_t fih_i2c_write_table(const struct i2c_client *client, struct fih_i2c_reg_conf const *reg_conf_tbl, int num_of_items_in_table);

/*===========================================================================
 * FUNCTION    - fih_set_gpio_output_value -
 *
 * DESCRIPTION: Use to set output gpio value.
 *
 * PARAMETER:
 *   gpio_id : gpio number.
 *   tag : Tag of gpio.
 *   value : HIGH or LOW.
 *==========================================================================*/
extern int fih_set_gpio_output_value(int gpio_id, const char *tag, int value);

extern int fih_regulator_enable(const char *id, int voltage, const char *tag);
extern int fih_regulator_disable(const char *id, const char *tag);
