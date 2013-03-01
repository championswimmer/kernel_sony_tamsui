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
#include "mipi_himax.h"
#include <mach/vreg.h>
#include <linux/gpio.h>

static struct msm_panel_common_pdata *mipi_himax_pdata;

static struct dsi_buf himax_tx_buf;
static struct dsi_buf himax_rx_buf;

/* FIH-SW-MM-VH-DISPLAY-09*[ */
static struct msm_fb_data_type *gmfd = NULL;
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
int gMinBrightness = DEALULT_MIN_BRIGHTNESS;
int gDeltaMinBrightness = DEALULT_DELTA_BRIGHTNESS;
#endif
/* FIH-SW-MM-VH-DISPLAY-09*] */

static int display_initialize = 0;
/* FIH-SW-MM-VH-DISPLAY-26*[ */
static char BKL_PWM[11] = {
/*   LEVEL Value,	Brightness */
	0x00,  /*  0,	0.00 cd/m^2 */
	0x0A,  /* 10,	35 cd/m^2 */
	0x28,  /* 40,	85 cd/m^2 */
	0x41,  /* 65,	135 cd/m^2 */
	0x5A,  /* 90,	188 cd/m^2 */
	0x73,  /*115,	226 cd/m^2 */
	0x91,  /*145,	265 cd/m^2 */
	0xAA,  /*170,	303 cd/m^2 */
	0xC3,  /*195,	342 cd/m^2 */
	0xDC,  /*220,	380 cd/m^2 */
	0xFF   /*255,	416 cd/m^2 */
};
/* FIH-SW-MM-VH-DISPLAY-26*] */
static char himax_EnableExtensionCommand[4] = {0xB9, 0xFF, 0x83, 0x57}; /* DTYPE_GEN_LWRITE */
static char himax_SleepIn[2] = {0x10, 0x00}; /* DTYPE_DCS_WRITE */
/* FIH-SW-MM-VH-DISPLAY-15*[ */
/* GAMMA 2.8*/
static char himax_Gamma[68] = {
	0xE0,
	0x00, 0x00, 0x05, 0x00, 
	0x0F, 0x00, 0x16, 0x00,
	0x20, 0x00, 0x28, 0x00,
	0x39, 0x00, 0x45, 0x00,
	0x51, 0x00, 0x46, 0x00,
	0x3F, 0x00, 0x32, 0x00,
	0x1B, 0x00, 0x0F, 0x00,
	0x04, 0x00, 0x01, 0x00,
	0x00, 0x01, 0x00, 0x00,
	0x09, 0x00, 0x10, 0x00,
	0x1E, 0x00, 0x26, 0x00,
	0x3B, 0x00, 0x47, 0x00,
	0x51, 0x00, 0x44, 0x00,
	0x3B, 0x00, 0x34, 0x00,
	0x1D, 0x00, 0x11, 0x00,
	0x06, 0x00, 0x03, 0x00,
	0x02, 0x00, 0x00,
};
/* FIH-SW-MM-VH-DISPLAY-15*] */
/* FIH-SW-MM-VH-DISPLAY-09*[ */
static char himax_SleepOut[2] = {0x11, 0x00}; /* DTYPE_DCS_WRITE */
static char himax_InterfacePixelFormat[2] = {0x3A, 0x77}; /* DTYPE_DCS_WRITE1 */
static char himax_PanelSetting[2] = {0xCC, 0x0B}; /* DTYPE_GEN_WRITE1 */
static char himax_SETBGP[3] = {0xB5, 0xA9, 0x18}; /* DTYPE_GEN_LWRITE */
static char himax_SetPowerControl[7] = {0xB1, 0x00, 0x11, 0x1C, 0x1C, 0x83, 0x48}; /* DTYPE_GEN_LWRITE */
static char himax_SetDisplayCycleRegister[8] = {0xB4, 0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78}; /* DTYPE_GEN_LWRITE */
static char himax_SETSTBA[7] = {0xC0, 0x73, 0x50, 0x01, 0x3C, 0xC8, 0x08}; /* DTYPE_GEN_LWRITE */
static char himax_MIPIDSISettings[16] = {0xBA, 0x00, 0x56, 0xD4, 0x00, 0x0A, 0x00, 0x10, 0x32, 0x6E, 0x04, 0x05, 0x9A, 0x17, 0x19, 0x10};
/* FIH-SW-MM-VH-DISPLAY-15-[ */
#if 0
static char himax_setVCOM[5] = {0xB6, 0x36}; /* DTYPE_GEN_WRITE1 */
#endif
/* FIH-SW-MM-VH-DISPLAY-15-] */
static char himax_ColumnAddress[5] = {0x2A, 0x00, 0x00, 0x01, 0x3F}; /* DTYPE_DCS_LWRITE */
static char himax_PageAddress[5] = {0x2B, 0x00, 0x00, 0x01, 0xDF}; /* DTYPE_DCS_LWRITE */
static char display_off[2] = {0x28, 0x00}; /* DTYPE_DCS_WRITE */
static char write_display_brightness[2] = {0x51, 0x00}; /* DTYPE_DCS_WRITE1 */
/* FIH-SW-MM-VH-DISPLAY-21*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
/* BCTRL=1, DD=1, BL=1 */
static char write_ctrl_displayDD1[2] = {0x53, 0x2C}; /* DTYPE_DCS_WRITE1 */
#endif
/* BCTRL=1, DD=0, BL=1 */
static char write_ctrl_displayDD0[2] = {0x53, 0x24}; /* DTYPE_DCS_WRITE1 */
/* FIH-SW-MM-VH-DISPLAY-21*] */

