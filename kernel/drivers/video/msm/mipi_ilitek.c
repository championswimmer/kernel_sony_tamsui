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
#include "mipi_ilitek.h"
#include <mach/vreg.h>
#include <linux/gpio.h>
/* FIH-SW-MM-VH-DISPLAY-47+ */
#include <mach/fih_lcm.h>

static struct msm_panel_common_pdata *mipi_ilitek_pdata;

static struct dsi_buf ilitek_tx_buf;
static struct dsi_buf ilitek_rx_buf;
static int mipi_ilitek_lcd_init(void);
/* FIH-SW-MM-VH-DISPLAY-21+ */
static struct msm_fb_data_type *gmfd = NULL;
static int display_initialize = 0;
/* FIH-SW3-MM-NC-LCM-07-[+ */
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
/* FIH-SW3-MM-NC-LCM-07-]- */

/* ilitek hvga panel */
static char normal_display_mode_on[2] = {0x13, 0x00}; /* DTYPE_DCS_WRITE */
static char inversion_mode_off[2] = {0x20, 0x00}; /* DTYPE_DCS_WRITE */
static char memory_address_control[2] = {0x36, 0x40}; /* DTYPE_DCS_WRITE1 */
/* FIH-SW3-MM-NC-LCM-07-[+ */
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
/* FIH-SW3-MM-NC-LCM-07-]- */
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
/* FIH-SW-MM-VH-DISPLAY-23*[ */
static char ilitek_page_address[5] = { /* DTYPE_DCS_LWRITE */
	0x2B, 0x00, 0x00, 0x01, 0xDF
};
/* FIH-SW-MM-VH-DISPLAY-23*] */
static char idle_mode_off[2] = {0x38, 0x00}; /* DTYPE_DCS_WRITE */
/* FIH-SW3-MM-NC-LCM-07-[+ */
static char power_setting_0[3] = {0xC0, 0x09, 0x09}; /* DTYPE_GEN_LWRITE */
/* FIH-SW3-MM-NC-LCM-07-]- */
static char power_setting_1[3] = {0xC1, 0x44, 0x00}; /* DTYPE_GEN_LWRITE */
static char power_setting_2[2] = {0xC2, 0x33}; /* DTYPE_GEN_LWRITE */
/* FIH-SW3-MM-NC-LCM-11-[+ */
static char egineer_test_code5[3] = {0xF9, 0x00, 0x08}; /* DTYPE_GEN_LWRITE */
/* FIH-SW3-MM-NC-LCM-11-]- */
static char two_dot_inversion[2] = {0xB4, 0x02}; /* DTYPE_GEN_LWRITE */
static char frame_rate_setting[3] = {0xB1, 0xB0, 0x11}; /* DTYPE_GEN_LWRITE */
static char sleep_out[2] = {0x11, 0x00}; /* DTYPE_DCS_WRITE */
static char display_on[2] = {0x29, 0x00}; /* DTYPE_DCS_WRITE */
static char display_off[2] = {0x28, 0x00}; /* DTYPE_DCS_WRITE */
static char cabc_ctrl_9[2] = {0xCF, 0x02}; /* DTYPE_GEN_WRITE1 */
static char write_display_brightness[2] = {0x51, 0x00}; /* DTYPE_DCS_WRITE1 */

#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
/* BCTRL=1, DD=1, BL=1 */
static char write_ctrl_displayDD1[2] = {0x53, 0x2C}; /* DTYPE_DCS_WRITE1 */
#endif
/* BCTRL=1, DD=0, BL=1 */
static char write_ctrl_displayDD0[2] = {0x53, 0x24}; /* DTYPE_DCS_WRITE1 */

#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
static struct dsi_cmd_desc ilitek_write_DD1[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD1), write_ctrl_displayDD1},
};

