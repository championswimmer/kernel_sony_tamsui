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

static struct msm_panel_info pinfo;

static struct mipi_dsi_phy_ctrl dsi_cmd_mode_phy_db = {
	/* DSI_BIT_CLK at 140MHz, 1 lane, RGB666 */
	{0x03, 0x01, 0x01, 0x00},	/* regulator */
	/* timing   */
/* FIH-SW3-MM-NC-LCM-03-[+ */
	{0x3C, 0x0f, 0x0f, 0x00, 0x1E, 0x1E, 0x14, 0x1E,
/* FIH-SW3-MM-NC-LCM-03-]- */
	0x13, 0x03, 0x04},
	{0x7f, 0x00, 0x00, 0x00},	/* phy ctrl */
	{0xee, 0x02, 0x86, 0x00},	/* strength */
	/* pll control */
	{0x41, 0x8f, 0xb1, 0xda, 0x00, 0x50, 0x48, 0x63,
	0x31, 0x0f, 0x0f,
	0x05, 0x14, 0x03, 0x03, 0x03, 0x54, 0x06, 0x10, 0x04, 0x03}
};

static int __init mipi_cmd_ilitek_hvga_pt_init(void)
{
	int ret;

	printk(KERN_ERR "[DISPLAY] Enter %s\n", __func__);
	pinfo.xres = 320;
	pinfo.yres = 480;
	pinfo.type = MIPI_CMD_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
	pinfo.lcdc.h_back_porch = 14;
	pinfo.lcdc.h_front_porch = 20;
	pinfo.lcdc.h_pulse_width = 4;
	pinfo.lcdc.v_back_porch = 2;
	pinfo.lcdc.v_front_porch = 2;
	pinfo.lcdc.v_pulse_width = 2;
	pinfo.clk_rate = 200000000;
	pinfo.lcdc.border_clr = 0;  /* blk */
	pinfo.lcdc.underflow_clr = 0xff;  /* blue */
	pinfo.lcdc.hsync_skew = 0;
/* FIH-SW3-MM-NC-LCM-03-[+ */
	pinfo.bl_max = 10;
/* FIH-SW3-MM-NC-LCM-03-]- */
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;
/* FIH-SW3-MM-NC-LCM-10-[+ */
	pinfo.width = 45;  /* 44.64mm */
	pinfo.height = 67;  /* 66.96mm */
/* FIH-SW3-MM-NC-LCM-10-]- */

	pinfo.mipi.mode = DSI_CMD_MODE;
	pinfo.mipi.dst_format = DSI_CMD_DST_FORMAT_RGB666;
	pinfo.mipi.vc = 0;
	pinfo.mipi.rgb_swap = DSI_RGB_SWAP_BGR;
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = FALSE;
	pinfo.mipi.data_lane2 = FALSE;
	pinfo.mipi.data_lane3 = FALSE;
	pinfo.mipi.tx_eot_append = TRUE;
	pinfo.mipi.t_clk_post = 0x04;
	pinfo.mipi.t_clk_pre = 0x0D;
	pinfo.mipi.stream = 0;  /* dma_p */
	pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
/* FIH-SW-MM-VH-DISPLAY-23* */
	pinfo.mipi.frame_rate = 62;
	pinfo.mipi.dsi_phy_db = &dsi_cmd_mode_phy_db;
	pinfo.mipi.dlane_swap = 0x01;
	pinfo.mipi.xres_pad = 0;
	pinfo.mipi.yres_pad = 0;
/* FIH-SW3-MM-NC-LCM-08-[+ */
	pinfo.lcd.refx100 = 7000; /* adjust refx100 to prevent tearing */
/* FIH-SW3-MM-NC-LCM-08-]- */
	pinfo.mipi.te_sel = 1; /* TE from vsync gpio */
	pinfo.mipi.interleave_max = 1;
	pinfo.mipi.insert_dcs_cmd = TRUE;
	pinfo.mipi.wr_mem_continue = 0x3c;
	pinfo.mipi.wr_mem_start = 0x2c;
	pinfo.mipi.rx_eot_ignore = 0;
	pinfo.lcd.vsync_enable = TRUE;
	pinfo.lcd.hw_vsync_mode = TRUE;
	pinfo.mipi.dsi_pclk_rate = 12000000;

	ret = mipi_ilitek_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_FWVGA_PT);
	if (ret)
		pr_err("%s: failed to register device!\n", __func__);

	return ret;
}

module_init(mipi_cmd_ilitek_hvga_pt_init);
