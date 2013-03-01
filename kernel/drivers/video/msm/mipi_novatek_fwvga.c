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
#include "mipi_novatek_fwvga.h"
#include <mach/vreg.h>
#include <linux/gpio.h>

static struct msm_panel_common_pdata *mipi_novatek_fwvga_pdata;

static struct dsi_buf novatek_fwvga_tx_buf;
static struct dsi_buf novatek_fwvga_rx_buf;

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

/* novatek fwvga panel */
static char cmd2_unlock[2] = {0xF3, 0xAA}; /* DTYPE_GEN_WRITE1 */
static char cmd2_page0[2] = {0x00, 0x00}; /* DTYPE_GEN_WRITE1 */
static char cmd2_page1[2] = {0x00, 0x01}; /* DTYPE_GEN_WRITE1 */
static char cmd2_page0_lock[2] = {0xFF, 0xAA}; /* DTYPE_GEN_WRITE1 */
static char cmd2_page1_lock[2] = {0x7F, 0xAA}; /* DTYPE_GEN_WRITE1 */
static char register_C980[2] = {0xC9, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_7DC0[2] = {0x7D, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_0180[2] = {0x01, 0x14}; /* DTYPE_GEN_WRITE1 */
static char register_0280[2] = {0x02, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_0380[2] = {0x03, 0x33}; /* DTYPE_GEN_WRITE1 */
static char register_0480[2] = {0x04, 0x48}; /* DTYPE_GEN_WRITE1 */
static char register_0780[2] = {0x07, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_0880[2] = {0x08, 0x44}; /* DTYPE_GEN_WRITE1 */
static char register_0980[2] = {0x09, 0x54}; /* DTYPE_GEN_WRITE1 */
static char register_0A80[2] = {0x0A, 0x12}; /* DTYPE_GEN_WRITE1 */
static char register_1280[2] = {0x12, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_1380[2] = {0x13, 0x10}; /* DTYPE_GEN_WRITE1 */
static char register_1480[2] = {0x14, 0x0D}; /* DTYPE_GEN_WRITE1 */
static char register_1580[2] = {0x15, 0xA0}; /* DTYPE_GEN_WRITE1 */
static char register_1A80[2] = {0x1A, 0x67}; /* DTYPE_GEN_WRITE1 */
static char register_1F80[2] = {0x1F, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_2080[2] = {0x20, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_2180[2] = {0x21, 0x63}; /* DTYPE_GEN_WRITE1 */
static char register_2480[2] = {0x24, 0x09}; /* DTYPE_GEN_WRITE1 */
static char register_2580[2] = {0x25, 0x28}; /* DTYPE_GEN_WRITE1 */
static char register_2680[2] = {0x26, 0x4D}; /* DTYPE_GEN_WRITE1 */
static char register_2780[2] = {0x27, 0x66}; /* DTYPE_GEN_WRITE1 */
static char register_2880[2] = {0x28, 0x1E}; /* DTYPE_GEN_WRITE1 */
static char register_2980[2] = {0x29, 0x36}; /* DTYPE_GEN_WRITE1 */
static char register_2A80[2] = {0x2A, 0x64}; /* DTYPE_GEN_WRITE1 */
static char register_2B80[2] = {0x2B, 0x7C}; /* DTYPE_GEN_WRITE1 */
static char register_2D80[2] = {0x2D, 0x21}; /* DTYPE_GEN_WRITE1 */
static char register_2F80[2] = {0x2F, 0x29}; /* DTYPE_GEN_WRITE1 */
static char register_3080[2] = {0x30, 0xB6}; /* DTYPE_GEN_WRITE1 */
static char register_3180[2] = {0x31, 0x1A}; /* DTYPE_GEN_WRITE1 */
static char register_3280[2] = {0x32, 0x38}; /* DTYPE_GEN_WRITE1 */
static char register_3380[2] = {0x33, 0x4D}; /* DTYPE_GEN_WRITE1 */
static char register_3480[2] = {0x34, 0x96}; /* DTYPE_GEN_WRITE1 */
static char register_3580[2] = {0x35, 0xB8}; /* DTYPE_GEN_WRITE1 */
static char register_3680[2] = {0x36, 0xD9}; /* DTYPE_GEN_WRITE1 */
static char register_3780[2] = {0x37, 0x76}; /* DTYPE_GEN_WRITE1 */
static char register_3880[2] = {0x38, 0x09}; /* DTYPE_GEN_WRITE1 */
static char register_3980[2] = {0x39, 0x26}; /* DTYPE_GEN_WRITE1 */
static char register_3A80[2] = {0x3A, 0x47}; /* DTYPE_GEN_WRITE1 */
static char register_3B80[2] = {0x3B, 0x69}; /* DTYPE_GEN_WRITE1 */
static char register_3D80[2] = {0x3D, 0x32}; /* DTYPE_GEN_WRITE1 */
static char register_3F80[2] = {0x3F, 0x47}; /* DTYPE_GEN_WRITE1 */
static char register_4080[2] = {0x40, 0x65}; /* DTYPE_GEN_WRITE1 */
static char register_4180[2] = {0x41, 0x49}; /* DTYPE_GEN_WRITE1 */
static char register_4280[2] = {0x42, 0x16}; /* DTYPE_GEN_WRITE1 */
static char register_4380[2] = {0x43, 0x1E}; /* DTYPE_GEN_WRITE1 */
static char register_4480[2] = {0x44, 0x83}; /* DTYPE_GEN_WRITE1 */
static char register_4580[2] = {0x45, 0x1B}; /* DTYPE_GEN_WRITE1 */
static char register_4680[2] = {0x46, 0x49}; /* DTYPE_GEN_WRITE1 */
static char register_4780[2] = {0x47, 0x61}; /* DTYPE_GEN_WRITE1 */
static char register_4880[2] = {0x48, 0x99}; /* DTYPE_GEN_WRITE1 */
static char register_4980[2] = {0x49, 0xB2}; /* DTYPE_GEN_WRITE1 */
static char register_4A80[2] = {0x4A, 0xD7}; /* DTYPE_GEN_WRITE1 */
static char register_4B80[2] = {0x4B, 0x76}; /* DTYPE_GEN_WRITE1 */
static char register_4C80[2] = {0x4C, 0x09}; /* DTYPE_GEN_WRITE1 */
static char register_4D80[2] = {0x4D, 0x28}; /* DTYPE_GEN_WRITE1 */
static char register_4E80[2] = {0x4E, 0x4D}; /* DTYPE_GEN_WRITE1 */
static char register_4F80[2] = {0x4F, 0x66}; /* DTYPE_GEN_WRITE1 */
static char register_5080[2] = {0x50, 0x1E}; /* DTYPE_GEN_WRITE1 */
static char register_5180[2] = {0x51, 0x36}; /* DTYPE_GEN_WRITE1 */
static char register_5280[2] = {0x52, 0x64}; /* DTYPE_GEN_WRITE1 */
static char register_5380[2] = {0x53, 0x85}; /* DTYPE_GEN_WRITE1 */
static char register_5480[2] = {0x54, 0x21}; /* DTYPE_GEN_WRITE1 */
static char register_5580[2] = {0x55, 0x29}; /* DTYPE_GEN_WRITE1 */
static char register_5680[2] = {0x56, 0xBB}; /* DTYPE_GEN_WRITE1 */
static char register_5780[2] = {0x57, 0x1D}; /* DTYPE_GEN_WRITE1 */
static char register_5880[2] = {0x58, 0x3E}; /* DTYPE_GEN_WRITE1 */
static char register_5980[2] = {0x59, 0x53}; /* DTYPE_GEN_WRITE1 */
static char register_5A80[2] = {0x5A, 0x94}; /* DTYPE_GEN_WRITE1 */
static char register_5B80[2] = {0x5B, 0xA9}; /* DTYPE_GEN_WRITE1 */
static char register_5C80[2] = {0x5C, 0xD0}; /* DTYPE_GEN_WRITE1 */
static char register_5D80[2] = {0x5D, 0x76}; /* DTYPE_GEN_WRITE1 */
static char register_5E80[2] = {0x5E, 0x09}; /* DTYPE_GEN_WRITE1 */
static char register_5F80[2] = {0x5F, 0x2F}; /* DTYPE_GEN_WRITE1 */
static char register_6080[2] = {0x60, 0x56}; /* DTYPE_GEN_WRITE1 */
static char register_6180[2] = {0x61, 0x6B}; /* DTYPE_GEN_WRITE1 */
static char register_6280[2] = {0x62, 0x2C}; /* DTYPE_GEN_WRITE1 */
static char register_6380[2] = {0x63, 0x41}; /* DTYPE_GEN_WRITE1 */
static char register_6480[2] = {0x64, 0x62}; /* DTYPE_GEN_WRITE1 */
static char register_6580[2] = {0x65, 0x44}; /* DTYPE_GEN_WRITE1 */
static char register_6680[2] = {0x66, 0x16}; /* DTYPE_GEN_WRITE1 */
static char register_6780[2] = {0x67, 0x1E}; /* DTYPE_GEN_WRITE1 */
static char register_6880[2] = {0x68, 0x7A}; /* DTYPE_GEN_WRITE1 */
static char register_6980[2] = {0x69, 0x1B}; /* DTYPE_GEN_WRITE1 */
static char register_6A80[2] = {0x6A, 0x49}; /* DTYPE_GEN_WRITE1 */
static char register_6B80[2] = {0x6B, 0x61}; /* DTYPE_GEN_WRITE1 */
static char register_6C80[2] = {0x6C, 0x99}; /* DTYPE_GEN_WRITE1 */
static char register_6D80[2] = {0x6D, 0xB2}; /* DTYPE_GEN_WRITE1 */
static char register_6E80[2] = {0x6E, 0xD7}; /* DTYPE_GEN_WRITE1 */
static char register_6F80[2] = {0x6F, 0x76}; /* DTYPE_GEN_WRITE1 */
static char register_7080[2] = {0x70, 0x19}; /* DTYPE_GEN_WRITE1 */
static char register_7180[2] = {0x71, 0x28}; /* DTYPE_GEN_WRITE1 */
static char register_7280[2] = {0x72, 0x4D}; /* DTYPE_GEN_WRITE1 */
static char register_7380[2] = {0x73, 0x8E}; /* DTYPE_GEN_WRITE1 */
static char register_7480[2] = {0x74, 0x34}; /* DTYPE_GEN_WRITE1 */
static char register_7580[2] = {0x75, 0x45}; /* DTYPE_GEN_WRITE1 */
static char register_7680[2] = {0x76, 0x69}; /* DTYPE_GEN_WRITE1 */
static char register_7780[2] = {0x77, 0x9C}; /* DTYPE_GEN_WRITE1 */
static char register_7880[2] = {0x78, 0x21}; /* DTYPE_GEN_WRITE1 */
static char register_7980[2] = {0x79, 0x29}; /* DTYPE_GEN_WRITE1 */
static char register_7A80[2] = {0x7A, 0xC5}; /* DTYPE_GEN_WRITE1 */
static char register_7B80[2] = {0x7B, 0x18}; /* DTYPE_GEN_WRITE1 */
static char register_7C80[2] = {0x7C, 0x3A}; /* DTYPE_GEN_WRITE1 */
static char register_7D80[2] = {0x7D, 0x50}; /* DTYPE_GEN_WRITE1 */
static char register_7E80[2] = {0x7E, 0xA1}; /* DTYPE_GEN_WRITE1 */
static char register_7F80[2] = {0x7F, 0xC9}; /* DTYPE_GEN_WRITE1 */
static char register_8080[2] = {0x80, 0xD0}; /* DTYPE_GEN_WRITE1 */
static char register_8180[2] = {0x81, 0x76}; /* DTYPE_GEN_WRITE1 */
static char register_8280[2] = {0x82, 0x09}; /* DTYPE_GEN_WRITE1 */
static char register_8380[2] = {0x83, 0x2F}; /* DTYPE_GEN_WRITE1 */
static char register_8480[2] = {0x84, 0x36}; /* DTYPE_GEN_WRITE1 */
static char register_8580[2] = {0x85, 0x5E}; /* DTYPE_GEN_WRITE1 */
static char register_8680[2] = {0x86, 0x2F}; /* DTYPE_GEN_WRITE1 */
static char register_8780[2] = {0x87, 0x45}; /* DTYPE_GEN_WRITE1 */
static char register_8880[2] = {0x88, 0x67}; /* DTYPE_GEN_WRITE1 */
static char register_8980[2] = {0x89, 0x3A}; /* DTYPE_GEN_WRITE1 */
static char register_8A80[2] = {0x8A, 0x16}; /* DTYPE_GEN_WRITE1 */
static char register_8B80[2] = {0x8B, 0x1E}; /* DTYPE_GEN_WRITE1 */
static char register_8C80[2] = {0x8C, 0x63}; /* DTYPE_GEN_WRITE1 */
static char register_8D80[2] = {0x8D, 0x16}; /* DTYPE_GEN_WRITE1 */
static char register_8E80[2] = {0x8E, 0x3A}; /* DTYPE_GEN_WRITE1 */
static char register_8F80[2] = {0x8F, 0x4B}; /* DTYPE_GEN_WRITE1 */
static char register_9080[2] = {0x90, 0x71}; /* DTYPE_GEN_WRITE1 */
static char register_9180[2] = {0x91, 0xB2}; /* DTYPE_GEN_WRITE1 */
static char register_9280[2] = {0x92, 0xD7}; /* DTYPE_GEN_WRITE1 */
static char register_9380[2] = {0x93, 0x66}; /* DTYPE_GEN_WRITE1 */
static char register_9480[2] = {0x94, 0xBF}; /* DTYPE_GEN_WRITE1 */
static char register_9580[2] = {0x95, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_9680[2] = {0x96, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_9780[2] = {0x97, 0xB4}; /* DTYPE_GEN_WRITE1 */
static char register_9880[2] = {0x98, 0x0D}; /* DTYPE_GEN_WRITE1 */
static char register_9980[2] = {0x99, 0x2C}; /* DTYPE_GEN_WRITE1 */
static char register_9A80[2] = {0x9A, 0x0A}; /* DTYPE_GEN_WRITE1 */
static char register_9B80[2] = {0x9B, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_9C80[2] = {0x9C, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_9D80[2] = {0x9D, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_9E80[2] = {0x9E, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_9F80[2] = {0x9F, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_A080[2] = {0xA0, 0x0A}; /* DTYPE_GEN_WRITE1 */
static char register_A280[2] = {0xA2, 0x06}; /* DTYPE_GEN_WRITE1 */
static char register_A380[2] = {0xA3, 0x2E}; /* DTYPE_GEN_WRITE1 */
static char register_A480[2] = {0xA4, 0x0E}; /* DTYPE_GEN_WRITE1 */
static char register_A580[2] = {0xA5, 0xC0}; /* DTYPE_GEN_WRITE1 */
static char register_A680[2] = {0xA6, 0x01}; /* DTYPE_GEN_WRITE1 */
static char register_A780[2] = {0xA7, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_A980[2] = {0xA9, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_AA80[2] = {0xAA, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_E780[2] = {0xE7, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_ED80[2] = {0xED, 0x00}; /* DTYPE_GEN_WRITE1 */
static char register_F380[2] = {0xF3, 0xCC}; /* DTYPE_GEN_WRITE1 */
static char register_FB80[2] = {0xFB, 0x00}; /* DTYPE_GEN_WRITE1 */

static char enter_sleep[2] = {0x10, 0x00}; /* DTYPE_DCS_WRITE */
static char exit_sleep[2] = {0x11, 0x00}; /* DTYPE_DCS_WRITE */
static char display_off[2] = {0x28, 0x00}; /* DTYPE_DCS_WRITE */
static char display_on[2] = {0x29, 0x00}; /* DTYPE_DCS_WRITE */
static char set_tear_scanline[3] = {0x44, 0x00, 0x00}; /* DTYPE_DCS_LWRITE */
static char set_address_mode[2] = {0x36, 0xD4}; /* DTYPE_DCS_WRITE1 */
/* FIH-SW2-MM-NC-MIPI_TWO_LANE-00-[+ */
static char set_mipi_mddi[2] = {0xAE, 0x03}; /* DTYPE_DCS_WRITE1 */
/* FIH-SW2-MM-NC-MIPI_TWO_LANE-00-]- */
static char write_ctrl_display[2] = {0x53, 0x24}; /* DTYPE_DCS_WRITE1 */
static char write_display_brightness[2] = {0x51, 0xFF}; /* DTYPE_DCS_WRITE1 */  /* FIH-SW2-MM-NC-BKL_EN-00 */

static struct dsi_cmd_desc novatek_fwvga_video_on_cmds[] = {
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_unlock), cmd2_unlock},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page0), cmd2_page0},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_C980), register_C980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page0_lock), cmd2_page0_lock},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_unlock), cmd2_unlock},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page1), cmd2_page1},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7DC0), register_7DC0},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page1_lock), cmd2_page1_lock},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_unlock), cmd2_unlock},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page0), cmd2_page0},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0180), register_0180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0280), register_0280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0380), register_0380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0480), register_0480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0780), register_0780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0880), register_0880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0980), register_0980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_0A80), register_0A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1280), register_1280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1380), register_1380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1480), register_1480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1580), register_1580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1A80), register_1A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_1F80), register_1F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2080), register_2080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2180), register_2180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2480), register_2480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2580), register_2580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2680), register_2680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2780), register_2780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2880), register_2880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2980), register_2980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2A80), register_2A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2B80), register_2B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2D80), register_2D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_2F80), register_2F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3080), register_3080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3180), register_3180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3280), register_3280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3380), register_3380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3480), register_3480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3580), register_3580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3680), register_3680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3780), register_3780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3880), register_3880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3980), register_3980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3A80), register_3A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3B80), register_3B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3D80), register_3D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_3F80), register_3F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4080), register_4080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4180), register_4180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4280), register_4280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4380), register_4380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4480), register_4480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4580), register_4580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4680), register_4680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4780), register_4780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4880), register_4880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4980), register_4980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4A80), register_4A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4B80), register_4B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4C80), register_4C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4D80), register_4D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4E80), register_4E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_4F80), register_4F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5080), register_5080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5180), register_5180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5280), register_5280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5380), register_5380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5480), register_5480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5580), register_5580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5680), register_5680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5780), register_5780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5880), register_5880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5980), register_5980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5A80), register_5A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5B80), register_5B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5C80), register_5C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5D80), register_5D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5E80), register_5E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_5F80), register_5F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6080), register_6080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6180), register_6180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6280), register_6280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6380), register_6380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6480), register_6480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6580), register_6580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6680), register_6680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6780), register_6780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6880), register_6880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6980), register_6980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6A80), register_6A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6B80), register_6B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6C80), register_6C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6D80), register_6D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6E80), register_6E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_6F80), register_6F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7080), register_7080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7180), register_7180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7280), register_7280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7380), register_7380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7480), register_7480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7580), register_7580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7680), register_7680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7780), register_7780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7880), register_7880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7980), register_7980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7A80), register_7A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7B80), register_7B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7C80), register_7C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7D80), register_7D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7E80), register_7E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_7F80), register_7F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8080), register_8080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8180), register_8180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8280), register_8280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8380), register_8380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8480), register_8480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8580), register_8580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8680), register_8680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8780), register_8780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8880), register_8880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8980), register_8980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8A80), register_8A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8B80), register_8B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8C80), register_8C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8D80), register_8D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8E80), register_8E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_8F80), register_8F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9080), register_9080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9180), register_9180},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9280), register_9280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9380), register_9380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9480), register_9480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9580), register_9580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9680), register_9680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9780), register_9780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9880), register_9880},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9980), register_9980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9A80), register_9A80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9B80), register_9B80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9C80), register_9C80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9D80), register_9D80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9E80), register_9E80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_9F80), register_9F80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A080), register_A080},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A280), register_A280},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A380), register_A380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A480), register_A480},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A580), register_A580},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A680), register_A680},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A780), register_A780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_A980), register_A980},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_AA80), register_AA80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_E780), register_E780},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_ED80), register_ED80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_F380), register_F380},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(register_FB80), register_FB80},
	{DTYPE_GEN_WRITE1, 1, 0, 0, 0,
		sizeof(cmd2_page0_lock), cmd2_page0_lock},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(set_tear_scanline), set_tear_scanline},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(set_address_mode), set_address_mode},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(set_mipi_mddi), set_mipi_mddi},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 120,
        sizeof(write_ctrl_display), write_ctrl_display},
	{DTYPE_DCS_WRITE, 1, 0, 0, 120,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_on), display_on}
};