static struct dsi_cmd_desc ilitek_write_DD0[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
};
#endif
/* FIH-SW-MM-VH-DISPLAY-24*[ */
static struct dsi_cmd_desc ilitek_video_on_cmds[] = {
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
/* FIH-SW-MM-VH-DISPLAY-23*[ */
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(ilitek_page_address), ilitek_page_address},
/* FIH-SW-MM-VH-DISPLAY-23*] */
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(idle_mode_off), idle_mode_off},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(power_setting_0), power_setting_0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(power_setting_1), power_setting_1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 10,
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
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
	{DTYPE_DCS_WRITE, 1, 0, 0, 131,
		sizeof(sleep_out), sleep_out},
	{DTYPE_DCS_WRITE, 1, 0, 0, 5,
		sizeof(display_on), display_on}
};
/* FIH-SW-MM-VH-DISPLAY-24*] */
/* FIH-SW-MM-VH-DISPLAY-20*[ */
static struct dsi_cmd_desc ilitek_video_off_cmds[] = {
/* FIH-SW-MM-VH-DISPLAY-48*[ */
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
/* FIH-SW-MM-VH-DISPLAY-48*] */
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off}
};
/* FIH-SW-MM-VH-DISPLAY-20*] */
/* FIH-SW3-MM-NC-LCM-05-[+ */
static struct dsi_cmd_desc ilitek_video_bkl_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness}
};
/* FIH-SW3-MM-NC-LCM-05-]- */

/* FIH-SW-MM-VH-DISPLAY-01+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_ID_CHECK

static char manufacture_idDA[2] = {0xDA, 0x00}; /* DTYPE_DCS_READ */
static char manufacture_idDB[2] = {0xDB, 0x00}; /* DTYPE_DCS_READ */
static char manufacture_idDC[2] = {0xDC, 0x00}; /* DTYPE_DCS_READ */

static struct dsi_cmd_desc ilitek_manufacture_id_cmdDA = {
	DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(manufacture_idDA), manufacture_idDA};
static struct dsi_cmd_desc ilitek_manufacture_id_cmdDB = {
	DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(manufacture_idDB), manufacture_idDB};
static struct dsi_cmd_desc ilitek_manufacture_id_cmdDC = {
	DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(manufacture_idDC), manufacture_idDC};
	
static char set_tear_on[2] = {0x35, 0x00};
static struct dsi_cmd_desc dsi_tear_on_cmd = {
	DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(set_tear_on), set_tear_on};

static char set_tear_off[2] = {0x34, 0x00};
static struct dsi_cmd_desc dsi_tear_off_cmd = {
	DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(set_tear_off), set_tear_off};

#endif
/* FIH-SW-MM-VH-DISPLAY-01+] */
/* FIH-SW-MM-VH-DISPLAY-03*[ */
static int mipi_ilitek_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
	/* FIH-SW-MM-VH-DISPLAY-00+ */
	int rc = 0;

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mfd = platform_get_drvdata(pdev);
	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	mipi = &mfd->panel_info.mipi;
	
	/* FIH-SW-MM-VH-DISPLAY-21+ */
	gmfd = mfd;
	
	if (display_initialize)
		return 0;

	if (mipi->mode == DSI_CMD_MODE) {
		egineer_test_code1[4] = 0x8A;
	}
	
	/*TODO: Is it necessary to enter critical section? */
	rc = mipi_dsi_cmds_tx(mfd, &ilitek_tx_buf, ilitek_video_on_cmds,
		ARRAY_SIZE(ilitek_video_on_cmds));

	printk(KERN_ALERT "[DISPLAY] Finish sending dsi commands\n, rc=%d\r\n", rc);

	display_initialize = 1;
	
/* FIH-SW-MM-VH-DISPLAY-47+[ */
	mfd->panel_info.lcm_model = LCM_ID_DA_TAP_CMI;
/* FIH-SW-MM-VH-DISPLAY-47+] */

	if(rc >0)
		rc = 0;

	return rc;
	/* FIH-SW-MM-VH-DISPLAY-00*] */
}

static int mipi_ilitek_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	if (!display_initialize)
		return 0;

	/*TODO: Is it necessary to enter critical section? */
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, &ilitek_tx_buf, ilitek_video_off_cmds,
			ARRAY_SIZE(ilitek_video_off_cmds));
	mipi_set_tx_power_mode(1);

	display_initialize = 0;

	return 0;
}