static char himax_DisplayON[2] = {0x29, 0x00};  /* DTYPE_DCS_WRITE1 */
/* FIH-SW-MM-VH-DISPLAY-28* */
static char CMI_PWM[3] = {0xC9, 0x8F, 0x01};  /* DTYPE_GEN_LWRITE */
static char himax_manufacture_idDA[2] = {0xDA, 0x00}; /* DTYPE_DCS_READ */
static char himax_manufacture_idDB[2] = {0xDB, 0x00}; /* DTYPE_DCS_READ */
static char himax_manufacture_idDC[2] = {0xDC, 0x00}; /* DTYPE_DCS_READ */
static char himax_manufacture_id0A[2] = {0x0A, 0x00}; /* DTYPE_DCS_READ */

static struct dsi_cmd_desc himax_ReadDA = {
	DTYPE_DCS_READ, 1, 0, 1, 20, sizeof(himax_manufacture_idDA), himax_manufacture_idDA};
static struct dsi_cmd_desc himax_ReadDB = {
	DTYPE_DCS_READ, 1, 0, 1, 20, sizeof(himax_manufacture_idDB), himax_manufacture_idDB};
static struct dsi_cmd_desc himax_ReadDC = {
	DTYPE_DCS_READ, 1, 0, 1, 20, sizeof(himax_manufacture_idDC), himax_manufacture_idDC};
static struct dsi_cmd_desc himax_Read0A = {
	DTYPE_DCS_READ, 1, 0, 1, 20, sizeof(himax_manufacture_id0A), himax_manufacture_id0A};

/* FIH-SW-MM-VH-DISPLAY-40*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_AUO_LCM_HEALTHY_CHECK
static char himax_manufacture_C1[2] = {0xC1, 0x00}; /* DTYPE_DCS_READ */
static struct dsi_cmd_desc himax_ReadC1 = {
	DTYPE_DCS_READ, 1, 0, 1, 20, sizeof(himax_manufacture_C1), himax_manufacture_C1};
