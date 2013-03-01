/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
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
 *
 */

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_renesas_hvga.h"
#include <mach/vreg.h>
#include <linux/gpio.h>

static struct msm_panel_common_pdata *mipi_renesas_pdata;

static struct dsi_buf renesas_tx_buf;
static struct dsi_buf renesas_rx_buf;
static int mipi_renesas_lcd_init(void);

static int bl_level_old = 31;
static int display_initialize = 0;

static char BKL_PWM[11] = {
/*   LEVEL Value,   Duty,    Brightness */
	0x00,  /*  0,   0.0%,   0.00 cd/m^2 */
	0x15,  /* 21,   8.2%,  39.78 cd/m^2 */
	0x31,  /* 49,  19.2%,  92.70 cd/m^2 */
	0x4E,  /* 78,  30.6%, 145.50 cd/m^2 */
	0x6D,  /*109,  42.8%, 201.10 cd/m^2 */
	0x84,  /*132,  51.7%, 242.30 cd/m^2 */
	0x9C,  /*156,  61.2%, 284.40 cd/m^2 */
	0xB4,  /*180,  70.7%, 326.00 cd/m^2 */
	0xCD,  /*205,  80.4%, 368.00 cd/m^2 */
	0xE6,  /*230,  90.2%, 410.00 cd/m^2 */
	0xFF   /*255, 100.0%, 450.00 cd/m^2 */
};

/* renesas hvga panel */
static char normal_display_mode_on[2] = {0x13, 0x00}; /* DTYPE_DCS_WRITE */
static char inversion_mode_off[2] = {0x20, 0x00}; /* DTYPE_DCS_WRITE */
static char memory_address_control[2] = {0x36, 0x40}; /* DTYPE_DCS_WRITE1 */

static char positive_gamma_setting[16] = { /* DTYPE_GEN_LWRITE */
	0xE0, 0x0C, 0x0D, 0x10,
	0x01, 0x0C, 0x05, 0x33,
	0x01, 0x46, 0x03, 0x10,
	0x0D, 0x13, 0x16, 0x0F
};
static char negative_gamma_setting[16] = { /* DTYPE_GEN_LWRITE */
	0xE1, 0x00, 0x1F, 0x26,
	0x04, 0x10, 0x04, 0x40,
	0x0A, 0x55, 0x04, 0x0C,
	0x09, 0x32, 0x36, 0x0C
};

static char egineer_test_code2[9] = { /* DTYPE_GEN_LWRITE */
	0xF1, 0x36, 0x04, 0x00,
	0x3C, 0x0F, 0x0F, 0xA4,
	0x02
};
static char egineer_test_code1[6] = { /* DTYPE_GEN_LWRITE */
	0xF7, 0xA9, 0x91, 0x2D,
	0x0A, 0x4F
};
static char egineer_test_code3[3] = {0xF8, 0x21, 0x04}; /* DTYPE_GEN_LWRITE */
static char egineer_test_code4[10] = { /* DTYPE_GEN_LWRITE */
	0xF2, 0x18, 0xA3, 0x12,
	0x02, 0xB2, 0x12, 0xFF,
	0x10, 0x00
};
static char column_address[5] = { /* DTYPE_DCS_LWRITE */
	0x2A, 0x00, 0x00, 0x01, 0x3F
};
static char page_address[5] = { /* DTYPE_DCS_LWRITE */
	0x2B, 0x00, 0x00, 0x01, 0xDF
};
static char idle_mode_off[2] = {0x38, 0x00}; /* DTYPE_DCS_WRITE */

static char power_setting_0[3] = {0xC0, 0x09, 0x09}; /* DTYPE_GEN_LWRITE */

static char power_setting_1[3] = {0xC1, 0x44, 0x00}; /* DTYPE_GEN_LWRITE */
static char power_setting_2[2] = {0xC2, 0x33}; /* DTYPE_GEN_LWRITE */

static char egineer_test_code5[3] = {0xF9, 0x00, 0x08}; /* DTYPE_GEN_LWRITE */

static char two_dot_inversion[2] = {0xB4, 0x02}; /* DTYPE_GEN_LWRITE */
static char frame_rate_setting[3] = {0xB1, 0xB0, 0x11}; /* DTYPE_GEN_LWRITE */
static char sleep_out[2] = {0x11, 0x00}; /* DTYPE_DCS_WRITE */
static char display_on[2] = {0x29, 0x00}; /* DTYPE_DCS_WRITE */

static char display_off[2] = {0x28, 0x00}; /* DTYPE_DCS_WRITE */

static char write_display_brightness[2] = {0x51, 0x00}; /* DTYPE_DCS_WRITE1 */
/* BCTRL=1, DD=0, BL=1 */
static char write_ctrl_display[2] = {0x53, 0x24}; /* DTYPE_DCS_WRITE1 */
static char cabc_ctrl_9[2] = {0xCF, 0x02}; /* DTYPE_GEN_WRITE1 */