/* FIH-SW-MM-VH-DISPLAY-07*[ */
static void mipi_ilitek_lcd_backlight(struct msm_fb_data_type *mfd)
{
	struct mipi_panel_info *mipi;

	mipi = &mfd->panel_info.mipi;

	printk(KERN_ALERT "[DISPLAY] Enter %s, set backlight level to %d\n",
			__func__, mfd->bl_level);

	if (!display_initialize)
		return;

/* FIH-SW3-MM-NC-LCM-03-[+ */
	write_display_brightness[1] = BKL_PWM[mfd->bl_level];  /* Duty_Cycle */
/* FIH-SW3-MM-NC-LCM-03-]- */

	/* FIH-SW-MM-VH-DISPLAY-04*[ */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, &ilitek_tx_buf, ilitek_video_bkl_cmds,
			ARRAY_SIZE(ilitek_video_bkl_cmds));
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);
	/* FIH-SW-MM-VH-DISPLAY-04*] */

}
/* FIH-SW-MM-VH-DISPLAY-07*] */
/* FIH-SW-MM-VH-DISPLAY-03*] */
/* FIH-SW-MM-VH-DISPLAY-21+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
static int mipi_ilitek_set_dimming(char enable)
{
	printk(KERN_ALERT "[DISPLAY] %s(%d)\n", __func__, enable);

	if (!display_initialize)
		return 0;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);

	if(enable) {
		mipi_dsi_cmds_tx(gmfd, &ilitek_tx_buf, ilitek_write_DD1,
				ARRAY_SIZE(ilitek_write_DD1));
	}else{
		mipi_dsi_cmds_tx(gmfd, &ilitek_tx_buf, ilitek_write_DD0,
				ARRAY_SIZE(ilitek_write_DD0));
	}

	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);
	
	return 0;
}
#endif
/* FIH-SW-MM-VH-DISPLAY-21+] */
/* FIH-SW-MM-VH-DISPLAY-04+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_ID_CHECK
static int mipi_ilitek_manufacture_id(struct msm_fb_data_type *mfd)
{
	struct dsi_buf *rp, *tp;
    char da, db, dc;
    int retVal = 0;

	tp = &ilitek_tx_buf;
	rp = &ilitek_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	/* Disable TE */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, tp, &dsi_tear_off_cmd, 1);
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);

	/* Read ID 0xDA */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	retVal = mipi_dsi_cmds_rx(mfd, tp, rp, &ilitek_manufacture_id_cmdDA, 1);
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);
	da = *((char *) rp->data);

	/* Read ID 0xDB */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	retVal = mipi_dsi_cmds_rx(mfd, tp, rp, &ilitek_manufacture_id_cmdDB, 1);
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);
	db = *((char *) rp->data);

	/* Read ID 0xDC */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	retVal = mipi_dsi_cmds_rx(mfd, tp, rp, &ilitek_manufacture_id_cmdDC, 1);
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);
	dc = *((char *) rp->data);

	/* Enable TE */
	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, tp, &dsi_tear_on_cmd, 1);
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);

	if((da == db) && (db == dc)) {
		retVal = -EPERM;
	}
	return retVal;
}
#endif
/* FIH-SW-MM-VH-DISPLAY-04+] */

static int __devinit mipi_ilitek_lcd_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	if (pdev->id == 0) {
		mipi_ilitek_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_ilitek_lcd_probe,
	.driver = {
		.name   = "mipi_ilitek",
	},
};

static struct msm_fb_panel_data ilitek_panel_data = {
	.on		= mipi_ilitek_lcd_on,
	.off	= mipi_ilitek_lcd_off,
	.set_backlight = mipi_ilitek_lcd_backlight,
/* FIH-SW-MM-VH-DISPLAY-01+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_ID_CHECK
	.get_id = mipi_ilitek_manufacture_id,
#endif
/* FIH-SW-MM-VH-DISPLAY-01+] */
/* FIH-SW-MM-VH-DISPLAY-21+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
	.set_dimming = mipi_ilitek_set_dimming,
#endif
/* FIH-SW-MM-VH-DISPLAY-21+] */

};

static int ch_used[3];

int mipi_ilitek_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	ret = mipi_ilitek_lcd_init();
	if (ret) {
		pr_err("mipi_ilitek_lcd_init() failed with ret %u\n", ret);
		return ret;
	}

	pdev = platform_device_alloc("mipi_ilitek", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	ilitek_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &ilitek_panel_data,
		sizeof(ilitek_panel_data));
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

static int mipi_ilitek_lcd_init(void)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	mipi_dsi_buf_alloc(&ilitek_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&ilitek_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}