#endif
/* FIH-SW-MM-VH-DISPLAY-40*] */
/* FIH-SW-MM-VH-DISPLAY-21*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
static char himax_WriteCABCMode[2] = {0x55, 0x00};  /* DTYPE_DCS_WRITE1 */
static char himax_WriteCABCMinBrightness[2] = {0x5E, 0x00};  /* DTYPE_DCS_WRITE1 */
#endif
#ifdef CONFIG_FIH_SW_DISPLAY_CABC_TOOLBOX
static char himax_ReadCABCMode[2] = {0x56, 0x00}; /* DTYPE_DCS_READ */
static char himax_ReadCABCMinBrightness[2] = {0x5F, 0x00};  /* DTYPE_DCS_WRITE1 */
static char himax_WriteCABCBrightness[2] = {0x51, 0x00};  /* DTYPE_DCS_WRITE1 */
static char himax_ReadCABCBrightness[2] = {0x52, 0x00};  /* DTYPE_DCS_WRITE1 */
/* FIH-SW-MM-VH-DISPLAY-21*] */
static char set_tear_on[2] = {0x35, 0x00};
static struct dsi_cmd_desc dsi_tear_on_cmd = {	DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(set_tear_on), set_tear_on};
static char set_tear_off[2] = {0x34, 0x00};
static struct dsi_cmd_desc dsi_tear_off_cmd = {	DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(set_tear_off), set_tear_off};
#endif
/* FIH-SW-MM-VH-DISPLAY-28*[ */
/* FIH-SW-MM-VH-DISPLAY-33*[ */
static char set_tear_on[2] = {0x35, 0x00};
static char auo_unlock_cmd2[3] = {0xED, 0x01, 0xFE}; /* DTYPE_GEN_LWRITE */
static char auo_inversion[2] = {0xB4, 0x15};  /* DTYPE_GEN_WRITE1 */
static char himax_B7[2] = {0xB7, 0x20};  /* DTYPE_GEN_WRITE1 */
static char auo_pump[4] = {0xC2, 0x24, 0x24, 0x24};  /* DTYPE_GEN_LWRITE */
static char auo_pump_clamp[5] = {0xC6, 0x00, 0xE4, 0xE4, 0xE4};  /* DTYPE_GEN_LWRITE */
static char auo_cmd2_p1[2] = {0xBF, 0xAA}; /* DTYPE_GEN_WRITE1 */
static char AUO_PWM[5] = {0xC1, 0x20, 0x00, 0x01, 0x00}; /* DTYPE_GEN_LWRITE1 */
static char himax_CMD_RET[2] = {0x00, 0xAA}; /* DTYPE_GEN_WRITE1 */
/* FIH-SW-MM-VH-DISPLAY-40*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_AUO_LCM_HEALTHY_CHECK
static struct dsi_cmd_desc auo_cmd2_p1_cmd = {
	DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(auo_cmd2_p1), auo_cmd2_p1};
static struct dsi_cmd_desc auo_cmd_ret_cmd = {
	DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_CMD_RET), himax_CMD_RET};
#endif
/* FIH-SW-MM-VH-DISPLAY-40*] */
static char auo_red_positive_gamma[37] = {0xE0, 
	0x07, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xF3, 0x00
};  /* DTYPE_GEN_LWRITE */
static char auo_red_negative_gamma[37] = {0xE1, 
	0x02, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xEE, 0x00
};  /* DTYPE_GEN_LWRITE */
static char auo_green_positive_gamma[37] = {0xE2, 
	0x07, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xF3, 0x00
};  /* DTYPE_GEN_LWRITE */
static char auo_green_negative_gamma[37] = {0xE3, 
	0x02, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xEE, 0x00
};  /* DTYPE_GEN_LWRITE */
static char auo_blue_positive_gamma[37] = {0xE4, 
	0x07, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xF3, 0x00
};  /* DTYPE_GEN_LWRITE */
static char auo_blue_negative_gamma[37] = {0xE5, 
	0x02, 0x00,
	0x13, 0x00, 
	0x1D, 0x00, 
	0x2B, 0x00,
	0x34, 0x00,
	0x3D, 0x00,
	0x49, 0x00,
	0x5A, 0x00,
	0x68, 0x00,
	0x72, 0x00,
	0x7C, 0x00,
	0x85, 0x00,
	0x8C, 0x00,
	0x91, 0x00,
	0x9A, 0x00,
	0xA7, 0x00,
	0xBE, 0x00,
	0xEE, 0x00
};  /* DTYPE_GEN_LWRITE */
/* FIH-SW-MM-VH-DISPLAY-33*] */
static struct dsi_cmd_desc himax_CMI_on_cmds[] = {
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_EnableExtensionCommand), himax_EnableExtensionCommand},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(himax_SleepIn), himax_SleepIn},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_Gamma), himax_Gamma},
	{DTYPE_DCS_WRITE, 1, 0, 0, 125,
		sizeof(himax_SleepOut), himax_SleepOut},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(himax_InterfacePixelFormat), himax_InterfacePixelFormat},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(himax_PanelSetting), himax_PanelSetting}, 
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_SETBGP), himax_SETBGP},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_SetPowerControl), himax_SetPowerControl},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_SetDisplayCycleRegister), himax_SetDisplayCycleRegister},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_SETSTBA), himax_SETSTBA}, 
	/* FIH-SW-MM-VH-DISPLAY-05+ */
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(himax_MIPIDSISettings), himax_MIPIDSISettings},
/* FIH-SW-MM-VH-DISPLAY-15-[ */
//	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
//		sizeof(himax_setVCOM), himax_setVCOM},
/* FIH-SW-MM-VH-DISPLAY-15-] */
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(himax_ColumnAddress), himax_ColumnAddress},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(himax_PageAddress), himax_PageAddress},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(CMI_PWM), CMI_PWM},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(himax_DisplayON), himax_DisplayON},
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(himax_WriteCABCMode), himax_WriteCABCMode},
#endif
#ifndef CONFIG_FIH_SW_DISPLAY_BACKLIGHT_CMD_QUEUE
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness},
#endif
};
/* FIH-SW-MM-VH-DISPLAY-09*] */
/* FIH-SW-MM-VH-DISPLAY-33*[ */
static struct dsi_cmd_desc himax_AUO_0B_on_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 125,
		sizeof(himax_SleepOut), himax_SleepOut},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(set_tear_on), set_tear_on},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_unlock_cmd2), auo_unlock_cmd2},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(auo_inversion), auo_inversion},	
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(himax_B7), himax_B7},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_pump), auo_pump},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_pump_clamp), auo_pump_clamp},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(auo_cmd2_p1), auo_cmd2_p1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_red_positive_gamma), auo_red_positive_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_red_negative_gamma), auo_red_negative_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_green_positive_gamma), auo_green_positive_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_green_negative_gamma), auo_green_negative_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_blue_positive_gamma), auo_blue_positive_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_blue_negative_gamma), auo_blue_negative_gamma},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(AUO_PWM), AUO_PWM},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 120,
		sizeof(himax_CMD_RET), himax_CMD_RET},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(himax_DisplayON), himax_DisplayON},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