static struct dsi_cmd_desc novatek_fwvga_video_off_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 1, 0, 0, 120,
		sizeof(enter_sleep), enter_sleep}
};

static struct dsi_cmd_desc novatek_fwvga_video_bkl_cmds[] = {
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0,
		sizeof(write_display_brightness), write_display_brightness}
};

static int mipi_novatek_fwvga_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mfd = platform_get_drvdata(pdev);
	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	mipi = &mfd->panel_info.mipi;

	if (display_initialize)
		return 0;

	mdelay(120);
	mipi_dsi_cmds_tx(mfd, &novatek_fwvga_tx_buf, novatek_fwvga_video_on_cmds,
		ARRAY_SIZE(novatek_fwvga_video_on_cmds));
	printk(KERN_ALERT "[DISPLAY] Finish sending dsi commands\n");

	display_initialize = 1;

	return 0;
}

static int mipi_novatek_fwvga_lcd_off(struct platform_device *pdev)
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

	mipi_set_tx_power_mode(0);
	mipi_dsi_cmds_tx(mfd, &novatek_fwvga_tx_buf, novatek_fwvga_video_off_cmds,
			ARRAY_SIZE(novatek_fwvga_video_off_cmds));
	mipi_set_tx_power_mode(1);

	write_display_brightness[1] = 0xFF;  /* FIH-SW2-MM-NC-BKL_EN-00 */

	display_initialize = 0;

	return 0;
}