static struct dsi_cmd_desc renesas_video_on_cmds[] = {

	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(normal_display_mode_on), normal_display_mode_on},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(inversion_mode_off), inversion_mode_off},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(memory_address_control), memory_address_control},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(positive_gamma_setting), positive_gamma_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(negative_gamma_setting), negative_gamma_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(egineer_test_code2), egineer_test_code2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(egineer_test_code1), egineer_test_code1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(egineer_test_code3), egineer_test_code3},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 2,
		sizeof(egineer_test_code4), egineer_test_code4},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(column_address), column_address},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(page_address), page_address},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(idle_mode_off), idle_mode_off},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(power_setting_0), power_setting_0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(power_setting_1), power_setting_1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 5,
		sizeof(power_setting_2), power_setting_2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(egineer_test_code5), egineer_test_code5},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(two_dot_inversion), two_dot_inversion},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(frame_rate_setting), frame_rate_setting},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cabc_ctrl_9), cabc_ctrl_9},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_display), write_ctrl_display},
	{DTYPE_DCS_WRITE, 1, 0, 0, 131,
		sizeof(sleep_out), sleep_out},
	{DTYPE_DCS_WRITE, 1, 0, 0, 5,
		sizeof(display_on), display_on}

};

static struct dsi_cmd_desc renesas_video_off_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off}
};


static struct dsi_cmd_desc renesas_video_bkl_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness}
};


static int mipi_renesas_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
    int rc = 0; 

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mfd = platform_get_drvdata(pdev);
	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	mipi = &mfd->panel_info.mipi;
	/* FIH-SW-MM-VH-DISPLAY-00+ */
    return -ENODEV;

	if (display_initialize)
		return 0;

	if (mipi->mode == DSI_CMD_MODE) {
		egineer_test_code1[4] = 0x8A;
	}

	mutex_lock(&mfd->dma->ov_mutex);
	/* FIH-SW-MM-VH-DISPLAY-00*[ */
	rc=mipi_dsi_cmds_tx(mfd, &renesas_tx_buf, renesas_video_on_cmds,
		ARRAY_SIZE(renesas_video_on_cmds));
	mutex_unlock(&mfd->dma->ov_mutex);
	printk(KERN_ALERT "[DISPLAY] Finish sending dsi commands\n");

	display_initialize = 1;

	return rc;
	/* FIH-SW-MM-VH-DISPLAY-00*] */
}

static int mipi_renesas_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mfd = platform_get_drvdata(pdev);
	/* FIH-SW-MM-VH-DISPLAY-00+ */
    return 0;

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	if (!display_initialize)
		return 0;

	mutex_lock(&mfd->dma->ov_mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, &renesas_tx_buf, renesas_video_off_cmds,
			ARRAY_SIZE(renesas_video_off_cmds));
	mipi_set_tx_power_mode(1);
	mutex_unlock(&mfd->dma->ov_mutex);

	display_initialize = 0;

	return 0;
}

static void mipi_renesas_lcd_backlight(struct msm_fb_data_type *mfd)
{
	struct mipi_panel_info *mipi;

	mipi = &mfd->panel_info.mipi;

	printk(KERN_ALERT "[DISPLAY] Enter %s, set backlight level to %d\n",
			__func__, mfd->bl_level);
	/* FIH-SW-MM-VH-DISPLAY-00+ */
    return;

	if ((bl_level_old == mfd->bl_level) || (!display_initialize))
		return;


	write_display_brightness[1] = BKL_PWM[mfd->bl_level];  /* Duty_Cycle */


	mutex_lock(&mfd->dma->ov_mutex);
	mipi_set_tx_power_mode(0);
	down(&mfd->dma->mutex);
	mipi_dsi_cmds_tx(mfd, &renesas_tx_buf, renesas_video_bkl_cmds,
			ARRAY_SIZE(renesas_video_bkl_cmds));
	up(&mfd->dma->mutex);
	mipi_set_tx_power_mode(1);
	mutex_unlock(&mfd->dma->ov_mutex);

	bl_level_old = mfd->bl_level;
}

static int __devinit mipi_renesas_lcd_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	if (pdev->id == 0) {
		mipi_renesas_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_renesas_lcd_probe,
	.driver = {
		.name   = "mipi_renesas",
	},
};

static struct msm_fb_panel_data renesas_panel_data = {
	.on		= mipi_renesas_lcd_on,
	.off	= mipi_renesas_lcd_off,
	.set_backlight = mipi_renesas_lcd_backlight,
};

static int ch_used[3];

int mipi_renesas_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;
	ret = mipi_renesas_lcd_init();
    if (ret) {
        pr_err("mipi_renesas_lcd_init() failed with ret %u\n", ret);
        return ret;
        }

	pdev = platform_device_alloc("mipi_renesas", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	renesas_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &renesas_panel_data,
		sizeof(renesas_panel_data));
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}

static int  mipi_renesas_lcd_init(void)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	mipi_dsi_buf_alloc(&renesas_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&renesas_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}