#ifndef CONFIG_FIH_SW_DISPLAY_BACKLIGHT_CMD_QUEUE
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness},
#endif
};
static struct dsi_cmd_desc himax_AUO_0D_on_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 125,
		sizeof(himax_SleepOut), himax_SleepOut},
	{DTYPE_DCS_WRITE, 1, 0, 0, 0,
		sizeof(set_tear_on), set_tear_on},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_unlock_cmd2), auo_unlock_cmd2},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(auo_inversion), auo_inversion},	
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(himax_B7), himax_B7},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_pump), auo_pump},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(auo_pump_clamp), auo_pump_clamp},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(auo_cmd2_p1), auo_cmd2_p1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0,
		sizeof(AUO_PWM), AUO_PWM},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 120,
		sizeof(himax_CMD_RET), himax_CMD_RET},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(himax_DisplayON), himax_DisplayON},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
#ifndef CONFIG_FIH_SW_DISPLAY_BACKLIGHT_CMD_QUEUE
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness},
#endif
};
static struct dsi_cmd_desc himax_CMI_off_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off}
};
static struct dsi_cmd_desc himax_AUO_off_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 1, 0, 0, 50,
		sizeof(himax_SleepIn), himax_SleepIn}
};
/* FIH-SW-MM-VH-DISPLAY-33*] */
/* FIH-SW-MM-VH-DISPLAY-28*] */

/* FIH-SW-MM-VH-DISPLAY-21+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
static struct dsi_cmd_desc himax_write_DD1[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD1), write_ctrl_displayDD1},
};
static struct dsi_cmd_desc himax_write_DD0[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_ctrl_displayDD0), write_ctrl_displayDD0},
};
#endif
/* FIH-SW-MM-VH-DISPLAY-21+] */

static struct dsi_cmd_desc himax_video_bkl_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness}
};
/* FIH-SW-MM-VH-DISPLAY-21*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
static struct dsi_cmd_desc himax_write_cabc_mode_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(himax_WriteCABCMode), himax_WriteCABCMode}
	
};
static struct dsi_cmd_desc himax_write_cabc_min_brightness_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(himax_WriteCABCMinBrightness), himax_WriteCABCMinBrightness}
};

#endif
#ifdef CONFIG_FIH_SW_DISPLAY_CABC_TOOLBOX
static struct dsi_cmd_desc himax_read_cabc_mode_cmds = {
	DTYPE_GEN_READ, 1, 0, 1, 5, 
		sizeof(himax_ReadCABCMode), himax_ReadCABCMode
};

static struct dsi_cmd_desc himax_read_cabc_min_brightness_cmds = {
	DTYPE_GEN_READ, 1, 0, 1, 5, 
		sizeof(himax_ReadCABCMinBrightness),himax_ReadCABCMinBrightness
};
/* FIH-SW-MM-VH-DISPLAY-21*] */
static struct dsi_cmd_desc himax_read_cabc_brightness_cmds = {
	DTYPE_GEN_READ, 1, 0, 1, 5, 
		sizeof(himax_ReadCABCBrightness),himax_ReadCABCBrightness
};

static struct dsi_cmd_desc himax_write_cabc_brightness_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(himax_WriteCABCBrightness), himax_WriteCABCBrightness}
};
#endif
/* FIH-SW-MM-VH-DISPLAY-40*[ */
static int mipi_himax_manufacture_id(struct msm_fb_data_type *mfd)
{
	struct dsi_buf *rp, *tp;
	int retVal = 0;
	char retDA = 0, retDB = 0, retDC = 0, ret0A = 0;
	tp = &himax_tx_buf;
	rp = &himax_rx_buf;

	/* TODO: Enter critical here cause deadlock?*/
	mipi_set_tx_power_mode(1);

	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);
	retVal |= mipi_dsi_cmds_rx(mfd, tp, rp, &himax_ReadDA, 1);
	retDA = *((char *) rp->data);

	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);
	retVal |= mipi_dsi_cmds_rx(mfd, tp, rp, &himax_ReadDB, 1);
	retDB = *((char *) rp->data);

	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);
	retVal |= mipi_dsi_cmds_rx(mfd, tp, rp, &himax_ReadDC, 1);
	retDC = *((char *) rp->data);
	
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);
	retVal |= mipi_dsi_cmds_rx(mfd, tp, rp, &himax_Read0A, 1);
	ret0A = *((char *) rp->data);

	if(retVal >= 0) {
		switch(retDA)
		{
			case LCM_ID_DA_MES_CMI_DP:
			case LCM_ID_DA_MES_AUO_0B:
			case LCM_ID_DA_MES_AUO_0D:
			case LCM_ID_DA_MES_CMI_TP:
				retVal = (unsigned int) retDA;
				break;
			default:
				if (retDB  == LCM_ID_DB_MES_AUO){
					retVal = (unsigned int) LCM_ID_DA_MES_AUO_0B;
				}else if(((ret0A & 0x03) == 0x00)){
					retVal = (unsigned int) retDA;
				}else{
					retVal = -1;
				}
			break;
		}
	}else{
		retVal = -1;
	}

	printk(KERN_ALERT "[DISPLAY] Panel ID = 0x%02x, 0x%02x, 0x%02x, 0x0A = 0x%02x, retVal = 0x%X\r\n", retDA, retDB, retDC, ret0A, retVal);
	return retVal;
}