static void mipi_novatek_fwvga_lcd_backlight(struct msm_fb_data_type *mfd)
{
	struct mipi_panel_info *mipi;
	struct msm_panel_info *pinfo;

	mipi = &mfd->panel_info.mipi;
	pinfo = &mfd->panel_info;

	printk(KERN_ALERT "[DISPLAY] Enter %s, set backlight level to %d\n",
			__func__, mfd->bl_level);

	if ((bl_level_old == mfd->bl_level) || (!display_initialize))
		return;

	write_display_brightness[1] = BKL_PWM[mfd->bl_level];  /* Duty_Cycle */

	mipi_set_tx_power_mode(0);
	down(&mfd->dma->mutex);
	mipi_dsi_cmds_tx(mfd, &novatek_fwvga_tx_buf, novatek_fwvga_video_bkl_cmds,
			ARRAY_SIZE(novatek_fwvga_video_bkl_cmds));
	up(&mfd->dma->mutex);
	mipi_set_tx_power_mode(1);

	bl_level_old = mfd->bl_level;
}

static int __devinit mipi_novatek_fwvga_lcd_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	if (pdev->id == 0) {
		mipi_novatek_fwvga_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_novatek_fwvga_lcd_probe,
	.driver = {
		.name   = "mipi_novatek_fwvga",
	},
};

static struct msm_fb_panel_data novatek_fwvga_panel_data = {
	.on		= mipi_novatek_fwvga_lcd_on,
	.off	= mipi_novatek_fwvga_lcd_off,
	.set_backlight = mipi_novatek_fwvga_lcd_backlight,
};

static int ch_used[3];

int mipi_novatek_fwvga_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	pdev = platform_device_alloc("mipi_novatek_fwvga", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	novatek_fwvga_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &novatek_fwvga_panel_data,
		sizeof(novatek_fwvga_panel_data));
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

static int __init mipi_novatek_fwvga_lcd_init(void)
{
	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);
	mipi_dsi_buf_alloc(&novatek_fwvga_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&novatek_fwvga_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}

module_init(mipi_novatek_fwvga_lcd_init);
