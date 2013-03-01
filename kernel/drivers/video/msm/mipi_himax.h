/* Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 * Copyright(C) 2011-2012 Foxconn International Holdings, Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef MIPI_HIMAX_H
#define MIPI_HIMAX_H

/* FIH-SW-VH-DISPLAY-09+*[ */
#ifdef CONFIG_FIH_SW_DISPLAY_CABC
	#define DEALULT_MIN_BRIGHTNESS 0x00;
	#define DEALULT_DELTA_BRIGHTNESS 0x02;
#endif
/* FIH-SW-VH-DISPLAY-09+*] */

/* FIH-SW-MM-VH-DISPLAY-33*[ */
enum {
	LCM_ID_DA_MES_CMI_DP = 0x0A,
	LCM_ID_DA_MES_AUO_0B = 0x0B,
	LCM_ID_DA_MES_AUO_0D = 0x0D,
	LCM_ID_DA_MES_CMI_TP = 0x0C,
	LCM_ID_DA_JLO_AUO = 0x42,
	LCM_ID_DA_JLO_CMI = 0x43,
	LCM_ID_DA_TAP_CMI = 0x54,
};
enum{
	LCM_ID_DB_MES_AUO = 0x80,
};
/* FIH-SW-MM-VH-DISPLAY-33*] */

int mipi_himax_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel);

#endif  /* MIPI_HIMAX_H */