#ifdef CONFIG_FIH_SW_DISPLAY_AUO_LCM_HEALTHY_CHECK
static int mipi_himax_get_healthy(struct msm_fb_data_type *mfd)
{
	struct dsi_buf *rp, *tp;
	int retVal = 0;
	char *pretTMP = NULL;
	tp = &himax_tx_buf;
	rp = &himax_rx_buf;

	/* TODO: Enter critical here cause deadlock?*/
	mipi_set_tx_power_mode(1);

	/* Switch to page2*/
	mipi_dsi_cmds_tx(mfd, &himax_tx_buf, &auo_cmd2_p1_cmd, 1);
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);
	mipi_dsi_cmds_rx(mfd, tp, rp, &himax_ReadC1, 6);
	pretTMP = ((char *) rp->data);
	if((*(pretTMP+2)) != 0x01){
		printk("[DISPLAY] ERROR: LCM failed\r\n");
		printk("[DISPLAY] 0xC1 = 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\r\n", *pretTMP, *(pretTMP+1), *(pretTMP+2), *(pretTMP+3), *(pretTMP+4), *(pretTMP+5));
		retVal = -EPERM;
	}

	/* Return from page2*/
	mipi_dsi_cmds_tx(mfd, &himax_tx_buf, &auo_cmd_ret_cmd, 1);

	return retVal;
}
#endif
/* FIH-SW-MM-VH-DISPLAY-40*] */

static ssize_t himax_read_da(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_ReadDA, 1);
	retData = *((char *) rp->data);

	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	printk(KERN_ALERT "%s: %x\r\n", __func__, retData);    
	return retVal;

}
static ssize_t himax_read_db(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_ReadDB, 1);
	retData = *((char *) rp->data);


	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	printk(KERN_ALERT "%s: %x\r\n", __func__, retData);   
		return retVal;

}
static ssize_t himax_read_dc(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_ReadDC, 1);
	retData = *((char *) rp->data);

	
	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	printk(KERN_ALERT "%s: %x\r\n", __func__, retData);    

	return retVal;
}

static ssize_t himax_read_0A(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_Read0A, 1);
	retData = *((char *) rp->data);

	
	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	printk(KERN_ALERT "%s: %x\r\n", __func__, retData);    

	return retVal;
}


static DEVICE_ATTR(idDA, S_IRUGO, himax_read_da, NULL);
static DEVICE_ATTR(idDB, S_IRUGO, himax_read_db, NULL);
static DEVICE_ATTR(idDC, S_IRUGO, himax_read_dc, NULL);
static DEVICE_ATTR(id0A, S_IRUGO, himax_read_0A, NULL);
/* FIH-SW-MM-VH-DISPLAY-09*] */
/* FIH-SW-MM-VH-DISPLAY-40*[ */
static int mipi_himax_lcd_on(struct platform_device *pdev)
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

	if (display_initialize)
		return 0;

	mipi = &mfd->panel_info.mipi;

	gmfd = mfd;
	rc = mipi_himax_manufacture_id(mfd);

	if(rc >= 0){
		mfd->panel_info.lcm_model = rc;

		/*TODO: Is it necessary to enter critical section? */
		if(mfd->panel_info.lcm_model == LCM_ID_DA_MES_AUO_0B) {
			rc = mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_AUO_0B_on_cmds,
				ARRAY_SIZE(himax_AUO_0B_on_cmds));
		}else if(mfd->panel_info.lcm_model == LCM_ID_DA_MES_AUO_0D){
			rc = mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_AUO_0D_on_cmds,
				ARRAY_SIZE(himax_AUO_0D_on_cmds));
		}else{
			rc = mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_CMI_on_cmds,
				ARRAY_SIZE(himax_CMI_on_cmds));
		}

		printk(KERN_ALERT "[DISPLAY] Finish sending dsi commands\n, rc=%d\r\n", rc);
		
#ifdef CONFIG_FIH_SW_DISPLAY_CMI_LCM_HEALTHY_CHECK
		if (rc >= 0){
			rc = mipi_himax_manufacture_id(mfd);
		}
#endif
	
		if(rc >= 0){
			rc = 0;
			display_initialize = 1;
		}
	}
	
	printk("[DISPLAY]%s: rc = %d\r\n", __func__, rc);
	return rc;
}

static int mipi_himax_lcd_off(struct platform_device *pdev)
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

	if((mfd->panel_info.lcm_model == LCM_ID_DA_MES_AUO_0B) || (mfd->panel_info.lcm_model == LCM_ID_DA_MES_AUO_0D)) {
		mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_AUO_off_cmds,
		ARRAY_SIZE(himax_AUO_off_cmds));
	} else {
		mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_CMI_off_cmds,
		ARRAY_SIZE(himax_CMI_off_cmds));
	}

	mipi_set_tx_power_mode(1);

	display_initialize = 0;

	return 0;
}
/* FIH-SW-MM-VH-DISPLAY-40*] */
/* FIH-SW-MM-VH-DISPLAY-09*[ */
static void mipi_himax_lcd_backlight(struct msm_fb_data_type *mfd)
{
	struct mipi_panel_info *mipi;
	
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
	int brightnessTmp = 0;
#endif

	mipi = &mfd->panel_info.mipi;

	printk(KERN_ALERT "[DISPLAY] Enter %s, set backlight level to %d\n",
			__func__, mfd->bl_level);

	if (!display_initialize)
		return;

	/* Duty_Cycle */
	write_display_brightness[1] = BKL_PWM[mfd->bl_level];

	down(&mfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, &himax_tx_buf, himax_video_bkl_cmds,
			ARRAY_SIZE(himax_video_bkl_cmds));
	mipi_set_tx_power_mode(1);
	up(&mfd->dma->mutex);

#ifdef CONFIG_FIH_SW_DISPLAY_CABC
	brightnessTmp = mfd->bl_level - gDeltaMinBrightness;

	if(brightnessTmp <0)
		gMinBrightness = 0;
	else
		gMinBrightness = brightnessTmp;

	
	himax_WriteCABCMinBrightness[1] = BKL_PWM[gMinBrightness];
	printk("[DISPLAY] mfd->bl_level = %d, gMinBrightness = %d\r\n", mfd->bl_level, gMinBrightness);
	printk("[DISPLAY] himax_WriteCABCMinBrightness[1] = %d, BKL_PWM[gMinBrightness] = %d\r\n", himax_WriteCABCMinBrightness[1], BKL_PWM[gMinBrightness]);

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_min_brightness_cmds,
			ARRAY_SIZE(himax_write_cabc_min_brightness_cmds));
	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);
#endif
}

/* FIH-SW-MM-VH-DISPLAY-21+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
static int mipi_himax_set_dimming(char enable)
{
	printk(KERN_ALERT "[DISPLAY] %s(%d)\n",	__func__, enable);

	if (!display_initialize)
		return 0;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);

	if(enable) {
		mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_DD1,
				ARRAY_SIZE(himax_write_DD1));
	}else{
		mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_DD0,
				ARRAY_SIZE(himax_write_DD0));
	}

	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);
	
	return 0;
}
#endif
/* FIH-SW-MM-VH-DISPLAY-21+] */

#ifdef CONFIG_FIH_SW_DISPLAY_CABC
/* FIH-SW-MM-VH-DISPLAY-18+[ */
static int mipi_himax_set_cabc_mode(char mode)
{
		printk(KERN_ALERT "[DISPLAY] Enter %s, set cabc mode to %d\n",
			__func__, mode);

	if (!display_initialize)
		return 0;

	himax_WriteCABCMode[1] =mode;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_mode_cmds,
			ARRAY_SIZE(himax_write_cabc_mode_cmds));
	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);

	return 0;
}
/* FIH-SW-MM-VH-DISPLAY-18+] */
/* FIH-SW-MM-VH-DISPLAY-21+[ */
#endif
#ifdef CONFIG_FIH_SW_DISPLAY_CABC_TOOLBOX
/* FIH-SW-MM-VH-DISPLAY-21+] */
static ssize_t himax_read_cabc_mode(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_off_cmd, 1);	
	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_read_cabc_mode_cmds, 1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_on_cmd, 1);
	up(&gmfd->dma->mutex);

	retData = *((char *) rp->data);
	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	printk(KERN_ALERT "-%s: %x\r\n", __func__, retData);

	return retVal;
}

static ssize_t himax_write_cabc_mode(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = strnlen(buf, PAGE_SIZE);
	int cmd;

	if ((!display_initialize) || (gmfd == NULL))
	return -1;

	sscanf(buf, "%x", &cmd);
	himax_WriteCABCMode[1] = cmd;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_mode_cmds,
			ARRAY_SIZE(himax_write_cabc_mode_cmds));
	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);
	
	printk(KERN_ALERT "-%s: %x\r\n", __func__ , cmd);

	return ret;
}

static ssize_t himax_read_cabc_min_brightness(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_off_cmd, 1);	
	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_read_cabc_min_brightness_cmds, 1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_on_cmd, 1);
	up(&gmfd->dma->mutex);

	retData = *((char *) rp->data);
	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	
	printk(KERN_ALERT "-%s: %x\r\n", __func__, retData);

	return retVal;
}

static ssize_t himax_write_cabc_min_brightness(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = strnlen(buf, PAGE_SIZE);
	int cmd;

	if ((!display_initialize) || (gmfd == NULL))
    	return -1;
        
	sscanf(buf, "%x", &cmd);
	himax_WriteCABCMinBrightness[1] = cmd;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_min_brightness_cmds,
			ARRAY_SIZE(himax_write_cabc_min_brightness_cmds));
	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);

	printk(KERN_ALERT "-%s: %x\r\n", __func__ , cmd);

	return ret;
}

static ssize_t himax_read_cabc_brightness(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;
	char retData = 0;
	struct dsi_buf *rp, *tp;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	tp = &himax_tx_buf;
	rp = &himax_rx_buf;
	
	mipi_dsi_buf_init(rp);
	mipi_dsi_buf_init(tp);

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_off_cmd, 1);	
	retVal = mipi_dsi_cmds_rx(gmfd, tp, rp, &himax_read_cabc_brightness_cmds, 1);
	mipi_dsi_cmds_tx(gmfd, tp, &dsi_tear_on_cmd, 1);
	up(&gmfd->dma->mutex);

	retData = *((char *) rp->data);
	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", retData);
	
	printk(KERN_ALERT "%s: %x\r\n", __func__, retData);

	return retVal;
}

/* FIH-SW-MM-VH-DISPLAY-15*[ */
static ssize_t himax_write_cabc_brightness(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = strnlen(buf, PAGE_SIZE);
	int cmd;

	if ((!display_initialize) || (gmfd == NULL))
		return -1;

	sscanf(buf, "%x", &cmd);
	himax_WriteCABCBrightness[1] = cmd;

	down(&gmfd->dma->mutex);
	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_brightness_cmds,
			ARRAY_SIZE(himax_write_cabc_brightness_cmds));
	mipi_set_tx_power_mode(1);
	up(&gmfd->dma->mutex);

	printk(KERN_ALERT "%s: %x\r\n", __func__ , cmd);

	return ret;
}
/* FIH-SW-MM-VH-DISPLAY-15*] */
static ssize_t himax_read_gDeltaMinBrightness(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;

	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", gDeltaMinBrightness);
	
	printk(KERN_ALERT "%s: %x\r\n", __func__, gDeltaMinBrightness);

	return retVal;
}

static ssize_t himax_write_gDeltaMinBrightness(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = strnlen(buf, PAGE_SIZE);
	int cmd;

	sscanf(buf, "%x", &cmd);
	gDeltaMinBrightness = cmd;


	printk(KERN_ALERT "%s: %x\r\n", __func__ , cmd);

	return ret;
}
static ssize_t himax_read_gMinBrightness(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int retVal = 0;

	retVal = snprintf(buf, PAGE_SIZE, "0x%02x\n", gMinBrightness);
	
	printk(KERN_ALERT "%s: %x\r\n", __func__, gDeltaMinBrightness);

	return retVal;
}

static ssize_t himax_write_gMinBrightness(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = strnlen(buf, PAGE_SIZE);
	int cmd;

	sscanf(buf, "%x", &cmd);
	gMinBrightness = cmd;


	printk(KERN_ALERT "%s: %x\r\n", __func__ , cmd);

	return ret;
}
/* FIH-SW-MM-VH-DISPLAY-15+[ */
static ssize_t himax_flicker_write(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
	struct fb_info *fbi = dev_get_drvdata(dev);
	struct msm_fb_data_type *mfd = NULL;
	struct msm_fb_panel_data *pdata = NULL;
	char *tok, str[80], *tmp;
	int interval = 0;
    int command = 0;

	mfd = (struct msm_fb_data_type *)fbi->par;
	pdata = (struct msm_fb_panel_data *)mfd->pdev->dev.platform_data;

	printk(KERN_ERR "[DISPLAY] +%s\n", __func__);

	strncpy(str, buf, 80);
	tmp = str;
	tok = strsep(&tmp, " ,.");

	if(tok == NULL)
		return -1;
	
	/* Use %3d to limit size to avoid overflow */
	sscanf(tok, "%3d", &interval);

	printk(KERN_ERR "[DISPLAY] INTERVAL = %d\n", interval);
	while(1) {
		tok = strsep(&tmp, " ,.");
		if(tok == NULL)
			break;

		/* Use %3d to limit size to avoid overflow */
		sscanf(tok, "%x", &command);

		himax_WriteCABCBrightness[1] = command;
		
		down(&gmfd->dma->mutex);
		mipi_set_tx_power_mode(0);
		mipi_dsi_cmds_tx(gmfd, &himax_tx_buf, himax_write_cabc_brightness_cmds,
				ARRAY_SIZE(himax_write_cabc_brightness_cmds));
		mipi_set_tx_power_mode(1);
		up(&gmfd->dma->mutex);

		hr_msleep(interval);
	}
	
    return size;
}
static DEVICE_ATTR(CABCFlicker, 0644, NULL, himax_flicker_write);
/* FIH-SW-MM-VH-DISPLAY-15+] */
static DEVICE_ATTR(CABCMode, 0600, himax_read_cabc_mode,
	himax_write_cabc_mode);
static DEVICE_ATTR(CABCMinBrightness, 0600, himax_read_cabc_min_brightness,
	himax_write_cabc_min_brightness); 
static DEVICE_ATTR(CABCBrightness, 0600, himax_read_cabc_brightness,
	himax_write_cabc_brightness); 
static DEVICE_ATTR(CABCgMinBrightness,0600, himax_read_gMinBrightness,
	himax_write_gMinBrightness); 
static DEVICE_ATTR(CABCgDeltaMinBrightness, 0600, himax_read_gDeltaMinBrightness,
	himax_write_gDeltaMinBrightness); 

#endif

static int __devinit mipi_himax_lcd_probe(struct platform_device *pdev)
{
	int retVal = 0;
	
	printk(KERN_ALERT "[DISPLAY] +%s\n", __func__);

	if (pdev->id == 0) {
		mipi_himax_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);
	/* FIH-SW-MM-VH-DISPLAY-21* */
	#ifdef CONFIG_FIH_SW_DISPLAY_CABC_TOOLBOX
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCMode);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: ddev_attr_cabc_mode failed\n", __func__);
	}  
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCMinBrightness);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: dev_attr_cabc_min_brightness failed\n", __func__);
	}
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCBrightness);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: dev_attr_cabc_min_brightness failed\n", __func__);
	}
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCgMinBrightness);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: dev_attr_cabc_min_brightness failed\n", __func__);
	}
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCgDeltaMinBrightness);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: dev_attr_cabc_min_brightness failed\n", __func__);
	}
	/* FIH-SW-MM-VH-DISPLAY-15+[ */
	retVal = device_create_file(&pdev->dev, &dev_attr_CABCFlicker);
	if (retVal) {
		dev_err(&pdev->dev,
			"%s: dev_attr_CABCFlicker failed\n", __func__);
	/* FIH-SW-MM-VH-DISPLAY-15+] */
	}

	#endif
	retVal = device_create_file(&pdev->dev, &dev_attr_idDA);
	if (retVal) {
		dev_err(&pdev->dev,
				"%s: dev_attr_idDA failed\n", __func__);
	}  
	retVal = device_create_file(&pdev->dev, &dev_attr_idDB);
	if (retVal) {
		dev_err(&pdev->dev,
				"%s: dev_attr_idDB failed\n", __func__);
	}  
	retVal = device_create_file(&pdev->dev, &dev_attr_idDC);
	if (retVal) {
		dev_err(&pdev->dev,
				"%s: dev_attr_idDC failed\n", __func__);
	}  
	retVal = device_create_file(&pdev->dev, &dev_attr_id0A);
	if (retVal) {
		dev_err(&pdev->dev,
				"%s: dev_attr_idDC failed\n", __func__);
	}  
	printk(KERN_ALERT "[DISPLAY] -%s\n", __func__);
	return 0;
}

/* FIH-SW-MM-VH-DISPLAY-09*] */

static struct platform_driver this_driver = {
	.probe  = mipi_himax_lcd_probe,
	.driver = {
		.name   = "mipi_himax",
	},
};

static struct msm_fb_panel_data himax_panel_data = {
	.on		= mipi_himax_lcd_on,
	.off	= mipi_himax_lcd_off,
	.set_backlight = mipi_himax_lcd_backlight,
/* FIH-SW-MM-VH-DISPLAY-18+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
	.set_cabc_mode = mipi_himax_set_cabc_mode,
#endif
/* FIH-SW-MM-VH-DISPLAY-18+] */
/* FIH-SW-MM-VH-DISPLAY-21+[ */
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_DIMMING
	.set_dimming = mipi_himax_set_dimming,
#endif
/* FIH-SW-MM-VH-DISPLAY-40*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_AUO_LCM_HEALTHY_CHECK
	.get_healthy = mipi_himax_get_healthy,

#endif
#ifdef CONFIG_FIH_SW_DISPLAY_LCM_ID_CHECK
.get_id = mipi_himax_manufacture_id,
#endif
/* FIH-SW-MM-VH-DISPLAY-40*] */
/* FIH-SW-MM-VH-DISPLAY-21+] */

};

static int ch_used[3];

int mipi_himax_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	pdev = platform_device_alloc("mipi_himax", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	himax_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &himax_panel_data,
		sizeof(himax_panel_data));
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

static int __init mipi_himax_lcd_init(void)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	mipi_dsi_buf_alloc(&himax_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&himax_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}

module_init(mipi_himax_lcd_init);
