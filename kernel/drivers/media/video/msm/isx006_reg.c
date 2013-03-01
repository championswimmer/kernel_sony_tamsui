/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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
 */


#include "isx006.h"

struct isx006_i2c_reg_conf isx006_init_settings[] = {
	//	PLL:648MHz, MIPI 2Lane
	/*Cat. : USERCTRL (System related) */
	{0x3206,0x00, BYTE_LEN, 0 },		// ENDIAN(Little)
	{0x000B,0x01, BYTE_LEN, 0 },		// PLL_CKSEL(648MHz)
	{0x02C7,0x03, BYTE_LEN, 0 },		// SRCCK_DIV(1/8)
	{0x02B8,0x10, BYTE_LEN, 0 },		// VIF_CLKCONFIG1(FullSize/YUV)
	{0x02B9,0x10, BYTE_LEN, 0 },		// VIF_CLKCONFIG2(V1/2/YUV)
	{0x0350,0x02, BYTE_LEN, 0 },		// I2C Address(3C)

	{0x0022,0x0500, WORD_LEN, 0 },		// HSIZE_MONI(1280) /* FIH-SW3-MM-SL-AddForSoMCPanorama-00* 0x0280  */
	{0x0024,0x0A20, WORD_LEN, 0 },		// HSIZE_CAP(2592)
	{0x0026,0x0280, WORD_LEN, 0 },		// HSIZE_MOVIE(640)
	{0x0028,0x03C0, WORD_LEN, 0 },		// VSIZE_MONI(960)  /* FIH-SW3-MM-SL-AddForSoMCPanorama-00* 0x01E0  */
	{0x002A,0x0798, WORD_LEN, 0 },		// VSIZE_CAP(1944)
	{0x002C,0x01E0, WORD_LEN, 0 },		// VSIZE_MOVIE(480)

       /*MM-UW-support AF 01+*/
	{0x002E,0x01, BYTE_LEN, 0 },		// AFMODE_MONI(OFF)
	//{0x002E,0x00, BYTE_LEN, 0 },		// AFMODE_MONI(SAF)
	/*MM-UW-support AF 01-*/
	{0x002F,0x00, BYTE_LEN, 0 },		// AFMODE_HREL(SAF)
	{0x0030,0x01, BYTE_LEN, 0 },		// AFMODE_MOVIE(CAF)
	{0x00FA,0x1F, BYTE_LEN, 0 },		// INTEN0

       {0x0386,0x01, BYTE_LEN, 0 },        // Low power mode

	{0x3E01,0x00, BYTE_LEN, 0 },		// MIPI 2Lane
	{0x3E04,0x06, BYTE_LEN, 0 },		// RGTLPX
	{0x3E05,0x05, BYTE_LEN, 0 },		// RGTCLKPREPARE
	{0x3E06,0x14, BYTE_LEN, 0 },		// RGTCLKZERO
	{0x3E07,0x02, BYTE_LEN, 0 },		// RGTCLKPRE
	{0x3E08,0x0D, BYTE_LEN, 0 },		// RGTCLKPOST
	{0x3E09,0x07, BYTE_LEN, 0 },		// RGTCLKTRAIL
	{0x3E0A,0x0A, BYTE_LEN, 0 },		// RGTHSEXIT
	{0x3E0B,0x05, BYTE_LEN, 0 },		// RGTHSPREPARE
	{0x3E0C,0x08, BYTE_LEN, 0 },		// RGTHSZERO
	{0x3E0D,0x07, BYTE_LEN, 0 },		// RGTHSTRAIL
	/*Cat. : MODE                 */

	/* Cat. : AWB                 */
	{0x442A,0x0B7B, WORD_LEN, 0 },// Fixed coordinates for start-up (indoor) R/G
	{0x442C,0x1846, WORD_LEN, 0 },// Fixed coordinate for start-up (indoor) B/G
	{0x442E,0x0B7B, WORD_LEN, 0 },// Fixed coordinate for start-up (outdoor) R/G
	{0x4430,0x1846, WORD_LEN, 0 },// Fixed coordinate for start-up (outdoor) B/G
	{0x444A,0x7A01, WORD_LEN, 0 },// Indoor decision threshold value /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x444C,0x7DE9, WORD_LEN, 0 },// Outdoor decision threshold value /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	
	/*Cat. : AWB_FRM             */
	{0x4685,0x65, BYTE_LEN, 0 },// INAIM_RIGHT15
	{0x4686,0x65, BYTE_LEN, 0 },// INAIM_RIGHT16
	{0x4687,0x65, BYTE_LEN, 0 },// INAIM_RIGHT17
	{0x4688,0x63, BYTE_LEN, 0 },// INAIM_RIGHT18
	{0x469D,0x0F, BYTE_LEN, 0 },// INAIM_BOTM
	{0x46B3,0x3C, BYTE_LEN, 0 },// OUTFRM_LEFT19
	{0x46B4,0x35, BYTE_LEN, 0 },// OUTFRM_LEFT20
	{0x46B5,0x30, BYTE_LEN, 0 },// OUTFRM_LEFT21
	{0x46EC,0x1A, BYTE_LEN, 0 },// OUTFRM_TOP
	{0x46ED,0x13, BYTE_LEN, 0 },// OUTFRM_BOTM
	{0x4704,0x47, BYTE_LEN, 0 },// OUTAIM_LEFT20
	{0x4705,0x43, BYTE_LEN, 0 },// OUTAIM_LEFT21
	{0x4706,0x41, BYTE_LEN, 0 },// OUTAIM_LEFT22
	{0x472A,0x4B, BYTE_LEN, 0 },// OUTAIM_RIGHT20
	{0x472B,0x47, BYTE_LEN, 0 },// OUTAIM_RIGHT21
	{0x473C,0x19, BYTE_LEN, 0 },// OUTAIM_TOP
	{0x473D,0x14, BYTE_LEN, 0 },// OUTAIM_BOTM
	{0x473E,0x16, BYTE_LEN, 0 },// OUTAIM_FLTOP
	{0x473F,0x14, BYTE_LEN, 0 },// OUTAIM_FLBOTM

	/*Cat. : USERCTRL (INCK_SET) */
	{0x0009,0x16, BYTE_LEN, 0 },		// INCK_SET(24Mhz)
};

/* FIH-SW3-MM-URI-isx006 sensor setting-00+ */
struct isx006_i2c_reg_conf isx006_preload2_settings[] = {
	 ///////////////////////////////////////
	///// Cat. : USERCTRL(Gamma copy) /////
	///////////////////////////////////////

	{0x0105, 0x80, BYTE_LEN, 0 },//
	{0x0387, 0x01, BYTE_LEN, 0 },// RGB_GAMMA_G2RB_F

	////////////////////////////////////////
	////////////// Cat. : ADJ //////////////
	////////////////////////////////////////

	{0x4A04, 0x10BD, WORD_LEN, 0 },// 5800K normalized coefficient RAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 1000h.When 0 is set, it is regarded as 1.
	{0x4A06, 0x0EE0, WORD_LEN, 0 },// 5800K normalized coefficient BAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 1000h.When 0 is set, it is regarded as 1.
	{0x4A08, 0x0146, WORD_LEN, 0 },// 3200K R gainAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 100h.When 0 is set, it is regarded as 1.When the value larger than FFFh is set, it is regarded as FFFh.
	{0x4A0A, 0x0239, WORD_LEN, 0 },// 3200K B gainAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 100h.When 0 is set, it is regarded as 1.When the value larger than FFFh is set, it is regarded as FFFh.
	{0x4A24, 0x0013, WORD_LEN, 0 },// SHD, PreR offset, for R2 /*MTD-MM-SL-ColorShading-00*/ //0x0012
	{0x4A28, 0x0000, WORD_LEN, 0 },// SHD, PreR offset, for RB
	{0x4A2C, 0xFFF8, WORD_LEN, 0 },// SHD, PreB offset, for RB /*MTD-MM-SL-ColorShading-00*/ //0xFFF5

	///////////////////////////////////////
	////////////// Cat. : AE //////////////
	///////////////////////////////////////

	{0x4014, 0x0A5E, WORD_LEN, 0 },// AGCLOWSCL_N
	{0x4016, 0x28DE, WORD_LEN, 0 },// NORMSHTSCL_L/* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4018, 0x0397, WORD_LEN, 0 },// AGCLOWSCL_L
	{0x401A, 0x0540, WORD_LEN, 0 },// EXPSHTSCL_L
	{0x401C, 0x03FD, WORD_LEN, 0 },// AGCHISCL_L
	{0x401E, 0x0268, WORD_LEN, 0 },// MAXSHTSCL_L /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4020, 0x02CB, WORD_LEN, 0 },// AGCMAXSCL_L
    {0x402B, 0x8F, BYTE_LEN, 0 },// FPS_SENSALL /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x402E, 0x0A, BYTE_LEN, 0 },// CAP_GAIN_LIMIT
	{0x4036, 0x0510, WORD_LEN, 0 },// AEPRIAGC
	{0x403E, 0x21FA, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4040, 0x20EC, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4044, 0x1FA4, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x404D, 0xA0, BYTE_LEN, 0 },// AUTORATIO_TH
	{0x405C, 0x09B8, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x405E, 0x08C6, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4060, 0x1FA4, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4085, 0x04, BYTE_LEN, 0 },// AUTOCENT_WEIGHT
	{0x409D, 0x33, BYTE_LEN, 0 },// HIGHJUDG_A
	{0x409E, 0x2D, BYTE_LEN, 0 },// HIGHJUDG_B
	{0x409F, 0x64, BYTE_LEN, 0 },// HIGHJUDG_C
	{0x40A0, 0x5E, BYTE_LEN, 0 },// HIGHJUDG_D

	///////////////////////////////////////
	///////////// Cat. : MODE /////////////
	///////////////////////////////////////
	{0x4C14, 0x0400, WORD_LEN, 0 },// AEPRIAGC /* FIH-SW3-MM-UW-fix flicker issue-00+*/ //0x4000 /*MTD-MM-SL-ColorShading-00*/
	///////////////////////////////////////
	//////////// Cat. : AE_FRM ////////////
	///////////////////////////////////////

	{0x42C0, 0x07, BYTE_LEN, 0 },// Center weight photometry 03 window weight coefficient  Type 4
	{0x42C1, 0x08, BYTE_LEN, 0 },// Center weight photometry 04 window weight coefficient  Type 4
	{0x42C2, 0x07, BYTE_LEN, 0 },// Center weight photometry 05 window weight coefficient  Type 4
	{0x42C6, 0x09, BYTE_LEN, 0 },// Center weight photometry 09 window weight coefficient  Type 4
	{0x42C7, 0x0D, BYTE_LEN, 0 },// Center weight photometry 10 window weight coefficient  Type 4
	{0x42C8, 0x0E, BYTE_LEN, 0 },// Center weight photometry 11 window weight coefficient  Type 4
	{0x42C9, 0x10, BYTE_LEN, 0 },// Center weight photometry 12 window weight coefficient  Type 4
	{0x42CA, 0x11, BYTE_LEN, 0 },// Center weight photometry 13 window weight coefficient  Type 4
	{0x42CB, 0x10, BYTE_LEN, 0 },// Center weight photometry 14 window weight coefficient  Type 4
	{0x42CC, 0x0E, BYTE_LEN, 0 },// Center weight photometry 15 window weight coefficient  Type 4
	{0x42CD, 0x0D, BYTE_LEN, 0 },// Center weight photometry 16 window weight coefficient  Type 4
	{0x42CE, 0x09, BYTE_LEN, 0 },// Center weight photometry 17 window weight coefficient  Type 4
	{0x42CF, 0x0C, BYTE_LEN, 0 },// Center weight photometry 18 window weight coefficient  Type 4
	{0x42D0, 0x13, BYTE_LEN, 0 },// Center weight photometry 19 window weight coefficient  Type 4
	{0x42D1, 0x1F, BYTE_LEN, 0 },// Center weight photometry 20 window weight coefficient  Type 4
	{0x42D2, 0x27, BYTE_LEN, 0 },// Center weight photometry 21 window weight coefficient  Type 4
	{0x42D3, 0x33, BYTE_LEN, 0 },// Center weight photometry 22 window weight coefficient  Type 4
	{0x42D4, 0x27, BYTE_LEN, 0 },// Center weight photometry 23 window weight coefficient  Type 4
	{0x42D5, 0x1F, BYTE_LEN, 0 },// Center weight photometry 24 window weight coefficient  Type 4
	{0x42D6, 0x13, BYTE_LEN, 0 },// Center weight photometry 25 window weight coefficient  Type 4
	{0x42D7, 0x0C, BYTE_LEN, 0 },// Center weight photometry 26 window weight coefficient  Type 4
	{0x42D8, 0x0D, BYTE_LEN, 0 },// Center weight photometry 27 window weight coefficient  Type 4
	{0x42D9, 0x1F, BYTE_LEN, 0 },// Center weight photometry 28 window weight coefficient  Type 4
	{0x42DA, 0x47, BYTE_LEN, 0 },// Center weight photometry 29 window weight coefficient  Type 4
	{0x42DB, 0x4E, BYTE_LEN, 0 },// Center weight photometry 30 window weight coefficient  Type 4
	{0x42DC, 0x56, BYTE_LEN, 0 },// Center weight photometry 31 window weight coefficient  Type 4
	{0x42DD, 0x4E, BYTE_LEN, 0 },// Center weight photometry 32 window weight coefficient  Type 4
	{0x42DE, 0x47, BYTE_LEN, 0 },// Center weight photometry 33 window weight coefficient  Type 4
	{0x42DF, 0x1F, BYTE_LEN, 0 },// Center weight photometry 34 window weight coefficient  Type 4
	{0x42E0, 0x0D, BYTE_LEN, 0 },// Center weight photometry 35 window weight coefficient  Type 4
	{0x42E1, 0x0E, BYTE_LEN, 0 },// Center weight photometry 36 window weight coefficient  Type 4
	{0x42E2, 0x2A, BYTE_LEN, 0 },// Center weight photometry 37 window weight coefficient  Type 4
	{0x42E3, 0x4D, BYTE_LEN, 0 },// Center weight photometry 38 window weight coefficient  Type 4
	{0x42E4, 0x5A, BYTE_LEN, 0 },// Center weight photometry 39 window weight coefficient  Type 4
	{0x42E6, 0x5A, BYTE_LEN, 0 },// Center weight photometry 41 window weight coefficient  Type 4
	{0x42E7, 0x4D, BYTE_LEN, 0 },// Center weight photometry 42 window weight coefficient  Type 4
	{0x42E8, 0x2A, BYTE_LEN, 0 },// Center weight photometry 43 window weight coefficient  Type 4
	{0x42E9, 0x0E, BYTE_LEN, 0 },// Center weight photometry 44 window weight coefficient  Type 4
	{0x42EA, 0x0D, BYTE_LEN, 0 },// Center weight photometry 45 window weight coefficient  Type 4
	{0x42EB, 0x1F, BYTE_LEN, 0 },// Center weight photometry 46 window weight coefficient  Type 4
	{0x42EC, 0x3B, BYTE_LEN, 0 },// Center weight photometry 47 window weight coefficient  Type 4
	{0x42ED, 0x43, BYTE_LEN, 0 },// Center weight photometry 48 window weight coefficient  Type 4
	{0x42EE, 0x4B, BYTE_LEN, 0 },// Center weight photometry 49 window weight coefficient  Type 4
	{0x42EF, 0x43, BYTE_LEN, 0 },// Center weight photometry 50 window weight coefficient  Type 4
	{0x42F0, 0x3B, BYTE_LEN, 0 },// Center weight photometry 51 window weight coefficient  Type 4
	{0x42F1, 0x1F, BYTE_LEN, 0 },// Center weight photometry 52 window weight coefficient  Type 4
	{0x42F2, 0x0D, BYTE_LEN, 0 },// Center weight photometry 53 window weight coefficient  Type 4
	{0x42F3, 0x0B, BYTE_LEN, 0 },// Center weight photometry 54 window weight coefficient  Type 4
	{0x42F4, 0x11, BYTE_LEN, 0 },// Center weight photometry 55 window weight coefficient  Type 4
	{0x42F5, 0x14, BYTE_LEN, 0 },// Center weight photometry 56 window weight coefficient  Type 4
	{0x42F6, 0x18, BYTE_LEN, 0 },// Center weight photometry 57 window weight coefficient  Type 4
	{0x42F8, 0x18, BYTE_LEN, 0 },// Center weight photometry 59 window weight coefficient  Type 4
	{0x42F9, 0x14, BYTE_LEN, 0 },// Center weight photometry 60 window weight coefficient  Type 4
	{0x42FA, 0x11, BYTE_LEN, 0 },// Center weight photometry 61 window weight coefficient  Type 4
	{0x42FB, 0x0B, BYTE_LEN, 0 },// Center weight photometry 62 window weight coefficient  Type 4

	////////////////////////////////////////
	////// Cat. : USERCTRL(AErelated) //////
	////////////////////////////////////////

	{0x0104, 0x41, BYTE_LEN, 0 },// AE_SUB_SN1
	{0x01BD, 0x01, BYTE_LEN, 0 },// MAXFRMEXP_TYPE1
	{0x01BE, 0x02, BYTE_LEN, 0 },// MAXFRMEXP_TYPE2
	{0x01BF, 0x03, BYTE_LEN, 0 },// MAXFRMEXP_TYPE3
	//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*{
	//{0x01C0, 0x08, BYTE_LEN, 0 },// MAXFRMEXP_TYPE4
	{0x01C0, 0x04, BYTE_LEN, 0 },
	//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*}
	////////////////////////////////////////
	////////////// Cat. : AWB //////////////
	////////////////////////////////////////

	{0x440A, 0x1000, WORD_LEN, 0 },// Initial value of error amount for determining commencement of AWB startup

	////////////////////////////////////////
	//////////// Cat. : AWB_FRM ////////////
	////////////////////////////////////////

	////////////////////////////////////////
	/////// Cat. : LMT(Linearmatrix) ///////
	////////////////////////////////////////

	{0x5000, 0xFFA6, WORD_LEN, 0 },// GRG linear matrix coefficient POS1
	{0x5002, 0xFFF3, WORD_LEN, 0 },// GRB linear matrix coefficient POS1
	{0x5004, 0xFFDC, WORD_LEN, 0 },// GGR linear matrix coefficient POS1
	{0x5006, 0xFFE8, WORD_LEN, 0 },// GGB linear matrix coefficient POS1
	{0x5008, 0xFFFF, WORD_LEN, 0 },// GBR linear matrix coefficient POS1
	{0x500A, 0xFFCE, WORD_LEN, 0 },// GBG linear matrix coefficient POS1
	{0x500C, 0xFF9D, WORD_LEN, 0 },// GRG linear matrix coefficient POS2
	{0x500E, 0xFFFA, WORD_LEN, 0 },// GRB linear matrix coefficient POS2
	{0x5010, 0xFFDC, WORD_LEN, 0 },// GGR linear matrix coefficient POS2
	{0x5012, 0xFFEE, WORD_LEN, 0 },// GGB linear matrix coefficient POS2
	{0x5014, 0x0000, WORD_LEN, 0 },// GBR linear matrix coefficient POS2
	{0x5016, 0xFFC0, WORD_LEN, 0 },// GBG linear matrix coefficient POS2
	{0x5018, 0xFFB3, WORD_LEN, 0 },// GRG linear matrix coefficient POS3
	{0x501A, 0xFFFA, WORD_LEN, 0 },// GRB linear matrix coefficient POS3
	{0x501C, 0xFFD2, WORD_LEN, 0 },// GGR linear matrix coefficient POS3
	{0x501E, 0xFFF6, WORD_LEN, 0 },// GGB linear matrix coefficient POS3
	{0x5020, 0xFFF8, WORD_LEN, 0 },// GBR linear matrix coefficient POS3
	{0x5022, 0xFFC8, WORD_LEN, 0 },// GBG linear matrix coefficient POS3
	{0x5024, 0xFFA9, WORD_LEN, 0 },// GRG linear matrix coefficient POS4
	{0x5026, 0x0000, WORD_LEN, 0 },// GRB linear matrix coefficient POS4
	{0x5028, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS4
	{0x502A, 0x0001, WORD_LEN, 0 },// GGB linear matrix coefficient POS4
	{0x502C, 0xFFF4, WORD_LEN, 0 },// GBR linear matrix coefficient POS4
	{0x502E, 0xFF73, WORD_LEN, 0 },// GBG linear matrix coefficient POS4
	{0x5030, 0xFFA9, WORD_LEN, 0 },// GRG linear matrix coefficient POS5
	{0x5032, 0x0000, WORD_LEN, 0 },// GRB linear matrix coefficient POS5
	{0x5034, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS5
	{0x5036, 0x0001, WORD_LEN, 0 },// GGB linear matrix coefficient POS5
	{0x5038, 0xFFF4, WORD_LEN, 0 },// GBR linear matrix coefficient POS5
	{0x503A, 0xFF73, WORD_LEN, 0 },// GBG linear matrix coefficient POS5
	{0x503C, 0xFF83, WORD_LEN, 0 },// GRG linear matrix coefficient POS6
	{0x503E, 0xFFEE, WORD_LEN, 0 },// GRB linear matrix coefficient POS6
	{0x5040, 0xFFD6, WORD_LEN, 0 },// GGR linear matrix coefficient POS6
	{0x5042, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS6
	{0x5044, 0x0000, WORD_LEN, 0 },// GBR linear matrix coefficient POS6
	{0x5046, 0xFFB8, WORD_LEN, 0 },// GBG linear matrix coefficient POS6
	{0x5048, 0xFF83, WORD_LEN, 0 },// GRG linear matrix coefficient POS7
	{0x504A, 0xFFEE, WORD_LEN, 0 },// GRB linear matrix coefficient POS7
	{0x504C, 0xFFD6, WORD_LEN, 0 },// GGR linear matrix coefficient POS7
	{0x504E, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS7
	{0x5050, 0x0000, WORD_LEN, 0 },// GBR linear matrix coefficient POS7
	{0x5052, 0xFFB8, WORD_LEN, 0 },// GBG linear matrix coefficient POS7
	{0x5055, 0x1C, BYTE_LEN, 0 },// POS1 B/G coordinate setting
	{0x5056, 0x3F, BYTE_LEN, 0 },// POS2 R/G coordinate setting
	{0x5057, 0x17, BYTE_LEN, 0 },// POS2 B/G coordinate setting
	{0x5058, 0x5D, BYTE_LEN, 0 },// POS3 R/G coordinate setting
	{0x505A, 0x6C, BYTE_LEN, 0 },// POS4 R/G coordinate setting
	{0x505B, 0x0E, BYTE_LEN, 0 },// POS4 B/G coordinate setting
	{0x505C, 0x95, BYTE_LEN, 0 },// POS5 R/G coordinate setting
	{0x505E, 0x41, BYTE_LEN, 0 },// POS6 R/G coordinate setting
	{0x505F, 0x12, BYTE_LEN, 0 },// POS6 B/G coordinate setting
	{0x5060, 0x4D, BYTE_LEN, 0 },// POS7 R/G coordinate setting
	{0x5061, 0x10, BYTE_LEN, 0 },// POS7 B/G coordinate setting
	{0x50A2, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (1st quadrant), for automatic control, POS1
	{0x50A3, 0x51, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), for automatic control, POS1
	{0x50A4, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (2nd quadrant), for automatic control, POS1
	{0x50A5, 0x61, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), for automatic control, POS1
	{0x50A6, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (3rd quadrant), for automatic control, POS1
	{0x50A7, 0x61, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), for automatic control, POS1
	{0x50A8, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (4th quadrant), for automatic control, POS1
	{0x50A9, 0x51, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), for automatic control, POS1
	{0x50AA, 0xFFF5, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), for automatic control, POS2
	{0x50AC, 0xFFEC, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), for automatic control, POS2
	{0x50AE, 0xFFF5, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), for automatic control, POS2
	{0x50B0, 0xFFE1, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), for automatic control, POS2
	{0x50B2, 0xFFFA, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), for automatic control, POS2
	{0x50B4, 0xFFE1, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), for automatic control, POS2
	{0x50B6, 0xFFFA, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), for automatic control, POS2
	{0x50B8, 0xFFEC, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), for automatic control, POS2
	{0x50BA, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (1st quadrant), for automatic control, POS2
	{0x50BB, 0x6E, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), for automatic control, POS2
	{0x50BC, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (2nd quadrant), for automatic control, POS2
	{0x50BD, 0x73, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), for automatic control, POS2
	{0x50BE, 0x7C, BYTE_LEN, 0 },// RYGAIN reference value (3rd quadrant), for automatic control, POS2
	{0x50BF, 0x73, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), for automatic control, POS2
	{0x50C0, 0x7C, BYTE_LEN, 0 },// RYGAIN reference value (4th quadrant), for automatic control, POS2
	{0x50C1, 0x6E, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), for automatic control, POS2
	{0x50C2, 0x12, BYTE_LEN, 0 },// HueGain pos1 coordinate for automatic control (high color temperature sideÅjx256 is the coordinate.

	///////////////////////////////////////
	//////////// Cat. : GAMMA0 ////////////
	///////////////////////////////////////

	{0x5238, 0x0004, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table0)
	{0x523A, 0x0008, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table0)
	{0x523C, 0x000E, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table0)
	{0x523E, 0x0016, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table0)
	{0x5240, 0x001E, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table0)
	{0x5242, 0x0026, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table0)
	{0x5244, 0x002E, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table0)
	{0x5246, 0x0036, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table0)
	{0x5248, 0x003D, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table0)
	{0x524A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table0)
	{0x524C, 0x0049, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table0)
	{0x524E, 0x004E, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table0)
	{0x5250, 0x0054, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table0)
	{0x5252, 0x0059, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table0)
	{0x5254, 0x005E, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table0)
	{0x5256, 0x0063, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table0)
	{0x5258, 0x0066, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table0)
	{0x525A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table0)
	{0x525C, 0x0087, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table0)
	{0x525E, 0x00AF, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table0)
	{0x5260, 0x00C8, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table0)
	{0x5262, 0x00DC, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table0)
	{0x5264, 0x00EB, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table0)
	{0x5266, 0x00F6, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table0)
	{0x5268, 0x0100, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table0)
	{0x526A, 0x0102, WORD_LEN, 0 },// RGB-Gamma G-knot26(Table0)
	{0x52A2, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -R (Table0)
	{0x52A6, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -G (Table0)
	{0x52AA, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -B (Table0)
	{0x52AE, 0x2100, WORD_LEN, 0 },// Convergence luminance setting (Table0)
	{0x0105, 0x40, BYTE_LEN, 0 },//

	/////////////////////////////////////////
	//// Cat. : PICT(SHD,Y-gamma,Y-knee) ////
	/////////////////////////////////////////
	{0x4E40, 0x1964, WORD_LEN, 0 },/*MM-UW-fix unbalance warning-00+*/
       {0x4E42, 0x18CE, WORD_LEN, 0 },/*MM-UW-fix unbalance warning-00+*/
	{0x4E48, 0x1A2C, WORD_LEN, 0 },// R/G coordinates high threshold value for shading color correction for R2.
	{0x4E4C, 0x6679, WORD_LEN, 0 },// High luminance side threshold value for shading gain correction. /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4E4E, 0x5AC1, WORD_LEN, 0 },// Low luminance side threshold value for shading gain correction. /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x4E58, 0x1EDC, WORD_LEN, 0 },// High threshold for RB at the R/G coordinates for shading color correction.
	{0x4E60, 0x0C0A, WORD_LEN, 0 },// AREACMP_SET2_TB1
	{0x4E62, 0x0CC4, WORD_LEN, 0 },// AREACMP_SET2_TB1
	{0x4E64, 0xE0DD, WORD_LEN, 0 },// AREACMP_SET3_TB1
	{0x4E66, 0xDB1A, WORD_LEN, 0 },// AREACMP_SET3_TB1
	{0x4E68, 0x2023, WORD_LEN, 0 },// AREACMP_SET4_TB1
	{0x4E6A, 0x28C5, WORD_LEN, 0 },// AREACMP_SET4_TB1
	{0x4E6C, 0x0033, WORD_LEN, 0 },// AREACMP_SET5_TB1
	{0x4E6E, 0x0033, WORD_LEN, 0 },// AREACMP_SET5_TB1
	{0x4E70, 0x0C0A, WORD_LEN, 0 },// AREACMP_SET6_TB1
	{0x4E72, 0x0CC4, WORD_LEN, 0 },// AREACMP_SET6_TB1
	{0x4E74, 0xE0DD, WORD_LEN, 0 },// AREACMP_SET7_TB1
	{0x4E76, 0xDB1A, WORD_LEN, 0 },// AREACMP_SET7_TB1
	{0x4E78, 0x2023, WORD_LEN, 0 },// AREACMP_SET8_TB1
	{0x4E7A, 0x28C5, WORD_LEN, 0 },// AREACMP_SET8_TB1
	{0x4E7C, 0x0033, WORD_LEN, 0 },// AREACMP_SET9_TB1
	{0x4E7E, 0x0033, WORD_LEN, 0 },// AREACMP_SET9_TB1
	{0x4F52, 0x00, BYTE_LEN, 0 },// PLUS_START_POS
	{0x4F54, 0x19, BYTE_LEN, 0 },// PLUS_END_POS
	{0x4F55, 0x19, BYTE_LEN, 0 },// MINUS_START_POS
	{0x4F56, 0x1D, BYTE_LEN, 0 },// MINUS_POS
	{0x4F59, 0x01, BYTE_LEN, 0 },// YLOW_TH
	{0x4F5A, 0x14, BYTE_LEN, 0 },// YLOW_RATIO_A
	{0x4F5B, 0x28, BYTE_LEN, 0 },// YLOW_RATIO_B
	{0x4F5C, 0x32, BYTE_LEN, 0 },// YLOW_PLUS
	{0x4F5D, 0x1C, BYTE_LEN, 0 },// YHIGH_TH
	{0x4F60, 0x0A, BYTE_LEN, 0 },// YHIGH_MINUS
	{0x4F6A, 0x00, BYTE_LEN, 0 },// HIST_BLEND
	{0x4F6C, 0x63DF, WORD_LEN, 0 },// AUTOYGAMMA_DOWN
	{0x4F6E, 0x63DE, WORD_LEN, 0 },// AUTOYGAMMA_OFF
	////////////////////////////////////////
	///// Cat. : CXC_DATA(Pre-Shading) /////
	////////////////////////////////////////
    /*MTD-MM-SL-ColorShading-00*{*/
     {0x9000, 0x8282, WORD_LEN, 0	},//valid_code
     {0x9002, 0x01, BYTE_LEN, 0 },
     {0x9003, 0x10, BYTE_LEN, 0 },
     {0x9004, 0x04, BYTE_LEN, 0 },
     {0x9005, 0x40, BYTE_LEN, 0 },
     {0x9006, 0x10, BYTE_LEN, 0 },
     {0x9007, 0x20, BYTE_LEN, 0 },
     {0x9008, 0xC1, BYTE_LEN, 0 },
     {0x9009, 0xFF, BYTE_LEN, 0 },
     {0x900A, 0x03, BYTE_LEN, 0 },
     {0x900B, 0x00, BYTE_LEN, 0 },
     {0x900C, 0x0E, BYTE_LEN, 0 },
     {0x900D, 0x00, BYTE_LEN, 0 },
     {0x900E, 0x40, BYTE_LEN, 0 },
     {0x900F, 0x10, BYTE_LEN, 0 },
     {0x9010, 0xE0, BYTE_LEN, 0 },
     {0x9011, 0x40, BYTE_LEN, 0 },
     {0x9012, 0x80, BYTE_LEN, 0 },
     {0x9013, 0x04, BYTE_LEN, 0 },
     {0x9014, 0x01, BYTE_LEN, 0 },
     {0x9015, 0x12, BYTE_LEN, 0 },
     {0x9016, 0x04, BYTE_LEN, 0 },
     {0x9017, 0x40, BYTE_LEN, 0 },
     {0x9018, 0x10, BYTE_LEN, 0 },
     {0x9019, 0x00, BYTE_LEN, 0 },
     {0x901A, 0x41, BYTE_LEN, 0 },
     {0x901B, 0x80, BYTE_LEN, 0 },
     {0x901C, 0x04, BYTE_LEN, 0 },
     {0x901D, 0xFF, BYTE_LEN, 0 },
     {0x901E, 0x0F, BYTE_LEN, 0 },
     {0x901F, 0x00, BYTE_LEN, 0 },
     {0x9020, 0x38, BYTE_LEN, 0 },
     {0x9021, 0x00, BYTE_LEN, 0 },
     {0x9022, 0x00, BYTE_LEN, 0 },
     {0x9023, 0x41, BYTE_LEN, 0 },
     {0x9024, 0x80, BYTE_LEN, 0 },
     {0x9025, 0x03, BYTE_LEN, 0 },
     {0x9026, 0x01, BYTE_LEN, 0 },
     {0x9027, 0x12, BYTE_LEN, 0 },
     {0x9028, 0x04, BYTE_LEN, 0 },
     {0x9029, 0x48, BYTE_LEN, 0 },
     {0x902A, 0x10, BYTE_LEN, 0 },
     {0x902B, 0x00, BYTE_LEN, 0 },
     {0x902C, 0x41, BYTE_LEN, 0 },
     {0x902D, 0x00, BYTE_LEN, 0 },
     {0x902E, 0x04, BYTE_LEN, 0 },
     {0x902F, 0x01, BYTE_LEN, 0 },
     {0x9030, 0x0C, BYTE_LEN, 0 },
     {0x9031, 0x00, BYTE_LEN, 0 },
     {0x9032, 0x38, BYTE_LEN, 0 },
     {0x9033, 0x00, BYTE_LEN, 0 },
     {0x9034, 0xE0, BYTE_LEN, 0 },
     {0x9035, 0x00, BYTE_LEN, 0 },
     {0x9036, 0x00, BYTE_LEN, 0 },
     {0x9037, 0x04, BYTE_LEN, 0 },
     {0x9038, 0x00, BYTE_LEN, 0 },
     {0x9039, 0x10, BYTE_LEN, 0 },
     {0x903A, 0x0C, BYTE_LEN, 0 },
     {0x903B, 0x50, BYTE_LEN, 0 },
     {0x903C, 0x30, BYTE_LEN, 0 },
     {0x903D, 0x40, BYTE_LEN, 0 },
     {0x903E, 0x01, BYTE_LEN, 0 },
     {0x903F, 0x80, BYTE_LEN, 0 },
     {0x9040, 0x02, BYTE_LEN, 0 },
     {0x9041, 0x00, BYTE_LEN, 0 },
     {0x9042, 0x0A, BYTE_LEN, 0 },
     {0x9043, 0x00, BYTE_LEN, 0 },
     {0x9044, 0x28, BYTE_LEN, 0 },
     {0x9045, 0x20, BYTE_LEN, 0 },
     {0x9046, 0xA0, BYTE_LEN, 0 },
     {0x9047, 0x40, BYTE_LEN, 0 },
     {0x9048, 0x80, BYTE_LEN, 0 },
     {0x9049, 0x02, BYTE_LEN, 0 },
     {0x904A, 0x01, BYTE_LEN, 0 },
     {0x904B, 0x0A, BYTE_LEN, 0 },
     {0x904C, 0x08, BYTE_LEN, 0 },
     {0x904D, 0x30, BYTE_LEN, 0 },
     {0x904E, 0x20, BYTE_LEN, 0 },
     {0x904F, 0x00, BYTE_LEN, 0 },
     {0x9050, 0x81, BYTE_LEN, 0 },
     {0x9051, 0x00, BYTE_LEN, 0 },
     {0x9052, 0x04, BYTE_LEN, 0 },
     {0x9053, 0x03, BYTE_LEN, 0 },
     {0x9054, 0x0A, BYTE_LEN, 0 },
     {0x9055, 0x0C, BYTE_LEN, 0 },
     {0x9056, 0x28, BYTE_LEN, 0 },
     {0x9057, 0x20, BYTE_LEN, 0 },
     {0x9058, 0x60, BYTE_LEN, 0 },
     {0x9059, 0x40, BYTE_LEN, 0 },
     {0x905A, 0x80, BYTE_LEN, 0 },
     {0x905B, 0x00, BYTE_LEN, 0 },
     {0x905C, 0x00, BYTE_LEN, 0 },
     {0x905D, 0x04, BYTE_LEN, 0 },
     {0x905E, 0x04, BYTE_LEN, 0 },
     {0x905F, 0x18, BYTE_LEN, 0 },
     {0x9060, 0x00, BYTE_LEN, 0 },
     {0x9061, 0x80, BYTE_LEN, 0 },
     {0x9062, 0x80, BYTE_LEN, 0 },
     {0x9063, 0x00, BYTE_LEN, 0 },
     {0x9064, 0x03, BYTE_LEN, 0 },
     {0x9065, 0x02, BYTE_LEN, 0 },
     {0x9066, 0x0C, BYTE_LEN, 0 },
     {0x9067, 0x08, BYTE_LEN, 0 },
     {0x9068, 0x20, BYTE_LEN, 0 },
     {0x9069, 0x20, BYTE_LEN, 0 },
     {0x906A, 0x80, BYTE_LEN, 0 },
     {0x906B, 0x80, BYTE_LEN, 0 },
     {0x906C, 0x80, BYTE_LEN, 0 },
     {0x906D, 0x00, BYTE_LEN, 0 },
     {0x906E, 0x01, BYTE_LEN, 0 },
     {0x906F, 0x02, BYTE_LEN, 0 },
     {0x9070, 0x08, BYTE_LEN, 0 },
     {0x9071, 0x08, BYTE_LEN, 0 },
     {0x9072, 0x10, BYTE_LEN, 0 },
     {0x9073, 0x20, BYTE_LEN, 0 },
     {0x9074, 0x80, BYTE_LEN, 0 },
     {0x9075, 0x00, BYTE_LEN, 0 },
     {0x9076, 0x01, BYTE_LEN, 0 },
     {0x9077, 0x02, BYTE_LEN, 0 },
     {0x9078, 0x0A, BYTE_LEN, 0 },
     {0x9079, 0x08, BYTE_LEN, 0 },
     {0x907A, 0x28, BYTE_LEN, 0 },
     {0x907B, 0x40, BYTE_LEN, 0 },
     {0x907C, 0x60, BYTE_LEN, 0 },
     {0x907D, 0x00, BYTE_LEN, 0 },
     {0x907E, 0x81, BYTE_LEN, 0 },
     {0x907F, 0x01, BYTE_LEN, 0 },
     {0x9080, 0x02, BYTE_LEN, 0 },
     {0x9081, 0x02, BYTE_LEN, 0 },
     {0x9082, 0x00, BYTE_LEN, 0 },
     {0x9083, 0x00, BYTE_LEN, 0 },
     {0x9084, 0x30, BYTE_LEN, 0 },
     {0x9085, 0xE0, BYTE_LEN, 0 },
     {0x9086, 0x7F, BYTE_LEN, 0 },
     {0x9087, 0x00, BYTE_LEN, 0 },
     {0x9088, 0x00, BYTE_LEN, 0 },
     {0x9089, 0x01, BYTE_LEN, 0 },
     {0x908A, 0x02, BYTE_LEN, 0 },
     {0x908B, 0x0C, BYTE_LEN, 0 },
     {0x908C, 0x20, BYTE_LEN, 0 },
     {0x908D, 0x30, BYTE_LEN, 0 },
     {0x908E, 0x80, BYTE_LEN, 0 },
     {0x908F, 0x80, BYTE_LEN, 0 },
     {0x9090, 0x00, BYTE_LEN, 0 },
     {0x9091, 0x01, BYTE_LEN, 0 },
     {0x9092, 0x02, BYTE_LEN, 0 },
     {0x9093, 0x04, BYTE_LEN, 0 },
     {0x9094, 0x08, BYTE_LEN, 0 },
     {0x9095, 0x10, BYTE_LEN, 0 },
     {0x9096, 0x20, BYTE_LEN, 0 },
     {0x9097, 0x00, BYTE_LEN, 0 },
     {0x9098, 0x00, BYTE_LEN, 0 },
     {0x9099, 0x01, BYTE_LEN, 0 },
     {0x909A, 0x00, BYTE_LEN, 0 },
     {0x909B, 0x03, BYTE_LEN, 0 },
     {0x909C, 0x00, BYTE_LEN, 0 },
     {0x909D, 0x00, BYTE_LEN, 0 },
     {0x909E, 0x08, BYTE_LEN, 0 },
     {0x909F, 0x30, BYTE_LEN, 0 },
     {0x90A0, 0x80, BYTE_LEN, 0 },
     {0x90A1, 0xC0, BYTE_LEN, 0 },
     {0x90A2, 0x00, BYTE_LEN, 0 },
     {0x90A3, 0x02, BYTE_LEN, 0 },
     {0x90A4, 0x03, BYTE_LEN, 0 },
     {0x90A5, 0x08, BYTE_LEN, 0 },
     {0x90A6, 0x0C, BYTE_LEN, 0 },
     {0x90A7, 0x20, BYTE_LEN, 0 },
     {0x90A8, 0x10, BYTE_LEN, 0 },
     {0x90A9, 0x40, BYTE_LEN, 0 },
     {0x90AA, 0x80, BYTE_LEN, 0 },
     {0x90AB, 0x00, BYTE_LEN, 0 },
     {0x90AC, 0x00, BYTE_LEN, 0 },
     {0x90AD, 0x02, BYTE_LEN, 0 },
     {0x90AE, 0x00, BYTE_LEN, 0 },
     {0x90AF, 0x08, BYTE_LEN, 0 },
     {0x90B0, 0x08, BYTE_LEN, 0 },
     {0x90B1, 0x30, BYTE_LEN, 0 },
     {0x90B2, 0x60, BYTE_LEN, 0 },
     {0x90B3, 0xC0, BYTE_LEN, 0 },
     {0x90B4, 0x80, BYTE_LEN, 0 },
     {0x90B5, 0x01, BYTE_LEN, 0 },
     {0x90B6, 0x03, BYTE_LEN, 0 },
     {0x90B7, 0x06, BYTE_LEN, 0 },
     {0x90B8, 0x0C, BYTE_LEN, 0 },
     {0x90B9, 0x28, BYTE_LEN, 0 },
     {0x90BA, 0x30, BYTE_LEN, 0 },
     {0x90BB, 0xA0, BYTE_LEN, 0 },
     {0x90BC, 0x40, BYTE_LEN, 0 },
     {0x90BD, 0x80, BYTE_LEN, 0 },
     {0x90BE, 0x02, BYTE_LEN, 0 },
     {0x90BF, 0x03, BYTE_LEN, 0 },
     {0x90C0, 0x08, BYTE_LEN, 0 },
     {0x90C1, 0x0C, BYTE_LEN, 0 },
     {0x90C2, 0x20, BYTE_LEN, 0 },
     {0x90C3, 0x40, BYTE_LEN, 0 },
     {0x90C4, 0xA0, BYTE_LEN, 0 },
     {0x90C5, 0xC0, BYTE_LEN, 0 },
     {0x90C6, 0x00, BYTE_LEN, 0 },
     {0x90C7, 0x02, BYTE_LEN, 0 },
     {0x90C8, 0x02, BYTE_LEN, 0 },
     {0x90C9, 0x08, BYTE_LEN, 0 },
     {0x90CA, 0x08, BYTE_LEN, 0 },
     {0x90CB, 0x20, BYTE_LEN, 0 },
     {0x90CC, 0x10, BYTE_LEN, 0 },
     {0x90CD, 0xC0, BYTE_LEN, 0 },
     {0x90CE, 0x40, BYTE_LEN, 0 },
     {0x90CF, 0x00, BYTE_LEN, 0 },
     {0x90D0, 0x03, BYTE_LEN, 0 },
     {0x90D1, 0x02, BYTE_LEN, 0 },
     {0x90D2, 0x0A, BYTE_LEN, 0 },
     {0x90D3, 0x10, BYTE_LEN, 0 },
     {0x90D4, 0x28, BYTE_LEN, 0 },
     {0x90D5, 0x20, BYTE_LEN, 0 },
     {0x90D6, 0xA0, BYTE_LEN, 0 },
     {0x90D7, 0xC0, BYTE_LEN, 0 },
     {0x90D8, 0x80, BYTE_LEN, 0 },
     {0x90D9, 0x02, BYTE_LEN, 0 },
     {0x90DA, 0x03, BYTE_LEN, 0 },
     {0x90DB, 0x0C, BYTE_LEN, 0 },
     {0x90DC, 0x0C, BYTE_LEN, 0 },
     {0x90DD, 0x28, BYTE_LEN, 0 },
     {0x90DE, 0x30, BYTE_LEN, 0 },
     {0x90DF, 0xA0, BYTE_LEN, 0 },
     {0x90E0, 0x40, BYTE_LEN, 0 },
     {0x90E1, 0x00, BYTE_LEN, 0 },
     {0x90E2, 0x03, BYTE_LEN, 0 },
     {0x90E3, 0x01, BYTE_LEN, 0 },
     {0x90E4, 0x0C, BYTE_LEN, 0 },
     {0x90E5, 0x08, BYTE_LEN, 0 },
     {0x90E6, 0x28, BYTE_LEN, 0 },
     {0x90E7, 0x40, BYTE_LEN, 0 },
     {0x90E8, 0xA0, BYTE_LEN, 0 },
     {0x90E9, 0x80, BYTE_LEN, 0 },
     {0x90EA, 0x80, BYTE_LEN, 0 },
     {0x90EB, 0x02, BYTE_LEN, 0 },
     {0x90EC, 0x03, BYTE_LEN, 0 },
     {0x90ED, 0x0A, BYTE_LEN, 0 },
     {0x90EE, 0x0C, BYTE_LEN, 0 },
     {0x90EF, 0x30, BYTE_LEN, 0 },
     {0x90F0, 0x30, BYTE_LEN, 0 },
     {0x90F1, 0xA0, BYTE_LEN, 0 },
     {0x90F2, 0xC0, BYTE_LEN, 0 },
     {0x90F3, 0x80, BYTE_LEN, 0 },
     {0x90F4, 0x02, BYTE_LEN, 0 },
     {0x90F5, 0x02, BYTE_LEN, 0 },
     {0x90F6, 0xF0, BYTE_LEN, 0 },
     {0x90F7, 0x0B, BYTE_LEN, 0 },
     {0x90F8, 0xC0, BYTE_LEN, 0 },
     {0x90F9, 0x2F, BYTE_LEN, 0 },
     {0x90FA, 0x40, BYTE_LEN, 0 },
     {0x90FB, 0xBF, BYTE_LEN, 0 },
     {0x90FC, 0x00, BYTE_LEN, 0 },
     {0x90FD, 0xFC, BYTE_LEN, 0 },
     {0x90FE, 0x01, BYTE_LEN, 0 },
     {0x90FF, 0xF2, BYTE_LEN, 0 },
     {0x9100, 0x03, BYTE_LEN, 0 },
     {0x9101, 0xC0, BYTE_LEN, 0 },
     {0x9102, 0xFF, BYTE_LEN, 0 },
     {0x9103, 0xDF, BYTE_LEN, 0 },
     {0x9104, 0x3E, BYTE_LEN, 0 },
     {0x9105, 0x80, BYTE_LEN, 0 },
     {0x9106, 0xFB, BYTE_LEN, 0 },
     {0x9107, 0x00, BYTE_LEN, 0 },
     {0x9108, 0xEE, BYTE_LEN, 0 },
     {0x9109, 0x0B, BYTE_LEN, 0 },
     {0x910A, 0xC0, BYTE_LEN, 0 },
     {0x910B, 0x2F, BYTE_LEN, 0 },
     {0x910C, 0x00, BYTE_LEN, 0 },
     {0x910D, 0xBF, BYTE_LEN, 0 },
     {0x910E, 0x00, BYTE_LEN, 0 },
     {0x910F, 0xFD, BYTE_LEN, 0 },
     {0x9110, 0x02, BYTE_LEN, 0 },
     {0x9111, 0xF0, BYTE_LEN, 0 },
     {0x9112, 0x07, BYTE_LEN, 0 },
     {0x9113, 0xC8, BYTE_LEN, 0 },
     {0x9114, 0x0F, BYTE_LEN, 0 },
     {0x9115, 0x00, BYTE_LEN, 0 },
     {0x9116, 0xFF, BYTE_LEN, 0 },
     {0x9117, 0x7F, BYTE_LEN, 0 },
     {0x9118, 0xFB, BYTE_LEN, 0 },
     {0x9119, 0x00, BYTE_LEN, 0 },
     {0x911A, 0xEE, BYTE_LEN, 0 },
     {0x911B, 0x03, BYTE_LEN, 0 },
     {0x911C, 0xB8, BYTE_LEN, 0 },
     {0x911D, 0x2F, BYTE_LEN, 0 },
     {0x911E, 0x00, BYTE_LEN, 0 },
     {0x911F, 0xBF, BYTE_LEN, 0 },
     {0x9120, 0x00, BYTE_LEN, 0 },
     {0x9121, 0xFC, BYTE_LEN, 0 },
     {0x9122, 0x02, BYTE_LEN, 0 },
     {0x9123, 0xF0, BYTE_LEN, 0 },
     {0x9124, 0x03, BYTE_LEN, 0 },
     {0x9125, 0xC0, BYTE_LEN, 0 },
     {0x9126, 0xFF, BYTE_LEN, 0 },
     {0x9127, 0x3F, BYTE_LEN, 0 },
     {0x9128, 0x3F, BYTE_LEN, 0 },
     {0x9129, 0x80, BYTE_LEN, 0 },
     {0x912A, 0xFB, BYTE_LEN, 0 },
     {0x912B, 0x00, BYTE_LEN, 0 },
     {0x912C, 0xE8, BYTE_LEN, 0 },
     {0x912D, 0xFF, BYTE_LEN, 0 },
     {0x912E, 0xBF, BYTE_LEN, 0 },
     {0x912F, 0xFF, BYTE_LEN, 0 },
     {0x9130, 0xFF, BYTE_LEN, 0 },
     {0x9131, 0xBE, BYTE_LEN, 0 },
     {0x9132, 0x80, BYTE_LEN, 0 },
     {0x9133, 0xFD, BYTE_LEN, 0 },
     {0x9134, 0x02, BYTE_LEN, 0 },
     {0x9135, 0xF6, BYTE_LEN, 0 },
     {0x9136, 0x03, BYTE_LEN, 0 },
     {0x9137, 0xC0, BYTE_LEN, 0 },
     {0x9138, 0x0F, BYTE_LEN, 0 },
     {0x9139, 0x00, BYTE_LEN, 0 },
     {0x913A, 0xBF, BYTE_LEN, 0 },
     {0x913B, 0x7F, BYTE_LEN, 0 },
     {0x913C, 0xFD, BYTE_LEN, 0 },
     {0x913D, 0xFF, BYTE_LEN, 0 },
     {0x913E, 0xF3, BYTE_LEN, 0 },
     {0x913F, 0x03, BYTE_LEN, 0 },
     {0x9140, 0xD0, BYTE_LEN, 0 },
     {0x9141, 0x0F, BYTE_LEN, 0 },
     {0x9142, 0x40, BYTE_LEN, 0 },
     {0x9143, 0x3F, BYTE_LEN, 0 },
     {0x9144, 0x00, BYTE_LEN, 0 },
     {0x9145, 0xFD, BYTE_LEN, 0 },
     {0x9146, 0x02, BYTE_LEN, 0 },
     {0x9147, 0xF4, BYTE_LEN, 0 },
     {0x9148, 0x0B, BYTE_LEN, 0 },
     {0x9149, 0xD0, BYTE_LEN, 0 },
     {0x914A, 0x0F, BYTE_LEN, 0 },
     {0x914B, 0x40, BYTE_LEN, 0 },
     {0x914C, 0xFF, BYTE_LEN, 0 },
     {0x914D, 0x7F, BYTE_LEN, 0 },
     {0x914E, 0xFF, BYTE_LEN, 0 },
     {0x914F, 0xFF, BYTE_LEN, 0 },
     {0x9150, 0xF3, BYTE_LEN, 0 },
     {0x9151, 0xFF, BYTE_LEN, 0 },
     {0x9152, 0xD7, BYTE_LEN, 0 },
     {0x9153, 0xFF, BYTE_LEN, 0 },
     {0x9154, 0xFF, BYTE_LEN, 0 },
     {0x9155, 0x3E, BYTE_LEN, 0 },
     {0x9156, 0x80, BYTE_LEN, 0 },
     {0x9157, 0xFD, BYTE_LEN, 0 },
     {0x9158, 0x00, BYTE_LEN, 0 },
     {0x9159, 0xF6, BYTE_LEN, 0 },
     {0x915A, 0x07, BYTE_LEN, 0 },
     {0x915B, 0xE0, BYTE_LEN, 0 },
     {0x915C, 0x1F, BYTE_LEN, 0 },
     {0x915D, 0x80, BYTE_LEN, 0 },
     {0x915E, 0xBF, BYTE_LEN, 0 },
     {0x915F, 0x00, BYTE_LEN, 0 },
     {0x9160, 0xFE, BYTE_LEN, 0 },
     {0x9161, 0x00, BYTE_LEN, 0 },
     {0x9162, 0xF8, BYTE_LEN, 0 },
     {0x9163, 0x03, BYTE_LEN, 0 },
     {0x9164, 0xE8, BYTE_LEN, 0 },
     {0x9165, 0xFF, BYTE_LEN, 0 },
     {0x9166, 0x7F, BYTE_LEN, 0 },
     {0x9167, 0xFF, BYTE_LEN, 0 },
     {0x9168, 0xFF, BYTE_LEN, 0 },
     {0x9169, 0xFE, BYTE_LEN, 0 },
     {0x916A, 0xFE, BYTE_LEN, 0 },
     {0x916B, 0xF9, BYTE_LEN, 0 },
     {0x916C, 0xFB, BYTE_LEN, 0 },
     {0x916D, 0xE7, BYTE_LEN, 0 },
     {0x916E, 0x2F, BYTE_LEN, 0 },
     {0x916F, 0x20, BYTE_LEN, 0 },
     {0x9170, 0x80, BYTE_LEN, 0 },
     {0x9171, 0x80, BYTE_LEN, 0 },
     {0x9172, 0x00, BYTE_LEN, 0 },
     {0x9173, 0x02, BYTE_LEN, 0 },
     {0x9174, 0xFC, BYTE_LEN, 0 },
     {0x9175, 0x03, BYTE_LEN, 0 },
     {0x9176, 0xF8, BYTE_LEN, 0 },
     {0x9177, 0x0F, BYTE_LEN, 0 },
     {0x9178, 0x60, BYTE_LEN, 0 },
     {0x9179, 0xC0, BYTE_LEN, 0 },
     {0x917A, 0x7F, BYTE_LEN, 0 },
     {0x917B, 0x00, BYTE_LEN, 0 },
     {0x917C, 0xFF, BYTE_LEN, 0 },
     {0x917D, 0x03, BYTE_LEN, 0 },
     {0x917E, 0x04, BYTE_LEN, 0 },
     {0x917F, 0xF8, BYTE_LEN, 0 },
     {0x9180, 0x1F, BYTE_LEN, 0 },
     {0x9181, 0xE0, BYTE_LEN, 0 },
     {0x9182, 0x3F, BYTE_LEN, 0 },
     {0x9183, 0x01, BYTE_LEN, 0 },
     {0x9184, 0x02, BYTE_LEN, 0 },
     {0x9185, 0x04, BYTE_LEN, 0 },
     {0x9186, 0x08, BYTE_LEN, 0 },
     {0x9187, 0x10, BYTE_LEN, 0 },
     {0x9188, 0x18, BYTE_LEN, 0 },
     {0x9189, 0x30, BYTE_LEN, 0 },
     {0x918A, 0x20, BYTE_LEN, 0 },
     {0x918B, 0x80, BYTE_LEN, 0 },
     {0x918C, 0x80, BYTE_LEN, 0 },
     {0x918D, 0x01, BYTE_LEN, 0 },
     {0x918E, 0x00, BYTE_LEN, 0 },
     {0x918F, 0x06, BYTE_LEN, 0 },
     {0x9190, 0x08, BYTE_LEN, 0 },
     {0x9191, 0x10, BYTE_LEN, 0 },
     {0x9192, 0x10, BYTE_LEN, 0 },
     {0x9193, 0x20, BYTE_LEN, 0 },
     {0x9194, 0x40, BYTE_LEN, 0 },
     {0x9195, 0x80, BYTE_LEN, 0 },
     {0x9196, 0x00, BYTE_LEN, 0 },
     {0x9197, 0x05, BYTE_LEN, 0 },
     {0x9198, 0x0C, BYTE_LEN, 0 },
     {0x9199, 0x14, BYTE_LEN, 0 },
     {0x919A, 0x30, BYTE_LEN, 0 },
     {0x919B, 0x40, BYTE_LEN, 0 },
     {0x919C, 0xA0, BYTE_LEN, 0 },
     {0x919D, 0x00, BYTE_LEN, 0 },
     {0x919E, 0x81, BYTE_LEN, 0 },
     {0x919F, 0x02, BYTE_LEN, 0 },
     {0x91A0, 0x01, BYTE_LEN, 0 },
     {0x91A1, 0x0C, BYTE_LEN, 0 },
     {0x91A2, 0x04, BYTE_LEN, 0 },
     {0x91A3, 0x20, BYTE_LEN, 0 },
     {0x91A4, 0x10, BYTE_LEN, 0 },
     {0x91A5, 0x80, BYTE_LEN, 0 },
     {0x91A6, 0x80, BYTE_LEN, 0 },
     {0x91A7, 0x00, BYTE_LEN, 0 },
     {0x91A8, 0x02, BYTE_LEN, 0 },
     {0x91A9, 0x02, BYTE_LEN, 0 },
     {0x91AA, 0x08, BYTE_LEN, 0 },
     {0x91AB, 0x18, BYTE_LEN, 0 },
     {0x91AC, 0x28, BYTE_LEN, 0 },
     {0x91AD, 0x60, BYTE_LEN, 0 },
     {0x91AE, 0xA0, BYTE_LEN, 0 },
     {0x91AF, 0x40, BYTE_LEN, 0 },
     {0x91B0, 0x81, BYTE_LEN, 0 },
     {0x91B1, 0x01, BYTE_LEN, 0 },
     {0x91B2, 0x06, BYTE_LEN, 0 },
     {0x91B3, 0x0C, BYTE_LEN, 0 },
     {0x91B4, 0x10, BYTE_LEN, 0 },
     {0x91B5, 0x18, BYTE_LEN, 0 },
     {0x91B6, 0x10, BYTE_LEN, 0 },
     {0x91B7, 0x60, BYTE_LEN, 0 },
     {0x91B8, 0xC0, BYTE_LEN, 0 },
     {0x91B9, 0x80, BYTE_LEN, 0 },
     {0x91BA, 0x02, BYTE_LEN, 0 },
     {0x91BB, 0x02, BYTE_LEN, 0 },
     {0x91BC, 0x0C, BYTE_LEN, 0 },
     {0x91BD, 0x08, BYTE_LEN, 0 },
     {0x91BE, 0x30, BYTE_LEN, 0 },
     {0x91BF, 0x50, BYTE_LEN, 0 },
     {0x91C0, 0xA0, BYTE_LEN, 0 },
     {0x91C1, 0x40, BYTE_LEN, 0 },
     {0x91C2, 0x81, BYTE_LEN, 0 },
     {0x91C3, 0x02, BYTE_LEN, 0 },
     {0x91C4, 0x04, BYTE_LEN, 0 },
     {0x91C5, 0x0C, BYTE_LEN, 0 },
     {0x91C6, 0x10, BYTE_LEN, 0 },
     {0x91C7, 0x18, BYTE_LEN, 0 },
     {0x91C8, 0x40, BYTE_LEN, 0 },
     {0x91C9, 0x60, BYTE_LEN, 0 },
     {0x91CA, 0xC0, BYTE_LEN, 0 },
     {0x91CB, 0x80, BYTE_LEN, 0 },
     {0x91CC, 0x03, BYTE_LEN, 0 },
     {0x91CD, 0x02, BYTE_LEN, 0 },
     {0x91CE, 0x0C, BYTE_LEN, 0 },
     {0x91CF, 0x0C, BYTE_LEN, 0 },
     {0x91D0, 0x28, BYTE_LEN, 0 },
     {0x91D1, 0x30, BYTE_LEN, 0 },
     {0x91D2, 0xA0, BYTE_LEN, 0 },
     {0x91D3, 0x40, BYTE_LEN, 0 },
     {0x91D4, 0x81, BYTE_LEN, 0 },
     {0x91D5, 0x02, BYTE_LEN, 0 },
     {0x91D6, 0x05, BYTE_LEN, 0 },
     {0x91D7, 0x0A, BYTE_LEN, 0 },
     {0x91D8, 0x10, BYTE_LEN, 0 },
     {0x91D9, 0x30, BYTE_LEN, 0 },
     {0x91DA, 0x40, BYTE_LEN, 0 },
     {0x91DB, 0x60, BYTE_LEN, 0 },
     {0x91DC, 0x00, BYTE_LEN, 0 },
     {0x91DD, 0x81, BYTE_LEN, 0 },
     {0x91DE, 0x01, BYTE_LEN, 0 },
     {0x91DF, 0x03, BYTE_LEN, 0 },
     {0x91E0, 0x0E, BYTE_LEN, 0 },
     {0x91E1, 0x08, BYTE_LEN, 0 },
     {0x91E2, 0x30, BYTE_LEN, 0 },
     {0x91E3, 0x30, BYTE_LEN, 0 },
     {0x91E4, 0xA0, BYTE_LEN, 0 },
     {0x91E5, 0xC0, BYTE_LEN, 0 },
     {0x91E6, 0x80, BYTE_LEN, 0 },
     {0x91E7, 0x02, BYTE_LEN, 0 },
     /*MTD-MM-SL-ColorShading-00*}*/



 ///////////////////////////////////////
 /////////// Cat. : SHD_DATA ///////////
 ///////////////////////////////////////
 /*MTD-MM-SL-ColorShading-00*{*/
	  {0xA000, 0x9191, WORD_LEN, 0 },	 //valid_code
	  {0xA002, 0x1D,BYTE_LEN, 0 },
	  {0xA003, 0xD9,BYTE_LEN, 0 },
	  {0xA004, 0x8A,BYTE_LEN, 0 },
	  {0xA005, 0x57,BYTE_LEN, 0 },
	  {0xA006, 0x50,BYTE_LEN, 0 },
	  {0xA007, 0x93,BYTE_LEN, 0 },
	  {0xA008, 0x15,BYTE_LEN, 0 },
	  {0xA009, 0xD4,BYTE_LEN, 0 },
	  {0xA00A, 0x58,BYTE_LEN, 0 },
	  {0xA00B, 0x25,BYTE_LEN, 0 },
	  {0xA00C, 0x34,BYTE_LEN, 0 },
	  {0xA00D, 0x5A,BYTE_LEN, 0 },
	  {0xA00E, 0x21,BYTE_LEN, 0 },
	  {0xA00F, 0xCD,BYTE_LEN, 0 },
	  {0xA010, 0x55,BYTE_LEN, 0 },
	  {0xA011, 0x4A,BYTE_LEN, 0 },
	  {0xA012, 0x93,BYTE_LEN, 0 },
	  {0xA013, 0x15,BYTE_LEN, 0 },
	  {0xA014, 0xD4,BYTE_LEN, 0 },
	  {0xA015, 0x98,BYTE_LEN, 0 },
	  {0xA016, 0x25,BYTE_LEN, 0 },
	  {0xA017, 0x37,BYTE_LEN, 0 },
	  {0xA018, 0x2E,BYTE_LEN, 0 },
	  {0xA019, 0xA1,BYTE_LEN, 0 },
	  {0xA01A, 0xCB,BYTE_LEN, 0 },
	  {0xA01B, 0x5F,BYTE_LEN, 0 },
	  {0xA01C, 0x98,BYTE_LEN, 0 },
	  {0xA01D, 0x83,BYTE_LEN, 0 },
	  {0xA01E, 0x19,BYTE_LEN, 0 },
	  {0xA01F, 0xF4,BYTE_LEN, 0 },
	  {0xA020, 0x20,BYTE_LEN, 0 },
	  {0xA021, 0x06,BYTE_LEN, 0 },
	  {0xA022, 0x3B,BYTE_LEN, 0 },
	  {0xA023, 0x87,BYTE_LEN, 0 },
	  {0xA024, 0x91,BYTE_LEN, 0 },
	  {0xA025, 0xCE,BYTE_LEN, 0 },
	  {0xA026, 0x60,BYTE_LEN, 0 },
	  {0xA027, 0x9A,BYTE_LEN, 0 },
	  {0xA028, 0x73,BYTE_LEN, 0 },
	  {0xA029, 0x98,BYTE_LEN, 0 },
	  {0xA02A, 0xEB,BYTE_LEN, 0 },
	  {0xA02B, 0x30,BYTE_LEN, 0 },
	  {0xA02C, 0xE6,BYTE_LEN, 0 },
	  {0xA02D, 0x3A,BYTE_LEN, 0 },
	  {0xA02E, 0x95,BYTE_LEN, 0 },
	  {0xA02F, 0x79,BYTE_LEN, 0 },
	  {0xA030, 0x4F,BYTE_LEN, 0 },
	  {0xA031, 0x60,BYTE_LEN, 0 },
	  {0xA032, 0xB6,BYTE_LEN, 0 },
	  {0xA033, 0xA3,BYTE_LEN, 0 },
	  {0xA034, 0x16,BYTE_LEN, 0 },
	  {0xA035, 0xD8,BYTE_LEN, 0 },
	  {0xA036, 0xF8,BYTE_LEN, 0 },
	  {0xA037, 0x85,BYTE_LEN, 0 },
	  {0xA038, 0x38,BYTE_LEN, 0 },
	  {0xA039, 0x6C,BYTE_LEN, 0 },
	  {0xA03A, 0x11,BYTE_LEN, 0 },
	  {0xA03B, 0x4D,BYTE_LEN, 0 },
	  {0xA03C, 0x57,BYTE_LEN, 0 },
	  {0xA03D, 0x2A,BYTE_LEN, 0 },
	  {0xA03E, 0x73,BYTE_LEN, 0 },
	  {0xA03F, 0x95,BYTE_LEN, 0 },
	  {0xA040, 0xC6,BYTE_LEN, 0 },
	  {0xA041, 0x7C,BYTE_LEN, 0 },
	  {0xA042, 0x45,BYTE_LEN, 0 },
	  {0xA043, 0x33,BYTE_LEN, 0 },
	  {0xA044, 0x6A,BYTE_LEN, 0 },
	  {0xA045, 0x51,BYTE_LEN, 0 },
	  {0xA046, 0x4D,BYTE_LEN, 0 },
	  {0xA047, 0x60,BYTE_LEN, 0 },
	  {0xA048, 0xA4,BYTE_LEN, 0 },
	  {0xA049, 0xF3,BYTE_LEN, 0 },
	  {0xA04A, 0x96,BYTE_LEN, 0 },
	  {0xA04B, 0xE1,BYTE_LEN, 0 },
	  {0xA04C, 0xAC,BYTE_LEN, 0 },
	  {0xA04D, 0x05,BYTE_LEN, 0 },
	  {0xA04E, 0x35,BYTE_LEN, 0 },
	  {0xA04F, 0x6D,BYTE_LEN, 0 },
	  {0xA050, 0xF9,BYTE_LEN, 0 },
	  {0xA051, 0x4C,BYTE_LEN, 0 },
	  {0xA052, 0x53,BYTE_LEN, 0 },
	  {0xA053, 0xEA,BYTE_LEN, 0 },
	  {0xA054, 0xD2,BYTE_LEN, 0 },
	  {0xA055, 0x13,BYTE_LEN, 0 },
	  {0xA056, 0xAD,BYTE_LEN, 0 },
	  {0xA057, 0xD0,BYTE_LEN, 0 },
	  {0xA058, 0x24,BYTE_LEN, 0 },
	  {0xA059, 0x2A,BYTE_LEN, 0 },
	  {0xA05A, 0x3B,BYTE_LEN, 0 },
	  {0xA05B, 0xD1,BYTE_LEN, 0 },
	  {0xA05C, 0x8A,BYTE_LEN, 0 },
	  {0xA05D, 0x53,BYTE_LEN, 0 },
	  {0xA05E, 0xEC,BYTE_LEN, 0 },
	  {0xA05F, 0xF2,BYTE_LEN, 0 },
	  {0xA060, 0x96,BYTE_LEN, 0 },
	  {0xA061, 0xD7,BYTE_LEN, 0 },
	  {0xA062, 0xC4,BYTE_LEN, 0 },
	  {0xA063, 0x25,BYTE_LEN, 0 },
	  {0xA064, 0x37,BYTE_LEN, 0 },
	  {0xA065, 0x68,BYTE_LEN, 0 },
	  {0xA066, 0xD9,BYTE_LEN, 0 },
	  {0xA067, 0x8C,BYTE_LEN, 0 },
	  {0xA068, 0x56,BYTE_LEN, 0 },
	  {0xA069, 0x02,BYTE_LEN, 0 },
	  {0xA06A, 0x73,BYTE_LEN, 0 },
	  {0xA06B, 0x93,BYTE_LEN, 0 },
	  {0xA06C, 0xA5,BYTE_LEN, 0 },
	  {0xA06D, 0x70,BYTE_LEN, 0 },
	  {0xA06E, 0xC4,BYTE_LEN, 0 },
	  {0xA06F, 0x24,BYTE_LEN, 0 },
	  {0xA070, 0x11,BYTE_LEN, 0 },
	  {0xA071, 0xD9,BYTE_LEN, 0 },
	  {0xA072, 0x88,BYTE_LEN, 0 },
	  {0xA073, 0x46,BYTE_LEN, 0 },
	  {0xA074, 0x4C,BYTE_LEN, 0 },
	  {0xA075, 0x22,BYTE_LEN, 0 },
	  {0xA076, 0x93,BYTE_LEN, 0 },
	  {0xA077, 0xA4,BYTE_LEN, 0 },
	  {0xA078, 0x64,BYTE_LEN, 0 },
	  {0xA079, 0x65,BYTE_LEN, 0 },
	  {0xA07A, 0x30,BYTE_LEN, 0 },
	  {0xA07B, 0x68,BYTE_LEN, 0 },
	  {0xA07C, 0x29,BYTE_LEN, 0 },
	  {0xA07D, 0xCD,BYTE_LEN, 0 },
	  {0xA07E, 0x57,BYTE_LEN, 0 },
	  {0xA07F, 0x20,BYTE_LEN, 0 },
	  {0xA080, 0xE3,BYTE_LEN, 0 },
	  {0xA081, 0x94,BYTE_LEN, 0 },
	  {0xA082, 0xB8,BYTE_LEN, 0 },
	  {0xA083, 0x90,BYTE_LEN, 0 },
	  {0xA084, 0x04,BYTE_LEN, 0 },
	  {0xA085, 0x26,BYTE_LEN, 0 },
	  {0xA086, 0x09,BYTE_LEN, 0 },
	  {0xA087, 0x71,BYTE_LEN, 0 },
	  {0xA088, 0x08,BYTE_LEN, 0 },
	  {0xA089, 0x40,BYTE_LEN, 0 },
	  {0xA08A, 0x04,BYTE_LEN, 0 },
	  {0xA08B, 0x62,BYTE_LEN, 0 },
	  {0xA08C, 0x10,BYTE_LEN, 0 },
	  {0xA08D, 0x86,BYTE_LEN, 0 },
	  {0xA08E, 0x88,BYTE_LEN, 0 },
	  {0xA08F, 0xE4,BYTE_LEN, 0 },
	  {0xA090, 0x25,BYTE_LEN, 0 },
	  {0xA091, 0x4C,BYTE_LEN, 0 },
	  {0xA092, 0x89,BYTE_LEN, 0 },
	  {0xA093, 0x8B,BYTE_LEN, 0 },
	  {0xA094, 0x58,BYTE_LEN, 0 },
	  {0xA095, 0x36,BYTE_LEN, 0 },
	  {0xA096, 0x33,BYTE_LEN, 0 },
	  {0xA097, 0x16,BYTE_LEN, 0 },
	  {0xA098, 0xC9,BYTE_LEN, 0 },
	  {0xA099, 0x40,BYTE_LEN, 0 },
	  {0xA09A, 0x05,BYTE_LEN, 0 },
	  {0xA09B, 0x2E,BYTE_LEN, 0 },
	  {0xA09C, 0x24,BYTE_LEN, 0 },
	  {0xA09D, 0x89,BYTE_LEN, 0 },
	  {0xA09E, 0xC9,BYTE_LEN, 0 },
	  {0xA09F, 0x41,BYTE_LEN, 0 },
	  {0xA0A0, 0x1A,BYTE_LEN, 0 },
	  {0xA0A1, 0x02,BYTE_LEN, 0 },
	  {0xA0A2, 0x10,BYTE_LEN, 0 },
	  {0xA0A3, 0x80,BYTE_LEN, 0 },
	  {0xA0A4, 0x18,BYTE_LEN, 0 },
	  {0xA0A5, 0x44,BYTE_LEN, 0 },
	  {0xA0A6, 0x21,BYTE_LEN, 0 },
	  {0xA0A7, 0x21,BYTE_LEN, 0 },
	  {0xA0A8, 0x79,BYTE_LEN, 0 },
	  {0xA0A9, 0x89,BYTE_LEN, 0 },
	  {0xA0AA, 0x53,BYTE_LEN, 0 },
	  {0xA0AB, 0xE4,BYTE_LEN, 0 },
	  {0xA0AC, 0x62,BYTE_LEN, 0 },
	  {0xA0AD, 0x16,BYTE_LEN, 0 },
	  {0xA0AE, 0xCD,BYTE_LEN, 0 },
	  {0xA0AF, 0xA4,BYTE_LEN, 0 },
	  {0xA0B0, 0x65,BYTE_LEN, 0 },
	  {0xA0B1, 0x33,BYTE_LEN, 0 },
	  {0xA0B2, 0x5B,BYTE_LEN, 0 },
	  {0xA0B3, 0xF9,BYTE_LEN, 0 },
	  {0xA0B4, 0x8B,BYTE_LEN, 0 },
	  {0xA0B5, 0x4D,BYTE_LEN, 0 },
	  {0xA0B6, 0x94,BYTE_LEN, 0 },
	  {0xA0B7, 0xB2,BYTE_LEN, 0 },
	  {0xA0B8, 0x91,BYTE_LEN, 0 },
	  {0xA0B9, 0x91,BYTE_LEN, 0 },
	  {0xA0BA, 0x48,BYTE_LEN, 0 },
	  {0xA0BB, 0xC4,BYTE_LEN, 0 },
	  {0xA0BC, 0x22,BYTE_LEN, 0 },
	  {0xA0BD, 0x1A,BYTE_LEN, 0 },
	  {0xA0BE, 0x11,BYTE_LEN, 0 },
	  {0xA0BF, 0xC9,BYTE_LEN, 0 },
	  {0xA0C0, 0x4C,BYTE_LEN, 0 },
	  {0xA0C1, 0x8E,BYTE_LEN, 0 },
	  {0xA0C2, 0xD2,BYTE_LEN, 0 },
	  {0xA0C3, 0x95,BYTE_LEN, 0 },
	  {0xA0C4, 0xC3,BYTE_LEN, 0 },
	  {0xA0C5, 0xC0,BYTE_LEN, 0 },
	  {0xA0C6, 0x65,BYTE_LEN, 0 },
	  {0xA0C7, 0x35,BYTE_LEN, 0 },
	  {0xA0C8, 0x76,BYTE_LEN, 0 },
	  {0xA0C9, 0x91,BYTE_LEN, 0 },
	  {0xA0CA, 0x0D,BYTE_LEN, 0 },
	  {0xA0CB, 0x5D,BYTE_LEN, 0 },
	  {0xA0CC, 0x50,BYTE_LEN, 0 },
	  {0xA0CD, 0x03,BYTE_LEN, 0 },
	  {0xA0CE, 0x15,BYTE_LEN, 0 },
	  {0xA0CF, 0xB8,BYTE_LEN, 0 },
	  {0xA0D0, 0xEC,BYTE_LEN, 0 },
	  {0xA0D1, 0xC4,BYTE_LEN, 0 },
	  {0xA0D2, 0x29,BYTE_LEN, 0 },
	  {0xA0D3, 0x34,BYTE_LEN, 0 },
	  {0xA0D4, 0x21,BYTE_LEN, 0 },
	  {0xA0D5, 0x8A,BYTE_LEN, 0 },
	  {0xA0D6, 0x4E,BYTE_LEN, 0 },
	  {0xA0D7, 0xA2,BYTE_LEN, 0 },
	  {0xA0D8, 0x12,BYTE_LEN, 0 },
	  {0xA0D9, 0x15,BYTE_LEN, 0 },
	  {0xA0DA, 0xBA,BYTE_LEN, 0 },
	  {0xA0DB, 0xE0,BYTE_LEN, 0 },
	  {0xA0DC, 0x65,BYTE_LEN, 0 },
	  {0xA0DD, 0x35,BYTE_LEN, 0 },
	  {0xA0DE, 0x7C,BYTE_LEN, 0 },
	  {0xA0DF, 0xD1,BYTE_LEN, 0 },
	  {0xA0E0, 0x0D,BYTE_LEN, 0 },
	  {0xA0E1, 0x5D,BYTE_LEN, 0 },
	  {0xA0E2, 0x72,BYTE_LEN, 0 },
	  {0xA0E3, 0x63,BYTE_LEN, 0 },
	  {0xA0E4, 0x98,BYTE_LEN, 0 },
	  {0xA0E5, 0xE4,BYTE_LEN, 0 },
	  {0xA0E6, 0xB8,BYTE_LEN, 0 },
	  {0xA0E7, 0x25,BYTE_LEN, 0 },
	  {0xA0E8, 0x35,BYTE_LEN, 0 },
	  {0xA0E9, 0x61,BYTE_LEN, 0 },
	  {0xA0EA, 0x79,BYTE_LEN, 0 },
	  {0xA0EB, 0xCC,BYTE_LEN, 0 },
	  {0xA0EC, 0x56,BYTE_LEN, 0 },
	  {0xA0ED, 0x10,BYTE_LEN, 0 },
	  {0xA0EE, 0x23,BYTE_LEN, 0 },
	  {0xA0EF, 0x16,BYTE_LEN, 0 },
	  {0xA0F0, 0xCA,BYTE_LEN, 0 },
	  {0xA0F1, 0xCC,BYTE_LEN, 0 },
	  {0xA0F2, 0x85,BYTE_LEN, 0 },
	  {0xA0F3, 0x35,BYTE_LEN, 0 },
	  {0xA0F4, 0x8B,BYTE_LEN, 0 },
	  {0xA0F5, 0x79,BYTE_LEN, 0 },
	  {0xA0F6, 0x4E,BYTE_LEN, 0 },
	  {0xA0F7, 0x5E,BYTE_LEN, 0 },
	  {0xA0F8, 0x86,BYTE_LEN, 0 },
	  {0xA0F9, 0x43,BYTE_LEN, 0 },
	  {0xA0FA, 0x98,BYTE_LEN, 0 },
	  {0xA0FB, 0xEB,BYTE_LEN, 0 },
	  {0xA0FC, 0x70,BYTE_LEN, 0 },
	  {0xA0FD, 0xA6,BYTE_LEN, 0 },
	  {0xA0FE, 0x3E,BYTE_LEN, 0 },
	  {0xA0FF, 0x90,BYTE_LEN, 0 },
	  {0xA100, 0xD1,BYTE_LEN, 0 },
	  {0xA101, 0xCE,BYTE_LEN, 0 },
	  {0xA102, 0x63,BYTE_LEN, 0 },
	  {0xA103, 0xAC,BYTE_LEN, 0 },
	  {0xA104, 0xA3,BYTE_LEN, 0 },
	  {0xA105, 0x98,BYTE_LEN, 0 },
	  {0xA106, 0xE9,BYTE_LEN, 0 },
	  {0xA107, 0x44,BYTE_LEN, 0 },
	  {0xA108, 0x66,BYTE_LEN, 0 },
	  {0xA109, 0x3B,BYTE_LEN, 0 },
	  {0xA10A, 0x98,BYTE_LEN, 0 },
	  {0xA10B, 0x49,BYTE_LEN, 0 },
	  {0xA10C, 0xCF,BYTE_LEN, 0 },
	  {0xA10D, 0x68,BYTE_LEN, 0 },
	  {0xA10E, 0xF8,BYTE_LEN, 0 },
	  {0xA10F, 0xF3,BYTE_LEN, 0 },
	  {0xA110, 0x18,BYTE_LEN, 0 },
	  {0xA111, 0xF0,BYTE_LEN, 0 },
	  {0xA112, 0x88,BYTE_LEN, 0 },
	  {0xA113, 0xA4,BYTE_LEN, 0 },
	  {0xA114, 0x2B,BYTE_LEN, 0 },
	  {0xA115, 0x5D,BYTE_LEN, 0 },
	  {0xA116, 0x79,BYTE_LEN, 0 },
	  {0xA117, 0x4D,BYTE_LEN, 0 },
	  {0xA118, 0x56,BYTE_LEN, 0 },
	  {0xA119, 0x50,BYTE_LEN, 0 },
	  {0xA11A, 0xD3,BYTE_LEN, 0 },
	  {0xA11B, 0x95,BYTE_LEN, 0 },
	  {0xA11C, 0xD5,BYTE_LEN, 0 },
	  {0xA11D, 0x70,BYTE_LEN, 0 },
	  {0xA11E, 0xE5,BYTE_LEN, 0 },
	  {0xA11F, 0x34,BYTE_LEN, 0 },
	  {0xA120, 0x5B,BYTE_LEN, 0 },
	  {0xA121, 0x41,BYTE_LEN, 0 },
	  {0xA122, 0xCD,BYTE_LEN, 0 },
	  {0xA123, 0x56,BYTE_LEN, 0 },
	  {0xA124, 0x60,BYTE_LEN, 0 },
	  {0xA125, 0x73,BYTE_LEN, 0 },
	  {0xA126, 0x16,BYTE_LEN, 0 },
	  {0xA127, 0xDA,BYTE_LEN, 0 },
	  {0xA128, 0xE0,BYTE_LEN, 0 },
	  {0xA129, 0xC4,BYTE_LEN, 0 },
	  {0xA12A, 0x2F,BYTE_LEN, 0 },
	  {0xA12B, 0x12,BYTE_LEN, 0 },
	  {0xA12C, 0xF9,BYTE_LEN, 0 },
	  {0xA12D, 0x48,BYTE_LEN, 0 },
	  {0xA12E, 0x52,BYTE_LEN, 0 },
	  {0xA12F, 0xC2,BYTE_LEN, 0 },
	  {0xA130, 0x92,BYTE_LEN, 0 },
	  {0xA131, 0x14,BYTE_LEN, 0 },
	  {0xA132, 0xAE,BYTE_LEN, 0 },
	  {0xA133, 0x30,BYTE_LEN, 0 },
	  {0xA134, 0x85,BYTE_LEN, 0 },
	  {0xA135, 0x2B,BYTE_LEN, 0 },
	  {0xA136, 0x4F,BYTE_LEN, 0 },
	  {0xA137, 0x01,BYTE_LEN, 0 },
	  {0xA138, 0x4B,BYTE_LEN, 0 },
	  {0xA139, 0x53,BYTE_LEN, 0 },
	  {0xA13A, 0xBE,BYTE_LEN, 0 },
	  {0xA13B, 0xC2,BYTE_LEN, 0 },
	  {0xA13C, 0x94,BYTE_LEN, 0 },
	  {0xA13D, 0xB0,BYTE_LEN, 0 },
	  {0xA13E, 0x60,BYTE_LEN, 0 },
	  {0xA13F, 0x65,BYTE_LEN, 0 },
	  {0xA140, 0x2D,BYTE_LEN, 0 },
	  {0xA141, 0x23,BYTE_LEN, 0 },
	  {0xA142, 0xB1,BYTE_LEN, 0 },
	  {0xA143, 0x09,BYTE_LEN, 0 },
	  {0xA144, 0x5A,BYTE_LEN, 0 },
	  {0xA145, 0x04,BYTE_LEN, 0 },
	  {0xA146, 0x03,BYTE_LEN, 0 },
	  {0xA147, 0x98,BYTE_LEN, 0 },
	  {0xA148, 0xCC,BYTE_LEN, 0 },
	  {0xA149, 0xDC,BYTE_LEN, 0 },
	  {0xA14A, 0xE5,BYTE_LEN, 0 },
	  {0xA14B, 0x31,BYTE_LEN, 0 },
	  {0xA14C, 0x7A,BYTE_LEN, 0 },
	  {0xA14D, 0x69,BYTE_LEN, 0 },
	  {0xA14E, 0x4C,BYTE_LEN, 0 },
	  {0xA14F, 0x5E,BYTE_LEN, 0 },
	  {0xA150, 0x16,BYTE_LEN, 0 },
	  {0xA151, 0xD3,BYTE_LEN, 0 },
	  {0xA152, 0x97,BYTE_LEN, 0 },
	  {0xA153, 0xC8,BYTE_LEN, 0 },
	  {0xA154, 0xF4,BYTE_LEN, 0 },
	  {0xA155, 0xA5,BYTE_LEN, 0 },
	  {0xA156, 0x32,BYTE_LEN, 0 },
	  {0xA157, 0x8A,BYTE_LEN, 0 },
	  {0xA158, 0x09,BYTE_LEN, 0 },
	  {0xA159, 0x8D,BYTE_LEN, 0 },
	  {0xA15A, 0x5D,BYTE_LEN, 0 },
	  {0xA15B, 0x14,BYTE_LEN, 0 },
	  {0xA15C, 0x43,BYTE_LEN, 0 },
	  {0xA15D, 0x15,BYTE_LEN, 0 },
	  {0xA15E, 0xB5,BYTE_LEN, 0 },
	  {0xA15F, 0xB0,BYTE_LEN, 0 },
	  {0xA160, 0x25,BYTE_LEN, 0 },
	  {0xA161, 0x30,BYTE_LEN, 0 },
	  {0xA162, 0x61,BYTE_LEN, 0 },
	  {0xA163, 0x79,BYTE_LEN, 0 },
	  {0xA164, 0x8B,BYTE_LEN, 0 },
	  {0xA165, 0x55,BYTE_LEN, 0 },
	  {0xA166, 0xC4,BYTE_LEN, 0 },
	  {0xA167, 0x22,BYTE_LEN, 0 },
	  {0xA168, 0x95,BYTE_LEN, 0 },
	  {0xA169, 0xAE,BYTE_LEN, 0 },
	  {0xA16A, 0x70,BYTE_LEN, 0 },
	  {0xA16B, 0xA5,BYTE_LEN, 0 },
	  {0xA16C, 0x2C,BYTE_LEN, 0 },
	  {0xA16D, 0x66,BYTE_LEN, 0 },
	  {0xA16E, 0x89,BYTE_LEN, 0 },
	  {0xA16F, 0x4B,BYTE_LEN, 0 },
	  {0xA170, 0x5D,BYTE_LEN, 0 },
	  {0xA171, 0x12,BYTE_LEN, 0 },
	  {0xA172, 0x03,BYTE_LEN, 0 },
	  {0xA173, 0x96,BYTE_LEN, 0 },
	  {0xA174, 0xBA,BYTE_LEN, 0 },
	  {0xA175, 0x60,BYTE_LEN, 0 },
	  {0xA176, 0xE5,BYTE_LEN, 0 },
	  {0xA177, 0x2D,BYTE_LEN, 0 },
	  {0xA178, 0x60,BYTE_LEN, 0 },
	  {0xA179, 0x91,BYTE_LEN, 0 },
	  {0xA17A, 0x8B,BYTE_LEN, 0 },
	  {0xA17B, 0x51,BYTE_LEN, 0 },
	  {0xA17C, 0xA2,BYTE_LEN, 0 },
	  {0xA17D, 0x92,BYTE_LEN, 0 },
	  {0xA17E, 0x13,BYTE_LEN, 0 },
	  {0xA17F, 0xA0,BYTE_LEN, 0 },
	  {0xA180, 0xCC,BYTE_LEN, 0 },
	  {0xA181, 0x24,BYTE_LEN, 0 },
	  {0xA182, 0x27,BYTE_LEN, 0 },
	  {0xA183, 0x3B,BYTE_LEN, 0 },
	  {0xA184, 0x09,BYTE_LEN, 0 },
	  {0xA185, 0x4A,BYTE_LEN, 0 },
	  {0xA186, 0x53,BYTE_LEN, 0 },
	  {0xA187, 0xA6,BYTE_LEN, 0 },
	  {0xA188, 0xA2,BYTE_LEN, 0 },
	  {0xA189, 0x96,BYTE_LEN, 0 },
	  {0xA18A, 0xBB,BYTE_LEN, 0 },
	  {0xA18B, 0x9C,BYTE_LEN, 0 },
	  {0xA18C, 0x05,BYTE_LEN, 0 },
	  {0xA18D, 0x2F,BYTE_LEN, 0 },
	  {0xA18E, 0x4F,BYTE_LEN, 0 },
	  {0xA18F, 0x29,BYTE_LEN, 0 },
	  {0xA190, 0x4B,BYTE_LEN, 0 },
	  {0xA191, 0x53,BYTE_LEN, 0 },
	  {0xA192, 0xB2,BYTE_LEN, 0 },
	  {0xA193, 0x02,BYTE_LEN, 0 },
	  {0xA194, 0x93,BYTE_LEN, 0 },
	  {0xA195, 0x9C,BYTE_LEN, 0 },
	  {0xA196, 0x70,BYTE_LEN, 0 },
	  {0xA197, 0x04,BYTE_LEN, 0 },
	  {0xA198, 0x24,BYTE_LEN, 0 },
	  {0xA199, 0x14,BYTE_LEN, 0 },
	  {0xA19A, 0x99,BYTE_LEN, 0 },
	  {0xA19B, 0x48,BYTE_LEN, 0 },
	  {0xA19C, 0x47,BYTE_LEN, 0 },
	  {0xA19D, 0x38,BYTE_LEN, 0 },
	  {0xA19E, 0x32,BYTE_LEN, 0 },
	  {0xA19F, 0x13,BYTE_LEN, 0 },
	  {0xA1A0, 0x9A,BYTE_LEN, 0 },
	  {0xA1A1, 0x50,BYTE_LEN, 0 },
	  {0xA1A2, 0xA5,BYTE_LEN, 0 },
	  {0xA1A3, 0x2B,BYTE_LEN, 0 },
	  {0xA1A4, 0x5E,BYTE_LEN, 0 },
	  {0xA1A5, 0x69,BYTE_LEN, 0 },
	  {0xA1A6, 0x8B,BYTE_LEN, 0 },
	  {0xA1A7, 0x52,BYTE_LEN, 0 },
	  {0xA1A8, 0xBA,BYTE_LEN, 0 },
	  {0xA1A9, 0x22,BYTE_LEN, 0 },
	  {0xA1AA, 0x14,BYTE_LEN, 0 },
	  {0xA1AB, 0xA7,BYTE_LEN, 0 },
	  {0xA1AC, 0x88,BYTE_LEN, 0 },
	  {0xA1AD, 0xC4,BYTE_LEN, 0 },
	  {0xA1AE, 0x24,BYTE_LEN, 0 },
	  {0xA1AF, 0x09,BYTE_LEN, 0 },
	  {0xA1B0, 0x51,BYTE_LEN, 0 },
	  {0xA1B1, 0x88,BYTE_LEN, 0 },
	  {0xA1B2, 0x40,BYTE_LEN, 0 },
	  {0xA1B3, 0x02,BYTE_LEN, 0 },
	  {0xA1B4, 0x92,BYTE_LEN, 0 },
	  {0xA1B5, 0x90,BYTE_LEN, 0 },
	  {0xA1B6, 0x83,BYTE_LEN, 0 },
	  {0xA1B7, 0x84,BYTE_LEN, 0 },
	  {0xA1B8, 0x64,BYTE_LEN, 0 },
	  {0xA1B9, 0x24,BYTE_LEN, 0 },
	  {0xA1BA, 0x44,BYTE_LEN, 0 },
	  {0xA1BB, 0x79,BYTE_LEN, 0 },
	  {0xA1BC, 0xCA,BYTE_LEN, 0 },
	  {0xA1BD, 0x54,BYTE_LEN, 0 },
	  {0xA1BE, 0xC8,BYTE_LEN, 0 },
	  {0xA1BF, 0xC2,BYTE_LEN, 0 },
	  {0xA1C0, 0x14,BYTE_LEN, 0 },
	  {0xA1C1, 0xB0,BYTE_LEN, 0 },
	  {0xA1C2, 0x04,BYTE_LEN, 0 },
	  {0xA1C3, 0xC5,BYTE_LEN, 0 },
	  {0xA1C4, 0x29,BYTE_LEN, 0 },
	  {0xA1C5, 0x21,BYTE_LEN, 0 },
	  {0xA1C6, 0x21,BYTE_LEN, 0 },
	  {0xA1C7, 0xC9,BYTE_LEN, 0 },
	  {0xA1C8, 0x41,BYTE_LEN, 0 },
	  {0xA1C9, 0x10,BYTE_LEN, 0 },
	  {0xA1CA, 0x02,BYTE_LEN, 0 },
	  {0xA1CB, 0x10,BYTE_LEN, 0 },
	  {0xA1CC, 0x80,BYTE_LEN, 0 },
	  {0xA1CD, 0x1C,BYTE_LEN, 0 },
	  {0xA1CE, 0xE4,BYTE_LEN, 0 },
	  {0xA1CF, 0x20,BYTE_LEN, 0 },
	  {0xA1D0, 0x1F,BYTE_LEN, 0 },
	  {0xA1D1, 0x19,BYTE_LEN, 0 },
	  {0xA1D2, 0x49,BYTE_LEN, 0 },
	  {0xA1D3, 0x51,BYTE_LEN, 0 },
	  {0xA1D4, 0x9A,BYTE_LEN, 0 },
	  {0xA1D5, 0x52,BYTE_LEN, 0 },
	  {0xA1D6, 0x95,BYTE_LEN, 0 },
	  {0xA1D7, 0xB2,BYTE_LEN, 0 },
	  {0xA1D8, 0x50,BYTE_LEN, 0 },
	  {0xA1D9, 0x05,BYTE_LEN, 0 },
	  {0xA1DA, 0x2D,BYTE_LEN, 0 },
	  {0xA1DB, 0x50,BYTE_LEN, 0 },
	  {0xA1DC, 0xD1,BYTE_LEN, 0 },
	  {0xA1DD, 0x4A,BYTE_LEN, 0 },
	  {0xA1DE, 0x4C,BYTE_LEN, 0 },
	  {0xA1DF, 0x6C,BYTE_LEN, 0 },
	  {0xA1E0, 0x92,BYTE_LEN, 0 },
	  {0xA1E1, 0x91,BYTE_LEN, 0 },
	  {0xA1E2, 0x8C,BYTE_LEN, 0 },
	  {0xA1E3, 0x3C,BYTE_LEN, 0 },
	  {0xA1E4, 0xE4,BYTE_LEN, 0 },
	  {0xA1E5, 0x21,BYTE_LEN, 0 },
	  {0xA1E6, 0x16,BYTE_LEN, 0 },
	  {0xA1E7, 0xC1,BYTE_LEN, 0 },
	  {0xA1E8, 0x88,BYTE_LEN, 0 },
	  {0xA1E9, 0x4B,BYTE_LEN, 0 },
	  {0xA1EA, 0x64,BYTE_LEN, 0 },
	  {0xA1EB, 0xE2,BYTE_LEN, 0 },
	  {0xA1EC, 0x94,BYTE_LEN, 0 },
	  {0xA1ED, 0xAD,BYTE_LEN, 0 },
	  {0xA1EE, 0x60,BYTE_LEN, 0 },
	  {0xA1EF, 0xC5,BYTE_LEN, 0 },
	  {0xA1F0, 0x2D,BYTE_LEN, 0 },
	  {0xA1F1, 0x5F,BYTE_LEN, 0 },
	  {0xA1F2, 0x91,BYTE_LEN, 0 },
	  {0xA1F3, 0x4B,BYTE_LEN, 0 },
	  {0xA1F4, 0x59,BYTE_LEN, 0 },
	  {0xA1F5, 0xE4,BYTE_LEN, 0 },
	  {0xA1F6, 0x82,BYTE_LEN, 0 },
	  {0xA1F7, 0x94,BYTE_LEN, 0 },
	  {0xA1F8, 0xA7,BYTE_LEN, 0 },
	  {0xA1F9, 0xDC,BYTE_LEN, 0 },
	  {0xA1FA, 0x44,BYTE_LEN, 0 },
	  {0xA1FB, 0x27,BYTE_LEN, 0 },
	  {0xA1FC, 0x2D,BYTE_LEN, 0 },
	  {0xA1FD, 0x91,BYTE_LEN, 0 },
	  {0xA1FE, 0x89,BYTE_LEN, 0 },
	  {0xA1FF, 0x4C,BYTE_LEN, 0 },
	  {0xA200, 0x72,BYTE_LEN, 0 },
	  {0xA201, 0x22,BYTE_LEN, 0 },
	  {0xA202, 0x14,BYTE_LEN, 0 },
	  {0xA203, 0xA8,BYTE_LEN, 0 },
	  {0xA204, 0x80,BYTE_LEN, 0 },
	  {0xA205, 0xC5,BYTE_LEN, 0 },
	  {0xA206, 0x2E,BYTE_LEN, 0 },
	  {0xA207, 0x5F,BYTE_LEN, 0 },
	  {0xA208, 0xD1,BYTE_LEN, 0 },
	  {0xA209, 0xCB,BYTE_LEN, 0 },
	  {0xA20A, 0x57,BYTE_LEN, 0 },
	  {0xA20B, 0xDE,BYTE_LEN, 0 },
	  {0xA20C, 0x62,BYTE_LEN, 0 },
	  {0xA20D, 0x17,BYTE_LEN, 0 },
	  {0xA20E, 0xC2,BYTE_LEN, 0 },
	  {0xA20F, 0x90,BYTE_LEN, 0 },
	  {0xA210, 0xC5,BYTE_LEN, 0 },
	  {0xA211, 0x2D,BYTE_LEN, 0 },
	  {0xA212, 0x5B,BYTE_LEN, 0 },
	  {0xA213, 0x09,BYTE_LEN, 0 },
	  {0xA214, 0xCB,BYTE_LEN, 0 },
	  {0xA215, 0x54,BYTE_LEN, 0 },
	  {0xA216, 0xB2,BYTE_LEN, 0 },
	  {0xA217, 0x12,BYTE_LEN, 0 },
	  {0xA218, 0x15,BYTE_LEN, 0 },
	  {0xA219, 0xB0,BYTE_LEN, 0 },
	  {0xA21A, 0x80,BYTE_LEN, 0 },
	  {0xA21B, 0x85,BYTE_LEN, 0 },
	  {0xA21C, 0x2E,BYTE_LEN, 0 },
	  {0xA21D, 0x6F,BYTE_LEN, 0 },
	  {0xA21E, 0x79,BYTE_LEN, 0 },
	  {0xA21F, 0xCC,BYTE_LEN, 0 },
	  {0xA220, 0x56,BYTE_LEN, 0 },
	  {0xA221, 0xF4,BYTE_LEN, 0 },
	  {0xA222, 0x02,BYTE_LEN, 0 },
	  {0xA223, 0x97,BYTE_LEN, 0 },
	  {0xA224, 0xC1,BYTE_LEN, 0 },
	  {0xA225, 0x24,BYTE_LEN, 0 },
	  {0xA226, 0xA6,BYTE_LEN, 0 },
	  {0xA227, 0x33,BYTE_LEN, 0 },
	  {0xA228, 0x7E,BYTE_LEN, 0 },
	  {0xA229, 0x89,BYTE_LEN, 0 },
	  {0xA22A, 0x8C,BYTE_LEN, 0 },
	  {0xA22B, 0x5F,BYTE_LEN, 0 },
	  {0xA22C, 0x1E,BYTE_LEN, 0 },
	  {0xA22D, 0xC3,BYTE_LEN, 0 },
	  {0xA22E, 0x17,BYTE_LEN, 0 },
	  {0xA22F, 0xC6,BYTE_LEN, 0 },
	  {0xA230, 0xEC,BYTE_LEN, 0 },
	  {0xA231, 0xA5,BYTE_LEN, 0 },
	  {0xA232, 0x32,BYTE_LEN, 0 },
	  {0xA233, 0x79,BYTE_LEN, 0 },
	  {0xA234, 0xE1,BYTE_LEN, 0 },
	  {0xA235, 0x4C,BYTE_LEN, 0 },
	  {0xA236, 0x61,BYTE_LEN, 0 },
	  {0xA237, 0x4C,BYTE_LEN, 0 },
	  {0xA238, 0x03,BYTE_LEN, 0 },
	  {0xA239, 0x17,BYTE_LEN, 0 },
	  {0xA23A, 0xC7,BYTE_LEN, 0 },
	  {0xA23B, 0x50,BYTE_LEN, 0 },
	  {0xA23C, 0x84,BYTE_LEN, 0 },
	  {0xA23D, 0x24,BYTE_LEN, 0 },
	  {0xA23E, 0x52,BYTE_LEN, 0 },
	  {0xA23F, 0x01,BYTE_LEN, 0 },
	  {0xA240, 0xCB,BYTE_LEN, 0 },
	  {0xA241, 0x53,BYTE_LEN, 0 },
	  {0xA242, 0xBA,BYTE_LEN, 0 },
	  {0xA243, 0x12,BYTE_LEN, 0 },
	  {0xA244, 0x15,BYTE_LEN, 0 },
	  {0xA245, 0xAF,BYTE_LEN, 0 },
	  {0xA246, 0x48,BYTE_LEN, 0 },
	  {0xA247, 0x05,BYTE_LEN, 0 },
	  {0xA248, 0x2C,BYTE_LEN, 0 },
	  {0xA249, 0x4F,BYTE_LEN, 0 },
	  {0xA24A, 0x21,BYTE_LEN, 0 },
	  {0xA24B, 0xCB,BYTE_LEN, 0 },
	  {0xA24C, 0x51,BYTE_LEN, 0 },
	  {0xA24D, 0xC6,BYTE_LEN, 0 },
	  {0xA24E, 0xF2,BYTE_LEN, 0 },
	  {0xA24F, 0x14,BYTE_LEN, 0 },
	  {0xA250, 0xB6,BYTE_LEN, 0 },
	  {0xA251, 0x88,BYTE_LEN, 0 },
	  {0xA252, 0x04,BYTE_LEN, 0 },
	  {0xA253, 0x27,BYTE_LEN, 0 },
 
 // SHD2 CWF TGT575757//
 
	  {0xA254, 0x46,BYTE_LEN, 0 },
	  {0xA255, 0x69,BYTE_LEN, 0 },
	  {0xA256, 0x8C,BYTE_LEN, 0 },
	  {0xA257, 0x61,BYTE_LEN, 0 },
	  {0xA258, 0x08,BYTE_LEN, 0 },
	  {0xA259, 0x63,BYTE_LEN, 0 },
	  {0xA25A, 0x18,BYTE_LEN, 0 },
	  {0xA25B, 0xC3,BYTE_LEN, 0 },
	  {0xA25C, 0x28,BYTE_LEN, 0 },
	  {0xA25D, 0xE6,BYTE_LEN, 0 },
	  {0xA25E, 0x32,BYTE_LEN, 0 },
	  {0xA25F, 0x58,BYTE_LEN, 0 },
	  {0xA260, 0x61,BYTE_LEN, 0 },
	  {0xA261, 0x0D,BYTE_LEN, 0 },
	  {0xA262, 0x71,BYTE_LEN, 0 },
	  {0xA263, 0x6E,BYTE_LEN, 0 },
	  {0xA264, 0x03,BYTE_LEN, 0 },
	  {0xA265, 0x9B,BYTE_LEN, 0 },
	  {0xA266, 0xD6,BYTE_LEN, 0 },
	  {0xA267, 0xD0,BYTE_LEN, 0 },
	  {0xA268, 0xA6,BYTE_LEN, 0 },
	  {0xA269, 0x36,BYTE_LEN, 0 },
	  {0xA26A, 0xC9,BYTE_LEN, 0 },
	  {0xA26B, 0xB9,BYTE_LEN, 0 },
	  {0xA26C, 0x4D,BYTE_LEN, 0 },
	  {0xA26D, 0x65,BYTE_LEN, 0 },
	  {0xA26E, 0x4A,BYTE_LEN, 0 },
	  {0xA26F, 0xA3,BYTE_LEN, 0 },
	  {0xA270, 0x18,BYTE_LEN, 0 },
	  {0xA271, 0xBF,BYTE_LEN, 0 },
	  {0xA272, 0xD8,BYTE_LEN, 0 },
	  {0xA273, 0x25,BYTE_LEN, 0 },
	  {0xA274, 0x30,BYTE_LEN, 0 },
	  {0xA275, 0x8F,BYTE_LEN, 0 },
	  {0xA276, 0x79,BYTE_LEN, 0 },
	  {0xA277, 0x8D,BYTE_LEN, 0 },
	  {0xA278, 0x68,BYTE_LEN, 0 },
	  {0xA279, 0x18,BYTE_LEN, 0 },
	  {0xA27A, 0x83,BYTE_LEN, 0 },
	  {0xA27B, 0x18,BYTE_LEN, 0 },
	  {0xA27C, 0xB2,BYTE_LEN, 0 },
	  {0xA27D, 0x34,BYTE_LEN, 0 },
	  {0xA27E, 0xA5,BYTE_LEN, 0 },
	  {0xA27F, 0x28,BYTE_LEN, 0 },
	  {0xA280, 0x4C,BYTE_LEN, 0 },
	  {0xA281, 0x19,BYTE_LEN, 0 },
	  {0xA282, 0xCB,BYTE_LEN, 0 },
	  {0xA283, 0x64,BYTE_LEN, 0 },
	  {0xA284, 0x36,BYTE_LEN, 0 },
	  {0xA285, 0x13,BYTE_LEN, 0 },
	  {0xA286, 0x18,BYTE_LEN, 0 },
	  {0xA287, 0xB7,BYTE_LEN, 0 },
	  {0xA288, 0x00,BYTE_LEN, 0 },
	  {0xA289, 0x25,BYTE_LEN, 0 },
	  {0xA28A, 0x24,BYTE_LEN, 0 },
	  {0xA28B, 0x17,BYTE_LEN, 0 },
	  {0xA28C, 0x01,BYTE_LEN, 0 },
	  {0xA28D, 0x89,BYTE_LEN, 0 },
	  {0xA28E, 0x4F,BYTE_LEN, 0 },
	  {0xA28F, 0xE0,BYTE_LEN, 0 },
	  {0xA290, 0x92,BYTE_LEN, 0 },
	  {0xA291, 0x18,BYTE_LEN, 0 },
	  {0xA292, 0xBD,BYTE_LEN, 0 },
	  {0xA293, 0x84,BYTE_LEN, 0 },
	  {0xA294, 0x65,BYTE_LEN, 0 },
	  {0xA295, 0x25,BYTE_LEN, 0 },
	  {0xA296, 0x0C,BYTE_LEN, 0 },
	  {0xA297, 0x11,BYTE_LEN, 0 },
	  {0xA298, 0x88,BYTE_LEN, 0 },
	  {0xA299, 0x42,BYTE_LEN, 0 },
	  {0xA29A, 0x50,BYTE_LEN, 0 },
	  {0xA29B, 0xF2,BYTE_LEN, 0 },
	  {0xA29C, 0x95,BYTE_LEN, 0 },
	  {0xA29D, 0xC1,BYTE_LEN, 0 },
	  {0xA29E, 0xEC,BYTE_LEN, 0 },
	  {0xA29F, 0x25,BYTE_LEN, 0 },
	  {0xA2A0, 0x2C,BYTE_LEN, 0 },
	  {0xA2A1, 0x2B,BYTE_LEN, 0 },
	  {0xA2A2, 0x59,BYTE_LEN, 0 },
	  {0xA2A3, 0x08,BYTE_LEN, 0 },
	  {0xA2A4, 0x40,BYTE_LEN, 0 },
	  {0xA2A5, 0x12,BYTE_LEN, 0 },
	  {0xA2A6, 0x82,BYTE_LEN, 0 },
	  {0xA2A7, 0x92,BYTE_LEN, 0 },
	  {0xA2A8, 0xB0,BYTE_LEN, 0 },
	  {0xA2A9, 0x04,BYTE_LEN, 0 },
	  {0xA2AA, 0x66,BYTE_LEN, 0 },
	  {0xA2AB, 0x30,BYTE_LEN, 0 },
	  {0xA2AC, 0x6C,BYTE_LEN, 0 },
	  {0xA2AD, 0x01,BYTE_LEN, 0 },
	  {0xA2AE, 0x8A,BYTE_LEN, 0 },
	  {0xA2AF, 0x47,BYTE_LEN, 0 },
	  {0xA2B0, 0x26,BYTE_LEN, 0 },
	  {0xA2B1, 0xD2,BYTE_LEN, 0 },
	  {0xA2B2, 0x11,BYTE_LEN, 0 },
	  {0xA2B3, 0x9E,BYTE_LEN, 0 },
	  {0xA2B4, 0xCC,BYTE_LEN, 0 },
	  {0xA2B5, 0xA5,BYTE_LEN, 0 },
	  {0xA2B6, 0x31,BYTE_LEN, 0 },
	  {0xA2B7, 0x95,BYTE_LEN, 0 },
	  {0xA2B8, 0x71,BYTE_LEN, 0 },
	  {0xA2B9, 0x0C,BYTE_LEN, 0 },
	  {0xA2BA, 0x58,BYTE_LEN, 0 },
	  {0xA2BB, 0x84,BYTE_LEN, 0 },
	  {0xA2BC, 0x92,BYTE_LEN, 0 },
	  {0xA2BD, 0x13,BYTE_LEN, 0 },
	  {0xA2BE, 0xA2,BYTE_LEN, 0 },
	  {0xA2BF, 0x88,BYTE_LEN, 0 },
	  {0xA2C0, 0xE5,BYTE_LEN, 0 },
	  {0xA2C1, 0x31,BYTE_LEN, 0 },
	  {0xA2C2, 0x9D,BYTE_LEN, 0 },
	  {0xA2C3, 0xD1,BYTE_LEN, 0 },
	  {0xA2C4, 0x8C,BYTE_LEN, 0 },
	  {0xA2C5, 0x6A,BYTE_LEN, 0 },
	  {0xA2C6, 0x1C,BYTE_LEN, 0 },
	  {0xA2C7, 0x93,BYTE_LEN, 0 },
	  {0xA2C8, 0x97,BYTE_LEN, 0 },
	  {0xA2C9, 0xB9,BYTE_LEN, 0 },
	  {0xA2CA, 0xF4,BYTE_LEN, 0 },
	  {0xA2CB, 0x25,BYTE_LEN, 0 },
	  {0xA2CC, 0x32,BYTE_LEN, 0 },
	  {0xA2CD, 0xAF,BYTE_LEN, 0 },
	  {0xA2CE, 0x09,BYTE_LEN, 0 },
	  {0xA2CF, 0x8D,BYTE_LEN, 0 },
	  {0xA2D0, 0x6D,BYTE_LEN, 0 },
	  {0xA2D1, 0xA0,BYTE_LEN, 0 },
	  {0xA2D2, 0xA3,BYTE_LEN, 0 },
	  {0xA2D3, 0x1B,BYTE_LEN, 0 },
	  {0xA2D4, 0xDB,BYTE_LEN, 0 },
	  {0xA2D5, 0xD0,BYTE_LEN, 0 },
	  {0xA2D6, 0x06,BYTE_LEN, 0 },
	  {0xA2D7, 0x37,BYTE_LEN, 0 },
	  {0xA2D8, 0xC5,BYTE_LEN, 0 },
	  {0xA2D9, 0xA1,BYTE_LEN, 0 },
	  {0xA2DA, 0x0E,BYTE_LEN, 0 },
	  {0xA2DB, 0x6F,BYTE_LEN, 0 },
	  {0xA2DC, 0x9A,BYTE_LEN, 0 },
	  {0xA2DD, 0xD2,BYTE_LEN, 0 },
	  {0xA2DE, 0x18,BYTE_LEN, 0 },
	  {0xA2DF, 0xC4,BYTE_LEN, 0 },
	  {0xA2E0, 0x20,BYTE_LEN, 0 },
	  {0xA2E1, 0xE6,BYTE_LEN, 0 },
	  {0xA2E2, 0x30,BYTE_LEN, 0 },
	  {0xA2E3, 0x8B,BYTE_LEN, 0 },
	  {0xA2E4, 0x79,BYTE_LEN, 0 },
	  {0xA2E5, 0x0C,BYTE_LEN, 0 },
	  {0xA2E6, 0x64,BYTE_LEN, 0 },
	  {0xA2E7, 0xD2,BYTE_LEN, 0 },
	  {0xA2E8, 0x02,BYTE_LEN, 0 },
	  {0xA2E9, 0x00,BYTE_LEN, 0 },
	  {0xA2EA, 0x00,BYTE_LEN, 0 },
	  {0xA2EB, 0x00,BYTE_LEN, 0 },
	  {0xA2EC, 0x00,BYTE_LEN, 0 },
	  {0xA2ED, 0x00,BYTE_LEN, 0 },
 
 
 
 //SHD3 A+TLD TGT575757//
	  {0xA2EE, 0x55,BYTE_LEN, 0 },
	  {0xA2EF, 0x39,BYTE_LEN, 0 },
	  {0xA2F0, 0xCD,BYTE_LEN, 0 },
	  {0xA2F1, 0x69,BYTE_LEN, 0 },
	  {0xA2F2, 0x48,BYTE_LEN, 0 },
	  {0xA2F3, 0xA3,BYTE_LEN, 0 },
	  {0xA2F4, 0x1A,BYTE_LEN, 0 },
	  {0xA2F5, 0xD3,BYTE_LEN, 0 },
	  {0xA2F6, 0xA4,BYTE_LEN, 0 },
	  {0xA2F7, 0xE6,BYTE_LEN, 0 },
	  {0xA2F8, 0x36,BYTE_LEN, 0 },
	  {0xA2F9, 0x71,BYTE_LEN, 0 },
	  {0xA2FA, 0x69,BYTE_LEN, 0 },
	  {0xA2FB, 0x4E,BYTE_LEN, 0 },
	  {0xA2FC, 0x7A,BYTE_LEN, 0 },
	  {0xA2FD, 0xAE,BYTE_LEN, 0 },
	  {0xA2FE, 0x03,BYTE_LEN, 0 },
	  {0xA2FF, 0x9D,BYTE_LEN, 0 },
	  {0xA300, 0xE5,BYTE_LEN, 0 },
	  {0xA301, 0x4C,BYTE_LEN, 0 },
	  {0xA302, 0x47,BYTE_LEN, 0 },
	  {0xA303, 0x3B,BYTE_LEN, 0 },
	  {0xA304, 0xEE,BYTE_LEN, 0 },
	  {0xA305, 0xC9,BYTE_LEN, 0 },
	  {0xA306, 0xCE,BYTE_LEN, 0 },
	  {0xA307, 0x6C,BYTE_LEN, 0 },
	  {0xA308, 0x88,BYTE_LEN, 0 },
	  {0xA309, 0x33,BYTE_LEN, 0 },
	  {0xA30A, 0x1A,BYTE_LEN, 0 },
	  {0xA30B, 0xC9,BYTE_LEN, 0 },
	  {0xA30C, 0x20,BYTE_LEN, 0 },
	  {0xA30D, 0xC6,BYTE_LEN, 0 },
	  {0xA30E, 0x32,BYTE_LEN, 0 },
	  {0xA30F, 0xA9,BYTE_LEN, 0 },
	  {0xA310, 0x81,BYTE_LEN, 0 },
	  {0xA311, 0x0E,BYTE_LEN, 0 },
	  {0xA312, 0x71,BYTE_LEN, 0 },
	  {0xA313, 0x54,BYTE_LEN, 0 },
	  {0xA314, 0x23,BYTE_LEN, 0 },
	  {0xA315, 0x9A,BYTE_LEN, 0 },
	  {0xA316, 0xB9,BYTE_LEN, 0 },
	  {0xA317, 0x60,BYTE_LEN, 0 },
	  {0xA318, 0xA5,BYTE_LEN, 0 },
	  {0xA319, 0x29,BYTE_LEN, 0 },
	  {0xA31A, 0x57,BYTE_LEN, 0 },
	  {0xA31B, 0xA9,BYTE_LEN, 0 },
	  {0xA31C, 0x4B,BYTE_LEN, 0 },
	  {0xA31D, 0x6B,BYTE_LEN, 0 },
	  {0xA31E, 0x76,BYTE_LEN, 0 },
	  {0xA31F, 0xD3,BYTE_LEN, 0 },
	  {0xA320, 0x99,BYTE_LEN, 0 },
	  {0xA321, 0xC0,BYTE_LEN, 0 },
	  {0xA322, 0x24,BYTE_LEN, 0 },
	  {0xA323, 0xC5,BYTE_LEN, 0 },
	  {0xA324, 0x24,BYTE_LEN, 0 },
	  {0xA325, 0x1A,BYTE_LEN, 0 },
	  {0xA326, 0x29,BYTE_LEN, 0 },
	  {0xA327, 0x49,BYTE_LEN, 0 },
	  {0xA328, 0x52,BYTE_LEN, 0 },
	  {0xA329, 0x08,BYTE_LEN, 0 },
	  {0xA32A, 0x83,BYTE_LEN, 0 },
	  {0xA32B, 0x9A,BYTE_LEN, 0 },
	  {0xA32C, 0xCA,BYTE_LEN, 0 },
	  {0xA32D, 0xC4,BYTE_LEN, 0 },
	  {0xA32E, 0x25,BYTE_LEN, 0 },
	  {0xA32F, 0x26,BYTE_LEN, 0 },
	  {0xA330, 0x0E,BYTE_LEN, 0 },
	  {0xA331, 0x09,BYTE_LEN, 0 },
	  {0xA332, 0xC8,BYTE_LEN, 0 },
	  {0xA333, 0x42,BYTE_LEN, 0 },
	  {0xA334, 0x62,BYTE_LEN, 0 },
	  {0xA335, 0x22,BYTE_LEN, 0 },
	  {0xA336, 0x17,BYTE_LEN, 0 },
	  {0xA337, 0xCF,BYTE_LEN, 0 },
	  {0xA338, 0x58,BYTE_LEN, 0 },
	  {0xA339, 0x26,BYTE_LEN, 0 },
	  {0xA33A, 0x2E,BYTE_LEN, 0 },
	  {0xA33B, 0x33,BYTE_LEN, 0 },
	  {0xA33C, 0x61,BYTE_LEN, 0 },
	  {0xA33D, 0x08,BYTE_LEN, 0 },
	  {0xA33E, 0x40,BYTE_LEN, 0 },
	  {0xA33F, 0x16,BYTE_LEN, 0 },
	  {0xA340, 0x12,BYTE_LEN, 0 },
	  {0xA341, 0x13,BYTE_LEN, 0 },
	  {0xA342, 0xBA,BYTE_LEN, 0 },
	  {0xA343, 0x7C,BYTE_LEN, 0 },
	  {0xA344, 0x26,BYTE_LEN, 0 },
	  {0xA345, 0x34,BYTE_LEN, 0 },
	  {0xA346, 0x82,BYTE_LEN, 0 },
	  {0xA347, 0x51,BYTE_LEN, 0 },
	  {0xA348, 0xCA,BYTE_LEN, 0 },
	  {0xA349, 0x48,BYTE_LEN, 0 },
	  {0xA34A, 0x2E,BYTE_LEN, 0 },
	  {0xA34B, 0x32,BYTE_LEN, 0 },
	  {0xA34C, 0x12,BYTE_LEN, 0 },
	  {0xA34D, 0xA5,BYTE_LEN, 0 },
	  {0xA34E, 0x28,BYTE_LEN, 0 },
	  {0xA34F, 0xE6,BYTE_LEN, 0 },
	  {0xA350, 0x35,BYTE_LEN, 0 },
	  {0xA351, 0xB3,BYTE_LEN, 0 },
	  {0xA352, 0x49,BYTE_LEN, 0 },
	  {0xA353, 0x8D,BYTE_LEN, 0 },
	  {0xA354, 0x5C,BYTE_LEN, 0 },
	  {0xA355, 0xA0,BYTE_LEN, 0 },
	  {0xA356, 0x62,BYTE_LEN, 0 },
	  {0xA357, 0x94,BYTE_LEN, 0 },
	  {0xA358, 0xA9,BYTE_LEN, 0 },
	  {0xA359, 0xDC,BYTE_LEN, 0 },
	  {0xA35A, 0x05,BYTE_LEN, 0 },
	  {0xA35B, 0x36,BYTE_LEN, 0 },
	  {0xA35C, 0xC0,BYTE_LEN, 0 },
	  {0xA35D, 0xF9,BYTE_LEN, 0 },
	  {0xA35E, 0x0D,BYTE_LEN, 0 },
	  {0xA35F, 0x73,BYTE_LEN, 0 },
	  {0xA360, 0x50,BYTE_LEN, 0 },
	  {0xA361, 0x03,BYTE_LEN, 0 },
	  {0xA362, 0x19,BYTE_LEN, 0 },
	  {0xA363, 0xC4,BYTE_LEN, 0 },
	  {0xA364, 0x50,BYTE_LEN, 0 },
	  {0xA365, 0xC6,BYTE_LEN, 0 },
	  {0xA366, 0x35,BYTE_LEN, 0 },
	  {0xA367, 0xD6,BYTE_LEN, 0 },
	  {0xA368, 0x59,BYTE_LEN, 0 },
	  {0xA369, 0x8E,BYTE_LEN, 0 },
	  {0xA36A, 0x75,BYTE_LEN, 0 },
	  {0xA36B, 0xE8,BYTE_LEN, 0 },
	  {0xA36C, 0xF3,BYTE_LEN, 0 },
	  {0xA36D, 0x1D,BYTE_LEN, 0 },
	  {0xA36E, 0xEC,BYTE_LEN, 0 },
	  {0xA36F, 0x50,BYTE_LEN, 0 },
	  {0xA370, 0xA7,BYTE_LEN, 0 },
	  {0xA371, 0x3B,BYTE_LEN, 0 },
	  {0xA372, 0xEA,BYTE_LEN, 0 },
	  {0xA373, 0x01,BYTE_LEN, 0 },
	  {0xA374, 0x10,BYTE_LEN, 0 },
	  {0xA375, 0x79,BYTE_LEN, 0 },
	  {0xA376, 0xC6,BYTE_LEN, 0 },
	  {0xA377, 0x22,BYTE_LEN, 0 },
	  {0xA378, 0x1B,BYTE_LEN, 0 },
	  {0xA379, 0xD4,BYTE_LEN, 0 },
	  {0xA37A, 0xBC,BYTE_LEN, 0 },
	  {0xA37B, 0x86,BYTE_LEN, 0 },
	  {0xA37C, 0x35,BYTE_LEN, 0 },
	  {0xA37D, 0xAD,BYTE_LEN, 0 },
	  {0xA37E, 0x89,BYTE_LEN, 0 },
	  {0xA37F, 0xCD,BYTE_LEN, 0 },
	  {0xA380, 0x6D,BYTE_LEN, 0 },
	  {0xA381, 0x06,BYTE_LEN, 0 },
	  {0xA382, 0x03,BYTE_LEN, 0 },
	  {0xA383, 0x00,BYTE_LEN, 0 },
	  {0xA384, 0x00,BYTE_LEN, 0 },
	  {0xA385, 0x00,BYTE_LEN, 0 },
	  {0xA386, 0x00,BYTE_LEN, 0 },
	  {0xA387, 0x00,BYTE_LEN, 0 },
	  {0xA388, 0x29,BYTE_LEN, 0 },
	  {0xA389, 0x09,BYTE_LEN, 0 },
	  {0xA38A, 0x0B,BYTE_LEN, 0 },
	  {0xA38B, 0x57,BYTE_LEN, 0 },
	  {0xA38C, 0xBE,BYTE_LEN, 0 },
	  {0xA38D, 0xB2,BYTE_LEN, 0 },
	  {0xA38E, 0x15,BYTE_LEN, 0 },
	  {0xA38F, 0xAD,BYTE_LEN, 0 },
	  {0xA390, 0x68,BYTE_LEN, 0 },
	  {0xA391, 0xC5,BYTE_LEN, 0 },
	  {0xA392, 0x2C,BYTE_LEN, 0 },
	  {0xA393, 0x3B,BYTE_LEN, 0 },
	  {0xA394, 0xE9,BYTE_LEN, 0 },
	  {0xA395, 0x4B,BYTE_LEN, 0 },
	  {0xA396, 0x64,BYTE_LEN, 0 },
	  {0xA397, 0x08,BYTE_LEN, 0 },
	  {0xA398, 0x43,BYTE_LEN, 0 },
	  {0xA399, 0x18,BYTE_LEN, 0 },
	  {0xA39A, 0xC0,BYTE_LEN, 0 },
	  {0xA39B, 0x0C,BYTE_LEN, 0 },
	  {0xA39C, 0x46,BYTE_LEN, 0 },
	  {0xA39D, 0x30,BYTE_LEN, 0 },
	  {0xA39E, 0x98,BYTE_LEN, 0 },
	  {0xA39F, 0x39,BYTE_LEN, 0 },
	  {0xA3A0, 0x4C,BYTE_LEN, 0 },
	  {0xA3A1, 0x59,BYTE_LEN, 0 },
	  {0xA3A2, 0xF2,BYTE_LEN, 0 },
	  {0xA3A3, 0xB2,BYTE_LEN, 0 },
	  {0xA3A4, 0x96,BYTE_LEN, 0 },
	  {0xA3A5, 0xAE,BYTE_LEN, 0 },
	  {0xA3A6, 0x54,BYTE_LEN, 0 },
	  {0xA3A7, 0x25,BYTE_LEN, 0 },
	  {0xA3A8, 0x2C,BYTE_LEN, 0 },
	  {0xA3A9, 0x6D,BYTE_LEN, 0 },
	  {0xA3AA, 0xE1,BYTE_LEN, 0 },
	  {0xA3AB, 0xCB,BYTE_LEN, 0 },
	  {0xA3AC, 0x5A,BYTE_LEN, 0 },
	  {0xA3AD, 0xC8,BYTE_LEN, 0 },
	  {0xA3AE, 0xB2,BYTE_LEN, 0 },
	  {0xA3AF, 0x96,BYTE_LEN, 0 },
	  {0xA3B0, 0xA6,BYTE_LEN, 0 },
	  {0xA3B1, 0xF0,BYTE_LEN, 0 },
	  {0xA3B2, 0x84,BYTE_LEN, 0 },
	  {0xA3B3, 0x26,BYTE_LEN, 0 },
	  {0xA3B4, 0x3D,BYTE_LEN, 0 },
	  {0xA3B5, 0x91,BYTE_LEN, 0 },
	  {0xA3B6, 0x8A,BYTE_LEN, 0 },
	  {0xA3B7, 0x5C,BYTE_LEN, 0 },
	  {0xA3B8, 0xE2,BYTE_LEN, 0 },
	  {0xA3B9, 0x92,BYTE_LEN, 0 },
	  {0xA3BA, 0x95,BYTE_LEN, 0 },
	  {0xA3BB, 0xAA,BYTE_LEN, 0 },
	  {0xA3BC, 0xD0,BYTE_LEN, 0 },
	  {0xA3BD, 0xE4,BYTE_LEN, 0 },
	  {0xA3BE, 0x23,BYTE_LEN, 0 },
	  {0xA3BF, 0x16,BYTE_LEN, 0 },
	  {0xA3C0, 0xF1,BYTE_LEN, 0 },
	  {0xA3C1, 0x48,BYTE_LEN, 0 },
	  {0xA3C2, 0x4D,BYTE_LEN, 0 },
	  {0xA3C3, 0xB2,BYTE_LEN, 0 },
	  {0xA3C4, 0x52,BYTE_LEN, 0 },
	  {0xA3C5, 0x96,BYTE_LEN, 0 },
	  {0xA3C6, 0xA9,BYTE_LEN, 0 },
	  {0xA3C7, 0x20,BYTE_LEN, 0 },
	  {0xA3C8, 0x05,BYTE_LEN, 0 },
	  {0xA3C9, 0x25,BYTE_LEN, 0 },
	  {0xA3CA, 0x0B,BYTE_LEN, 0 },
	  {0xA3CB, 0x19,BYTE_LEN, 0 },
	  {0xA3CC, 0x48,BYTE_LEN, 0 },
	  {0xA3CD, 0x42,BYTE_LEN, 0 },
	  {0xA3CE, 0x42,BYTE_LEN, 0 },
	  {0xA3CF, 0x42,BYTE_LEN, 0 },
	  {0xA3D0, 0x14,BYTE_LEN, 0 },
	  {0xA3D1, 0xAB,BYTE_LEN, 0 },
	  {0xA3D2, 0x4C,BYTE_LEN, 0 },
	  {0xA3D3, 0xC5,BYTE_LEN, 0 },
	  {0xA3D4, 0x28,BYTE_LEN, 0 },
	  {0xA3D5, 0x26,BYTE_LEN, 0 },
	  {0xA3D6, 0x39,BYTE_LEN, 0 },
	  {0xA3D7, 0x08,BYTE_LEN, 0 },
	  {0xA3D8, 0x40,BYTE_LEN, 0 },
	  {0xA3D9, 0x0C,BYTE_LEN, 0 },
	  {0xA3DA, 0x02,BYTE_LEN, 0 },
	  {0xA3DB, 0x12,BYTE_LEN, 0 },
	  {0xA3DC, 0xA5,BYTE_LEN, 0 },
	  {0xA3DD, 0x78,BYTE_LEN, 0 },
	  {0xA3DE, 0xE5,BYTE_LEN, 0 },
	  {0xA3DF, 0x2B,BYTE_LEN, 0 },
	  {0xA3E0, 0x56,BYTE_LEN, 0 },
	  {0xA3E1, 0xB9,BYTE_LEN, 0 },
	  {0xA3E2, 0x09,BYTE_LEN, 0 },
	  {0xA3E3, 0x47,BYTE_LEN, 0 },
	  {0xA3E4, 0x20,BYTE_LEN, 0 },
	  {0xA3E5, 0x52,BYTE_LEN, 0 },
	  {0xA3E6, 0x91,BYTE_LEN, 0 },
	  {0xA3E7, 0x98,BYTE_LEN, 0 },
	  {0xA3E8, 0x4C,BYTE_LEN, 0 },
	  {0xA3E9, 0x05,BYTE_LEN, 0 },
	  {0xA3EA, 0x2C,BYTE_LEN, 0 },
	  {0xA3EB, 0x68,BYTE_LEN, 0 },
	  {0xA3EC, 0x69,BYTE_LEN, 0 },
	  {0xA3ED, 0x4B,BYTE_LEN, 0 },
	  {0xA3EE, 0x53,BYTE_LEN, 0 },
	  {0xA3EF, 0x74,BYTE_LEN, 0 },
	  {0xA3F0, 0xC2,BYTE_LEN, 0 },
	  {0xA3F1, 0x92,BYTE_LEN, 0 },
	  {0xA3F2, 0x98,BYTE_LEN, 0 },
	  {0xA3F3, 0x10,BYTE_LEN, 0 },
	  {0xA3F4, 0x05,BYTE_LEN, 0 },
	  {0xA3F5, 0x2D,BYTE_LEN, 0 },
	  {0xA3F6, 0x6B,BYTE_LEN, 0 },
	  {0xA3F7, 0x69,BYTE_LEN, 0 },
	  {0xA3F8, 0xCB,BYTE_LEN, 0 },
	  {0xA3F9, 0x5F,BYTE_LEN, 0 },
	  {0xA3FA, 0xD2,BYTE_LEN, 0 },
	  {0xA3FB, 0xF2,BYTE_LEN, 0 },
	  {0xA3FC, 0x95,BYTE_LEN, 0 },
	  {0xA3FD, 0xAA,BYTE_LEN, 0 },
	  {0xA3FE, 0x40,BYTE_LEN, 0 },
	  {0xA3FF, 0xC5,BYTE_LEN, 0 },
	  {0xA400, 0x2C,BYTE_LEN, 0 },
	  {0xA401, 0x78,BYTE_LEN, 0 },
	  {0xA402, 0x61,BYTE_LEN, 0 },
	  {0xA403, 0x4B,BYTE_LEN, 0 },
	  {0xA404, 0x5F,BYTE_LEN, 0 },
	  {0xA405, 0x22,BYTE_LEN, 0 },
	  {0xA406, 0x03,BYTE_LEN, 0 },
	  {0xA407, 0x18,BYTE_LEN, 0 },
	  {0xA408, 0xC0,BYTE_LEN, 0 },
	  {0xA409, 0xF8,BYTE_LEN, 0 },
	  {0xA40A, 0xA5,BYTE_LEN, 0 },
	  {0xA40B, 0x2F,BYTE_LEN, 0 },
	  {0xA40C, 0x7E,BYTE_LEN, 0 },
	  {0xA40D, 0x79,BYTE_LEN, 0 },
	  {0xA40E, 0x8C,BYTE_LEN, 0 },
	  {0xA40F, 0x5F,BYTE_LEN, 0 },
	  {0xA410, 0x56,BYTE_LEN, 0 },
	  {0xA411, 0x22,BYTE_LEN, 0 },
	  {0xA412, 0x96,BYTE_LEN, 0 },
	  {0xA413, 0xAE,BYTE_LEN, 0 },
	  {0xA414, 0x70,BYTE_LEN, 0 },
	  {0xA415, 0xA5,BYTE_LEN, 0 },
	  {0xA416, 0x2B,BYTE_LEN, 0 },
	  {0xA417, 0x5A,BYTE_LEN, 0 },
	  {0xA418, 0xA9,BYTE_LEN, 0 },
	  {0xA419, 0xCA,BYTE_LEN, 0 },
	  {0xA41A, 0x57,BYTE_LEN, 0 },
	  {0xA41B, 0x72,BYTE_LEN, 0 },
	  {0xA41C, 0x02,BYTE_LEN, 0 },
	  {0xA41D, 0x00,BYTE_LEN, 0 },
	  {0xA41E, 0x00,BYTE_LEN, 0 },
	  {0xA41F, 0x00,BYTE_LEN, 0 },
	  {0xA420, 0x00,BYTE_LEN, 0 },
	  {0xA421, 0x00,BYTE_LEN, 0 },
	  /*MTD-MM-SL-ColorShading-00*}*/


        ////////////////////////////////////////
        //// Cat. : USERCTRL (PICT related) ////
        ////////////////////////////////////////

        {0x0068, 0x5F, BYTE_LEN, 0 },// SHD_EN
        {0x0105, 0x40, BYTE_LEN, 0 },// PICT1_SN1

};

/*MM-UW-support AF+++*/
struct isx006_i2c_reg_conf isx006_preload3_settings[] = {
	 ////////////////////////////////////////
	 /////////// Cat. : PICT_GAIN ///////////
	 ////////////////////////////////////////
	{0x5842, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_0
	{0x5843, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_1
	{0x5844, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_2
	{0x5845, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_3
	{0x5846, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_4
	{0x5847, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_5
	{0x5848, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_6
	{0x5849, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_7
	{0x584A, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_8
	{0x584B, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_9
	{0x584C, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_10
	{0x584D, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_11
	{0x584E, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_12
	{0x584F, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_13
	{0x5850, 0x00, BYTE_LEN, 0 },// Gain-linked mode target setting0: AGC gain coordination (including shutter interpolation), 1: AGC gain interpolation (not including gain interpolation), 2: AE scale coordination, 3: Reference scale coordination, 4: Dark level coordination
	{0x5858, 0x0A2A, WORD_LEN, 0 },// Gain coordination threshold value setting  Low brightness/High gain side
	{0x585A, 0x0396, WORD_LEN, 0 },// Gain coordination threshold value setting  Medium brightness/Medium gain side
	{0x585C, 0x0000, WORD_LEN, 0 },// Gain coordination threshold value setting  Higih brightness/Low gain side
	{0x5882, 0x0B29, WORD_LEN, 0 },// Gain coordination threshold value setting  Low brightness/High gain side
	{0x5884, 0x0100, WORD_LEN, 0 },// Gain coordination threshold value setting  Medium brightness/Medium gain side
	{0x5886, 0x0000, WORD_LEN, 0 },// Gain coordination threshold value setting  Higih brightness/Low gain side
	{0x5888, 0x0024, WORD_LEN, 0 },// Luminance threshold value A setting value
	{0x588A, 0x000B, WORD_LEN, 0 },// Luminance threshold value B setting value
	{0x588C, 0x000A, WORD_LEN, 0 },// Luminance threshold value C setting value
	{0x588E, 0x0030, WORD_LEN, 0 },// Chroma threshold value A setting value
	{0x5890, 0x0028, WORD_LEN, 0 },// Chroma threshold value B setting value
	{0x5892, 0x0020, WORD_LEN, 0 },// Chroma threshold value C setting value
	{0x5894, 0x0004, WORD_LEN, 0 },// Low-range Apcon positive-side coring range (X-coordinate) for threshold value A
	{0x589A, 0x0008, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value A
	{0x589C, 0x0012, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value B
	{0x589E, 0x0012, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value C
	{0x58A6, 0x0004, WORD_LEN, 0 },// Low-range Apcon negative-side coring range (X-coordinate) for threshold value A
	{0x58AC, 0x0008, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value A
	{0x58AE, 0x0012, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value B
	{0x58B0, 0x0012, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value C
	{0x58B8, 0x0001, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value A
	{0x58BA, 0x0001, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value B
	{0x58BC, 0x0000, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value C
	{0x58BE, 0x0004, WORD_LEN, 0 },// Middle-range Apcon positive-side 1st contact point X-coordinate for threshold value A
	{0x58C0, 0x0005, WORD_LEN, 0 },// Middle-range Apcon positive-side 1st contact point X-coordinate for threshold value B
	{0x58CA, 0x0001, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value A
	{0x58CC, 0x0001, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value B
	{0x58CE, 0x0000, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value C
	{0x58D0, 0x0004, WORD_LEN, 0 },// Middle-range Apcon negative-side 1st contact point X-coordinate for threshold value A
	{0x58D4, 0x0004, WORD_LEN, 0 },// Middle-range Apcon negative-side 1st contact point X-coordinate for threshold value C
	{0x58DC, 0x000A, WORD_LEN, 0 },// High-range Apcon positive-side coring range (X-coordinate) for threshold value A
	{0x58E2, 0x000E, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value A
	{0x58E4, 0x000C, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value B
	{0x58E6, 0x000A, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value C
	{0x58EE, 0x000A, WORD_LEN, 0 },// High-range Apcon negative-side coring range (X-coordinate) for threshold value A
	{0x58F2, 0x0005, WORD_LEN, 0 },// High-range Apcon negative-side coring range (X-coordinate) for threshold value C
	{0x58F4, 0x000E, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value A
	{0x58F6, 0x000C, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value B
	{0x58F8, 0x000D, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value C
	{0x5906, 0x015E, WORD_LEN, 0 },// Threshold value A, low-range Apcon 2nd contact point X-coordinate
	{0x5908, 0x015E, WORD_LEN, 0 },// Threshold value B, low-range Apcon 2nd contact point X-coordinate
	{0x590A, 0x015E, WORD_LEN, 0 },// Threshold value C, low-range Apcon 2nd contact point X-coordinate
	{0x590C, 0x0226, WORD_LEN, 0 },// Threshold value A, low-range Apcon 3rd contact point X-coordinate
	{0x590E, 0x0226, WORD_LEN, 0 },// Threshold value B, low-range Apcon 3rd contact point X-coordinate
	{0x5910, 0x0226, WORD_LEN, 0 },// Threshold value C, low-range Apcon 3rd contact point X-coordinate
	{0x591E, 0x0003, WORD_LEN, 0 },// Threshold value A, Clip value from low-range Apcon 4th contact point and after
	{0x5920, 0x0004, WORD_LEN, 0 },// Threshold value B, Clip value from low-range Apcon 4th contact point and after
	{0x5922, 0x0004, WORD_LEN, 0 },// Threshold value C, Clip value from low-range Apcon 4th contact point and after
	{0x5926, 0x0082, WORD_LEN, 0 },// Threshold value B, middle-range Apcon 1st contact point X-coordinate
	{0x592A, 0x0320, WORD_LEN, 0 },// Threshold value A, middle-range Apcon 2nd contact point X-coordinate
	{0x592C, 0x0320, WORD_LEN, 0 },// Threshold value B, middle-range Apcon 2nd contact point X-coordinate
	{0x592E, 0x0320, WORD_LEN, 0 },// Threshold value C, middle-range Apcon 2nd contact point X-coordinate
	{0x5930, 0x0384, WORD_LEN, 0 },// Threshold value A, middle-range Apcon 3rd contact point X-coordinate
	{0x5932, 0x0384, WORD_LEN, 0 },// Threshold value B, middle-range Apcon 3rd contact point X-coordinate
	{0x5934, 0x0384, WORD_LEN, 0 },// Threshold value C, middle-range Apcon 3rd contact point X-coordinate
	{0x5942, 0x0003, WORD_LEN, 0 },// Threshold value A, Clip value from middle-range Apcon 4th contact point and after
	{0x5944, 0x0004, WORD_LEN, 0 },// Threshold value B, Clip value from middle-range Apcon 4th contact point and after
	{0x5946, 0x0004, WORD_LEN, 0 },// Threshold value C, Clip value from middle-range Apcon 4th contact point and after
	{0x594A, 0x0023, WORD_LEN, 0 },// Threshold value B, high-range Apcon 1st contact point X-coordinate
	{0x594E, 0x0032, WORD_LEN, 0 },// Threshold value A, high-range Apcon 2nd contact point X-coordinate
	{0x5950, 0x0023, WORD_LEN, 0 },// Threshold value B, high-range Apcon 2nd contact point X-coordinate
	{0x5952, 0x0032, WORD_LEN, 0 },// Threshold value C, high-range Apcon 2nd contact point X-coordinate
	{0x5954, 0x00C8, WORD_LEN, 0 },// Threshold value A, high-range Apcon 3rd contact point X-coordinate
	{0x5956, 0x005D, WORD_LEN, 0 },// Threshold value B, high-range Apcon 3rd contact point X-coordinate
	{0x5958, 0x00C8, WORD_LEN, 0 },// Threshold value C, high-range Apcon 3rd contact point X-coordinate
	{0x5968, 0x0000, WORD_LEN, 0 },// Threshold value B, Clip value from high-range Apcon 4th contact point and after
	{0x596A, 0x0000, WORD_LEN, 0 },// Threshold value C, Clip value from high-range Apcon 4th contact point and after
	{0x596C, 0x32, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (before LVD) for threshold value A.
	{0x596D, 0x32, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (before LVD) for threshold value B.
	{0x596F, 0x32, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value A.
	{0x5970, 0x40, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value B.
	{0x5971, 0x40, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value C.
	{0x5972, 0x32, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value A.
	{0x5973, 0x40, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value B.
	{0x5974, 0x37, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value C.
	{0x5975, 0x20, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value A.
	{0x5976, 0x40, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value B.
	{0x5977, 0x4A, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value C.
	{0x5979, 0x5A, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (after Coring) for threshold value B.
	{0x597A, 0x50, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (after Coring) for threshold value C.
	{0x597C, 0x5A, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (after Coring) for threshold value B.
	{0x597D, 0x87, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (after Coring) for threshold value C.
	{0x597E, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value A
	{0x597F, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value B
	{0x5980, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value C
	{0x5981, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side 1st contact point and after for threshold value A
	{0x5982, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side 1st contact point and after for threshold value B
	{0x5985, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side low to 1st contact point for threshold value B
	{0x5986, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side low to 1st contact point for threshold value C
	{0x5987, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value A
	{0x5988, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value B
	{0x5989, 0x08, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value C
	{0x598A, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value A
	{0x598B, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value B
	{0x598C, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value C
	{0x598D, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side 1st contact point and after for threshold value A
	{0x598F, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side 1st contact point and after for threshold value C
	{0x5991, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side low to 1st contact point for threshold value B
	{0x5992, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side low to 1st contact point for threshold value C
	{0x5993, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value A
	{0x5994, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value B
	{0x5995, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value C
	{0x5997, 0x0C, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side low to 1st contact point for threshold value B
	{0x5998, 0x0C, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side low to 1st contact point for threshold value C
	{0x5999, 0x04, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value A
	{0x599A, 0x03, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value B
	{0x599B, 0x08, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value C
	{0x599D, 0x08, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side low to 1st contact point for threshold value B
	{0x599E, 0x10, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side low to 1st contact point for threshold value C
	{0x599F, 0x04, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side 1st contact point and after for threshold value A
	{0x59A0, 0x03, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side 1st contact point and after for threshold value B
	{0x59A1, 0x08, BYTE_LEN, 0 },// Slope from ,high-range Apcon negative-side 1st contact point and after for threshold value C
	{0x59A5, 0x20, BYTE_LEN, 0 },// Threshold value A, Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59A6, 0x20, BYTE_LEN, 0 },// Threshold value B, Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59A7, 0x20, BYTE_LEN, 0 },// Threshold value C, Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59A8, 0x50, BYTE_LEN, 0 },// Threshold value A, Slope from low-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59A9, 0x50, BYTE_LEN, 0 },// Threshold value B, Slope from low-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59AA, 0x50, BYTE_LEN, 0 },// Threshold value C, Slope from low-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59AC, 0x90, BYTE_LEN, 0 },// Threshold value B, Slope from middle-range Apcon origin to 1st contact point (absolute value)
	{0x59AE, 0x50, BYTE_LEN, 0 },// Threshold value A, Slope from middle-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59B1, 0x50, BYTE_LEN, 0 },// Threshold value A, Slope from middle-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59B2, 0x50, BYTE_LEN, 0 },// Threshold value B, Slope from middle-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59B3, 0x50, BYTE_LEN, 0 },// Threshold value C, Slope from middle-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59B5, 0xFF, BYTE_LEN, 0 },// Threshold value B, Slope from high-range Apcon origin to 1st contact point (absolute value)
	{0x59B7, 0x30, BYTE_LEN, 0 },// Threshold value A, Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59B8, 0xE0, BYTE_LEN, 0 },// Threshold value B, Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59B9, 0x30, BYTE_LEN, 0 },// Threshold value C, Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, treated as negative coefficient)
	{0x59BA, 0x20, BYTE_LEN, 0 },// Threshold value A, Slope from high-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59BB, 0x20, BYTE_LEN, 0 },// Threshold value B, Slope from high-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59BC, 0x20, BYTE_LEN, 0 },// Threshold value C, Slope from high-range Apcon 3rd contact point and after (absolute value, treated as negative coefficient)
	{0x59BD, 0x30, BYTE_LEN, 0 },// LMT_WEIGHT_A
	{0x59BE, 0x60, BYTE_LEN, 0 },// LMT_WEIGHT_B
	{0x59C5, 0x08, BYTE_LEN, 0 },// CS_SLP_C_A
	{0x59C6, 0x08, BYTE_LEN, 0 },// CS_SLP_C_B
	{0x59C7, 0x08, BYTE_LEN, 0 },// CS_SLP_C_C
	{0x59C8, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_A
	{0x59C9, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_B
	{0x59CA, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_C
	{0x59CB, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_A
	{0x59CC, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_B
	{0x59CD, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_C
	{0x59D4, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_A
	{0x59D6, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_B
	{0x59D8, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_C
	{0x59DA, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_A
	{0x59DC, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_B
	{0x59DE, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_C
	{0x59EC, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_A
	{0x59ED, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_B
	{0x59EE, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_C
	{0x59F2, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_A
	{0x59F3, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_B
	{0x59F4, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_C

	///////////////////////////////////////
	///////// Cat.::AF Driver STW /////////
	///////////////////////////////////////
	{0xC000, 0xB5F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC002, 0x4D0E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC004, 0x4C0E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC006, 0x4A0F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC008, 0x4F0F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC00A, 0x4B10, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC00C, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC00E, 0x2A00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC010, 0xD904, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC012, 0x5C6E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC014, 0x5466, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC016, 0x3101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC018, 0x4291, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC01A, 0xD3FA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC01C, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC01E, 0x2B00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC020, 0xD904, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC022, 0x2200, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC024, 0x547A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC026, 0x3101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC028, 0x4299, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC02A, 0xD3FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC02C, 0x4908, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC02E, 0x6088, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC030, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC032, 0x4808, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC034, 0x6008, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC036, 0xB003, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC038, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC03A, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC03C, 0x0D20, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC03E, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC040, 0x0D20, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC042, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC044, 0x0004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC046, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC048, 0x0D24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC04A, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC04C, 0x000C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC04E, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC050, 0x0D24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC052, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC054, 0x0D20, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC056, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC058, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC05A, 0x781F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC05C, 0x2F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC05E, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC060, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC062, 0xF8B8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC064, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC066, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC068, 0xF801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC06A, 0xE7FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC06C, 0xB5FF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC06E, 0xB083, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC070, 0x1C0C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC072, 0x1C1F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC074, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC076, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC078, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC07A, 0x43EB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC07C, 0x4E54, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC07E, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC080, 0xD128, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC082, 0x80F2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC084, 0x1AA0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC086, 0xD502, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC088, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC08A, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC08C, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC08E, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC090, 0x7031, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC092, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC094, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC096, 0x8070, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC098, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC09A, 0xD11B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC09C, 0x01A0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC09E, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0A0, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0A2, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0A4, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0A6, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0A8, 0xF8EE, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0AA, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0AC, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0AE, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0B0, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0B2, 0x2102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0B4, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0B6, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0B8, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0BA, 0xFBAF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0BC, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0BE, 0xD004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0C0, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0C2, 0x43C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0C4, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0C6, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0C8, 0xE07F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0CA, 0x9803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0CC, 0x8004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0CE, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0D0, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0D2, 0xE07A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0D4, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0D6, 0x4E3E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0D8, 0x9002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0DA, 0x78B9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0DC, 0x0040, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0DE, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0E0, 0x78F9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0E2, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0E4, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0E6, 0x0049, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0E8, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0EA, 0xFB9C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0EC, 0x0404, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0EE, 0x0C24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0F0, 0x8A38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0F2, 0x42A0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0F4, 0xDA02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0F6, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0F8, 0x1C04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0FA, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0FC, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC0FE, 0x9101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC100, 0x9802, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC102, 0x2600, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC104, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC106, 0xDD0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC108, 0x1C30, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC10A, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC10C, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC10E, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC110, 0xF89F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC112, 0x1940, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC114, 0x0405, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC116, 0x0C2D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC118, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC11A, 0x3601, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC11C, 0x42B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC11E, 0xDCF3, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC120, 0x4E2B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC122, 0x88B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC124, 0x1B40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC126, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC128, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC12A, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC12C, 0x2301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC12E, 0x42D8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC130, 0xD113, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC132, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC134, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC136, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC138, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC13A, 0x8139, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC13C, 0xE00D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC13E, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC140, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC142, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC144, 0xFAB9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC146, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC148, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC14A, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC14C, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC14E, 0xFAB4, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC150, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC152, 0xD002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC154, 0x8938, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC156, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC158, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC15A, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC15C, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC15E, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC160, 0xDD32, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC162, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC164, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC166, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC168, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC16A, 0xF872, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC16C, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC16E, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC170, 0xD107, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC172, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC174, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC176, 0xDD04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC178, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC17A, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC17C, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC17E, 0x3901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC180, 0x80B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC182, 0x7831, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC184, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC186, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC188, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC18A, 0x1808, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC18C, 0xE001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC18E, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC190, 0x1A08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC192, 0x80F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC194, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC196, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC198, 0x0180, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC19A, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC19C, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC19E, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1A0, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1A2, 0xF871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1A4, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1A6, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1A8, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1AA, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1AC, 0x2102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1AE, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1B0, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1B2, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1B4, 0xFB32, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1B6, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1B8, 0xD182, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1BA, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1BC, 0x9903, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1BE, 0x8008, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1C0, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1C2, 0x3501, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1C4, 0x42A8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1C6, 0xDCCC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1C8, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1CA, 0xB007, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1CC, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1CE, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1D0, 0x0D24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1D2, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1D4, 0xB5F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1D6, 0x1C1C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1D8, 0x1C15, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1DA, 0x1C06, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1DC, 0x1C0F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1DE, 0x01B8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1E0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1E2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1E4, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1E6, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1E8, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1EA, 0xF84D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1EC, 0xAB00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1EE, 0x8018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1F0, 0x4809, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1F2, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1F4, 0x6880, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1F6, 0x2102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1F8, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1FA, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1FC, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC1FE, 0xFB0D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC200, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC202, 0xD001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC204, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC206, 0xE006, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC208, 0x1C38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC20A, 0x1C29, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC20C, 0x1C22, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC20E, 0x8037, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC210, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC212, 0xF804, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC214, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC216, 0xBDF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC218, 0x0D24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC21A, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC21C, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC21E, 0x1C17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC220, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC222, 0xD500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC224, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC226, 0x89BA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC228, 0x0901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC22A, 0x4351, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC22C, 0x0700, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC22E, 0x0F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC230, 0xD000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC232, 0x1851, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC234, 0x89F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC236, 0x1841, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC238, 0x6978, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC23A, 0x1809, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC23C, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC23E, 0xFA3C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC240, 0x4B02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC242, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC244, 0xD900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC246, 0x1C18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC248, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC24A, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC24C, 0x7FFF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC24E, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC250, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC252, 0x7893, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC254, 0x4283, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC256, 0xDD05, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC258, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC25A, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC25C, 0x1C0A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC25E, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC260, 0x1C58, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC262, 0xE009, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC264, 0x7853, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC266, 0x78D2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC268, 0x1A9F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC26A, 0x4287, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC26C, 0xDC09, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC26E, 0x1A18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC270, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC272, 0x1C0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC274, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC276, 0x1C50, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC278, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC27A, 0xFAD4, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC27C, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC27E, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC280, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC282, 0x1C08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC284, 0xE7FC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC286, 0x0201, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC288, 0x1200, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC28A, 0x4308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC28C, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC28E, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC290, 0x46F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC292, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC294, 0x0AE5, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0xC296, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_STW_ES2
	{0x485C, 0x0298, WORD_LEN, 0 },// AF_DRV_SIZE
	{0x485E, 0x5665, WORD_LEN, 0 },// AF_DRV_CHKSUM_CODE
	{0x000A, 0x01, BYTE_LEN, 0 },// AF_EXT

	///////////////////////////////////////
	/////////////// Cat.:AF ///////////////
	///////////////////////////////////////
	{0x4808, 0x0019, WORD_LEN, 0 },// Minimum AF-OPD_TH value for IIR
	{0x480A, 0x00FA, WORD_LEN, 0 },// Maximum AF-OPD_TH value for IIR
	{0x480C, 0x03EB, WORD_LEN, 0 },// AF scale offset value used for AF_IIR_PEAK_OPD_TH_MIN
	{0x480E, 0x03E8, WORD_LEN, 0 },// Minimum AF-OPD_TH value for FIR
	{0x4810, 0x03E8, WORD_LEN, 0 },// Maximum AF-OPD_TH value for FIR
	{0x4812, 0x03EB, WORD_LEN, 0 },// AF scale offset value used for AF_FIR_PEAK_OPD_TH_MIN
	{0x481C, 0x00, BYTE_LEN, 0 },// Evaluation value averaging mode
	{0x4824, 0x0004, WORD_LEN, 0 },// Movement amount per step on Climb
	{0x4826, 0x0005, WORD_LEN, 0 },// FIR judgment threshold on Wobble [as percent(0.1%)] or [Numerical value]
	{0x482C, 0x001E, WORD_LEN, 0 },// FIR peak judgment threshold on Climb [as percent(0.1%)] or [Numerical value]
	{0x4832, 0x01F4, WORD_LEN, 0 },// FIR judgment threshold for Judge [as percent(0.1%)] or [Numerical value] /*MM-UW-fix DP device green preview-00+*/
	{0x4838, 0x0020, WORD_LEN, 0 },// Maximum value of extended movement on Wobble, Climb failure
	{0x4844, 0x0020, WORD_LEN, 0 },// FINE search range offset
	{0x484F, 0x00, BYTE_LEN, 0 },// Exposure time-dependent lens control flag
	{0x4856, 0x14, BYTE_LEN, 0 },// AF_DROPRATE_ON_PEAK_DETECT_FIR
	{0x486C, 0x0010, WORD_LEN, 0 },// AF_DRV_AMOUNT_TONEAR_F
	{0x486E, 0x0004, WORD_LEN, 0 },// AF_DRV_AMOUNT_TONEAR_S
	{0x4870, 0x0010, WORD_LEN, 0 },// AF_DRV_AMOUNT_TOFAR_F
	{0x4872, 0x0004, WORD_LEN, 0 },// AF_DRV_AMOUNT_TOFAR_S
	{0x4876, 0x0000, WORD_LEN, 0 },// AF_AREA_LOW_TYPE1
	{0x4878, 0x00FF, WORD_LEN, 0 },// AF_AREA_HIGH_TYPE1
	{0x487A, 0x0000, WORD_LEN, 0 },// AF_AREA_LOW_TYPE2
	{0x487C, 0x0080, WORD_LEN, 0 },// AF_AREA_HIGH_TYPE2
	{0x4880, 0x00FF, WORD_LEN, 0 },// AF_AREA_HIGH_TYPE3
	{0x4884, 0x00, BYTE_LEN, 0 },// AF_MONICHG_MOVE_F
	{0x4889, 0x10, BYTE_LEN, 0 },// AF_SENDNUM_ALL
	{0x488A, 0x00, BYTE_LEN, 0 },// AF_SENDNUM_UP
	{0x488B, 0x00, BYTE_LEN, 0 },// AF_SENDNUM_DOWN
	{0x488C, 0x0001, WORD_LEN, 0 },// AF_SENDAMOUNT_ADDLIMIT
/* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x489A,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Specifies the luminance side low level threshold value for HPF FIR coring processin
    {0x489C,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Specifies the luminance side low level threshold value for HPF FIR coring processin
    {0x489E,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Specifies the luminance side low level threshold value for HPF FIR coring processin
    {0x48A6,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dep
    {0x48A8,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dep
    {0x48AA,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dep
    {0x48B2,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    {0x48B4,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    {0x48B6,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    {0x48BE,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    {0x48C0,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    {0x48C2,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    {0x48CA,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Specifies the luminance side low level threshold value for HPF IIR coring processin
    {0x48CC,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Specifies the luminance side low level threshold value for HPF IIR coring processin
    {0x48CE,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Specifies the luminance side low level threshold value for HPF IIR coring processin
    {0x48D0,0x03FF, WORD_LEN, 0 },// Value1 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    {0x48D2,0x03FF, WORD_LEN, 0 },// Value2 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    {0x48D4,0x03FF, WORD_LEN, 0 },// Value3 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    {0x48D6,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dep
    {0x48D8,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dep
    {0x48DA,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dep
    {0x48E2,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48E4,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48E6,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48E8,0x03FF, WORD_LEN, 0 },// Value1 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48EA,0x03FF, WORD_LEN, 0 },// Value2 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48EC,0x03FF, WORD_LEN, 0 },// Value3 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    {0x48EE,0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    {0x48F0,0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    {0x48F2,0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
/* FIH-SW3-MM-UW-fix flicker issue-00-*/
	{0x48D0, 0x03FF, WORD_LEN, 0 },// Value1 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
	{0x48D2, 0x03FF, WORD_LEN, 0 },// Value2 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
	{0x48D4, 0x03FF, WORD_LEN, 0 },// Value3 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
	{0x48E8, 0x03FF, WORD_LEN, 0 },// Value1 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
	{0x48EA, 0x03FF, WORD_LEN, 0 },// Value2 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
	{0x48EC, 0x03FF, WORD_LEN, 0 },// Value3 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
	{0x48F4, 0x03FF, WORD_LEN, 0 },// Value1 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
	{0x48F6, 0x03FF, WORD_LEN, 0 },// Value2 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
	{0x48F8, 0x03FF, WORD_LEN, 0 },// Value3 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
	{0x495C, 0x01, BYTE_LEN, 0 },// Lens movement anti-noise limiter control flag
	{0x4968, 0x00, BYTE_LEN, 0 },// Stop decision setting during Wobble/Climb
	{0x4969, 0x08, BYTE_LEN, 0 },// Threshold change decision count until restoring Wobble during Judge
	{0x496C, 0x00, BYTE_LEN, 0 },// Set whether to enable FILTER setting
	{0x496E, 0x01F4, WORD_LEN, 0 },// Uniform increase evaluation value threshold (for FIR)
	{0x4970, 0x03E8, WORD_LEN, 0 },// Uniform increase evaluation value threshold (for IIR)

	///////////////////////////////////////
	///////////// Cat.:AF EXT /////////////
	///////////////////////////////////////
	{0x6E00, 0x01, BYTE_LEN, 0 },// FIR/IIR/FIR&IIR switch
	{0x6E08, 0x001E, WORD_LEN, 0 },// The threshold of the AF scale to refer to during a lens edge stop
	{0x6E12, 0x0020, WORD_LEN, 0 },// The threshold of the AF scale to refer to at the time of stable waiting
	{0x6E8E, 0x0096, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Wobble.
	{0x6E90, 0x01F4, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Climb.
	{0x6E92, 0x0096, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Judge.

	///////////////////////////////////////
	//////// Cat.:MODE(AF related) ////////
	///////////////////////////////////////
	{0x4C2C, 0x042E, WORD_LEN, 0 },// AF_OPD0_HDELAY
	{0x4C2E, 0x02C5, WORD_LEN, 0 },// AF_OPD0_VDELAY
	{0x4C30, 0x0217, WORD_LEN, 0 },// AF_OPD0_HVALID
	{0x4C32, 0x0217, WORD_LEN, 0 },// AF_OPD0_VVALID
	{0x4C34, 0x048A, WORD_LEN, 0 },// AF_OPD1_HDELAY
	{0x4C36, 0x0105, WORD_LEN, 0 },// AF_OPD1_VDELAY
	{0x4C38, 0x015F, WORD_LEN, 0 },// AF_OPD1_HVALID
	{0x4C3A, 0x015F, WORD_LEN, 0 },// AF_OPD1_VVALID
	{0x4C44, 0x026E, WORD_LEN, 0 },// AF_OPD3_HDELAY
	{0x4C46, 0x0321, WORD_LEN, 0 },// AF_OPD3_VDELAY
	{0x4C48, 0x015F, WORD_LEN, 0 },// AF_OPD3_HVALID
	{0x4C4A, 0x015F, WORD_LEN, 0 },// AF_OPD3_VVALID
	{0x4C54, 0x048A, WORD_LEN, 0 },// AF_OPD5_HDELAY
	{0x4C56, 0x0321, WORD_LEN, 0 },// AF_OPD5_VDELAY
	{0x4C58, 0x015F, WORD_LEN, 0 },// AF_OPD5_HVALID
	{0x4C5A, 0x015F, WORD_LEN, 0 },// AF_OPD5_VVALID
	{0x4C64, 0x06A6, WORD_LEN, 0 },// AF_OPD7_HDELAY
	{0x4C66, 0x0321, WORD_LEN, 0 },// AF_OPD7_VDELAY
	{0x4C68, 0x015F, WORD_LEN, 0 },// AF_OPD7_HVALID
	{0x4C6A, 0x015F, WORD_LEN, 0 },// AF_OPD7_VVALID
	{0x4C74, 0x048A, WORD_LEN, 0 },// AF_OPD9_HDELAY
	{0x4C76, 0x053D, WORD_LEN, 0 },// AF_OPD9_VDELAY
	{0x4C78, 0x015F, WORD_LEN, 0 },// AF_OPD9_HVALID
	{0x4C7A, 0x015F, WORD_LEN, 0 },// AF_OPD9_VVALID
	{0x4C7D, 0x00, BYTE_LEN, 0 },// AF_OPD1B_WEIGHT
	{0x4C7E, 0x00, BYTE_LEN, 0 },// AF_OPD2A_WEIGHT
	{0x4C7F, 0x00, BYTE_LEN, 0 },// AF_OPD2B_WEIGHT
	{0x4C82, 0x00, BYTE_LEN, 0 },// AF_OPD4A_WEIGHT
	{0x4C83, 0x00, BYTE_LEN, 0 },// AF_OPD4B_WEIGHT
	{0x4C84, 0x00, BYTE_LEN, 0 },// AF_OPD5A_WEIGHT
	{0x4C85, 0x00, BYTE_LEN, 0 },// AF_OPD5B_WEIGHT

	///////////////////////////////////////
	//////////// Cat. : GAMMA1 ////////////
	///////////////////////////////////////
	{0x5438, 0x0001, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table1)
	{0x543A, 0x0002, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table1)
	{0x543C, 0x0004, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table1)
	{0x543E, 0x0006, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table1)
	{0x5440, 0x0008, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table1)
	{0x5442, 0x000B, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table1)
	{0x5444, 0x000E, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table1)
	{0x5446, 0x0011, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table1)
	{0x5448, 0x0014, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table1)
	{0x544A, 0x0017, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table1)
	{0x544C, 0x001B, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table1)
	{0x544E, 0x001F, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table1)
	{0x5450, 0x0023, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table1)
	{0x5452, 0x0027, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table1)
	{0x5454, 0x002C, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table1)
	{0x5456, 0x0032, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table1)
	{0x5458, 0x0037, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table1)
	{0x545A, 0x0016, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table1)
	{0x545C, 0x0052, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table1)
	{0x545E, 0x0084, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table1)
	{0x5460, 0x00AA, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table1)
	{0x5462, 0x00C8, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table1)
	{0x5464, 0x00DC, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table1)
	{0x5466, 0x00F0, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table1)
	{0x5468, 0x00FD, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table1)
	{0x54A2, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -R (Table1)
	{0x54A6, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -G (Table1)
	{0x54AA, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -B (Table1)
	{0x54AE, 0x5D01, WORD_LEN, 0 },// Convergence luminance setting (Table1)

	///////////////////////////////////////
	//////////// Cat. : GAMMA2 ////////////
	///////////////////////////////////////
	{0x5638, 0x0000, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table2)
	{0x563A, 0x0001, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table2)
	{0x563C, 0x0006, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table2)
	{0x563E, 0x000C, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table2)
	{0x5640, 0x0015, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table2)
	{0x5642, 0x001D, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table2)
	{0x5644, 0x0027, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table2)
	{0x5646, 0x0031, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table2)
	{0x5648, 0x003A, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table2)
	{0x564A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table2)
	{0x564C, 0x004B, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table2)
	{0x564E, 0x0053, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table2)
	{0x5650, 0x005B, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table2)
	{0x5652, 0x0063, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table2)
	{0x5654, 0x006A, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table2)
	{0x5656, 0x0071, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table2)
	{0x5658, 0x007B, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table2)
	{0x565A, 0x003E, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table2)
	{0x565C, 0x00AC, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table2)
	{0x565E, 0x00D4, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table2)
	{0x5660, 0x00E6, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table2)
	{0x5662, 0x00F2, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table2)
	{0x5664, 0x00F8, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table2)
	{0x5666, 0x00FE, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table2)
	{0x5668, 0x0101, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table2)
	{0x566A, 0x0104, WORD_LEN, 0 },// RGB-Gamma G-knot26(Table2)
	{0x56AE, 0x2300, WORD_LEN, 0 },// Convergence luminance setting (Table2)

	///////////////////////////////////////
	///////////// Cat. : PICT /////////////
	///////////////////////////////////////
	{0x4E0B, 0x01, BYTE_LEN, 0 },// Hue gain mode selection0: AUTO (coloring control)1: Fixed at setting value for POS12: Fixed at setting value for POS2
	{0x4E0C, 0x01FE, WORD_LEN, 0 },// Chroma start
	{0x4E0E, 0x0A2A, WORD_LEN, 0 },// Chroma end
	{0x4E10, 0x0100, WORD_LEN, 0 },// Chroma suppress levelWhen the value larger than 100h is set, it is limited at 100h.
	{0x4F24, 0x3C, BYTE_LEN, 0 },// MAIN_CONFIG1
	{0x4F25, 0x09, BYTE_LEN, 0 },// MAIN_CONFIG2
	{0x4F2E, 0x0000, WORD_LEN, 0 },// DS_ADGRADCORE_B
	{0x4F30, 0x0000, WORD_LEN, 0 },// DS_ADGRADCORE_C
	{0x4F34, 0x0000, WORD_LEN, 0 },// DS_HVGRADCORE_B
	{0x4F36, 0x0000, WORD_LEN, 0 },// DS_HVGRADCORE_C
	{0x4F38, 0x0A, BYTE_LEN, 0 },// DS_ADGRADLIM_A
	{0x4F39, 0x14, BYTE_LEN, 0 },// DS_ADGRADLIM_B
	{0x4F3A, 0x14, BYTE_LEN, 0 },// DS_ADGRADLIM_C
	{0x4F3B, 0x14, BYTE_LEN, 0 },// DS_HVGRADLIM_A
	{0x4F3C, 0x1E, BYTE_LEN, 0 },// DS_HVGRADLIM_B
	{0x4F3D, 0x1E, BYTE_LEN, 0 },// DS_HVGRADLIM_C
	{0x4F3E, 0x0A, BYTE_LEN, 0 },// DS_DFCT_TH_A
	{0x4F3F, 0x1E, BYTE_LEN, 0 },// DS_DFCT_TH_B
	{0x4F40, 0x1E, BYTE_LEN, 0 },// DS_DFCT_TH_C

	////////////////////////////////////////
	///// Cat. : LMT (Hue/Gain for HD) /////
	////////////////////////////////////////
	{0x5062, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), for HD, POS1
	{0x5064, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), for HD, POS1
	{0x5066, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), for HD, POS1
	{0x5068, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), for HD, POS1
	{0x506A, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), for HD, POS1
	{0x506C, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), for HD, POS1
	{0x506E, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), for HD, POS1
	{0x5070, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), for HD, POS1
	{0x5073, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), for HD, POS1
	{0x5075, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), for HD, POS1
	{0x5077, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), for HD, POS1
	{0x5079, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), for HD, POS1
	{0x507A, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), for HD, POS2
	{0x507C, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), for HD, POS2
	{0x507E, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), for HD, POS2
	{0x5080, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), for HD, POS2
	{0x5082, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), for HD, POS2
	{0x5084, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), for HD, POS2
	{0x5086, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), for HD, POS2
	{0x5088, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), for HD, POS2
	{0x508B, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), for HD, POS2
	{0x508D, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), for HD, POS2
	{0x508F, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), for HD, POS2
	{0x5091, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), for HD, POS2

        /* FIH-SW3-MM-UW-set AF range-00+*/ 
	////////////////////////////////////////
	//// Cat. : USERCTRL (PICT related) ////
	////////////////////////////////////////
	{0x0102, 0x20, BYTE_LEN, 0 },// AWB_SN1
	{0x0103, 0x01, BYTE_LEN, 0 },// AE_SN1
	{0x0107, 0x10, BYTE_LEN, 0 },// AWB_SN2
	{0x0108, 0x01, BYTE_LEN, 0 },// AE_SN2
	{0x0109, 0x4D, BYTE_LEN, 0 },// AE_SUB_SN2
	{0x010C, 0x20, BYTE_LEN, 0 },// AWB_SN3
	{0x010D, 0x01, BYTE_LEN, 0 },// AE_SN3
	{0x010E, 0x41, BYTE_LEN, 0 },// AE_SUB_SN3
	{0x0111, 0x10, BYTE_LEN, 0 },// AWB_SN4
	{0x0112, 0x01, BYTE_LEN, 0 },// AE_SN4
	{0x0113, 0x41, BYTE_LEN, 0 },// AE_SUB_SN4
	{0x0116, 0x20, BYTE_LEN, 0 },// AWB_SN5
	{0x0117, 0x01, BYTE_LEN, 0 },// AE_SN5
	{0x0118, 0x01, BYTE_LEN, 0 },// AE_SUB_SN5
	{0x011B, 0x20, BYTE_LEN, 0 },// AWB_SN6
	{0x011C, 0x01, BYTE_LEN, 0 },// AE_SN6
	{0x011D, 0xCD, BYTE_LEN, 0 },// AE_SUB_SN6
	{0x0120, 0x20, BYTE_LEN, 0 },// AWB_SN7
	{0x0121, 0x01, BYTE_LEN, 0 },// AE_SN7
	{0x0122, 0x01, BYTE_LEN, 0 },// AE_SUB_SN7
	//{0x0125, 0x20, BYTE_LEN, 0 },// AWB_SN8
	//{0x0126, 0x01, BYTE_LEN, 0 },// AE_SN8
	//{0x0127, 0xC1, BYTE_LEN, 0 },// AE_SUB_SN8
	//{0x012A, 0x20, BYTE_LEN, 0 },// AWB_SN9
	//{0x012B, 0x01, BYTE_LEN, 0 },// AE_SN9
	//{0x012C, 0x03, BYTE_LEN, 0 },// AE_SUB_SN9
	//{0x012F, 0x20, BYTE_LEN, 0 },// AWB_SN10
	//{0x0130, 0x01, BYTE_LEN, 0 },// AE_SN10
	//{0x0131, 0x03, BYTE_LEN, 0 },// AE_SUB_SN10
	//{0x0134, 0x20, BYTE_LEN, 0 },// AWB_SN11
	//{0x0135, 0x01, BYTE_LEN, 0 },// AE_SN11
	//{0x0136, 0x03, BYTE_LEN, 0 },// AE_SUB_SN11
	//{0x0139, 0x20, BYTE_LEN, 0 },// AWB_SN12
	//{0x013A, 0x01, BYTE_LEN, 0 },// AE_SN12
	//{0x013B, 0x03, BYTE_LEN, 0 },// AE_SUB_SN12
	{0x01D3, 0x00, BYTE_LEN, 0 },// AF_SN1-Auro
	{0x01D4, 0x08, BYTE_LEN, 0 },// AF_SN2-Landscape
	{0x01D5, 0x00, BYTE_LEN, 0 },// AF_SN3
	{0x01D6, 0x00, BYTE_LEN, 0 },// AF_SN4-Bench
	{0x01D7, 0x00, BYTE_LEN, 0 },// AF_SN5-Sprots
	{0x01D8, 0x08, BYTE_LEN, 0 },// AF_SN6-Night
	{0x01D9, 0x04, BYTE_LEN, 0 },// AF_SN7-Document
	//{0x01DA, 0x00, BYTE_LEN, 0 },// AF_SN8
	//{0x01DB, 0x00, BYTE_LEN, 0 },// AF_SN9
	//{0x01DC, 0x00, BYTE_LEN, 0 },// AF_SN10
	//{0x01DD, 0x00, BYTE_LEN, 0 },// AF_SN11
	//{0x01DE, 0x00, BYTE_LEN, 0 },// AF_SN12
	{0x010A, 0x40, BYTE_LEN, 0 },// PICT1_SN2
	{0x010F, 0x40, BYTE_LEN, 0 },// PICT1_SN3
	{0x0114, 0x40, BYTE_LEN, 0 },// PICT1_SN4
	{0x0119, 0x40, BYTE_LEN, 0 },// PICT1_SN5
	{0x011E, 0x40, BYTE_LEN, 0 },// PICT1_SN6
	{0x0123, 0x90, BYTE_LEN, 0 },// PICT1_SN7
	//{0x0128, 0x40, BYTE_LEN, 0 },// PICT1_SN8
	//{0x012D, 0x40, BYTE_LEN, 0 },// PICT1_SN9
	//{0x0132, 0x40, BYTE_LEN, 0 },// PICT1_SN10
	//{0x0137, 0x40, BYTE_LEN, 0 },// PICT1_SN11
	//{0x013C, 0x40, BYTE_LEN, 0 },// PICT1_SN12
	{0x01B2, 0x59, BYTE_LEN, 0 },// UISATURATION_TYPE2
	{0x01F9, 0x65, BYTE_LEN, 0 },// PICT3_GAMMA1
	{0x01FC, 0x65, BYTE_LEN, 0 },// PICT3_GAMMA4
	{0x3208, 0x01, BYTE_LEN, 0 },/* FIH-SW3-MM-UW-performance tuning-00+*/
	/* FIH-SW3-MM-UW-set AF range-00-*/ 

	//////////////////////////////////////////
	//// Cat. : USERCTRL (System related) ////
	//////////////////////////////////////////
	{0x001D, 0x00, BYTE_LEN, 0 },//OUTFMT_CAP from 0d jpeg buffering mode to yuv
	{0x0024, 0x0A20, WORD_LEN, 0 },// HSIZE_CAP
	{0x002A, 0x0798, WORD_LEN, 0 },// VSIZE_CAP
	{0x021A, 0x0280, WORD_LEN, 0 },// HSIZE_TN
	{0x021C, 0x01E0, WORD_LEN, 0 },// VSIZE_TN
	{0x0226, 0x06A0, WORD_LEN, 0 },// SIZE_HOLD_HOUT
       {0x0226, 0001, WORD_LEN, 0 },// VADJ_SENS_1_2 /* FIH-SW3-MM-UW-fix flicker issue-00+*/
	{0x02B8, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG1
	{0x02BA, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG3
	{0x02BB, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG4
	{0x02BC, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG5
	{0x02BD, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG6
	{0x02BE, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG7
	{0x02C0, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG9
	{0x02C1, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG10
	{0x033F, 0x00, BYTE_LEN, 0 },// JPGBUF_LINEFIX_F
	
	///////////////////////////////////////
	///////////// Cat. : JPEG /////////////
	///////////////////////////////////////

	////////////////////////////////////////
	////////// Cat. : QTABLE_DATA //////////
	////////////////////////////////////////

	///////////////////////////////////////
	////// Cat. : AE_FRM (for Sence) //////
	///////////////////////////////////////
};
/*MM-UW-support AF---*/
/* FIH-SW3-MM-URI-isx006 sensor setting-00- */

/* FIH-SW3-MM-UW-read vendor id-00+*/
struct isx006_i2c_reg_conf isx006_preload2_2nd_settings[] = {
    //forISX006ES2, 0x, 0x, 0x, 0x, 0x
    //forPeriod_2(KMO), 0x, 0x, 0x, 0x, 0x
    //version 11, 0x, 0x, 0x, 0x, 0x
    //2012.07.17, 0x, 0x, 0x, 0x, 0x
    //ImagingLSIBD, 0xSemiconductorBG, 0xCPDG, 0xSonyCorp., 0x, 0x
    
    ///////////////////////////////////////
    ///// Cat. : USERCTRL(Gamma copy) /////
    ///////////////////////////////////////
    
    { 0x0105, 0x80, BYTE_LEN, 0 },//
    { 0x0387, 0x01, BYTE_LEN, 0 },// RGB_GAMMA_G2RB_F
    
    ////////////////////////////////////////
    ////////////// Cat. : ADJ //////////////
    ////////////////////////////////////////
    
    { 0x4A04, 0x10FB, WORD_LEN, 0 },// 5800K normalized coefficient RAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 1000h.When 0 is set, 0x it is regarded as 1.
    { 0x4A06, 0x10AB, WORD_LEN, 0 },// 5800K normalized coefficient BAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 1000h.When 0 is set, 0x it is regarded as 1.
    { 0x4A08, 0x013C, WORD_LEN, 0 },// 3200K R gainAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 100h.When 0 is set, 0x it is regarded as 1.When the value larger than FFFh is set, 0x it is regarded as FFFh.
    { 0x4A0A, 0x0241, WORD_LEN, 0 },// 3200K B gainAdjust this using the Pre-white balance function of the adjustment mode.1.0 = 100h.When 0 is set, 0x it is regarded as 1.When the value larger than FFFh is set, 0x it is regarded as FFFh.
    { 0x4A24, 0x0013, WORD_LEN, 0 },// SHD, 0x PreR offset, 0x for R2
    { 0x4A28, 0x0000, WORD_LEN, 0 },// SHD, 0x PreR offset, 0x for RB
    { 0x4A2C, 0xFFF8, WORD_LEN, 0 },// SHD, 0x PreB offset, 0x for RB
    
    ///////////////////////////////////////
    ////////////// Cat. : AE //////////////
    ///////////////////////////////////////
    
    { 0x4014, 0x0A5E, WORD_LEN, 0 },// AGCLOWSCL_N
    { 0x4016, 0x28DE, WORD_LEN, 0 },// NORMSHTSCL_L
    { 0x4018, 0x0397, WORD_LEN, 0 },// AGCLOWSCL_L
    { 0x401A, 0x0540, WORD_LEN, 0 },// EXPSHTSCL_L
    { 0x401C, 0x03FD, WORD_LEN, 0 },// AGCHISCL_L
    { 0x401E, 0x0268, WORD_LEN, 0 },// MAXSHTSCL_L
    { 0x4020, 0x02CB, WORD_LEN, 0 },// AGCMAXSCL_L
    
    { 0x402B, 0x8F, BYTE_LEN, 0 },// FPS_SENSALL
    { 0x402E, 0x0A, BYTE_LEN, 0 },// CAP_GAIN_LIMIT
    { 0x4036, 0x0510, WORD_LEN, 0 },// AEPRIAGC
    { 0x403E, 0x21FA, WORD_LEN, 0 },// FLSHT50
    { 0x4040, 0x20EC, WORD_LEN, 0 },// FLSHT60
    { 0x4044, 0x1AF4, WORD_LEN, 0 },// 1SECCLK_ALL
    { 0x404D, 0xA0, BYTE_LEN, 0 },// AUTORATIO_TH
    { 0x405C, 0x09B8, WORD_LEN, 0 },// CLKSHTMIN_FDON_MACRO_RAW10
    { 0x405E, 0x08C6, WORD_LEN, 0 },// CLKSHTMIN_FDOFF_MACRO_RAW10
    { 0x4060, 0x1FA4, WORD_LEN, 0 },// PIXEL_CLK
    { 0x4085, 0x04, BYTE_LEN, 0 },// AUTOCENT_WEIGHT
    { 0x409D, 0x33, BYTE_LEN, 0 },// HIGHJUDG_A
    { 0x409E, 0x2D, BYTE_LEN, 0 },// HIGHJUDG_B
    { 0x409F, 0x64, BYTE_LEN, 0 },// HIGHJUDG_C
    { 0x40A0, 0x5E, BYTE_LEN, 0 },// HIGHJUDG_D
        
    ///////////////////////////////////////
    ///////////// Cat. : MODE /////////////
    ///////////////////////////////////////
    
    { 0x4C14, 0x0400, WORD_LEN, 0 },// Detection window vertical size with all 32 windows for FLC full frame pixel
    
    ///////////////////////////////////////
    //////////// Cat. : AE_FRM ////////////
    /////////////////////////////////////// 
    
    { 0x42C0, 0x07, BYTE_LEN, 0 },// Center weight photometry 03 window weight coefficient  Type 4
    { 0x42C1, 0x08, BYTE_LEN, 0 },// Center weight photometry 04 window weight coefficient  Type 4
    { 0x42C2, 0x07, BYTE_LEN, 0 },// Center weight photometry 05 window weight coefficient  Type 4
    
    { 0x42C6, 0x09, BYTE_LEN, 0 },// Center weight photometry 09 window weight coefficient  Type 4
    { 0x42C7, 0x0D, BYTE_LEN, 0 },// Center weight photometry 10 window weight coefficient  Type 4
    { 0x42C8, 0x0E, BYTE_LEN, 0 },// Center weight photometry 11 window weight coefficient  Type 4
    { 0x42C9, 0x10, BYTE_LEN, 0 },// Center weight photometry 12 window weight coefficient  Type 4
    { 0x42CA, 0x11, BYTE_LEN, 0 },// Center weight photometry 13 window weight coefficient  Type 4
    { 0x42CB, 0x10, BYTE_LEN, 0 },// Center weight photometry 14 window weight coefficient  Type 4
    { 0x42CC, 0x0E, BYTE_LEN, 0 },// Center weight photometry 15 window weight coefficient  Type 4
    { 0x42CD, 0x0D, BYTE_LEN, 0 },// Center weight photometry 16 window weight coefficient  Type 4
    { 0x42CE, 0x09, BYTE_LEN, 0 },// Center weight photometry 17 window weight coefficient  Type 4
    { 0x42CF, 0x0C, BYTE_LEN, 0 },// Center weight photometry 18 window weight coefficient  Type 4
    { 0x42D0, 0x13, BYTE_LEN, 0 },// Center weight photometry 19 window weight coefficient  Type 4
    { 0x42D1, 0x1F, BYTE_LEN, 0 },// Center weight photometry 20 window weight coefficient  Type 4
    { 0x42D2, 0x27, BYTE_LEN, 0 },// Center weight photometry 21 window weight coefficient  Type 4
    { 0x42D3, 0x33, BYTE_LEN, 0 },// Center weight photometry 22 window weight coefficient  Type 4
    { 0x42D4, 0x27, BYTE_LEN, 0 },// Center weight photometry 23 window weight coefficient  Type 4
    { 0x42D5, 0x1F, BYTE_LEN, 0 },// Center weight photometry 24 window weight coefficient  Type 4
    { 0x42D6, 0x13, BYTE_LEN, 0 },// Center weight photometry 25 window weight coefficient  Type 4
    { 0x42D7, 0x0C, BYTE_LEN, 0 },// Center weight photometry 26 window weight coefficient  Type 4
    { 0x42D8, 0x0D, BYTE_LEN, 0 },// Center weight photometry 27 window weight coefficient  Type 4
    { 0x42D9, 0x1F, BYTE_LEN, 0 },// Center weight photometry 28 window weight coefficient  Type 4
    { 0x42DA, 0x47, BYTE_LEN, 0 },// Center weight photometry 29 window weight coefficient  Type 4
    { 0x42DB, 0x4E, BYTE_LEN, 0 },// Center weight photometry 30 window weight coefficient  Type 4
    { 0x42DC, 0x56, BYTE_LEN, 0 },// Center weight photometry 31 window weight coefficient  Type 4
    { 0x42DD, 0x4E, BYTE_LEN, 0 },// Center weight photometry 32 window weight coefficient  Type 4
    { 0x42DE, 0x47, BYTE_LEN, 0 },// Center weight photometry 33 window weight coefficient  Type 4
    { 0x42DF, 0x1F, BYTE_LEN, 0 },// Center weight photometry 34 window weight coefficient  Type 4
    { 0x42E0, 0x0D, BYTE_LEN, 0 },// Center weight photometry 35 window weight coefficient  Type 4
    { 0x42E1, 0x0E, BYTE_LEN, 0 },// Center weight photometry 36 window weight coefficient  Type 4
    { 0x42E2, 0x2A, BYTE_LEN, 0 },// Center weight photometry 37 window weight coefficient  Type 4
    { 0x42E3, 0x4D, BYTE_LEN, 0 },// Center weight photometry 38 window weight coefficient  Type 4
    { 0x42E4, 0x5A, BYTE_LEN, 0 },// Center weight photometry 39 window weight coefficient  Type 4
    { 0x42E6, 0x5A, BYTE_LEN, 0 },// Center weight photometry 41 window weight coefficient  Type 4
    { 0x42E7, 0x4D, BYTE_LEN, 0 },// Center weight photometry 42 window weight coefficient  Type 4
    { 0x42E8, 0x2A, BYTE_LEN, 0 },// Center weight photometry 43 window weight coefficient  Type 4
    { 0x42E9, 0x0E, BYTE_LEN, 0 },// Center weight photometry 44 window weight coefficient  Type 4
    { 0x42EA, 0x0D, BYTE_LEN, 0 },// Center weight photometry 45 window weight coefficient  Type 4
    { 0x42EB, 0x1F, BYTE_LEN, 0 },// Center weight photometry 46 window weight coefficient  Type 4
    { 0x42EC, 0x3B, BYTE_LEN, 0 },// Center weight photometry 47 window weight coefficient  Type 4
    { 0x42ED, 0x43, BYTE_LEN, 0 },// Center weight photometry 48 window weight coefficient  Type 4
    { 0x42EE, 0x4B, BYTE_LEN, 0 },// Center weight photometry 49 window weight coefficient  Type 4
    { 0x42EF, 0x43, BYTE_LEN, 0 },// Center weight photometry 50 window weight coefficient  Type 4
    { 0x42F0, 0x3B, BYTE_LEN, 0 },// Center weight photometry 51 window weight coefficient  Type 4
    { 0x42F1, 0x1F, BYTE_LEN, 0 },// Center weight photometry 52 window weight coefficient  Type 4
    { 0x42F2, 0x0D, BYTE_LEN, 0 },// Center weight photometry 53 window weight coefficient  Type 4
    { 0x42F3, 0x0B, BYTE_LEN, 0 },// Center weight photometry 54 window weight coefficient  Type 4
    { 0x42F4, 0x11, BYTE_LEN, 0 },// Center weight photometry 55 window weight coefficient  Type 4
    { 0x42F5, 0x14, BYTE_LEN, 0 },// Center weight photometry 56 window weight coefficient  Type 4
    { 0x42F6, 0x18, BYTE_LEN, 0 },// Center weight photometry 57 window weight coefficient  Type 4
    { 0x42F8, 0x18, BYTE_LEN, 0 },// Center weight photometry 59 window weight coefficient  Type 4
    { 0x42F9, 0x14, BYTE_LEN, 0 },// Center weight photometry 60 window weight coefficient  Type 4
    { 0x42FA, 0x11, BYTE_LEN, 0 },// Center weight photometry 61 window weight coefficient  Type 4
    { 0x42FB, 0x0B, BYTE_LEN, 0 },// Center weight photometry 62 window weight coefficient  Type 4
    
    ////////////////////////////////////////
    ////// Cat. : USERCTRL(AErelated) //////
    ////////////////////////////////////////
    
    { 0x0104, 0x41, BYTE_LEN, 0 },// AE_SUB_SN1
    { 0x01BD, 0x01, BYTE_LEN, 0 },// MAXFRMEXP_TYPE1
    { 0x01BE, 0x02, BYTE_LEN, 0 },// MAXFRMEXP_TYPE2
    { 0x01BF, 0x03, BYTE_LEN, 0 },// MAXFRMEXP_TYPE3
    { 0x01C0, 0x08, BYTE_LEN, 0 },// MAXFRMEXP_TYPE4
    
    ////////////////////////////////////////
    ////////////// Cat. : AWB //////////////
    ////////////////////////////////////////
    
    { 0x440A, 0x1000, WORD_LEN, 0 },// Initial value of error amount for determining commencement of AWB startup
    
    ////////////////////////////////////////
    //////////// Cat. : AWB_FRM ////////////
    ////////////////////////////////////////
    
    ////////////////////////////////////////
    /////// Cat. : LMT(Linearmatrix) ///////
    ////////////////////////////////////////
    
    { 0x5000, 0xFFA6, WORD_LEN, 0 },// GRG linear matrix coefficient POS1
    { 0x5002, 0xFFF3, WORD_LEN, 0 },// GRB linear matrix coefficient POS1
    { 0x5004, 0xFFDA, WORD_LEN, 0 },// GGR linear matrix coefficient POS1
    { 0x5006, 0xFFE6, WORD_LEN, 0 },// GGB linear matrix coefficient POS1
    { 0x5008, 0xFFFF, WORD_LEN, 0 },// GBR linear matrix coefficient POS1
    { 0x500A, 0xFFCD, WORD_LEN, 0 },// GBG linear matrix coefficient POS1
    { 0x500C, 0xFF9A, WORD_LEN, 0 },// GRG linear matrix coefficient POS2
    { 0x500E, 0xFFFA, WORD_LEN, 0 },// GRB linear matrix coefficient POS2
    { 0x5010, 0xFFDA, WORD_LEN, 0 },// GGR linear matrix coefficient POS2
    { 0x5012, 0xFFED, WORD_LEN, 0 },// GGB linear matrix coefficient POS2
    { 0x5014, 0xFFFF, WORD_LEN, 0 },// GBR linear matrix coefficient POS2
    { 0x5016, 0xFFC0, WORD_LEN, 0 },// GBG linear matrix coefficient POS2
    { 0x5018, 0xFFAC, WORD_LEN, 0 },// GRG linear matrix coefficient POS3
    { 0x501A, 0xFFEE, WORD_LEN, 0 },// GRB linear matrix coefficient POS3
    { 0x501C, 0xFFD1, WORD_LEN, 0 },// GGR linear matrix coefficient POS3
    { 0x501E, 0xFFF8, WORD_LEN, 0 },// GGB linear matrix coefficient POS3
    { 0x5020, 0xFFFD, WORD_LEN, 0 },// GBR linear matrix coefficient POS3
    { 0x5022, 0xFFB8, WORD_LEN, 0 },// GBG linear matrix coefficient POS3
    { 0x5024, 0xFFAC, WORD_LEN, 0 },// GRG linear matrix coefficient POS4
    { 0x5026, 0x0006, WORD_LEN, 0 },// GRB linear matrix coefficient POS4
    { 0x5028, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS4
    { 0x502A, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS4
    { 0x502C, 0xFFF8, WORD_LEN, 0 },// GBR linear matrix coefficient POS4
    { 0x502E, 0xFF7A, WORD_LEN, 0 },// GBG linear matrix coefficient POS4
    { 0x5030, 0xFFAC, WORD_LEN, 0 },// GRG linear matrix coefficient POS5
    { 0x5032, 0x0006, WORD_LEN, 0 },// GRB linear matrix coefficient POS5
    { 0x5034, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS5
    { 0x5036, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS5
    { 0x5038, 0xFFF8, WORD_LEN, 0 },// GBR linear matrix coefficient POS5
    { 0x503A, 0xFF7A, WORD_LEN, 0 },// GBG linear matrix coefficient POS5
    { 0x503C, 0xFF93, WORD_LEN, 0 },// GRG linear matrix coefficient POS6
    { 0x503E, 0xFFEE, WORD_LEN, 0 },// GRB linear matrix coefficient POS6
    { 0x5040, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS6
    { 0x5042, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS6
    { 0x5044, 0xFFFD, WORD_LEN, 0 },// GBR linear matrix coefficient POS6
    { 0x5046, 0xFFB3, WORD_LEN, 0 },// GBG linear matrix coefficient POS6
    { 0x5048, 0xFF93, WORD_LEN, 0 },// GRG linear matrix coefficient POS7
    { 0x504A, 0xFFEE, WORD_LEN, 0 },// GRB linear matrix coefficient POS7
    { 0x504C, 0xFFD3, WORD_LEN, 0 },// GGR linear matrix coefficient POS7
    { 0x504E, 0x0000, WORD_LEN, 0 },// GGB linear matrix coefficient POS7
    { 0x5050, 0xFFFD, WORD_LEN, 0 },// GBR linear matrix coefficient POS7
    { 0x5052, 0xFFB3, WORD_LEN, 0 },// GBG linear matrix coefficient POS7
    { 0x5055, 0x1C, BYTE_LEN, 0 },// POS1 B/G coordinate setting
    { 0x5056, 0x3F, BYTE_LEN, 0 },// POS2 R/G coordinate setting
    { 0x5057, 0x17, BYTE_LEN, 0 },// POS2 B/G coordinate setting
    { 0x5058, 0x5D, BYTE_LEN, 0 },// POS3 R/G coordinate setting
    { 0x505A, 0x6C, BYTE_LEN, 0 },// POS4 R/G coordinate setting
    { 0x505B, 0x0E, BYTE_LEN, 0 },// POS4 B/G coordinate setting
    { 0x505C, 0x95, BYTE_LEN, 0 },// POS5 R/G coordinate setting
    { 0x505E, 0x41, BYTE_LEN, 0 },// POS6 R/G coordinate setting
    { 0x505F, 0x12, BYTE_LEN, 0 },// POS6 B/G coordinate setting
    { 0x5060, 0x4D, BYTE_LEN, 0 },// POS7 R/G coordinate setting
    { 0x5061, 0x10, BYTE_LEN, 0 },// POS7 B/G coordinate setting
    { 0x50A2, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (1st quadrant), 0x for automatic control, 0x POS1
    { 0x50A3, 0x51, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), 0x for automatic control, 0x POS1
    { 0x50A4, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (2nd quadrant), 0x for automatic control, 0x POS1
    { 0x50A5, 0x61, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), 0x for automatic control, 0x POS1
    { 0x50A6, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (3rd quadrant), 0x for automatic control, 0x POS1
    { 0x50A7, 0x61, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), 0x for automatic control, 0x POS1
    { 0x50A8, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (4th quadrant), 0x for automatic control, 0x POS1
    { 0x50A9, 0x51, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), 0x for automatic control, 0x POS1
    { 0x50AA, 0xFFF5, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), 0x for automatic control, 0x POS2
    { 0x50AC, 0xFFEC, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), 0x for automatic control, 0x POS2
    { 0x50AE, 0xFFF5, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), 0x for automatic control, 0x POS2
    { 0x50B0, 0xFFE1, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), 0x for automatic control, 0x POS2
    { 0x50B2, 0xFFFA, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), 0x for automatic control, 0x POS2
    { 0x50B4, 0xFFE1, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), 0x for automatic control, 0x POS2
    { 0x50B6, 0xFFFA, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), 0x for automatic control, 0x POS2
    { 0x50B8, 0xFFEC, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), 0x for automatic control, 0x POS2
    { 0x50BA, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (1st quadrant), 0x for automatic control, 0x POS2
    { 0x50BB, 0x6E, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), 0x for automatic control, 0x POS2
    { 0x50BC, 0x48, BYTE_LEN, 0 },// RYGAIN reference value (2nd quadrant), 0x for automatic control, 0x POS2
    { 0x50BD, 0x73, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), 0x for automatic control, 0x POS2
    { 0x50BE, 0x7C, BYTE_LEN, 0 },// RYGAIN reference value (3rd quadrant), 0x for automatic control, 0x POS2
    { 0x50BF, 0x73, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), 0x for automatic control, 0x POS2
    { 0x50C0, 0x7C, BYTE_LEN, 0 },// RYGAIN reference value (4th quadrant), 0x for automatic control, 0x POS2
    { 0x50C1, 0x6E, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), 0x for automatic control, 0x POS2
    { 0x50C2, 0x12, BYTE_LEN, 0 },// HueGain pos1 coordinate for automatic control (high color temperature sideÅjx256 is the coordinate.
    
    ///////////////////////////////////////
    //////////// Cat. : GAMMA0 ////////////
    ///////////////////////////////////////
    
    { 0x5238, 0x0004, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table0)
    { 0x523A, 0x0008, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table0)
    { 0x523C, 0x000E, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table0)
    { 0x523E, 0x0016, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table0)
    { 0x5240, 0x001E, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table0)
    { 0x5242, 0x0026, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table0)
    { 0x5244, 0x002E, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table0)
    { 0x5246, 0x0036, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table0)
    { 0x5248, 0x003D, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table0)
    { 0x524A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table0)
    { 0x524C, 0x0049, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table0)
    { 0x524E, 0x004E, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table0)
    { 0x5250, 0x0054, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table0)
    { 0x5252, 0x0059, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table0)
    { 0x5254, 0x005E, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table0)
    { 0x5256, 0x0063, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table0)
    { 0x5258, 0x0066, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table0)
    { 0x525A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table0)
    { 0x525C, 0x0087, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table0)
    { 0x525E, 0x00AF, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table0)
    { 0x5260, 0x00C8, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table0)
    { 0x5262, 0x00DC, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table0)
    { 0x5264, 0x00EB, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table0)
    { 0x5266, 0x00F6, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table0)
    { 0x5268, 0x0100, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table0)
    { 0x526A, 0x0102, WORD_LEN, 0 },// RGB-Gamma G-knot26(Table0)
    { 0x52A2, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -R (Table0)
    { 0x52A6, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -G (Table0)
    { 0x52AA, 0x0210, WORD_LEN, 0 },// Low-range setting/offset setting -B (Table0)
    { 0x52AE, 0x2100, WORD_LEN, 0 },// Convergence luminance setting (Table0)
    { 0x0105, 0x40, BYTE_LEN, 0 },//
    
    /////////////////////////////////////////
    //// Cat. : PICT(SHD, 0xY-gamma, 0xY-knee) ////
    /////////////////////////////////////////
    
    { 0x4E40, 0x1964, WORD_LEN, 0 },// High threshold for R2 at the B/G coordinates and high color temperature side for shading color correction.
    { 0x4E42, 0x18CE, WORD_LEN, 0 },// Low threshold for R2 at the B/G coordinates and high color temperature side for shading color correction.
    
    { 0x4E48, 0x1A2C, WORD_LEN, 0 },// R/G coordinates high threshold value for shading color correction for R2.
    
    { 0x4E4C, 0x6679, WORD_LEN, 0 },// High luminance side threshold value for shading gain correction.
    { 0x4E4E, 0x5AC1, WORD_LEN, 0 },// Low luminance side threshold value for shading gain correction.
    
    { 0x4E58, 0x1EDC, WORD_LEN, 0 },// High threshold for RB at the R/G coordinates for shading color correction.

    {0x4E60, 0x0C0A, WORD_LEN, 0 },// AREACMP_SET2_TB1
    {0x4E62, 0x0CC4, WORD_LEN, 0 },// AREACMP_SET2_TB1
    {0x4E64, 0xE0DD, WORD_LEN, 0 },// AREACMP_SET3_TB1
    {0x4E66, 0xDB1A, WORD_LEN, 0 },// AREACMP_SET3_TB1
    {0x4E68, 0x2023, WORD_LEN, 0 },// AREACMP_SET4_TB1
    {0x4E6A, 0x28C5, WORD_LEN, 0 },// AREACMP_SET4_TB1
    {0x4E6C, 0x0033, WORD_LEN, 0 },// AREACMP_SET5_TB1
    {0x4E6E, 0x0033, WORD_LEN, 0 },// AREACMP_SET5_TB1
    {0x4E70, 0x0C0A, WORD_LEN, 0 },// AREACMP_SET6_TB1
    {0x4E72, 0x0CC4, WORD_LEN, 0 },// AREACMP_SET6_TB1
    {0x4E74, 0xE0DD, WORD_LEN, 0 },// AREACMP_SET7_TB1
    {0x4E76, 0xDB1A, WORD_LEN, 0 },// AREACMP_SET7_TB1
    {0x4E78, 0x2023, WORD_LEN, 0 },// AREACMP_SET8_TB1
    {0x4E7A, 0x28C5, WORD_LEN, 0 },// AREACMP_SET8_TB1
    {0x4E7C, 0x0033, WORD_LEN, 0 },// AREACMP_SET9_TB1
    {0x4E7E, 0x0033, WORD_LEN, 0 },// AREACMP_SET9_TB1
    
    { 0x4F52, 0x00, BYTE_LEN, 0 },// PLUS_START_POS
    { 0x4F54, 0x19, BYTE_LEN, 0 },// PLUS_END_POS
    { 0x4F55, 0x19, BYTE_LEN, 0 },// MINUS_START_POS
    { 0x4F56, 0x1D, BYTE_LEN, 0 },// MINUS_POS
    
    { 0x4F59, 0x01, BYTE_LEN, 0 },// YLOW_TH
    { 0x4F5A, 0x14, BYTE_LEN, 0 },// YLOW_RATIO_A
    { 0x4F5B, 0x28, BYTE_LEN, 0 },// YLOW_RATIO_B
    { 0x4F5C, 0x32, BYTE_LEN, 0 },// YLOW_PLUS
    { 0x4F5D, 0x1C, BYTE_LEN, 0 },// YHIGH_TH
    
    { 0x4F60, 0x0A, BYTE_LEN, 0 },// YHIGH_MINUS
    
    { 0x4F6A, 0x00, BYTE_LEN, 0 },// HIST_BLEND
    { 0x4F6C, 0x63DF, WORD_LEN, 0 },// AUTOYGAMMA_DOWN
    { 0x4F6E, 0x63DE, WORD_LEN, 0 },// AUTOYGAMMA_OFF
    
    ////////////////////////////////////////
    ///// Cat. : CXC_DATA(Pre-Shading) /////
    ////////////////////////////////////////
    
    //PreSHD no.83//
    { 0x9000, 0x8282, WORD_LEN, 0 },// CXC_Validation code
    { 0x9002, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte0
    { 0x9003, 0x0E, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte1
    { 0x9004, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte2
    { 0x9005, 0x38, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte3
    { 0x9006, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte4
    { 0x9007, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte5
    { 0x9008, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte6
    { 0x9009, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte7
    { 0x900A, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit0 Byte8
    { 0x900B, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte0
    { 0x900C, 0x12, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte1
    { 0x900D, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte2
    { 0x900E, 0x48, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte3
    { 0x900F, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte4
    { 0x9010, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte5
    { 0x9011, 0xC1, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte6
    { 0x9012, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte7
    { 0x9013, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit1 Byte8
    { 0x9014, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte0
    { 0x9015, 0x12, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte1
    { 0x9016, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte2
    { 0x9017, 0x38, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte3
    { 0x9018, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte4
    { 0x9019, 0xE0, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte5
    { 0x901A, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte6
    { 0x901B, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte7
    { 0x901C, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit2 Byte8
    { 0x901D, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte0
    { 0x901E, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte1
    { 0x901F, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte2
    { 0x9020, 0x48, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte3
    { 0x9021, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte4
    { 0x9022, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte5
    { 0x9023, 0x41, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte6
    { 0x9024, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte7
    { 0x9025, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit3 Byte8
    { 0x9026, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte0
    { 0x9027, 0x12, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte1
    { 0x9028, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte2
    { 0x9029, 0x48, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte3
    { 0x902A, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte4
    { 0x902B, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte5
    { 0x902C, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte6
    { 0x902D, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte7
    { 0x902E, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit4 Byte8
    { 0x902F, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte0
    { 0x9030, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte1
    { 0x9031, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte2
    { 0x9032, 0x38, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte3
    { 0x9033, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte4
    { 0x9034, 0xA0, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte5
    { 0x9035, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte6
    { 0x9036, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte7
    { 0x9037, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit5 Byte8
    { 0x9038, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte0
    { 0x9039, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte1
    { 0x903A, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte2
    { 0x903B, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte3
    { 0x903C, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte4
    { 0x903D, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte5
    { 0x903E, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte6
    { 0x903F, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte7
    { 0x9040, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit6 Byte8
    { 0x9041, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte0
    { 0x9042, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte1
    { 0x9043, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte2
    { 0x9044, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte3
    { 0x9045, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte4
    { 0x9046, 0xA0, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte5
    { 0x9047, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte6
    { 0x9048, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte7
    { 0x9049, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit7 Byte8
    { 0x904A, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte0
    { 0x904B, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte1
    { 0x904C, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte2
    { 0x904D, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte3
    { 0x904E, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte4
    { 0x904F, 0xE0, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte5
    { 0x9050, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte6
    { 0x9051, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte7
    { 0x9052, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit8 Byte8
    { 0x9053, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte0
    { 0x9054, 0x0A, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte1
    { 0x9055, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte2
    { 0x9056, 0x28, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte3
    { 0x9057, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte4
    { 0x9058, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte5
    { 0x9059, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte6
    { 0x905A, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte7
    { 0x905B, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit9 Byte8
    { 0x905C, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte0
    { 0x905D, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte1
    { 0x905E, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte2
    { 0x905F, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte3
    { 0x9060, 0xE0, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte4
    { 0x9061, 0x9F, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte5
    { 0x9062, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte6
    { 0x9063, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte7
    { 0x9064, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit10 Byte8
    { 0x9065, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte0
    { 0x9066, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte1
    { 0x9067, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte2
    { 0x9068, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte3
    { 0x9069, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte4
    { 0x906A, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte5
    { 0x906B, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte6
    { 0x906C, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte7
    { 0x906D, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit11 Byte8
    { 0x906E, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte0
    { 0x906F, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte1
    { 0x9070, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte2
    { 0x9071, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte3
    { 0x9072, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte4
    { 0x9073, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte5
    { 0x9074, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte6
    { 0x9075, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte7
    { 0x9076, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit12 Byte8
    { 0x9077, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte0
    { 0x9078, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte1
    { 0x9079, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte2
    { 0x907A, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte3
    { 0x907B, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte4
    { 0x907C, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte5
    { 0x907D, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte6
    { 0x907E, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte7
    { 0x907F, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit13 Byte8
    { 0x9080, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte0
    { 0x9081, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte1
    { 0x9082, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte2
    { 0x9083, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte3
    { 0x9084, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte4
    { 0x9085, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte5
    { 0x9086, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte6
    { 0x9087, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte7
    { 0x9088, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit14 Byte8
    { 0x9089, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte0
    { 0x908A, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte1
    { 0x908B, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte2
    { 0x908C, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte3
    { 0x908D, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte4
    { 0x908E, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte5
    { 0x908F, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte6
    { 0x9090, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte7
    { 0x9091, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit15 Byte8
    { 0x9092, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte0
    { 0x9093, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte1
    { 0x9094, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte2
    { 0x9095, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte3
    { 0x9096, 0x50, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte4
    { 0x9097, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte5
    { 0x9098, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte6
    { 0x9099, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte7
    { 0x909A, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit16 Byte8
    { 0x909B, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte0
    { 0x909C, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte1
    { 0x909D, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte2
    { 0x909E, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte3
    { 0x909F, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte4
    { 0x90A0, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte5
    { 0x90A1, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte6
    { 0x90A2, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte7
    { 0x90A3, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit17 Byte8
    { 0x90A4, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte0
    { 0x90A5, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte1
    { 0x90A6, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte2
    { 0x90A7, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte3
    { 0x90A8, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte4
    { 0x90A9, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte5
    { 0x90AA, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte6
    { 0x90AB, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte7
    { 0x90AC, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit18 Byte8
    { 0x90AD, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte0
    { 0x90AE, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte1
    { 0x90AF, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte2
    { 0x90B0, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte3
    { 0x90B1, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte4
    { 0x90B2, 0x60, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte5
    { 0x90B3, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte6
    { 0x90B4, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte7
    { 0x90B5, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit19 Byte8
    { 0x90B6, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte0
    { 0x90B7, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte1
    { 0x90B8, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte2
    { 0x90B9, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte3
    { 0x90BA, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte4
    { 0x90BB, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte5
    { 0x90BC, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte6
    { 0x90BD, 0x81, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte7
    { 0x90BE, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit20 Byte8
    { 0x90BF, 0x04, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte0
    { 0x90C0, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte1
    { 0x90C1, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte2
    { 0x90C2, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte3
    { 0x90C3, 0x60, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte4
    { 0x90C4, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte5
    { 0x90C5, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte6
    { 0x90C6, 0x81, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte7
    { 0x90C7, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit21 Byte8
    { 0x90C8, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte0
    { 0x90C9, 0x0A, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte1
    { 0x90CA, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte2
    { 0x90CB, 0x28, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte3
    { 0x90CC, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte4
    { 0x90CD, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte5
    { 0x90CE, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte6
    { 0x90CF, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte7
    { 0x90D0, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit22 Byte8
    { 0x90D1, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte0
    { 0x90D2, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte1
    { 0x90D3, 0x10, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte2
    { 0x90D4, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte3
    { 0x90D5, 0x60, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte4
    { 0x90D6, 0xA0, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte5
    { 0x90D7, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte6
    { 0x90D8, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte7
    { 0x90D9, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit23 Byte8
    { 0x90DA, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte0
    { 0x90DB, 0x06, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte1
    { 0x90DC, 0x1C, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte2
    { 0x90DD, 0x30, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte3
    { 0x90DE, 0x70, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte4
    { 0x90DF, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte5
    { 0x90E0, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte6
    { 0x90E1, 0x00, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte7
    { 0x90E2, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit24 Byte8
    { 0x90E3, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte0
    { 0x90E4, 0x08, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte1
    { 0x90E5, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte2
    { 0x90E6, 0x20, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte3
    { 0x90E7, 0x40, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte4
    { 0x90E8, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte5
    { 0x90E9, 0x80, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte6
    { 0x90EA, 0x81, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte7
    { 0x90EB, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit25 Byte8
    { 0x90EC, 0x02, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte0
    { 0x90ED, 0x0A, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte1
    { 0x90EE, 0x0C, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte2
    { 0x90EF, 0x18, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte3
    { 0x90F0, 0x70, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte4
    { 0x90F1, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte5
    { 0x90F2, 0xC0, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte6
    { 0x90F3, 0x01, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte7
    { 0x90F4, 0x03, BYTE_LEN, 0 },// CXC R Gb Data Unit26 Byte8
    { 0x90F5, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte0
    { 0x90F6, 0xF0, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte1
    { 0x90F7, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte2
    { 0x90F8, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte3
    { 0x90F9, 0x1F, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte4
    { 0x90FA, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte5
    { 0x90FB, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte6
    { 0x90FC, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte7
    { 0x90FD, 0xFC, BYTE_LEN, 0 },// CXC Gr B Data Unit0 Byte8
    { 0x90FE, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte0
    { 0x90FF, 0xEC, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte1
    { 0x9100, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte2
    { 0x9101, 0xBF, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte3
    { 0x9102, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte4
    { 0x9103, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte5
    { 0x9104, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte6
    { 0x9105, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte7
    { 0x9106, 0xFB, BYTE_LEN, 0 },// CXC Gr B Data Unit1 Byte8
    { 0x9107, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte0
    { 0x9108, 0xEC, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte1
    { 0x9109, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte2
    { 0x910A, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte3
    { 0x910B, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte4
    { 0x910C, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte5
    { 0x910D, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte6
    { 0x910E, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte7
    { 0x910F, 0xFB, BYTE_LEN, 0 },// CXC Gr B Data Unit2 Byte8
    { 0x9110, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte0
    { 0x9111, 0xF3, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte1
    { 0x9112, 0x07, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte2
    { 0x9113, 0xB0, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte3
    { 0x9114, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte4
    { 0x9115, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte5
    { 0x9116, 0x3E, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte6
    { 0x9117, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte7
    { 0x9118, 0xFC, BYTE_LEN, 0 },// CXC Gr B Data Unit3 Byte8
    { 0x9119, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte0
    { 0x911A, 0xEC, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte1
    { 0x911B, 0x07, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte2
    { 0x911C, 0xB0, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte3
    { 0x911D, 0x2F, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte4
    { 0x911E, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte5
    { 0x911F, 0xBE, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte6
    { 0x9120, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte7
    { 0x9121, 0xFA, BYTE_LEN, 0 },// CXC Gr B Data Unit4 Byte8
    { 0x9122, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte0
    { 0x9123, 0xEC, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte1
    { 0x9124, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte2
    { 0x9125, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte3
    { 0x9126, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte4
    { 0x9127, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte5
    { 0x9128, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte6
    { 0x9129, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte7
    { 0x912A, 0xFA, BYTE_LEN, 0 },// CXC Gr B Data Unit5 Byte8
    { 0x912B, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte0
    { 0x912C, 0xF2, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte1
    { 0x912D, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte2
    { 0x912E, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte3
    { 0x912F, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte4
    { 0x9130, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte5
    { 0x9131, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte6
    { 0x9132, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte7
    { 0x9133, 0xFC, BYTE_LEN, 0 },// CXC Gr B Data Unit6 Byte8
    { 0x9134, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte0
    { 0x9135, 0xF0, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte1
    { 0x9136, 0x07, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte2
    { 0x9137, 0xA8, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte3
    { 0x9138, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte4
    { 0x9139, 0xA0, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte5
    { 0x913A, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte6
    { 0x913B, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte7
    { 0x913C, 0xFB, BYTE_LEN, 0 },// CXC Gr B Data Unit7 Byte8
    { 0x913D, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte0
    { 0x913E, 0xF1, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte1
    { 0x913F, 0xFB, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte2
    { 0x9140, 0xB7, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte3
    { 0x9141, 0x1F, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte4
    { 0x9142, 0xA0, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte5
    { 0x9143, 0x7E, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte6
    { 0x9144, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte7
    { 0x9145, 0xFA, BYTE_LEN, 0 },// CXC Gr B Data Unit8 Byte8
    { 0x9146, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte0
    { 0x9147, 0xEE, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte1
    { 0x9148, 0x0B, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte2
    { 0x9149, 0xB8, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte3
    { 0x914A, 0x2F, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte4
    { 0x914B, 0xE0, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte5
    { 0x914C, 0x3E, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte6
    { 0x914D, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte7
    { 0x914E, 0xFD, BYTE_LEN, 0 },// CXC Gr B Data Unit9 Byte8
    { 0x914F, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte0
    { 0x9150, 0xEF, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte1
    { 0x9151, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte2
    { 0x9152, 0xCF, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte3
    { 0x9153, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte4
    { 0x9154, 0xE0, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte5
    { 0x9155, 0x3E, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte6
    { 0x9156, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte7
    { 0x9157, 0xFD, BYTE_LEN, 0 },// CXC Gr B Data Unit10 Byte8
    { 0x9158, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte0
    { 0x9159, 0xF4, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte1
    { 0x915A, 0x13, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte2
    { 0x915B, 0xE0, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte3
    { 0x915C, 0x4F, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte4
    { 0x915D, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte5
    { 0x915E, 0x3F, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte6
    { 0x915F, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte7
    { 0x9160, 0xFD, BYTE_LEN, 0 },// CXC Gr B Data Unit11 Byte8
    { 0x9161, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte0
    { 0x9162, 0xF8, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte1
    { 0x9163, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte2
    { 0x9164, 0xEF, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte3
    { 0x9165, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte4
    { 0x9166, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte5
    { 0x9167, 0x3F, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte6
    { 0x9168, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte7
    { 0x9169, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit12 Byte8
    { 0x916A, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte0
    { 0x916B, 0xF8, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte1
    { 0x916C, 0x07, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte2
    { 0x916D, 0xE0, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte3
    { 0x916E, 0x6F, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte4
    { 0x916F, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte5
    { 0x9170, 0xBF, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte6
    { 0x9171, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte7
    { 0x9172, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit13 Byte8
    { 0x9173, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte0
    { 0x9174, 0xFE, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte1
    { 0x9175, 0x0B, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte2
    { 0x9176, 0xF8, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte3
    { 0x9177, 0x0F, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte4
    { 0x9178, 0xE0, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte5
    { 0x9179, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte6
    { 0x917A, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte7
    { 0x917B, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit14 Byte8
    { 0x917C, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte0
    { 0x917D, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte1
    { 0x917E, 0x08, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte2
    { 0x917F, 0xE8, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte3
    { 0x9180, 0x2F, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte4
    { 0x9181, 0xA0, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte5
    { 0x9182, 0x7F, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte6
    { 0x9183, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte7
    { 0x9184, 0xFF, BYTE_LEN, 0 },// CXC Gr B Data Unit15 Byte8
    { 0x9185, 0x05, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte0
    { 0x9186, 0xFC, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte1
    { 0x9187, 0x13, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte2
    { 0x9188, 0x10, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte3
    { 0x9189, 0x30, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte4
    { 0x918A, 0x60, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte5
    { 0x918B, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte6
    { 0x918C, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte7
    { 0x918D, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit16 Byte8
    { 0x918E, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte0
    { 0x918F, 0x0C, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte1
    { 0x9190, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte2
    { 0x9191, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte3
    { 0x9192, 0x30, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte4
    { 0x9193, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte5
    { 0x9194, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte6
    { 0x9195, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte7
    { 0x9196, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit17 Byte8
    { 0x9197, 0x07, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte0
    { 0x9198, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte1
    { 0x9199, 0x1C, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte2
    { 0x919A, 0x10, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte3
    { 0x919B, 0x60, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte4
    { 0x919C, 0xA0, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte5
    { 0x919D, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte6
    { 0x919E, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte7
    { 0x919F, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit18 Byte8
    { 0x91A0, 0x05, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte0
    { 0x91A1, 0x0C, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte1
    { 0x91A2, 0x0C, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte2
    { 0x91A3, 0x30, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte3
    { 0x91A4, 0x30, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte4
    { 0x91A5, 0x60, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte5
    { 0x91A6, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte6
    { 0x91A7, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte7
    { 0x91A8, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit19 Byte8
    { 0x91A9, 0x03, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte0
    { 0x91AA, 0x0A, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte1
    { 0x91AB, 0x18, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte2
    { 0x91AC, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte3
    { 0x91AD, 0x60, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte4
    { 0x91AE, 0x80, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte5
    { 0x91AF, 0xC0, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte6
    { 0x91B0, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte7
    { 0x91B1, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit20 Byte8
    { 0x91B2, 0x05, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte0
    { 0x91B3, 0x16, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte1
    { 0x91B4, 0x14, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte2
    { 0x91B5, 0x48, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte3
    { 0x91B6, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte4
    { 0x91B7, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte5
    { 0x91B8, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte6
    { 0x91B9, 0x81, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte7
    { 0x91BA, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit21 Byte8
    { 0x91BB, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte0
    { 0x91BC, 0x0A, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte1
    { 0x91BD, 0x10, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte2
    { 0x91BE, 0x28, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte3
    { 0x91BF, 0x50, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte4
    { 0x91C0, 0x60, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte5
    { 0x91C1, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte6
    { 0x91C2, 0x81, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte7
    { 0x91C3, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit22 Byte8
    { 0x91C4, 0x05, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte0
    { 0x91C5, 0x0E, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte1
    { 0x91C6, 0x10, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte2
    { 0x91C7, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte3
    { 0x91C8, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte4
    { 0x91C9, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte5
    { 0x91CA, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte6
    { 0x91CB, 0x81, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte7
    { 0x91CC, 0x02, BYTE_LEN, 0 },// CXC Gr B Data Unit23 Byte8
    { 0x91CD, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte0
    { 0x91CE, 0x0C, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte1
    { 0x91CF, 0x14, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte2
    { 0x91D0, 0x08, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte3
    { 0x91D1, 0x50, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte4
    { 0x91D2, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte5
    { 0x91D3, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte6
    { 0x91D4, 0x81, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte7
    { 0x91D5, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit24 Byte8
    { 0x91D6, 0x05, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte0
    { 0x91D7, 0x06, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte1
    { 0x91D8, 0x14, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte2
    { 0x91D9, 0x38, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte3
    { 0x91DA, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte4
    { 0x91DB, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte5
    { 0x91DC, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte6
    { 0x91DD, 0x01, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte7
    { 0x91DE, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit25 Byte8
    { 0x91DF, 0x04, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte0
    { 0x91E0, 0x0A, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte1
    { 0x91E1, 0x10, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte2
    { 0x91E2, 0x30, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte3
    { 0x91E3, 0x50, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte4
    { 0x91E4, 0x20, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte5
    { 0x91E5, 0x40, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte6
    { 0x91E6, 0x81, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte7
    { 0x91E7, 0x00, BYTE_LEN, 0 },// CXC Gr B Data Unit26 Byte8
    
    
    
    ///////////////////////////////////////
    /////////// Cat. : SHD_DATA ///////////
    ///////////////////////////////////////
    
    
    // Mesona TYP No83 //
    // D65 SHD1 CHKSHD_TGT57, 0x57, 0x57 //
    
    { 0xA000, 0x9191, WORD_LEN, 0 },// SHD_Validation code
    { 0xA002, 0x7C, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte0
    { 0xA003, 0xE1, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte1
    { 0xA004, 0x4D, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte2
    { 0xA005, 0x63, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte3
    { 0xA006, 0x9E, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte4
    { 0xA007, 0x83, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte5
    { 0xA008, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte6
    { 0xA009, 0xE7, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte7
    { 0xA00A, 0xDC, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte8
    { 0xA00B, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte9
    { 0xA00C, 0x37, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte10
    { 0xA00D, 0x73, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte0
    { 0xA00E, 0xA9, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte1
    { 0xA00F, 0x4D, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte2
    { 0xA010, 0x5E, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte3
    { 0xA011, 0x7A, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte4
    { 0xA012, 0xA3, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte5
    { 0xA013, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte6
    { 0xA014, 0xE7, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte7
    { 0xA015, 0x54, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte8
    { 0xA016, 0xC6, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte9
    { 0xA017, 0x3B, BYTE_LEN, 0 },// SHD R Gb Data Unit1 Byte10
    { 0xA018, 0x8C, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte0
    { 0xA019, 0xA1, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte1
    { 0xA01A, 0x8E, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte2
    { 0xA01B, 0x66, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte3
    { 0xA01C, 0xBC, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte4
    { 0xA01D, 0x93, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte5
    { 0xA01E, 0x19, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte6
    { 0xA01F, 0xEE, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte7
    { 0xA020, 0x10, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte8
    { 0xA021, 0xA6, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte9
    { 0xA022, 0x38, BYTE_LEN, 0 },// SHD R Gb Data Unit2 Byte10
    { 0xA023, 0x74, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte0
    { 0xA024, 0x81, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte1
    { 0xA025, 0xCD, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte2
    { 0xA026, 0x5B, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte3
    { 0xA027, 0x52, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte4
    { 0xA028, 0x43, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte5
    { 0xA029, 0x97, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte6
    { 0xA02A, 0xD8, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte7
    { 0xA02B, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte8
    { 0xA02C, 0xA6, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte9
    { 0xA02D, 0x38, BYTE_LEN, 0 },// SHD R Gb Data Unit3 Byte10
    { 0xA02E, 0x9E, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte0
    { 0xA02F, 0x29, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte1
    { 0xA030, 0x0F, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte2
    { 0xA031, 0x68, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte3
    { 0xA032, 0xD6, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte4
    { 0xA033, 0x33, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte5
    { 0xA034, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte6
    { 0xA035, 0xDF, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte7
    { 0xA036, 0xE0, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte8
    { 0xA037, 0xA5, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte9
    { 0xA038, 0x35, BYTE_LEN, 0 },// SHD R Gb Data Unit4 Byte10
    { 0xA039, 0x59, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte0
    { 0xA03A, 0x29, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte1
    { 0xA03B, 0x8C, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte2
    { 0xA03C, 0x52, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte3
    { 0xA03D, 0xE0, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte4
    { 0xA03E, 0x52, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte5
    { 0xA03F, 0x14, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte6
    { 0xA040, 0xB4, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte7
    { 0xA041, 0x28, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte8
    { 0xA042, 0x05, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte9
    { 0xA043, 0x2E, BYTE_LEN, 0 },// SHD R Gb Data Unit5 Byte10
    { 0xA044, 0x5A, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte0
    { 0xA045, 0x39, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte1
    { 0xA046, 0x8C, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte2
    { 0xA047, 0x5E, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte3
    { 0xA048, 0x66, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte4
    { 0xA049, 0x23, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte5
    { 0xA04A, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte6
    { 0xA04B, 0xE1, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte7
    { 0xA04C, 0x98, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte8
    { 0xA04D, 0xE5, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte9
    { 0xA04E, 0x32, BYTE_LEN, 0 },// SHD R Gb Data Unit6 Byte10
    { 0xA04F, 0x56, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte0
    { 0xA050, 0xF9, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte1
    { 0xA051, 0x8B, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte2
    { 0xA052, 0x4F, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte3
    { 0xA053, 0xB6, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte4
    { 0xA054, 0xD2, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte5
    { 0xA055, 0x12, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte6
    { 0xA056, 0xA1, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte7
    { 0xA057, 0x98, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte8
    { 0xA058, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte9
    { 0xA059, 0x27, BYTE_LEN, 0 },// SHD R Gb Data Unit7 Byte10
    { 0xA05A, 0x2D, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte0
    { 0xA05B, 0x19, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte1
    { 0xA05C, 0xCA, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte2
    { 0xA05D, 0x4F, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte3
    { 0xA05E, 0xB8, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte4
    { 0xA05F, 0x82, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte5
    { 0xA060, 0x15, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte6
    { 0xA061, 0xC1, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte7
    { 0xA062, 0x9C, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte8
    { 0xA063, 0x45, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte9
    { 0xA064, 0x33, BYTE_LEN, 0 },// SHD R Gb Data Unit8 Byte10
    { 0xA065, 0x57, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte0
    { 0xA066, 0xF1, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte1
    { 0xA067, 0x8B, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte2
    { 0xA068, 0x51, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte3
    { 0xA069, 0xCA, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte4
    { 0xA06A, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte5
    { 0xA06B, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte6
    { 0xA06C, 0x9D, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte7
    { 0xA06D, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte8
    { 0xA06E, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte9
    { 0xA06F, 0x23, BYTE_LEN, 0 },// SHD R Gb Data Unit9 Byte10
    { 0xA070, 0x09, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte0
    { 0xA071, 0x81, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte1
    { 0xA072, 0x88, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte2
    { 0xA073, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte3
    { 0xA074, 0x36, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte4
    { 0xA075, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte5
    { 0xA076, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte6
    { 0xA077, 0x9E, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte7
    { 0xA078, 0x1C, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte8
    { 0xA079, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte9
    { 0xA07A, 0x2D, BYTE_LEN, 0 },// SHD R Gb Data Unit10 Byte10
    { 0xA07B, 0x55, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte0
    { 0xA07C, 0x01, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte1
    { 0xA07D, 0x4C, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte2
    { 0xA07E, 0x53, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte3
    { 0xA07F, 0xE4, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte4
    { 0xA080, 0xF2, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte5
    { 0xA081, 0x93, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte6
    { 0xA082, 0xAD, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte7
    { 0xA083, 0x7C, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte8
    { 0xA084, 0x64, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte9
    { 0xA085, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit11 Byte10
    { 0xA086, 0x04, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte0
    { 0xA087, 0x41, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte1
    { 0xA088, 0x48, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte2
    { 0xA089, 0x3F, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte3
    { 0xA08A, 0xFA, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte4
    { 0xA08B, 0x61, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte5
    { 0xA08C, 0x90, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte6
    { 0xA08D, 0x84, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte7
    { 0xA08E, 0x80, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte8
    { 0xA08F, 0xC4, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte9
    { 0xA090, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit12 Byte10
    { 0xA091, 0x41, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte0
    { 0xA092, 0xE9, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte1
    { 0xA093, 0x0A, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte2
    { 0xA094, 0x53, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte3
    { 0xA095, 0xE4, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte4
    { 0xA096, 0xF2, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte5
    { 0xA097, 0x94, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte6
    { 0xA098, 0xB9, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte7
    { 0xA099, 0x08, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte8
    { 0xA09A, 0xA5, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte9
    { 0xA09B, 0x2B, BYTE_LEN, 0 },// SHD R Gb Data Unit13 Byte10
    { 0xA09C, 0x22, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte0
    { 0xA09D, 0x79, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte1
    { 0xA09E, 0x09, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte2
    { 0xA09F, 0x42, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte3
    { 0xA0A0, 0x18, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte4
    { 0xA0A1, 0x22, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte5
    { 0xA0A2, 0x10, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte6
    { 0xA0A3, 0x81, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte7
    { 0xA0A4, 0x28, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte8
    { 0xA0A5, 0xA4, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte9
    { 0xA0A6, 0x21, BYTE_LEN, 0 },// SHD R Gb Data Unit14 Byte10
    { 0xA0A7, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte0
    { 0xA0A8, 0x89, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte1
    { 0xA0A9, 0x49, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte2
    { 0xA0AA, 0x51, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte3
    { 0xA0AB, 0xBE, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte4
    { 0xA0AC, 0xF2, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte5
    { 0xA0AD, 0x94, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte6
    { 0xA0AE, 0xB9, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte7
    { 0xA0AF, 0x74, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte8
    { 0xA0B0, 0x05, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte9
    { 0xA0B1, 0x31, BYTE_LEN, 0 },// SHD R Gb Data Unit15 Byte10
    { 0xA0B2, 0x4E, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte0
    { 0xA0B3, 0x71, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte1
    { 0xA0B4, 0xCB, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte2
    { 0xA0B5, 0x4C, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte3
    { 0xA0B6, 0x86, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte4
    { 0xA0B7, 0xC2, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte5
    { 0xA0B8, 0x11, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte6
    { 0xA0B9, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte7
    { 0xA0BA, 0x54, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte8
    { 0xA0BB, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte9
    { 0xA0BC, 0x23, BYTE_LEN, 0 },// SHD R Gb Data Unit16 Byte10
    { 0xA0BD, 0x1E, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte0
    { 0xA0BE, 0x29, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte1
    { 0xA0BF, 0xC9, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte2
    { 0xA0C0, 0x4D, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte3
    { 0xA0C1, 0x8E, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte4
    { 0xA0C2, 0x32, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte5
    { 0xA0C3, 0x95, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte6
    { 0xA0C4, 0xB8, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte7
    { 0xA0C5, 0x80, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte8
    { 0xA0C6, 0x25, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte9
    { 0xA0C7, 0x31, BYTE_LEN, 0 },// SHD R Gb Data Unit17 Byte10
    { 0xA0C8, 0x75, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte0
    { 0xA0C9, 0x39, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte1
    { 0xA0CA, 0x4D, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte2
    { 0xA0CB, 0x59, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte3
    { 0xA0CC, 0x1C, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte4
    { 0xA0CD, 0xC3, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte5
    { 0xA0CE, 0x94, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte6
    { 0xA0CF, 0xB4, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte7
    { 0xA0D0, 0xF4, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte8
    { 0xA0D1, 0x44, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte9
    { 0xA0D2, 0x2A, BYTE_LEN, 0 },// SHD R Gb Data Unit18 Byte10
    { 0xA0D3, 0x37, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte0
    { 0xA0D4, 0x49, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte1
    { 0xA0D5, 0x8A, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte2
    { 0xA0D6, 0x4F, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte3
    { 0xA0D7, 0xA4, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte4
    { 0xA0D8, 0xF2, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte5
    { 0xA0D9, 0x94, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte6
    { 0xA0DA, 0xB5, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte7
    { 0xA0DB, 0xA4, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte8
    { 0xA0DC, 0x65, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte9
    { 0xA0DD, 0x32, BYTE_LEN, 0 },// SHD R Gb Data Unit19 Byte10
    { 0xA0DE, 0x79, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte0
    { 0xA0DF, 0x51, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte1
    { 0xA0E0, 0x4D, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte2
    { 0xA0E1, 0x65, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte3
    { 0xA0E2, 0xA2, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte4
    { 0xA0E3, 0xB3, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte5
    { 0xA0E4, 0x98, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte6
    { 0xA0E5, 0xE0, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte7
    { 0xA0E6, 0xB0, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte8
    { 0xA0E7, 0x05, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte9
    { 0xA0E8, 0x33, BYTE_LEN, 0 },// SHD R Gb Data Unit20 Byte10
    { 0xA0E9, 0x5D, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte0
    { 0xA0EA, 0x11, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte1
    { 0xA0EB, 0x8C, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte2
    { 0xA0EC, 0x56, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte3
    { 0xA0ED, 0xF6, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte4
    { 0xA0EE, 0xF2, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte5
    { 0xA0EF, 0x95, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte6
    { 0xA0F0, 0xC1, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte7
    { 0xA0F1, 0xBC, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte8
    { 0xA0F2, 0x65, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte9
    { 0xA0F3, 0x33, BYTE_LEN, 0 },// SHD R Gb Data Unit21 Byte10
    { 0xA0F4, 0x92, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte0
    { 0xA0F5, 0x49, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte1
    { 0xA0F6, 0xCE, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte2
    { 0xA0F7, 0x66, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte3
    { 0xA0F8, 0xB2, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte4
    { 0xA0F9, 0xB3, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte5
    { 0xA0FA, 0x9A, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte6
    { 0xA0FB, 0xF6, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte7
    { 0xA0FC, 0xB4, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte8
    { 0xA0FD, 0xC6, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte9
    { 0xA0FE, 0x3D, BYTE_LEN, 0 },// SHD R Gb Data Unit22 Byte10
    { 0xA0FF, 0x9C, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte0
    { 0xA100, 0xB9, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte1
    { 0xA101, 0x8E, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte2
    { 0xA102, 0x63, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte3
    { 0xA103, 0x88, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte4
    { 0xA104, 0xA3, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte5
    { 0xA105, 0x98, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte6
    { 0xA106, 0xDF, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte7
    { 0xA107, 0x38, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte8
    { 0xA108, 0xE6, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte9
    { 0xA109, 0x38, BYTE_LEN, 0 },// SHD R Gb Data Unit23 Byte10
    { 0xA10A, 0xA0, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte0
    { 0xA10B, 0xE1, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte1
    { 0xA10C, 0x4E, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte2
    { 0xA10D, 0x6E, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte3
    { 0xA10E, 0xFC, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte4
    { 0xA10F, 0x73, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte5
    { 0xA110, 0x1B, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte6
    { 0xA111, 0xFF, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte7
    { 0xA112, 0x34, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte8
    { 0xA113, 0x86, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte9
    { 0xA114, 0x39, BYTE_LEN, 0 },// SHD R Gb Data Unit24 Byte10
    { 0xA115, 0x9F, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte0
    { 0xA116, 0x19, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte1
    { 0xA117, 0x0F, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte2
    { 0xA118, 0x68, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte3
    { 0xA119, 0xBE, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte4
    { 0xA11A, 0x33, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte5
    { 0xA11B, 0x19, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte6
    { 0xA11C, 0xE9, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte7
    { 0xA11D, 0x48, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte8
    { 0xA11E, 0xE6, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte9
    { 0xA11F, 0x39, BYTE_LEN, 0 },// SHD R Gb Data Unit26 Byte10
    { 0xA120, 0x94, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte0
    { 0xA121, 0xA9, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte1
    { 0xA122, 0x4E, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte2
    { 0xA123, 0x69, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte3
    { 0xA124, 0xCC, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte4
    { 0xA125, 0xE3, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte5
    { 0xA126, 0x1A, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte6
    { 0xA127, 0xFA, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte7
    { 0xA128, 0x74, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte8
    { 0xA129, 0xE6, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte9
    { 0xA12A, 0x3B, BYTE_LEN, 0 },// SHD R Gb Data Unit0 Byte10
    { 0xA12B, 0x63, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte0
    { 0xA12C, 0x01, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte1
    { 0xA12D, 0x8C, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte2
    { 0xA12E, 0x5D, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte3
    { 0xA12F, 0x24, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte4
    { 0xA130, 0x53, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte5
    { 0xA131, 0x97, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte6
    { 0xA132, 0xC6, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte7
    { 0xA133, 0xA0, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte8
    { 0xA134, 0xE5, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte9
    { 0xA135, 0x2F, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte10
    { 0xA136, 0x68, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte0
    { 0xA137, 0xC9, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte1
    { 0xA138, 0x4B, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte2
    { 0xA139, 0x5B, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte3
    { 0xA13A, 0xFE, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte4
    { 0xA13B, 0xF2, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte5
    { 0xA13C, 0x17, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte6
    { 0xA13D, 0xC9, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte7
    { 0xA13E, 0x24, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte8
    { 0xA13F, 0x26, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte9
    { 0xA140, 0x33, BYTE_LEN, 0 },// SHD Gr B Data Unit1 Byte10
    { 0xA141, 0x7E, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte0
    { 0xA142, 0x79, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte1
    { 0xA143, 0x4C, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte2
    { 0xA144, 0x60, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte3
    { 0xA145, 0x3C, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte4
    { 0xA146, 0x23, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte5
    { 0xA147, 0x18, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte6
    { 0xA148, 0xCF, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte7
    { 0xA149, 0xC8, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte8
    { 0xA14A, 0x25, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte9
    { 0xA14B, 0x31, BYTE_LEN, 0 },// SHD Gr B Data Unit2 Byte10
    { 0xA14C, 0x66, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte0
    { 0xA14D, 0xD1, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte1
    { 0xA14E, 0x4B, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte2
    { 0xA14F, 0x59, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte3
    { 0xA150, 0xE6, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte4
    { 0xA151, 0xA2, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte5
    { 0xA152, 0x16, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte6
    { 0xA153, 0xBD, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte7
    { 0xA154, 0xEC, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte8
    { 0xA155, 0xA5, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte9
    { 0xA156, 0x31, BYTE_LEN, 0 },// SHD Gr B Data Unit3 Byte10
    { 0xA157, 0x92, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte0
    { 0xA158, 0x19, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte1
    { 0xA159, 0x8D, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte2
    { 0xA15A, 0x64, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte3
    { 0xA15B, 0x46, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte4
    { 0xA15C, 0xE3, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte5
    { 0xA15D, 0x96, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte6
    { 0xA15E, 0xC2, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte7
    { 0xA15F, 0x98, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte8
    { 0xA160, 0x65, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte9
    { 0xA161, 0x2F, BYTE_LEN, 0 },// SHD Gr B Data Unit4 Byte10
    { 0xA162, 0x4C, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte0
    { 0xA163, 0xE1, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte1
    { 0xA164, 0x4A, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte2
    { 0xA165, 0x50, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte3
    { 0xA166, 0x9A, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte4
    { 0xA167, 0xF2, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte5
    { 0xA168, 0x93, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte6
    { 0xA169, 0xA3, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte7
    { 0xA16A, 0x10, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte8
    { 0xA16B, 0xA5, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte9
    { 0xA16C, 0x29, BYTE_LEN, 0 },// SHD Gr B Data Unit5 Byte10
    { 0xA16D, 0x54, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte0
    { 0xA16E, 0xF9, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte1
    { 0xA16F, 0x4A, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte2
    { 0xA170, 0x5C, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte3
    { 0xA171, 0xFC, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte4
    { 0xA172, 0x82, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte5
    { 0xA173, 0x17, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte6
    { 0xA174, 0xC3, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte7
    { 0xA175, 0x4C, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte8
    { 0xA176, 0x25, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte9
    { 0xA177, 0x2D, BYTE_LEN, 0 },// SHD Gr B Data Unit6 Byte10
    { 0xA178, 0x47, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte0
    { 0xA179, 0xC9, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte1
    { 0xA17A, 0x0A, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte2
    { 0xA17B, 0x4D, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte3
    { 0xA17C, 0x80, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte4
    { 0xA17D, 0x82, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte5
    { 0xA17E, 0x92, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte6
    { 0xA17F, 0x97, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte7
    { 0xA180, 0x90, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte8
    { 0xA181, 0x24, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte9
    { 0xA182, 0x25, BYTE_LEN, 0 },// SHD Gr B Data Unit7 Byte10
    { 0xA183, 0x2B, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte0
    { 0xA184, 0x89, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte1
    { 0xA185, 0x89, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte2
    { 0xA186, 0x4E, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte3
    { 0xA187, 0x84, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte4
    { 0xA188, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte5
    { 0xA189, 0x95, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte6
    { 0xA18A, 0xAD, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte7
    { 0xA18B, 0x7C, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte8
    { 0xA18C, 0x05, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte9
    { 0xA18D, 0x2D, BYTE_LEN, 0 },// SHD Gr B Data Unit8 Byte10
    { 0xA18E, 0x44, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte0
    { 0xA18F, 0xB1, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte1
    { 0xA190, 0x0A, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte2
    { 0xA191, 0x4E, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte3
    { 0xA192, 0x8E, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte4
    { 0xA193, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte5
    { 0xA194, 0x92, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte6
    { 0xA195, 0x95, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte7
    { 0xA196, 0x38, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte8
    { 0xA197, 0x64, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte9
    { 0xA198, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit9 Byte10
    { 0xA199, 0x0A, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte0
    { 0xA19A, 0x59, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte1
    { 0xA19B, 0x88, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte2
    { 0xA19C, 0x44, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte3
    { 0xA19D, 0x26, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte4
    { 0xA19E, 0x92, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte5
    { 0xA19F, 0x12, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte6
    { 0xA1A0, 0x96, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte7
    { 0xA1A1, 0x04, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte8
    { 0xA1A2, 0x25, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte9
    { 0xA1A3, 0x29, BYTE_LEN, 0 },// SHD Gr B Data Unit10 Byte10
    { 0xA1A4, 0x4C, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte0
    { 0xA1A5, 0xB1, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte1
    { 0xA1A6, 0x0A, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte2
    { 0xA1A7, 0x4F, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte3
    { 0xA1A8, 0x96, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte4
    { 0xA1A9, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte5
    { 0xA1AA, 0x93, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte6
    { 0xA1AB, 0x9F, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte7
    { 0xA1AC, 0x5C, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte8
    { 0xA1AD, 0xE4, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte9
    { 0xA1AE, 0x23, BYTE_LEN, 0 },// SHD Gr B Data Unit11 Byte10
    { 0xA1AF, 0x02, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte0
    { 0xA1B0, 0x31, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte1
    { 0xA1B1, 0x88, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte2
    { 0xA1B2, 0x3F, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte3
    { 0xA1B3, 0xFE, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte4
    { 0xA1B4, 0x71, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte5
    { 0xA1B5, 0x10, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte6
    { 0xA1B6, 0x83, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte7
    { 0xA1B7, 0x7C, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte8
    { 0xA1B8, 0x04, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte9
    { 0xA1B9, 0x24, BYTE_LEN, 0 },// SHD Gr B Data Unit12 Byte10
    { 0xA1BA, 0x3A, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte0
    { 0xA1BB, 0x01, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte1
    { 0xA1BC, 0x8A, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte2
    { 0xA1BD, 0x50, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte3
    { 0xA1BE, 0x96, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte4
    { 0xA1BF, 0x02, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte5
    { 0xA1C0, 0x94, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte6
    { 0xA1C1, 0xA5, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte7
    { 0xA1C2, 0xD8, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte8
    { 0xA1C3, 0xE4, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte9
    { 0xA1C4, 0x27, BYTE_LEN, 0 },// SHD Gr B Data Unit13 Byte10
    { 0xA1C5, 0x1B, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte0
    { 0xA1C6, 0x11, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte1
    { 0xA1C7, 0x89, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte2
    { 0xA1C8, 0x41, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte3
    { 0xA1C9, 0x10, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte4
    { 0xA1CA, 0x12, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte5
    { 0xA1CB, 0x10, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte6
    { 0xA1CC, 0x80, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte7
    { 0xA1CD, 0x24, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte8
    { 0xA1CE, 0x04, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte9
    { 0xA1CF, 0x21, BYTE_LEN, 0 },// SHD Gr B Data Unit14 Byte10
    { 0xA1D0, 0x21, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte0
    { 0xA1D1, 0x19, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte1
    { 0xA1D2, 0xC9, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte2
    { 0xA1D3, 0x4E, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte3
    { 0xA1D4, 0x84, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte4
    { 0xA1D5, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte5
    { 0xA1D6, 0x14, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte6
    { 0xA1D7, 0xA6, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte7
    { 0xA1D8, 0x38, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte8
    { 0xA1D9, 0x25, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte9
    { 0xA1DA, 0x2B, BYTE_LEN, 0 },// SHD Gr B Data Unit15 Byte10
    { 0xA1DB, 0x41, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte0
    { 0xA1DC, 0x59, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte1
    { 0xA1DD, 0x8A, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte2
    { 0xA1DE, 0x4A, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte3
    { 0xA1DF, 0x62, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte4
    { 0xA1E0, 0x62, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte5
    { 0xA1E1, 0x11, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte6
    { 0xA1E2, 0x8D, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte7
    { 0xA1E3, 0x44, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte8
    { 0xA1E4, 0x44, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte9
    { 0xA1E5, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit16 Byte10
    { 0xA1E6, 0x18, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte0
    { 0xA1E7, 0xD9, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte1
    { 0xA1E8, 0x08, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte2
    { 0xA1E9, 0x4B, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte3
    { 0xA1EA, 0x68, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte4
    { 0xA1EB, 0x52, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte5
    { 0xA1EC, 0x14, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte6
    { 0xA1ED, 0xA8, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte7
    { 0xA1EE, 0x3C, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte8
    { 0xA1EF, 0xA5, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte9
    { 0xA1F0, 0x2B, BYTE_LEN, 0 },// SHD Gr B Data Unit17 Byte10
    { 0xA1F1, 0x65, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte0
    { 0xA1F2, 0x89, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte1
    { 0xA1F3, 0xCB, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte2
    { 0xA1F4, 0x55, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte3
    { 0xA1F5, 0xC2, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte4
    { 0xA1F6, 0x12, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte5
    { 0xA1F7, 0x14, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte6
    { 0xA1F8, 0xA5, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte7
    { 0xA1F9, 0xCC, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte8
    { 0xA1FA, 0x64, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte9
    { 0xA1FB, 0x27, BYTE_LEN, 0 },// SHD Gr B Data Unit18 Byte10
    { 0xA1FC, 0x30, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte0
    { 0xA1FD, 0xA9, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte1
    { 0xA1FE, 0x49, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte2
    { 0xA1FF, 0x4D, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte3
    { 0xA200, 0x7A, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte4
    { 0xA201, 0x12, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte5
    { 0xA202, 0x94, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte6
    { 0xA203, 0xA6, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte7
    { 0xA204, 0x58, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte8
    { 0xA205, 0x05, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte9
    { 0xA206, 0x2D, BYTE_LEN, 0 },// SHD Gr B Data Unit19 Byte10
    { 0xA207, 0x61, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte0
    { 0xA208, 0xB1, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte1
    { 0xA209, 0x8B, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte2
    { 0xA20A, 0x60, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte3
    { 0xA20B, 0x22, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte4
    { 0xA20C, 0xB3, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte5
    { 0xA20D, 0x97, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte6
    { 0xA20E, 0xC4, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte7
    { 0xA20F, 0x7C, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte8
    { 0xA210, 0x45, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte9
    { 0xA211, 0x2D, BYTE_LEN, 0 },// SHD Gr B Data Unit20 Byte10
    { 0xA212, 0x51, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte0
    { 0xA213, 0xF1, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte1
    { 0xA214, 0x4A, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte2
    { 0xA215, 0x53, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte3
    { 0xA216, 0xB2, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte4
    { 0xA217, 0x02, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte5
    { 0xA218, 0x15, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte6
    { 0xA219, 0xAF, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte7
    { 0xA21A, 0x70, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte8
    { 0xA21B, 0xE5, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte9
    { 0xA21C, 0x2D, BYTE_LEN, 0 },// SHD Gr B Data Unit21 Byte10
    { 0xA21D, 0x78, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte0
    { 0xA21E, 0x79, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte1
    { 0xA21F, 0xCC, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte2
    { 0xA220, 0x5F, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte3
    { 0xA221, 0x2E, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte4
    { 0xA222, 0x73, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte5
    { 0xA223, 0x99, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte6
    { 0xA224, 0xD4, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte7
    { 0xA225, 0x6C, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte8
    { 0xA226, 0xA6, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte9
    { 0xA227, 0x35, BYTE_LEN, 0 },// SHD Gr B Data Unit22 Byte10
    { 0xA228, 0x8B, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte0
    { 0xA229, 0xE9, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte1
    { 0xA22A, 0x4C, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte2
    { 0xA22B, 0x5F, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte3
    { 0xA22C, 0x1E, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte4
    { 0xA22D, 0x83, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte5
    { 0xA22E, 0x17, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte6
    { 0xA22F, 0xC5, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte7
    { 0xA230, 0xF0, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte8
    { 0xA231, 0x05, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte9
    { 0xA232, 0x32, BYTE_LEN, 0 },// SHD Gr B Data Unit23 Byte10
    { 0xA233, 0x89, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte0
    { 0xA234, 0x09, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte1
    { 0xA235, 0x0D, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte2
    { 0xA236, 0x67, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte3
    { 0xA237, 0x6A, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte4
    { 0xA238, 0x73, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte5
    { 0xA239, 0x19, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte6
    { 0xA23A, 0xD8, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte7
    { 0xA23B, 0xEC, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte8
    { 0xA23C, 0x65, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte9
    { 0xA23D, 0x31, BYTE_LEN, 0 },// SHD Gr B Data Unit24 Byte10
    { 0xA23E, 0x8E, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte0
    { 0xA23F, 0x09, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte1
    { 0xA240, 0x8D, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte2
    { 0xA241, 0x63, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte3
    { 0xA242, 0x42, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte4
    { 0xA243, 0x23, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte5
    { 0xA244, 0x98, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte6
    { 0xA245, 0xCA, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte7
    { 0xA246, 0x00, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte8
    { 0xA247, 0x66, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte9
    { 0xA248, 0x32, BYTE_LEN, 0 },// SHD Gr B Data Unit26 Byte10
    { 0xA249, 0x82, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte0
    { 0xA24A, 0xB1, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte1
    { 0xA24B, 0xCC, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte2
    { 0xA24C, 0x63, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte3
    { 0xA24D, 0x4E, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte4
    { 0xA24E, 0x13, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte5
    { 0xA24F, 0x19, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte6
    { 0xA250, 0xD5, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte7
    { 0xA251, 0xF8, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte8
    { 0xA252, 0xC5, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte9
    { 0xA253, 0x32, BYTE_LEN, 0 },// SHD Gr B Data Unit0 Byte10
    { 0xA254, 0x91, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte0
    { 0xA255, 0x21, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte1
    { 0xA256, 0x0D, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte2
    { 0xA257, 0x68, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte3
    { 0xA258, 0x20, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte4
    { 0xA259, 0xD3, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte5
    { 0xA25A, 0x98, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte6
    { 0xA25B, 0xC9, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte7
    { 0xA25C, 0x90, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte8
    { 0xA25D, 0x26, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte9
    { 0xA25E, 0x36, BYTE_LEN, 0 },// SHD R1 Data Unit0 Byte10
    { 0xA25F, 0xA6, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte0
    { 0xA260, 0x79, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte1
    { 0xA261, 0xCD, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte2
    { 0xA262, 0x6B, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte3
    { 0xA263, 0x36, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte4
    { 0xA264, 0x93, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte5
    { 0xA265, 0x18, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte6
    { 0xA266, 0xC2, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte7
    { 0xA267, 0x2C, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte8
    { 0xA268, 0xA6, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte9
    { 0xA269, 0x33, BYTE_LEN, 0 },// SHD R1 Data Unit1 Byte10
    { 0xA26A, 0xB8, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte0
    { 0xA26B, 0xE1, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte1
    { 0xA26C, 0x4D, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte2
    { 0xA26D, 0x65, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte3
    { 0xA26E, 0x0E, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte4
    { 0xA26F, 0x53, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte5
    { 0xA270, 0x16, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte6
    { 0xA271, 0xAA, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte7
    { 0xA272, 0x38, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte8
    { 0xA273, 0xA5, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte9
    { 0xA274, 0x2A, BYTE_LEN, 0 },// SHD R1 Data Unit2 Byte10
    { 0xA275, 0x68, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte0
    { 0xA276, 0x69, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte1
    { 0xA277, 0x8C, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte2
    { 0xA278, 0x66, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte3
    { 0xA279, 0xE8, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte4
    { 0xA27A, 0x12, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte5
    { 0xA27B, 0x16, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte6
    { 0xA27C, 0xA2, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte7
    { 0xA27D, 0xC4, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte8
    { 0xA27E, 0x64, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte9
    { 0xA27F, 0x25, BYTE_LEN, 0 },// SHD R1 Data Unit3 Byte10
    { 0xA280, 0x33, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte0
    { 0xA281, 0x31, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte1
    { 0xA282, 0x4A, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte2
    { 0xA283, 0x59, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte3
    { 0xA284, 0xF0, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte4
    { 0xA285, 0x02, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte5
    { 0xA286, 0x96, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte6
    { 0xA287, 0xA6, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte7
    { 0xA288, 0xB4, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte8
    { 0xA289, 0x44, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte9
    { 0xA28A, 0x22, BYTE_LEN, 0 },// SHD R1 Data Unit4 Byte10
    { 0xA28B, 0x0A, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte0
    { 0xA28C, 0x99, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte1
    { 0xA28D, 0xC8, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte2
    { 0xA28E, 0x4B, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte3
    { 0xA28F, 0xA4, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte4
    { 0xA290, 0x42, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte5
    { 0xA291, 0x16, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte6
    { 0xA292, 0xAB, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte7
    { 0xA293, 0x18, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte8
    { 0xA294, 0x25, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte9
    { 0xA295, 0x24, BYTE_LEN, 0 },// SHD R1 Data Unit5 Byte10
    { 0xA296, 0x06, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte0
    { 0xA297, 0xE9, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte1
    { 0xA298, 0xC7, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte2
    { 0xA299, 0x41, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte3
    { 0xA29A, 0x48, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte4
    { 0xA29B, 0xA2, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte5
    { 0xA29C, 0x94, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte6
    { 0xA29D, 0xAC, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte7
    { 0xA29E, 0x60, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte8
    { 0xA29F, 0x05, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte9
    { 0xA2A0, 0x29, BYTE_LEN, 0 },// SHD R1 Data Unit6 Byte10
    { 0xA2A1, 0x24, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte0
    { 0xA2A2, 0x49, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte1
    { 0xA2A3, 0x88, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte2
    { 0xA2A4, 0x40, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte3
    { 0xA2A5, 0x16, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte4
    { 0xA2A6, 0x82, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte5
    { 0xA2A7, 0x12, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte6
    { 0xA2A8, 0xA6, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte7
    { 0xA2A9, 0x6C, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte8
    { 0xA2AA, 0x25, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte9
    { 0xA2AB, 0x2D, BYTE_LEN, 0 },// SHD R1 Data Unit7 Byte10
    { 0xA2AC, 0x55, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte0
    { 0xA2AD, 0xA9, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte1
    { 0xA2AE, 0x09, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte2
    { 0xA2AF, 0x47, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte3
    { 0xA2B0, 0x28, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte4
    { 0xA2B1, 0xD2, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte5
    { 0xA2B2, 0x91, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte6
    { 0xA2B3, 0x9C, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte7
    { 0xA2B4, 0x68, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte8
    { 0xA2B5, 0x85, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte9
    { 0xA2B6, 0x2D, BYTE_LEN, 0 },// SHD R1 Data Unit8 Byte10
    { 0xA2B7, 0x83, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte0
    { 0xA2B8, 0x79, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte1
    { 0xA2B9, 0x8B, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte2
    { 0xA2BA, 0x54, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte3
    { 0xA2BB, 0x82, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte4
    { 0xA2BC, 0xA2, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte5
    { 0xA2BD, 0x13, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte6
    { 0xA2BE, 0xA1, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte7
    { 0xA2BF, 0x58, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte8
    { 0xA2C0, 0xA5, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte9
    { 0xA2C1, 0x2E, BYTE_LEN, 0 },// SHD R1 Data Unit9 Byte10
    { 0xA2C2, 0x88, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte0
    { 0xA2C3, 0x41, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte1
    { 0xA2C4, 0xCD, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte2
    { 0xA2C5, 0x66, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte3
    { 0xA2C6, 0xF0, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte4
    { 0xA2C7, 0x62, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte5
    { 0xA2C8, 0x16, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte6
    { 0xA2C9, 0xB1, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte7
    { 0xA2CA, 0xA0, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte8
    { 0xA2CB, 0x85, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte9
    { 0xA2CC, 0x2F, BYTE_LEN, 0 },// SHD R1 Data Unit10 Byte10
    { 0xA2CD, 0xA4, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte0
    { 0xA2CE, 0x81, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte1
    { 0xA2CF, 0x4D, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte2
    { 0xA2D0, 0x70, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte3
    { 0xA2D1, 0x88, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte4
    { 0xA2D2, 0xF3, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte5
    { 0xA2D3, 0x1A, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte6
    { 0xA2D4, 0xCF, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte7
    { 0xA2D5, 0x6C, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte8
    { 0xA2D6, 0x26, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte9
    { 0xA2D7, 0x34, BYTE_LEN, 0 },// SHD R1 Data Unit11 Byte10
    { 0xA2D8, 0xB4, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte0
    { 0xA2D9, 0x89, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte1
    { 0xA2DA, 0xCE, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte2
    { 0xA2DB, 0x73, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte3
    { 0xA2DC, 0x42, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte4
    { 0xA2DD, 0x63, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte5
    { 0xA2DE, 0x9B, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte6
    { 0xA2DF, 0xDA, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte7
    { 0xA2E0, 0xA4, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte8
    { 0xA2E1, 0xE6, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte9
    { 0xA2E2, 0x34, BYTE_LEN, 0 },// SHD R1 Data Unit12 Byte10
    { 0xA2E3, 0xAB, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte0
    { 0xA2E4, 0xD9, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte1
    { 0xA2E5, 0x4D, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte2
    { 0xA2E6, 0x71, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte3
    { 0xA2E7, 0x64, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte4
    { 0xA2E8, 0x03, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte5
    { 0xA2E9, 0x13, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte6
    { 0xA2EA, 0xBC, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte7
    { 0xA2EB, 0x44, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte8
    { 0xA2EC, 0x14, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte9
    { 0xA2ED, 0xA6, BYTE_LEN, 0 },// SHD R1 Data Unit13 Byte10
    { 0xA2EE, 0xC6, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte0
    { 0xA2EF, 0xC9, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte1
    { 0xA2F0, 0x4E, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte2
    { 0xA2F1, 0x75, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte3
    { 0xA2F2, 0x80, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte4
    { 0xA2F3, 0xC3, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte5
    { 0xA2F4, 0x9B, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte6
    { 0xA2F5, 0xE1, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte7
    { 0xA2F6, 0x60, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte8
    { 0xA2F7, 0xE7, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte9
    { 0xA2F8, 0x3C, BYTE_LEN, 0 },// SHD R2 Data Unit0 Byte10
    { 0xA2F9, 0xDE, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte0
    { 0xA2FA, 0x31, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte1
    { 0xA2FB, 0x0F, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte2
    { 0xA2FC, 0x79, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte3
    { 0xA2FD, 0x96, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte4
    { 0xA2FE, 0x43, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte5
    { 0xA2FF, 0x1B, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte6
    { 0xA300, 0xD7, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte7
    { 0xA301, 0xD8, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte8
    { 0xA302, 0xA6, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte9
    { 0xA303, 0x39, BYTE_LEN, 0 },// SHD R2 Data Unit1 Byte10
    { 0xA304, 0xEE, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte0
    { 0xA305, 0x99, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte1
    { 0xA306, 0x4F, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte2
    { 0xA307, 0x71, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte3
    { 0xA308, 0x64, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte4
    { 0xA309, 0x83, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte5
    { 0xA30A, 0x98, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte6
    { 0xA30B, 0xB8, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte7
    { 0xA30C, 0xA8, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte8
    { 0xA30D, 0x65, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte9
    { 0xA30E, 0x2E, BYTE_LEN, 0 },// SHD R2 Data Unit2 Byte10
    { 0xA30F, 0x8A, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte0
    { 0xA310, 0xC1, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte1
    { 0xA311, 0x4D, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte2
    { 0xA312, 0x72, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte3
    { 0xA313, 0x38, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte4
    { 0xA314, 0x13, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte5
    { 0xA315, 0x18, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte6
    { 0xA316, 0xAE, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte7
    { 0xA317, 0x04, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte8
    { 0xA318, 0x25, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte9
    { 0xA319, 0x27, BYTE_LEN, 0 },// SHD R2 Data Unit3 Byte10
    { 0xA31A, 0x44, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte0
    { 0xA31B, 0xF1, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte1
    { 0xA31C, 0x8A, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte2
    { 0xA31D, 0x61, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte3
    { 0xA31E, 0x3E, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte4
    { 0xA31F, 0x23, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte5
    { 0xA320, 0x98, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte6
    { 0xA321, 0xB3, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte7
    { 0xA322, 0xEC, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte8
    { 0xA323, 0x24, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte9
    { 0xA324, 0x23, BYTE_LEN, 0 },// SHD R2 Data Unit4 Byte10
    { 0xA325, 0x0F, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte0
    { 0xA326, 0xD1, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte1
    { 0xA327, 0x48, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte2
    { 0xA328, 0x4F, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte3
    { 0xA329, 0xD6, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte4
    { 0xA32A, 0x42, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte5
    { 0xA32B, 0x18, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte6
    { 0xA32C, 0xBB, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte7
    { 0xA32D, 0x74, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte8
    { 0xA32E, 0x85, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte9
    { 0xA32F, 0x25, BYTE_LEN, 0 },// SHD R2 Data Unit5 Byte10
    { 0xA330, 0x08, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte0
    { 0xA331, 0xE9, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte1
    { 0xA332, 0x07, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte2
    { 0xA333, 0x42, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte3
    { 0xA334, 0x5A, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte4
    { 0xA335, 0xF2, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte5
    { 0xA336, 0x95, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte6
    { 0xA337, 0xBA, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte7
    { 0xA338, 0xE4, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte8
    { 0xA339, 0x25, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte9
    { 0xA33A, 0x2C, BYTE_LEN, 0 },// SHD R2 Data Unit6 Byte10
    { 0xA33B, 0x31, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte0
    { 0xA33C, 0x61, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte1
    { 0xA33D, 0x88, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte2
    { 0xA33E, 0x40, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte3
    { 0xA33F, 0x18, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte4
    { 0xA340, 0x02, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte5
    { 0xA341, 0x13, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte6
    { 0xA342, 0xB0, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte7
    { 0xA343, 0xD8, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte8
    { 0xA344, 0xC5, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte9
    { 0xA345, 0x31, BYTE_LEN, 0 },// SHD R2 Data Unit7 Byte10
    { 0xA346, 0x73, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte0
    { 0xA347, 0x31, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte1
    { 0xA348, 0x0A, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte2
    { 0xA349, 0x49, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte3
    { 0xA34A, 0x32, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte4
    { 0xA34B, 0x42, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte5
    { 0xA34C, 0x92, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte6
    { 0xA34D, 0xA3, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte7
    { 0xA34E, 0xC8, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte8
    { 0xA34F, 0x65, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte9
    { 0xA350, 0x31, BYTE_LEN, 0 },// SHD R2 Data Unit8 Byte10
    { 0xA351, 0xAA, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte0
    { 0xA352, 0x81, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte1
    { 0xA353, 0x8C, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte2
    { 0xA354, 0x5A, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte3
    { 0xA355, 0xA0, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte4
    { 0xA356, 0x82, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte5
    { 0xA357, 0x94, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte6
    { 0xA358, 0xA8, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte7
    { 0xA359, 0xAC, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte8
    { 0xA35A, 0x65, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte9
    { 0xA35B, 0x32, BYTE_LEN, 0 },// SHD R2 Data Unit9 Byte10
    { 0xA35C, 0xAC, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte0
    { 0xA35D, 0x91, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte1
    { 0xA35E, 0x8E, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte2
    { 0xA35F, 0x70, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte3
    { 0xA360, 0x2E, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte4
    { 0xA361, 0x13, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte5
    { 0xA362, 0x18, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte6
    { 0xA363, 0xBD, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte7
    { 0xA364, 0x0C, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte8
    { 0xA365, 0x66, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte9
    { 0xA366, 0x33, BYTE_LEN, 0 },// SHD R2 Data Unit10 Byte10
    { 0xA367, 0xCA, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte0
    { 0xA368, 0xD1, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte1
    { 0xA369, 0xCE, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte2
    { 0xA36A, 0x7B, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte3
    { 0xA36B, 0xE0, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte4
    { 0xA36C, 0x83, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte5
    { 0xA36D, 0x1D, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte6
    { 0xA36E, 0xE2, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte7
    { 0xA36F, 0xF8, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte8
    { 0xA370, 0xE6, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte9
    { 0xA371, 0x38, BYTE_LEN, 0 },// SHD R2 Data Unit11 Byte10
    { 0xA372, 0xDD, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte0
    { 0xA373, 0xF1, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte1
    { 0xA374, 0x4F, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte2
    { 0xA375, 0x7F, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte3
    { 0xA376, 0x96, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte4
    { 0xA377, 0x33, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte5
    { 0xA378, 0x1E, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte6
    { 0xA379, 0xF0, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte7
    { 0xA37A, 0x44, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte8
    { 0xA37B, 0xE7, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte9
    { 0xA37C, 0x39, BYTE_LEN, 0 },// SHD R2 Data Unit12 Byte10
    { 0xA37D, 0xD4, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte0
    { 0xA37E, 0x39, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte1
    { 0xA37F, 0x4F, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte2
    { 0xA380, 0x7C, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte3
    { 0xA381, 0xBC, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte4
    { 0xA382, 0xB3, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte5
    { 0xA383, 0x17, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte6
    { 0xA384, 0xC5, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte7
    { 0xA385, 0x1C, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte8
    { 0xA386, 0x06, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte9
    { 0xA387, 0x2F, BYTE_LEN, 0 },// SHD R2 Data Unit13 Byte10
    { 0xA388, 0x7B, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte0
    { 0xA389, 0x51, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte1
    { 0xA38A, 0xCC, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte2
    { 0xA38B, 0x61, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte3
    { 0xA38C, 0xF0, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte4
    { 0xA38D, 0x72, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte5
    { 0xA38E, 0x17, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte6
    { 0xA38F, 0xBE, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte7
    { 0xA390, 0x48, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte8
    { 0xA391, 0x46, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte9
    { 0xA392, 0x34, BYTE_LEN, 0 },// SHD B2 Data Unit0 Byte10
    { 0xA393, 0x9C, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte0
    { 0xA394, 0xA9, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte1
    { 0xA395, 0xCC, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte2
    { 0xA396, 0x64, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte3
    { 0xA397, 0x04, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte4
    { 0xA398, 0x23, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte5
    { 0xA399, 0x17, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte6
    { 0xA39A, 0xB8, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte7
    { 0xA39B, 0xD4, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte8
    { 0xA39C, 0x45, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte9
    { 0xA39D, 0x31, BYTE_LEN, 0 },// SHD B2 Data Unit1 Byte10
    { 0xA39E, 0xA6, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte0
    { 0xA39F, 0x49, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte1
    { 0xA3A0, 0xCD, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte2
    { 0xA3A1, 0x5F, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte3
    { 0xA3A2, 0xEA, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte4
    { 0xA3A3, 0x72, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte5
    { 0xA3A4, 0x95, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte6
    { 0xA3A5, 0xA4, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte7
    { 0xA3A6, 0x18, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte8
    { 0xA3A7, 0x65, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte9
    { 0xA3A8, 0x29, BYTE_LEN, 0 },// SHD B2 Data Unit2 Byte10
    { 0xA3A9, 0x5D, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte0
    { 0xA3AA, 0xF1, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte1
    { 0xA3AB, 0xCB, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte2
    { 0xA3AC, 0x61, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte3
    { 0xA3AD, 0xBE, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte4
    { 0xA3AE, 0x12, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte5
    { 0xA3AF, 0x15, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte6
    { 0xA3B0, 0x9E, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte7
    { 0xA3B1, 0xB4, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte8
    { 0xA3B2, 0x04, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte9
    { 0xA3B3, 0x25, BYTE_LEN, 0 },// SHD B2 Data Unit3 Byte10
    { 0xA3B4, 0x2F, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte0
    { 0xA3B5, 0x01, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte1
    { 0xA3B6, 0x0A, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte2
    { 0xA3B7, 0x57, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte3
    { 0xA3B8, 0xD6, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte4
    { 0xA3B9, 0xF2, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte5
    { 0xA3BA, 0x14, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte6
    { 0xA3BB, 0xA0, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte7
    { 0xA3BC, 0xA0, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte8
    { 0xA3BD, 0x44, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte9
    { 0xA3BE, 0x22, BYTE_LEN, 0 },// SHD B2 Data Unit4 Byte10
    { 0xA3BF, 0x0C, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte0
    { 0xA3C0, 0xA9, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte1
    { 0xA3C1, 0x48, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte2
    { 0xA3C2, 0x4B, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte3
    { 0xA3C3, 0x8E, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte4
    { 0xA3C4, 0x32, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte5
    { 0xA3C5, 0x95, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte6
    { 0xA3C6, 0xA3, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte7
    { 0xA3C7, 0xEC, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte8
    { 0xA3C8, 0x84, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte9
    { 0xA3C9, 0x23, BYTE_LEN, 0 },// SHD B2 Data Unit5 Byte10
    { 0xA3CA, 0x04, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte0
    { 0xA3CB, 0xF9, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte1
    { 0xA3CC, 0xC7, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte2
    { 0xA3CD, 0x41, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte3
    { 0xA3CE, 0x42, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte4
    { 0xA3CF, 0xF2, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte5
    { 0xA3D0, 0x93, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte6
    { 0xA3D1, 0xA3, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte7
    { 0xA3D2, 0x34, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte8
    { 0xA3D3, 0x25, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte9
    { 0xA3D4, 0x28, BYTE_LEN, 0 },// SHD B2 Data Unit6 Byte10
    { 0xA3D5, 0x22, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte0
    { 0xA3D6, 0x49, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte1
    { 0xA3D7, 0x08, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte2
    { 0xA3D8, 0x40, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte3
    { 0xA3D9, 0x0E, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte4
    { 0xA3DA, 0x22, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte5
    { 0xA3DB, 0x92, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte6
    { 0xA3DC, 0x9F, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte7
    { 0xA3DD, 0x1C, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte8
    { 0xA3DE, 0x45, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte9
    { 0xA3DF, 0x2B, BYTE_LEN, 0 },// SHD B2 Data Unit7 Byte10
    { 0xA3E0, 0x4C, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte0
    { 0xA3E1, 0x89, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte1
    { 0xA3E2, 0x09, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte2
    { 0xA3E3, 0x46, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte3
    { 0xA3E4, 0x22, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte4
    { 0xA3E5, 0x72, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte5
    { 0xA3E6, 0x11, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte6
    { 0xA3E7, 0x96, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte7
    { 0xA3E8, 0x20, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte8
    { 0xA3E9, 0xA5, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte9
    { 0xA3EA, 0x2A, BYTE_LEN, 0 },// SHD B2 Data Unit8 Byte10
    { 0xA3EB, 0x70, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte0
    { 0xA3EC, 0xF9, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte1
    { 0xA3ED, 0x8A, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte2
    { 0xA3EE, 0x51, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte3
    { 0xA3EF, 0x66, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte4
    { 0xA3F0, 0x02, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte5
    { 0xA3F1, 0x13, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte6
    { 0xA3F2, 0x9A, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte7
    { 0xA3F3, 0x04, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte8
    { 0xA3F4, 0x45, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte9
    { 0xA3F5, 0x2B, BYTE_LEN, 0 },// SHD B2 Data Unit9 Byte10
    { 0xA3F6, 0x67, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte0
    { 0xA3F7, 0x59, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte1
    { 0xA3F8, 0x0C, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte2
    { 0xA3F9, 0x60, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte3
    { 0xA3FA, 0xC4, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte4
    { 0xA3FB, 0x12, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte5
    { 0xA3FC, 0x95, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte6
    { 0xA3FD, 0xA6, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte7
    { 0xA3FE, 0x40, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte8
    { 0xA3FF, 0xA5, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte9
    { 0xA400, 0x2B, BYTE_LEN, 0 },// SHD B2 Data Unit10 Byte10
    { 0xA401, 0x7E, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte0
    { 0xA402, 0x39, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte1
    { 0xA403, 0xCC, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte2
    { 0xA404, 0x67, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte3
    { 0xA405, 0x3E, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte4
    { 0xA406, 0xC3, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte5
    { 0xA407, 0x98, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte6
    { 0xA408, 0xBD, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte7
    { 0xA409, 0xDC, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte8
    { 0xA40A, 0x85, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte9
    { 0xA40B, 0x2F, BYTE_LEN, 0 },// SHD B2 Data Unit11 Byte10
    { 0xA40C, 0x8D, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte0
    { 0xA40D, 0x29, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte1
    { 0xA40E, 0x0D, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte2
    { 0xA40F, 0x69, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte3
    { 0xA410, 0x0E, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte4
    { 0xA411, 0x73, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte5
    { 0xA412, 0x19, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte6
    { 0xA413, 0xC9, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte7
    { 0xA414, 0x0C, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte8
    { 0xA415, 0x06, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte9
    { 0xA416, 0x30, BYTE_LEN, 0 },// SHD B2 Data Unit12 Byte10
    { 0xA417, 0x83, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte0
    { 0xA418, 0x91, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte1
    { 0xA419, 0x8C, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte2
    { 0xA41A, 0x67, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte3
    { 0xA41B, 0x1A, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte4
    { 0xA41C, 0x03, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte5
    { 0xA41D, 0x00, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte6
    { 0xA41E, 0x00, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte7
    { 0xA41F, 0x00, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte8
    { 0xA420, 0x00, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte9
    { 0xA421, 0x04, BYTE_LEN, 0 },// SHD B2 Data Unit13 Byte10
    
    ////////////////////////////////////////
    //// Cat. : USERCTRL (PICT related) ////
    ////////////////////////////////////////
    
    { 0x0068, 0x5F, BYTE_LEN, 0 },// SHD_EN
    //{ 0x0100, 0x00, BYTE_LEN, 0 },// SCENE_SELECT
    { 0x0105, 0x40, BYTE_LEN, 0 },// PICT1_SN1

};

struct isx006_i2c_reg_conf isx006_preload3_2nd_settings[] = {
    //for ISX006 ES2, 0x, 0x, 0x, 0x, 0x, 0x
    //for Period_3 (KMO), 0x, 0x, 0x, 0x, 0x, 0x
    //version 11, 0x, 0x, 0x, 0x, 0x, 0x
    //2010.07 17 , 0x, 0x, 0x, 0x, 0x, 0x
    //Imaging LSI BD, 0x Semiconductor BG, 0x CPDG, 0x Sony Corp. , 0x, 0x, 0x
    
    ////////////////////////////////////////
    /////////// Cat. : PICT_GAIN ///////////
    ////////////////////////////////////////
    
    { 0x5842, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_0
    { 0x5843, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_1
    { 0x5844, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_2
    { 0x5845, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_3
    { 0x5846, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_4
    { 0x5847, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_5
    { 0x5848, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_6
    { 0x5849, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_7
    { 0x584A, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_8
    { 0x584B, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_9
    { 0x584C, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_10
    { 0x584D, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_11
    { 0x584E, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_12
    { 0x584F, 0x07, BYTE_LEN, 0 },// MAIN_GAINADJ_13
    { 0x5850, 0x00, BYTE_LEN, 0 },// Gain-linked mode target setting0: AGC gain coordination (including shutter interpolation), 0x 1: AGC gain interpolation (not including gain interpolation), 0x 2: AE scale coordination, 0x 3: Reference scale coordination, 0x 4: Dark level coordination
    { 0x5858, 0x0A2A, WORD_LEN, 0 },// Gain coordination threshold value setting  Low brightness/High gain side
    { 0x585A, 0x0396, WORD_LEN, 0 },// Gain coordination threshold value setting  Medium brightness/Medium gain side
    { 0x585C, 0x0000, WORD_LEN, 0 },// Gain coordination threshold value setting  Higih brightness/Low gain side
    { 0x5882, 0x0B29, WORD_LEN, 0 },// Gain coordination threshold value setting  Low brightness/High gain side
    { 0x5884, 0x0100, WORD_LEN, 0 },// Gain coordination threshold value setting  Medium brightness/Medium gain side
    { 0x5886, 0x0000, WORD_LEN, 0 },// Gain coordination threshold value setting  Higih brightness/Low gain side
    { 0x5888, 0x0024, WORD_LEN, 0 },// Luminance threshold value A setting value
    { 0x588A, 0x000B, WORD_LEN, 0 },// Luminance threshold value B setting value
    { 0x588C, 0x000A, WORD_LEN, 0 },// Luminance threshold value C setting value
    { 0x588E, 0x0030, WORD_LEN, 0 },// Chroma threshold value A setting value
    { 0x5890, 0x0028, WORD_LEN, 0 },// Chroma threshold value B setting value
    { 0x5892, 0x0020, WORD_LEN, 0 },// Chroma threshold value C setting value
    { 0x5894, 0x0004, WORD_LEN, 0 },// Low-range Apcon positive-side coring range (X-coordinate) for threshold value A
    { 0x589A, 0x0008, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value A
    { 0x589C, 0x0012, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value B
    { 0x589E, 0x0012, WORD_LEN, 0 },// Low-range Apcon positive-side 1st contact point X-coordinate for threshold value C
    { 0x58A6, 0x0004, WORD_LEN, 0 },// Low-range Apcon negative-side coring range (X-coordinate) for threshold value A
    { 0x58AC, 0x0008, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value A
    { 0x58AE, 0x0012, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value B
    { 0x58B0, 0x0012, WORD_LEN, 0 },// Low-range Apcon negative-side 1st contact point X-coordinate for threshold value C
    { 0x58B8, 0x0001, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value A
    { 0x58BA, 0x0001, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value B
    { 0x58BC, 0x0000, WORD_LEN, 0 },// Middle-range Apcon positive-side coring range (X-coordinate) for threshold value C
    { 0x58BE, 0x0004, WORD_LEN, 0 },// Middle-range Apcon positive-side 1st contact point X-coordinate for threshold value A
    { 0x58C0, 0x0005, WORD_LEN, 0 },// Middle-range Apcon positive-side 1st contact point X-coordinate for threshold value B
    { 0x58CA, 0x0001, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value A
    { 0x58CC, 0x0001, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value B
    { 0x58CE, 0x0000, WORD_LEN, 0 },// Middle-range Apcon negative-side coring range (X-coordinate) for threshold value C
    { 0x58D0, 0x0004, WORD_LEN, 0 },// Middle-range Apcon negative-side 1st contact point X-coordinate for threshold value A
    { 0x58D4, 0x0004, WORD_LEN, 0 },// Middle-range Apcon negative-side 1st contact point X-coordinate for threshold value C
    { 0x58DC, 0x000A, WORD_LEN, 0 },// High-range Apcon positive-side coring range (X-coordinate) for threshold value A
    { 0x58E2, 0x000E, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value A
    { 0x58E4, 0x000C, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value B
    { 0x58E6, 0x000A, WORD_LEN, 0 },// High-range Apcon positive-side 1st contact point X-coordinate for threshold value C
    { 0x58EE, 0x000A, WORD_LEN, 0 },// High-range Apcon negative-side coring range (X-coordinate) for threshold value A
    { 0x58F2, 0x0005, WORD_LEN, 0 },// High-range Apcon negative-side coring range (X-coordinate) for threshold value C
    { 0x58F4, 0x000E, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value A
    { 0x58F6, 0x000C, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value B
    { 0x58F8, 0x000D, WORD_LEN, 0 },// High-range Apcon negative-side 1st contact point X-coordinate for threshold value C
    { 0x5906, 0x015E, WORD_LEN, 0 },// Threshold value A, 0x low-range Apcon 2nd contact point X-coordinate
    { 0x5908, 0x015E, WORD_LEN, 0 },// Threshold value B, 0x low-range Apcon 2nd contact point X-coordinate
    { 0x590A, 0x015E, WORD_LEN, 0 },// Threshold value C, 0x low-range Apcon 2nd contact point X-coordinate
    { 0x590C, 0x0226, WORD_LEN, 0 },// Threshold value A, 0x low-range Apcon 3rd contact point X-coordinate
    { 0x590E, 0x0226, WORD_LEN, 0 },// Threshold value B, 0x low-range Apcon 3rd contact point X-coordinate
    { 0x5910, 0x0226, WORD_LEN, 0 },// Threshold value C, 0x low-range Apcon 3rd contact point X-coordinate
    { 0x591E, 0x0003, WORD_LEN, 0 },// Threshold value A, 0x Clip value from low-range Apcon 4th contact point and after
    { 0x5920, 0x0004, WORD_LEN, 0 },// Threshold value B, 0x Clip value from low-range Apcon 4th contact point and after
    { 0x5922, 0x0004, WORD_LEN, 0 },// Threshold value C, 0x Clip value from low-range Apcon 4th contact point and after
    { 0x5926, 0x0082, WORD_LEN, 0 },// Threshold value B, 0x middle-range Apcon 1st contact point X-coordinate
    { 0x592A, 0x0320, WORD_LEN, 0 },// Threshold value A, 0x middle-range Apcon 2nd contact point X-coordinate
    { 0x592C, 0x0320, WORD_LEN, 0 },// Threshold value B, 0x middle-range Apcon 2nd contact point X-coordinate
    { 0x592E, 0x0320, WORD_LEN, 0 },// Threshold value C, 0x middle-range Apcon 2nd contact point X-coordinate
    { 0x5930, 0x0384, WORD_LEN, 0 },// Threshold value A, 0x middle-range Apcon 3rd contact point X-coordinate
    { 0x5932, 0x0384, WORD_LEN, 0 },// Threshold value B, 0x middle-range Apcon 3rd contact point X-coordinate
    { 0x5934, 0x0384, WORD_LEN, 0 },// Threshold value C, 0x middle-range Apcon 3rd contact point X-coordinate
    { 0x5942, 0x0003, WORD_LEN, 0 },// Threshold value A, 0x Clip value from middle-range Apcon 4th contact point and after
    { 0x5944, 0x0004, WORD_LEN, 0 },// Threshold value B, 0x Clip value from middle-range Apcon 4th contact point and after
    { 0x5946, 0x0004, WORD_LEN, 0 },// Threshold value C, 0x Clip value from middle-range Apcon 4th contact point and after
    { 0x594A, 0x0023, WORD_LEN, 0 },// Threshold value B, 0x high-range Apcon 1st contact point X-coordinate
    { 0x594E, 0x0032, WORD_LEN, 0 },// Threshold value A, 0x high-range Apcon 2nd contact point X-coordinate
    { 0x5950, 0x0023, WORD_LEN, 0 },// Threshold value B, 0x high-range Apcon 2nd contact point X-coordinate
    { 0x5952, 0x0032, WORD_LEN, 0 },// Threshold value C, 0x high-range Apcon 2nd contact point X-coordinate
    { 0x5954, 0x00C8, WORD_LEN, 0 },// Threshold value A, 0x high-range Apcon 3rd contact point X-coordinate
    { 0x5956, 0x005D, WORD_LEN, 0 },// Threshold value B, 0x high-range Apcon 3rd contact point X-coordinate
    { 0x5958, 0x00C8, WORD_LEN, 0 },// Threshold value C, 0x high-range Apcon 3rd contact point X-coordinate
    { 0x5968, 0x0000, WORD_LEN, 0 },// Threshold value B, 0x Clip value from high-range Apcon 4th contact point and after
    { 0x596A, 0x0000, WORD_LEN, 0 },// Threshold value C, 0x Clip value from high-range Apcon 4th contact point and after
    { 0x596C, 0x32, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (before LVD) for threshold value A.
    { 0x596D, 0x32, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (before LVD) for threshold value B.
    { 0x596F, 0x32, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value A.
    { 0x5970, 0x40, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value B.
    { 0x5971, 0x40, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (before LVD) for threshold value C.
    { 0x5972, 0x32, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value A.
    { 0x5973, 0x40, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value B.
    { 0x5974, 0x37, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (before LVD) for threshold value C.
    { 0x5975, 0x20, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value A.
    { 0x5976, 0x40, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value B.
    { 0x5977, 0x4A, BYTE_LEN, 0 },// This sets the low-range Apcon Gain (after Coring) for threshold value C.
    { 0x5979, 0x5A, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (after Coring) for threshold value B.
    { 0x597A, 0x50, BYTE_LEN, 0 },// This sets the middle-range Apcon Gain (after Coring) for threshold value C.
    { 0x597C, 0x5A, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (after Coring) for threshold value B.
    { 0x597D, 0x87, BYTE_LEN, 0 },// This sets the high-range Apcon Gain (after Coring) for threshold value C.
    { 0x597E, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value A
    { 0x597F, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value B
    { 0x5980, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side low to 1st contact point for threshold value C
    { 0x5981, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side 1st contact point and after for threshold value A
    { 0x5982, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon positive-side 1st contact point and after for threshold value B
    { 0x5985, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side low to 1st contact point for threshold value B
    { 0x5986, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side low to 1st contact point for threshold value C
    { 0x5987, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value A
    { 0x5988, 0x10, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value B
    { 0x5989, 0x08, BYTE_LEN, 0 },// Slope from low-range Apcon negative-side 1st contact point and after for threshold value C
    { 0x598A, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value A
    { 0x598B, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value B
    { 0x598C, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side low to 1st contact point for threshold value C
    { 0x598D, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side 1st contact point and after for threshold value A
    { 0x598F, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon positive-side 1st contact point and after for threshold value C
    { 0x5991, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side low to 1st contact point for threshold value B
    { 0x5992, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side low to 1st contact point for threshold value C
    { 0x5993, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value A
    { 0x5994, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value B
    { 0x5995, 0x10, BYTE_LEN, 0 },// Slope from middle-range Apcon negative-side 1st contact point and after for threshold value C
    
    { 0x5997, 0x0C, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side low to 1st contact point for threshold value B
    { 0x5998, 0x0C, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side low to 1st contact point for threshold value C
    { 0x5999, 0x04, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value A
    { 0x599A, 0x03, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value B
    { 0x599B, 0x08, BYTE_LEN, 0 },// Slope from high-range Apcon positive-side 1st contact point and after for threshold value C
    
    { 0x599D, 0x08, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side low to 1st contact point for threshold value B
    { 0x599E, 0x10, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side low to 1st contact point for threshold value C
    { 0x599F, 0x04, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side 1st contact point and after for threshold value A
    { 0x59A0, 0x03, BYTE_LEN, 0 },// Slope from high-range Apcon negative-side 1st contact point and after for threshold value B
    { 0x59A1, 0x08, BYTE_LEN, 0 },// Slope from , 0xhigh-range Apcon negative-side 1st contact point and after for threshold value C
    
    { 0x59A5, 0x20, BYTE_LEN, 0 },// Threshold value A, 0x Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59A6, 0x20, BYTE_LEN, 0 },// Threshold value B, 0x Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59A7, 0x20, BYTE_LEN, 0 },// Threshold value C, 0x Slope from low-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59A8, 0x50, BYTE_LEN, 0 },// Threshold value A, 0x Slope from low-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59A9, 0x50, BYTE_LEN, 0 },// Threshold value B, 0x Slope from low-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59AA, 0x50, BYTE_LEN, 0 },// Threshold value C, 0x Slope from low-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59AC, 0x90, BYTE_LEN, 0 },// Threshold value B, 0x Slope from middle-range Apcon origin to 1st contact point (absolute value)
    { 0x59AE, 0x50, BYTE_LEN, 0 },// Threshold value A, 0x Slope from middle-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59B1, 0x50, BYTE_LEN, 0 },// Threshold value A, 0x Slope from middle-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59B2, 0x50, BYTE_LEN, 0 },// Threshold value B, 0x Slope from middle-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59B3, 0x50, BYTE_LEN, 0 },// Threshold value C, 0x Slope from middle-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59B5, 0xFF, BYTE_LEN, 0 },// Threshold value B, 0x Slope from high-range Apcon origin to 1st contact point (absolute value)
    { 0x59B7, 0x30, BYTE_LEN, 0 },// Threshold value A, 0x Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59B8, 0xE0, BYTE_LEN, 0 },// Threshold value B, 0x Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59B9, 0x30, BYTE_LEN, 0 },// Threshold value C, 0x Slope from high-range Apcon 2nd contact point to 3rd contact point (absolute value, 0x treated as negative coefficient)
    { 0x59BA, 0x20, BYTE_LEN, 0 },// Threshold value A, 0x Slope from high-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59BB, 0x20, BYTE_LEN, 0 },// Threshold value B, 0x Slope from high-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59BC, 0x20, BYTE_LEN, 0 },// Threshold value C, 0x Slope from high-range Apcon 3rd contact point and after (absolute value, 0x treated as negative coefficient)
    { 0x59BD, 0x30, BYTE_LEN, 0 },// LMT_WEIGHT_A
    { 0x59BE, 0x60, BYTE_LEN, 0 },// LMT_WEIGHT_B
    
    { 0x59C5, 0x08, BYTE_LEN, 0 },// CS_SLP_C_A
    { 0x59C6, 0x08, BYTE_LEN, 0 },// CS_SLP_C_B
    { 0x59C7, 0x08, BYTE_LEN, 0 },// CS_SLP_C_C
    { 0x59C8, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_A
    { 0x59C9, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_B
    { 0x59CA, 0x1E, BYTE_LEN, 0 },// CS_CBHLEV_C
    { 0x59CB, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_A
    { 0x59CC, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_B
    { 0x59CD, 0x1E, BYTE_LEN, 0 },// CS_CRHLEV_C
    { 0x59D4, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_A
    { 0x59D6, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_B
    { 0x59D8, 0x0000, WORD_LEN, 0 },// CS_CBLLEV_C
    { 0x59DA, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_A
    { 0x59DC, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_B
    { 0x59DE, 0xFFE2, WORD_LEN, 0 },// CS_CRLLEV_C
    { 0x59EC, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_A
    { 0x59ED, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_B
    { 0x59EE, 0xF9, BYTE_LEN, 0 },// CS_APSH_H_C
    { 0x59F2, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_A
    { 0x59F3, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_B
    { 0x59F4, 0xF9, BYTE_LEN, 0 },// CS_APSH_L_C
    
    ///////////////////////////////////////
    ///////// Cat.::AF Driver KMO /////////
    ///////////////////////////////////////
    
    { 0xC000, 0xB5F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC002, 0xB081, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC004, 0x4D16, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC006, 0x4C17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC008, 0x4F17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC00A, 0x4A18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC00C, 0x4918, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC00E, 0x2300, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC010, 0x2F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC012, 0xD904, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC014, 0x5CEE, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC016, 0x54E6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC018, 0x3301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC01A, 0x42BB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC01C, 0xD3FA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC01E, 0x2300, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC020, 0x2700, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC022, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC024, 0xD903, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC026, 0x54D7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC028, 0x3301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC02A, 0x428B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC02C, 0xD3FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC02E, 0x4911, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC030, 0x6088, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC032, 0x9A02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC034, 0x4810, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC036, 0x6010, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC038, 0x4810, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC03A, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC03C, 0x6888, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC03E, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC040, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC042, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC044, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC046, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC048, 0xFBE8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC04A, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC04C, 0xD005, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC04E, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC050, 0x9A03, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC052, 0x43C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC054, 0x8110, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC056, 0x1C38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC058, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC05A, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC05C, 0xB004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC05E, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC060, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC062, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC064, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC066, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC068, 0x0004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC06A, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC06C, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC06E, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC070, 0x000C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC072, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC074, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC076, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC078, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC07A, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC07C, 0x01CC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC07E, 0x0006, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC080, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC082, 0x781F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC084, 0x2F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC086, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC088, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC08A, 0xF8B6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC08C, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC08E, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC090, 0xF801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC092, 0xE7FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC094, 0xB5FF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC096, 0xB083, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC098, 0x1C0C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC09A, 0x1C1F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC09C, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC09E, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0A0, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0A2, 0x43EB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0A4, 0x4E53, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0A6, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0A8, 0xD127, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0AA, 0x80F2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0AC, 0x1AA0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0AE, 0xD502, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0B0, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0B2, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0B4, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0B6, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0B8, 0x7031, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0BA, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0BC, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0BE, 0x8070, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0C0, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0C2, 0xD11A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0C4, 0x2019, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0C6, 0x02C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0C8, 0x4320, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0CA, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0CC, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0CE, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0D0, 0xF8EC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0D2, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0D4, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0D6, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0D8, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0DA, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0DC, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0DE, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0E0, 0xFB9C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0E2, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0E4, 0xD004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0E6, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0E8, 0x43C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0EA, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0EC, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0EE, 0xE07E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0F0, 0x9803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0F2, 0x8004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0F4, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0F6, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0F8, 0xE079, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0FA, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0FC, 0x4E3D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC0FE, 0x9002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC100, 0x78B9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC102, 0x0040, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC104, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC106, 0x78F9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC108, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC10A, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC10C, 0x0049, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC10E, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC110, 0xFB89, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC112, 0x0404, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC114, 0x0C24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC116, 0x8A38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC118, 0x42A0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC11A, 0xDA02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC11C, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC11E, 0x1C04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC120, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC122, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC124, 0x9101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC126, 0x9802, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC128, 0x2600, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC12A, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC12C, 0xDD0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC12E, 0x1C30, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC130, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC132, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC134, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC136, 0xF89E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC138, 0x1940, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC13A, 0x0405, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC13C, 0x0C2D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC13E, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC140, 0x3601, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC142, 0x42B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC144, 0xDCF3, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC146, 0x4E2B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC148, 0x88B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC14A, 0x1B40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC14C, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC14E, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC150, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC152, 0x2301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC154, 0x42D8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC156, 0xD113, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC158, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC15A, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC15C, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC15E, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC160, 0x8139, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC162, 0xE00D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC164, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC166, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC168, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC16A, 0xFAA6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC16C, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC16E, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC170, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC172, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC174, 0xFAA1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC176, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC178, 0xD002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC17A, 0x8938, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC17C, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC17E, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC180, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC182, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC184, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC186, 0xDD31, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC188, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC18A, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC18C, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC18E, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC190, 0xF871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC192, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC194, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC196, 0xD107, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC198, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC19A, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC19C, 0xDD04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC19E, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1A0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1A2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1A4, 0x3901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1A6, 0x80B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1A8, 0x7831, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1AA, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1AC, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1AE, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1B0, 0x1808, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1B2, 0xE001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1B4, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1B6, 0x1A08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1B8, 0x80F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1BA, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1BC, 0x2319, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1BE, 0x02DB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1C0, 0x4318, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1C2, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1C4, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1C6, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1C8, 0xF870, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1CA, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1CC, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1CE, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1D0, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1D2, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1D4, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1D6, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1D8, 0xFB20, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1DA, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1DC, 0xD183, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1DE, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1E0, 0x9903, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1E2, 0x8008, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1E4, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1E6, 0x3501, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1E8, 0x42A8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1EA, 0xDCCD, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1EC, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1EE, 0xB007, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1F0, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1F2, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1F4, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1F6, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1F8, 0xB5F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1FA, 0x1C1C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1FC, 0x1C15, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC1FE, 0x1C06, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC200, 0x1C0F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC202, 0x2019, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC204, 0x02C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC206, 0x4338, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC208, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC20A, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC20C, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC20E, 0xF84D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC210, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC212, 0x480A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC214, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC216, 0x6880, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC218, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC21A, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC21C, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC21E, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC220, 0xFAFC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC222, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC224, 0xD001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC226, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC228, 0xE006, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC22A, 0x1C38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC22C, 0x1C29, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC22E, 0x1C22, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC230, 0x8037, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC232, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC234, 0xF805, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC236, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC238, 0xBDF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC23A, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC23C, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC23E, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC240, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC242, 0x1C17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC244, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC246, 0xD500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC248, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC24A, 0x89BA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC24C, 0x0901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC24E, 0x4351, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC250, 0x0700, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC252, 0x0F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC254, 0xD000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC256, 0x1851, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC258, 0x89F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC25A, 0x1841, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC25C, 0x6978, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC25E, 0x1809, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC260, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC262, 0xFA2A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC264, 0x4B02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC266, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC268, 0xD900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC26A, 0x1C18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC26C, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC26E, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC270, 0x7FFF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC272, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC274, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC276, 0x7893, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC278, 0x4283, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC27A, 0xDD05, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC27C, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC27E, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC280, 0x1C0A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC282, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC284, 0x1C58, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC286, 0xE009, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC288, 0x7853, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC28A, 0x78D2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC28C, 0x1A9F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC28E, 0x4287, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC290, 0xDC09, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC292, 0x1A18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC294, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC296, 0x1C0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC298, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC29A, 0x1C50, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC29C, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC29E, 0xFAC2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2A0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2A2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2A4, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2A6, 0x1C08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2A8, 0xE7FC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2AA, 0x0201, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2AC, 0x1200, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2AE, 0x4308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2B0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2B2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2B4, 0x46F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2B6, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2B8, 0x0B0D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0xC2BA, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
    { 0x485C, 0x02BC, WORD_LEN, 0 },// AF_DRV_SIZE
    { 0x485E, 0x1F8D, WORD_LEN, 0 },// AF_DRV_CHKSUM_CODE
    { 0x000A, 0x01, BYTE_LEN, 0 },// AF_EXT
    
    ///////////////////////////////////////
    /////////////// Cat.:AF ///////////////
    ///////////////////////////////////////
    
    { 0x4808, 0x0019, WORD_LEN, 0 },// Minimum AF-OPD_TH value for IIR
    { 0x480A, 0x00FA, WORD_LEN, 0 },// Maximum AF-OPD_TH value for IIR
    { 0x480C, 0x03EB, WORD_LEN, 0 },// AF scale offset value used for AF_IIR_PEAK_OPD_TH_MIN
    { 0x480E, 0x03E8, WORD_LEN, 0 },// Minimum AF-OPD_TH value for FIR
    { 0x4810, 0x03E8, WORD_LEN, 0 },// Maximum AF-OPD_TH value for FIR
    { 0x4812, 0x03EB, WORD_LEN, 0 },// AF scale offset value used for AF_FIR_PEAK_OPD_TH_MIN
    { 0x481C, 0x00, BYTE_LEN, 0 },// Evaluation value averaging mode
    { 0x4826, 0x0005, WORD_LEN, 0 },// FIR judgment threshold on Wobble [as percent(0.1%)] or [Numerical value]
    { 0x482C, 0x001E, WORD_LEN, 0 },// FIR peak judgment threshold on Climb [as percent(0.1%)] or [Numerical value]
    { 0x4832, 0x01F4, WORD_LEN, 0 },// FIR judgment threshold for Judge [as percent(0.1%)] or [Numerical value]
    { 0x4838, 0x0020, WORD_LEN, 0 },// Maximum value of extended movement on Wobble, 0x Climb failure
    { 0x4844, 0x0080, WORD_LEN, 0 },// FINE search range offset
    { 0x484F, 0x00, BYTE_LEN, 0 },// Exposure time-dependent lens control flag
    { 0x4856, 0x14, BYTE_LEN, 0 },// AF_DROPRATE_ON_PEAK_DETECT_FIR
    { 0x486C, 0x0040, WORD_LEN, 0 },// AF_DRV_AMOUNT_TONEAR_F
    { 0x486E, 0x0010, WORD_LEN, 0 },// AF_DRV_AMOUNT_TONEAR_S
    { 0x4870, 0x0040, WORD_LEN, 0 },// AF_DRV_AMOUNT_TOFAR_F
    { 0x4872, 0x0010, WORD_LEN, 0 },// AF_DRV_AMOUNT_TOFAR_S
    { 0x4876, 0x0000, WORD_LEN, 0 },// AF_AREA_LOW_TYPE1
    { 0x4878, 0x0300, WORD_LEN, 0 },// AF_AREA_HIGH_TYPE1
    { 0x487A, 0x0000, WORD_LEN, 0 },// AF_AREA_LOW_TYPE2
    { 0x4884, 0x00, BYTE_LEN, 0 },// AF_MONICHG_MOVE_F //uriwei
    { 0x4889, 0x18, BYTE_LEN, 0 },// AF_SENDNUM_ALL
    { 0x488A, 0x00, BYTE_LEN, 0 },// AF_SENDNUM_UP
    { 0x488B, 0x00, BYTE_LEN, 0 },// AF_SENDNUM_DOWN
    { 0x488C, 0x0004, WORD_LEN, 0 },// AF_SENDAMOUNT_ADDLIMIT
    { 0x489A, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Specifies the luminance side low level threshold value for HPF FIR coring processing luminance dependence.
    { 0x489C, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Specifies the luminance side low level threshold value for HPF FIR coring processing luminance dependence.
    { 0x489E, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Specifies the luminance side low level threshold value for HPF FIR coring processing luminance dependence.
    { 0x48A6, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48A8, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48AA, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the medium-luminance area gradient for HST FIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48B2, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48B4, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48B6, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the minimum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48BE, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48C0, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48C2, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the maximum coring amount for HPF FIR coring processing luminance dependence.
    { 0x48CA, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48CC, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48CE, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48D0, 0x03FF, WORD_LEN, 0 },// Value1 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48D2, 0x03FF, WORD_LEN, 0 },// Value2 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48D4, 0x03FF, WORD_LEN, 0 },// Value3 setting: Specifies the luminance side low level threshold value for HPF IIR coring processing luminance dependence.
    { 0x48D6, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48D8, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48DA, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the medium-luminance area gradient for HPF IIR coring processing luminance dependence. A negative or positive gradient can be specified.
    { 0x48E2, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48E4, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48E6, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48E8, 0x03FF, WORD_LEN, 0 },// Value1 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48EA, 0x03FF, WORD_LEN, 0 },// Value2 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48EC, 0x03FF, WORD_LEN, 0 },// Value3 setting: Sets the minimum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48EE, 0x5EC1, WORD_LEN, 0 },// SclTh1 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48F0, 0x68F6, WORD_LEN, 0 },// SclTh2 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48F2, 0x77A4, WORD_LEN, 0 },// SclTh3 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48F4, 0x03FF, WORD_LEN, 0 },// Value1 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48F6, 0x03FF, WORD_LEN, 0 },// Value2 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    { 0x48F8, 0x03FF, WORD_LEN, 0 },// Value3 setting: Sets the maximum coring amount for HPF IIR coring processing luminance dependence.
    
    { 0x495C, 0x01, BYTE_LEN, 0 },// Lens movement anti-noise limiter control flag
    { 0x4968, 0x00, BYTE_LEN, 0 },// Stop decision setting during Wobble/Climb
    { 0x4969, 0x08, BYTE_LEN, 0 },// Threshold change decision count until restoring Wobble during Judge
    { 0x496C, 0x00, BYTE_LEN, 0 },// Set whether to enable FILTER setting
    { 0x496E, 0x01F4, WORD_LEN, 0 },// Uniform increase evaluation value threshold (for FIR)
    { 0x4970, 0x03E8, WORD_LEN, 0 },// Uniform increase evaluation value threshold (for IIR)
    
    ///////////////////////////////////////
    ///////////// Cat.:AF EXT /////////////
    ///////////////////////////////////////
    
    { 0x6E00, 0x01, BYTE_LEN, 0 },// FIR/IIR/FIR&IIR switch
    { 0x6E08, 0x001E, WORD_LEN, 0 },// The threshold of the AF scale to refer to during a lens edge stop
    { 0x6E12, 0x0020, WORD_LEN, 0 },// The threshold of the AF scale to refer to at the time of stable waiting
    { 0x6E8E, 0x0096, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Wobble.
    { 0x6E90, 0x01F4, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Climb.
    { 0x6E92, 0x0096, WORD_LEN, 0 },// The threshold of the AF scale to judge as scene change in Judge.
    
    ///////////////////////////////////////
    //////// Cat.:MODE(AF related) ////////
    ///////////////////////////////////////
    
    { 0x4C2C, 0x042E, WORD_LEN, 0 },// AF_OPD0_HDELAY
    { 0x4C2E, 0x02C5, WORD_LEN, 0 },// AF_OPD0_VDELAY
    { 0x4C30, 0x0217, WORD_LEN, 0 },// AF_OPD0_HVALID
    { 0x4C32, 0x0217, WORD_LEN, 0 },// AF_OPD0_VVALID
    { 0x4C34, 0x048A, WORD_LEN, 0 },// AF_OPD1_HDELAY
    { 0x4C36, 0x0105, WORD_LEN, 0 },// AF_OPD1_VDELAY
    { 0x4C38, 0x015F, WORD_LEN, 0 },// AF_OPD1_HVALID
    { 0x4C3A, 0x015F, WORD_LEN, 0 },// AF_OPD1_VVALID
    { 0x4C44, 0x026E, WORD_LEN, 0 },// AF_OPD3_HDELAY
    { 0x4C46, 0x0321, WORD_LEN, 0 },// AF_OPD3_VDELAY
    { 0x4C48, 0x015F, WORD_LEN, 0 },// AF_OPD3_HVALID
    { 0x4C4A, 0x015F, WORD_LEN, 0 },// AF_OPD3_VVALID
    { 0x4C4C, 0x042E, WORD_LEN, 0 },// AF_OPD4_HDELAY
    { 0x4C4E, 0x02C5, WORD_LEN, 0 },// AF_OPD4_VDELAY
    { 0x4C50, 0x0217, WORD_LEN, 0 },// AF_OPD4_HVALID
    { 0x4C52, 0x0217, WORD_LEN, 0 },// AF_OPD4_VVALID
    { 0x4C54, 0x048A, WORD_LEN, 0 },// AF_OPD5_HDELAY
    { 0x4C56, 0x0321, WORD_LEN, 0 },// AF_OPD5_VDELAY
    { 0x4C58, 0x015F, WORD_LEN, 0 },// AF_OPD5_HVALID
    { 0x4C5A, 0x015F, WORD_LEN, 0 },// AF_OPD5_VVALID
    { 0x4C64, 0x06A6, WORD_LEN, 0 },// AF_OPD7_HDELAY
    { 0x4C66, 0x0321, WORD_LEN, 0 },// AF_OPD7_VDELAY
    { 0x4C68, 0x015F, WORD_LEN, 0 },// AF_OPD7_HVALID
    { 0x4C6A, 0x015F, WORD_LEN, 0 },// AF_OPD7_VVALID
    { 0x4C74, 0x048A, WORD_LEN, 0 },// AF_OPD9_HDELAY
    { 0x4C76, 0x053D, WORD_LEN, 0 },// AF_OPD9_VDELAY
    { 0x4C78, 0x015F, WORD_LEN, 0 },// AF_OPD9_HVALID
    { 0x4C7A, 0x015F, WORD_LEN, 0 },// AF_OPD9_VVALID
    { 0x4C7D, 0x00, BYTE_LEN, 0 },// AF_OPD1B_WEIGHT
    { 0x4C7E, 0x00, BYTE_LEN, 0 },// AF_OPD2A_WEIGHT
    { 0x4C7F, 0x00, BYTE_LEN, 0 },// AF_OPD2B_WEIGHT
    { 0x4C82, 0x00, BYTE_LEN, 0 },// AF_OPD4A_WEIGHT
    { 0x4C83, 0x00, BYTE_LEN, 0 },// AF_OPD4B_WEIGHT
    { 0x4C84, 0x00, BYTE_LEN, 0 },// AF_OPD5A_WEIGHT
    { 0x4C85, 0x00, BYTE_LEN, 0 },// AF_OPD5B_WEIGHT
    
    ///////////////////////////////////////
    //////////// Cat. : GAMMA1 ////////////
    ///////////////////////////////////////
    
    { 0x5438, 0x0001, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table1)
    { 0x543A, 0x0002, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table1)
    { 0x543C, 0x0004, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table1)
    { 0x543E, 0x0006, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table1)
    { 0x5440, 0x0008, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table1)
    { 0x5442, 0x000B, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table1)
    { 0x5444, 0x000E, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table1)
    { 0x5446, 0x0011, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table1)
    { 0x5448, 0x0014, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table1)
    { 0x544A, 0x0017, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table1)
    { 0x544C, 0x001B, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table1)
    { 0x544E, 0x001F, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table1)
    { 0x5450, 0x0023, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table1)
    { 0x5452, 0x0027, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table1)
    { 0x5454, 0x002C, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table1)
    { 0x5456, 0x0032, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table1)
    { 0x5458, 0x0037, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table1)
    { 0x545A, 0x0016, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table1)
    { 0x545C, 0x0052, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table1)
    { 0x545E, 0x0084, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table1)
    { 0x5460, 0x00AA, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table1)
    { 0x5462, 0x00C8, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table1)
    { 0x5464, 0x00DC, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table1)
    { 0x5466, 0x00F0, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table1)
    { 0x5468, 0x00FD, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table1)
    { 0x54A2, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -R (Table1)
    { 0x54A6, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -G (Table1)
    { 0x54AA, 0x0110, WORD_LEN, 0 },// Low-range setting/offset setting -B (Table1)
    { 0x54AE, 0x5D01, WORD_LEN, 0 },// Convergence luminance setting (Table1)
    
    ///////////////////////////////////////
    //////////// Cat. : GAMMA2 ////////////
    ///////////////////////////////////////
    
    { 0x5638, 0x0000, WORD_LEN, 0 },// RGB-Gamma G-knot1(Table2)
    { 0x563A, 0x0001, WORD_LEN, 0 },// RGB-Gamma G-knot2(Table2)
    { 0x563C, 0x0006, WORD_LEN, 0 },// RGB-Gamma G-knot3(Table2)
    { 0x563E, 0x000C, WORD_LEN, 0 },// RGB-Gamma G-knot4(Table2)
    { 0x5640, 0x0015, WORD_LEN, 0 },// RGB-Gamma G-knot5(Table2)
    { 0x5642, 0x001D, WORD_LEN, 0 },// RGB-Gamma G-knot6(Table2)
    { 0x5644, 0x0027, WORD_LEN, 0 },// RGB-Gamma G-knot7(Table2)
    { 0x5646, 0x0031, WORD_LEN, 0 },// RGB-Gamma G-knot8(Table2)
    { 0x5648, 0x003A, WORD_LEN, 0 },// RGB-Gamma G-knot9(Table2)
    { 0x564A, 0x0043, WORD_LEN, 0 },// RGB-Gamma G-knot10(Table2)
    { 0x564C, 0x004B, WORD_LEN, 0 },// RGB-Gamma G-knot11(Table2)
    { 0x564E, 0x0053, WORD_LEN, 0 },// RGB-Gamma G-knot12(Table2)
    { 0x5650, 0x005B, WORD_LEN, 0 },// RGB-Gamma G-knot13(Table2)
    { 0x5652, 0x0063, WORD_LEN, 0 },// RGB-Gamma G-knot14(Table2)
    { 0x5654, 0x006A, WORD_LEN, 0 },// RGB-Gamma G-knot15(Table2)
    { 0x5656, 0x0071, WORD_LEN, 0 },// RGB-Gamma G-knot16(Table2)
    { 0x5658, 0x007B, WORD_LEN, 0 },// RGB-Gamma G-knot17(Table2)
    { 0x565A, 0x003E, WORD_LEN, 0 },// RGB-Gamma G-knot18(Table2)
    { 0x565C, 0x00AC, WORD_LEN, 0 },// RGB-Gamma G-knot19(Table2)
    { 0x565E, 0x00D4, WORD_LEN, 0 },// RGB-Gamma G-knot20(Table2)
    { 0x5660, 0x00E6, WORD_LEN, 0 },// RGB-Gamma G-knot21(Table2)
    { 0x5662, 0x00F2, WORD_LEN, 0 },// RGB-Gamma G-knot22(Table2)
    { 0x5664, 0x00F8, WORD_LEN, 0 },// RGB-Gamma G-knot23(Table2)
    { 0x5666, 0x00FE, WORD_LEN, 0 },// RGB-Gamma G-knot24(Table2)
    { 0x5668, 0x0101, WORD_LEN, 0 },// RGB-Gamma G-knot25(Table2)
    { 0x566A, 0x0104, WORD_LEN, 0 },// RGB-Gamma G-knot26(Table2)
    { 0x56AE, 0x2300, WORD_LEN, 0 },// Convergence luminance setting (Table2)
    
    ///////////////////////////////////////
    ///////////// Cat. : PICT /////////////
    ///////////////////////////////////////
    
    { 0x4E0B, 0x01, BYTE_LEN, 0 },// Hue gain mode selection0: AUTO (coloring control)1: Fixed at setting value for POS12: Fixed at setting value for POS2
    { 0x4E0C, 0x01FE, WORD_LEN, 0 },// Chroma start
    { 0x4E0E, 0x0A2A, WORD_LEN, 0 },// Chroma end
    { 0x4E10, 0x0100, WORD_LEN, 0 },// Chroma suppress levelWhen the value larger than 100h is set, 0x it is limited at 100h.
    
    { 0x4F24, 0x3C, BYTE_LEN, 0 },// MAIN_CONFIG1
    { 0x4F25, 0x09, BYTE_LEN, 0 },// MAIN_CONFIG2
    { 0x4F2E, 0x0000, WORD_LEN, 0 },// DS_ADGRADCORE_B
    { 0x4F30, 0x0000, WORD_LEN, 0 },// DS_ADGRADCORE_C
    { 0x4F34, 0x0000, WORD_LEN, 0 },// DS_HVGRADCORE_B
    { 0x4F36, 0x0000, WORD_LEN, 0 },// DS_HVGRADCORE_C
    { 0x4F38, 0x0A, BYTE_LEN, 0 },// DS_ADGRADLIM_A
    { 0x4F39, 0x14, BYTE_LEN, 0 },// DS_ADGRADLIM_B
    { 0x4F3A, 0x14, BYTE_LEN, 0 },// DS_ADGRADLIM_C
    { 0x4F3B, 0x14, BYTE_LEN, 0 },// DS_HVGRADLIM_A
    { 0x4F3C, 0x1E, BYTE_LEN, 0 },// DS_HVGRADLIM_B
    { 0x4F3D, 0x1E, BYTE_LEN, 0 },// DS_HVGRADLIM_C
    { 0x4F3E, 0x0A, BYTE_LEN, 0 },// DS_DFCT_TH_A
    { 0x4F3F, 0x1E, BYTE_LEN, 0 },// DS_DFCT_TH_B
    { 0x4F40, 0x1E, BYTE_LEN, 0 },// DS_DFCT_TH_C
    
    ////////////////////////////////////////
    ///// Cat. : LMT (Hue/Gain for HD) /////
    ////////////////////////////////////////
    
    { 0x5062, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), 0x for HD, 0x POS1
    { 0x5064, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), 0x for HD, 0x POS1
    { 0x5066, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), 0x for HD, 0x POS1
    { 0x5068, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), 0x for HD, 0x POS1
    { 0x506A, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), 0x for HD, 0x POS1
    { 0x506C, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), 0x for HD, 0x POS1
    { 0x506E, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), 0x for HD, 0x POS1
    { 0x5070, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), 0x for HD, 0x POS1
    { 0x5073, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), 0x for HD, 0x POS1
    { 0x5075, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), 0x for HD, 0x POS1
    { 0x5077, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), 0x for HD, 0x POS1
    { 0x5079, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), 0x for HD, 0x POS1
    { 0x507A, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (1st quadrant), 0x for HD, 0x POS2
    { 0x507C, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (1st quadrant), 0x for HD, 0x POS2
    { 0x507E, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (2nd quadrant), 0x for HD, 0x POS2
    { 0x5080, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (2nd quadrant), 0x for HD, 0x POS2
    { 0x5082, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (3rd quadrant), 0x for HD, 0x POS2
    { 0x5084, 0xFFEA, WORD_LEN, 0 },// RYHUE reference value (3rd quadrant), 0x for HD, 0x POS2
    { 0x5086, 0xFFF6, WORD_LEN, 0 },// BYHUE reference value (4th quadrant), 0x for HD, 0x POS2
    { 0x5088, 0xFFE9, WORD_LEN, 0 },// RYHUE reference value (4th quadrant), 0x for HD, 0x POS2
    { 0x508B, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (1st quadrant), 0x for HD, 0x POS2
    { 0x508D, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (2nd quadrant), 0x for HD, 0x POS2
    { 0x508F, 0x56, BYTE_LEN, 0 },// BYGAIN reference value (3rd quadrant), 0x for HD, 0x POS2
    { 0x5091, 0x48, BYTE_LEN, 0 },// BYGAIN reference value (4th quadrant), 0x for HD, 0x POS2
    
    ////////////////////////////////////////
    //// Cat. : USERCTRL (PICT related) ////
    ////////////////////////////////////////
    {0x0102, 0x20, BYTE_LEN, 0 },// AWB_SN1
    {0x0103, 0x01, BYTE_LEN, 0 },// AE_SN1
    {0x0107, 0x10, BYTE_LEN, 0 },// AWB_SN2
    {0x0108, 0x01, BYTE_LEN, 0 },// AE_SN2
    {0x0109, 0x4D, BYTE_LEN, 0 },// AE_SUB_SN2
    {0x010C, 0x20, BYTE_LEN, 0 },// AWB_SN3
    {0x010D, 0x01, BYTE_LEN, 0 },// AE_SN3
    {0x010E, 0x41, BYTE_LEN, 0 },// AE_SUB_SN3
    {0x0111, 0x10, BYTE_LEN, 0 },// AWB_SN4
    {0x0112, 0x01, BYTE_LEN, 0 },// AE_SN4
    {0x0113, 0x41, BYTE_LEN, 0 },// AE_SUB_SN4
    {0x0116, 0x20, BYTE_LEN, 0 },// AWB_SN5
    {0x0117, 0x01, BYTE_LEN, 0 },// AE_SN5
    {0x0118, 0x01, BYTE_LEN, 0 },// AE_SUB_SN5
    {0x011B, 0x20, BYTE_LEN, 0 },// AWB_SN6
    {0x011C, 0x01, BYTE_LEN, 0 },// AE_SN6
    {0x011D, 0xCD, BYTE_LEN, 0 },// AE_SUB_SN6
    {0x0120, 0x20, BYTE_LEN, 0 },// AWB_SN7
    {0x0121, 0x01, BYTE_LEN, 0 },// AE_SN7
    {0x0122, 0x01, BYTE_LEN, 0 },// AE_SUB_SN7
    //{0x0125, 0x20, BYTE_LEN, 0 },// AWB_SN8
    //{0x0126, 0x01, BYTE_LEN, 0 },// AE_SN8
    //{0x0127, 0xC1, BYTE_LEN, 0 },// AE_SUB_SN8
    //{0x012A, 0x20, BYTE_LEN, 0 },// AWB_SN9
    //{0x012B, 0x01, BYTE_LEN, 0 },// AE_SN9
    //{0x012C, 0x03, BYTE_LEN, 0 },// AE_SUB_SN9
    //{0x012F, 0x20, BYTE_LEN, 0 },// AWB_SN10
    //{0x0130, 0x01, BYTE_LEN, 0 },// AE_SN10
    //{0x0131, 0x03, BYTE_LEN, 0 },// AE_SUB_SN10
    //{0x0134, 0x20, BYTE_LEN, 0 },// AWB_SN11
    //{0x0135, 0x01, BYTE_LEN, 0 },// AE_SN11
    //{0x0136, 0x03, BYTE_LEN, 0 },// AE_SUB_SN11
    //{0x0139, 0x20, BYTE_LEN, 0 },// AWB_SN12
    //{0x013A, 0x01, BYTE_LEN, 0 },// AE_SN12
    //{0x013B, 0x03, BYTE_LEN, 0 },// AE_SUB_SN12
    {0x01D3, 0x00, BYTE_LEN, 0 },// AF_SN1-Auro
    {0x01D4, 0x08, BYTE_LEN, 0 },// AF_SN2-Landscape
    {0x01D5, 0x00, BYTE_LEN, 0 },// AF_SN3
    {0x01D6, 0x00, BYTE_LEN, 0 },// AF_SN4-Bench
    {0x01D7, 0x00, BYTE_LEN, 0 },// AF_SN5-Sprots
    {0x01D8, 0x08, BYTE_LEN, 0 },// AF_SN6-Night
    {0x01D9, 0x04, BYTE_LEN, 0 },// AF_SN7-Document
    //{0x01DA, 0x00, BYTE_LEN, 0 },// AF_SN8
    //{0x01DB, 0x00, BYTE_LEN, 0 },// AF_SN9
    //{0x01DC, 0x00, BYTE_LEN, 0 },// AF_SN10
    //{0x01DD, 0x00, BYTE_LEN, 0 },// AF_SN11
    //{0x01DE, 0x00, BYTE_LEN, 0 },// AF_SN12
    {0x010A, 0x40, BYTE_LEN, 0 },// PICT1_SN2
    {0x010F, 0x40, BYTE_LEN, 0 },// PICT1_SN3
    {0x0114, 0x40, BYTE_LEN, 0 },// PICT1_SN4
    {0x0119, 0x40, BYTE_LEN, 0 },// PICT1_SN5
    {0x011E, 0x40, BYTE_LEN, 0 },// PICT1_SN6
    {0x0123, 0x90, BYTE_LEN, 0 },// PICT1_SN7
    //{0x0128, 0x40, BYTE_LEN, 0 },// PICT1_SN8
    //{0x012D, 0x40, BYTE_LEN, 0 },// PICT1_SN9
    //{0x0132, 0x40, BYTE_LEN, 0 },// PICT1_SN10
    //{0x0137, 0x40, BYTE_LEN, 0 },// PICT1_SN11
    //{0x013C, 0x40, BYTE_LEN, 0 },// PICT1_SN12
    {0x01B2, 0x59, BYTE_LEN, 0 },// UISATURATION_TYPE2
    {0x01F9, 0x65, BYTE_LEN, 0 },// PICT3_GAMMA1
    {0x01FC, 0x65, BYTE_LEN, 0 },// PICT3_GAMMA4
    {0x3208, 0x01, BYTE_LEN, 0 },/* FIH-SW3-MM-UW-performance tuning-00+*/
    /* FIH-SW3-MM-UW-set AF range-00-*/ 
    
    //////////////////////////////////////////
    //// Cat. : USERCTRL (System related) ////
    //////////////////////////////////////////
    
    { 0x001D, 0x00, BYTE_LEN, 0 },// OUTFMT_CAP
    { 0x0024, 0x0A20, WORD_LEN, 0 },// HSIZE_CAP
    { 0x002A, 0x0798, WORD_LEN, 0 },// VSIZE_CAP
    { 0x021A, 0x0280, WORD_LEN, 0 },// HSIZE_TN
    { 0x021C, 0x01E0, WORD_LEN, 0 },// VSIZE_TN
    { 0x0226, 0x06A0, WORD_LEN, 0 },// SIZE_HOLD_HOUT
    { 0x02A4, 0x0001, WORD_LEN, 0 },// VADJ_SENS_1_2
    { 0x02B8, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG1
    { 0x02BA, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG3
    { 0x02BB, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG4
    { 0x02BC, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG5
    { 0x02BD, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG6
    { 0x02BE, 0x50, BYTE_LEN, 0 },// VIF_CLKCONFIG7
    { 0x02C0, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG9
    { 0x02C1, 0x10, BYTE_LEN, 0 },// VIF_CLKCONFIG10
    { 0x033F, 0x00, BYTE_LEN, 0 },// JPGBUF_LINEFIX_F
    
    ///////////////////////////////////////
    ///////////// Cat. : JPEG /////////////
    ///////////////////////////////////////
    
    ////////////////////////////////////////
    ////////// Cat. : QTABLE_DATA //////////
    ////////////////////////////////////////
    
    ///////////////////////////////////////
    ////// Cat. : AE_FRM (for Sence) //////
    ///////////////////////////////////////

};
/* FIH-SW3-MM-UW-read vendor id-00-*/

struct isx006_i2c_reg_conf isx006_preload3_reload_settings[] = {
   
   ///////////////////////////////////////
   ///////// Cat.::AF Driver KMO /////////
   ///////////////////////////////////////
   
   { 0xC000, 0xB5F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC002, 0xB081, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC004, 0x4D16, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC006, 0x4C17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC008, 0x4F17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC00A, 0x4A18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC00C, 0x4918, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC00E, 0x2300, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC010, 0x2F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC012, 0xD904, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC014, 0x5CEE, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC016, 0x54E6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC018, 0x3301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC01A, 0x42BB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC01C, 0xD3FA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC01E, 0x2300, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC020, 0x2700, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC022, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC024, 0xD903, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC026, 0x54D7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC028, 0x3301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC02A, 0x428B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC02C, 0xD3FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC02E, 0x4911, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC030, 0x6088, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC032, 0x9A02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC034, 0x4810, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC036, 0x6010, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC038, 0x4810, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC03A, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC03C, 0x6888, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC03E, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC040, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC042, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC044, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC046, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC048, 0xFBE8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC04A, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC04C, 0xD005, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC04E, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC050, 0x9A03, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC052, 0x43C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC054, 0x8110, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC056, 0x1C38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC058, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC05A, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC05C, 0xB004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC05E, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC060, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC062, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC064, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC066, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC068, 0x0004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC06A, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC06C, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC06E, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC070, 0x000C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC072, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC074, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC076, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC078, 0x0D44, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC07A, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC07C, 0x01CC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC07E, 0x0006, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC080, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC082, 0x781F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC084, 0x2F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC086, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC088, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC08A, 0xF8B6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC08C, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC08E, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC090, 0xF801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC092, 0xE7FB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC094, 0xB5FF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC096, 0xB083, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC098, 0x1C0C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC09A, 0x1C1F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC09C, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC09E, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0A0, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0A2, 0x43EB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0A4, 0x4E53, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0A6, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0A8, 0xD127, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0AA, 0x80F2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0AC, 0x1AA0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0AE, 0xD502, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0B0, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0B2, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0B4, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0B6, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0B8, 0x7031, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0BA, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0BC, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0BE, 0x8070, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0C0, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0C2, 0xD11A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0C4, 0x2019, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0C6, 0x02C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0C8, 0x4320, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0CA, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0CC, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0CE, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0D0, 0xF8EC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0D2, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0D4, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0D6, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0D8, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0DA, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0DC, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0DE, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0E0, 0xFB9C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0E2, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0E4, 0xD004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0E6, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0E8, 0x43C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0EA, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0EC, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0EE, 0xE07E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0F0, 0x9803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0F2, 0x8004, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0F4, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0F6, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0F8, 0xE079, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0FA, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0FC, 0x4E3D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC0FE, 0x9002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC100, 0x78B9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC102, 0x0040, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC104, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC106, 0x78F9, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC108, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC10A, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC10C, 0x0049, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC10E, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC110, 0xFB89, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC112, 0x0404, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC114, 0x0C24, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC116, 0x8A38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC118, 0x42A0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC11A, 0xDA02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC11C, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC11E, 0x1C04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC120, 0xE000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC122, 0x2100, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC124, 0x9101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC126, 0x9802, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC128, 0x2600, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC12A, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC12C, 0xDD0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC12E, 0x1C30, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC130, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC132, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC134, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC136, 0xF89E, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC138, 0x1940, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC13A, 0x0405, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC13C, 0x0C2D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC13E, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC140, 0x3601, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC142, 0x42B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC144, 0xDCF3, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC146, 0x4E2B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC148, 0x88B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC14A, 0x1B40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC14C, 0x80B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC14E, 0x2308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC150, 0x5EF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC152, 0x2301, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC154, 0x42D8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC156, 0xD113, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC158, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC15A, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC15C, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC15E, 0x2101, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC160, 0x8139, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC162, 0xE00D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC164, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC166, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC168, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC16A, 0xFAA6, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC16C, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC16E, 0x8871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC170, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC172, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC174, 0xFAA1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC176, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC178, 0xD002, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC17A, 0x8938, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC17C, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC17E, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC180, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC182, 0x2500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC184, 0x2800, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC186, 0xDD31, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC188, 0x1C28, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC18A, 0x1C21, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC18C, 0x1C3A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC18E, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC190, 0xF871, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC192, 0x9901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC194, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC196, 0xD107, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC198, 0x88B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC19A, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC19C, 0xDD04, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC19E, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1A0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1A2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1A4, 0x3901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1A6, 0x80B1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1A8, 0x7831, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1AA, 0x2900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1AC, 0xD102, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1AE, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1B0, 0x1808, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1B2, 0xE001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1B4, 0x88F1, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1B6, 0x1A08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1B8, 0x80F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1BA, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1BC, 0x2319, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1BE, 0x02DB, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1C0, 0x4318, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1C2, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1C4, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1C6, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1C8, 0xF870, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1CA, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1CC, 0x68B0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1CE, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1D0, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1D2, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1D4, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1D6, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1D8, 0xFB20, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1DA, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1DC, 0xD183, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1DE, 0x88F0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1E0, 0x9903, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1E2, 0x8008, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1E4, 0x7878, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1E6, 0x3501, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1E8, 0x42A8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1EA, 0xDCCD, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1EC, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1EE, 0xB007, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1F0, 0xBDF0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1F2, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1F4, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1F6, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1F8, 0xB5F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1FA, 0x1C1C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1FC, 0x1C15, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC1FE, 0x1C06, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC200, 0x1C0F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC202, 0x2019, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC204, 0x02C0, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC206, 0x4338, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC208, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC20A, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC20C, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC20E, 0xF84D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC210, 0x9000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC212, 0x480A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC214, 0x466A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC216, 0x6880, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC218, 0x2103, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC21A, 0x6803, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC21C, 0x200C, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC21E, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC220, 0xFAFC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC222, 0x2801, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC224, 0xD001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC226, 0x2000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC228, 0xE006, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC22A, 0x1C38, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC22C, 0x1C29, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC22E, 0x1C22, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC230, 0x8037, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC232, 0xF000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC234, 0xF805, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC236, 0x2001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC238, 0xBDF8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC23A, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC23C, 0x0D48, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC23E, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC240, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC242, 0x1C17, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC244, 0x1A40, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC246, 0xD500, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC248, 0x4240, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC24A, 0x89BA, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC24C, 0x0901, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC24E, 0x4351, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC250, 0x0700, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC252, 0x0F00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC254, 0xD000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC256, 0x1851, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC258, 0x89F8, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC25A, 0x1841, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC25C, 0x6978, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC25E, 0x1809, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC260, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC262, 0xFA2A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC264, 0x4B02, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC266, 0x4298, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC268, 0xD900, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC26A, 0x1C18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC26C, 0x8138, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC26E, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC270, 0x7FFF, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC272, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC274, 0xB580, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC276, 0x7893, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC278, 0x4283, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC27A, 0xDD05, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC27C, 0x3001, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC27E, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC280, 0x1C0A, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC282, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC284, 0x1C58, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC286, 0xE009, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC288, 0x7853, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC28A, 0x78D2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC28C, 0x1A9F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC28E, 0x4287, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC290, 0xDC09, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC292, 0x1A18, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC294, 0x4348, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC296, 0x1C0B, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC298, 0x1C01, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC29A, 0x1C50, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC29C, 0xF67F, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC29E, 0xFAC2, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2A0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2A2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2A4, 0xBD80, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2A6, 0x1C08, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2A8, 0xE7FC, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2AA, 0x0201, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2AC, 0x1200, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2AE, 0x4308, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2B0, 0x0400, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2B2, 0x0C00, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2B4, 0x46F7, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2B6, 0x0000, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2B8, 0x0B0D, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0xC2BA, 0x0018, WORD_LEN, 0 },// .\AF_RAMDRV_I2C_KMO_ES2
   { 0x485C, 0x02BC, WORD_LEN, 0 },// AF_DRV_SIZE
   { 0x485E, 0x1F8D, WORD_LEN, 0 },// AF_DRV_CHKSUM_CODE
   { 0x000A, 0x01, BYTE_LEN, 0 },// AF_EXT
};
/* FIH-SW3-MM-UW-read vendor id-00-*/


/* FIH-SW3-MM-SL-PatchForCameraFeature-01+{ */
struct isx006_i2c_reg_conf isx006_sport_settings[] = {
   	// ISX006 ES2 KMO V03_2
   	//,Scene5,Sports_Shutter2ms_16_7ms_ISO250
   	{0x6A01,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.LSB),
   	{0x6A02,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.MSB),
   	{0x6A03,0x04, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(0),
   	{0x6A04,0x62, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.LSB),
   	{0x6A05,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.MSB),
   	{0x6A06,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(1),
   	{0x6A07,0x5D, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.LSB),
   	{0x6A08,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.MSB),
   	{0x6A09,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(2),
   	{0x6A0A,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.LSB),
   	{0x6A0B,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.MSB),
   	{0x6A0C,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(3),
   	{0x6A0D,0xE1, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.LSB),
   	{0x6A0E,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.MSB),
   	{0x6A0F,0x08, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(4)
   	{0x6A10,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.LSB)
   	{0x6A11,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.MSB)
   	{0x6A12,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(5)
   	{0x6A13,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.LSB)
   	{0x6A14,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.MSB)
   	{0x6A15,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(6)
   	{0x6A16,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.LSB)
   	{0x6A17,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.MSB)
   	{0x6A18,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(7)
   	{0x6A19,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.LSB)
   	{0x6A1A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.MSB)
   	{0x6A1B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(8)
   	{0x6A1C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.LSB)
   	{0x6A1D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.MSB)
   	{0x6A1E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(9)
   	{0x6A1F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.LSB)
   	{0x6A20,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.MSB)
   	{0x6A21,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(10)
   	{0x6A22,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.LSB)
   	{0x6A23,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.MSB)
   	{0x6A24,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(11)
   	{0x6A25,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.LSB)
   	{0x6A26,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.MSB)
   	{0x6A27,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(12)
   	{0x6A28,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.LSB)
   	{0x6A29,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.MSB)
   	{0x6A2A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(13)
   	{0x6A2B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.LSB)
   	{0x6A2C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.MSB)
   	{0x6A2D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(14)
   	{0x6A2E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.LSB)
   	{0x6A2F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.MSB)
   	{0x6A30,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(15)
   	{0x6A31,0x16, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.LSB)
   	{0x6A32,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.MSB)
   	{0x6A33,0xA6, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.LSB)
   	{0x6A34,0x18, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.MSB)
   	{0x6A35,0x18, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.LSB)
   	{0x6A36,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.MSB)
   	{0x6A37,0x5E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.LSB)
   	{0x6A38,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.MSB)
   	{0x6A39,0x1A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.LSB)
   	{0x6A3A,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.MSB)
   	{0x6A3B,0x3F, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.LSB)
   	{0x6A3C,0x0C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.MSB)
   	{0x6A3D,0x1C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.LSB)
   	{0x6A3E,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.MSB)
   	{0x6A3F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.LSB)
   	{0x6A40,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.MSB)
   	{0x6A41,0x1E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.LSB)
   	{0x6A42,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.MSB)
   	{0x6A43,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.LSB)
   	{0x6A44,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.MSB)
   	{0x6A45,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.LSB)
   	{0x6A46,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.MSB)
   	{0x6A47,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.LSB)
   	{0x6A48,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.MSB)
   	{0x6A49,0xAE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.LSB)
   	{0x6A4A,0x52, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.MSB)
   	{0x6A4B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.LSB)
   	{0x6A4C,0x21, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.MSB)
   	{0x6A4D,0x88, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.LSB)
   	{0x6A4E,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.MSB)
   	{0x6A4F,0x24, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.LSB)
   	{0x6A50,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.MSB)
   	{0x6A51,0x8A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.LSB)
   	{0x6A52,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.MSB)
   	{0x6A53,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.LSB)
   	{0x6A54,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.MSB)
   	{0x6A55,0x8C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.LSB)
   	{0x6A56,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.MSB)
   	{0x6A57,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.LSB)
   	{0x6A58,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.MSB)
   	{0x6A59,0x5E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.LSB)
   	{0x6A5A,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.MSB)
   	{0x6A5B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.LSB)
   	{0x6A5C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.MSB)
   	{0x6A5D,0x80, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.LSB)
   	{0x6A5E,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.MSB)
   	{0x6A5F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.LSB)
   	{0x6A60,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.MSB)
   	{0x6A61,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.LSB)
   	{0x6A62,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.MSB)
   	{0x6A63,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.LSB)
   	{0x6A64,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.MSB)
   	{0x6A65,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.LSB)
   	{0x6A66,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.MSB)
   	{0x6A67,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.LSB)
   	{0x6A68,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.MSB)
   	{0x6A69,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.LSB)
   	{0x6A6A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.MSB)
   	{0x6A6B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.LSB)
   	{0x6A6C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.MSB)
   	{0x6A6D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.LSB)
   	{0x6A6E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.MSB)
   	{0x6A6F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.LSB)
   	{0x6A70,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.MSB)
   	{0x6A00,0x01, BYTE_LEN, 0 },  //V-Latch TRG  0:No use /  1:V-Latch ON	
};

struct isx006_i2c_reg_conf isx006_bench_snow_settings[] = {
	// ISX006 ES2 KMO V03_2
	//,0xScene4,0xBeach&Snow,0x,0x,0x
    {0x6A01,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.LSB),0x
    {0x6A02,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.MSB),0x
    {0x6A03,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(0),0x
    {0x6A04,0x62, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.LSB),0x
    {0x6A05,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.MSB),0x
    {0x6A06,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(1),0x
    {0x6A07,0x5D, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.LSB),0x
    {0x6A08,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.MSB),0x
    {0x6A09,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(2),0x
    {0x6A0A,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.LSB),0x
    {0x6A0B,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.MSB),0x
    {0x6A0C,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(3),0x
    {0x6A0D,0xE1, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.LSB),0x
    {0x6A0E,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.MSB),0x
    {0x6A0F,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(4)
    {0x6A10,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.LSB)
    {0x6A11,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.MSB)
    {0x6A12,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(5)
    {0x6A13,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.LSB)
    {0x6A14,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.MSB)
    {0x6A15,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(6)
    {0x6A16,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.LSB)
    {0x6A17,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.MSB)
    {0x6A18,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(7)
    {0x6A19,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.LSB)
    {0x6A1A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.MSB)
    {0x6A1B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(8)
    {0x6A1C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.LSB)
    {0x6A1D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.MSB)
    {0x6A1E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(9)
    {0x6A1F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.LSB)
    {0x6A20,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.MSB)
    {0x6A21,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(10)
    {0x6A22,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.LSB)
    {0x6A23,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.MSB)
    {0x6A24,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(11)
    {0x6A25,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.LSB)
    {0x6A26,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.MSB)
    {0x6A27,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(12)
    {0x6A28,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.LSB)
    {0x6A29,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.MSB)
    {0x6A2A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(13)
    {0x6A2B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.LSB)
    {0x6A2C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.MSB)
    {0x6A2D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(14)
    {0x6A2E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.LSB)
    {0x6A2F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.MSB)
    {0x6A30,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(15)
    {0x6A31,0x16, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.LSB)
    {0x6A32,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.MSB)
    {0x6A33,0xDE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.LSB)
    {0x6A34,0x28, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.MSB)
    {0x6A35,0x18, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.LSB)
    {0x6A36,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.MSB)
    {0x6A37,0x97, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.LSB)
    {0x6A38,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.MSB)
    {0x6A39,0x1A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.LSB)
    {0x6A3A,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.MSB)
    {0x6A3B,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.LSB)
    {0x6A3C,0x05, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.MSB)
    {0x6A3D,0x1C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.LSB)
    {0x6A3E,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.MSB)
    {0x6A3F,0xFD, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.LSB)
    {0x6A40,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.MSB)
    {0x6A41,0x1E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.LSB)
    {0x6A42,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.MSB)
    {0x6A43,0x68, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.LSB)
    {0x6A44,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.MSB)
    {0x6A45,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.LSB)
    {0x6A46,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.MSB)
    {0x6A47,0xCB, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.LSB)
    {0x6A48,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.MSB)
    {0x6A49,0xAE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.LSB)
    {0x6A4A,0x52, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.MSB)
    {0x6A4B,0x9D, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.LSB)
    {0x6A4C,0x2E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.MSB)
    {0x6A4D,0x88, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.LSB)
    {0x6A4E,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.MSB)
    {0x6A4F,0x24, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.LSB)
    {0x6A50,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.MSB)
    {0x6A51,0x8A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.LSB)
    {0x6A52,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.MSB)
    {0x6A53,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.LSB)
    {0x6A54,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.MSB)
    {0x6A55,0x8C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.LSB)
    {0x6A56,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.MSB)
    {0x6A57,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.LSB)
    {0x6A58,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.MSB)
    {0x6A59,0x5E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.LSB)
    {0x6A5A,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.MSB)
    {0x6A5B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.LSB)
    {0x6A5C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.MSB)
    {0x6A5D,0x80, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.LSB)
    {0x6A5E,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.MSB)
    {0x6A5F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.LSB)
    {0x6A60,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.MSB)
    {0x6A61,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.LSB)
    {0x6A62,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.MSB)
    {0x6A63,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.LSB)
    {0x6A64,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.MSB)
    {0x6A65,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.LSB)
    {0x6A66,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.MSB)
    {0x6A67,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.LSB)
    {0x6A68,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.MSB)
    {0x6A69,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.LSB)
    {0x6A6A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.MSB)
    {0x6A6B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.LSB)
    {0x6A6C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.MSB)
    {0x6A6D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.LSB)
    {0x6A6E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.MSB)
    {0x6A6F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.LSB)
    {0x6A70,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.MSB)
    {0x6A00,0x01, BYTE_LEN, 0 },  //V-Latch TRG  0:No use /  1:V-Latch ON	
};

struct isx006_i2c_reg_conf isx006_auto_scene_settings[] = {
	// ISX006 ES2 KMO V03_2
	//,Scene1,Auto,,,
	{0x6A01,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.LSB),
	{0x6A02,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.MSB),
	{0x6A03,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(0),
	{0x6A04,0x62, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.LSB),
	{0x6A05,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.MSB),
	{0x6A06,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(1),
	{0x6A07,0x5D, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.LSB),
	{0x6A08,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.MSB),
	{0x6A09,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(2),
	{0x6A0A,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.LSB),
	{0x6A0B,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.MSB),
	{0x6A0C,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(3),
	{0x6A0D,0xE1, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.LSB),
	{0x6A0E,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.MSB),
	{0x6A0F,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(4)
	{0x6A10,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.LSB)
	{0x6A11,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.MSB)
	{0x6A12,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(5)
	{0x6A13,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.LSB)
	{0x6A14,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.MSB)
	{0x6A15,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(6)
	{0x6A16,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.LSB)
	{0x6A17,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.MSB)
	{0x6A18,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(7)
	{0x6A19,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.LSB)
	{0x6A1A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.MSB)
	{0x6A1B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(8)
	{0x6A1C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.LSB)
	{0x6A1D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.MSB)
	{0x6A1E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(9)
	{0x6A1F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.LSB)
	{0x6A20,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.MSB)
	{0x6A21,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(10)
	{0x6A22,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.LSB)
	{0x6A23,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.MSB)
	{0x6A24,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(11)
	{0x6A25,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.LSB)
	{0x6A26,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.MSB)
	{0x6A27,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(12)
	{0x6A28,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.LSB)
	{0x6A29,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.MSB)
	{0x6A2A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(13)
	{0x6A2B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.LSB)
	{0x6A2C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.MSB)
	{0x6A2D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(14)
	{0x6A2E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.LSB)
	{0x6A2F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.MSB)
	{0x6A30,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(15)
	{0x6A31,0x16, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.LSB)
	{0x6A32,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.MSB)
	{0x6A33,0xDE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.LSB)
	{0x6A34,0x28, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.MSB)
	{0x6A35,0x18, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.LSB)
	{0x6A36,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.MSB)
	{0x6A37,0x97, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.LSB)
	{0x6A38,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.MSB)
	{0x6A39,0x1A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.LSB)
	{0x6A3A,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.MSB)
	{0x6A3B,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.LSB)
	{0x6A3C,0x05, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.MSB)
	{0x6A3D,0x1C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.LSB)
	{0x6A3E,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.MSB)
	{0x6A3F,0xFD, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.LSB)
	{0x6A40,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.MSB)
	{0x6A41,0x1E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.LSB)
	{0x6A42,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.MSB)
	{0x6A43,0x68, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.LSB)
	{0x6A44,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.MSB)
	{0x6A45,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.LSB)
	{0x6A46,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.MSB)
	{0x6A47,0xCB, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.LSB)
	{0x6A48,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.MSB)
	{0x6A49,0xAE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.LSB)
	{0x6A4A,0x52, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.MSB)
	{0x6A4B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.LSB)
	{0x6A4C,0x21, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.MSB)
	{0x6A4D,0x88, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.LSB)
	{0x6A4E,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.MSB)
	{0x6A4F,0x24, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.LSB)
	{0x6A50,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.MSB)
	{0x6A51,0x8A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.LSB)
	{0x6A52,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.MSB)
	{0x6A53,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.LSB)
	{0x6A54,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.MSB)
	{0x6A55,0x8C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.LSB)
	{0x6A56,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.MSB)
	{0x6A57,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.LSB)
	{0x6A58,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.MSB)
	{0x6A59,0x5E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.LSB)
	{0x6A5A,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.MSB)
	{0x6A5B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.LSB)
	{0x6A5C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.MSB)
	{0x6A5D,0x80, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.LSB)
	{0x6A5E,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.MSB)
	{0x6A5F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.LSB)
	{0x6A60,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.MSB)
	{0x6A61,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.LSB)
	{0x6A62,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.MSB)
	{0x6A63,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.LSB)
	{0x6A64,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.MSB)
	{0x6A65,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.LSB)
	{0x6A66,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.MSB)
	{0x6A67,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.LSB)
	{0x6A68,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.MSB)
	{0x6A69,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.LSB)
	{0x6A6A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.MSB)
	{0x6A6B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.LSB)
	{0x6A6C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.MSB)
	{0x6A6D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.LSB)
	{0x6A6E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.MSB)
	{0x6A6F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.LSB)
	{0x6A70,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.MSB)
	{0x6A00,0x01, BYTE_LEN, 0 },  //V-Latch TRG	0:No use /	1:V-Latch ON
};

/*TwilightLandScape*/
struct isx006_i2c_reg_conf isx006_night_settings[] = {
	// ISX006 ES2 KMO V03_2
	//,Scene6,TwilightLandScape,,,
	{0x6A01,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.LSB),
	{0x6A02,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(0.MSB),
	{0x6A03,0x05, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(0),
	{0x6A04,0x62, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.LSB),
	{0x6A05,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(1.MSB),
	{0x6A06,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(1),
	{0x6A07,0x5D, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.LSB),
	{0x6A08,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(2.MSB),
	{0x6A09,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(2),
	{0x6A0A,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.LSB),
	{0x6A0B,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(3.MSB),
	{0x6A0C,0x01, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(3),
	{0x6A0D,0xE1, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.LSB),
	{0x6A0E,0x02, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(4.MSB),
	{0x6A0F,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(4)
	{0x6A10,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.LSB)
	{0x6A11,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(5.MSB)
	{0x6A12,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(5)
	{0x6A13,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.LSB)
	{0x6A14,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(6.MSB)
	{0x6A15,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(6)
	{0x6A16,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.LSB)
	{0x6A17,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(7.MSB)
	{0x6A18,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(7)
	{0x6A19,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.LSB)
	{0x6A1A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(8.MSB)
	{0x6A1B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(8)
	{0x6A1C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.LSB)
	{0x6A1D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(9.MSB)
	{0x6A1E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(9)
	{0x6A1F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.LSB)
	{0x6A20,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(10.MSB)
	{0x6A21,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(10)
	{0x6A22,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.LSB)
	{0x6A23,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(11.MSB)
	{0x6A24,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(11)
	{0x6A25,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.LSB)
	{0x6A26,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(12.MSB)
	{0x6A27,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(12)
	{0x6A28,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.LSB)
	{0x6A29,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(13.MSB)
	{0x6A2A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(13)
	{0x6A2B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.LSB)
	{0x6A2C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(14.MSB)
	{0x6A2D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(14)
	{0x6A2E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.LSB)
	{0x6A2F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Address(15.MSB)
	{0x6A30,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Single Byte)Data(15)
	{0x6A31,0x16, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.LSB)
	{0x6A32,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(0.MSB)
	{0x6A33,0xDE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.LSB)
	{0x6A34,0x28, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(0.MSB)
	{0x6A35,0x18, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.LSB)
	{0x6A36,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(1.MSB)
	{0x6A37,0x97, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.LSB)
	{0x6A38,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(1.MSB)
	{0x6A39,0x1A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.LSB)
	{0x6A3A,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(2.MSB)
	{0x6A3B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.LSB)
	{0x6A3C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(2.MSB)
	{0x6A3D,0x1C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.LSB)
	{0x6A3E,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(3.MSB)
	{0x6A3F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.LSB)
	{0x6A40,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(3.MSB)
	{0x6A41,0x1E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.LSB)
	{0x6A42,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(4.MSB)
	{0x6A43,0xA8, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.LSB)
	{0x6A44,0x0F, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(4.MSB)
	{0x6A45,0x20, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.LSB)
	{0x6A46,0x40, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(5.MSB)
	{0x6A47,0xFD, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.LSB)
	{0x6A48,0x03, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(5.MSB)
	{0x6A49,0xAE, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.LSB)
	{0x6A4A,0x52, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(6.MSB)
	{0x6A4B,0x5C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.LSB)
	{0x6A4C,0x17, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(6.MSB)
	{0x6A4D,0x88, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.LSB)
	{0x6A4E,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(7.MSB)
	{0x6A4F,0x24, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.LSB)
	{0x6A50,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(7.MSB)
	{0x6A51,0x8A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.LSB)
	{0x6A52,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(8.MSB)
	{0x6A53,0x0B, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.LSB)
	{0x6A54,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(8.MSB)
	{0x6A55,0x8C, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.LSB)
	{0x6A56,0x58, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(9.MSB)
	{0x6A57,0x0A, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.LSB)
	{0x6A58,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(9.MSB)
	{0x6A59,0x5E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.LSB)
	{0x6A5A,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(10.MSB)
	{0x6A5B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.LSB)
	{0x6A5C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(10.MSB)
	{0x6A5D,0x80, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.LSB)
	{0x6A5E,0x4E, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(11.MSB)
	{0x6A5F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.LSB)
	{0x6A60,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(11.MSB)
	{0x6A61,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.LSB)
	{0x6A62,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(12.MSB)
	{0x6A63,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.LSB)
	{0x6A64,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(12.MSB)
	{0x6A65,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.LSB)
	{0x6A66,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(13.MSB)
	{0x6A67,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.LSB)
	{0x6A68,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(13.MSB)
	{0x6A69,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.LSB)
	{0x6A6A,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(14.MSB)
	{0x6A6B,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.LSB)
	{0x6A6C,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(14.MSB)
	{0x6A6D,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.LSB)
	{0x6A6E,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Address(15.MSB)
	{0x6A6F,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.LSB)
	{0x6A70,0x00, BYTE_LEN, 0 },  //V-Latch Parameter(Word)Data(15.MSB)
	{0x6A00,0x01, BYTE_LEN, 0 },  //V-Latch TRG  0:No use /  1:V-Latch ON
};
/* FIH-SW3-MM-SL-PatchForCameraFeature-01+} */

//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
/*LandScape*/
struct isx006_i2c_reg_conf isx006_landscape_settings[] = {
    // ISX006 ES2 KMO V03_2
    //,Scene2,LandScape,,,
    {0x6A01, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(0.LSB)
    {0x6A02, 0x01, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(0.MSB)
    {0x6A03, 0x01, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(0)
    {0x6A04, 0x62, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(1.LSB)
    {0x6A05, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(1.MSB)
    {0x6A06, 0x20, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(1)
    {0x6A07, 0x5D, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(2.LSB)
    {0x6A08, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(2.MSB)
    {0x6A09, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(2)
    {0x6A0A, 0x0B, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(3.LSB)
    {0x6A0B, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(3.MSB)
    {0x6A0C, 0x02, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(3)
    {0x6A0D, 0xE1, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(4.LSB)
    {0x6A0E, 0x02, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(4.MSB)
    {0x6A0F, 0x0A, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(4)
    {0x6A10, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(5.LSB)
    {0x6A11, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(5.MSB)
    {0x6A12, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(5)
    {0x6A13, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(6.LSB)
    {0x6A14, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(6.MSB)
    {0x6A15, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(6)
    {0x6A16, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(7.LSB)
    {0x6A17, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(7.MSB)
    {0x6A18, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(7)
    {0x6A19, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(8.LSB)
    {0x6A1A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(8.MSB)
    {0x6A1B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(8)
    {0x6A1C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(9.LSB)
    {0x6A1D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(9.MSB)
    {0x6A1E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(9)
    {0x6A1F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(10.LSB)
    {0x6A20, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(10.MSB)
    {0x6A21, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(10)
    {0x6A22, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(11.LSB)
    {0x6A23, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(11.MSB)
    {0x6A24, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(11)
    {0x6A25, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(12.LSB)
    {0x6A26, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(12.MSB)
    {0x6A27, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(12)
    {0x6A28, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(13.LSB)
    {0x6A29, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(13.MSB)
    {0x6A2A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(13)
    {0x6A2B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(14.LSB)
    {0x6A2C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(14.MSB)
    {0x6A2D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(14)
    {0x6A2E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(15.LSB)
    {0x6A2F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(15.MSB)
    {0x6A30, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(15)
    {0x6A31, 0x16, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(0.LSB)
    {0x6A32, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(0.MSB)
    {0x6A33, 0xDE, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(0.LSB)
    {0x6A34, 0x28, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(0.MSB)
    {0x6A35, 0x18, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(1.LSB)
    {0x6A36, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(1.MSB)
    {0x6A37, 0x97, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(1.LSB)
    {0x6A38, 0x03, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(1.MSB)
    {0x6A39, 0x1A, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(2.LSB)
    {0x6A3A, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(2.MSB)
    {0x6A3B, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(2.LSB)
    {0x6A3C, 0x05, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(2.MSB)
    {0x6A3D, 0x1C, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(3.LSB)
    {0x6A3E, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(3.MSB)
    {0x6A3F, 0xFD, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(3.LSB)
    {0x6A40, 0x03, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(3.MSB)
    {0x6A41, 0x1E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(4.LSB)
    {0x6A42, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(4.MSB)
    {0x6A43, 0x68, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(4.LSB)
    {0x6A44, 0x02, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(4.MSB)
    {0x6A45, 0x20, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(5.LSB)
    {0x6A46, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(5.MSB)
    {0x6A47, 0xCB, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(5.LSB)
    {0x6A48, 0x02, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(5.MSB)
    {0x6A49, 0xAE, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(6.LSB)
    {0x6A4A, 0x52, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(6.MSB)
    {0x6A4B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(6.LSB)
    {0x6A4C, 0x21, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(6.MSB)
    {0x6A4D, 0x88, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(7.LSB)
    {0x6A4E, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(7.MSB)
    {0x6A4F, 0x24, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(7.LSB)
    {0x6A50, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(7.MSB)
    {0x6A51, 0x8A, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(8.LSB)
    {0x6A52, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(8.MSB)
    {0x6A53, 0x0B, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(8.LSB)
    {0x6A54, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(8.MSB)
    {0x6A55, 0x8C, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(9.LSB)
    {0x6A56, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(9.MSB)
    {0x6A57, 0x0A, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(9.LSB)
    {0x6A58, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(9.MSB)
    {0x6A59, 0x5E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(10.LSB)
    {0x6A5A, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(10.MSB)
    {0x6A5B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(10.LSB)
    {0x6A5C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(10.MSB)
    {0x6A5D, 0x80, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(11.LSB)
    {0x6A5E, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(11.MSB)
    {0x6A5F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(11.LSB)
    {0x6A60, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(11.MSB)
    {0x6A61, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(12.LSB)
    {0x6A62, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(12.MSB)
    {0x6A63, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(12.LSB)
    {0x6A64, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(12.MSB)
    {0x6A65, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(13.LSB)
    {0x6A66, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(13.MSB)
    {0x6A67, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(13.LSB)
    {0x6A68, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(13.MSB)
    {0x6A69, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(14.LSB)
    {0x6A6A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(14.MSB)
    {0x6A6B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(14.LSB)
    {0x6A6C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(14.MSB)
    {0x6A6D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(15.LSB)
    {0x6A6E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(15.MSB)
    {0x6A6F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(15.LSB)
    {0x6A70, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(15.MSB)
    {0x6A00, 0x01, BYTE_LEN, 0 },//V-Latch TRG  0:No use /  1:V-Latch ON
};


/*Document*/
struct isx006_i2c_reg_conf isx006_document_settings[] = {
    // ISX006 ES2 KMO V03_2
    //,Scene7,Document,,,
    {0x6A01, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(0.LSB)
    {0x6A02, 0x01, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(0.MSB)
    {0x6A03, 0x06, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(0)
    {0x6A04, 0x62, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(1.LSB)
    {0x6A05, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(1.MSB)
    {0x6A06, 0x30, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(1)
    {0x6A07, 0x5D, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(2.LSB)
    {0x6A08, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(2.MSB)
    {0x6A09, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(2)
    {0x6A0A, 0x0B, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(3.LSB)
    {0x6A0B, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(3.MSB)
    {0x6A0C, 0x01, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(3)
    {0x6A0D, 0xE1, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(4.LSB)
    {0x6A0E, 0x02, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(4.MSB)
    {0x6A0F, 0x0A, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(4)
    {0x6A10, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(5.LSB)
    {0x6A11, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(5.MSB)
    {0x6A12, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(5)
    {0x6A13, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(6.LSB)
    {0x6A14, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(6.MSB)
    {0x6A15, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(6)
    {0x6A16, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(7.LSB)
    {0x6A17, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(7.MSB)
    {0x6A18, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(7)
    {0x6A19, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(8.LSB)
    {0x6A1A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(8.MSB)
    {0x6A1B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(8)
    {0x6A1C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(9.LSB)
    {0x6A1D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(9.MSB)
    {0x6A1E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(9)
    {0x6A1F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(10.LSB)
    {0x6A20, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(10.MSB)
    {0x6A21, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(10)
    {0x6A22, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(11.LSB)
    {0x6A23, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(11.MSB)
    {0x6A24, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(11)
    {0x6A25, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(12.LSB)
    {0x6A26, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(12.MSB)
    {0x6A27, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(12)
    {0x6A28, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(13.LSB)
    {0x6A29, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(13.MSB)
    {0x6A2A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(13)
    {0x6A2B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(14.LSB)
    {0x6A2C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(14.MSB)
    {0x6A2D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(14)
    {0x6A2E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(15.LSB)
    {0x6A2F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Address(15.MSB)
    {0x6A30, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Single Byte)Data(15)
    {0x6A31, 0x16, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(0.LSB)
    {0x6A32, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(0.MSB)
    {0x6A33, 0x97, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(0.LSB)
    {0x6A34, 0x24, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(0.MSB)
    {0x6A35, 0x18, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(1.LSB)
    {0x6A36, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(1.MSB)
    {0x6A37, 0x97, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(1.LSB)
    {0x6A38, 0x03, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(1.MSB)
    {0x6A39, 0x1A, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(2.LSB)
    {0x6A3A, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(2.MSB)
    {0x6A3B, 0x2D, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(2.LSB)
    {0x6A3C, 0x04, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(2.MSB)
    {0x6A3D, 0x1C, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(3.LSB)
    {0x6A3E, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(3.MSB)
    {0x6A3F, 0xFD, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(3.LSB)
    {0x6A40, 0x03, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(3.MSB)
    {0x6A41, 0x1E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(4.LSB)
    {0x6A42, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(4.MSB)
    {0x6A43, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(4.LSB)
    {0x6A44, 0x04, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(4.MSB)
    {0x6A45, 0x20, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(5.LSB)
    {0x6A46, 0x40, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(5.MSB)
    {0x6A47, 0xC8, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(5.LSB)
    {0x6A48, 0x06, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(5.MSB)
    {0x6A49, 0xAE, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(6.LSB)
    {0x6A4A, 0x52, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(6.MSB)
    {0x6A4B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(6.LSB)
    {0x6A4C, 0x21, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(6.MSB)
    {0x6A4D, 0x88, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(7.LSB)
    {0x6A4E, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(7.MSB)
    {0x6A4F, 0x25, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(7.LSB)
    {0x6A50, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(7.MSB)
    {0x6A51, 0x8A, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(8.LSB)
    {0x6A52, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(8.MSB)
    {0x6A53, 0x10, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(8.LSB)
    {0x6A54, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(8.MSB)
    {0x6A55, 0x8C, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(9.LSB)
    {0x6A56, 0x58, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(9.MSB)
    {0x6A57, 0x10, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(9.LSB)
    {0x6A58, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(9.MSB)
    {0x6A59, 0x5E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(10.LSB)
    {0x6A5A, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(10.MSB)
    {0x6A5B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(10.LSB)
    {0x6A5C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(10.MSB)
    {0x6A5D, 0x80, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(11.LSB)
    {0x6A5E, 0x4E, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(11.MSB)
    {0x6A5F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(11.LSB)
    {0x6A60, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(11.MSB)
    {0x6A61, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(12.LSB)
    {0x6A62, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(12.MSB)
    {0x6A63, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(12.LSB)
    {0x6A64, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(12.MSB)
    {0x6A65, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(13.LSB)
    {0x6A66, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(13.MSB)
    {0x6A67, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(13.LSB)
    {0x6A68, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(13.MSB)
    {0x6A69, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(14.LSB)
    {0x6A6A, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(14.MSB)
    {0x6A6B, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(14.LSB)
    {0x6A6C, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(14.MSB)
    {0x6A6D, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(15.LSB)
    {0x6A6E, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Address(15.MSB)
    {0x6A6F, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(15.LSB)
    {0x6A70, 0x00, BYTE_LEN, 0 },//V-Latch Parameter(Word)Data(15.MSB)
    {0x6A00, 0x01, BYTE_LEN, 0 },//V-Latch TRG  0:No use /  1:V-Latch ON
};
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}

/* FIH-SW3-MM-UW-write OTP setting-00+*/
/*SHD_MAX*/
struct isx006_i2c_reg_conf isx006_SHD_MAX_settings[] = {
	{0x0068,0x50, BYTE_LEN, 0 },

	{0x9000,0x8282, WORD_LEN, 0 },//CXC_valid_code
	{0x9002,0xfe, BYTE_LEN, 0 },
	{0x9003,0x11, BYTE_LEN, 0 },
	{0x9004,0xF8, BYTE_LEN, 0 },
	{0x9005,0x47, BYTE_LEN, 0 },
	{0x9006,0x00, BYTE_LEN, 0 },
	{0x9007,0x20, BYTE_LEN, 0 },
	{0x9008,0x81, BYTE_LEN, 0 },
	{0x9009,0x80, BYTE_LEN, 0 },
	{0x900A,0x04, BYTE_LEN, 0 },
	{0x900B,0x00, BYTE_LEN, 0 },
	{0x900C,0x10, BYTE_LEN, 0 },
	{0x900D,0x04, BYTE_LEN, 0 },
	{0x900E,0x48, BYTE_LEN, 0 },
	{0x900F,0x10, BYTE_LEN, 0 },
	{0x9010,0x40, BYTE_LEN, 0 },
	{0x9011,0x41, BYTE_LEN, 0 },
	{0x9012,0x80, BYTE_LEN, 0 },
	{0x9013,0x05, BYTE_LEN, 0 },
	{0x9014,0x01, BYTE_LEN, 0 },
	{0x9015,0x16, BYTE_LEN, 0 },
	{0x9016,0xF8, BYTE_LEN, 0 },
	{0x9017,0x47, BYTE_LEN, 0 },
	{0x9018,0xE0, BYTE_LEN, 0 },
	{0x9019,0x1f, BYTE_LEN, 0 },
	{0x901A,0x01, BYTE_LEN, 0 },
	{0x901B,0x80, BYTE_LEN, 0 },
	{0x901C,0x04, BYTE_LEN, 0 },
	{0x901D,0x02, BYTE_LEN, 0 },
	{0x901E,0x12, BYTE_LEN, 0 },
	{0x901F,0x00, BYTE_LEN, 0 },
	{0x9020,0x40, BYTE_LEN, 0 },
	{0x9021,0x10, BYTE_LEN, 0 },
	{0x9022,0x20, BYTE_LEN, 0 },
	{0x9023,0x41, BYTE_LEN, 0 },
	{0x9024,0x00, BYTE_LEN, 0 },
	{0x9025,0x05, BYTE_LEN, 0 },
	{0x9026,0x01, BYTE_LEN, 0 },
	{0x9027,0x16, BYTE_LEN, 0 },
	{0x9028,0x04, BYTE_LEN, 0 },
	{0x9029,0x58, BYTE_LEN, 0 },
	{0x902A,0x20, BYTE_LEN, 0 },
	{0x902B,0x00, BYTE_LEN, 0 },
	{0x902C,0x81, BYTE_LEN, 0 },
	{0x902D,0x00, BYTE_LEN, 0 },
	{0x902E,0x04, BYTE_LEN, 0 },
	{0x902F,0x01, BYTE_LEN, 0 },
	{0x9030,0x12, BYTE_LEN, 0 },
	{0x9031,0x08, BYTE_LEN, 0 },
	{0x9032,0x38, BYTE_LEN, 0 },
	{0x9033,0x10, BYTE_LEN, 0 },
	{0x9034,0x00, BYTE_LEN, 0 },
	{0x9035,0x81, BYTE_LEN, 0 },
	{0x9036,0x80, BYTE_LEN, 0 },
	{0x9037,0x04, BYTE_LEN, 0 },
	{0x9038,0x01, BYTE_LEN, 0 },
	{0x9039,0x12, BYTE_LEN, 0 },
	{0x903A,0x04, BYTE_LEN, 0 },
	{0x903B,0x50, BYTE_LEN, 0 },
	{0x903C,0x10, BYTE_LEN, 0 },
	{0x903D,0x40, BYTE_LEN, 0 },
	{0x903E,0x81, BYTE_LEN, 0 },
	{0x903F,0x80, BYTE_LEN, 0 },
	{0x9040,0x03, BYTE_LEN, 0 },
	{0x9041,0x02, BYTE_LEN, 0 },
	{0x9042,0x0e, BYTE_LEN, 0 },
	{0x9043,0x00, BYTE_LEN, 0 },
	{0x9044,0x28, BYTE_LEN, 0 },
	{0x9045,0x20, BYTE_LEN, 0 },
	{0x9046,0x80, BYTE_LEN, 0 },
	{0x9047,0x40, BYTE_LEN, 0 },
	{0x9048,0x00, BYTE_LEN, 0 },
	{0x9049,0x02, BYTE_LEN, 0 },
	{0x904A,0x02, BYTE_LEN, 0 },
	{0x904B,0x08, BYTE_LEN, 0 },
	{0x904C,0x04, BYTE_LEN, 0 },
	{0x904D,0x30, BYTE_LEN, 0 },
	{0x904E,0x20, BYTE_LEN, 0 },
	{0x904F,0x20, BYTE_LEN, 0 },
	{0x9050,0x81, BYTE_LEN, 0 },
	{0x9051,0x80, BYTE_LEN, 0 },
	{0x9052,0x04, BYTE_LEN, 0 },
	{0x9053,0x03, BYTE_LEN, 0 },
	{0x9054,0x0a, BYTE_LEN, 0 },
	{0x9055,0x0c, BYTE_LEN, 0 },
	{0x9056,0x28, BYTE_LEN, 0 },
	{0x9057,0x30, BYTE_LEN, 0 },
	{0x9058,0x60, BYTE_LEN, 0 },
	{0x9059,0x80, BYTE_LEN, 0 },
	{0x905A,0x00, BYTE_LEN, 0 },
	{0x905B,0x01, BYTE_LEN, 0 },
	{0x905C,0x03, BYTE_LEN, 0 },
	{0x905D,0x02, BYTE_LEN, 0 },
	{0x905E,0x08, BYTE_LEN, 0 },
	{0x905F,0x08, BYTE_LEN, 0 },
	{0x9060,0x00, BYTE_LEN, 0 },
	{0x9061,0xA0, BYTE_LEN, 0 },
	{0x9062,0x80, BYTE_LEN, 0 },
	{0x9063,0x80, BYTE_LEN, 0 },
	{0x9064,0x02, BYTE_LEN, 0 },
	{0x9065,0x02, BYTE_LEN, 0 },
	{0x9066,0x0a, BYTE_LEN, 0 },
	{0x9067,0x0c, BYTE_LEN, 0 },
	{0x9068,0x18, BYTE_LEN, 0 },
	{0x9069,0x30, BYTE_LEN, 0 },
	{0x906A,0x60, BYTE_LEN, 0 },
	{0x906B,0x40, BYTE_LEN, 0 },
	{0x906C,0x81, BYTE_LEN, 0 },
	{0x906D,0x00, BYTE_LEN, 0 },
	{0x906E,0x02, BYTE_LEN, 0 },
	{0x906F,0x02, BYTE_LEN, 0 },
	{0x9070,0x00, BYTE_LEN, 0 },
	{0x9071,0xF8, BYTE_LEN, 0 },
	{0x9072,0x2f, BYTE_LEN, 0 },
	{0x9073,0x40, BYTE_LEN, 0 },
	{0x9074,0xC0, BYTE_LEN, 0 },
	{0x9075,0x00, BYTE_LEN, 0 },
	{0x9076,0x01, BYTE_LEN, 0 },
	{0x9077,0x03, BYTE_LEN, 0 },
	{0x9078,0x0c, BYTE_LEN, 0 },
	{0x9079,0x0c, BYTE_LEN, 0 },
	{0x907A,0x30, BYTE_LEN, 0 },
	{0x907B,0x10, BYTE_LEN, 0 },
	{0x907C,0x60, BYTE_LEN, 0 },
	{0x907D,0x40, BYTE_LEN, 0 },
	{0x907E,0x80, BYTE_LEN, 0 },
	{0x907F,0x01, BYTE_LEN, 0 },
	{0x9080,0x01, BYTE_LEN, 0 },
	{0x9081,0x04, BYTE_LEN, 0 },
	{0x9082,0x08, BYTE_LEN, 0 },
	{0x9083,0xF8, BYTE_LEN, 0 },
	{0x9084,0x0f, BYTE_LEN, 0 },
	{0x9085,0x00, BYTE_LEN, 0 },
	{0x9086,0x40, BYTE_LEN, 0 },
	{0x9087,0x00, BYTE_LEN, 0 },
	{0x9088,0x00, BYTE_LEN, 0 },
	{0x9089,0x02, BYTE_LEN, 0 },
	{0x908A,0x04, BYTE_LEN, 0 },
	{0x908B,0x0c, BYTE_LEN, 0 },
	{0x908C,0x20, BYTE_LEN, 0 },
	{0x908D,0x30, BYTE_LEN, 0 },
	{0x908E,0x80, BYTE_LEN, 0 },
	{0x908F,0xC0, BYTE_LEN, 0 },
	{0x9090,0x80, BYTE_LEN, 0 },
	{0x9091,0x01, BYTE_LEN, 0 },
	{0x9092,0x03, BYTE_LEN, 0 },
	{0x9093,0x06, BYTE_LEN, 0 },
	{0x9094,0x0c, BYTE_LEN, 0 },
	{0x9095,0x00, BYTE_LEN, 0 },
	{0x9096,0x20, BYTE_LEN, 0 },
	{0x9097,0x20, BYTE_LEN, 0 },
	{0x9098,0x00, BYTE_LEN, 0 },
	{0x9099,0x81, BYTE_LEN, 0 },
	{0x909A,0xFf, BYTE_LEN, 0 },
	{0x909B,0x03, BYTE_LEN, 0 },
	{0x909C,0x00, BYTE_LEN, 0 },
	{0x909D,0x10, BYTE_LEN, 0 },
	{0x909E,0x00, BYTE_LEN, 0 },
	{0x909F,0x10, BYTE_LEN, 0 },
	{0x90A0,0x80, BYTE_LEN, 0 },
	{0x90A1,0x40, BYTE_LEN, 0 },
	{0x90A2,0x00, BYTE_LEN, 0 },
	{0x90A3,0x02, BYTE_LEN, 0 },
	{0x90A4,0x03, BYTE_LEN, 0 },
	{0x90A5,0x08, BYTE_LEN, 0 },
	{0x90A6,0x0c, BYTE_LEN, 0 },
	{0x90A7,0x20, BYTE_LEN, 0 },
	{0x90A8,0x20, BYTE_LEN, 0 },
	{0x90A9,0x60, BYTE_LEN, 0 },
	{0x90AA,0xC0, BYTE_LEN, 0 },
	{0x90AB,0x80, BYTE_LEN, 0 },
	{0x90AC,0x01, BYTE_LEN, 0 },
	{0x90AD,0x03, BYTE_LEN, 0 },
	{0x90AE,0x02, BYTE_LEN, 0 },
	{0x90AF,0x0c, BYTE_LEN, 0 },
	{0x90B0,0x10, BYTE_LEN, 0 },
	{0x90B1,0x30, BYTE_LEN, 0 },
	{0x90B2,0x60, BYTE_LEN, 0 },
	{0x90B3,0xC0, BYTE_LEN, 0 },
	{0x90B4,0x80, BYTE_LEN, 0 },
	{0x90B5,0x02, BYTE_LEN, 0 },
	{0x90B6,0x03, BYTE_LEN, 0 },
	{0x90B7,0x0a, BYTE_LEN, 0 },
	{0x90B8,0x08, BYTE_LEN, 0 },
	{0x90B9,0x20, BYTE_LEN, 0 },
	{0x90BA,0x20, BYTE_LEN, 0 },
	{0x90BB,0x80, BYTE_LEN, 0 },
	{0x90BC,0x00, BYTE_LEN, 0 },
	{0x90BD,0x01, BYTE_LEN, 0 },
	{0x90BE,0x02, BYTE_LEN, 0 },
	{0x90BF,0x04, BYTE_LEN, 0 },
	{0x90C0,0x06, BYTE_LEN, 0 },
	{0x90C1,0x10, BYTE_LEN, 0 },
	{0x90C2,0x18, BYTE_LEN, 0 },
	{0x90C3,0x30, BYTE_LEN, 0 },
	{0x90C4,0x60, BYTE_LEN, 0 },
	{0x90C5,0x80, BYTE_LEN, 0 },
	{0x90C6,0x00, BYTE_LEN, 0 },
	{0x90C7,0x02, BYTE_LEN, 0 },
	{0x90C8,0x04, BYTE_LEN, 0 },
	{0x90C9,0x0a, BYTE_LEN, 0 },
	{0x90CA,0x10, BYTE_LEN, 0 },
	{0x90CB,0x28, BYTE_LEN, 0 },
	{0x90CC,0x50, BYTE_LEN, 0 },
	{0x90CD,0xC0, BYTE_LEN, 0 },
	{0x90CE,0x40, BYTE_LEN, 0 },
	{0x90CF,0x01, BYTE_LEN, 0 },
	{0x90D0,0x03, BYTE_LEN, 0 },
	{0x90D1,0x05, BYTE_LEN, 0 },
	{0x90D2,0x08, BYTE_LEN, 0 },
	{0x90D3,0x08, BYTE_LEN, 0 },
	{0x90D4,0x30, BYTE_LEN, 0 },
	{0x90D5,0x40, BYTE_LEN, 0 },
	{0x90D6,0xE0, BYTE_LEN, 0 },
	{0x90D7,0x40, BYTE_LEN, 0 },
	{0x90D8,0x81, BYTE_LEN, 0 },
	{0x90D9,0x03, BYTE_LEN, 0 },
	{0x90DA,0x04, BYTE_LEN, 0 },
	{0x90DB,0x0a, BYTE_LEN, 0 },
	{0x90DC,0x0c, BYTE_LEN, 0 },
	{0x90DD,0x30, BYTE_LEN, 0 },
	{0x90DE,0x30, BYTE_LEN, 0 },
	{0x90DF,0xC0, BYTE_LEN, 0 },
	{0x90E0,0x40, BYTE_LEN, 0 },
	{0x90E1,0x01, BYTE_LEN, 0 },
	{0x90E2,0x03, BYTE_LEN, 0 },
	{0x90E3,0x05, BYTE_LEN, 0 },
	{0x90E4,0x0c, BYTE_LEN, 0 },
	{0x90E5,0x14, BYTE_LEN, 0 },
	{0x90E6,0x20, BYTE_LEN, 0 },
	{0x90E7,0x20, BYTE_LEN, 0 },
	{0x90E8,0xC0, BYTE_LEN, 0 },
	{0x90E9,0x00, BYTE_LEN, 0 },
	{0x90EA,0x81, BYTE_LEN, 0 },
	{0x90EB,0x03, BYTE_LEN, 0 },
	{0x90EC,0x05, BYTE_LEN, 0 },
	{0x90ED,0x0e, BYTE_LEN, 0 },
	{0x90EE,0x10, BYTE_LEN, 0 },
	{0x90EF,0x28, BYTE_LEN, 0 },
	{0x90F0,0x30, BYTE_LEN, 0 },
	{0x90F1,0xC0, BYTE_LEN, 0 },
	{0x90F2,0xC0, BYTE_LEN, 0 },
	{0x90F3,0x00, BYTE_LEN, 0 },
	{0x90F4,0x03, BYTE_LEN, 0 },
	{0x90F5,0x01, BYTE_LEN, 0 },
	{0x90F6,0xE6, BYTE_LEN, 0 },
	{0x90F7,0x07, BYTE_LEN, 0 },
	{0x90F8,0x98, BYTE_LEN, 0 },
	{0x90F9,0x1f, BYTE_LEN, 0 },
	{0x90FA,0x40, BYTE_LEN, 0 },
	{0x90FB,0x7e, BYTE_LEN, 0 },
	{0x90FC,0x80, BYTE_LEN, 0 },
	{0x90FD,0xFa, BYTE_LEN, 0 },
	{0x90FE,0x01, BYTE_LEN, 0 },
	{0x90FF,0xE2, BYTE_LEN, 0 },
	{0x9100,0x03, BYTE_LEN, 0 },
	{0x9101,0xC0, BYTE_LEN, 0 },
	{0x9102,0x0f, BYTE_LEN, 0 },
	{0x9103,0x80, BYTE_LEN, 0 },
	{0x9104,0x7e, BYTE_LEN, 0 },
	{0x9105,0x80, BYTE_LEN, 0 },
	{0x9106,0xFb, BYTE_LEN, 0 },
	{0x9107,0x01, BYTE_LEN, 0 },
	{0x9108,0xEe, BYTE_LEN, 0 },
	{0x9109,0x07, BYTE_LEN, 0 },
	{0x910A,0x98, BYTE_LEN, 0 },
	{0x910B,0x1f, BYTE_LEN, 0 },
	{0x910C,0x60, BYTE_LEN, 0 },
	{0x910D,0x7e, BYTE_LEN, 0 },
	{0x910E,0x00, BYTE_LEN, 0 },
	{0x910F,0xF9, BYTE_LEN, 0 },
	{0x9110,0x01, BYTE_LEN, 0 },
	{0x9111,0xEa, BYTE_LEN, 0 },
	{0x9112,0x07, BYTE_LEN, 0 },
	{0x9113,0x88, BYTE_LEN, 0 },
	{0x9114,0x0f, BYTE_LEN, 0 },
	{0x9115,0x00, BYTE_LEN, 0 },
	{0x9116,0x3f, BYTE_LEN, 0 },
	{0x9117,0x00, BYTE_LEN, 0 },
	{0x9118,0xFa, BYTE_LEN, 0 },
	{0x9119,0x01, BYTE_LEN, 0 },
	{0x911A,0xEe, BYTE_LEN, 0 },
	{0x911B,0x07, BYTE_LEN, 0 },
	{0x911C,0xB8, BYTE_LEN, 0 },
	{0x911D,0x3f, BYTE_LEN, 0 },
	{0x911E,0x80, BYTE_LEN, 0 },
	{0x911F,0xFe, BYTE_LEN, 0 },
	{0x9120,0x00, BYTE_LEN, 0 },
	{0x9121,0xFa, BYTE_LEN, 0 },
	{0x9122,0x01, BYTE_LEN, 0 },
	{0x9123,0xDc, BYTE_LEN, 0 },
	{0x9124,0x03, BYTE_LEN, 0 },
	{0x9125,0xA8, BYTE_LEN, 0 },
	{0x9126,0x2f, BYTE_LEN, 0 },
	{0x9127,0x00, BYTE_LEN, 0 },
	{0x9128,0x7f, BYTE_LEN, 0 },
	{0x9129,0x00, BYTE_LEN, 0 },
	{0x912A,0xFb, BYTE_LEN, 0 },
	{0x912B,0x03, BYTE_LEN, 0 },
	{0x912C,0xEe, BYTE_LEN, 0 },
	{0x912D,0x07, BYTE_LEN, 0 },
	{0x912E,0xC8, BYTE_LEN, 0 },
	{0x912F,0x1f, BYTE_LEN, 0 },
	{0x9130,0x20, BYTE_LEN, 0 },
	{0x9131,0xFf, BYTE_LEN, 0 },
	{0x9132,0x00, BYTE_LEN, 0 },
	{0x9133,0xFa, BYTE_LEN, 0 },
	{0x9134,0x03, BYTE_LEN, 0 },
	{0x9135,0xE8, BYTE_LEN, 0 },
	{0x9136,0x03, BYTE_LEN, 0 },
	{0x9137,0xA0, BYTE_LEN, 0 },
	{0x9138,0x3f, BYTE_LEN, 0 },
	{0x9139,0xC0, BYTE_LEN, 0 },
	{0x913A,0xFe, BYTE_LEN, 0 },
	{0x913B,0xFf, BYTE_LEN, 0 },
	{0x913C,0xFb, BYTE_LEN, 0 },
	{0x913D,0xFf, BYTE_LEN, 0 },
	{0x913E,0xF1, BYTE_LEN, 0 },
	{0x913F,0x03, BYTE_LEN, 0 },
	{0x9140,0xB8, BYTE_LEN, 0 },
	{0x9141,0x0f, BYTE_LEN, 0 },
	{0x9142,0xC0, BYTE_LEN, 0 },
	{0x9143,0x3e, BYTE_LEN, 0 },
	{0x9144,0x00, BYTE_LEN, 0 },
	{0x9145,0xFb, BYTE_LEN, 0 },
	{0x9146,0x03, BYTE_LEN, 0 },
	{0x9147,0xE6, BYTE_LEN, 0 },
	{0x9148,0x0f, BYTE_LEN, 0 },
	{0x9149,0x98, BYTE_LEN, 0 },
	{0x914A,0x1f, BYTE_LEN, 0 },
	{0x914B,0x00, BYTE_LEN, 0 },
	{0x914C,0xFf, BYTE_LEN, 0 },
	{0x914D,0x7f, BYTE_LEN, 0 },
	{0x914E,0xFc, BYTE_LEN, 0 },
	{0x914F,0xFf, BYTE_LEN, 0 },
	{0x9150,0xF3, BYTE_LEN, 0 },
	{0x9151,0xFb, BYTE_LEN, 0 },
	{0x9152,0xC7, BYTE_LEN, 0 },
	{0x9153,0xDf, BYTE_LEN, 0 },
	{0x9154,0x1f, BYTE_LEN, 0 },
	{0x9155,0xFf, BYTE_LEN, 0 },
	{0x9156,0xFf, BYTE_LEN, 0 },
	{0x9157,0xFb, BYTE_LEN, 0 },
	{0x9158,0xFf, BYTE_LEN, 0 },
	{0x9159,0xEf, BYTE_LEN, 0 },
	{0x915A,0x0f, BYTE_LEN, 0 },
	{0x915B,0xC0, BYTE_LEN, 0 },
	{0x915C,0x3f, BYTE_LEN, 0 },
	{0x915D,0x00, BYTE_LEN, 0 },
	{0x915E,0x7f, BYTE_LEN, 0 },
	{0x915F,0x80, BYTE_LEN, 0 },
	{0x9160,0xFc, BYTE_LEN, 0 },
	{0x9161,0xFf, BYTE_LEN, 0 },
	{0x9162,0xF7, BYTE_LEN, 0 },
	{0x9163,0xFf, BYTE_LEN, 0 },
	{0x9164,0xC7, BYTE_LEN, 0 },
	{0x9165,0xEf, BYTE_LEN, 0 },
	{0x9166,0x5f, BYTE_LEN, 0 },
	{0x9167,0xBf, BYTE_LEN, 0 },
	{0x9168,0xFf, BYTE_LEN, 0 },
	{0x9169,0xFd, BYTE_LEN, 0 },
	{0x916A,0x00, BYTE_LEN, 0 },
	{0x916B,0xFc, BYTE_LEN, 0 },
	{0x916C,0x03, BYTE_LEN, 0 },
	{0x916D,0xF0, BYTE_LEN, 0 },
	{0x916E,0x4f, BYTE_LEN, 0 },
	{0x916F,0x60, BYTE_LEN, 0 },
	{0x9170,0x3f, BYTE_LEN, 0 },
	{0x9171,0x81, BYTE_LEN, 0 },
	{0x9172,0xFd, BYTE_LEN, 0 },
	{0x9173,0x03, BYTE_LEN, 0 },
	{0x9174,0xFc, BYTE_LEN, 0 },
	{0x9175,0xFf, BYTE_LEN, 0 },
	{0x9176,0xEf, BYTE_LEN, 0 },
	{0x9177,0x0f, BYTE_LEN, 0 },
	{0x9178,0x00, BYTE_LEN, 0 },
	{0x9179,0x00, BYTE_LEN, 0 },
	{0x917A,0x80, BYTE_LEN, 0 },
	{0x917B,0xFe, BYTE_LEN, 0 },
	{0x917C,0xFf, BYTE_LEN, 0 },
	{0x917D,0xFd, BYTE_LEN, 0 },
	{0x917E,0x07, BYTE_LEN, 0 },
	{0x917F,0x08, BYTE_LEN, 0 },
	{0x9180,0x10, BYTE_LEN, 0 },
	{0x9181,0x20, BYTE_LEN, 0 },
	{0x9182,0x80, BYTE_LEN, 0 },
	{0x9183,0x01, BYTE_LEN, 0 },
	{0x9184,0x00, BYTE_LEN, 0 },
	{0x9185,0x06, BYTE_LEN, 0 },
	{0x9186,0x00, BYTE_LEN, 0 },
	{0x9187,0x10, BYTE_LEN, 0 },
	{0x9188,0x08, BYTE_LEN, 0 },
	{0x9189,0x30, BYTE_LEN, 0 },
	{0x918A,0x20, BYTE_LEN, 0 },
	{0x918B,0x00, BYTE_LEN, 0 },
	{0x918C,0x80, BYTE_LEN, 0 },
	{0x918D,0x01, BYTE_LEN, 0 },
	{0x918E,0x02, BYTE_LEN, 0 },
	{0x918F,0x04, BYTE_LEN, 0 },
	{0x9190,0x00, BYTE_LEN, 0 },
	{0x9191,0x28, BYTE_LEN, 0 },
	{0x9192,0x20, BYTE_LEN, 0 },
	{0x9193,0x00, BYTE_LEN, 0 },
	{0x9194,0x80, BYTE_LEN, 0 },
	{0x9195,0x00, BYTE_LEN, 0 },
	{0x9196,0x00, BYTE_LEN, 0 },
	{0x9197,0x06, BYTE_LEN, 0 },
	{0x9198,0x00, BYTE_LEN, 0 },
	{0x9199,0x18, BYTE_LEN, 0 },
	{0x919A,0x00, BYTE_LEN, 0 },
	{0x919B,0x40, BYTE_LEN, 0 },
	{0x919C,0x40, BYTE_LEN, 0 },
	{0x919D,0x40, BYTE_LEN, 0 },
	{0x919E,0x01, BYTE_LEN, 0 },
	{0x919F,0x02, BYTE_LEN, 0 },
	{0x91A0,0x02, BYTE_LEN, 0 },
	{0x91A1,0x0a, BYTE_LEN, 0 },
	{0x91A2,0x08, BYTE_LEN, 0 },
	{0x91A3,0x38, BYTE_LEN, 0 },
	{0x91A4,0x30, BYTE_LEN, 0 },
	{0x91A5,0xA0, BYTE_LEN, 0 },
	{0x91A6,0x40, BYTE_LEN, 0 },
	{0x91A7,0x01, BYTE_LEN, 0 },
	{0x91A8,0x03, BYTE_LEN, 0 },
	{0x91A9,0x05, BYTE_LEN, 0 },
	{0x91AA,0x0c, BYTE_LEN, 0 },
	{0x91AB,0x1c, BYTE_LEN, 0 },
	{0x91AC,0x18, BYTE_LEN, 0 },
	{0x91AD,0x70, BYTE_LEN, 0 },
	{0x91AE,0x60, BYTE_LEN, 0 },
	{0x91AF,0xC0, BYTE_LEN, 0 },
	{0x91B0,0x01, BYTE_LEN, 0 },
	{0x91B1,0x04, BYTE_LEN, 0 },
	{0x91B2,0x06, BYTE_LEN, 0 },
	{0x91B3,0x0c, BYTE_LEN, 0 },
	{0x91B4,0x0c, BYTE_LEN, 0 },
	{0x91B5,0x28, BYTE_LEN, 0 },
	{0x91B6,0x50, BYTE_LEN, 0 },
	{0x91B7,0x20, BYTE_LEN, 0 },
	{0x91B8,0x81, BYTE_LEN, 0 },
	{0x91B9,0x01, BYTE_LEN, 0 },
	{0x91BA,0x05, BYTE_LEN, 0 },
	{0x91BB,0x04, BYTE_LEN, 0 },
	{0x91BC,0x0e, BYTE_LEN, 0 },
	{0x91BD,0x10, BYTE_LEN, 0 },
	{0x91BE,0x38, BYTE_LEN, 0 },
	{0x91BF,0x70, BYTE_LEN, 0 },
	{0x91C0,0x60, BYTE_LEN, 0 },
	{0x91C1,0xC0, BYTE_LEN, 0 },
	{0x91C2,0x81, BYTE_LEN, 0 },
	{0x91C3,0x01, BYTE_LEN, 0 },
	{0x91C4,0x07, BYTE_LEN, 0 },
	{0x91C5,0x0c, BYTE_LEN, 0 },
	{0x91C6,0x1c, BYTE_LEN, 0 },
	{0x91C7,0x28, BYTE_LEN, 0 },
	{0x91C8,0x60, BYTE_LEN, 0 },
	{0x91C9,0x40, BYTE_LEN, 0 },
	{0x91CA,0x01, BYTE_LEN, 0 },
	{0x91CB,0x01, BYTE_LEN, 0 },
	{0x91CC,0x03, BYTE_LEN, 0 },
	{0x91CD,0x04, BYTE_LEN, 0 },
	{0x91CE,0x10, BYTE_LEN, 0 },
	{0x91CF,0x10, BYTE_LEN, 0 },
	{0x91D0,0x48, BYTE_LEN, 0 },
	{0x91D1,0x40, BYTE_LEN, 0 },
	{0x91D2,0x20, BYTE_LEN, 0 },
	{0x91D3,0xC1, BYTE_LEN, 0 },
	{0x91D4,0x81, BYTE_LEN, 0 },
	{0x91D5,0x01, BYTE_LEN, 0 },
	{0x91D6,0x07, BYTE_LEN, 0 },
	{0x91D7,0x06, BYTE_LEN, 0 },
	{0x91D8,0x1c, BYTE_LEN, 0 },
	{0x91D9,0x30, BYTE_LEN, 0 },
	{0x91DA,0x70, BYTE_LEN, 0 },
	{0x91DB,0xA0, BYTE_LEN, 0 },
	{0x91DC,0x80, BYTE_LEN, 0 },
	{0x91DD,0x01, BYTE_LEN, 0 },
	{0x91DE,0x05, BYTE_LEN, 0 },
	{0x91DF,0x04, BYTE_LEN, 0 },
	{0x91E0,0x0c, BYTE_LEN, 0 },
	{0x91E1,0x10, BYTE_LEN, 0 },
	{0x91E2,0x40, BYTE_LEN, 0 },
	{0x91E3,0x40, BYTE_LEN, 0 },
	{0x91E4,0x20, BYTE_LEN, 0 },
	{0x91E5,0x01, BYTE_LEN, 0 },
	{0x91E6,0x81, BYTE_LEN, 0 },
	{0x91E7,0x04, BYTE_LEN, 0 },

	{0xA000,0x9191, WORD_LEN, 0 },
	{0xA002,0x4c, BYTE_LEN, 0 },
	{0xA003,0x11, BYTE_LEN, 0 },
	{0xA004,0x0d, BYTE_LEN, 0 },
	{0xA005,0x5b, BYTE_LEN, 0 },
	{0xA006,0x98, BYTE_LEN, 0 },
	{0xA007,0xE3, BYTE_LEN, 0 },
	{0xA008,0x96, BYTE_LEN, 0 },
	{0xA009,0xE7, BYTE_LEN, 0 },
	{0xA00A,0x9c, BYTE_LEN, 0 },
	{0xA00B,0x65, BYTE_LEN, 0 },
	{0xA00C,0x38, BYTE_LEN, 0 },
	{0xA00D,0x63, BYTE_LEN, 0 },
	{0xA00E,0xE1, BYTE_LEN, 0 },
	{0xA00F,0xCd, BYTE_LEN, 0 },
	{0xA010,0x58, BYTE_LEN, 0 },
	{0xA011,0x76, BYTE_LEN, 0 },
	{0xA012,0x73, BYTE_LEN, 0 },
	{0xA013,0x16, BYTE_LEN, 0 },
	{0xA014,0xE2, BYTE_LEN, 0 },
	{0xA015,0x94, BYTE_LEN, 0 },
	{0xA016,0xC5, BYTE_LEN, 0 },
	{0xA017,0x38, BYTE_LEN, 0 },
	{0xA018,0x4a, BYTE_LEN, 0 },
	{0xA019,0x19, BYTE_LEN, 0 },
	{0xA01A,0x0d, BYTE_LEN, 0 },
	{0xA01B,0x5e, BYTE_LEN, 0 },
	{0xA01C,0xB6, BYTE_LEN, 0 },
	{0xA01D,0x23, BYTE_LEN, 0 },
	{0xA01E,0x18, BYTE_LEN, 0 },
	{0xA01F,0xF4, BYTE_LEN, 0 },
	{0xA020,0xF8, BYTE_LEN, 0 },
	{0xA021,0xE5, BYTE_LEN, 0 },
	{0xA022,0x3b, BYTE_LEN, 0 },
	{0xA023,0x79, BYTE_LEN, 0 },
	{0xA024,0x91, BYTE_LEN, 0 },
	{0xA025,0x0e, BYTE_LEN, 0 },
	{0xA026,0x5d, BYTE_LEN, 0 },
	{0xA027,0x94, BYTE_LEN, 0 },
	{0xA028,0x43, BYTE_LEN, 0 },
	{0xA029,0x17, BYTE_LEN, 0 },
	{0xA02A,0xE5, BYTE_LEN, 0 },
	{0xA02B,0xD8, BYTE_LEN, 0 },
	{0xA02C,0x05, BYTE_LEN, 0 },
	{0xA02D,0x3a, BYTE_LEN, 0 },
	{0xA02E,0x78, BYTE_LEN, 0 },
	{0xA02F,0xC9, BYTE_LEN, 0 },
	{0xA030,0x4e, BYTE_LEN, 0 },
	{0xA031,0x5b, BYTE_LEN, 0 },
	{0xA032,0xA2, BYTE_LEN, 0 },
	{0xA033,0x83, BYTE_LEN, 0 },
	{0xA034,0x97, BYTE_LEN, 0 },
	{0xA035,0xEa, BYTE_LEN, 0 },
	{0xA036,0xF8, BYTE_LEN, 0 },
	{0xA037,0x05, BYTE_LEN, 0 },
	{0xA038,0x3b, BYTE_LEN, 0 },
	{0xA039,0x6b, BYTE_LEN, 0 },
	{0xA03A,0xC9, BYTE_LEN, 0 },
	{0xA03B,0x8d, BYTE_LEN, 0 },
	{0xA03C,0x57, BYTE_LEN, 0 },
	{0xA03D,0x3e, BYTE_LEN, 0 },
	{0xA03E,0x63, BYTE_LEN, 0 },
	{0xA03F,0x15, BYTE_LEN, 0 },
	{0xA040,0xC9, BYTE_LEN, 0 },
	{0xA041,0x64, BYTE_LEN, 0 },
	{0xA042,0xE5, BYTE_LEN, 0 },
	{0xA043,0x32, BYTE_LEN, 0 },
	{0xA044,0x62, BYTE_LEN, 0 },
	{0xA045,0x41, BYTE_LEN, 0 },
	{0xA046,0x4d, BYTE_LEN, 0 },
	{0xA047,0x5c, BYTE_LEN, 0 },
	{0xA048,0x88, BYTE_LEN, 0 },
	{0xA049,0x63, BYTE_LEN, 0 },
	{0xA04A,0x96, BYTE_LEN, 0 },
	{0xA04B,0xDf, BYTE_LEN, 0 },
	{0xA04C,0xD4, BYTE_LEN, 0 },
	{0xA04D,0xE5, BYTE_LEN, 0 },
	{0xA04E,0x38, BYTE_LEN, 0 },
	{0xA04F,0x6d, BYTE_LEN, 0 },
	{0xA050,0xA9, BYTE_LEN, 0 },
	{0xA051,0x4d, BYTE_LEN, 0 },
	{0xA052,0x54, BYTE_LEN, 0 },
	{0xA053,0x08, BYTE_LEN, 0 },
	{0xA054,0xD3, BYTE_LEN, 0 },
	{0xA055,0x13, BYTE_LEN, 0 },
	{0xA056,0xB0, BYTE_LEN, 0 },
	{0xA057,0xD0, BYTE_LEN, 0 },
	{0xA058,0x24, BYTE_LEN, 0 },
	{0xA059,0x2a, BYTE_LEN, 0 },
	{0xA05A,0x3a, BYTE_LEN, 0 },
	{0xA05B,0xC1, BYTE_LEN, 0 },
	{0xA05C,0x4a, BYTE_LEN, 0 },
	{0xA05D,0x52, BYTE_LEN, 0 },
	{0xA05E,0xE6, BYTE_LEN, 0 },
	{0xA05F,0xE2, BYTE_LEN, 0 },
	{0xA060,0x95, BYTE_LEN, 0 },
	{0xA061,0xCe, BYTE_LEN, 0 },
	{0xA062,0x84, BYTE_LEN, 0 },
	{0xA063,0x85, BYTE_LEN, 0 },
	{0xA064,0x35, BYTE_LEN, 0 },
	{0xA065,0x6d, BYTE_LEN, 0 },
	{0xA066,0x89, BYTE_LEN, 0 },
	{0xA067,0x4d, BYTE_LEN, 0 },
	{0xA068,0x57, BYTE_LEN, 0 },
	{0xA069,0x26, BYTE_LEN, 0 },
	{0xA06A,0xA3, BYTE_LEN, 0 },
	{0xA06B,0x13, BYTE_LEN, 0 },
	{0xA06C,0xAc, BYTE_LEN, 0 },
	{0xA06D,0x74, BYTE_LEN, 0 },
	{0xA06E,0x84, BYTE_LEN, 0 },
	{0xA06F,0x25, BYTE_LEN, 0 },
	{0xA070,0x13, BYTE_LEN, 0 },
	{0xA071,0xD9, BYTE_LEN, 0 },
	{0xA072,0x48, BYTE_LEN, 0 },
	{0xA073,0x46, BYTE_LEN, 0 },
	{0xA074,0x46, BYTE_LEN, 0 },
	{0xA075,0x02, BYTE_LEN, 0 },
	{0xA076,0x13, BYTE_LEN, 0 },
	{0xA077,0xA4, BYTE_LEN, 0 },
	{0xA078,0x34, BYTE_LEN, 0 },
	{0xA079,0xE5, BYTE_LEN, 0 },
	{0xA07A,0x2e, BYTE_LEN, 0 },
	{0xA07B,0x58, BYTE_LEN, 0 },
	{0xA07C,0x81, BYTE_LEN, 0 },
	{0xA07D,0x8c, BYTE_LEN, 0 },
	{0xA07E,0x58, BYTE_LEN, 0 },
	{0xA07F,0x38, BYTE_LEN, 0 },
	{0xA080,0x23, BYTE_LEN, 0 },
	{0xA081,0x95, BYTE_LEN, 0 },
	{0xA082,0xBe, BYTE_LEN, 0 },
	{0xA083,0xB0, BYTE_LEN, 0 },
	{0xA084,0xE4, BYTE_LEN, 0 },
	{0xA085,0x27, BYTE_LEN, 0 },
	{0xA086,0x0c, BYTE_LEN, 0 },
	{0xA087,0x91, BYTE_LEN, 0 },
	{0xA088,0x08, BYTE_LEN, 0 },
	{0xA089,0x40, BYTE_LEN, 0 },
	{0xA08A,0x00, BYTE_LEN, 0 },
	{0xA08B,0x72, BYTE_LEN, 0 },
	{0xA08C,0x10, BYTE_LEN, 0 },
	{0xA08D,0x85, BYTE_LEN, 0 },
	{0xA08E,0x84, BYTE_LEN, 0 },
	{0xA08F,0xC4, BYTE_LEN, 0 },
	{0xA090,0x25, BYTE_LEN, 0 },
	{0xA091,0x42, BYTE_LEN, 0 },
	{0xA092,0x19, BYTE_LEN, 0 },
	{0xA093,0x4b, BYTE_LEN, 0 },
	{0xA094,0x53, BYTE_LEN, 0 },
	{0xA095,0xFc, BYTE_LEN, 0 },
	{0xA096,0x22, BYTE_LEN, 0 },
	{0xA097,0x96, BYTE_LEN, 0 },
	{0xA098,0xCf, BYTE_LEN, 0 },
	{0xA099,0x48, BYTE_LEN, 0 },
	{0xA09A,0xC5, BYTE_LEN, 0 },
	{0xA09B,0x2f, BYTE_LEN, 0 },
	{0xA09C,0x2b, BYTE_LEN, 0 },
	{0xA09D,0xF1, BYTE_LEN, 0 },
	{0xA09E,0xC9, BYTE_LEN, 0 },
	{0xA09F,0x42, BYTE_LEN, 0 },
	{0xA0A0,0x20, BYTE_LEN, 0 },
	{0xA0A1,0xF2, BYTE_LEN, 0 },
	{0xA0A2,0x8f, BYTE_LEN, 0 },
	{0xA0A3,0x7f, BYTE_LEN, 0 },
	{0xA0A4,0x14, BYTE_LEN, 0 },
	{0xA0A5,0xC4, BYTE_LEN, 0 },
	{0xA0A6,0x20, BYTE_LEN, 0 },
	{0xA0A7,0x1f, BYTE_LEN, 0 },
	{0xA0A8,0x51, BYTE_LEN, 0 },
	{0xA0A9,0x49, BYTE_LEN, 0 },
	{0xA0AA,0x50, BYTE_LEN, 0 },
	{0xA0AB,0xC0, BYTE_LEN, 0 },
	{0xA0AC,0xC2, BYTE_LEN, 0 },
	{0xA0AD,0x14, BYTE_LEN, 0 },
	{0xA0AE,0xBd, BYTE_LEN, 0 },
	{0xA0AF,0xC8, BYTE_LEN, 0 },
	{0xA0B0,0x85, BYTE_LEN, 0 },
	{0xA0B1,0x36, BYTE_LEN, 0 },
	{0xA0B2,0x60, BYTE_LEN, 0 },
	{0xA0B3,0x99, BYTE_LEN, 0 },
	{0xA0B4,0x8c, BYTE_LEN, 0 },
	{0xA0B5,0x4e, BYTE_LEN, 0 },
	{0xA0B6,0xA8, BYTE_LEN, 0 },
	{0xA0B7,0xC2, BYTE_LEN, 0 },
	{0xA0B8,0x91, BYTE_LEN, 0 },
	{0xA0B9,0x93, BYTE_LEN, 0 },
	{0xA0BA,0x40, BYTE_LEN, 0 },
	{0xA0BB,0x84, BYTE_LEN, 0 },
	{0xA0BC,0x22, BYTE_LEN, 0 },
	{0xA0BD,0x16, BYTE_LEN, 0 },
	{0xA0BE,0xD9, BYTE_LEN, 0 },
	{0xA0BF,0x48, BYTE_LEN, 0 },
	{0xA0C0,0x4b, BYTE_LEN, 0 },
	{0xA0C1,0x7a, BYTE_LEN, 0 },
	{0xA0C2,0xA2, BYTE_LEN, 0 },
	{0xA0C3,0x94, BYTE_LEN, 0 },
	{0xA0C4,0xB8, BYTE_LEN, 0 },
	{0xA0C5,0x58, BYTE_LEN, 0 },
	{0xA0C6,0x85, BYTE_LEN, 0 },
	{0xA0C7,0x31, BYTE_LEN, 0 },
	{0xA0C8,0x7d, BYTE_LEN, 0 },
	{0xA0C9,0x49, BYTE_LEN, 0 },
	{0xA0CA,0x0e, BYTE_LEN, 0 },
	{0xA0CB,0x5d, BYTE_LEN, 0 },
	{0xA0CC,0x6a, BYTE_LEN, 0 },
	{0xA0CD,0x53, BYTE_LEN, 0 },
	{0xA0CE,0x95, BYTE_LEN, 0 },
	{0xA0CF,0xC0, BYTE_LEN, 0 },
	{0xA0D0,0xF8, BYTE_LEN, 0 },
	{0xA0D1,0x64, BYTE_LEN, 0 },
	{0xA0D2,0x2b, BYTE_LEN, 0 },
	{0xA0D3,0x32, BYTE_LEN, 0 },
	{0xA0D4,0x31, BYTE_LEN, 0 },
	{0xA0D5,0x4a, BYTE_LEN, 0 },
	{0xA0D6,0x4d, BYTE_LEN, 0 },
	{0xA0D7,0x98, BYTE_LEN, 0 },
	{0xA0D8,0x62, BYTE_LEN, 0 },
	{0xA0D9,0x94, BYTE_LEN, 0 },
	{0xA0DA,0xB4, BYTE_LEN, 0 },
	{0xA0DB,0x74, BYTE_LEN, 0 },
	{0xA0DC,0xA5, BYTE_LEN, 0 },
	{0xA0DD,0x32, BYTE_LEN, 0 },
	{0xA0DE,0x64, BYTE_LEN, 0 },
	{0xA0DF,0x41, BYTE_LEN, 0 },
	{0xA0E0,0xCd, BYTE_LEN, 0 },
	{0xA0E1,0x60, BYTE_LEN, 0 },
	{0xA0E2,0xBa, BYTE_LEN, 0 },
	{0xA0E3,0x83, BYTE_LEN, 0 },
	{0xA0E4,0x18, BYTE_LEN, 0 },
	{0xA0E5,0xEe, BYTE_LEN, 0 },
	{0xA0E6,0xC8, BYTE_LEN, 0 },
	{0xA0E7,0x85, BYTE_LEN, 0 },
	{0xA0E8,0x36, BYTE_LEN, 0 },
	{0xA0E9,0x60, BYTE_LEN, 0 },
	{0xA0EA,0xB1, BYTE_LEN, 0 },
	{0xA0EB,0x8c, BYTE_LEN, 0 },
	{0xA0EC,0x55, BYTE_LEN, 0 },
	{0xA0ED,0x0e, BYTE_LEN, 0 },
	{0xA0EE,0x73, BYTE_LEN, 0 },
	{0xA0EF,0x15, BYTE_LEN, 0 },
	{0xA0F0,0xC5, BYTE_LEN, 0 },
	{0xA0F1,0x88, BYTE_LEN, 0 },
	{0xA0F2,0xE5, BYTE_LEN, 0 },
	{0xA0F3,0x33, BYTE_LEN, 0 },
	{0xA0F4,0x74, BYTE_LEN, 0 },
	{0xA0F5,0x09, BYTE_LEN, 0 },
	{0xA0F6,0x0e, BYTE_LEN, 0 },
	{0xA0F7,0x5b, BYTE_LEN, 0 },
	{0xA0F8,0x7a, BYTE_LEN, 0 },
	{0xA0F9,0xA3, BYTE_LEN, 0 },
	{0xA0FA,0x18, BYTE_LEN, 0 },
	{0xA0FB,0xF7, BYTE_LEN, 0 },
	{0xA0FC,0x48, BYTE_LEN, 0 },
	{0xA0FD,0x46, BYTE_LEN, 0 },
	{0xA0FE,0x3e, BYTE_LEN, 0 },
	{0xA0FF,0x89, BYTE_LEN, 0 },
	{0xA100,0x01, BYTE_LEN, 0 },
	{0xA101,0x8f, BYTE_LEN, 0 },
	{0xA102,0x5f, BYTE_LEN, 0 },
	{0xA103,0xA6, BYTE_LEN, 0 },
	{0xA104,0x83, BYTE_LEN, 0 },
	{0xA105,0x97, BYTE_LEN, 0 },
	{0xA106,0xE6, BYTE_LEN, 0 },
	{0xA107,0xE4, BYTE_LEN, 0 },
	{0xA108,0xA5, BYTE_LEN, 0 },
	{0xA109,0x39, BYTE_LEN, 0 },
	{0xA10A,0x7b, BYTE_LEN, 0 },
	{0xA10B,0x81, BYTE_LEN, 0 },
	{0xA10C,0x8e, BYTE_LEN, 0 },
	{0xA10D,0x5f, BYTE_LEN, 0 },
	{0xA10E,0xB4, BYTE_LEN, 0 },
	{0xA10F,0x33, BYTE_LEN, 0 },
	{0xA110,0x17, BYTE_LEN, 0 },
	{0xA111,0xE8, BYTE_LEN, 0 },
	{0xA112,0x78, BYTE_LEN, 0 },
	{0xA113,0xA5, BYTE_LEN, 0 },
	{0xA114,0x36, BYTE_LEN, 0 },
	{0xA115,0x7b, BYTE_LEN, 0 },
	{0xA116,0xD1, BYTE_LEN, 0 },
	{0xA117,0x0e, BYTE_LEN, 0 },
	{0xA118,0x5e, BYTE_LEN, 0 },
	{0xA119,0x9e, BYTE_LEN, 0 },
	{0xA11A,0xB3, BYTE_LEN, 0 },
	{0xA11B,0x16, BYTE_LEN, 0 },
	{0xA11C,0xE3, BYTE_LEN, 0 },
	{0xA11D,0xA8, BYTE_LEN, 0 },
	{0xA11E,0xA5, BYTE_LEN, 0 },
	{0xA11F,0x38, BYTE_LEN, 0 },
	{0xA120,0x69, BYTE_LEN, 0 },
	{0xA121,0x19, BYTE_LEN, 0 },
	{0xA122,0x4e, BYTE_LEN, 0 },
	{0xA123,0x5b, BYTE_LEN, 0 },
	{0xA124,0x88, BYTE_LEN, 0 },
	{0xA125,0xB3, BYTE_LEN, 0 },
	{0xA126,0x96, BYTE_LEN, 0 },
	{0xA127,0xE2, BYTE_LEN, 0 },
	{0xA128,0x50, BYTE_LEN, 0 },
	{0xA129,0x45, BYTE_LEN, 0 },
	{0xA12A,0x35, BYTE_LEN, 0 },
	{0xA12B,0x42, BYTE_LEN, 0 },
	{0xA12C,0x89, BYTE_LEN, 0 },
	{0xA12D,0x8a, BYTE_LEN, 0 },
	{0xA12E,0x57, BYTE_LEN, 0 },
	{0xA12F,0xE0, BYTE_LEN, 0 },
	{0xA130,0xF2, BYTE_LEN, 0 },
	{0xA131,0x95, BYTE_LEN, 0 },
	{0xA132,0xB8, BYTE_LEN, 0 },
	{0xA133,0x6c, BYTE_LEN, 0 },
	{0xA134,0x45, BYTE_LEN, 0 },
	{0xA135,0x2d, BYTE_LEN, 0 },
	{0xA136,0x5c, BYTE_LEN, 0 },
	{0xA137,0x39, BYTE_LEN, 0 },
	{0xA138,0x8b, BYTE_LEN, 0 },
	{0xA139,0x56, BYTE_LEN, 0 },
	{0xA13A,0xCc, BYTE_LEN, 0 },
	{0xA13B,0xF2, BYTE_LEN, 0 },
	{0xA13C,0x15, BYTE_LEN, 0 },
	{0xA13D,0xB5, BYTE_LEN, 0 },
	{0xA13E,0x7c, BYTE_LEN, 0 },
	{0xA13F,0x25, BYTE_LEN, 0 },
	{0xA140,0x2d, BYTE_LEN, 0 },
	{0xA141,0x44, BYTE_LEN, 0 },
	{0xA142,0x71, BYTE_LEN, 0 },
	{0xA143,0x8a, BYTE_LEN, 0 },
	{0xA144,0x59, BYTE_LEN, 0 },
	{0xA145,0xF8, BYTE_LEN, 0 },
	{0xA146,0x02, BYTE_LEN, 0 },
	{0xA147,0x17, BYTE_LEN, 0 },
	{0xA148,0xC3, BYTE_LEN, 0 },
	{0xA149,0xB8, BYTE_LEN, 0 },
	{0xA14A,0x05, BYTE_LEN, 0 },
	{0xA14B,0x30, BYTE_LEN, 0 },
	{0xA14C,0x6b, BYTE_LEN, 0 },
	{0xA14D,0xD9, BYTE_LEN, 0 },
	{0xA14E,0xCb, BYTE_LEN, 0 },
	{0xA14F,0x5a, BYTE_LEN, 0 },
	{0xA150,0xEe, BYTE_LEN, 0 },
	{0xA151,0xC2, BYTE_LEN, 0 },
	{0xA152,0x16, BYTE_LEN, 0 },
	{0xA153,0xBc, BYTE_LEN, 0 },
	{0xA154,0xB8, BYTE_LEN, 0 },
	{0xA155,0x25, BYTE_LEN, 0 },
	{0xA156,0x2f, BYTE_LEN, 0 },
	{0xA157,0x70, BYTE_LEN, 0 },
	{0xA158,0xE1, BYTE_LEN, 0 },
	{0xA159,0x0b, BYTE_LEN, 0 },
	{0xA15A,0x59, BYTE_LEN, 0 },
	{0xA15B,0xE2, BYTE_LEN, 0 },
	{0xA15C,0x32, BYTE_LEN, 0 },
	{0xA15D,0x16, BYTE_LEN, 0 },
	{0xA15E,0xBc, BYTE_LEN, 0 },
	{0xA15F,0xAc, BYTE_LEN, 0 },
	{0xA160,0xC5, BYTE_LEN, 0 },
	{0xA161,0x2f, BYTE_LEN, 0 },
	{0xA162,0x5d, BYTE_LEN, 0 },
	{0xA163,0x61, BYTE_LEN, 0 },
	{0xA164,0x4b, BYTE_LEN, 0 },
	{0xA165,0x55, BYTE_LEN, 0 },
	{0xA166,0xC0, BYTE_LEN, 0 },
	{0xA167,0x22, BYTE_LEN, 0 },
	{0xA168,0x15, BYTE_LEN, 0 },
	{0xA169,0xAd, BYTE_LEN, 0 },
	{0xA16A,0x54, BYTE_LEN, 0 },
	{0xA16B,0x85, BYTE_LEN, 0 },
	{0xA16C,0x2b, BYTE_LEN, 0 },
	{0xA16D,0x5f, BYTE_LEN, 0 },
	{0xA16E,0x31, BYTE_LEN, 0 },
	{0xA16F,0xCb, BYTE_LEN, 0 },
	{0xA170,0x5a, BYTE_LEN, 0 },
	{0xA171,0xE8, BYTE_LEN, 0 },
	{0xA172,0xE2, BYTE_LEN, 0 },
	{0xA173,0x15, BYTE_LEN, 0 },
	{0xA174,0xB5, BYTE_LEN, 0 },
	{0xA175,0x7c, BYTE_LEN, 0 },
	{0xA176,0x45, BYTE_LEN, 0 },
	{0xA177,0x2e, BYTE_LEN, 0 },
	{0xA178,0x5b, BYTE_LEN, 0 },
	{0xA179,0x61, BYTE_LEN, 0 },
	{0xA17A,0xCb, BYTE_LEN, 0 },
	{0xA17B,0x51, BYTE_LEN, 0 },
	{0xA17C,0xA6, BYTE_LEN, 0 },
	{0xA17D,0x92, BYTE_LEN, 0 },
	{0xA17E,0x93, BYTE_LEN, 0 },
	{0xA17F,0x9f, BYTE_LEN, 0 },
	{0xA180,0xCc, BYTE_LEN, 0 },
	{0xA181,0xE4, BYTE_LEN, 0 },
	{0xA182,0x26, BYTE_LEN, 0 },
	{0xA183,0x38, BYTE_LEN, 0 },
	{0xA184,0xD9, BYTE_LEN, 0 },
	{0xA185,0x89, BYTE_LEN, 0 },
	{0xA186,0x51, BYTE_LEN, 0 },
	{0xA187,0x94, BYTE_LEN, 0 },
	{0xA188,0x72, BYTE_LEN, 0 },
	{0xA189,0x15, BYTE_LEN, 0 },
	{0xA18A,0xAf, BYTE_LEN, 0 },
	{0xA18B,0x5c, BYTE_LEN, 0 },
	{0xA18C,0x25, BYTE_LEN, 0 },
	{0xA18D,0x2c, BYTE_LEN, 0 },
	{0xA18E,0x57, BYTE_LEN, 0 },
	{0xA18F,0x41, BYTE_LEN, 0 },
	{0xA190,0x4b, BYTE_LEN, 0 },
	{0xA191,0x53, BYTE_LEN, 0 },
	{0xA192,0xB4, BYTE_LEN, 0 },
	{0xA193,0x22, BYTE_LEN, 0 },
	{0xA194,0x93, BYTE_LEN, 0 },
	{0xA195,0x9d, BYTE_LEN, 0 },
	{0xA196,0x68, BYTE_LEN, 0 },
	{0xA197,0xC4, BYTE_LEN, 0 },
	{0xA198,0x23, BYTE_LEN, 0 },
	{0xA199,0x12, BYTE_LEN, 0 },
	{0xA19A,0xA1, BYTE_LEN, 0 },
	{0xA19B,0x48, BYTE_LEN, 0 },
	{0xA19C,0x46, BYTE_LEN, 0 },
	{0xA19D,0x34, BYTE_LEN, 0 },
	{0xA19E,0xE2, BYTE_LEN, 0 },
	{0xA19F,0x92, BYTE_LEN, 0 },
	{0xA1A0,0x98, BYTE_LEN, 0 },
	{0xA1A1,0x18, BYTE_LEN, 0 },
	{0xA1A2,0x85, BYTE_LEN, 0 },
	{0xA1A3,0x29, BYTE_LEN, 0 },
	{0xA1A4,0x4c, BYTE_LEN, 0 },
	{0xA1A5,0xB1, BYTE_LEN, 0 },
	{0xA1A6,0x0a, BYTE_LEN, 0 },
	{0xA1A7,0x53, BYTE_LEN, 0 },
	{0xA1A8,0xB8, BYTE_LEN, 0 },
	{0xA1A9,0x32, BYTE_LEN, 0 },
	{0xA1AA,0x94, BYTE_LEN, 0 },
	{0xA1AB,0xA7, BYTE_LEN, 0 },
	{0xA1AC,0x90, BYTE_LEN, 0 },
	{0xA1AD,0x64, BYTE_LEN, 0 },
	{0xA1AE,0x25, BYTE_LEN, 0 },
	{0xA1AF,0x09, BYTE_LEN, 0 },
	{0xA1B0,0x61, BYTE_LEN, 0 },
	{0xA1B1,0x48, BYTE_LEN, 0 },
	{0xA1B2,0x40, BYTE_LEN, 0 },
	{0xA1B3,0x00, BYTE_LEN, 0 },
	{0xA1B4,0x72, BYTE_LEN, 0 },
	{0xA1B5,0x10, BYTE_LEN, 0 },
	{0xA1B6,0x83, BYTE_LEN, 0 },
	{0xA1B7,0x78, BYTE_LEN, 0 },
	{0xA1B8,0x04, BYTE_LEN, 0 },
	{0xA1B9,0x24, BYTE_LEN, 0 },
	{0xA1BA,0x3a, BYTE_LEN, 0 },
	{0xA1BB,0x01, BYTE_LEN, 0 },
	{0xA1BC,0x0a, BYTE_LEN, 0 },
	{0xA1BD,0x50, BYTE_LEN, 0 },
	{0xA1BE,0x94, BYTE_LEN, 0 },
	{0xA1BF,0xE2, BYTE_LEN, 0 },
	{0xA1C0,0x14, BYTE_LEN, 0 },
	{0xA1C1,0xAe, BYTE_LEN, 0 },
	{0xA1C2,0x0c, BYTE_LEN, 0 },
	{0xA1C3,0xC5, BYTE_LEN, 0 },
	{0xA1C4,0x29, BYTE_LEN, 0 },
	{0xA1C5,0x24, BYTE_LEN, 0 },
	{0xA1C6,0x51, BYTE_LEN, 0 },
	{0xA1C7,0xC9, BYTE_LEN, 0 },
	{0xA1C8,0x41, BYTE_LEN, 0 },
	{0xA1C9,0x14, BYTE_LEN, 0 },
	{0xA1CA,0xE2, BYTE_LEN, 0 },
	{0xA1CB,0x8f, BYTE_LEN, 0 },
	{0xA1CC,0x7f, BYTE_LEN, 0 },
	{0xA1CD,0x14, BYTE_LEN, 0 },
	{0xA1CE,0x64, BYTE_LEN, 0 },
	{0xA1CF,0x20, BYTE_LEN, 0 },
	{0xA1D0,0x1b, BYTE_LEN, 0 },
	{0xA1D1,0xE1, BYTE_LEN, 0 },
	{0xA1D2,0xC8, BYTE_LEN, 0 },
	{0xA1D3,0x4d, BYTE_LEN, 0 },
	{0xA1D4,0x7a, BYTE_LEN, 0 },
	{0xA1D5,0xD2, BYTE_LEN, 0 },
	{0xA1D6,0x93, BYTE_LEN, 0 },
	{0xA1D7,0xA3, BYTE_LEN, 0 },
	{0xA1D8,0x70, BYTE_LEN, 0 },
	{0xA1D9,0x45, BYTE_LEN, 0 },
	{0xA1DA,0x2d, BYTE_LEN, 0 },
	{0xA1DB,0x50, BYTE_LEN, 0 },
	{0xA1DC,0xC9, BYTE_LEN, 0 },
	{0xA1DD,0x8a, BYTE_LEN, 0 },
	{0xA1DE,0x4c, BYTE_LEN, 0 },
	{0xA1DF,0x6e, BYTE_LEN, 0 },
	{0xA1E0,0x72, BYTE_LEN, 0 },
	{0xA1E1,0x91, BYTE_LEN, 0 },
	{0xA1E2,0x8c, BYTE_LEN, 0 },
	{0xA1E3,0x30, BYTE_LEN, 0 },
	{0xA1E4,0xA4, BYTE_LEN, 0 },
	{0xA1E5,0x21, BYTE_LEN, 0 },
	{0xA1E6,0x12, BYTE_LEN, 0 },
	{0xA1E7,0x89, BYTE_LEN, 0 },
	{0xA1E8,0x88, BYTE_LEN, 0 },
	{0xA1E9,0x49, BYTE_LEN, 0 },
	{0xA1EA,0x52, BYTE_LEN, 0 },
	{0xA1EB,0xD2, BYTE_LEN, 0 },
	{0xA1EC,0x93, BYTE_LEN, 0 },
	{0xA1ED,0xA2, BYTE_LEN, 0 },
	{0xA1EE,0x10, BYTE_LEN, 0 },
	{0xA1EF,0x25, BYTE_LEN, 0 },
	{0xA1F0,0x2a, BYTE_LEN, 0 },
	{0xA1F1,0x66, BYTE_LEN, 0 },
	{0xA1F2,0x99, BYTE_LEN, 0 },
	{0xA1F3,0x4b, BYTE_LEN, 0 },
	{0xA1F4,0x58, BYTE_LEN, 0 },
	{0xA1F5,0xD6, BYTE_LEN, 0 },
	{0xA1F6,0x92, BYTE_LEN, 0 },
	{0xA1F7,0x94, BYTE_LEN, 0 },
	{0xA1F8,0xA7, BYTE_LEN, 0 },
	{0xA1F9,0xD8, BYTE_LEN, 0 },
	{0xA1FA,0x04, BYTE_LEN, 0 },
	{0xA1FB,0x27, BYTE_LEN, 0 },
	{0xA1FC,0x2a, BYTE_LEN, 0 },
	{0xA1FD,0x69, BYTE_LEN, 0 },
	{0xA1FE,0x49, BYTE_LEN, 0 },
	{0xA1FF,0x4b, BYTE_LEN, 0 },
	{0xA200,0x62, BYTE_LEN, 0 },
	{0xA201,0xB2, BYTE_LEN, 0 },
	{0xA202,0x13, BYTE_LEN, 0 },
	{0xA203,0xA1, BYTE_LEN, 0 },
	{0xA204,0x34, BYTE_LEN, 0 },
	{0xA205,0x25, BYTE_LEN, 0 },
	{0xA206,0x2b, BYTE_LEN, 0 },
	{0xA207,0x4e, BYTE_LEN, 0 },
	{0xA208,0xF9, BYTE_LEN, 0 },
	{0xA209,0xCa, BYTE_LEN, 0 },
	{0xA20A,0x5b, BYTE_LEN, 0 },
	{0xA20B,0xF6, BYTE_LEN, 0 },
	{0xA20C,0x52, BYTE_LEN, 0 },
	{0xA20D,0x17, BYTE_LEN, 0 },
	{0xA20E,0xC0, BYTE_LEN, 0 },
	{0xA20F,0x90, BYTE_LEN, 0 },
	{0xA210,0xA5, BYTE_LEN, 0 },
	{0xA211,0x2d, BYTE_LEN, 0 },
	{0xA212,0x56, BYTE_LEN, 0 },
	{0xA213,0xD9, BYTE_LEN, 0 },
	{0xA214,0x0a, BYTE_LEN, 0 },
	{0xA215,0x53, BYTE_LEN, 0 },
	{0xA216,0xA6, BYTE_LEN, 0 },
	{0xA217,0xD2, BYTE_LEN, 0 },
	{0xA218,0x94, BYTE_LEN, 0 },
	{0xA219,0xAa, BYTE_LEN, 0 },
	{0xA21A,0x50, BYTE_LEN, 0 },
	{0xA21B,0x45, BYTE_LEN, 0 },
	{0xA21C,0x2c, BYTE_LEN, 0 },
	{0xA21D,0x5f, BYTE_LEN, 0 },
	{0xA21E,0x91, BYTE_LEN, 0 },
	{0xA21F,0x0b, BYTE_LEN, 0 },
	{0xA220,0x55, BYTE_LEN, 0 },
	{0xA221,0xD4, BYTE_LEN, 0 },
	{0xA222,0x52, BYTE_LEN, 0 },
	{0xA223,0x97, BYTE_LEN, 0 },
	{0xA224,0xC0, BYTE_LEN, 0 },
	{0xA225,0xF4, BYTE_LEN, 0 },
	{0xA226,0x25, BYTE_LEN, 0 },
	{0xA227,0x31, BYTE_LEN, 0 },
	{0xA228,0x79, BYTE_LEN, 0 },
	{0xA229,0x21, BYTE_LEN, 0 },
	{0xA22A,0x8c, BYTE_LEN, 0 },
	{0xA22B,0x5c, BYTE_LEN, 0 },
	{0xA22C,0xF8, BYTE_LEN, 0 },
	{0xA22D,0xC2, BYTE_LEN, 0 },
	{0xA22E,0x96, BYTE_LEN, 0 },
	{0xA22F,0xBc, BYTE_LEN, 0 },
	{0xA230,0xA4, BYTE_LEN, 0 },
	{0xA231,0x05, BYTE_LEN, 0 },
	{0xA232,0x2f, BYTE_LEN, 0 },
	{0xA233,0x68, BYTE_LEN, 0 },
	{0xA234,0xE9, BYTE_LEN, 0 },
	{0xA235,0x8b, BYTE_LEN, 0 },
	{0xA236,0x59, BYTE_LEN, 0 },
	{0xA237,0xFe, BYTE_LEN, 0 },
	{0xA238,0xB2, BYTE_LEN, 0 },
	{0xA239,0x15, BYTE_LEN, 0 },
	{0xA23A,0xBa, BYTE_LEN, 0 },
	{0xA23B,0x34, BYTE_LEN, 0 },
	{0xA23C,0xE5, BYTE_LEN, 0 },
	{0xA23D,0x2a, BYTE_LEN, 0 },
	{0xA23E,0x69, BYTE_LEN, 0 },
	{0xA23F,0xA1, BYTE_LEN, 0 },
	{0xA240,0x8b, BYTE_LEN, 0 },
	{0xA241,0x5a, BYTE_LEN, 0 },
	{0xA242,0xEa, BYTE_LEN, 0 },
	{0xA243,0x32, BYTE_LEN, 0 },
	{0xA244,0x16, BYTE_LEN, 0 },
	{0xA245,0xB6, BYTE_LEN, 0 },
	{0xA246,0x7c, BYTE_LEN, 0 },
	{0xA247,0x85, BYTE_LEN, 0 },
	{0xA248,0x2d, BYTE_LEN, 0 },
	{0xA249,0x5a, BYTE_LEN, 0 },
	{0xA24A,0x51, BYTE_LEN, 0 },
	{0xA24B,0x0b, BYTE_LEN, 0 },
	{0xA24C,0x57, BYTE_LEN, 0 },
	{0xA24D,0xE0, BYTE_LEN, 0 },
	{0xA24E,0x72, BYTE_LEN, 0 },
	{0xA24F,0x95, BYTE_LEN, 0 },
	{0xA250,0xB6, BYTE_LEN, 0 },
	{0xA251,0xFc, BYTE_LEN, 0 },
	{0xA252,0x84, BYTE_LEN, 0 },
	{0xA253,0x2a, BYTE_LEN, 0 },

	{0xA254,0x9c, BYTE_LEN, 0 },
	{0xA255,0x79, BYTE_LEN, 0 },
	{0xA256,0xCe, BYTE_LEN, 0 },
	{0xA257,0x75, BYTE_LEN, 0 },
	{0xA258,0x94, BYTE_LEN, 0 },
	{0xA259,0x43, BYTE_LEN, 0 },
	{0xA25A,0x9c, BYTE_LEN, 0 },
	{0xA25B,0xDf, BYTE_LEN, 0 },
	{0xA25C,0x24, BYTE_LEN, 0 },
	{0xA25D,0x07, BYTE_LEN, 0 },
	{0xA25E,0x39, BYTE_LEN, 0 },
	{0xA25F,0xA1, BYTE_LEN, 0 },
	{0xA260,0xF9, BYTE_LEN, 0 },
	{0xA261,0x4e, BYTE_LEN, 0 },
	{0xA262,0x7c, BYTE_LEN, 0 },
	{0xA263,0xD0, BYTE_LEN, 0 },
	{0xA264,0x93, BYTE_LEN, 0 },
	{0xA265,0x1d, BYTE_LEN, 0 },
	{0xA266,0xE7, BYTE_LEN, 0 },
	{0xA267,0x30, BYTE_LEN, 0 },
	{0xA268,0x87, BYTE_LEN, 0 },
	{0xA269,0x3a, BYTE_LEN, 0 },
	{0xA26A,0xDe, BYTE_LEN, 0 },
	{0xA26B,0xA9, BYTE_LEN, 0 },
	{0xA26C,0x8e, BYTE_LEN, 0 },
	{0xA26D,0x77, BYTE_LEN, 0 },
	{0xA26E,0xC2, BYTE_LEN, 0 },
	{0xA26F,0xC3, BYTE_LEN, 0 },
	{0xA270,0x9b, BYTE_LEN, 0 },
	{0xA271,0xCe, BYTE_LEN, 0 },
	{0xA272,0x34, BYTE_LEN, 0 },
	{0xA273,0xE6, BYTE_LEN, 0 },
	{0xA274,0x31, BYTE_LEN, 0 },
	{0xA275,0xA3, BYTE_LEN, 0 },
	{0xA276,0x39, BYTE_LEN, 0 },
	{0xA277,0xCe, BYTE_LEN, 0 },
	{0xA278,0x71, BYTE_LEN, 0 },
	{0xA279,0x98, BYTE_LEN, 0 },
	{0xA27A,0x63, BYTE_LEN, 0 },
	{0xA27B,0x9b, BYTE_LEN, 0 },
	{0xA27C,0xC0, BYTE_LEN, 0 },
	{0xA27D,0x68, BYTE_LEN, 0 },
	{0xA27E,0x25, BYTE_LEN, 0 },
	{0xA27F,0x29, BYTE_LEN, 0 },
	{0xA280,0x4d, BYTE_LEN, 0 },
	{0xA281,0x49, BYTE_LEN, 0 },
	{0xA282,0x0b, BYTE_LEN, 0 },
	{0xA283,0x66, BYTE_LEN, 0 },
	{0xA284,0x60, BYTE_LEN, 0 },
	{0xA285,0x33, BYTE_LEN, 0 },
	{0xA286,0x9b, BYTE_LEN, 0 },
	{0xA287,0xC7, BYTE_LEN, 0 },
	{0xA288,0x48, BYTE_LEN, 0 },
	{0xA289,0xE5, BYTE_LEN, 0 },
	{0xA28A,0x24, BYTE_LEN, 0 },
	{0xA28B,0x16, BYTE_LEN, 0 },
	{0xA28C,0xE1, BYTE_LEN, 0 },
	{0xA28D,0x48, BYTE_LEN, 0 },
	{0xA28E,0x4f, BYTE_LEN, 0 },
	{0xA28F,0xE0, BYTE_LEN, 0 },
	{0xA290,0x22, BYTE_LEN, 0 },
	{0xA291,0x99, BYTE_LEN, 0 },
	{0xA292,0xCe, BYTE_LEN, 0 },
	{0xA293,0xE4, BYTE_LEN, 0 },
	{0xA294,0x25, BYTE_LEN, 0 },
	{0xA295,0x27, BYTE_LEN, 0 },
	{0xA296,0x10, BYTE_LEN, 0 },
	{0xA297,0x01, BYTE_LEN, 0 },
	{0xA298,0x88, BYTE_LEN, 0 },
	{0xA299,0x41, BYTE_LEN, 0 },
	{0xA29A,0x4c, BYTE_LEN, 0 },
	{0xA29B,0xB2, BYTE_LEN, 0 },
	{0xA29C,0x95, BYTE_LEN, 0 },
	{0xA29D,0xBf, BYTE_LEN, 0 },
	{0xA29E,0x7c, BYTE_LEN, 0 },
	{0xA29F,0x26, BYTE_LEN, 0 },
	{0xA2A0,0x2f, BYTE_LEN, 0 },
	{0xA2A1,0x39, BYTE_LEN, 0 },
	{0xA2A2,0x71, BYTE_LEN, 0 },
	{0xA2A3,0xC8, BYTE_LEN, 0 },
	{0xA2A4,0x3f, BYTE_LEN, 0 },
	{0xA2A5,0x08, BYTE_LEN, 0 },
	{0xA2A6,0x42, BYTE_LEN, 0 },
	{0xA2A7,0x12, BYTE_LEN, 0 },
	{0xA2A8,0xAd, BYTE_LEN, 0 },
	{0xA2A9,0xF0, BYTE_LEN, 0 },
	{0xA2AA,0xC5, BYTE_LEN, 0 },
	{0xA2AB,0x36, BYTE_LEN, 0 },
	{0xA2AC,0x8f, BYTE_LEN, 0 },
	{0xA2AD,0x71, BYTE_LEN, 0 },
	{0xA2AE,0xCa, BYTE_LEN, 0 },
	{0xA2AF,0x48, BYTE_LEN, 0 },
	{0xA2B0,0x24, BYTE_LEN, 0 },
	{0xA2B1,0x72, BYTE_LEN, 0 },
	{0xA2B2,0x91, BYTE_LEN, 0 },
	{0xA2B3,0x9b, BYTE_LEN, 0 },
	{0xA2B4,0xB8, BYTE_LEN, 0 },
	{0xA2B5,0x45, BYTE_LEN, 0 },
	{0xA2B6,0x32, BYTE_LEN, 0 },
	{0xA2B7,0xD3, BYTE_LEN, 0 },
	{0xA2B8,0xB9, BYTE_LEN, 0 },
	{0xA2B9,0x4d, BYTE_LEN, 0 },
	{0xA2BA,0x5f, BYTE_LEN, 0 },
	{0xA2BB,0xA8, BYTE_LEN, 0 },
	{0xA2BC,0x12, BYTE_LEN, 0 },
	{0xA2BD,0x94, BYTE_LEN, 0 },
	{0xA2BE,0xA3, BYTE_LEN, 0 },
	{0xA2BF,0x98, BYTE_LEN, 0 },
	{0xA2C0,0x05, BYTE_LEN, 0 },
	{0xA2C1,0x33, BYTE_LEN, 0 },
	{0xA2C2,0xB2, BYTE_LEN, 0 },
	{0xA2C3,0x51, BYTE_LEN, 0 },
	{0xA2C4,0x8f, BYTE_LEN, 0 },
	{0xA2C5,0x79, BYTE_LEN, 0 },
	{0xA2C6,0x70, BYTE_LEN, 0 },
	{0xA2C7,0x63, BYTE_LEN, 0 },
	{0xA2C8,0x99, BYTE_LEN, 0 },
	{0xA2C9,0xC2, BYTE_LEN, 0 },
	{0xA2CA,0x28, BYTE_LEN, 0 },
	{0xA2CB,0x66, BYTE_LEN, 0 },
	{0xA2CC,0x34, BYTE_LEN, 0 },
	{0xA2CD,0xCd, BYTE_LEN, 0 },
	{0xA2CE,0x81, BYTE_LEN, 0 },
	{0xA2CF,0x0e, BYTE_LEN, 0 },
	{0xA2D0,0x7e, BYTE_LEN, 0 },
	{0xA2D1,0x04, BYTE_LEN, 0 },
	{0xA2D2,0xE4, BYTE_LEN, 0 },
	{0xA2D3,0x1e, BYTE_LEN, 0 },
	{0xA2D4,0xEf, BYTE_LEN, 0 },
	{0xA2D5,0x54, BYTE_LEN, 0 },
	{0xA2D6,0xE7, BYTE_LEN, 0 },
	{0xA2D7,0x3a, BYTE_LEN, 0 },
	{0xA2D8,0xDe, BYTE_LEN, 0 },
	{0xA2D9,0x61, BYTE_LEN, 0 },
	{0xA2DA,0x8f, BYTE_LEN, 0 },
	{0xA2DB,0x78, BYTE_LEN, 0 },
	{0xA2DC,0x6c, BYTE_LEN, 0 },
	{0xA2DD,0x53, BYTE_LEN, 0 },
	{0xA2DE,0x9e, BYTE_LEN, 0 },
	{0xA2DF,0xEf, BYTE_LEN, 0 },
	{0xA2E0,0x50, BYTE_LEN, 0 },
	{0xA2E1,0x47, BYTE_LEN, 0 },
	{0xA2E2,0x3a, BYTE_LEN, 0 },
	{0xA2E3,0xD0, BYTE_LEN, 0 },
	{0xA2E4,0xA1, BYTE_LEN, 0 },
	{0xA2E5,0x0e, BYTE_LEN, 0 },
	{0xA2E6,0x75, BYTE_LEN, 0 },
	{0xA2E7,0x68, BYTE_LEN, 0 },
	{0xA2E8,0x03, BYTE_LEN, 0 },
	{0xA2E9,0x80, BYTE_LEN, 0 },
	{0xA2EA,0x00, BYTE_LEN, 0 },
	{0xA2EB,0x00, BYTE_LEN, 0 },
	{0xA2EC,0x00, BYTE_LEN, 0 },
	{0xA2ED,0x00, BYTE_LEN, 0 },

	{0xA2EE,0xB7, BYTE_LEN, 0 },
	{0xA2EF,0x41, BYTE_LEN, 0 },
	{0xA2F0,0x0f, BYTE_LEN, 0 },
	{0xA2F1,0x7b, BYTE_LEN, 0 },
	{0xA2F2,0xBa, BYTE_LEN, 0 },
	{0xA2F3,0x23, BYTE_LEN, 0 },
	{0xA2F4,0x1d, BYTE_LEN, 0 },
	{0xA2F5,0xE5, BYTE_LEN, 0 },
	{0xA2F6,0x34, BYTE_LEN, 0 },
	{0xA2F7,0x27, BYTE_LEN, 0 },
	{0xA2F8,0x39, BYTE_LEN, 0 },
	{0xA2F9,0xA2, BYTE_LEN, 0 },
	{0xA2FA,0xC9, BYTE_LEN, 0 },
	{0xA2FB,0xCf, BYTE_LEN, 0 },
	{0xA2FC,0x81, BYTE_LEN, 0 },
	{0xA2FD,0xF4, BYTE_LEN, 0 },
	{0xA2FE,0x93, BYTE_LEN, 0 },
	{0xA2FF,0x9e, BYTE_LEN, 0 },
	{0xA300,0xEd, BYTE_LEN, 0 },
	{0xA301,0x54, BYTE_LEN, 0 },
	{0xA302,0x07, BYTE_LEN, 0 },
	{0xA303,0x3b, BYTE_LEN, 0 },
	{0xA304,0xDd, BYTE_LEN, 0 },
	{0xA305,0x91, BYTE_LEN, 0 },
	{0xA306,0x0e, BYTE_LEN, 0 },
	{0xA307,0x7d, BYTE_LEN, 0 },
	{0xA308,0xE6, BYTE_LEN, 0 },
	{0xA309,0xA3, BYTE_LEN, 0 },
	{0xA30A,0x1c, BYTE_LEN, 0 },
	{0xA30B,0xD5, BYTE_LEN, 0 },
	{0xA30C,0x5c, BYTE_LEN, 0 },
	{0xA30D,0xC6, BYTE_LEN, 0 },
	{0xA30E,0x32, BYTE_LEN, 0 },
	{0xA30F,0xA6, BYTE_LEN, 0 },
	{0xA310,0x31, BYTE_LEN, 0 },
	{0xA311,0x8e, BYTE_LEN, 0 },
	{0xA312,0x70, BYTE_LEN, 0 },
	{0xA313,0xC4, BYTE_LEN, 0 },
	{0xA314,0x83, BYTE_LEN, 0 },
	{0xA315,0x9c, BYTE_LEN, 0 },
	{0xA316,0xC7, BYTE_LEN, 0 },
	{0xA317,0x94, BYTE_LEN, 0 },
	{0xA318,0x05, BYTE_LEN, 0 },
	{0xA319,0x2a, BYTE_LEN, 0 },
	{0xA31A,0x52, BYTE_LEN, 0 },
	{0xA31B,0x69, BYTE_LEN, 0 },
	{0xA31C,0x4b, BYTE_LEN, 0 },
	{0xA31D,0x66, BYTE_LEN, 0 },
	{0xA31E,0x58, BYTE_LEN, 0 },
	{0xA31F,0xA3, BYTE_LEN, 0 },
	{0xA320,0x1c, BYTE_LEN, 0 },
	{0xA321,0xD1, BYTE_LEN, 0 },
	{0xA322,0x7c, BYTE_LEN, 0 },
	{0xA323,0xC5, BYTE_LEN, 0 },
	{0xA324,0x25, BYTE_LEN, 0 },
	{0xA325,0x1a, BYTE_LEN, 0 },
	{0xA326,0xF1, BYTE_LEN, 0 },
	{0xA327,0x08, BYTE_LEN, 0 },
	{0xA328,0x50, BYTE_LEN, 0 },
	{0xA329,0xE2, BYTE_LEN, 0 },
	{0xA32A,0xF2, BYTE_LEN, 0 },
	{0xA32B,0x98, BYTE_LEN, 0 },
	{0xA32C,0xDa, BYTE_LEN, 0 },
	{0xA32D,0x2c, BYTE_LEN, 0 },
	{0xA32E,0x86, BYTE_LEN, 0 },
	{0xA32F,0x28, BYTE_LEN, 0 },
	{0xA330,0x14, BYTE_LEN, 0 },
	{0xA331,0x01, BYTE_LEN, 0 },
	{0xA332,0x88, BYTE_LEN, 0 },
	{0xA333,0x41, BYTE_LEN, 0 },
	{0xA334,0x4e, BYTE_LEN, 0 },
	{0xA335,0xD2, BYTE_LEN, 0 },
	{0xA336,0x95, BYTE_LEN, 0 },
	{0xA337,0xBd, BYTE_LEN, 0 },
	{0xA338,0xD8, BYTE_LEN, 0 },
	{0xA339,0x86, BYTE_LEN, 0 },
	{0xA33A,0x31, BYTE_LEN, 0 },
	{0xA33B,0x43, BYTE_LEN, 0 },
	{0xA33C,0x91, BYTE_LEN, 0 },
	{0xA33D,0xC8, BYTE_LEN, 0 },
	{0xA33E,0x3f, BYTE_LEN, 0 },
	{0xA33F,0x08, BYTE_LEN, 0 },
	{0xA340,0x52, BYTE_LEN, 0 },
	{0xA341,0x12, BYTE_LEN, 0 },
	{0xA342,0xAe, BYTE_LEN, 0 },
	{0xA343,0xF0, BYTE_LEN, 0 },
	{0xA344,0xC5, BYTE_LEN, 0 },
	{0xA345,0x39, BYTE_LEN, 0 },
	{0xA346,0xA2, BYTE_LEN, 0 },
	{0xA347,0xD1, BYTE_LEN, 0 },
	{0xA348,0x4a, BYTE_LEN, 0 },
	{0xA349,0x4a, BYTE_LEN, 0 },
	{0xA34A,0x28, BYTE_LEN, 0 },
	{0xA34B,0x92, BYTE_LEN, 0 },
	{0xA34C,0x11, BYTE_LEN, 0 },
	{0xA34D,0x9d, BYTE_LEN, 0 },
	{0xA34E,0xC4, BYTE_LEN, 0 },
	{0xA34F,0x65, BYTE_LEN, 0 },
	{0xA350,0x32, BYTE_LEN, 0 },
	{0xA351,0xEb, BYTE_LEN, 0 },
	{0xA352,0x59, BYTE_LEN, 0 },
	{0xA353,0xCe, BYTE_LEN, 0 },
	{0xA354,0x62, BYTE_LEN, 0 },
	{0xA355,0xBc, BYTE_LEN, 0 },
	{0xA356,0x82, BYTE_LEN, 0 },
	{0xA357,0x14, BYTE_LEN, 0 },
	{0xA358,0xA7, BYTE_LEN, 0 },
	{0xA359,0xAc, BYTE_LEN, 0 },
	{0xA35A,0x65, BYTE_LEN, 0 },
	{0xA35B,0x33, BYTE_LEN, 0 },
	{0xA35C,0xB2, BYTE_LEN, 0 },
	{0xA35D,0x11, BYTE_LEN, 0 },
	{0xA35E,0xD0, BYTE_LEN, 0 },
	{0xA35F,0x7e, BYTE_LEN, 0 },
	{0xA360,0x90, BYTE_LEN, 0 },
	{0xA361,0x23, BYTE_LEN, 0 },
	{0xA362,0x9a, BYTE_LEN, 0 },
	{0xA363,0xC8, BYTE_LEN, 0 },
	{0xA364,0x4c, BYTE_LEN, 0 },
	{0xA365,0x26, BYTE_LEN, 0 },
	{0xA366,0x35, BYTE_LEN, 0 },
	{0xA367,0xCe, BYTE_LEN, 0 },
	{0xA368,0x71, BYTE_LEN, 0 },
	{0xA369,0xCe, BYTE_LEN, 0 },
	{0xA36A,0x84, BYTE_LEN, 0 },
	{0xA36B,0x2e, BYTE_LEN, 0 },
	{0xA36C,0xF4, BYTE_LEN, 0 },
	{0xA36D,0x1f, BYTE_LEN, 0 },
	{0xA36E,0xF6, BYTE_LEN, 0 },
	{0xA36F,0x98, BYTE_LEN, 0 },
	{0xA370,0x27, BYTE_LEN, 0 },
	{0xA371,0x3c, BYTE_LEN, 0 },
	{0xA372,0xE5, BYTE_LEN, 0 },
	{0xA373,0x69, BYTE_LEN, 0 },
	{0xA374,0x8f, BYTE_LEN, 0 },
	{0xA375,0x78, BYTE_LEN, 0 },
	{0xA376,0xA2, BYTE_LEN, 0 },
	{0xA377,0xC3, BYTE_LEN, 0 },
	{0xA378,0x1f, BYTE_LEN, 0 },
	{0xA379,0xF9, BYTE_LEN, 0 },
	{0xA37A,0x8c, BYTE_LEN, 0 },
	{0xA37B,0x07, BYTE_LEN, 0 },
	{0xA37C,0x3c, BYTE_LEN, 0 },
	{0xA37D,0xDa, BYTE_LEN, 0 },
	{0xA37E,0xE1, BYTE_LEN, 0 },
	{0xA37F,0xCe, BYTE_LEN, 0 },
	{0xA380,0x75, BYTE_LEN, 0 },
	{0xA381,0x6a, BYTE_LEN, 0 },
	{0xA382,0x53, BYTE_LEN, 0 },
	{0xA383,0x16, BYTE_LEN, 0 },
	{0xA384,0xC0, BYTE_LEN, 0 },
	{0xA385,0xEc, BYTE_LEN, 0 },
	{0xA386,0x65, BYTE_LEN, 0 },
	{0xA387,0x2e, BYTE_LEN, 0 },
	{0xA388,0x65, BYTE_LEN, 0 },
	{0xA389,0x01, BYTE_LEN, 0 },
	{0xA38A,0xCc, BYTE_LEN, 0 },
	{0xA38B,0x5e, BYTE_LEN, 0 },
	{0xA38C,0xE6, BYTE_LEN, 0 },
	{0xA38D,0x02, BYTE_LEN, 0 },
	{0xA38E,0x17, BYTE_LEN, 0 },
	{0xA38F,0xB4, BYTE_LEN, 0 },
	{0xA390,0xAc, BYTE_LEN, 0 },
	{0xA391,0xC5, BYTE_LEN, 0 },
	{0xA392,0x2d, BYTE_LEN, 0 },
	{0xA393,0x55, BYTE_LEN, 0 },
	{0xA394,0x49, BYTE_LEN, 0 },
	{0xA395,0xCc, BYTE_LEN, 0 },
	{0xA396,0x63, BYTE_LEN, 0 },
	{0xA397,0x0e, BYTE_LEN, 0 },
	{0xA398,0x03, BYTE_LEN, 0 },
	{0xA399,0x98, BYTE_LEN, 0 },
	{0xA39A,0xBd, BYTE_LEN, 0 },
	{0xA39B,0xDc, BYTE_LEN, 0 },
	{0xA39C,0x05, BYTE_LEN, 0 },
	{0xA39D,0x2f, BYTE_LEN, 0 },
	{0xA39E,0x7c, BYTE_LEN, 0 },
	{0xA39F,0x99, BYTE_LEN, 0 },
	{0xA3A0,0x0b, BYTE_LEN, 0 },
	{0xA3A1,0x61, BYTE_LEN, 0 },
	{0xA3A2,0x0c, BYTE_LEN, 0 },
	{0xA3A3,0xF3, BYTE_LEN, 0 },
	{0xA3A4,0x16, BYTE_LEN, 0 },
	{0xA3A5,0xB2, BYTE_LEN, 0 },
	{0xA3A6,0x70, BYTE_LEN, 0 },
	{0xA3A7,0x45, BYTE_LEN, 0 },
	{0xA3A8,0x2b, BYTE_LEN, 0 },
	{0xA3A9,0x65, BYTE_LEN, 0 },
	{0xA3AA,0x91, BYTE_LEN, 0 },
	{0xA3AB,0x0b, BYTE_LEN, 0 },
	{0xA3AC,0x5a, BYTE_LEN, 0 },
	{0xA3AD,0xF8, BYTE_LEN, 0 },
	{0xA3AE,0x32, BYTE_LEN, 0 },
	{0xA3AF,0x17, BYTE_LEN, 0 },
	{0xA3B0,0xAb, BYTE_LEN, 0 },
	{0xA3B1,0x14, BYTE_LEN, 0 },
	{0xA3B2,0x05, BYTE_LEN, 0 },
	{0xA3B3,0x27, BYTE_LEN, 0 },
	{0xA3B4,0x38, BYTE_LEN, 0 },
	{0xA3B5,0x29, BYTE_LEN, 0 },
	{0xA3B6,0x0a, BYTE_LEN, 0 },
	{0xA3B7,0x56, BYTE_LEN, 0 },
	{0xA3B8,0xB6, BYTE_LEN, 0 },
	{0xA3B9,0x12, BYTE_LEN, 0 },
	{0xA3BA,0x97, BYTE_LEN, 0 },
	{0xA3BB,0xB0, BYTE_LEN, 0 },
	{0xA3BC,0xFc, BYTE_LEN, 0 },
	{0xA3BD,0x24, BYTE_LEN, 0 },
	{0xA3BE,0x24, BYTE_LEN, 0 },
	{0xA3BF,0x14, BYTE_LEN, 0 },
	{0xA3C0,0xA9, BYTE_LEN, 0 },
	{0xA3C1,0x48, BYTE_LEN, 0 },
	{0xA3C2,0x4a, BYTE_LEN, 0 },
	{0xA3C3,0x86, BYTE_LEN, 0 },
	{0xA3C4,0xB2, BYTE_LEN, 0 },
	{0xA3C5,0x14, BYTE_LEN, 0 },
	{0xA3C6,0xB2, BYTE_LEN, 0 },
	{0xA3C7,0x54, BYTE_LEN, 0 },
	{0xA3C8,0xE5, BYTE_LEN, 0 },
	{0xA3C9,0x25, BYTE_LEN, 0 },
	{0xA3CA,0x0e, BYTE_LEN, 0 },
	{0xA3CB,0x09, BYTE_LEN, 0 },
	{0xA3CC,0xC8, BYTE_LEN, 0 },
	{0xA3CD,0x40, BYTE_LEN, 0 },
	{0xA3CE,0x30, BYTE_LEN, 0 },
	{0xA3CF,0x72, BYTE_LEN, 0 },
	{0xA3D0,0x13, BYTE_LEN, 0 },
	{0xA3D1,0xA0, BYTE_LEN, 0 },
	{0xA3D2,0x94, BYTE_LEN, 0 },
	{0xA3D3,0xA5, BYTE_LEN, 0 },
	{0xA3D4,0x2a, BYTE_LEN, 0 },
	{0xA3D5,0x2e, BYTE_LEN, 0 },
	{0xA3D6,0x59, BYTE_LEN, 0 },
	{0xA3D7,0x88, BYTE_LEN, 0 },
	{0xA3D8,0x3f, BYTE_LEN, 0 },
	{0xA3D9,0x04, BYTE_LEN, 0 },
	{0xA3DA,0x62, BYTE_LEN, 0 },
	{0xA3DB,0x91, BYTE_LEN, 0 },
	{0xA3DC,0x9a, BYTE_LEN, 0 },
	{0xA3DD,0xFc, BYTE_LEN, 0 },
	{0xA3DE,0xA4, BYTE_LEN, 0 },
	{0xA3DF,0x2e, BYTE_LEN, 0 },
	{0xA3E0,0x63, BYTE_LEN, 0 },
	{0xA3E1,0xE9, BYTE_LEN, 0 },
	{0xA3E2,0xC9, BYTE_LEN, 0 },
	{0xA3E3,0x46, BYTE_LEN, 0 },
	{0xA3E4,0x18, BYTE_LEN, 0 },
	{0xA3E5,0x02, BYTE_LEN, 0 },
	{0xA3E6,0x91, BYTE_LEN, 0 },
	{0xA3E7,0x91, BYTE_LEN, 0 },
	{0xA3E8,0x00, BYTE_LEN, 0 },
	{0xA3E9,0x25, BYTE_LEN, 0 },
	{0xA3EA,0x29, BYTE_LEN, 0 },
	{0xA3EB,0x81, BYTE_LEN, 0 },
	{0xA3EC,0xA9, BYTE_LEN, 0 },
	{0xA3ED,0x8b, BYTE_LEN, 0 },
	{0xA3EE,0x55, BYTE_LEN, 0 },
	{0xA3EF,0x7a, BYTE_LEN, 0 },
	{0xA3F0,0xB2, BYTE_LEN, 0 },
	{0xA3F1,0x12, BYTE_LEN, 0 },
	{0xA3F2,0x97, BYTE_LEN, 0 },
	{0xA3F3,0xF8, BYTE_LEN, 0 },
	{0xA3F4,0x84, BYTE_LEN, 0 },
	{0xA3F5,0x2a, BYTE_LEN, 0 },
	{0xA3F6,0x58, BYTE_LEN, 0 },
	{0xA3F7,0x69, BYTE_LEN, 0 },
	{0xA3F8,0xCc, BYTE_LEN, 0 },
	{0xA3F9,0x63, BYTE_LEN, 0 },
	{0xA3FA,0xEa, BYTE_LEN, 0 },
	{0xA3FB,0x02, BYTE_LEN, 0 },
	{0xA3FC,0x96, BYTE_LEN, 0 },
	{0xA3FD,0xA9, BYTE_LEN, 0 },
	{0xA3FE,0x4c, BYTE_LEN, 0 },
	{0xA3FF,0x85, BYTE_LEN, 0 },
	{0xA400,0x2b, BYTE_LEN, 0 },
	{0xA401,0x68, BYTE_LEN, 0 },
	{0xA402,0x01, BYTE_LEN, 0 },
	{0xA403,0xCb, BYTE_LEN, 0 },
	{0xA404,0x66, BYTE_LEN, 0 },
	{0xA405,0x38, BYTE_LEN, 0 },
	{0xA406,0x03, BYTE_LEN, 0 },
	{0xA407,0x19, BYTE_LEN, 0 },
	{0xA408,0xC2, BYTE_LEN, 0 },
	{0xA409,0xF0, BYTE_LEN, 0 },
	{0xA40A,0x85, BYTE_LEN, 0 },
	{0xA40B,0x2e, BYTE_LEN, 0 },
	{0xA40C,0x73, BYTE_LEN, 0 },
	{0xA40D,0x99, BYTE_LEN, 0 },
	{0xA40E,0x8b, BYTE_LEN, 0 },
	{0xA40F,0x5a, BYTE_LEN, 0 },
	{0xA410,0xE6, BYTE_LEN, 0 },
	{0xA411,0xB2, BYTE_LEN, 0 },
	{0xA412,0x18, BYTE_LEN, 0 },
	{0xA413,0xC2, BYTE_LEN, 0 },
	{0xA414,0xDc, BYTE_LEN, 0 },
	{0xA415,0xE5, BYTE_LEN, 0 },
	{0xA416,0x2d, BYTE_LEN, 0 },
	{0xA417,0x66, BYTE_LEN, 0 },
	{0xA418,0x49, BYTE_LEN, 0 },
	{0xA419,0x0b, BYTE_LEN, 0 },
	{0xA41A,0x59, BYTE_LEN, 0 },
	{0xA41B,0x9a, BYTE_LEN, 0 },
	{0xA41C,0x02, BYTE_LEN, 0 },
	{0xA41D,0x00, BYTE_LEN, 0 },
	{0xA41E,0x00, BYTE_LEN, 0 },
	{0xA41F,0x00, BYTE_LEN, 0 },
	{0xA420,0x00, BYTE_LEN, 0 },
	{0xA421,0x0a, BYTE_LEN, 0 },

	{0x0068,0x5F, BYTE_LEN, 0 },
};

/*SHD_MIN*/
struct isx006_i2c_reg_conf isx006_SHD_MIN_settings[] = {
	{ 0x0068,0x50, BYTE_LEN, 0 },

	{ 0x9000,0x8282, WORD_LEN, 0 },//CXC_valid_code
	{ 0x9002,0x01, BYTE_LEN, 0 },
	{ 0x9003,0x0c, BYTE_LEN, 0 },
	{ 0x9004,0x04, BYTE_LEN, 0 },
	{ 0x9005,0x30, BYTE_LEN, 0 },
	{ 0x9006,0xF0, BYTE_LEN, 0 },
	{ 0x9007,0xFf, BYTE_LEN, 0 },
	{ 0x9008,0xC0, BYTE_LEN, 0 },
	{ 0x9009,0x7f, BYTE_LEN, 0 },
	{ 0x900A,0x04, BYTE_LEN, 0 },
	{ 0x900B,0x01, BYTE_LEN, 0 },
	{ 0x900C,0x12, BYTE_LEN, 0 },
	{ 0x900D,0x08, BYTE_LEN, 0 },
	{ 0x900E,0x50, BYTE_LEN, 0 },
	{ 0x900F,0x20, BYTE_LEN, 0 },
	{ 0x9010,0x20, BYTE_LEN, 0 },
	{ 0x9011,0x81, BYTE_LEN, 0 },
	{ 0x9012,0x00, BYTE_LEN, 0 },
	{ 0x9013,0x04, BYTE_LEN, 0 },
	{ 0x9014,0x02, BYTE_LEN, 0 },
	{ 0x9015,0x10, BYTE_LEN, 0 },
	{ 0x9016,0x04, BYTE_LEN, 0 },
	{ 0x9017,0x30, BYTE_LEN, 0 },
	{ 0x9018,0x10, BYTE_LEN, 0 },
	{ 0x9019,0xC0, BYTE_LEN, 0 },
	{ 0x901A,0xC0, BYTE_LEN, 0 },
	{ 0x901B,0xFf, BYTE_LEN, 0 },
	{ 0x901C,0x03, BYTE_LEN, 0 },
	{ 0x901D,0xFf, BYTE_LEN, 0 },
	{ 0x901E,0x11, BYTE_LEN, 0 },
	{ 0x901F,0x04, BYTE_LEN, 0 },
	{ 0x9020,0x48, BYTE_LEN, 0 },
	{ 0x9021,0x20, BYTE_LEN, 0 },
	{ 0x9022,0x40, BYTE_LEN, 0 },
	{ 0x9023,0x81, BYTE_LEN, 0 },
	{ 0x9024,0x80, BYTE_LEN, 0 },
	{ 0x9025,0x04, BYTE_LEN, 0 },
	{ 0x9026,0x02, BYTE_LEN, 0 },
	{ 0x9027,0x10, BYTE_LEN, 0 },
	{ 0x9028,0x08, BYTE_LEN, 0 },
	{ 0x9029,0x40, BYTE_LEN, 0 },
	{ 0x902A,0x00, BYTE_LEN, 0 },
	{ 0x902B,0xC0, BYTE_LEN, 0 },
	{ 0x902C,0x00, BYTE_LEN, 0 },
	{ 0x902D,0x00, BYTE_LEN, 0 },
	{ 0x902E,0x03, BYTE_LEN, 0 },
	{ 0x902F,0x01, BYTE_LEN, 0 },
	{ 0x9030,0x0e, BYTE_LEN, 0 },
	{ 0x9031,0x00, BYTE_LEN, 0 },
	{ 0x9032,0x30, BYTE_LEN, 0 },
	{ 0x9033,0x00, BYTE_LEN, 0 },
	{ 0x9034,0xE0, BYTE_LEN, 0 },
	{ 0x9035,0xC0, BYTE_LEN, 0 },
	{ 0x9036,0x80, BYTE_LEN, 0 },
	{ 0x9037,0x03, BYTE_LEN, 0 },
	{ 0x9038,0x02, BYTE_LEN, 0 },
	{ 0x9039,0x14, BYTE_LEN, 0 },
	{ 0x903A,0x0c, BYTE_LEN, 0 },
	{ 0x903B,0x48, BYTE_LEN, 0 },
	{ 0x903C,0x30, BYTE_LEN, 0 },
	{ 0x903D,0x20, BYTE_LEN, 0 },
	{ 0x903E,0x01, BYTE_LEN, 0 },
	{ 0x903F,0x00, BYTE_LEN, 0 },
	{ 0x9040,0x03, BYTE_LEN, 0 },
	{ 0x9041,0x00, BYTE_LEN, 0 },
	{ 0x9042,0x0c, BYTE_LEN, 0 },
	{ 0x9043,0x04, BYTE_LEN, 0 },
	{ 0x9044,0x30, BYTE_LEN, 0 },
	{ 0x9045,0x10, BYTE_LEN, 0 },
	{ 0x9046,0xA0, BYTE_LEN, 0 },
	{ 0x9047,0x00, BYTE_LEN, 0 },
	{ 0x9048,0x80, BYTE_LEN, 0 },
	{ 0x9049,0x01, BYTE_LEN, 0 },
	{ 0x904A,0x00, BYTE_LEN, 0 },
	{ 0x904B,0x0c, BYTE_LEN, 0 },
	{ 0x904C,0x04, BYTE_LEN, 0 },
	{ 0x904D,0x30, BYTE_LEN, 0 },
	{ 0x904E,0x30, BYTE_LEN, 0 },
	{ 0x904F,0xE0, BYTE_LEN, 0 },
	{ 0x9050,0xC0, BYTE_LEN, 0 },
	{ 0x9051,0x80, BYTE_LEN, 0 },
	{ 0x9052,0x03, BYTE_LEN, 0 },
	{ 0x9053,0x04, BYTE_LEN, 0 },
	{ 0x9054,0x0a, BYTE_LEN, 0 },
	{ 0x9055,0x10, BYTE_LEN, 0 },
	{ 0x9056,0x28, BYTE_LEN, 0 },
	{ 0x9057,0x20, BYTE_LEN, 0 },
	{ 0x9058,0x60, BYTE_LEN, 0 },
	{ 0x9059,0xC0, BYTE_LEN, 0 },
	{ 0x905A,0x00, BYTE_LEN, 0 },
	{ 0x905B,0x01, BYTE_LEN, 0 },
	{ 0x905C,0x03, BYTE_LEN, 0 },
	{ 0x905D,0x02, BYTE_LEN, 0 },
	{ 0x905E,0x00, BYTE_LEN, 0 },
	{ 0x905F,0x18, BYTE_LEN, 0 },
	{ 0x9060,0x10, BYTE_LEN, 0 },
	{ 0x9061,0x60, BYTE_LEN, 0 },
	{ 0x9062,0x00, BYTE_LEN, 0 },
	{ 0x9063,0x80, BYTE_LEN, 0 },
	{ 0x9064,0x02, BYTE_LEN, 0 },
	{ 0x9065,0x00, BYTE_LEN, 0 },
	{ 0x9066,0x0a, BYTE_LEN, 0 },
	{ 0x9067,0x04, BYTE_LEN, 0 },
	{ 0x9068,0x20, BYTE_LEN, 0 },
	{ 0x9069,0x10, BYTE_LEN, 0 },
	{ 0x906A,0x80, BYTE_LEN, 0 },
	{ 0x906B,0x80, BYTE_LEN, 0 },
	{ 0x906C,0x80, BYTE_LEN, 0 },
	{ 0x906D,0x00, BYTE_LEN, 0 },
	{ 0x906E,0x03, BYTE_LEN, 0 },
	{ 0x906F,0x00, BYTE_LEN, 0 },
	{ 0x9070,0x04, BYTE_LEN, 0 },
	{ 0x9071,0x00, BYTE_LEN, 0 },
	{ 0x9072,0x00, BYTE_LEN, 0 },
	{ 0x9073,0x00, BYTE_LEN, 0 },
	{ 0x9074,0x40, BYTE_LEN, 0 },
	{ 0x9075,0x80, BYTE_LEN, 0 },
	{ 0x9076,0x01, BYTE_LEN, 0 },
	{ 0x9077,0x01, BYTE_LEN, 0 },
	{ 0x9078,0x0a, BYTE_LEN, 0 },
	{ 0x9079,0x04, BYTE_LEN, 0 },
	{ 0x907A,0x28, BYTE_LEN, 0 },
	{ 0x907B,0x30, BYTE_LEN, 0 },
	{ 0x907C,0x40, BYTE_LEN, 0 },
	{ 0x907D,0xC0, BYTE_LEN, 0 },
	{ 0x907E,0x00, BYTE_LEN, 0 },
	{ 0x907F,0x01, BYTE_LEN, 0 },
	{ 0x9080,0x03, BYTE_LEN, 0 },
	{ 0x9081,0x00, BYTE_LEN, 0 },
	{ 0x9082,0x08, BYTE_LEN, 0 },
	{ 0x9083,0xF8, BYTE_LEN, 0 },
	{ 0x9084,0x3f, BYTE_LEN, 0 },
	{ 0x9085,0xC0, BYTE_LEN, 0 },
	{ 0x9086,0xBf, BYTE_LEN, 0 },
	{ 0x9087,0x00, BYTE_LEN, 0 },
	{ 0x9088,0x00, BYTE_LEN, 0 },
	{ 0x9089,0x01, BYTE_LEN, 0 },
	{ 0x908A,0x02, BYTE_LEN, 0 },
	{ 0x908B,0x10, BYTE_LEN, 0 },
	{ 0x908C,0x20, BYTE_LEN, 0 },
	{ 0x908D,0x40, BYTE_LEN, 0 },
	{ 0x908E,0x80, BYTE_LEN, 0 },
	{ 0x908F,0x80, BYTE_LEN, 0 },
	{ 0x9090,0x80, BYTE_LEN, 0 },
	{ 0x9091,0x01, BYTE_LEN, 0 },
	{ 0x9092,0x02, BYTE_LEN, 0 },
	{ 0x9093,0x06, BYTE_LEN, 0 },
	{ 0x9094,0x08, BYTE_LEN, 0 },
	{ 0x9095,0x00, BYTE_LEN, 0 },
	{ 0x9096,0x20, BYTE_LEN, 0 },
	{ 0x9097,0xE0, BYTE_LEN, 0 },
	{ 0x9098,0x3f, BYTE_LEN, 0 },
	{ 0x9099,0x81, BYTE_LEN, 0 },
	{ 0x909A,0xFf, BYTE_LEN, 0 },
	{ 0x909B,0x03, BYTE_LEN, 0 },
	{ 0x909C,0x00, BYTE_LEN, 0 },
	{ 0x909D,0x04, BYTE_LEN, 0 },
	{ 0x909E,0x08, BYTE_LEN, 0 },
	{ 0x909F,0x30, BYTE_LEN, 0 },
	{ 0x90A0,0x80, BYTE_LEN, 0 },
	{ 0x90A1,0xC0, BYTE_LEN, 0 },
	{ 0x90A2,0x00, BYTE_LEN, 0 },
	{ 0x90A3,0x02, BYTE_LEN, 0 },
	{ 0x90A4,0x03, BYTE_LEN, 0 },
	{ 0x90A5,0x04, BYTE_LEN, 0 },
	{ 0x90A6,0x0c, BYTE_LEN, 0 },
	{ 0x90A7,0x10, BYTE_LEN, 0 },
	{ 0x90A8,0x40, BYTE_LEN, 0 },
	{ 0x90A9,0x40, BYTE_LEN, 0 },
	{ 0x90AA,0x40, BYTE_LEN, 0 },
	{ 0x90AB,0x01, BYTE_LEN, 0 },
	{ 0x90AC,0x00, BYTE_LEN, 0 },
	{ 0x90AD,0x05, BYTE_LEN, 0 },
	{ 0x90AE,0x02, BYTE_LEN, 0 },
	{ 0x90AF,0x04, BYTE_LEN, 0 },
	{ 0x90B0,0x08, BYTE_LEN, 0 },
	{ 0x90B1,0x30, BYTE_LEN, 0 },
	{ 0x90B2,0x40, BYTE_LEN, 0 },
	{ 0x90B3,0x00, BYTE_LEN, 0 },
	{ 0x90B4,0x01, BYTE_LEN, 0 },
	{ 0x90B5,0x03, BYTE_LEN, 0 },
	{ 0x90B6,0x04, BYTE_LEN, 0 },
	{ 0x90B7,0x0c, BYTE_LEN, 0 },
	{ 0x90B8,0x08, BYTE_LEN, 0 },
	{ 0x90B9,0x28, BYTE_LEN, 0 },
	{ 0x90BA,0x20, BYTE_LEN, 0 },
	{ 0x90BB,0xA0, BYTE_LEN, 0 },
	{ 0x90BC,0x00, BYTE_LEN, 0 },
	{ 0x90BD,0x01, BYTE_LEN, 0 },
	{ 0x90BE,0x02, BYTE_LEN, 0 },
	{ 0x90BF,0x02, BYTE_LEN, 0 },
	{ 0x90C0,0x0a, BYTE_LEN, 0 },
	{ 0x90C1,0x10, BYTE_LEN, 0 },
	{ 0x90C2,0x20, BYTE_LEN, 0 },
	{ 0x90C3,0x40, BYTE_LEN, 0 },
	{ 0x90C4,0x60, BYTE_LEN, 0 },
	{ 0x90C5,0x00, BYTE_LEN, 0 },
	{ 0x90C6,0x01, BYTE_LEN, 0 },
	{ 0x90C7,0x02, BYTE_LEN, 0 },
	{ 0x90C8,0x04, BYTE_LEN, 0 },
	{ 0x90C9,0x0a, BYTE_LEN, 0 },
	{ 0x90CA,0x10, BYTE_LEN, 0 },
	{ 0x90CB,0x28, BYTE_LEN, 0 },
	{ 0x90CC,0x40, BYTE_LEN, 0 },
	{ 0x90CD,0x80, BYTE_LEN, 0 },
	{ 0x90CE,0x00, BYTE_LEN, 0 },
	{ 0x90CF,0x01, BYTE_LEN, 0 },
	{ 0x90D0,0x02, BYTE_LEN, 0 },
	{ 0x90D1,0x03, BYTE_LEN, 0 },
	{ 0x90D2,0x0e, BYTE_LEN, 0 },
	{ 0x90D3,0x0c, BYTE_LEN, 0 },
	{ 0x90D4,0x30, BYTE_LEN, 0 },
	{ 0x90D5,0x50, BYTE_LEN, 0 },
	{ 0x90D6,0xE0, BYTE_LEN, 0 },
	{ 0x90D7,0x40, BYTE_LEN, 0 },
	{ 0x90D8,0x01, BYTE_LEN, 0 },
	{ 0x90D9,0x03, BYTE_LEN, 0 },
	{ 0x90DA,0x04, BYTE_LEN, 0 },
	{ 0x90DB,0x0a, BYTE_LEN, 0 },
	{ 0x90DC,0x10, BYTE_LEN, 0 },
	{ 0x90DD,0x30, BYTE_LEN, 0 },
	{ 0x90DE,0x40, BYTE_LEN, 0 },
	{ 0x90DF,0xC0, BYTE_LEN, 0 },
	{ 0x90E0,0x00, BYTE_LEN, 0 },
	{ 0x90E1,0x01, BYTE_LEN, 0 },
	{ 0x90E2,0x02, BYTE_LEN, 0 },
	{ 0x90E3,0x04, BYTE_LEN, 0 },
	{ 0x90E4,0x08, BYTE_LEN, 0 },
	{ 0x90E5,0x0c, BYTE_LEN, 0 },
	{ 0x90E6,0x38, BYTE_LEN, 0 },
	{ 0x90E7,0x30, BYTE_LEN, 0 },
	{ 0x90E8,0xC0, BYTE_LEN, 0 },
	{ 0x90E9,0x40, BYTE_LEN, 0 },
	{ 0x90EA,0x81, BYTE_LEN, 0 },
	{ 0x90EB,0x03, BYTE_LEN, 0 },
	{ 0x90EC,0x05, BYTE_LEN, 0 },
	{ 0x90ED,0x0c, BYTE_LEN, 0 },
	{ 0x90EE,0x10, BYTE_LEN, 0 },
	{ 0x90EF,0x28, BYTE_LEN, 0 },
	{ 0x90F0,0x40, BYTE_LEN, 0 },
	{ 0x90F1,0xC0, BYTE_LEN, 0 },
	{ 0x90F2,0x00, BYTE_LEN, 0 },
	{ 0x90F3,0x01, BYTE_LEN, 0 },
	{ 0x90F4,0x03, BYTE_LEN, 0 },
	{ 0x90F5,0x02, BYTE_LEN, 0 },
	{ 0x90F6,0xDe, BYTE_LEN, 0 },
	{ 0x90F7,0x0b, BYTE_LEN, 0 },
	{ 0x90F8,0x78, BYTE_LEN, 0 },
	{ 0x90F9,0x3f, BYTE_LEN, 0 },
	{ 0x90FA,0x80, BYTE_LEN, 0 },
	{ 0x90FB,0x3e, BYTE_LEN, 0 },
	{ 0x90FC,0x80, BYTE_LEN, 0 },
	{ 0x90FD,0xF9, BYTE_LEN, 0 },
	{ 0x90FE,0x02, BYTE_LEN, 0 },
	{ 0x90FF,0xE8, BYTE_LEN, 0 },
	{ 0x9100,0x07, BYTE_LEN, 0 },
	{ 0x9101,0x98, BYTE_LEN, 0 },
	{ 0x9102,0x1f, BYTE_LEN, 0 },
	{ 0x9103,0xE0, BYTE_LEN, 0 },
	{ 0x9104,0xFe, BYTE_LEN, 0 },
	{ 0x9105,0xFf, BYTE_LEN, 0 },
	{ 0x9106,0xFa, BYTE_LEN, 0 },
	{ 0x9107,0xFf, BYTE_LEN, 0 },
	{ 0x9108,0xEb, BYTE_LEN, 0 },
	{ 0x9109,0x0b, BYTE_LEN, 0 },
	{ 0x910A,0x78, BYTE_LEN, 0 },
	{ 0x910B,0x2f, BYTE_LEN, 0 },
	{ 0x910C,0xE0, BYTE_LEN, 0 },
	{ 0x910D,0xFd, BYTE_LEN, 0 },
	{ 0x910E,0x00, BYTE_LEN, 0 },
	{ 0x910F,0xFa, BYTE_LEN, 0 },
	{ 0x9110,0x00, BYTE_LEN, 0 },
	{ 0x9111,0xE6, BYTE_LEN, 0 },
	{ 0x9112,0x0b, BYTE_LEN, 0 },
	{ 0x9113,0xA0, BYTE_LEN, 0 },
	{ 0x9114,0x1f, BYTE_LEN, 0 },
	{ 0x9115,0x60, BYTE_LEN, 0 },
	{ 0x9116,0x7e, BYTE_LEN, 0 },
	{ 0x9117,0x80, BYTE_LEN, 0 },
	{ 0x9118,0xFb, BYTE_LEN, 0 },
	{ 0x9119,0xFf, BYTE_LEN, 0 },
	{ 0x911A,0xEb, BYTE_LEN, 0 },
	{ 0x911B,0xFf, BYTE_LEN, 0 },
	{ 0x911C,0xAf, BYTE_LEN, 0 },
	{ 0x911D,0x5f, BYTE_LEN, 0 },
	{ 0x911E,0x60, BYTE_LEN, 0 },
	{ 0x911F,0x7e, BYTE_LEN, 0 },
	{ 0x9120,0x81, BYTE_LEN, 0 },
	{ 0x9121,0xF9, BYTE_LEN, 0 },
	{ 0x9122,0x02, BYTE_LEN, 0 },
	{ 0x9123,0xE6, BYTE_LEN, 0 },
	{ 0x9124,0x03, BYTE_LEN, 0 },
	{ 0x9125,0x98, BYTE_LEN, 0 },
	{ 0x9126,0x0f, BYTE_LEN, 0 },
	{ 0x9127,0x20, BYTE_LEN, 0 },
	{ 0x9128,0x7e, BYTE_LEN, 0 },
	{ 0x9129,0x80, BYTE_LEN, 0 },
	{ 0x912A,0xFb, BYTE_LEN, 0 },
	{ 0x912B,0x00, BYTE_LEN, 0 },
	{ 0x912C,0xE8, BYTE_LEN, 0 },
	{ 0x912D,0x07, BYTE_LEN, 0 },
	{ 0x912E,0xB0, BYTE_LEN, 0 },
	{ 0x912F,0x1f, BYTE_LEN, 0 },
	{ 0x9130,0xC0, BYTE_LEN, 0 },
	{ 0x9131,0xBe, BYTE_LEN, 0 },
	{ 0x9132,0x80, BYTE_LEN, 0 },
	{ 0x9133,0xFb, BYTE_LEN, 0 },
	{ 0x9134,0x02, BYTE_LEN, 0 },
	{ 0x9135,0xEe, BYTE_LEN, 0 },
	{ 0x9136,0x0f, BYTE_LEN, 0 },
	{ 0x9137,0xC0, BYTE_LEN, 0 },
	{ 0x9138,0x0f, BYTE_LEN, 0 },
	{ 0x9139,0x80, BYTE_LEN, 0 },
	{ 0x913A,0xFe, BYTE_LEN, 0 },
	{ 0x913B,0xFf, BYTE_LEN, 0 },
	{ 0x913C,0xFb, BYTE_LEN, 0 },
	{ 0x913D,0xFf, BYTE_LEN, 0 },
	{ 0x913E,0xE7, BYTE_LEN, 0 },
	{ 0x913F,0xFf, BYTE_LEN, 0 },
	{ 0x9140,0xAf, BYTE_LEN, 0 },
	{ 0x9141,0x1f, BYTE_LEN, 0 },
	{ 0x9142,0xC0, BYTE_LEN, 0 },
	{ 0x9143,0x7e, BYTE_LEN, 0 },
	{ 0x9144,0x00, BYTE_LEN, 0 },
	{ 0x9145,0xFb, BYTE_LEN, 0 },
	{ 0x9146,0x04, BYTE_LEN, 0 },
	{ 0x9147,0xF2, BYTE_LEN, 0 },
	{ 0x9148,0x13, BYTE_LEN, 0 },
	{ 0x9149,0xC8, BYTE_LEN, 0 },
	{ 0x914A,0x0f, BYTE_LEN, 0 },
	{ 0x914B,0xC0, BYTE_LEN, 0 },
	{ 0x914C,0xFe, BYTE_LEN, 0 },
	{ 0x914D,0xFf, BYTE_LEN, 0 },
	{ 0x914E,0xFb, BYTE_LEN, 0 },
	{ 0x914F,0xFe, BYTE_LEN, 0 },
	{ 0x9150,0xF1, BYTE_LEN, 0 },
	{ 0x9151,0xFb, BYTE_LEN, 0 },
	{ 0x9152,0xC7, BYTE_LEN, 0 },
	{ 0x9153,0xFf, BYTE_LEN, 0 },
	{ 0x9154,0xFf, BYTE_LEN, 0 },
	{ 0x9155,0x3e, BYTE_LEN, 0 },
	{ 0x9156,0x00, BYTE_LEN, 0 },
	{ 0x9157,0xFc, BYTE_LEN, 0 },
	{ 0x9158,0x00, BYTE_LEN, 0 },
	{ 0x9159,0xF0, BYTE_LEN, 0 },
	{ 0x915A,0x13, BYTE_LEN, 0 },
	{ 0x915B,0xC8, BYTE_LEN, 0 },
	{ 0x915C,0x4f, BYTE_LEN, 0 },
	{ 0x915D,0x20, BYTE_LEN, 0 },
	{ 0x915E,0xBf, BYTE_LEN, 0 },
	{ 0x915F,0x00, BYTE_LEN, 0 },
	{ 0x9160,0xFd, BYTE_LEN, 0 },
	{ 0x9161,0x00, BYTE_LEN, 0 },
	{ 0x9162,0xF8, BYTE_LEN, 0 },
	{ 0x9163,0x03, BYTE_LEN, 0 },
	{ 0x9164,0xE0, BYTE_LEN, 0 },
	{ 0x9165,0x0f, BYTE_LEN, 0 },
	{ 0x9166,0x40, BYTE_LEN, 0 },
	{ 0x9167,0x3f, BYTE_LEN, 0 },
	{ 0x9168,0x00, BYTE_LEN, 0 },
	{ 0x9169,0xFd, BYTE_LEN, 0 },
	{ 0x916A,0x00, BYTE_LEN, 0 },
	{ 0x916B,0xFa, BYTE_LEN, 0 },
	{ 0x916C,0x03, BYTE_LEN, 0 },
	{ 0x916D,0xE8, BYTE_LEN, 0 },
	{ 0x916E,0x5f, BYTE_LEN, 0 },
	{ 0x916F,0x80, BYTE_LEN, 0 },
	{ 0x9170,0x7f, BYTE_LEN, 0 },
	{ 0x9171,0x01, BYTE_LEN, 0 },
	{ 0x9172,0xFe, BYTE_LEN, 0 },
	{ 0x9173,0x01, BYTE_LEN, 0 },
	{ 0x9174,0xFa, BYTE_LEN, 0 },
	{ 0x9175,0x07, BYTE_LEN, 0 },
	{ 0x9176,0xF0, BYTE_LEN, 0 },
	{ 0x9177,0x1f, BYTE_LEN, 0 },
	{ 0x9178,0x00, BYTE_LEN, 0 },
	{ 0x9179,0x00, BYTE_LEN, 0 },
	{ 0x917A,0x00, BYTE_LEN, 0 },
	{ 0x917B,0xFe, BYTE_LEN, 0 },
	{ 0x917C,0x00, BYTE_LEN, 0 },
	{ 0x917D,0xF8, BYTE_LEN, 0 },
	{ 0x917E,0x03, BYTE_LEN, 0 },
	{ 0x917F,0x08, BYTE_LEN, 0 },
	{ 0x9180,0x00, BYTE_LEN, 0 },
	{ 0x9181,0x20, BYTE_LEN, 0 },
	{ 0x9182,0x80, BYTE_LEN, 0 },
	{ 0x9183,0x81, BYTE_LEN, 0 },
	{ 0x9184,0xFf, BYTE_LEN, 0 },
	{ 0x9185,0x06, BYTE_LEN, 0 },
	{ 0x9186,0xFe, BYTE_LEN, 0 },
	{ 0x9187,0x13, BYTE_LEN, 0 },
	{ 0x9188,0x00, BYTE_LEN, 0 },
	{ 0x9189,0x10, BYTE_LEN, 0 },
	{ 0x918A,0x00, BYTE_LEN, 0 },
	{ 0x918B,0x40, BYTE_LEN, 0 },
	{ 0x918C,0x00, BYTE_LEN, 0 },
	{ 0x918D,0x01, BYTE_LEN, 0 },
	{ 0x918E,0x00, BYTE_LEN, 0 },
	{ 0x918F,0x04, BYTE_LEN, 0 },
	{ 0x9190,0x0c, BYTE_LEN, 0 },
	{ 0x9191,0x20, BYTE_LEN, 0 },
	{ 0x9192,0x30, BYTE_LEN, 0 },
	{ 0x9193,0x20, BYTE_LEN, 0 },
	{ 0x9194,0xC0, BYTE_LEN, 0 },
	{ 0x9195,0x80, BYTE_LEN, 0 },
	{ 0x9196,0x00, BYTE_LEN, 0 },
	{ 0x9197,0x07, BYTE_LEN, 0 },
	{ 0x9198,0x08, BYTE_LEN, 0 },
	{ 0x9199,0x1c, BYTE_LEN, 0 },
	{ 0x919A,0x20, BYTE_LEN, 0 },
	{ 0x919B,0x60, BYTE_LEN, 0 },
	{ 0x919C,0x40, BYTE_LEN, 0 },
	{ 0x919D,0xC0, BYTE_LEN, 0 },
	{ 0x919E,0x00, BYTE_LEN, 0 },
	{ 0x919F,0x02, BYTE_LEN, 0 },
	{ 0x91A0,0x04, BYTE_LEN, 0 },
	{ 0x91A1,0x0a, BYTE_LEN, 0 },
	{ 0x91A2,0x08, BYTE_LEN, 0 },
	{ 0x91A3,0x20, BYTE_LEN, 0 },
	{ 0x91A4,0x40, BYTE_LEN, 0 },
	{ 0x91A5,0x00, BYTE_LEN, 0 },
	{ 0x91A6,0xC1, BYTE_LEN, 0 },
	{ 0x91A7,0x00, BYTE_LEN, 0 },
	{ 0x91A8,0x01, BYTE_LEN, 0 },
	{ 0x91A9,0x03, BYTE_LEN, 0 },
	{ 0x91AA,0x04, BYTE_LEN, 0 },
	{ 0x91AB,0x20, BYTE_LEN, 0 },
	{ 0x91AC,0x30, BYTE_LEN, 0 },
	{ 0x91AD,0x80, BYTE_LEN, 0 },
	{ 0x91AE,0xC0, BYTE_LEN, 0 },
	{ 0x91AF,0x00, BYTE_LEN, 0 },
	{ 0x91B0,0x82, BYTE_LEN, 0 },
	{ 0x91B1,0x01, BYTE_LEN, 0 },
	{ 0x91B2,0x05, BYTE_LEN, 0 },
	{ 0x91B3,0x04, BYTE_LEN, 0 },
	{ 0x91B4,0x14, BYTE_LEN, 0 },
	{ 0x91B5,0x38, BYTE_LEN, 0 },
	{ 0x91B6,0x50, BYTE_LEN, 0 },
	{ 0x91B7,0xC0, BYTE_LEN, 0 },
	{ 0x91B8,0x80, BYTE_LEN, 0 },
	{ 0x91B9,0x01, BYTE_LEN, 0 },
	{ 0x91BA,0x03, BYTE_LEN, 0 },
	{ 0x91BB,0x06, BYTE_LEN, 0 },
	{ 0x91BC,0x14, BYTE_LEN, 0 },
	{ 0x91BD,0x18, BYTE_LEN, 0 },
	{ 0x91BE,0x50, BYTE_LEN, 0 },
	{ 0x91BF,0x70, BYTE_LEN, 0 },
	{ 0x91C0,0x80, BYTE_LEN, 0 },
	{ 0x91C1,0xC0, BYTE_LEN, 0 },
	{ 0x91C2,0x01, BYTE_LEN, 0 },
	{ 0x91C3,0x02, BYTE_LEN, 0 },
	{ 0x91C4,0x08, BYTE_LEN, 0 },
	{ 0x91C5,0x0c, BYTE_LEN, 0 },
	{ 0x91C6,0x20, BYTE_LEN, 0 },
	{ 0x91C7,0x28, BYTE_LEN, 0 },
	{ 0x91C8,0x50, BYTE_LEN, 0 },
	{ 0x91C9,0xC0, BYTE_LEN, 0 },
	{ 0x91CA,0x00, BYTE_LEN, 0 },
	{ 0x91CB,0x81, BYTE_LEN, 0 },
	{ 0x91CC,0x03, BYTE_LEN, 0 },
	{ 0x91CD,0x05, BYTE_LEN, 0 },
	{ 0x91CE,0x0c, BYTE_LEN, 0 },
	{ 0x91CF,0x18, BYTE_LEN, 0 },
	{ 0x91D0,0x30, BYTE_LEN, 0 },
	{ 0x91D1,0x60, BYTE_LEN, 0 },
	{ 0x91D2,0xC0, BYTE_LEN, 0 },
	{ 0x91D3,0xC0, BYTE_LEN, 0 },
	{ 0x91D4,0x01, BYTE_LEN, 0 },
	{ 0x91D5,0x02, BYTE_LEN, 0 },
	{ 0x91D6,0x07, BYTE_LEN, 0 },
	{ 0x91D7,0x08, BYTE_LEN, 0 },
	{ 0x91D8,0x20, BYTE_LEN, 0 },
	{ 0x91D9,0x30, BYTE_LEN, 0 },
	{ 0x91DA,0x80, BYTE_LEN, 0 },
	{ 0x91DB,0xA0, BYTE_LEN, 0 },
	{ 0x91DC,0x40, BYTE_LEN, 0 },
	{ 0x91DD,0x01, BYTE_LEN, 0 },
	{ 0x91DE,0x03, BYTE_LEN, 0 },
	{ 0x91DF,0x04, BYTE_LEN, 0 },
	{ 0x91E0,0x0e, BYTE_LEN, 0 },
	{ 0x91E1,0x14, BYTE_LEN, 0 },
	{ 0x91E2,0x30, BYTE_LEN, 0 },
	{ 0x91E3,0x60, BYTE_LEN, 0 },
	{ 0x91E4,0xC0, BYTE_LEN, 0 },
	{ 0x91E5,0x80, BYTE_LEN, 0 },
	{ 0x91E6,0x01, BYTE_LEN, 0 },
	{ 0x91E7,0x03, BYTE_LEN, 0 },

	{ 0xA000,0x9191, WORD_LEN, 0 },
	{ 0xA002,0x4a, BYTE_LEN, 0 },
	{ 0xA003,0x81, BYTE_LEN, 0 },
	{ 0xA004,0xCc, BYTE_LEN, 0 },
	{ 0xA005,0x59, BYTE_LEN, 0 },
	{ 0xA006,0x6a, BYTE_LEN, 0 },
	{ 0xA007,0x43, BYTE_LEN, 0 },
	{ 0xA008,0x96, BYTE_LEN, 0 },
	{ 0xA009,0xDb, BYTE_LEN, 0 },
	{ 0xA00A,0x74, BYTE_LEN, 0 },
	{ 0xA00B,0x25, BYTE_LEN, 0 },
	{ 0xA00C,0x36, BYTE_LEN, 0 },
	{ 0xA00D,0x5c, BYTE_LEN, 0 },
	{ 0xA00E,0x89, BYTE_LEN, 0 },
	{ 0xA00F,0x0d, BYTE_LEN, 0 },
	{ 0xA010,0x57, BYTE_LEN, 0 },
	{ 0xA011,0x66, BYTE_LEN, 0 },
	{ 0xA012,0x23, BYTE_LEN, 0 },
	{ 0xA013,0x96, BYTE_LEN, 0 },
	{ 0xA014,0xDc, BYTE_LEN, 0 },
	{ 0xA015,0x8c, BYTE_LEN, 0 },
	{ 0xA016,0x05, BYTE_LEN, 0 },
	{ 0xA017,0x37, BYTE_LEN, 0 },
	{ 0xA018,0x47, BYTE_LEN, 0 },
	{ 0xA019,0x99, BYTE_LEN, 0 },
	{ 0xA01A,0x4c, BYTE_LEN, 0 },
	{ 0xA01B,0x5c, BYTE_LEN, 0 },
	{ 0xA01C,0x82, BYTE_LEN, 0 },
	{ 0xA01D,0x93, BYTE_LEN, 0 },
	{ 0xA01E,0x17, BYTE_LEN, 0 },
	{ 0xA01F,0xE5, BYTE_LEN, 0 },
	{ 0xA020,0xC8, BYTE_LEN, 0 },
	{ 0xA021,0xA5, BYTE_LEN, 0 },
	{ 0xA022,0x38, BYTE_LEN, 0 },
	{ 0xA023,0x6d, BYTE_LEN, 0 },
	{ 0xA024,0xF1, BYTE_LEN, 0 },
	{ 0xA025,0xCd, BYTE_LEN, 0 },
	{ 0xA026,0x5a, BYTE_LEN, 0 },
	{ 0xA027,0x78, BYTE_LEN, 0 },
	{ 0xA028,0xD3, BYTE_LEN, 0 },
	{ 0xA029,0x16, BYTE_LEN, 0 },
	{ 0xA02A,0xE0, BYTE_LEN, 0 },
	{ 0xA02B,0xC4, BYTE_LEN, 0 },
	{ 0xA02C,0xA5, BYTE_LEN, 0 },
	{ 0xA02D,0x38, BYTE_LEN, 0 },
	{ 0xA02E,0x74, BYTE_LEN, 0 },
	{ 0xA02F,0x51, BYTE_LEN, 0 },
	{ 0xA030,0xCe, BYTE_LEN, 0 },
	{ 0xA031,0x5a, BYTE_LEN, 0 },
	{ 0xA032,0x80, BYTE_LEN, 0 },
	{ 0xA033,0xC3, BYTE_LEN, 0 },
	{ 0xA034,0x96, BYTE_LEN, 0 },
	{ 0xA035,0xDc, BYTE_LEN, 0 },
	{ 0xA036,0xC0, BYTE_LEN, 0 },
	{ 0xA037,0x65, BYTE_LEN, 0 },
	{ 0xA038,0x37, BYTE_LEN, 0 },
	{ 0xA039,0x5f, BYTE_LEN, 0 },
	{ 0xA03A,0x01, BYTE_LEN, 0 },
	{ 0xA03B,0xCd, BYTE_LEN, 0 },
	{ 0xA03C,0x54, BYTE_LEN, 0 },
	{ 0xA03D,0x18, BYTE_LEN, 0 },
	{ 0xA03E,0xD3, BYTE_LEN, 0 },
	{ 0xA03F,0x94, BYTE_LEN, 0 },
	{ 0xA040,0xC1, BYTE_LEN, 0 },
	{ 0xA041,0x44, BYTE_LEN, 0 },
	{ 0xA042,0x45, BYTE_LEN, 0 },
	{ 0xA043,0x31, BYTE_LEN, 0 },
	{ 0xA044,0x5c, BYTE_LEN, 0 },
	{ 0xA045,0xF9, BYTE_LEN, 0 },
	{ 0xA046,0x4c, BYTE_LEN, 0 },
	{ 0xA047,0x5b, BYTE_LEN, 0 },
	{ 0xA048,0x74, BYTE_LEN, 0 },
	{ 0xA049,0x43, BYTE_LEN, 0 },
	{ 0xA04A,0x96, BYTE_LEN, 0 },
	{ 0xA04B,0xDa, BYTE_LEN, 0 },
	{ 0xA04C,0x9c, BYTE_LEN, 0 },
	{ 0xA04D,0x85, BYTE_LEN, 0 },
	{ 0xA04E,0x35, BYTE_LEN, 0 },
	{ 0xA04F,0x5f, BYTE_LEN, 0 },
	{ 0xA050,0xE9, BYTE_LEN, 0 },
	{ 0xA051,0xCc, BYTE_LEN, 0 },
	{ 0xA052,0x51, BYTE_LEN, 0 },
	{ 0xA053,0xE8, BYTE_LEN, 0 },
	{ 0xA054,0x52, BYTE_LEN, 0 },
	{ 0xA055,0x93, BYTE_LEN, 0 },
	{ 0xA056,0xAa, BYTE_LEN, 0 },
	{ 0xA057,0xB4, BYTE_LEN, 0 },
	{ 0xA058,0x04, BYTE_LEN, 0 },
	{ 0xA059,0x29, BYTE_LEN, 0 },
	{ 0xA05A,0x32, BYTE_LEN, 0 },
	{ 0xA05B,0x99, BYTE_LEN, 0 },
	{ 0xA05C,0x8a, BYTE_LEN, 0 },
	{ 0xA05D,0x50, BYTE_LEN, 0 },
	{ 0xA05E,0xDa, BYTE_LEN, 0 },
	{ 0xA05F,0x92, BYTE_LEN, 0 },
	{ 0xA060,0x15, BYTE_LEN, 0 },
	{ 0xA061,0xCa, BYTE_LEN, 0 },
	{ 0xA062,0x78, BYTE_LEN, 0 },
	{ 0xA063,0x45, BYTE_LEN, 0 },
	{ 0xA064,0x34, BYTE_LEN, 0 },
	{ 0xA065,0x61, BYTE_LEN, 0 },
	{ 0xA066,0xD1, BYTE_LEN, 0 },
	{ 0xA067,0x4c, BYTE_LEN, 0 },
	{ 0xA068,0x54, BYTE_LEN, 0 },
	{ 0xA069,0xFe, BYTE_LEN, 0 },
	{ 0xA06A,0x12, BYTE_LEN, 0 },
	{ 0xA06B,0x13, BYTE_LEN, 0 },
	{ 0xA06C,0xA6, BYTE_LEN, 0 },
	{ 0xA06D,0x60, BYTE_LEN, 0 },
	{ 0xA06E,0xC4, BYTE_LEN, 0 },
	{ 0xA06F,0x24, BYTE_LEN, 0 },
	{ 0xA070,0x0e, BYTE_LEN, 0 },
	{ 0xA071,0xC1, BYTE_LEN, 0 },
	{ 0xA072,0x08, BYTE_LEN, 0 },
	{ 0xA073,0x45, BYTE_LEN, 0 },
	{ 0xA074,0x44, BYTE_LEN, 0 },
	{ 0xA075,0xC2, BYTE_LEN, 0 },
	{ 0xA076,0x12, BYTE_LEN, 0 },
	{ 0xA077,0xA2, BYTE_LEN, 0 },
	{ 0xA078,0x20, BYTE_LEN, 0 },
	{ 0xA079,0x65, BYTE_LEN, 0 },
	{ 0xA07A,0x2e, BYTE_LEN, 0 },
	{ 0xA07B,0x53, BYTE_LEN, 0 },
	{ 0xA07C,0x59, BYTE_LEN, 0 },
	{ 0xA07D,0x4c, BYTE_LEN, 0 },
	{ 0xA07E,0x55, BYTE_LEN, 0 },
	{ 0xA07F,0x10, BYTE_LEN, 0 },
	{ 0xA080,0x63, BYTE_LEN, 0 },
	{ 0xA081,0x94, BYTE_LEN, 0 },
	{ 0xA082,0xB6, BYTE_LEN, 0 },
	{ 0xA083,0x90, BYTE_LEN, 0 },
	{ 0xA084,0xA4, BYTE_LEN, 0 },
	{ 0xA085,0x26, BYTE_LEN, 0 },
	{ 0xA086,0x09, BYTE_LEN, 0 },
	{ 0xA087,0x71, BYTE_LEN, 0 },
	{ 0xA088,0xC8, BYTE_LEN, 0 },
	{ 0xA089,0x3f, BYTE_LEN, 0 },
	{ 0xA08A,0x00, BYTE_LEN, 0 },
	{ 0xA08B,0x52, BYTE_LEN, 0 },
	{ 0xA08C,0x10, BYTE_LEN, 0 },
	{ 0xA08D,0x85, BYTE_LEN, 0 },
	{ 0xA08E,0x78, BYTE_LEN, 0 },
	{ 0xA08F,0xE4, BYTE_LEN, 0 },
	{ 0xA090,0x25, BYTE_LEN, 0 },
	{ 0xA091,0x3f, BYTE_LEN, 0 },
	{ 0xA092,0x19, BYTE_LEN, 0 },
	{ 0xA093,0x8b, BYTE_LEN, 0 },
	{ 0xA094,0x52, BYTE_LEN, 0 },
	{ 0xA095,0xF6, BYTE_LEN, 0 },
	{ 0xA096,0x62, BYTE_LEN, 0 },
	{ 0xA097,0x95, BYTE_LEN, 0 },
	{ 0xA098,0xC3, BYTE_LEN, 0 },
	{ 0xA099,0x20, BYTE_LEN, 0 },
	{ 0xA09A,0x85, BYTE_LEN, 0 },
	{ 0xA09B,0x2d, BYTE_LEN, 0 },
	{ 0xA09C,0x26, BYTE_LEN, 0 },
	{ 0xA09D,0xA9, BYTE_LEN, 0 },
	{ 0xA09E,0x89, BYTE_LEN, 0 },
	{ 0xA09F,0x42, BYTE_LEN, 0 },
	{ 0xA0A0,0x1a, BYTE_LEN, 0 },
	{ 0xA0A1,0x02, BYTE_LEN, 0 },
	{ 0xA0A2,0x90, BYTE_LEN, 0 },
	{ 0xA0A3,0x7f, BYTE_LEN, 0 },
	{ 0xA0A4,0x1c, BYTE_LEN, 0 },
	{ 0xA0A5,0x44, BYTE_LEN, 0 },
	{ 0xA0A6,0x21, BYTE_LEN, 0 },
	{ 0xA0A7,0x20, BYTE_LEN, 0 },
	{ 0xA0A8,0x71, BYTE_LEN, 0 },
	{ 0xA0A9,0x49, BYTE_LEN, 0 },
	{ 0xA0AA,0x50, BYTE_LEN, 0 },
	{ 0xA0AB,0xC6, BYTE_LEN, 0 },
	{ 0xA0AC,0xD2, BYTE_LEN, 0 },
	{ 0xA0AD,0x14, BYTE_LEN, 0 },
	{ 0xA0AE,0xBe, BYTE_LEN, 0 },
	{ 0xA0AF,0x90, BYTE_LEN, 0 },
	{ 0xA0B0,0x85, BYTE_LEN, 0 },
	{ 0xA0B1,0x33, BYTE_LEN, 0 },
	{ 0xA0B2,0x54, BYTE_LEN, 0 },
	{ 0xA0B3,0x01, BYTE_LEN, 0 },
	{ 0xA0B4,0x8c, BYTE_LEN, 0 },
	{ 0xA0B5,0x4d, BYTE_LEN, 0 },
	{ 0xA0B6,0x96, BYTE_LEN, 0 },
	{ 0xA0B7,0xC2, BYTE_LEN, 0 },
	{ 0xA0B8,0x11, BYTE_LEN, 0 },
	{ 0xA0B9,0x92, BYTE_LEN, 0 },
	{ 0xA0BA,0x4c, BYTE_LEN, 0 },
	{ 0xA0BB,0xE4, BYTE_LEN, 0 },
	{ 0xA0BC,0x22, BYTE_LEN, 0 },
	{ 0xA0BD,0x18, BYTE_LEN, 0 },
	{ 0xA0BE,0x01, BYTE_LEN, 0 },
	{ 0xA0BF,0xC9, BYTE_LEN, 0 },
	{ 0xA0C0,0x4b, BYTE_LEN, 0 },
	{ 0xA0C1,0x86, BYTE_LEN, 0 },
	{ 0xA0C2,0xD2, BYTE_LEN, 0 },
	{ 0xA0C3,0x14, BYTE_LEN, 0 },
	{ 0xA0C4,0xBb, BYTE_LEN, 0 },
	{ 0xA0C5,0x68, BYTE_LEN, 0 },
	{ 0xA0C6,0x05, BYTE_LEN, 0 },
	{ 0xA0C7,0x32, BYTE_LEN, 0 },
	{ 0xA0C8,0x6f, BYTE_LEN, 0 },
	{ 0xA0C9,0x79, BYTE_LEN, 0 },
	{ 0xA0CA,0x4d, BYTE_LEN, 0 },
	{ 0xA0CB,0x5a, BYTE_LEN, 0 },
	{ 0xA0CC,0x3e, BYTE_LEN, 0 },
	{ 0xA0CD,0x23, BYTE_LEN, 0 },
	{ 0xA0CE,0x15, BYTE_LEN, 0 },
	{ 0xA0CF,0xBb, BYTE_LEN, 0 },
	{ 0xA0D0,0xF8, BYTE_LEN, 0 },
	{ 0xA0D1,0xA4, BYTE_LEN, 0 },
	{ 0xA0D2,0x2a, BYTE_LEN, 0 },
	{ 0xA0D3,0x35, BYTE_LEN, 0 },
	{ 0xA0D4,0x49, BYTE_LEN, 0 },
	{ 0xA0D5,0x0a, BYTE_LEN, 0 },
	{ 0xA0D6,0x4e, BYTE_LEN, 0 },
	{ 0xA0D7,0xA2, BYTE_LEN, 0 },
	{ 0xA0D8,0x82, BYTE_LEN, 0 },
	{ 0xA0D9,0x14, BYTE_LEN, 0 },
	{ 0xA0DA,0xB6, BYTE_LEN, 0 },
	{ 0xA0DB,0x80, BYTE_LEN, 0 },
	{ 0xA0DC,0x25, BYTE_LEN, 0 },
	{ 0xA0DD,0x33, BYTE_LEN, 0 },
	{ 0xA0DE,0x66, BYTE_LEN, 0 },
	{ 0xA0DF,0x51, BYTE_LEN, 0 },
	{ 0xA0E0,0xCd, BYTE_LEN, 0 },
	{ 0xA0E1,0x5d, BYTE_LEN, 0 },
	{ 0xA0E2,0x88, BYTE_LEN, 0 },
	{ 0xA0E3,0xF3, BYTE_LEN, 0 },
	{ 0xA0E4,0x97, BYTE_LEN, 0 },
	{ 0xA0E5,0xE4, BYTE_LEN, 0 },
	{ 0xA0E6,0xB4, BYTE_LEN, 0 },
	{ 0xA0E7,0x65, BYTE_LEN, 0 },
	{ 0xA0E8,0x35, BYTE_LEN, 0 },
	{ 0xA0E9,0x5f, BYTE_LEN, 0 },
	{ 0xA0EA,0xA1, BYTE_LEN, 0 },
	{ 0xA0EB,0x0c, BYTE_LEN, 0 },
	{ 0xA0EC,0x56, BYTE_LEN, 0 },
	{ 0xA0ED,0x10, BYTE_LEN, 0 },
	{ 0xA0EE,0xA3, BYTE_LEN, 0 },
	{ 0xA0EF,0x95, BYTE_LEN, 0 },
	{ 0xA0F0,0xC5, BYTE_LEN, 0 },
	{ 0xA0F1,0x90, BYTE_LEN, 0 },
	{ 0xA0F2,0xE5, BYTE_LEN, 0 },
	{ 0xA0F3,0x33, BYTE_LEN, 0 },
	{ 0xA0F4,0x75, BYTE_LEN, 0 },
	{ 0xA0F5,0xF1, BYTE_LEN, 0 },
	{ 0xA0F6,0x4d, BYTE_LEN, 0 },
	{ 0xA0F7,0x5b, BYTE_LEN, 0 },
	{ 0xA0F8,0x74, BYTE_LEN, 0 },
	{ 0xA0F9,0xD3, BYTE_LEN, 0 },
	{ 0xA0FA,0x17, BYTE_LEN, 0 },
	{ 0xA0FB,0xE8, BYTE_LEN, 0 },
	{ 0xA0FC,0x1c, BYTE_LEN, 0 },
	{ 0xA0FD,0x66, BYTE_LEN, 0 },
	{ 0xA0FE,0x3b, BYTE_LEN, 0 },
	{ 0xA0FF,0x82, BYTE_LEN, 0 },
	{ 0xA100,0xC1, BYTE_LEN, 0 },
	{ 0xA101,0x0e, BYTE_LEN, 0 },
	{ 0xA102,0x5f, BYTE_LEN, 0 },
	{ 0xA103,0x9a, BYTE_LEN, 0 },
	{ 0xA104,0x93, BYTE_LEN, 0 },
	{ 0xA105,0x17, BYTE_LEN, 0 },
	{ 0xA106,0xE4, BYTE_LEN, 0 },
	{ 0xA107,0xE0, BYTE_LEN, 0 },
	{ 0xA108,0xA5, BYTE_LEN, 0 },
	{ 0xA109,0x38, BYTE_LEN, 0 },
	{ 0xA10A,0x79, BYTE_LEN, 0 },
	{ 0xA10B,0x39, BYTE_LEN, 0 },
	{ 0xA10C,0x0e, BYTE_LEN, 0 },
	{ 0xA10D,0x5f, BYTE_LEN, 0 },
	{ 0xA10E,0xA0, BYTE_LEN, 0 },
	{ 0xA10F,0x13, BYTE_LEN, 0 },
	{ 0xA110,0x17, BYTE_LEN, 0 },
	{ 0xA111,0xE3, BYTE_LEN, 0 },
	{ 0xA112,0x44, BYTE_LEN, 0 },
	{ 0xA113,0xC5, BYTE_LEN, 0 },
	{ 0xA114,0x32, BYTE_LEN, 0 },
	{ 0xA115,0x70, BYTE_LEN, 0 },
	{ 0xA116,0x11, BYTE_LEN, 0 },
	{ 0xA117,0x0e, BYTE_LEN, 0 },
	{ 0xA118,0x5c, BYTE_LEN, 0 },
	{ 0xA119,0x90, BYTE_LEN, 0 },
	{ 0xA11A,0x93, BYTE_LEN, 0 },
	{ 0xA11B,0x96, BYTE_LEN, 0 },
	{ 0xA11C,0xDe, BYTE_LEN, 0 },
	{ 0xA11D,0xA4, BYTE_LEN, 0 },
	{ 0xA11E,0xA5, BYTE_LEN, 0 },
	{ 0xA11F,0x37, BYTE_LEN, 0 },
	{ 0xA120,0x66, BYTE_LEN, 0 },
	{ 0xA121,0xB1, BYTE_LEN, 0 },
	{ 0xA122,0x4d, BYTE_LEN, 0 },
	{ 0xA123,0x5a, BYTE_LEN, 0 },
	{ 0xA124,0x74, BYTE_LEN, 0 },
	{ 0xA125,0x73, BYTE_LEN, 0 },
	{ 0xA126,0x96, BYTE_LEN, 0 },
	{ 0xA127,0xDc, BYTE_LEN, 0 },
	{ 0xA128,0x24, BYTE_LEN, 0 },
	{ 0xA129,0x85, BYTE_LEN, 0 },
	{ 0xA12A,0x32, BYTE_LEN, 0 },
	{ 0xA12B,0x3b, BYTE_LEN, 0 },
	{ 0xA12C,0x39, BYTE_LEN, 0 },
	{ 0xA12D,0x0a, BYTE_LEN, 0 },
	{ 0xA12E,0x56, BYTE_LEN, 0 },
	{ 0xA12F,0xCa, BYTE_LEN, 0 },
	{ 0xA130,0x92, BYTE_LEN, 0 },
	{ 0xA131,0x95, BYTE_LEN, 0 },
	{ 0xA132,0xB3, BYTE_LEN, 0 },
	{ 0xA133,0x50, BYTE_LEN, 0 },
	{ 0xA134,0x25, BYTE_LEN, 0 },
	{ 0xA135,0x2c, BYTE_LEN, 0 },
	{ 0xA136,0x57, BYTE_LEN, 0 },
	{ 0xA137,0x01, BYTE_LEN, 0 },
	{ 0xA138,0xCb, BYTE_LEN, 0 },
	{ 0xA139,0x55, BYTE_LEN, 0 },
	{ 0xA13A,0xC0, BYTE_LEN, 0 },
	{ 0xA13B,0xB2, BYTE_LEN, 0 },
	{ 0xA13C,0x95, BYTE_LEN, 0 },
	{ 0xA13D,0xB3, BYTE_LEN, 0 },
	{ 0xA13E,0x64, BYTE_LEN, 0 },
	{ 0xA13F,0xE5, BYTE_LEN, 0 },
	{ 0xA140,0x2c, BYTE_LEN, 0 },
	{ 0xA141,0x3c, BYTE_LEN, 0 },
	{ 0xA142,0x49, BYTE_LEN, 0 },
	{ 0xA143,0x0a, BYTE_LEN, 0 },
	{ 0xA144,0x58, BYTE_LEN, 0 },
	{ 0xA145,0xDe, BYTE_LEN, 0 },
	{ 0xA146,0x92, BYTE_LEN, 0 },
	{ 0xA147,0x16, BYTE_LEN, 0 },
	{ 0xA148,0xBc, BYTE_LEN, 0 },
	{ 0xA149,0xA0, BYTE_LEN, 0 },
	{ 0xA14A,0xA5, BYTE_LEN, 0 },
	{ 0xA14B,0x2e, BYTE_LEN, 0 },
	{ 0xA14C,0x64, BYTE_LEN, 0 },
	{ 0xA14D,0x89, BYTE_LEN, 0 },
	{ 0xA14E,0x4b, BYTE_LEN, 0 },
	{ 0xA14F,0x59, BYTE_LEN, 0 },
	{ 0xA150,0xDc, BYTE_LEN, 0 },
	{ 0xA151,0x72, BYTE_LEN, 0 },
	{ 0xA152,0x16, BYTE_LEN, 0 },
	{ 0xA153,0xB8, BYTE_LEN, 0 },
	{ 0xA154,0xA4, BYTE_LEN, 0 },
	{ 0xA155,0xA5, BYTE_LEN, 0 },
	{ 0xA156,0x2e, BYTE_LEN, 0 },
	{ 0xA157,0x69, BYTE_LEN, 0 },
	{ 0xA158,0xB9, BYTE_LEN, 0 },
	{ 0xA159,0x8b, BYTE_LEN, 0 },
	{ 0xA15A,0x57, BYTE_LEN, 0 },
	{ 0xA15B,0xDa, BYTE_LEN, 0 },
	{ 0xA15C,0xE2, BYTE_LEN, 0 },
	{ 0xA15D,0x95, BYTE_LEN, 0 },
	{ 0xA15E,0xB5, BYTE_LEN, 0 },
	{ 0xA15F,0x94, BYTE_LEN, 0 },
	{ 0xA160,0x25, BYTE_LEN, 0 },
	{ 0xA161,0x2e, BYTE_LEN, 0 },
	{ 0xA162,0x57, BYTE_LEN, 0 },
	{ 0xA163,0x09, BYTE_LEN, 0 },
	{ 0xA164,0x4b, BYTE_LEN, 0 },
	{ 0xA165,0x53, BYTE_LEN, 0 },
	{ 0xA166,0xAc, BYTE_LEN, 0 },
	{ 0xA167,0xA2, BYTE_LEN, 0 },
	{ 0xA168,0x14, BYTE_LEN, 0 },
	{ 0xA169,0xA8, BYTE_LEN, 0 },
	{ 0xA16A,0x38, BYTE_LEN, 0 },
	{ 0xA16B,0x85, BYTE_LEN, 0 },
	{ 0xA16C,0x2a, BYTE_LEN, 0 },
	{ 0xA16D,0x57, BYTE_LEN, 0 },
	{ 0xA16E,0xF9, BYTE_LEN, 0 },
	{ 0xA16F,0x8a, BYTE_LEN, 0 },
	{ 0xA170,0x59, BYTE_LEN, 0 },
	{ 0xA171,0xDe, BYTE_LEN, 0 },
	{ 0xA172,0xB2, BYTE_LEN, 0 },
	{ 0xA173,0x95, BYTE_LEN, 0 },
	{ 0xA174,0xB2, BYTE_LEN, 0 },
	{ 0xA175,0x5c, BYTE_LEN, 0 },
	{ 0xA176,0xE5, BYTE_LEN, 0 },
	{ 0xA177,0x2c, BYTE_LEN, 0 },
	{ 0xA178,0x53, BYTE_LEN, 0 },
	{ 0xA179,0x09, BYTE_LEN, 0 },
	{ 0xA17A,0x4b, BYTE_LEN, 0 },
	{ 0xA17B,0x50, BYTE_LEN, 0 },
	{ 0xA17C,0x92, BYTE_LEN, 0 },
	{ 0xA17D,0x22, BYTE_LEN, 0 },
	{ 0xA17E,0x93, BYTE_LEN, 0 },
	{ 0xA17F,0x9b, BYTE_LEN, 0 },
	{ 0xA180,0xB0, BYTE_LEN, 0 },
	{ 0xA181,0x04, BYTE_LEN, 0 },
	{ 0xA182,0x26, BYTE_LEN, 0 },
	{ 0xA183,0x32, BYTE_LEN, 0 },
	{ 0xA184,0xA9, BYTE_LEN, 0 },
	{ 0xA185,0x09, BYTE_LEN, 0 },
	{ 0xA186,0x50, BYTE_LEN, 0 },
	{ 0xA187,0x8a, BYTE_LEN, 0 },
	{ 0xA188,0x42, BYTE_LEN, 0 },
	{ 0xA189,0x15, BYTE_LEN, 0 },
	{ 0xA18A,0xAd, BYTE_LEN, 0 },
	{ 0xA18B,0x58, BYTE_LEN, 0 },
	{ 0xA18C,0xC5, BYTE_LEN, 0 },
	{ 0xA18D,0x2b, BYTE_LEN, 0 },
	{ 0xA18E,0x50, BYTE_LEN, 0 },
	{ 0xA18F,0xF1, BYTE_LEN, 0 },
	{ 0xA190,0x4a, BYTE_LEN, 0 },
	{ 0xA191,0x51, BYTE_LEN, 0 },
	{ 0xA192,0xA0, BYTE_LEN, 0 },
	{ 0xA193,0xB2, BYTE_LEN, 0 },
	{ 0xA194,0x12, BYTE_LEN, 0 },
	{ 0xA195,0x99, BYTE_LEN, 0 },
	{ 0xA196,0x54, BYTE_LEN, 0 },
	{ 0xA197,0x24, BYTE_LEN, 0 },
	{ 0xA198,0x23, BYTE_LEN, 0 },
	{ 0xA199,0x0e, BYTE_LEN, 0 },
	{ 0xA19A,0x81, BYTE_LEN, 0 },
	{ 0xA19B,0x48, BYTE_LEN, 0 },
	{ 0xA19C,0x45, BYTE_LEN, 0 },
	{ 0xA19D,0x2c, BYTE_LEN, 0 },
	{ 0xA19E,0xB2, BYTE_LEN, 0 },
	{ 0xA19F,0x92, BYTE_LEN, 0 },
	{ 0xA1A0,0x96, BYTE_LEN, 0 },
	{ 0xA1A1,0x10, BYTE_LEN, 0 },
	{ 0xA1A2,0x25, BYTE_LEN, 0 },
	{ 0xA1A3,0x29, BYTE_LEN, 0 },
	{ 0xA1A4,0x4c, BYTE_LEN, 0 },
	{ 0xA1A5,0x99, BYTE_LEN, 0 },
	{ 0xA1A6,0x4a, BYTE_LEN, 0 },
	{ 0xA1A7,0x51, BYTE_LEN, 0 },
	{ 0xA1A8,0xA4, BYTE_LEN, 0 },
	{ 0xA1A9,0xC2, BYTE_LEN, 0 },
	{ 0xA1AA,0x93, BYTE_LEN, 0 },
	{ 0xA1AB,0xA2, BYTE_LEN, 0 },
	{ 0xA1AC,0x7c, BYTE_LEN, 0 },
	{ 0xA1AD,0x84, BYTE_LEN, 0 },
	{ 0xA1AE,0x24, BYTE_LEN, 0 },
	{ 0xA1AF,0x07, BYTE_LEN, 0 },
	{ 0xA1B0,0x49, BYTE_LEN, 0 },
	{ 0xA1B1,0x08, BYTE_LEN, 0 },
	{ 0xA1B2,0x40, BYTE_LEN, 0 },
	{ 0xA1B3,0x00, BYTE_LEN, 0 },
	{ 0xA1B4,0x72, BYTE_LEN, 0 },
	{ 0xA1B5,0x10, BYTE_LEN, 0 },
	{ 0xA1B6,0x83, BYTE_LEN, 0 },
	{ 0xA1B7,0x7c, BYTE_LEN, 0 },
	{ 0xA1B8,0xC4, BYTE_LEN, 0 },
	{ 0xA1B9,0x23, BYTE_LEN, 0 },
	{ 0xA1BA,0x39, BYTE_LEN, 0 },
	{ 0xA1BB,0xF1, BYTE_LEN, 0 },
	{ 0xA1BC,0xC9, BYTE_LEN, 0 },
	{ 0xA1BD,0x4f, BYTE_LEN, 0 },
	{ 0xA1BE,0x92, BYTE_LEN, 0 },
	{ 0xA1BF,0x72, BYTE_LEN, 0 },
	{ 0xA1C0,0x94, BYTE_LEN, 0 },
	{ 0xA1C1,0xA8, BYTE_LEN, 0 },
	{ 0xA1C2,0xF4, BYTE_LEN, 0 },
	{ 0xA1C3,0xA4, BYTE_LEN, 0 },
	{ 0xA1C4,0x28, BYTE_LEN, 0 },
	{ 0xA1C5,0x20, BYTE_LEN, 0 },
	{ 0xA1C6,0x21, BYTE_LEN, 0 },
	{ 0xA1C7,0xC9, BYTE_LEN, 0 },
	{ 0xA1C8,0x41, BYTE_LEN, 0 },
	{ 0xA1C9,0x12, BYTE_LEN, 0 },
	{ 0xA1CA,0xF2, BYTE_LEN, 0 },
	{ 0xA1CB,0x8f, BYTE_LEN, 0 },
	{ 0xA1CC,0x7f, BYTE_LEN, 0 },
	{ 0xA1CD,0x18, BYTE_LEN, 0 },
	{ 0xA1CE,0xA4, BYTE_LEN, 0 },
	{ 0xA1CF,0x20, BYTE_LEN, 0 },
	{ 0xA1D0,0x1d, BYTE_LEN, 0 },
	{ 0xA1D1,0xE9, BYTE_LEN, 0 },
	{ 0xA1D2,0xC8, BYTE_LEN, 0 },
	{ 0xA1D3,0x4d, BYTE_LEN, 0 },
	{ 0xA1D4,0x7c, BYTE_LEN, 0 },
	{ 0xA1D5,0xC2, BYTE_LEN, 0 },
	{ 0xA1D6,0x93, BYTE_LEN, 0 },
	{ 0xA1D7,0xA4, BYTE_LEN, 0 },
	{ 0xA1D8,0x54, BYTE_LEN, 0 },
	{ 0xA1D9,0xC5, BYTE_LEN, 0 },
	{ 0xA1DA,0x2b, BYTE_LEN, 0 },
	{ 0xA1DB,0x4a, BYTE_LEN, 0 },
	{ 0xA1DC,0x89, BYTE_LEN, 0 },
	{ 0xA1DD,0xCa, BYTE_LEN, 0 },
	{ 0xA1DE,0x4b, BYTE_LEN, 0 },
	{ 0xA1DF,0x66, BYTE_LEN, 0 },
	{ 0xA1E0,0x62, BYTE_LEN, 0 },
	{ 0xA1E1,0x91, BYTE_LEN, 0 },
	{ 0xA1E2,0x8c, BYTE_LEN, 0 },
	{ 0xA1E3,0x38, BYTE_LEN, 0 },
	{ 0xA1E4,0x04, BYTE_LEN, 0 },
	{ 0xA1E5,0x22, BYTE_LEN, 0 },
	{ 0xA1E6,0x14, BYTE_LEN, 0 },
	{ 0xA1E7,0xA9, BYTE_LEN, 0 },
	{ 0xA1E8,0x88, BYTE_LEN, 0 },
	{ 0xA1E9,0x4a, BYTE_LEN, 0 },
	{ 0xA1EA,0x5a, BYTE_LEN, 0 },
	{ 0xA1EB,0x02, BYTE_LEN, 0 },
	{ 0xA1EC,0x94, BYTE_LEN, 0 },
	{ 0xA1ED,0xA4, BYTE_LEN, 0 },
	{ 0xA1EE,0x1c, BYTE_LEN, 0 },
	{ 0xA1EF,0xA5, BYTE_LEN, 0 },
	{ 0xA1F0,0x2a, BYTE_LEN, 0 },
	{ 0xA1F1,0x61, BYTE_LEN, 0 },
	{ 0xA1F2,0x51, BYTE_LEN, 0 },
	{ 0xA1F3,0x0b, BYTE_LEN, 0 },
	{ 0xA1F4,0x57, BYTE_LEN, 0 },
	{ 0xA1F5,0xCa, BYTE_LEN, 0 },
	{ 0xA1F6,0x92, BYTE_LEN, 0 },
	{ 0xA1F7,0x94, BYTE_LEN, 0 },
	{ 0xA1F8,0xA6, BYTE_LEN, 0 },
	{ 0xA1F9,0xD8, BYTE_LEN, 0 },
	{ 0xA1FA,0x44, BYTE_LEN, 0 },
	{ 0xA1FB,0x27, BYTE_LEN, 0 },
	{ 0xA1FC,0x2f, BYTE_LEN, 0 },
	{ 0xA1FD,0x91, BYTE_LEN, 0 },
	{ 0xA1FE,0x49, BYTE_LEN, 0 },
	{ 0xA1FF,0x4c, BYTE_LEN, 0 },
	{ 0xA200,0x6c, BYTE_LEN, 0 },
	{ 0xA201,0xE2, BYTE_LEN, 0 },
	{ 0xA202,0x93, BYTE_LEN, 0 },
	{ 0xA203,0xA3, BYTE_LEN, 0 },
	{ 0xA204,0x3c, BYTE_LEN, 0 },
	{ 0xA205,0x85, BYTE_LEN, 0 },
	{ 0xA206,0x2b, BYTE_LEN, 0 },
	{ 0xA207,0x50, BYTE_LEN, 0 },
	{ 0xA208,0x09, BYTE_LEN, 0 },
	{ 0xA209,0xCb, BYTE_LEN, 0 },
	{ 0xA20A,0x5a, BYTE_LEN, 0 },
	{ 0xA20B,0xE8, BYTE_LEN, 0 },
	{ 0xA20C,0x42, BYTE_LEN, 0 },
	{ 0xA20D,0x17, BYTE_LEN, 0 },
	{ 0xA20E,0xBe, BYTE_LEN, 0 },
	{ 0xA20F,0x94, BYTE_LEN, 0 },
	{ 0xA210,0x65, BYTE_LEN, 0 },
	{ 0xA211,0x2d, BYTE_LEN, 0 },
	{ 0xA212,0x57, BYTE_LEN, 0 },
	{ 0xA213,0xE9, BYTE_LEN, 0 },
	{ 0xA214,0x0a, BYTE_LEN, 0 },
	{ 0xA215,0x54, BYTE_LEN, 0 },
	{ 0xA216,0xAe, BYTE_LEN, 0 },
	{ 0xA217,0x02, BYTE_LEN, 0 },
	{ 0xA218,0x15, BYTE_LEN, 0 },
	{ 0xA219,0xAd, BYTE_LEN, 0 },
	{ 0xA21A,0x58, BYTE_LEN, 0 },
	{ 0xA21B,0x85, BYTE_LEN, 0 },
	{ 0xA21C,0x2c, BYTE_LEN, 0 },
	{ 0xA21D,0x62, BYTE_LEN, 0 },
	{ 0xA21E,0xB1, BYTE_LEN, 0 },
	{ 0xA21F,0x8b, BYTE_LEN, 0 },
	{ 0xA220,0x55, BYTE_LEN, 0 },
	{ 0xA221,0xD8, BYTE_LEN, 0 },
	{ 0xA222,0xE2, BYTE_LEN, 0 },
	{ 0xA223,0x16, BYTE_LEN, 0 },
	{ 0xA224,0xBd, BYTE_LEN, 0 },
	{ 0xA225,0xE4, BYTE_LEN, 0 },
	{ 0xA226,0x85, BYTE_LEN, 0 },
	{ 0xA227,0x30, BYTE_LEN, 0 },
	{ 0xA228,0x79, BYTE_LEN, 0 },
	{ 0xA229,0x11, BYTE_LEN, 0 },
	{ 0xA22A,0x4c, BYTE_LEN, 0 },
	{ 0xA22B,0x5d, BYTE_LEN, 0 },
	{ 0xA22C,0xFa, BYTE_LEN, 0 },
	{ 0xA22D,0xD2, BYTE_LEN, 0 },
	{ 0xA22E,0x16, BYTE_LEN, 0 },
	{ 0xA22F,0xBd, BYTE_LEN, 0 },
	{ 0xA230,0xA0, BYTE_LEN, 0 },
	{ 0xA231,0x45, BYTE_LEN, 0 },
	{ 0xA232,0x2f, BYTE_LEN, 0 },
	{ 0xA233,0x67, BYTE_LEN, 0 },
	{ 0xA234,0xE1, BYTE_LEN, 0 },
	{ 0xA235,0xCb, BYTE_LEN, 0 },
	{ 0xA236,0x59, BYTE_LEN, 0 },
	{ 0xA237,0xFc, BYTE_LEN, 0 },
	{ 0xA238,0xB2, BYTE_LEN, 0 },
	{ 0xA239,0x95, BYTE_LEN, 0 },
	{ 0xA23A,0xB8, BYTE_LEN, 0 },
	{ 0xA23B,0x10, BYTE_LEN, 0 },
	{ 0xA23C,0xC5, BYTE_LEN, 0 },
	{ 0xA23D,0x29, BYTE_LEN, 0 },
	{ 0xA23E,0x63, BYTE_LEN, 0 },
	{ 0xA23F,0x71, BYTE_LEN, 0 },
	{ 0xA240,0x4b, BYTE_LEN, 0 },
	{ 0xA241,0x5a, BYTE_LEN, 0 },
	{ 0xA242,0xE4, BYTE_LEN, 0 },
	{ 0xA243,0x52, BYTE_LEN, 0 },
	{ 0xA244,0x16, BYTE_LEN, 0 },
	{ 0xA245,0xB6, BYTE_LEN, 0 },
	{ 0xA246,0x78, BYTE_LEN, 0 },
	{ 0xA247,0x85, BYTE_LEN, 0 },
	{ 0xA248,0x2d, BYTE_LEN, 0 },
	{ 0xA249,0x56, BYTE_LEN, 0 },
	{ 0xA24A,0x51, BYTE_LEN, 0 },
	{ 0xA24B,0x0b, BYTE_LEN, 0 },
	{ 0xA24C,0x56, BYTE_LEN, 0 },
	{ 0xA24D,0xDc, BYTE_LEN, 0 },
	{ 0xA24E,0x52, BYTE_LEN, 0 },
	{ 0xA24F,0x15, BYTE_LEN, 0 },
	{ 0xA250,0xB4, BYTE_LEN, 0 },
	{ 0xA251,0xD8, BYTE_LEN, 0 },
	{ 0xA252,0xE4, BYTE_LEN, 0 },
	{ 0xA253,0x28, BYTE_LEN, 0 },

	{ 0xA254,0x77, BYTE_LEN, 0 },
	{ 0xA255,0xE9, BYTE_LEN, 0 },
	{ 0xA256,0xCc, BYTE_LEN, 0 },
	{ 0xA257,0x67, BYTE_LEN, 0 },
	{ 0xA258,0x30, BYTE_LEN, 0 },
	{ 0xA259,0x83, BYTE_LEN, 0 },
	{ 0xA25A,0x99, BYTE_LEN, 0 },
	{ 0xA25B,0xCc, BYTE_LEN, 0 },
	{ 0xA25C,0x84, BYTE_LEN, 0 },
	{ 0xA25D,0x26, BYTE_LEN, 0 },
	{ 0xA25E,0x34, BYTE_LEN, 0 },
	{ 0xA25F,0x81, BYTE_LEN, 0 },
	{ 0xA260,0x49, BYTE_LEN, 0 },
	{ 0xA261,0xCd, BYTE_LEN, 0 },
	{ 0xA262,0x6c, BYTE_LEN, 0 },
	{ 0xA263,0x58, BYTE_LEN, 0 },
	{ 0xA264,0x43, BYTE_LEN, 0 },
	{ 0xA265,0x1a, BYTE_LEN, 0 },
	{ 0xA266,0xD1, BYTE_LEN, 0 },
	{ 0xA267,0x98, BYTE_LEN, 0 },
	{ 0xA268,0xA6, BYTE_LEN, 0 },
	{ 0xA269,0x35, BYTE_LEN, 0 },
	{ 0xA26A,0xB5, BYTE_LEN, 0 },
	{ 0xA26B,0xA1, BYTE_LEN, 0 },
	{ 0xA26C,0xCd, BYTE_LEN, 0 },
	{ 0xA26D,0x68, BYTE_LEN, 0 },
	{ 0xA26E,0x46, BYTE_LEN, 0 },
	{ 0xA26F,0x73, BYTE_LEN, 0 },
	{ 0xA270,0x98, BYTE_LEN, 0 },
	{ 0xA271,0xB9, BYTE_LEN, 0 },
	{ 0xA272,0xAc, BYTE_LEN, 0 },
	{ 0xA273,0x45, BYTE_LEN, 0 },
	{ 0xA274,0x2e, BYTE_LEN, 0 },
	{ 0xA275,0x87, BYTE_LEN, 0 },
	{ 0xA276,0x21, BYTE_LEN, 0 },
	{ 0xA277,0x0d, BYTE_LEN, 0 },
	{ 0xA278,0x6b, BYTE_LEN, 0 },
	{ 0xA279,0x26, BYTE_LEN, 0 },
	{ 0xA27A,0x33, BYTE_LEN, 0 },
	{ 0xA27B,0x98, BYTE_LEN, 0 },
	{ 0xA27C,0xAe, BYTE_LEN, 0 },
	{ 0xA27D,0x0c, BYTE_LEN, 0 },
	{ 0xA27E,0x05, BYTE_LEN, 0 },
	{ 0xA27F,0x27, BYTE_LEN, 0 },
	{ 0xA280,0x41, BYTE_LEN, 0 },
	{ 0xA281,0xC9, BYTE_LEN, 0 },
	{ 0xA282,0x0a, BYTE_LEN, 0 },
	{ 0xA283,0x60, BYTE_LEN, 0 },
	{ 0xA284,0x36, BYTE_LEN, 0 },
	{ 0xA285,0x13, BYTE_LEN, 0 },
	{ 0xA286,0x98, BYTE_LEN, 0 },
	{ 0xA287,0xB3, BYTE_LEN, 0 },
	{ 0xA288,0xF0, BYTE_LEN, 0 },
	{ 0xA289,0x84, BYTE_LEN, 0 },
	{ 0xA28A,0x23, BYTE_LEN, 0 },
	{ 0xA28B,0x11, BYTE_LEN, 0 },
	{ 0xA28C,0xD1, BYTE_LEN, 0 },
	{ 0xA28D,0xC8, BYTE_LEN, 0 },
	{ 0xA28E,0x4d, BYTE_LEN, 0 },
	{ 0xA28F,0xC4, BYTE_LEN, 0 },
	{ 0xA290,0x62, BYTE_LEN, 0 },
	{ 0xA291,0x18, BYTE_LEN, 0 },
	{ 0xA292,0xB8, BYTE_LEN, 0 },
	{ 0xA293,0x60, BYTE_LEN, 0 },
	{ 0xA294,0x25, BYTE_LEN, 0 },
	{ 0xA295,0x25, BYTE_LEN, 0 },
	{ 0xA296,0x0a, BYTE_LEN, 0 },
	{ 0xA297,0x01, BYTE_LEN, 0 },
	{ 0xA298,0xC8, BYTE_LEN, 0 },
	{ 0xA299,0x41, BYTE_LEN, 0 },
	{ 0xA29A,0x4c, BYTE_LEN, 0 },
	{ 0xA29B,0x32, BYTE_LEN, 0 },
	{ 0xA29C,0x15, BYTE_LEN, 0 },
	{ 0xA29D,0xBa, BYTE_LEN, 0 },
	{ 0xA29E,0xC0, BYTE_LEN, 0 },
	{ 0xA29F,0x05, BYTE_LEN, 0 },
	{ 0xA2A0,0x2b, BYTE_LEN, 0 },
	{ 0xA2A1,0x2a, BYTE_LEN, 0 },
	{ 0xA2A2,0x51, BYTE_LEN, 0 },
	{ 0xA2A3,0xC8, BYTE_LEN, 0 },
	{ 0xA2A4,0x3f, BYTE_LEN, 0 },
	{ 0xA2A5,0x0e, BYTE_LEN, 0 },
	{ 0xA2A6,0x52, BYTE_LEN, 0 },
	{ 0xA2A7,0x12, BYTE_LEN, 0 },
	{ 0xA2A8,0xAa, BYTE_LEN, 0 },
	{ 0xA2A9,0xC4, BYTE_LEN, 0 },
	{ 0xA2AA,0x65, BYTE_LEN, 0 },
	{ 0xA2AB,0x30, BYTE_LEN, 0 },
	{ 0xA2AC,0x69, BYTE_LEN, 0 },
	{ 0xA2AD,0xE1, BYTE_LEN, 0 },
	{ 0xA2AE,0x09, BYTE_LEN, 0 },
	{ 0xA2AF,0x47, BYTE_LEN, 0 },
	{ 0xA2B0,0x22, BYTE_LEN, 0 },
	{ 0xA2B1,0xA2, BYTE_LEN, 0 },
	{ 0xA2B2,0x11, BYTE_LEN, 0 },
	{ 0xA2B3,0x9c, BYTE_LEN, 0 },
	{ 0xA2B4,0x94, BYTE_LEN, 0 },
	{ 0xA2B5,0x05, BYTE_LEN, 0 },
	{ 0xA2B6,0x30, BYTE_LEN, 0 },
	{ 0xA2B7,0x98, BYTE_LEN, 0 },
	{ 0xA2B8,0x31, BYTE_LEN, 0 },
	{ 0xA2B9,0xCc, BYTE_LEN, 0 },
	{ 0xA2BA,0x57, BYTE_LEN, 0 },
	{ 0xA2BB,0x88, BYTE_LEN, 0 },
	{ 0xA2BC,0xA2, BYTE_LEN, 0 },
	{ 0xA2BD,0x13, BYTE_LEN, 0 },
	{ 0xA2BE,0xA1, BYTE_LEN, 0 },
	{ 0xA2BF,0x6c, BYTE_LEN, 0 },
	{ 0xA2C0,0xA5, BYTE_LEN, 0 },
	{ 0xA2C1,0x30, BYTE_LEN, 0 },
	{ 0xA2C2,0x98, BYTE_LEN, 0 },
	{ 0xA2C3,0x61, BYTE_LEN, 0 },
	{ 0xA2C4,0x8d, BYTE_LEN, 0 },
	{ 0xA2C5,0x6b, BYTE_LEN, 0 },
	{ 0xA2C6,0x1e, BYTE_LEN, 0 },
	{ 0xA2C7,0xA3, BYTE_LEN, 0 },
	{ 0xA2C8,0x17, BYTE_LEN, 0 },
	{ 0xA2C9,0xB8, BYTE_LEN, 0 },
	{ 0xA2CA,0xD4, BYTE_LEN, 0 },
	{ 0xA2CB,0x45, BYTE_LEN, 0 },
	{ 0xA2CC,0x31, BYTE_LEN, 0 },
	{ 0xA2CD,0xAc, BYTE_LEN, 0 },
	{ 0xA2CE,0x59, BYTE_LEN, 0 },
	{ 0xA2CF,0x8d, BYTE_LEN, 0 },
	{ 0xA2D0,0x6d, BYTE_LEN, 0 },
	{ 0xA2D1,0x80, BYTE_LEN, 0 },
	{ 0xA2D2,0xA3, BYTE_LEN, 0 },
	{ 0xA2D3,0x1b, BYTE_LEN, 0 },
	{ 0xA2D4,0xD8, BYTE_LEN, 0 },
	{ 0xA2D5,0xB0, BYTE_LEN, 0 },
	{ 0xA2D6,0xA6, BYTE_LEN, 0 },
	{ 0xA2D7,0x35, BYTE_LEN, 0 },
	{ 0xA2D8,0xB4, BYTE_LEN, 0 },
	{ 0xA2D9,0xF1, BYTE_LEN, 0 },
	{ 0xA2DA,0x4d, BYTE_LEN, 0 },
	{ 0xA2DB,0x6d, BYTE_LEN, 0 },
	{ 0xA2DC,0xF8, BYTE_LEN, 0 },
	{ 0xA2DD,0x62, BYTE_LEN, 0 },
	{ 0xA2DE,0x1a, BYTE_LEN, 0 },
	{ 0xA2DF,0xD6, BYTE_LEN, 0 },
	{ 0xA2E0,0x88, BYTE_LEN, 0 },
	{ 0xA2E1,0x26, BYTE_LEN, 0 },
	{ 0xA2E2,0x34, BYTE_LEN, 0 },
	{ 0xA2E3,0xA0, BYTE_LEN, 0 },
	{ 0xA2E4,0x41, BYTE_LEN, 0 },
	{ 0xA2E5,0x8d, BYTE_LEN, 0 },
	{ 0xA2E6,0x69, BYTE_LEN, 0 },
	{ 0xA2E7,0xFe, BYTE_LEN, 0 },
	{ 0xA2E8,0x02, BYTE_LEN, 0 },
	{ 0xA2E9,0x80, BYTE_LEN, 0 },
	{ 0xA2EA,0x00, BYTE_LEN, 0 },
	{ 0xA2EB,0x00, BYTE_LEN, 0 },
	{ 0xA2EC,0x00, BYTE_LEN, 0 },
	{ 0xA2ED,0x00, BYTE_LEN, 0 },

	{ 0xA2EE,0x98, BYTE_LEN, 0 },
	{ 0xA2EF,0x09, BYTE_LEN, 0 },
	{ 0xA2F0,0x8e, BYTE_LEN, 0 },
	{ 0xA2F1,0x70, BYTE_LEN, 0 },
	{ 0xA2F2,0x74, BYTE_LEN, 0 },
	{ 0xA2F3,0x83, BYTE_LEN, 0 },
	{ 0xA2F4,0x1b, BYTE_LEN, 0 },
	{ 0xA2F5,0xDc, BYTE_LEN, 0 },
	{ 0xA2F6,0xF8, BYTE_LEN, 0 },
	{ 0xA2F7,0xA6, BYTE_LEN, 0 },
	{ 0xA2F8,0x37, BYTE_LEN, 0 },
	{ 0xA2F9,0x96, BYTE_LEN, 0 },
	{ 0xA2FA,0x81, BYTE_LEN, 0 },
	{ 0xA2FB,0x0e, BYTE_LEN, 0 },
	{ 0xA2FC,0x76, BYTE_LEN, 0 },
	{ 0xA2FD,0xA0, BYTE_LEN, 0 },
	{ 0xA2FE,0x63, BYTE_LEN, 0 },
	{ 0xA2FF,0x1c, BYTE_LEN, 0 },
	{ 0xA300,0xE1, BYTE_LEN, 0 },
	{ 0xA301,0x10, BYTE_LEN, 0 },
	{ 0xA302,0x47, BYTE_LEN, 0 },
	{ 0xA303,0x39, BYTE_LEN, 0 },
	{ 0xA304,0xD1, BYTE_LEN, 0 },
	{ 0xA305,0x31, BYTE_LEN, 0 },
	{ 0xA306,0x0e, BYTE_LEN, 0 },
	{ 0xA307,0x72, BYTE_LEN, 0 },
	{ 0xA308,0x8e, BYTE_LEN, 0 },
	{ 0xA309,0x63, BYTE_LEN, 0 },
	{ 0xA30A,0x1a, BYTE_LEN, 0 },
	{ 0xA30B,0xC7, BYTE_LEN, 0 },
	{ 0xA30C,0x10, BYTE_LEN, 0 },
	{ 0xA30D,0x26, BYTE_LEN, 0 },
	{ 0xA30E,0x31, BYTE_LEN, 0 },
	{ 0xA30F,0x9e, BYTE_LEN, 0 },
	{ 0xA310,0xE1, BYTE_LEN, 0 },
	{ 0xA311,0x4d, BYTE_LEN, 0 },
	{ 0xA312,0x6e, BYTE_LEN, 0 },
	{ 0xA313,0x6e, BYTE_LEN, 0 },
	{ 0xA314,0x33, BYTE_LEN, 0 },
	{ 0xA315,0x9a, BYTE_LEN, 0 },
	{ 0xA316,0xBa, BYTE_LEN, 0 },
	{ 0xA317,0x54, BYTE_LEN, 0 },
	{ 0xA318,0xE5, BYTE_LEN, 0 },
	{ 0xA319,0x28, BYTE_LEN, 0 },
	{ 0xA31A,0x50, BYTE_LEN, 0 },
	{ 0xA31B,0x59, BYTE_LEN, 0 },
	{ 0xA31C,0xCb, BYTE_LEN, 0 },
	{ 0xA31D,0x64, BYTE_LEN, 0 },
	{ 0xA31E,0x4a, BYTE_LEN, 0 },
	{ 0xA31F,0x13, BYTE_LEN, 0 },
	{ 0xA320,0x9a, BYTE_LEN, 0 },
	{ 0xA321,0xC0, BYTE_LEN, 0 },
	{ 0xA322,0x30, BYTE_LEN, 0 },
	{ 0xA323,0xA5, BYTE_LEN, 0 },
	{ 0xA324,0x24, BYTE_LEN, 0 },
	{ 0xA325,0x17, BYTE_LEN, 0 },
	{ 0xA326,0x01, BYTE_LEN, 0 },
	{ 0xA327,0x89, BYTE_LEN, 0 },
	{ 0xA328,0x50, BYTE_LEN, 0 },
	{ 0xA329,0xE4, BYTE_LEN, 0 },
	{ 0xA32A,0xE2, BYTE_LEN, 0 },
	{ 0xA32B,0x18, BYTE_LEN, 0 },
	{ 0xA32C,0xC7, BYTE_LEN, 0 },
	{ 0xA32D,0xBc, BYTE_LEN, 0 },
	{ 0xA32E,0xA5, BYTE_LEN, 0 },
	{ 0xA32F,0x26, BYTE_LEN, 0 },
	{ 0xA330,0x0e, BYTE_LEN, 0 },
	{ 0xA331,0x01, BYTE_LEN, 0 },
	{ 0xA332,0x48, BYTE_LEN, 0 },
	{ 0xA333,0x42, BYTE_LEN, 0 },
	{ 0xA334,0x58, BYTE_LEN, 0 },
	{ 0xA335,0x12, BYTE_LEN, 0 },
	{ 0xA336,0x96, BYTE_LEN, 0 },
	{ 0xA337,0xBe, BYTE_LEN, 0 },
	{ 0xA338,0x38, BYTE_LEN, 0 },
	{ 0xA339,0xE6, BYTE_LEN, 0 },
	{ 0xA33A,0x2d, BYTE_LEN, 0 },
	{ 0xA33B,0x36, BYTE_LEN, 0 },
	{ 0xA33C,0x69, BYTE_LEN, 0 },
	{ 0xA33D,0xC8, BYTE_LEN, 0 },
	{ 0xA33E,0x3f, BYTE_LEN, 0 },
	{ 0xA33F,0x12, BYTE_LEN, 0 },
	{ 0xA340,0xC2, BYTE_LEN, 0 },
	{ 0xA341,0x92, BYTE_LEN, 0 },
	{ 0xA342,0xB0, BYTE_LEN, 0 },
	{ 0xA343,0xF8, BYTE_LEN, 0 },
	{ 0xA344,0x85, BYTE_LEN, 0 },
	{ 0xA345,0x34, BYTE_LEN, 0 },
	{ 0xA346,0x84, BYTE_LEN, 0 },
	{ 0xA347,0x61, BYTE_LEN, 0 },
	{ 0xA348,0x0a, BYTE_LEN, 0 },
	{ 0xA349,0x49, BYTE_LEN, 0 },
	{ 0xA34A,0x2c, BYTE_LEN, 0 },
	{ 0xA34B,0xF2, BYTE_LEN, 0 },
	{ 0xA34C,0x11, BYTE_LEN, 0 },
	{ 0xA34D,0xA1, BYTE_LEN, 0 },
	{ 0xA34E,0xD8, BYTE_LEN, 0 },
	{ 0xA34F,0x65, BYTE_LEN, 0 },
	{ 0xA350,0x32, BYTE_LEN, 0 },
	{ 0xA351,0xBc, BYTE_LEN, 0 },
	{ 0xA352,0x31, BYTE_LEN, 0 },
	{ 0xA353,0x8d, BYTE_LEN, 0 },
	{ 0xA354,0x5d, BYTE_LEN, 0 },
	{ 0xA355,0xA8, BYTE_LEN, 0 },
	{ 0xA356,0x72, BYTE_LEN, 0 },
	{ 0xA357,0x94, BYTE_LEN, 0 },
	{ 0xA358,0xA7, BYTE_LEN, 0 },
	{ 0xA359,0xB0, BYTE_LEN, 0 },
	{ 0xA35A,0x45, BYTE_LEN, 0 },
	{ 0xA35B,0x33, BYTE_LEN, 0 },
	{ 0xA35C,0xAf, BYTE_LEN, 0 },
	{ 0xA35D,0x91, BYTE_LEN, 0 },
	{ 0xA35E,0x8e, BYTE_LEN, 0 },
	{ 0xA35F,0x74, BYTE_LEN, 0 },
	{ 0xA360,0x5a, BYTE_LEN, 0 },
	{ 0xA361,0x33, BYTE_LEN, 0 },
	{ 0xA362,0x19, BYTE_LEN, 0 },
	{ 0xA363,0xC3, BYTE_LEN, 0 },
	{ 0xA364,0x2c, BYTE_LEN, 0 },
	{ 0xA365,0x06, BYTE_LEN, 0 },
	{ 0xA366,0x34, BYTE_LEN, 0 },
	{ 0xA367,0xC3, BYTE_LEN, 0 },
	{ 0xA368,0x11, BYTE_LEN, 0 },
	{ 0xA369,0x4e, BYTE_LEN, 0 },
	{ 0xA36A,0x77, BYTE_LEN, 0 },
	{ 0xA36B,0xCc, BYTE_LEN, 0 },
	{ 0xA36C,0xE3, BYTE_LEN, 0 },
	{ 0xA36D,0x1d, BYTE_LEN, 0 },
	{ 0xA36E,0xE8, BYTE_LEN, 0 },
	{ 0xA36F,0x24, BYTE_LEN, 0 },
	{ 0xA370,0x07, BYTE_LEN, 0 },
	{ 0xA371,0x39, BYTE_LEN, 0 },
	{ 0xA372,0xCe, BYTE_LEN, 0 },
	{ 0xA373,0xC1, BYTE_LEN, 0 },
	{ 0xA374,0x4e, BYTE_LEN, 0 },
	{ 0xA375,0x73, BYTE_LEN, 0 },
	{ 0xA376,0x42, BYTE_LEN, 0 },
	{ 0xA377,0xD3, BYTE_LEN, 0 },
	{ 0xA378,0x9c, BYTE_LEN, 0 },
	{ 0xA379,0xE8, BYTE_LEN, 0 },
	{ 0xA37A,0x0c, BYTE_LEN, 0 },
	{ 0xA37B,0x07, BYTE_LEN, 0 },
	{ 0xA37C,0x38, BYTE_LEN, 0 },
	{ 0xA37D,0xBc, BYTE_LEN, 0 },
	{ 0xA37E,0x09, BYTE_LEN, 0 },
	{ 0xA37F,0xCe, BYTE_LEN, 0 },
	{ 0xA380,0x6f, BYTE_LEN, 0 },
	{ 0xA381,0x32, BYTE_LEN, 0 },
	{ 0xA382,0x33, BYTE_LEN, 0 },
	{ 0xA383,0x15, BYTE_LEN, 0 },
	{ 0xA384,0xB8, BYTE_LEN, 0 },
	{ 0xA385,0xB4, BYTE_LEN, 0 },
	{ 0xA386,0x65, BYTE_LEN, 0 },
	{ 0xA387,0x2c, BYTE_LEN, 0 },
	{ 0xA388,0x53, BYTE_LEN, 0 },
	{ 0xA389,0x81, BYTE_LEN, 0 },
	{ 0xA38A,0x4b, BYTE_LEN, 0 },
	{ 0xA38B,0x5b, BYTE_LEN, 0 },
	{ 0xA38C,0xC6, BYTE_LEN, 0 },
	{ 0xA38D,0x52, BYTE_LEN, 0 },
	{ 0xA38E,0x96, BYTE_LEN, 0 },
	{ 0xA38F,0xB2, BYTE_LEN, 0 },
	{ 0xA390,0xA4, BYTE_LEN, 0 },
	{ 0xA391,0xE5, BYTE_LEN, 0 },
	{ 0xA392,0x2c, BYTE_LEN, 0 },
	{ 0xA393,0x4b, BYTE_LEN, 0 },
	{ 0xA394,0xC9, BYTE_LEN, 0 },
	{ 0xA395,0xCb, BYTE_LEN, 0 },
	{ 0xA396,0x5f, BYTE_LEN, 0 },
	{ 0xA397,0xF4, BYTE_LEN, 0 },
	{ 0xA398,0x12, BYTE_LEN, 0 },
	{ 0xA399,0x17, BYTE_LEN, 0 },
	{ 0xA39A,0xB8, BYTE_LEN, 0 },
	{ 0xA39B,0xC4, BYTE_LEN, 0 },
	{ 0xA39C,0xA5, BYTE_LEN, 0 },
	{ 0xA39D,0x2e, BYTE_LEN, 0 },
	{ 0xA39E,0x76, BYTE_LEN, 0 },
	{ 0xA39F,0x61, BYTE_LEN, 0 },
	{ 0xA3A0,0x0b, BYTE_LEN, 0 },
	{ 0xA3A1,0x5d, BYTE_LEN, 0 },
	{ 0xA3A2,0xF0, BYTE_LEN, 0 },
	{ 0xA3A3,0x42, BYTE_LEN, 0 },
	{ 0xA3A4,0x96, BYTE_LEN, 0 },
	{ 0xA3A5,0xAa, BYTE_LEN, 0 },
	{ 0xA3A6,0x44, BYTE_LEN, 0 },
	{ 0xA3A7,0x85, BYTE_LEN, 0 },
	{ 0xA3A8,0x2a, BYTE_LEN, 0 },
	{ 0xA3A9,0x5d, BYTE_LEN, 0 },
	{ 0xA3AA,0x79, BYTE_LEN, 0 },
	{ 0xA3AB,0x8b, BYTE_LEN, 0 },
	{ 0xA3AC,0x59, BYTE_LEN, 0 },
	{ 0xA3AD,0xCe, BYTE_LEN, 0 },
	{ 0xA3AE,0x12, BYTE_LEN, 0 },
	{ 0xA3AF,0x96, BYTE_LEN, 0 },
	{ 0xA3B0,0xA5, BYTE_LEN, 0 },
	{ 0xA3B1,0xDc, BYTE_LEN, 0 },
	{ 0xA3B2,0xC4, BYTE_LEN, 0 },
	{ 0xA3B3,0x25, BYTE_LEN, 0 },
	{ 0xA3B4,0x34, BYTE_LEN, 0 },
	{ 0xA3B5,0x19, BYTE_LEN, 0 },
	{ 0xA3B6,0x8a, BYTE_LEN, 0 },
	{ 0xA3B7,0x56, BYTE_LEN, 0 },
	{ 0xA3B8,0xBa, BYTE_LEN, 0 },
	{ 0xA3B9,0xD2, BYTE_LEN, 0 },
	{ 0xA3BA,0x15, BYTE_LEN, 0 },
	{ 0xA3BB,0xA8, BYTE_LEN, 0 },
	{ 0xA3BC,0xC8, BYTE_LEN, 0 },
	{ 0xA3BD,0x04, BYTE_LEN, 0 },
	{ 0xA3BE,0x23, BYTE_LEN, 0 },
	{ 0xA3BF,0x0e, BYTE_LEN, 0 },
	{ 0xA3C0,0xA1, BYTE_LEN, 0 },
	{ 0xA3C1,0xC8, BYTE_LEN, 0 },
	{ 0xA3C2,0x4a, BYTE_LEN, 0 },
	{ 0xA3C3,0x8c, BYTE_LEN, 0 },
	{ 0xA3C4,0xF2, BYTE_LEN, 0 },
	{ 0xA3C5,0x94, BYTE_LEN, 0 },
	{ 0xA3C6,0xA8, BYTE_LEN, 0 },
	{ 0xA3C7,0x18, BYTE_LEN, 0 },
	{ 0xA3C8,0x85, BYTE_LEN, 0 },
	{ 0xA3C9,0x24, BYTE_LEN, 0 },
	{ 0xA3CA,0x09, BYTE_LEN, 0 },
	{ 0xA3CB,0x01, BYTE_LEN, 0 },
	{ 0xA3CC,0x88, BYTE_LEN, 0 },
	{ 0xA3CD,0x41, BYTE_LEN, 0 },
	{ 0xA3CE,0x3a, BYTE_LEN, 0 },
	{ 0xA3CF,0x82, BYTE_LEN, 0 },
	{ 0xA3D0,0x13, BYTE_LEN, 0 },
	{ 0xA3D1,0xA0, BYTE_LEN, 0 },
	{ 0xA3D2,0x4c, BYTE_LEN, 0 },
	{ 0xA3D3,0xE5, BYTE_LEN, 0 },
	{ 0xA3D4,0x28, BYTE_LEN, 0 },
	{ 0xA3D5,0x23, BYTE_LEN, 0 },
	{ 0xA3D6,0x41, BYTE_LEN, 0 },
	{ 0xA3D7,0xC8, BYTE_LEN, 0 },
	{ 0xA3D8,0x3f, BYTE_LEN, 0 },
	{ 0xA3D9,0x08, BYTE_LEN, 0 },
	{ 0xA3DA,0xB2, BYTE_LEN, 0 },
	{ 0xA3DB,0x11, BYTE_LEN, 0 },
	{ 0xA3DC,0x9b, BYTE_LEN, 0 },
	{ 0xA3DD,0xF8, BYTE_LEN, 0 },
	{ 0xA3DE,0x24, BYTE_LEN, 0 },
	{ 0xA3DF,0x2c, BYTE_LEN, 0 },
	{ 0xA3E0,0x54, BYTE_LEN, 0 },
	{ 0xA3E1,0x99, BYTE_LEN, 0 },
	{ 0xA3E2,0x89, BYTE_LEN, 0 },
	{ 0xA3E3,0x45, BYTE_LEN, 0 },
	{ 0xA3E4,0x18, BYTE_LEN, 0 },
	{ 0xA3E5,0x02, BYTE_LEN, 0 },
	{ 0xA3E6,0x91, BYTE_LEN, 0 },
	{ 0xA3E7,0x94, BYTE_LEN, 0 },
	{ 0xA3E8,0x0c, BYTE_LEN, 0 },
	{ 0xA3E9,0x65, BYTE_LEN, 0 },
	{ 0xA3EA,0x29, BYTE_LEN, 0 },
	{ 0xA3EB,0x6f, BYTE_LEN, 0 },
	{ 0xA3EC,0x31, BYTE_LEN, 0 },
	{ 0xA3ED,0x4b, BYTE_LEN, 0 },
	{ 0xA3EE,0x53, BYTE_LEN, 0 },
	{ 0xA3EF,0x6a, BYTE_LEN, 0 },
	{ 0xA3F0,0xC2, BYTE_LEN, 0 },
	{ 0xA3F1,0x92, BYTE_LEN, 0 },
	{ 0xA3F2,0x97, BYTE_LEN, 0 },
	{ 0xA3F3,0xFc, BYTE_LEN, 0 },
	{ 0xA3F4,0x64, BYTE_LEN, 0 },
	{ 0xA3F5,0x2a, BYTE_LEN, 0 },
	{ 0xA3F6,0x56, BYTE_LEN, 0 },
	{ 0xA3F7,0xD1, BYTE_LEN, 0 },
	{ 0xA3F8,0x8b, BYTE_LEN, 0 },
	{ 0xA3F9,0x5f, BYTE_LEN, 0 },
	{ 0xA3FA,0xD2, BYTE_LEN, 0 },
	{ 0xA3FB,0x72, BYTE_LEN, 0 },
	{ 0xA3FC,0x15, BYTE_LEN, 0 },
	{ 0xA3FD,0xA7, BYTE_LEN, 0 },
	{ 0xA3FE,0x40, BYTE_LEN, 0 },
	{ 0xA3FF,0x45, BYTE_LEN, 0 },
	{ 0xA400,0x2b, BYTE_LEN, 0 },
	{ 0xA401,0x6b, BYTE_LEN, 0 },
	{ 0xA402,0x19, BYTE_LEN, 0 },
	{ 0xA403,0xCb, BYTE_LEN, 0 },
	{ 0xA404,0x5f, BYTE_LEN, 0 },
	{ 0xA405,0x0a, BYTE_LEN, 0 },
	{ 0xA406,0x03, BYTE_LEN, 0 },
	{ 0xA407,0x18, BYTE_LEN, 0 },
	{ 0xA408,0xBc, BYTE_LEN, 0 },
	{ 0xA409,0xB0, BYTE_LEN, 0 },
	{ 0xA40A,0x25, BYTE_LEN, 0 },
	{ 0xA40B,0x2d, BYTE_LEN, 0 },
	{ 0xA40C,0x6f, BYTE_LEN, 0 },
	{ 0xA40D,0xA1, BYTE_LEN, 0 },
	{ 0xA40E,0x8b, BYTE_LEN, 0 },
	{ 0xA40F,0x5a, BYTE_LEN, 0 },
	{ 0xA410,0xAc, BYTE_LEN, 0 },
	{ 0xA411,0x12, BYTE_LEN, 0 },
	{ 0xA412,0x97, BYTE_LEN, 0 },
	{ 0xA413,0xB9, BYTE_LEN, 0 },
	{ 0xA414,0xAc, BYTE_LEN, 0 },
	{ 0xA415,0x25, BYTE_LEN, 0 },
	{ 0xA416,0x2c, BYTE_LEN, 0 },
	{ 0xA417,0x5a, BYTE_LEN, 0 },
	{ 0xA418,0x11, BYTE_LEN, 0 },
	{ 0xA419,0x0b, BYTE_LEN, 0 },
	{ 0xA41A,0x59, BYTE_LEN, 0 },
	{ 0xA41B,0x8e, BYTE_LEN, 0 },
	{ 0xA41C,0x02, BYTE_LEN, 0 },
	{ 0xA41D,0x00, BYTE_LEN, 0 },
	{ 0xA41E,0x00, BYTE_LEN, 0 },
	{ 0xA41F,0x00, BYTE_LEN, 0 },
	{ 0xA420,0x00, BYTE_LEN, 0 },
	{ 0xA421,0x0a, BYTE_LEN, 0 },

	{ 0x0068,0x5F, BYTE_LEN, 0 },
};

/*SHD_MIN*/
struct isx006_i2c_reg_conf isx006_SHD_TYP_settings[] = {
	{ 0x0068,0x50, BYTE_LEN, 0 },

	{ 0x9000,0x8282, WORD_LEN, 0 },//CXC_valid_code
	{ 0x9002,0x01, BYTE_LEN, 0 },
	{ 0x9003,0x10, BYTE_LEN, 0 },
	{ 0x9004,0x04, BYTE_LEN, 0 },
	{ 0x9005,0x40, BYTE_LEN, 0 },
	{ 0x9006,0x10, BYTE_LEN, 0 },
	{ 0x9007,0x00, BYTE_LEN, 0 },
	{ 0x9008,0x41, BYTE_LEN, 0 },
	{ 0x9009,0x80, BYTE_LEN, 0 },
	{ 0x900A,0x04, BYTE_LEN, 0 },
	{ 0x900B,0x00, BYTE_LEN, 0 },
	{ 0x900C,0x12, BYTE_LEN, 0 },
	{ 0x900D,0x04, BYTE_LEN, 0 },
	{ 0x900E,0x50, BYTE_LEN, 0 },
	{ 0x900F,0x10, BYTE_LEN, 0 },
	{ 0x9010,0x20, BYTE_LEN, 0 },
	{ 0x9011,0x81, BYTE_LEN, 0 },
	{ 0x9012,0x80, BYTE_LEN, 0 },
	{ 0x9013,0x04, BYTE_LEN, 0 },
	{ 0x9014,0x02, BYTE_LEN, 0 },
	{ 0x9015,0x12, BYTE_LEN, 0 },
	{ 0x9016,0x04, BYTE_LEN, 0 },
	{ 0x9017,0x40, BYTE_LEN, 0 },
	{ 0x9018,0x10, BYTE_LEN, 0 },
	{ 0x9019,0x00, BYTE_LEN, 0 },
	{ 0x901A,0x41, BYTE_LEN, 0 },
	{ 0x901B,0x00, BYTE_LEN, 0 },
	{ 0x901C,0x04, BYTE_LEN, 0 },
	{ 0x901D,0x01, BYTE_LEN, 0 },
	{ 0x901E,0x12, BYTE_LEN, 0 },
	{ 0x901F,0x00, BYTE_LEN, 0 },
	{ 0x9020,0x48, BYTE_LEN, 0 },
	{ 0x9021,0x10, BYTE_LEN, 0 },
	{ 0x9022,0x40, BYTE_LEN, 0 },
	{ 0x9023,0x41, BYTE_LEN, 0 },
	{ 0x9024,0x80, BYTE_LEN, 0 },
	{ 0x9025,0x04, BYTE_LEN, 0 },
	{ 0x9026,0x02, BYTE_LEN, 0 },
	{ 0x9027,0x12, BYTE_LEN, 0 },
	{ 0x9028,0x08, BYTE_LEN, 0 },
	{ 0x9029,0x48, BYTE_LEN, 0 },
	{ 0x902A,0x10, BYTE_LEN, 0 },
	{ 0x902B,0xE0, BYTE_LEN, 0 },
	{ 0x902C,0x40, BYTE_LEN, 0 },
	{ 0x902D,0x80, BYTE_LEN, 0 },
	{ 0x902E,0x03, BYTE_LEN, 0 },
	{ 0x902F,0x00, BYTE_LEN, 0 },
	{ 0x9030,0x0a, BYTE_LEN, 0 },
	{ 0x9031,0x04, BYTE_LEN, 0 },
	{ 0x9032,0x38, BYTE_LEN, 0 },
	{ 0x9033,0x30, BYTE_LEN, 0 },
	{ 0x9034,0xE0, BYTE_LEN, 0 },
	{ 0x9035,0x80, BYTE_LEN, 0 },
	{ 0x9036,0x80, BYTE_LEN, 0 },
	{ 0x9037,0x03, BYTE_LEN, 0 },
	{ 0x9038,0x01, BYTE_LEN, 0 },
	{ 0x9039,0x12, BYTE_LEN, 0 },
	{ 0x903A,0x0c, BYTE_LEN, 0 },
	{ 0x903B,0x50, BYTE_LEN, 0 },
	{ 0x903C,0x30, BYTE_LEN, 0 },
	{ 0x903D,0x40, BYTE_LEN, 0 },
	{ 0x903E,0xC1, BYTE_LEN, 0 },
	{ 0x903F,0x00, BYTE_LEN, 0 },
	{ 0x9040,0x03, BYTE_LEN, 0 },
	{ 0x9041,0x03, BYTE_LEN, 0 },
	{ 0x9042,0x0c, BYTE_LEN, 0 },
	{ 0x9043,0x0c, BYTE_LEN, 0 },
	{ 0x9044,0x28, BYTE_LEN, 0 },
	{ 0x9045,0x10, BYTE_LEN, 0 },
	{ 0x9046,0x60, BYTE_LEN, 0 },
	{ 0x9047,0x40, BYTE_LEN, 0 },
	{ 0x9048,0x00, BYTE_LEN, 0 },
	{ 0x9049,0x02, BYTE_LEN, 0 },
	{ 0x904A,0x01, BYTE_LEN, 0 },
	{ 0x904B,0x0c, BYTE_LEN, 0 },
	{ 0x904C,0x08, BYTE_LEN, 0 },
	{ 0x904D,0x30, BYTE_LEN, 0 },
	{ 0x904E,0x20, BYTE_LEN, 0 },
	{ 0x904F,0xE0, BYTE_LEN, 0 },
	{ 0x9050,0x80, BYTE_LEN, 0 },
	{ 0x9051,0x80, BYTE_LEN, 0 },
	{ 0x9052,0x03, BYTE_LEN, 0 },
	{ 0x9053,0x03, BYTE_LEN, 0 },
	{ 0x9054,0x06, BYTE_LEN, 0 },
	{ 0x9055,0x0c, BYTE_LEN, 0 },
	{ 0x9056,0x18, BYTE_LEN, 0 },
	{ 0x9057,0x20, BYTE_LEN, 0 },
	{ 0x9058,0x60, BYTE_LEN, 0 },
	{ 0x9059,0xC0, BYTE_LEN, 0 },
	{ 0x905A,0x00, BYTE_LEN, 0 },
	{ 0x905B,0x01, BYTE_LEN, 0 },
	{ 0x905C,0x02, BYTE_LEN, 0 },
	{ 0x905D,0x02, BYTE_LEN, 0 },
	{ 0x905E,0x08, BYTE_LEN, 0 },
	{ 0x905F,0x10, BYTE_LEN, 0 },
	{ 0x9060,0x30, BYTE_LEN, 0 },
	{ 0x9061,0x80, BYTE_LEN, 0 },
	{ 0x9062,0x80, BYTE_LEN, 0 },
	{ 0x9063,0x80, BYTE_LEN, 0 },
	{ 0x9064,0x02, BYTE_LEN, 0 },
	{ 0x9065,0x02, BYTE_LEN, 0 },
	{ 0x9066,0x0a, BYTE_LEN, 0 },
	{ 0x9067,0x08, BYTE_LEN, 0 },
	{ 0x9068,0x10, BYTE_LEN, 0 },
	{ 0x9069,0x20, BYTE_LEN, 0 },
	{ 0x906A,0x40, BYTE_LEN, 0 },
	{ 0x906B,0x40, BYTE_LEN, 0 },
	{ 0x906C,0x80, BYTE_LEN, 0 },
	{ 0x906D,0x00, BYTE_LEN, 0 },
	{ 0x906E,0x02, BYTE_LEN, 0 },
	{ 0x906F,0x00, BYTE_LEN, 0 },
	{ 0x9070,0x08, BYTE_LEN, 0 },
	{ 0x9071,0x08, BYTE_LEN, 0 },
	{ 0x9072,0x20, BYTE_LEN, 0 },
	{ 0x9073,0x00, BYTE_LEN, 0 },
	{ 0x9074,0x80, BYTE_LEN, 0 },
	{ 0x9075,0x00, BYTE_LEN, 0 },
	{ 0x9076,0x01, BYTE_LEN, 0 },
	{ 0x9077,0x02, BYTE_LEN, 0 },
	{ 0x9078,0x0a, BYTE_LEN, 0 },
	{ 0x9079,0x08, BYTE_LEN, 0 },
	{ 0x907A,0x28, BYTE_LEN, 0 },
	{ 0x907B,0x30, BYTE_LEN, 0 },
	{ 0x907C,0x40, BYTE_LEN, 0 },
	{ 0x907D,0xC0, BYTE_LEN, 0 },
	{ 0x907E,0x00, BYTE_LEN, 0 },
	{ 0x907F,0x01, BYTE_LEN, 0 },
	{ 0x9080,0x03, BYTE_LEN, 0 },
	{ 0x9081,0xFe, BYTE_LEN, 0 },
	{ 0x9082,0x0b, BYTE_LEN, 0 },
	{ 0x9083,0xF8, BYTE_LEN, 0 },
	{ 0x9084,0x2f, BYTE_LEN, 0 },
	{ 0x9085,0x00, BYTE_LEN, 0 },
	{ 0x9086,0x80, BYTE_LEN, 0 },
	{ 0x9087,0x00, BYTE_LEN, 0 },
	{ 0x9088,0x00, BYTE_LEN, 0 },
	{ 0x9089,0x01, BYTE_LEN, 0 },
	{ 0x908A,0x02, BYTE_LEN, 0 },
	{ 0x908B,0x04, BYTE_LEN, 0 },
	{ 0x908C,0x20, BYTE_LEN, 0 },
	{ 0x908D,0x10, BYTE_LEN, 0 },
	{ 0x908E,0x80, BYTE_LEN, 0 },
	{ 0x908F,0x80, BYTE_LEN, 0 },
	{ 0x9090,0x80, BYTE_LEN, 0 },
	{ 0x9091,0x01, BYTE_LEN, 0 },
	{ 0x9092,0x02, BYTE_LEN, 0 },
	{ 0x9093,0x06, BYTE_LEN, 0 },
	{ 0x9094,0x14, BYTE_LEN, 0 },
	{ 0x9095,0x00, BYTE_LEN, 0 },
	{ 0x9096,0x10, BYTE_LEN, 0 },
	{ 0x9097,0xE0, BYTE_LEN, 0 },
	{ 0x9098,0xBf, BYTE_LEN, 0 },
	{ 0x9099,0x80, BYTE_LEN, 0 },
	{ 0x909A,0xFf, BYTE_LEN, 0 },
	{ 0x909B,0x04, BYTE_LEN, 0 },
	{ 0x909C,0xFe, BYTE_LEN, 0 },
	{ 0x909D,0x0b, BYTE_LEN, 0 },
	{ 0x909E,0x00, BYTE_LEN, 0 },
	{ 0x909F,0x20, BYTE_LEN, 0 },
	{ 0x90A0,0x40, BYTE_LEN, 0 },
	{ 0x90A1,0x80, BYTE_LEN, 0 },
	{ 0x90A2,0x00, BYTE_LEN, 0 },
	{ 0x90A3,0x01, BYTE_LEN, 0 },
	{ 0x90A4,0x03, BYTE_LEN, 0 },
	{ 0x90A5,0x04, BYTE_LEN, 0 },
	{ 0x90A6,0x0c, BYTE_LEN, 0 },
	{ 0x90A7,0x10, BYTE_LEN, 0 },
	{ 0x90A8,0x40, BYTE_LEN, 0 },
	{ 0x90A9,0x20, BYTE_LEN, 0 },
	{ 0x90AA,0x40, BYTE_LEN, 0 },
	{ 0x90AB,0x01, BYTE_LEN, 0 },
	{ 0x90AC,0x00, BYTE_LEN, 0 },
	{ 0x90AD,0x05, BYTE_LEN, 0 },
	{ 0x90AE,0x00, BYTE_LEN, 0 },
	{ 0x90AF,0x10, BYTE_LEN, 0 },
	{ 0x90B0,0x08, BYTE_LEN, 0 },
	{ 0x90B1,0x30, BYTE_LEN, 0 },
	{ 0x90B2,0x40, BYTE_LEN, 0 },
	{ 0x90B3,0x00, BYTE_LEN, 0 },
	{ 0x90B4,0x01, BYTE_LEN, 0 },
	{ 0x90B5,0x02, BYTE_LEN, 0 },
	{ 0x90B6,0x04, BYTE_LEN, 0 },
	{ 0x90B7,0x08, BYTE_LEN, 0 },
	{ 0x90B8,0x00, BYTE_LEN, 0 },
	{ 0x90B9,0x18, BYTE_LEN, 0 },
	{ 0x90BA,0x00, BYTE_LEN, 0 },
	{ 0x90BB,0x60, BYTE_LEN, 0 },
	{ 0x90BC,0xC0, BYTE_LEN, 0 },
	{ 0x90BD,0x00, BYTE_LEN, 0 },
	{ 0x90BE,0x01, BYTE_LEN, 0 },
	{ 0x90BF,0x02, BYTE_LEN, 0 },
	{ 0x90C0,0x06, BYTE_LEN, 0 },
	{ 0x90C1,0x18, BYTE_LEN, 0 },
	{ 0x90C2,0x20, BYTE_LEN, 0 },
	{ 0x90C3,0x50, BYTE_LEN, 0 },
	{ 0x90C4,0x60, BYTE_LEN, 0 },
	{ 0x90C5,0x40, BYTE_LEN, 0 },
	{ 0x90C6,0x81, BYTE_LEN, 0 },
	{ 0x90C7,0x01, BYTE_LEN, 0 },
	{ 0x90C8,0x05, BYTE_LEN, 0 },
	{ 0x90C9,0x06, BYTE_LEN, 0 },
	{ 0x90CA,0x14, BYTE_LEN, 0 },
	{ 0x90CB,0x18, BYTE_LEN, 0 },
	{ 0x90CC,0x20, BYTE_LEN, 0 },
	{ 0x90CD,0x80, BYTE_LEN, 0 },
	{ 0x90CE,0x80, BYTE_LEN, 0 },
	{ 0x90CF,0x00, BYTE_LEN, 0 },
	{ 0x90D0,0x02, BYTE_LEN, 0 },
	{ 0x90D1,0x06, BYTE_LEN, 0 },
	{ 0x90D2,0x0a, BYTE_LEN, 0 },
	{ 0x90D3,0x08, BYTE_LEN, 0 },
	{ 0x90D4,0x20, BYTE_LEN, 0 },
	{ 0x90D5,0x50, BYTE_LEN, 0 },
	{ 0x90D6,0xA0, BYTE_LEN, 0 },
	{ 0x90D7,0xC0, BYTE_LEN, 0 },
	{ 0x90D8,0x80, BYTE_LEN, 0 },
	{ 0x90D9,0x02, BYTE_LEN, 0 },
	{ 0x90DA,0x04, BYTE_LEN, 0 },
	{ 0x90DB,0x0a, BYTE_LEN, 0 },
	{ 0x90DC,0x08, BYTE_LEN, 0 },
	{ 0x90DD,0x30, BYTE_LEN, 0 },
	{ 0x90DE,0x20, BYTE_LEN, 0 },
	{ 0x90DF,0xC0, BYTE_LEN, 0 },
	{ 0x90E0,0x80, BYTE_LEN, 0 },
	{ 0x90E1,0x00, BYTE_LEN, 0 },
	{ 0x90E2,0x02, BYTE_LEN, 0 },
	{ 0x90E3,0x02, BYTE_LEN, 0 },
	{ 0x90E4,0x08, BYTE_LEN, 0 },
	{ 0x90E5,0x18, BYTE_LEN, 0 },
	{ 0x90E6,0x28, BYTE_LEN, 0 },
	{ 0x90E7,0x20, BYTE_LEN, 0 },
	{ 0x90E8,0x80, BYTE_LEN, 0 },
	{ 0x90E9,0x40, BYTE_LEN, 0 },
	{ 0x90EA,0x81, BYTE_LEN, 0 },
	{ 0x90EB,0x02, BYTE_LEN, 0 },
	{ 0x90EC,0x03, BYTE_LEN, 0 },
	{ 0x90ED,0x0a, BYTE_LEN, 0 },
	{ 0x90EE,0x10, BYTE_LEN, 0 },
	{ 0x90EF,0x28, BYTE_LEN, 0 },
	{ 0x90F0,0x20, BYTE_LEN, 0 },
	{ 0x90F1,0xC0, BYTE_LEN, 0 },
	{ 0x90F2,0x80, BYTE_LEN, 0 },
	{ 0x90F3,0x00, BYTE_LEN, 0 },
	{ 0x90F4,0x03, BYTE_LEN, 0 },
	{ 0x90F5,0x01, BYTE_LEN, 0 },
	{ 0x90F6,0xF0, BYTE_LEN, 0 },
	{ 0x90F7,0x07, BYTE_LEN, 0 },
	{ 0x90F8,0xC0, BYTE_LEN, 0 },
	{ 0x90F9,0x1f, BYTE_LEN, 0 },
	{ 0x90FA,0xC0, BYTE_LEN, 0 },
	{ 0x90FB,0x3e, BYTE_LEN, 0 },
	{ 0x90FC,0x00, BYTE_LEN, 0 },
	{ 0x90FD,0xFd, BYTE_LEN, 0 },
	{ 0x90FE,0xFf, BYTE_LEN, 0 },
	{ 0x90FF,0xF1, BYTE_LEN, 0 },
	{ 0x9100,0x03, BYTE_LEN, 0 },
	{ 0x9101,0xB8, BYTE_LEN, 0 },
	{ 0x9102,0x0f, BYTE_LEN, 0 },
	{ 0x9103,0x40, BYTE_LEN, 0 },
	{ 0x9104,0x3f, BYTE_LEN, 0 },
	{ 0x9105,0x80, BYTE_LEN, 0 },
	{ 0x9106,0xFa, BYTE_LEN, 0 },
	{ 0x9107,0x00, BYTE_LEN, 0 },
	{ 0x9108,0xEa, BYTE_LEN, 0 },
	{ 0x9109,0x07, BYTE_LEN, 0 },
	{ 0x910A,0xC0, BYTE_LEN, 0 },
	{ 0x910B,0x1f, BYTE_LEN, 0 },
	{ 0x910C,0x00, BYTE_LEN, 0 },
	{ 0x910D,0x7f, BYTE_LEN, 0 },
	{ 0x910E,0x00, BYTE_LEN, 0 },
	{ 0x910F,0xFb, BYTE_LEN, 0 },
	{ 0x9110,0x00, BYTE_LEN, 0 },
	{ 0x9111,0xF4, BYTE_LEN, 0 },
	{ 0x9112,0xFf, BYTE_LEN, 0 },
	{ 0x9113,0xC7, BYTE_LEN, 0 },
	{ 0x9114,0x0f, BYTE_LEN, 0 },
	{ 0x9115,0xE0, BYTE_LEN, 0 },
	{ 0x9116,0x3e, BYTE_LEN, 0 },
	{ 0x9117,0x00, BYTE_LEN, 0 },
	{ 0x9118,0xFd, BYTE_LEN, 0 },
	{ 0x9119,0x00, BYTE_LEN, 0 },
	{ 0x911A,0xEa, BYTE_LEN, 0 },
	{ 0x911B,0x03, BYTE_LEN, 0 },
	{ 0x911C,0xA8, BYTE_LEN, 0 },
	{ 0x911D,0x2f, BYTE_LEN, 0 },
	{ 0x911E,0x40, BYTE_LEN, 0 },
	{ 0x911F,0xBf, BYTE_LEN, 0 },
	{ 0x9120,0x00, BYTE_LEN, 0 },
	{ 0x9121,0xFd, BYTE_LEN, 0 },
	{ 0x9122,0x01, BYTE_LEN, 0 },
	{ 0x9123,0xEc, BYTE_LEN, 0 },
	{ 0x9124,0x03, BYTE_LEN, 0 },
	{ 0x9125,0xA8, BYTE_LEN, 0 },
	{ 0x9126,0x0f, BYTE_LEN, 0 },
	{ 0x9127,0x20, BYTE_LEN, 0 },
	{ 0x9128,0xFf, BYTE_LEN, 0 },
	{ 0x9129,0xFf, BYTE_LEN, 0 },
	{ 0x912A,0xFc, BYTE_LEN, 0 },
	{ 0x912B,0x01, BYTE_LEN, 0 },
	{ 0x912C,0xF4, BYTE_LEN, 0 },
	{ 0x912D,0x07, BYTE_LEN, 0 },
	{ 0x912E,0xB0, BYTE_LEN, 0 },
	{ 0x912F,0x1f, BYTE_LEN, 0 },
	{ 0x9130,0xC0, BYTE_LEN, 0 },
	{ 0x9131,0x7e, BYTE_LEN, 0 },
	{ 0x9132,0x00, BYTE_LEN, 0 },
	{ 0x9133,0xFb, BYTE_LEN, 0 },
	{ 0x9134,0x01, BYTE_LEN, 0 },
	{ 0x9135,0xEc, BYTE_LEN, 0 },
	{ 0x9136,0x03, BYTE_LEN, 0 },
	{ 0x9137,0xB8, BYTE_LEN, 0 },
	{ 0x9138,0xFf, BYTE_LEN, 0 },
	{ 0x9139,0x1f, BYTE_LEN, 0 },
	{ 0x913A,0xBf, BYTE_LEN, 0 },
	{ 0x913B,0xFf, BYTE_LEN, 0 },
	{ 0x913C,0xFb, BYTE_LEN, 0 },
	{ 0x913D,0x00, BYTE_LEN, 0 },
	{ 0x913E,0xEc, BYTE_LEN, 0 },
	{ 0x913F,0xFf, BYTE_LEN, 0 },
	{ 0x9140,0xBf, BYTE_LEN, 0 },
	{ 0x9141,0x0f, BYTE_LEN, 0 },
	{ 0x9142,0x40, BYTE_LEN, 0 },
	{ 0x9143,0x3f, BYTE_LEN, 0 },
	{ 0x9144,0x00, BYTE_LEN, 0 },
	{ 0x9145,0xFd, BYTE_LEN, 0 },
	{ 0x9146,0x00, BYTE_LEN, 0 },
	{ 0x9147,0xE8, BYTE_LEN, 0 },
	{ 0x9148,0x03, BYTE_LEN, 0 },
	{ 0x9149,0xA0, BYTE_LEN, 0 },
	{ 0x914A,0xFf, BYTE_LEN, 0 },
	{ 0x914B,0x3f, BYTE_LEN, 0 },
	{ 0x914C,0xFf, BYTE_LEN, 0 },
	{ 0x914D,0xFf, BYTE_LEN, 0 },
	{ 0x914E,0xFd, BYTE_LEN, 0 },
	{ 0x914F,0xFe, BYTE_LEN, 0 },
	{ 0x9150,0xF3, BYTE_LEN, 0 },
	{ 0x9151,0xFb, BYTE_LEN, 0 },
	{ 0x9152,0xC7, BYTE_LEN, 0 },
	{ 0x9153,0x0f, BYTE_LEN, 0 },
	{ 0x9154,0x40, BYTE_LEN, 0 },
	{ 0x9155,0xFf, BYTE_LEN, 0 },
	{ 0x9156,0x7f, BYTE_LEN, 0 },
	{ 0x9157,0xFe, BYTE_LEN, 0 },
	{ 0x9158,0xFf, BYTE_LEN, 0 },
	{ 0x9159,0xF9, BYTE_LEN, 0 },
	{ 0x915A,0x07, BYTE_LEN, 0 },
	{ 0x915B,0xB8, BYTE_LEN, 0 },
	{ 0x915C,0x1f, BYTE_LEN, 0 },
	{ 0x915D,0xE0, BYTE_LEN, 0 },
	{ 0x915E,0x3e, BYTE_LEN, 0 },
	{ 0x915F,0x00, BYTE_LEN, 0 },
	{ 0x9160,0xFd, BYTE_LEN, 0 },
	{ 0x9161,0x00, BYTE_LEN, 0 },
	{ 0x9162,0xF6, BYTE_LEN, 0 },
	{ 0x9163,0xFf, BYTE_LEN, 0 },
	{ 0x9164,0xD7, BYTE_LEN, 0 },
	{ 0x9165,0xEf, BYTE_LEN, 0 },
	{ 0x9166,0xBf, BYTE_LEN, 0 },
	{ 0x9167,0xFf, BYTE_LEN, 0 },
	{ 0x9168,0x7f, BYTE_LEN, 0 },
	{ 0x9169,0xFd, BYTE_LEN, 0 },
	{ 0x916A,0xFf, BYTE_LEN, 0 },
	{ 0x916B,0xFd, BYTE_LEN, 0 },
	{ 0x916C,0xFf, BYTE_LEN, 0 },
	{ 0x916D,0xF7, BYTE_LEN, 0 },
	{ 0x916E,0x4f, BYTE_LEN, 0 },
	{ 0x916F,0xA0, BYTE_LEN, 0 },
	{ 0x9170,0x3f, BYTE_LEN, 0 },
	{ 0x9171,0x81, BYTE_LEN, 0 },
	{ 0x9172,0xFe, BYTE_LEN, 0 },
	{ 0x9173,0x03, BYTE_LEN, 0 },
	{ 0x9174,0xF4, BYTE_LEN, 0 },
	{ 0x9175,0x03, BYTE_LEN, 0 },
	{ 0x9176,0xE8, BYTE_LEN, 0 },
	{ 0x9177,0x0f, BYTE_LEN, 0 },
	{ 0x9178,0x20, BYTE_LEN, 0 },
	{ 0x9179,0x80, BYTE_LEN, 0 },
	{ 0x917A,0x7f, BYTE_LEN, 0 },
	{ 0x917B,0x00, BYTE_LEN, 0 },
	{ 0x917C,0x00, BYTE_LEN, 0 },
	{ 0x917D,0xFe, BYTE_LEN, 0 },
	{ 0x917E,0x0b, BYTE_LEN, 0 },
	{ 0x917F,0x00, BYTE_LEN, 0 },
	{ 0x9180,0x20, BYTE_LEN, 0 },
	{ 0x9181,0x00, BYTE_LEN, 0 },
	{ 0x9182,0x40, BYTE_LEN, 0 },
	{ 0x9183,0x81, BYTE_LEN, 0 },
	{ 0x9184,0x00, BYTE_LEN, 0 },
	{ 0x9185,0x05, BYTE_LEN, 0 },
	{ 0x9186,0x02, BYTE_LEN, 0 },
	{ 0x9187,0x0c, BYTE_LEN, 0 },
	{ 0x9188,0x08, BYTE_LEN, 0 },
	{ 0x9189,0x20, BYTE_LEN, 0 },
	{ 0x918A,0x00, BYTE_LEN, 0 },
	{ 0x918B,0x00, BYTE_LEN, 0 },
	{ 0x918C,0x00, BYTE_LEN, 0 },
	{ 0x918D,0x01, BYTE_LEN, 0 },
	{ 0x918E,0x00, BYTE_LEN, 0 },
	{ 0x918F,0x04, BYTE_LEN, 0 },
	{ 0x9190,0x04, BYTE_LEN, 0 },
	{ 0x9191,0x08, BYTE_LEN, 0 },
	{ 0x9192,0x10, BYTE_LEN, 0 },
	{ 0x9193,0x00, BYTE_LEN, 0 },
	{ 0x9194,0x40, BYTE_LEN, 0 },
	{ 0x9195,0x00, BYTE_LEN, 0 },
	{ 0x9196,0x00, BYTE_LEN, 0 },
	{ 0x9197,0x07, BYTE_LEN, 0 },
	{ 0x9198,0x00, BYTE_LEN, 0 },
	{ 0x9199,0x1c, BYTE_LEN, 0 },
	{ 0x919A,0x00, BYTE_LEN, 0 },
	{ 0x919B,0x40, BYTE_LEN, 0 },
	{ 0x919C,0xA0, BYTE_LEN, 0 },
	{ 0x919D,0x00, BYTE_LEN, 0 },
	{ 0x919E,0x01, BYTE_LEN, 0 },
	{ 0x919F,0x03, BYTE_LEN, 0 },
	{ 0x91A0,0x03, BYTE_LEN, 0 },
	{ 0x91A1,0x0c, BYTE_LEN, 0 },
	{ 0x91A2,0x04, BYTE_LEN, 0 },
	{ 0x91A3,0x28, BYTE_LEN, 0 },
	{ 0x91A4,0x20, BYTE_LEN, 0 },
	{ 0x91A5,0xC0, BYTE_LEN, 0 },
	{ 0x91A6,0xC0, BYTE_LEN, 0 },
	{ 0x91A7,0x00, BYTE_LEN, 0 },
	{ 0x91A8,0x03, BYTE_LEN, 0 },
	{ 0x91A9,0x03, BYTE_LEN, 0 },
	{ 0x91AA,0x0c, BYTE_LEN, 0 },
	{ 0x91AB,0x18, BYTE_LEN, 0 },
	{ 0x91AC,0x28, BYTE_LEN, 0 },
	{ 0x91AD,0x60, BYTE_LEN, 0 },
	{ 0x91AE,0xA0, BYTE_LEN, 0 },
	{ 0x91AF,0x80, BYTE_LEN, 0 },
	{ 0x91B0,0x81, BYTE_LEN, 0 },
	{ 0x91B1,0x02, BYTE_LEN, 0 },
	{ 0x91B2,0x03, BYTE_LEN, 0 },
	{ 0x91B3,0x0c, BYTE_LEN, 0 },
	{ 0x91B4,0x0c, BYTE_LEN, 0 },
	{ 0x91B5,0x40, BYTE_LEN, 0 },
	{ 0x91B6,0x30, BYTE_LEN, 0 },
	{ 0x91B7,0xE0, BYTE_LEN, 0 },
	{ 0x91B8,0xC0, BYTE_LEN, 0 },
	{ 0x91B9,0x80, BYTE_LEN, 0 },
	{ 0x91BA,0x02, BYTE_LEN, 0 },
	{ 0x91BB,0x03, BYTE_LEN, 0 },
	{ 0x91BC,0x14, BYTE_LEN, 0 },
	{ 0x91BD,0x0c, BYTE_LEN, 0 },
	{ 0x91BE,0x50, BYTE_LEN, 0 },
	{ 0x91BF,0x60, BYTE_LEN, 0 },
	{ 0x91C0,0x60, BYTE_LEN, 0 },
	{ 0x91C1,0x80, BYTE_LEN, 0 },
	{ 0x91C2,0x81, BYTE_LEN, 0 },
	{ 0x91C3,0x01, BYTE_LEN, 0 },
	{ 0x91C4,0x06, BYTE_LEN, 0 },
	{ 0x91C5,0x0c, BYTE_LEN, 0 },
	{ 0x91C6,0x10, BYTE_LEN, 0 },
	{ 0x91C7,0x30, BYTE_LEN, 0 },
	{ 0x91C8,0x50, BYTE_LEN, 0 },
	{ 0x91C9,0x00, BYTE_LEN, 0 },
	{ 0x91CA,0x41, BYTE_LEN, 0 },
	{ 0x91CB,0x81, BYTE_LEN, 0 },
	{ 0x91CC,0x04, BYTE_LEN, 0 },
	{ 0x91CD,0x04, BYTE_LEN, 0 },
	{ 0x91CE,0x10, BYTE_LEN, 0 },
	{ 0x91CF,0x10, BYTE_LEN, 0 },
	{ 0x91D0,0x40, BYTE_LEN, 0 },
	{ 0x91D1,0x40, BYTE_LEN, 0 },
	{ 0x91D2,0x00, BYTE_LEN, 0 },
	{ 0x91D3,0x81, BYTE_LEN, 0 },
	{ 0x91D4,0x81, BYTE_LEN, 0 },
	{ 0x91D5,0x01, BYTE_LEN, 0 },
	{ 0x91D6,0x06, BYTE_LEN, 0 },
	{ 0x91D7,0x06, BYTE_LEN, 0 },
	{ 0x91D8,0x18, BYTE_LEN, 0 },
	{ 0x91D9,0x30, BYTE_LEN, 0 },
	{ 0x91DA,0x40, BYTE_LEN, 0 },
	{ 0x91DB,0xC0, BYTE_LEN, 0 },
	{ 0x91DC,0x40, BYTE_LEN, 0 },
	{ 0x91DD,0x01, BYTE_LEN, 0 },
	{ 0x91DE,0x04, BYTE_LEN, 0 },
	{ 0x91DF,0x05, BYTE_LEN, 0 },
	{ 0x91E0,0x12, BYTE_LEN, 0 },
	{ 0x91E1,0x10, BYTE_LEN, 0 },
	{ 0x91E2,0x40, BYTE_LEN, 0 },
	{ 0x91E3,0x40, BYTE_LEN, 0 },
	{ 0x91E4,0x00, BYTE_LEN, 0 },
	{ 0x91E5,0x01, BYTE_LEN, 0 },
	{ 0x91E6,0x01, BYTE_LEN, 0 },
	{ 0x91E7,0x04, BYTE_LEN, 0 },

	{ 0xA000,0x9191, WORD_LEN, 0 },
	{ 0xA002,0x41, BYTE_LEN, 0 },
	{ 0xA003,0x61, BYTE_LEN, 0 },
	{ 0xA004,0x8c, BYTE_LEN, 0 },
	{ 0xA005,0x58, BYTE_LEN, 0 },
	{ 0xA006,0x74, BYTE_LEN, 0 },
	{ 0xA007,0x73, BYTE_LEN, 0 },
	{ 0xA008,0x16, BYTE_LEN, 0 },
	{ 0xA009,0xDf, BYTE_LEN, 0 },
	{ 0xA00A,0x88, BYTE_LEN, 0 },
	{ 0xA00B,0x25, BYTE_LEN, 0 },
	{ 0xA00C,0x37, BYTE_LEN, 0 },
	{ 0xA00D,0x60, BYTE_LEN, 0 },
	{ 0xA00E,0xC9, BYTE_LEN, 0 },
	{ 0xA00F,0x8d, BYTE_LEN, 0 },
	{ 0xA010,0x58, BYTE_LEN, 0 },
	{ 0xA011,0x72, BYTE_LEN, 0 },
	{ 0xA012,0x63, BYTE_LEN, 0 },
	{ 0xA013,0x96, BYTE_LEN, 0 },
	{ 0xA014,0xDe, BYTE_LEN, 0 },
	{ 0xA015,0x88, BYTE_LEN, 0 },
	{ 0xA016,0xC5, BYTE_LEN, 0 },
	{ 0xA017,0x36, BYTE_LEN, 0 },
	{ 0xA018,0x41, BYTE_LEN, 0 },
	{ 0xA019,0x59, BYTE_LEN, 0 },
	{ 0xA01A,0xCc, BYTE_LEN, 0 },
	{ 0xA01B,0x5b, BYTE_LEN, 0 },
	{ 0xA01C,0x90, BYTE_LEN, 0 },
	{ 0xA01D,0x93, BYTE_LEN, 0 },
	{ 0xA01E,0x17, BYTE_LEN, 0 },
	{ 0xA01F,0xE9, BYTE_LEN, 0 },
	{ 0xA020,0xD8, BYTE_LEN, 0 },
	{ 0xA021,0x85, BYTE_LEN, 0 },
	{ 0xA022,0x39, BYTE_LEN, 0 },
	{ 0xA023,0x73, BYTE_LEN, 0 },
	{ 0xA024,0x39, BYTE_LEN, 0 },
	{ 0xA025,0x4e, BYTE_LEN, 0 },
	{ 0xA026,0x5c, BYTE_LEN, 0 },
	{ 0xA027,0x88, BYTE_LEN, 0 },
	{ 0xA028,0x33, BYTE_LEN, 0 },
	{ 0xA029,0x97, BYTE_LEN, 0 },
	{ 0xA02A,0xE3, BYTE_LEN, 0 },
	{ 0xA02B,0xD8, BYTE_LEN, 0 },
	{ 0xA02C,0x65, BYTE_LEN, 0 },
	{ 0xA02D,0x39, BYTE_LEN, 0 },
	{ 0xA02E,0x77, BYTE_LEN, 0 },
	{ 0xA02F,0x81, BYTE_LEN, 0 },
	{ 0xA030,0xCe, BYTE_LEN, 0 },
	{ 0xA031,0x5a, BYTE_LEN, 0 },
	{ 0xA032,0x88, BYTE_LEN, 0 },
	{ 0xA033,0xE3, BYTE_LEN, 0 },
	{ 0xA034,0x16, BYTE_LEN, 0 },
	{ 0xA035,0xE1, BYTE_LEN, 0 },
	{ 0xA036,0xD0, BYTE_LEN, 0 },
	{ 0xA037,0x65, BYTE_LEN, 0 },
	{ 0xA038,0x38, BYTE_LEN, 0 },
	{ 0xA039,0x64, BYTE_LEN, 0 },
	{ 0xA03A,0x31, BYTE_LEN, 0 },
	{ 0xA03B,0x8d, BYTE_LEN, 0 },
	{ 0xA03C,0x56, BYTE_LEN, 0 },
	{ 0xA03D,0x2a, BYTE_LEN, 0 },
	{ 0xA03E,0x63, BYTE_LEN, 0 },
	{ 0xA03F,0x15, BYTE_LEN, 0 },
	{ 0xA040,0xC7, BYTE_LEN, 0 },
	{ 0xA041,0x64, BYTE_LEN, 0 },
	{ 0xA042,0x85, BYTE_LEN, 0 },
	{ 0xA043,0x32, BYTE_LEN, 0 },
	{ 0xA044,0x63, BYTE_LEN, 0 },
	{ 0xA045,0x41, BYTE_LEN, 0 },
	{ 0xA046,0x8d, BYTE_LEN, 0 },
	{ 0xA047,0x5c, BYTE_LEN, 0 },
	{ 0xA048,0x88, BYTE_LEN, 0 },
	{ 0xA049,0x83, BYTE_LEN, 0 },
	{ 0xA04A,0x16, BYTE_LEN, 0 },
	{ 0xA04B,0xDf, BYTE_LEN, 0 },
	{ 0xA04C,0xA8, BYTE_LEN, 0 },
	{ 0xA04D,0xE5, BYTE_LEN, 0 },
	{ 0xA04E,0x35, BYTE_LEN, 0 },
	{ 0xA04F,0x63, BYTE_LEN, 0 },
	{ 0xA050,0xF9, BYTE_LEN, 0 },
	{ 0xA051,0x0c, BYTE_LEN, 0 },
	{ 0xA052,0x53, BYTE_LEN, 0 },
	{ 0xA053,0xF0, BYTE_LEN, 0 },
	{ 0xA054,0xB2, BYTE_LEN, 0 },
	{ 0xA055,0x13, BYTE_LEN, 0 },
	{ 0xA056,0xAd, BYTE_LEN, 0 },
	{ 0xA057,0xD0, BYTE_LEN, 0 },
	{ 0xA058,0x04, BYTE_LEN, 0 },
	{ 0xA059,0x2a, BYTE_LEN, 0 },
	{ 0xA05A,0x3a, BYTE_LEN, 0 },
	{ 0xA05B,0xD9, BYTE_LEN, 0 },
	{ 0xA05C,0xCa, BYTE_LEN, 0 },
	{ 0xA05D,0x52, BYTE_LEN, 0 },
	{ 0xA05E,0xEe, BYTE_LEN, 0 },
	{ 0xA05F,0x02, BYTE_LEN, 0 },
	{ 0xA060,0x96, BYTE_LEN, 0 },
	{ 0xA061,0xCe, BYTE_LEN, 0 },
	{ 0xA062,0x90, BYTE_LEN, 0 },
	{ 0xA063,0x45, BYTE_LEN, 0 },
	{ 0xA064,0x35, BYTE_LEN, 0 },
	{ 0xA065,0x5f, BYTE_LEN, 0 },
	{ 0xA066,0xA9, BYTE_LEN, 0 },
	{ 0xA067,0x4c, BYTE_LEN, 0 },
	{ 0xA068,0x54, BYTE_LEN, 0 },
	{ 0xA069,0xF8, BYTE_LEN, 0 },
	{ 0xA06A,0x32, BYTE_LEN, 0 },
	{ 0xA06B,0x93, BYTE_LEN, 0 },
	{ 0xA06C,0xA6, BYTE_LEN, 0 },
	{ 0xA06D,0x6c, BYTE_LEN, 0 },
	{ 0xA06E,0x04, BYTE_LEN, 0 },
	{ 0xA06F,0x25, BYTE_LEN, 0 },
	{ 0xA070,0x13, BYTE_LEN, 0 },
	{ 0xA071,0xE1, BYTE_LEN, 0 },
	{ 0xA072,0xC8, BYTE_LEN, 0 },
	{ 0xA073,0x46, BYTE_LEN, 0 },
	{ 0xA074,0x4e, BYTE_LEN, 0 },
	{ 0xA075,0x42, BYTE_LEN, 0 },
	{ 0xA076,0x93, BYTE_LEN, 0 },
	{ 0xA077,0xA5, BYTE_LEN, 0 },
	{ 0xA078,0x40, BYTE_LEN, 0 },
	{ 0xA079,0x65, BYTE_LEN, 0 },
	{ 0xA07A,0x2f, BYTE_LEN, 0 },
	{ 0xA07B,0x5b, BYTE_LEN, 0 },
	{ 0xA07C,0x91, BYTE_LEN, 0 },
	{ 0xA07D,0x4c, BYTE_LEN, 0 },
	{ 0xA07E,0x54, BYTE_LEN, 0 },
	{ 0xA07F,0x02, BYTE_LEN, 0 },
	{ 0xA080,0x33, BYTE_LEN, 0 },
	{ 0xA081,0x14, BYTE_LEN, 0 },
	{ 0xA082,0xB3, BYTE_LEN, 0 },
	{ 0xA083,0x88, BYTE_LEN, 0 },
	{ 0xA084,0x44, BYTE_LEN, 0 },
	{ 0xA085,0x26, BYTE_LEN, 0 },
	{ 0xA086,0x09, BYTE_LEN, 0 },
	{ 0xA087,0x69, BYTE_LEN, 0 },
	{ 0xA088,0x48, BYTE_LEN, 0 },
	{ 0xA089,0x40, BYTE_LEN, 0 },
	{ 0xA08A,0x04, BYTE_LEN, 0 },
	{ 0xA08B,0x92, BYTE_LEN, 0 },
	{ 0xA08C,0x10, BYTE_LEN, 0 },
	{ 0xA08D,0x86, BYTE_LEN, 0 },
	{ 0xA08E,0x90, BYTE_LEN, 0 },
	{ 0xA08F,0x44, BYTE_LEN, 0 },
	{ 0xA090,0x26, BYTE_LEN, 0 },
	{ 0xA091,0x44, BYTE_LEN, 0 },
	{ 0xA092,0x39, BYTE_LEN, 0 },
	{ 0xA093,0xCb, BYTE_LEN, 0 },
	{ 0xA094,0x53, BYTE_LEN, 0 },
	{ 0xA095,0x02, BYTE_LEN, 0 },
	{ 0xA096,0x03, BYTE_LEN, 0 },
	{ 0xA097,0x95, BYTE_LEN, 0 },
	{ 0xA098,0xC0, BYTE_LEN, 0 },
	{ 0xA099,0x08, BYTE_LEN, 0 },
	{ 0xA09A,0x85, BYTE_LEN, 0 },
	{ 0xA09B,0x2c, BYTE_LEN, 0 },
	{ 0xA09C,0x21, BYTE_LEN, 0 },
	{ 0xA09D,0x69, BYTE_LEN, 0 },
	{ 0xA09E,0xC9, BYTE_LEN, 0 },
	{ 0xA09F,0x41, BYTE_LEN, 0 },
	{ 0xA0A0,0x10, BYTE_LEN, 0 },
	{ 0xA0A1,0xE2, BYTE_LEN, 0 },
	{ 0xA0A2,0x8f, BYTE_LEN, 0 },
	{ 0xA0A3,0x7e, BYTE_LEN, 0 },
	{ 0xA0A4,0x1c, BYTE_LEN, 0 },
	{ 0xA0A5,0x04, BYTE_LEN, 0 },
	{ 0xA0A6,0x21, BYTE_LEN, 0 },
	{ 0xA0A7,0x21, BYTE_LEN, 0 },
	{ 0xA0A8,0x69, BYTE_LEN, 0 },
	{ 0xA0A9,0x89, BYTE_LEN, 0 },
	{ 0xA0AA,0x50, BYTE_LEN, 0 },
	{ 0xA0AB,0xC6, BYTE_LEN, 0 },
	{ 0xA0AC,0xD2, BYTE_LEN, 0 },
	{ 0xA0AD,0x14, BYTE_LEN, 0 },
	{ 0xA0AE,0xBf, BYTE_LEN, 0 },
	{ 0xA0AF,0x70, BYTE_LEN, 0 },
	{ 0xA0B0,0x65, BYTE_LEN, 0 },
	{ 0xA0B1,0x32, BYTE_LEN, 0 },
	{ 0xA0B2,0x4d, BYTE_LEN, 0 },
	{ 0xA0B3,0xB1, BYTE_LEN, 0 },
	{ 0xA0B4,0xCb, BYTE_LEN, 0 },
	{ 0xA0B5,0x4b, BYTE_LEN, 0 },
	{ 0xA0B6,0x80, BYTE_LEN, 0 },
	{ 0xA0B7,0x52, BYTE_LEN, 0 },
	{ 0xA0B8,0x11, BYTE_LEN, 0 },
	{ 0xA0B9,0x8d, BYTE_LEN, 0 },
	{ 0xA0BA,0x34, BYTE_LEN, 0 },
	{ 0xA0BB,0xE4, BYTE_LEN, 0 },
	{ 0xA0BC,0x21, BYTE_LEN, 0 },
	{ 0xA0BD,0x16, BYTE_LEN, 0 },
	{ 0xA0BE,0xD1, BYTE_LEN, 0 },
	{ 0xA0BF,0xC8, BYTE_LEN, 0 },
	{ 0xA0C0,0x4b, BYTE_LEN, 0 },
	{ 0xA0C1,0x7c, BYTE_LEN, 0 },
	{ 0xA0C2,0xD2, BYTE_LEN, 0 },
	{ 0xA0C3,0x14, BYTE_LEN, 0 },
	{ 0xA0C4,0xB8, BYTE_LEN, 0 },
	{ 0xA0C5,0x64, BYTE_LEN, 0 },
	{ 0xA0C6,0x65, BYTE_LEN, 0 },
	{ 0xA0C7,0x31, BYTE_LEN, 0 },
	{ 0xA0C8,0x67, BYTE_LEN, 0 },
	{ 0xA0C9,0x39, BYTE_LEN, 0 },
	{ 0xA0CA,0x8d, BYTE_LEN, 0 },
	{ 0xA0CB,0x57, BYTE_LEN, 0 },
	{ 0xA0CC,0x26, BYTE_LEN, 0 },
	{ 0xA0CD,0x63, BYTE_LEN, 0 },
	{ 0xA0CE,0x94, BYTE_LEN, 0 },
	{ 0xA0CF,0xB2, BYTE_LEN, 0 },
	{ 0xA0D0,0xCc, BYTE_LEN, 0 },
	{ 0xA0D1,0xC4, BYTE_LEN, 0 },
	{ 0xA0D2,0x28, BYTE_LEN, 0 },
	{ 0xA0D3,0x2c, BYTE_LEN, 0 },
	{ 0xA0D4,0xD9, BYTE_LEN, 0 },
	{ 0xA0D5,0xC9, BYTE_LEN, 0 },
	{ 0xA0D6,0x4c, BYTE_LEN, 0 },
	{ 0xA0D7,0x8c, BYTE_LEN, 0 },
	{ 0xA0D8,0x62, BYTE_LEN, 0 },
	{ 0xA0D9,0x94, BYTE_LEN, 0 },
	{ 0xA0DA,0xB2, BYTE_LEN, 0 },
	{ 0xA0DB,0x7c, BYTE_LEN, 0 },
	{ 0xA0DC,0x25, BYTE_LEN, 0 },
	{ 0xA0DD,0x32, BYTE_LEN, 0 },
	{ 0xA0DE,0x65, BYTE_LEN, 0 },
	{ 0xA0DF,0x19, BYTE_LEN, 0 },
	{ 0xA0E0,0x0d, BYTE_LEN, 0 },
	{ 0xA0E1,0x5b, BYTE_LEN, 0 },
	{ 0xA0E2,0x72, BYTE_LEN, 0 },
	{ 0xA0E3,0x13, BYTE_LEN, 0 },
	{ 0xA0E4,0x97, BYTE_LEN, 0 },
	{ 0xA0E5,0xDb, BYTE_LEN, 0 },
	{ 0xA0E6,0x78, BYTE_LEN, 0 },
	{ 0xA0E7,0x85, BYTE_LEN, 0 },
	{ 0xA0E8,0x32, BYTE_LEN, 0 },
	{ 0xA0E9,0x50, BYTE_LEN, 0 },
	{ 0xA0EA,0xF1, BYTE_LEN, 0 },
	{ 0xA0EB,0x0b, BYTE_LEN, 0 },
	{ 0xA0EC,0x53, BYTE_LEN, 0 },
	{ 0xA0ED,0xEc, BYTE_LEN, 0 },
	{ 0xA0EE,0x12, BYTE_LEN, 0 },
	{ 0xA0EF,0x95, BYTE_LEN, 0 },
	{ 0xA0F0,0xBe, BYTE_LEN, 0 },
	{ 0xA0F1,0x7c, BYTE_LEN, 0 },
	{ 0xA0F2,0x85, BYTE_LEN, 0 },
	{ 0xA0F3,0x32, BYTE_LEN, 0 },
	{ 0xA0F4,0x73, BYTE_LEN, 0 },
	{ 0xA0F5,0xA9, BYTE_LEN, 0 },
	{ 0xA0F6,0xCd, BYTE_LEN, 0 },
	{ 0xA0F7,0x5a, BYTE_LEN, 0 },
	{ 0xA0F8,0x66, BYTE_LEN, 0 },
	{ 0xA0F9,0x03, BYTE_LEN, 0 },
	{ 0xA0FA,0x17, BYTE_LEN, 0 },
	{ 0xA0FB,0xE3, BYTE_LEN, 0 },
	{ 0xA0FC,0xDc, BYTE_LEN, 0 },
	{ 0xA0FD,0xA5, BYTE_LEN, 0 },
	{ 0xA0FE,0x39, BYTE_LEN, 0 },
	{ 0xA0FF,0x74, BYTE_LEN, 0 },
	{ 0xA100,0x11, BYTE_LEN, 0 },
	{ 0xA101,0x0e, BYTE_LEN, 0 },
	{ 0xA102,0x5b, BYTE_LEN, 0 },
	{ 0xA103,0x6a, BYTE_LEN, 0 },
	{ 0xA104,0xA3, BYTE_LEN, 0 },
	{ 0xA105,0x16, BYTE_LEN, 0 },
	{ 0xA106,0xD8, BYTE_LEN, 0 },
	{ 0xA107,0xB4, BYTE_LEN, 0 },
	{ 0xA108,0xA5, BYTE_LEN, 0 },
	{ 0xA109,0x36, BYTE_LEN, 0 },
	{ 0xA10A,0x73, BYTE_LEN, 0 },
	{ 0xA10B,0x01, BYTE_LEN, 0 },
	{ 0xA10C,0x0e, BYTE_LEN, 0 },
	{ 0xA10D,0x5e, BYTE_LEN, 0 },
	{ 0xA10E,0x9a, BYTE_LEN, 0 },
	{ 0xA10F,0xF3, BYTE_LEN, 0 },
	{ 0xA110,0x16, BYTE_LEN, 0 },
	{ 0xA111,0xE3, BYTE_LEN, 0 },
	{ 0xA112,0x38, BYTE_LEN, 0 },
	{ 0xA113,0x85, BYTE_LEN, 0 },
	{ 0xA114,0x33, BYTE_LEN, 0 },
	{ 0xA115,0x65, BYTE_LEN, 0 },
	{ 0xA116,0xD1, BYTE_LEN, 0 },
	{ 0xA117,0xCd, BYTE_LEN, 0 },
	{ 0xA118,0x59, BYTE_LEN, 0 },
	{ 0xA119,0x74, BYTE_LEN, 0 },
	{ 0xA11A,0xE3, BYTE_LEN, 0 },
	{ 0xA11B,0x95, BYTE_LEN, 0 },
	{ 0xA11C,0xD6, BYTE_LEN, 0 },
	{ 0xA11D,0x7c, BYTE_LEN, 0 },
	{ 0xA11E,0xA5, BYTE_LEN, 0 },
	{ 0xA11F,0x35, BYTE_LEN, 0 },
	{ 0xA120,0x60, BYTE_LEN, 0 },
	{ 0xA121,0x79, BYTE_LEN, 0 },
	{ 0xA122,0xCd, BYTE_LEN, 0 },
	{ 0xA123,0x59, BYTE_LEN, 0 },
	{ 0xA124,0x74, BYTE_LEN, 0 },
	{ 0xA125,0x73, BYTE_LEN, 0 },
	{ 0xA126,0x96, BYTE_LEN, 0 },
	{ 0xA127,0xDf, BYTE_LEN, 0 },
	{ 0xA128,0x44, BYTE_LEN, 0 },
	{ 0xA129,0xA5, BYTE_LEN, 0 },
	{ 0xA12A,0x34, BYTE_LEN, 0 },
	{ 0xA12B,0x34, BYTE_LEN, 0 },
	{ 0xA12C,0x21, BYTE_LEN, 0 },
	{ 0xA12D,0xCa, BYTE_LEN, 0 },
	{ 0xA12E,0x54, BYTE_LEN, 0 },
	{ 0xA12F,0xCc, BYTE_LEN, 0 },
	{ 0xA130,0x92, BYTE_LEN, 0 },
	{ 0xA131,0x15, BYTE_LEN, 0 },
	{ 0xA132,0xB5, BYTE_LEN, 0 },
	{ 0xA133,0x5c, BYTE_LEN, 0 },
	{ 0xA134,0xE5, BYTE_LEN, 0 },
	{ 0xA135,0x2c, BYTE_LEN, 0 },
	{ 0xA136,0x58, BYTE_LEN, 0 },
	{ 0xA137,0x39, BYTE_LEN, 0 },
	{ 0xA138,0xCb, BYTE_LEN, 0 },
	{ 0xA139,0x56, BYTE_LEN, 0 },
	{ 0xA13A,0xCc, BYTE_LEN, 0 },
	{ 0xA13B,0x02, BYTE_LEN, 0 },
	{ 0xA13C,0x16, BYTE_LEN, 0 },
	{ 0xA13D,0xB6, BYTE_LEN, 0 },
	{ 0xA13E,0x6c, BYTE_LEN, 0 },
	{ 0xA13F,0xA5, BYTE_LEN, 0 },
	{ 0xA140,0x2c, BYTE_LEN, 0 },
	{ 0xA141,0x3b, BYTE_LEN, 0 },
	{ 0xA142,0x21, BYTE_LEN, 0 },
	{ 0xA143,0x0a, BYTE_LEN, 0 },
	{ 0xA144,0x57, BYTE_LEN, 0 },
	{ 0xA145,0xE6, BYTE_LEN, 0 },
	{ 0xA146,0x62, BYTE_LEN, 0 },
	{ 0xA147,0x16, BYTE_LEN, 0 },
	{ 0xA148,0xBe, BYTE_LEN, 0 },
	{ 0xA149,0x9c, BYTE_LEN, 0 },
	{ 0xA14A,0x45, BYTE_LEN, 0 },
	{ 0xA14B,0x2f, BYTE_LEN, 0 },
	{ 0xA14C,0x67, BYTE_LEN, 0 },
	{ 0xA14D,0xC1, BYTE_LEN, 0 },
	{ 0xA14E,0xCb, BYTE_LEN, 0 },
	{ 0xA14F,0x59, BYTE_LEN, 0 },
	{ 0xA150,0xEe, BYTE_LEN, 0 },
	{ 0xA151,0xB2, BYTE_LEN, 0 },
	{ 0xA152,0x96, BYTE_LEN, 0 },
	{ 0xA153,0xBc, BYTE_LEN, 0 },
	{ 0xA154,0xB8, BYTE_LEN, 0 },
	{ 0xA155,0x85, BYTE_LEN, 0 },
	{ 0xA156,0x2f, BYTE_LEN, 0 },
	{ 0xA157,0x6f, BYTE_LEN, 0 },
	{ 0xA158,0xD9, BYTE_LEN, 0 },
	{ 0xA159,0x4b, BYTE_LEN, 0 },
	{ 0xA15A,0x58, BYTE_LEN, 0 },
	{ 0xA15B,0xDa, BYTE_LEN, 0 },
	{ 0xA15C,0xB2, BYTE_LEN, 0 },
	{ 0xA15D,0x15, BYTE_LEN, 0 },
	{ 0xA15E,0xB8, BYTE_LEN, 0 },
	{ 0xA15F,0x8c, BYTE_LEN, 0 },
	{ 0xA160,0x05, BYTE_LEN, 0 },
	{ 0xA161,0x2f, BYTE_LEN, 0 },
	{ 0xA162,0x58, BYTE_LEN, 0 },
	{ 0xA163,0x41, BYTE_LEN, 0 },
	{ 0xA164,0x4b, BYTE_LEN, 0 },
	{ 0xA165,0x54, BYTE_LEN, 0 },
	{ 0xA166,0xBa, BYTE_LEN, 0 },
	{ 0xA167,0xF2, BYTE_LEN, 0 },
	{ 0xA168,0x14, BYTE_LEN, 0 },
	{ 0xA169,0xAd, BYTE_LEN, 0 },
	{ 0xA16A,0x4c, BYTE_LEN, 0 },
	{ 0xA16B,0xC5, BYTE_LEN, 0 },
	{ 0xA16C,0x2b, BYTE_LEN, 0 },
	{ 0xA16D,0x5e, BYTE_LEN, 0 },
	{ 0xA16E,0x41, BYTE_LEN, 0 },
	{ 0xA16F,0xCb, BYTE_LEN, 0 },
	{ 0xA170,0x5a, BYTE_LEN, 0 },
	{ 0xA171,0xEa, BYTE_LEN, 0 },
	{ 0xA172,0x02, BYTE_LEN, 0 },
	{ 0xA173,0x16, BYTE_LEN, 0 },
	{ 0xA174,0xB5, BYTE_LEN, 0 },
	{ 0xA175,0x50, BYTE_LEN, 0 },
	{ 0xA176,0x05, BYTE_LEN, 0 },
	{ 0xA177,0x2d, BYTE_LEN, 0 },
	{ 0xA178,0x51, BYTE_LEN, 0 },
	{ 0xA179,0x19, BYTE_LEN, 0 },
	{ 0xA17A,0x8b, BYTE_LEN, 0 },
	{ 0xA17B,0x50, BYTE_LEN, 0 },
	{ 0xA17C,0x9c, BYTE_LEN, 0 },
	{ 0xA17D,0x62, BYTE_LEN, 0 },
	{ 0xA17E,0x13, BYTE_LEN, 0 },
	{ 0xA17F,0x9f, BYTE_LEN, 0 },
	{ 0xA180,0xC8, BYTE_LEN, 0 },
	{ 0xA181,0x04, BYTE_LEN, 0 },
	{ 0xA182,0x27, BYTE_LEN, 0 },
	{ 0xA183,0x39, BYTE_LEN, 0 },
	{ 0xA184,0xE9, BYTE_LEN, 0 },
	{ 0xA185,0x09, BYTE_LEN, 0 },
	{ 0xA186,0x52, BYTE_LEN, 0 },
	{ 0xA187,0x9c, BYTE_LEN, 0 },
	{ 0xA188,0x92, BYTE_LEN, 0 },
	{ 0xA189,0x95, BYTE_LEN, 0 },
	{ 0xA18A,0xB1, BYTE_LEN, 0 },
	{ 0xA18B,0x68, BYTE_LEN, 0 },
	{ 0xA18C,0xC5, BYTE_LEN, 0 },
	{ 0xA18D,0x2c, BYTE_LEN, 0 },
	{ 0xA18E,0x48, BYTE_LEN, 0 },
	{ 0xA18F,0xD9, BYTE_LEN, 0 },
	{ 0xA190,0x0a, BYTE_LEN, 0 },
	{ 0xA191,0x50, BYTE_LEN, 0 },
	{ 0xA192,0x9e, BYTE_LEN, 0 },
	{ 0xA193,0xB2, BYTE_LEN, 0 },
	{ 0xA194,0x92, BYTE_LEN, 0 },
	{ 0xA195,0x9a, BYTE_LEN, 0 },
	{ 0xA196,0x60, BYTE_LEN, 0 },
	{ 0xA197,0xC4, BYTE_LEN, 0 },
	{ 0xA198,0x23, BYTE_LEN, 0 },
	{ 0xA199,0x13, BYTE_LEN, 0 },
	{ 0xA19A,0xA9, BYTE_LEN, 0 },
	{ 0xA19B,0xC8, BYTE_LEN, 0 },
	{ 0xA19C,0x46, BYTE_LEN, 0 },
	{ 0xA19D,0x38, BYTE_LEN, 0 },
	{ 0xA19E,0x22, BYTE_LEN, 0 },
	{ 0xA19F,0x93, BYTE_LEN, 0 },
	{ 0xA1A0,0x9a, BYTE_LEN, 0 },
	{ 0xA1A1,0x20, BYTE_LEN, 0 },
	{ 0xA1A2,0x25, BYTE_LEN, 0 },
	{ 0xA1A3,0x2a, BYTE_LEN, 0 },
	{ 0xA1A4,0x4f, BYTE_LEN, 0 },
	{ 0xA1A5,0xD9, BYTE_LEN, 0 },
	{ 0xA1A6,0x4a, BYTE_LEN, 0 },
	{ 0xA1A7,0x4f, BYTE_LEN, 0 },
	{ 0xA1A8,0x98, BYTE_LEN, 0 },
	{ 0xA1A9,0x52, BYTE_LEN, 0 },
	{ 0xA1AA,0x93, BYTE_LEN, 0 },
	{ 0xA1AB,0xA0, BYTE_LEN, 0 },
	{ 0xA1AC,0x74, BYTE_LEN, 0 },
	{ 0xA1AD,0x64, BYTE_LEN, 0 },
	{ 0xA1AE,0x24, BYTE_LEN, 0 },
	{ 0xA1AF,0x08, BYTE_LEN, 0 },
	{ 0xA1B0,0x51, BYTE_LEN, 0 },
	{ 0xA1B1,0x48, BYTE_LEN, 0 },
	{ 0xA1B2,0x40, BYTE_LEN, 0 },
	{ 0xA1B3,0x02, BYTE_LEN, 0 },
	{ 0xA1B4,0xA2, BYTE_LEN, 0 },
	{ 0xA1B5,0x90, BYTE_LEN, 0 },
	{ 0xA1B6,0x84, BYTE_LEN, 0 },
	{ 0xA1B7,0x88, BYTE_LEN, 0 },
	{ 0xA1B8,0x64, BYTE_LEN, 0 },
	{ 0xA1B9,0x24, BYTE_LEN, 0 },
	{ 0xA1BA,0x3d, BYTE_LEN, 0 },
	{ 0xA1BB,0x21, BYTE_LEN, 0 },
	{ 0xA1BC,0x8a, BYTE_LEN, 0 },
	{ 0xA1BD,0x50, BYTE_LEN, 0 },
	{ 0xA1BE,0x9c, BYTE_LEN, 0 },
	{ 0xA1BF,0xE2, BYTE_LEN, 0 },
	{ 0xA1C0,0x93, BYTE_LEN, 0 },
	{ 0xA1C1,0xA5, BYTE_LEN, 0 },
	{ 0xA1C2,0xD8, BYTE_LEN, 0 },
	{ 0xA1C3,0xE4, BYTE_LEN, 0 },
	{ 0xA1C4,0x27, BYTE_LEN, 0 },
	{ 0xA1C5,0x1c, BYTE_LEN, 0 },
	{ 0xA1C6,0xF9, BYTE_LEN, 0 },
	{ 0xA1C7,0x08, BYTE_LEN, 0 },
	{ 0xA1C8,0x41, BYTE_LEN, 0 },
	{ 0xA1C9,0x0c, BYTE_LEN, 0 },
	{ 0xA1CA,0xE2, BYTE_LEN, 0 },
	{ 0xA1CB,0x0f, BYTE_LEN, 0 },
	{ 0xA1CC,0x7f, BYTE_LEN, 0 },
	{ 0xA1CD,0x14, BYTE_LEN, 0 },
	{ 0xA1CE,0xA4, BYTE_LEN, 0 },
	{ 0xA1CF,0x20, BYTE_LEN, 0 },
	{ 0xA1D0,0x1e, BYTE_LEN, 0 },
	{ 0xA1D1,0xF9, BYTE_LEN, 0 },
	{ 0xA1D2,0x88, BYTE_LEN, 0 },
	{ 0xA1D3,0x4e, BYTE_LEN, 0 },
	{ 0xA1D4,0x80, BYTE_LEN, 0 },
	{ 0xA1D5,0x12, BYTE_LEN, 0 },
	{ 0xA1D6,0x94, BYTE_LEN, 0 },
	{ 0xA1D7,0xA5, BYTE_LEN, 0 },
	{ 0xA1D8,0x28, BYTE_LEN, 0 },
	{ 0xA1D9,0xA5, BYTE_LEN, 0 },
	{ 0xA1DA,0x2a, BYTE_LEN, 0 },
	{ 0xA1DB,0x3f, BYTE_LEN, 0 },
	{ 0xA1DC,0x41, BYTE_LEN, 0 },
	{ 0xA1DD,0x8a, BYTE_LEN, 0 },
	{ 0xA1DE,0x49, BYTE_LEN, 0 },
	{ 0xA1DF,0x56, BYTE_LEN, 0 },
	{ 0xA1E0,0x02, BYTE_LEN, 0 },
	{ 0xA1E1,0x11, BYTE_LEN, 0 },
	{ 0xA1E2,0x89, BYTE_LEN, 0 },
	{ 0xA1E3,0x24, BYTE_LEN, 0 },
	{ 0xA1E4,0x44, BYTE_LEN, 0 },
	{ 0xA1E5,0x21, BYTE_LEN, 0 },
	{ 0xA1E6,0x10, BYTE_LEN, 0 },
	{ 0xA1E7,0x91, BYTE_LEN, 0 },
	{ 0xA1E8,0xC8, BYTE_LEN, 0 },
	{ 0xA1E9,0x49, BYTE_LEN, 0 },
	{ 0xA1EA,0x56, BYTE_LEN, 0 },
	{ 0xA1EB,0xE2, BYTE_LEN, 0 },
	{ 0xA1EC,0x13, BYTE_LEN, 0 },
	{ 0xA1ED,0xA4, BYTE_LEN, 0 },
	{ 0xA1EE,0x18, BYTE_LEN, 0 },
	{ 0xA1EF,0x85, BYTE_LEN, 0 },
	{ 0xA1F0,0x2a, BYTE_LEN, 0 },
	{ 0xA1F1,0x56, BYTE_LEN, 0 },
	{ 0xA1F2,0xF9, BYTE_LEN, 0 },
	{ 0xA1F3,0x0a, BYTE_LEN, 0 },
	{ 0xA1F4,0x54, BYTE_LEN, 0 },
	{ 0xA1F5,0xAe, BYTE_LEN, 0 },
	{ 0xA1F6,0xA2, BYTE_LEN, 0 },
	{ 0xA1F7,0x93, BYTE_LEN, 0 },
	{ 0xA1F8,0xA0, BYTE_LEN, 0 },
	{ 0xA1F9,0xA8, BYTE_LEN, 0 },
	{ 0xA1FA,0xC4, BYTE_LEN, 0 },
	{ 0xA1FB,0x25, BYTE_LEN, 0 },
	{ 0xA1FC,0x24, BYTE_LEN, 0 },
	{ 0xA1FD,0x39, BYTE_LEN, 0 },
	{ 0xA1FE,0x49, BYTE_LEN, 0 },
	{ 0xA1FF,0x4a, BYTE_LEN, 0 },
	{ 0xA200,0x5c, BYTE_LEN, 0 },
	{ 0xA201,0x82, BYTE_LEN, 0 },
	{ 0xA202,0x13, BYTE_LEN, 0 },
	{ 0xA203,0xA1, BYTE_LEN, 0 },
	{ 0xA204,0x2c, BYTE_LEN, 0 },
	{ 0xA205,0x45, BYTE_LEN, 0 },
	{ 0xA206,0x2b, BYTE_LEN, 0 },
	{ 0xA207,0x4d, BYTE_LEN, 0 },
	{ 0xA208,0x09, BYTE_LEN, 0 },
	{ 0xA209,0x0b, BYTE_LEN, 0 },
	{ 0xA20A,0x57, BYTE_LEN, 0 },
	{ 0xA20B,0xD0, BYTE_LEN, 0 },
	{ 0xA20C,0x22, BYTE_LEN, 0 },
	{ 0xA20D,0x96, BYTE_LEN, 0 },
	{ 0xA20E,0xB6, BYTE_LEN, 0 },
	{ 0xA20F,0x48, BYTE_LEN, 0 },
	{ 0xA210,0x45, BYTE_LEN, 0 },
	{ 0xA211,0x2b, BYTE_LEN, 0 },
	{ 0xA212,0x44, BYTE_LEN, 0 },
	{ 0xA213,0x69, BYTE_LEN, 0 },
	{ 0xA214,0x0a, BYTE_LEN, 0 },
	{ 0xA215,0x50, BYTE_LEN, 0 },
	{ 0xA216,0x90, BYTE_LEN, 0 },
	{ 0xA217,0x32, BYTE_LEN, 0 },
	{ 0xA218,0x14, BYTE_LEN, 0 },
	{ 0xA219,0xA7, BYTE_LEN, 0 },
	{ 0xA21A,0x30, BYTE_LEN, 0 },
	{ 0xA21B,0x85, BYTE_LEN, 0 },
	{ 0xA21C,0x2b, BYTE_LEN, 0 },
	{ 0xA21D,0x5a, BYTE_LEN, 0 },
	{ 0xA21E,0x81, BYTE_LEN, 0 },
	{ 0xA21F,0x0b, BYTE_LEN, 0 },
	{ 0xA220,0x54, BYTE_LEN, 0 },
	{ 0xA221,0xD2, BYTE_LEN, 0 },
	{ 0xA222,0x12, BYTE_LEN, 0 },
	{ 0xA223,0x16, BYTE_LEN, 0 },
	{ 0xA224,0xB6, BYTE_LEN, 0 },
	{ 0xA225,0xA0, BYTE_LEN, 0 },
	{ 0xA226,0x85, BYTE_LEN, 0 },
	{ 0xA227,0x2e, BYTE_LEN, 0 },
	{ 0xA228,0x65, BYTE_LEN, 0 },
	{ 0xA229,0x89, BYTE_LEN, 0 },
	{ 0xA22A,0x8b, BYTE_LEN, 0 },
	{ 0xA22B,0x57, BYTE_LEN, 0 },
	{ 0xA22C,0xD8, BYTE_LEN, 0 },
	{ 0xA22D,0xC2, BYTE_LEN, 0 },
	{ 0xA22E,0x15, BYTE_LEN, 0 },
	{ 0xA22F,0xB5, BYTE_LEN, 0 },
	{ 0xA230,0x78, BYTE_LEN, 0 },
	{ 0xA231,0xC5, BYTE_LEN, 0 },
	{ 0xA232,0x2d, BYTE_LEN, 0 },
	{ 0xA233,0x5f, BYTE_LEN, 0 },
	{ 0xA234,0xA9, BYTE_LEN, 0 },
	{ 0xA235,0x0b, BYTE_LEN, 0 },
	{ 0xA236,0x58, BYTE_LEN, 0 },
	{ 0xA237,0xF4, BYTE_LEN, 0 },
	{ 0xA238,0x62, BYTE_LEN, 0 },
	{ 0xA239,0x15, BYTE_LEN, 0 },
	{ 0xA23A,0xB8, BYTE_LEN, 0 },
	{ 0xA23B,0x08, BYTE_LEN, 0 },
	{ 0xA23C,0x65, BYTE_LEN, 0 },
	{ 0xA23D,0x29, BYTE_LEN, 0 },
	{ 0xA23E,0x57, BYTE_LEN, 0 },
	{ 0xA23F,0x11, BYTE_LEN, 0 },
	{ 0xA240,0x4b, BYTE_LEN, 0 },
	{ 0xA241,0x56, BYTE_LEN, 0 },
	{ 0xA242,0xCc, BYTE_LEN, 0 },
	{ 0xA243,0x22, BYTE_LEN, 0 },
	{ 0xA244,0x15, BYTE_LEN, 0 },
	{ 0xA245,0xB0, BYTE_LEN, 0 },
	{ 0xA246,0x48, BYTE_LEN, 0 },
	{ 0xA247,0x45, BYTE_LEN, 0 },
	{ 0xA248,0x2c, BYTE_LEN, 0 },
	{ 0xA249,0x53, BYTE_LEN, 0 },
	{ 0xA24A,0x21, BYTE_LEN, 0 },
	{ 0xA24B,0x4b, BYTE_LEN, 0 },
	{ 0xA24C,0x55, BYTE_LEN, 0 },
	{ 0xA24D,0xD6, BYTE_LEN, 0 },
	{ 0xA24E,0x22, BYTE_LEN, 0 },
	{ 0xA24F,0x15, BYTE_LEN, 0 },
	{ 0xA250,0xB5, BYTE_LEN, 0 },
	{ 0xA251,0xEc, BYTE_LEN, 0 },
	{ 0xA252,0x64, BYTE_LEN, 0 },
	{ 0xA253,0x2a, BYTE_LEN, 0 },

	{ 0xA254,0x6d, BYTE_LEN, 0 },
	{ 0xA255,0xC1, BYTE_LEN, 0 },
	{ 0xA256,0x4c, BYTE_LEN, 0 },
	{ 0xA257,0x67, BYTE_LEN, 0 },
	{ 0xA258,0x30, BYTE_LEN, 0 },
	{ 0xA259,0x93, BYTE_LEN, 0 },
	{ 0xA25A,0x19, BYTE_LEN, 0 },
	{ 0xA25B,0xCd, BYTE_LEN, 0 },
	{ 0xA25C,0x78, BYTE_LEN, 0 },
	{ 0xA25D,0xE6, BYTE_LEN, 0 },
	{ 0xA25E,0x32, BYTE_LEN, 0 },
	{ 0xA25F,0x6e, BYTE_LEN, 0 },
	{ 0xA260,0x29, BYTE_LEN, 0 },
	{ 0xA261,0x4d, BYTE_LEN, 0 },
	{ 0xA262,0x6c, BYTE_LEN, 0 },
	{ 0xA263,0x56, BYTE_LEN, 0 },
	{ 0xA264,0x53, BYTE_LEN, 0 },
	{ 0xA265,0x9a, BYTE_LEN, 0 },
	{ 0xA266,0xD1, BYTE_LEN, 0 },
	{ 0xA267,0x98, BYTE_LEN, 0 },
	{ 0xA268,0x66, BYTE_LEN, 0 },
	{ 0xA269,0x35, BYTE_LEN, 0 },
	{ 0xA26A,0xB0, BYTE_LEN, 0 },
	{ 0xA26B,0x19, BYTE_LEN, 0 },
	{ 0xA26C,0x8d, BYTE_LEN, 0 },
	{ 0xA26D,0x68, BYTE_LEN, 0 },
	{ 0xA26E,0x46, BYTE_LEN, 0 },
	{ 0xA26F,0x73, BYTE_LEN, 0 },
	{ 0xA270,0x98, BYTE_LEN, 0 },
	{ 0xA271,0xBa, BYTE_LEN, 0 },
	{ 0xA272,0xBc, BYTE_LEN, 0 },
	{ 0xA273,0xA5, BYTE_LEN, 0 },
	{ 0xA274,0x2e, BYTE_LEN, 0 },
	{ 0xA275,0x88, BYTE_LEN, 0 },
	{ 0xA276,0x19, BYTE_LEN, 0 },
	{ 0xA277,0x8d, BYTE_LEN, 0 },
	{ 0xA278,0x67, BYTE_LEN, 0 },
	{ 0xA279,0x20, BYTE_LEN, 0 },
	{ 0xA27A,0x03, BYTE_LEN, 0 },
	{ 0xA27B,0x98, BYTE_LEN, 0 },
	{ 0xA27C,0xAe, BYTE_LEN, 0 },
	{ 0xA27D,0x10, BYTE_LEN, 0 },
	{ 0xA27E,0xA5, BYTE_LEN, 0 },
	{ 0xA27F,0x27, BYTE_LEN, 0 },
	{ 0xA280,0x45, BYTE_LEN, 0 },
	{ 0xA281,0xE1, BYTE_LEN, 0 },
	{ 0xA282,0x8a, BYTE_LEN, 0 },
	{ 0xA283,0x5f, BYTE_LEN, 0 },
	{ 0xA284,0x18, BYTE_LEN, 0 },
	{ 0xA285,0x83, BYTE_LEN, 0 },
	{ 0xA286,0x97, BYTE_LEN, 0 },
	{ 0xA287,0xB0, BYTE_LEN, 0 },
	{ 0xA288,0xE8, BYTE_LEN, 0 },
	{ 0xA289,0xA4, BYTE_LEN, 0 },
	{ 0xA28A,0x23, BYTE_LEN, 0 },
	{ 0xA28B,0x14, BYTE_LEN, 0 },
	{ 0xA28C,0xE1, BYTE_LEN, 0 },
	{ 0xA28D,0x48, BYTE_LEN, 0 },
	{ 0xA28E,0x4e, BYTE_LEN, 0 },
	{ 0xA28F,0xC0, BYTE_LEN, 0 },
	{ 0xA290,0x72, BYTE_LEN, 0 },
	{ 0xA291,0x17, BYTE_LEN, 0 },
	{ 0xA292,0xB3, BYTE_LEN, 0 },
	{ 0xA293,0x40, BYTE_LEN, 0 },
	{ 0xA294,0xC5, BYTE_LEN, 0 },
	{ 0xA295,0x24, BYTE_LEN, 0 },
	{ 0xA296,0x0a, BYTE_LEN, 0 },
	{ 0xA297,0x09, BYTE_LEN, 0 },
	{ 0xA298,0x08, BYTE_LEN, 0 },
	{ 0xA299,0x42, BYTE_LEN, 0 },
	{ 0xA29A,0x4c, BYTE_LEN, 0 },
	{ 0xA29B,0x02, BYTE_LEN, 0 },
	{ 0xA29C,0x15, BYTE_LEN, 0 },
	{ 0xA29D,0xB3, BYTE_LEN, 0 },
	{ 0xA29E,0x94, BYTE_LEN, 0 },
	{ 0xA29F,0xC5, BYTE_LEN, 0 },
	{ 0xA2A0,0x29, BYTE_LEN, 0 },
	{ 0xA2A1,0x23, BYTE_LEN, 0 },
	{ 0xA2A2,0x31, BYTE_LEN, 0 },
	{ 0xA2A3,0x88, BYTE_LEN, 0 },
	{ 0xA2A4,0x3f, BYTE_LEN, 0 },
	{ 0xA2A5,0x0c, BYTE_LEN, 0 },
	{ 0xA2A6,0x32, BYTE_LEN, 0 },
	{ 0xA2A7,0x12, BYTE_LEN, 0 },
	{ 0xA2A8,0xA7, BYTE_LEN, 0 },
	{ 0xA2A9,0x94, BYTE_LEN, 0 },
	{ 0xA2AA,0xC5, BYTE_LEN, 0 },
	{ 0xA2AB,0x2e, BYTE_LEN, 0 },
	{ 0xA2AC,0x5c, BYTE_LEN, 0 },
	{ 0xA2AD,0x81, BYTE_LEN, 0 },
	{ 0xA2AE,0xC9, BYTE_LEN, 0 },
	{ 0xA2AF,0x44, BYTE_LEN, 0 },
	{ 0xA2B0,0x16, BYTE_LEN, 0 },
	{ 0xA2B1,0x32, BYTE_LEN, 0 },
	{ 0xA2B2,0x11, BYTE_LEN, 0 },
	{ 0xA2B3,0x98, BYTE_LEN, 0 },
	{ 0xA2B4,0x68, BYTE_LEN, 0 },
	{ 0xA2B5,0x45, BYTE_LEN, 0 },
	{ 0xA2B6,0x2e, BYTE_LEN, 0 },
	{ 0xA2B7,0x8a, BYTE_LEN, 0 },
	{ 0xA2B8,0xB1, BYTE_LEN, 0 },
	{ 0xA2B9,0x8b, BYTE_LEN, 0 },
	{ 0xA2BA,0x53, BYTE_LEN, 0 },
	{ 0xA2BB,0x6a, BYTE_LEN, 0 },
	{ 0xA2BC,0xD2, BYTE_LEN, 0 },
	{ 0xA2BD,0x12, BYTE_LEN, 0 },
	{ 0xA2BE,0x9b, BYTE_LEN, 0 },
	{ 0xA2BF,0x3c, BYTE_LEN, 0 },
	{ 0xA2C0,0xC5, BYTE_LEN, 0 },
	{ 0xA2C1,0x2e, BYTE_LEN, 0 },
	{ 0xA2C2,0x89, BYTE_LEN, 0 },
	{ 0xA2C3,0xE9, BYTE_LEN, 0 },
	{ 0xA2C4,0xCc, BYTE_LEN, 0 },
	{ 0xA2C5,0x66, BYTE_LEN, 0 },
	{ 0xA2C6,0xF2, BYTE_LEN, 0 },
	{ 0xA2C7,0x42, BYTE_LEN, 0 },
	{ 0xA2C8,0x96, BYTE_LEN, 0 },
	{ 0xA2C9,0xAe, BYTE_LEN, 0 },
	{ 0xA2CA,0x90, BYTE_LEN, 0 },
	{ 0xA2CB,0x25, BYTE_LEN, 0 },
	{ 0xA2CC,0x2f, BYTE_LEN, 0 },
	{ 0xA2CD,0x9b, BYTE_LEN, 0 },
	{ 0xA2CE,0xD9, BYTE_LEN, 0 },
	{ 0xA2CF,0x4c, BYTE_LEN, 0 },
	{ 0xA2D0,0x6a, BYTE_LEN, 0 },
	{ 0xA2D1,0x60, BYTE_LEN, 0 },
	{ 0xA2D2,0x53, BYTE_LEN, 0 },
	{ 0xA2D3,0x1a, BYTE_LEN, 0 },
	{ 0xA2D4,0xCc, BYTE_LEN, 0 },
	{ 0xA2D5,0x50, BYTE_LEN, 0 },
	{ 0xA2D6,0x06, BYTE_LEN, 0 },
	{ 0xA2D7,0x33, BYTE_LEN, 0 },
	{ 0xA2D8,0xA4, BYTE_LEN, 0 },
	{ 0xA2D9,0x89, BYTE_LEN, 0 },
	{ 0xA2DA,0x8d, BYTE_LEN, 0 },
	{ 0xA2DB,0x6a, BYTE_LEN, 0 },
	{ 0xA2DC,0x02, BYTE_LEN, 0 },
	{ 0xA2DD,0xE3, BYTE_LEN, 0 },
	{ 0xA2DE,0x19, BYTE_LEN, 0 },
	{ 0xA2DF,0xCf, BYTE_LEN, 0 },
	{ 0xA2E0,0x48, BYTE_LEN, 0 },
	{ 0xA2E1,0x46, BYTE_LEN, 0 },
	{ 0xA2E2,0x32, BYTE_LEN, 0 },
	{ 0xA2E3,0x93, BYTE_LEN, 0 },
	{ 0xA2E4,0xF1, BYTE_LEN, 0 },
	{ 0xA2E5,0x8c, BYTE_LEN, 0 },
	{ 0xA2E6,0x68, BYTE_LEN, 0 },
	{ 0xA2E7,0x12, BYTE_LEN, 0 },
	{ 0xA2E8,0x03, BYTE_LEN, 0 },
	{ 0xA2E9,0x80, BYTE_LEN, 0 },
	{ 0xA2EA,0x00, BYTE_LEN, 0 },
	{ 0xA2EB,0x00, BYTE_LEN, 0 },
	{ 0xA2EC,0x00, BYTE_LEN, 0 },
	{ 0xA2ED,0x00, BYTE_LEN, 0 },

	{ 0xA2EE,0x95, BYTE_LEN, 0 },
	{ 0xA2EF,0x19, BYTE_LEN, 0 },
	{ 0xA2F0,0xCe, BYTE_LEN, 0 },
	{ 0xA2F1,0x71, BYTE_LEN, 0 },
	{ 0xA2F2,0x7c, BYTE_LEN, 0 },
	{ 0xA2F3,0xE3, BYTE_LEN, 0 },
	{ 0xA2F4,0x1b, BYTE_LEN, 0 },
	{ 0xA2F5,0xDf, BYTE_LEN, 0 },
	{ 0xA2F6,0x08, BYTE_LEN, 0 },
	{ 0xA2F7,0x27, BYTE_LEN, 0 },
	{ 0xA2F8,0x37, BYTE_LEN, 0 },
	{ 0xA2F9,0x8b, BYTE_LEN, 0 },
	{ 0xA2FA,0x99, BYTE_LEN, 0 },
	{ 0xA2FB,0x4e, BYTE_LEN, 0 },
	{ 0xA2FC,0x77, BYTE_LEN, 0 },
	{ 0xA2FD,0xA8, BYTE_LEN, 0 },
	{ 0xA2FE,0xB3, BYTE_LEN, 0 },
	{ 0xA2FF,0x9c, BYTE_LEN, 0 },
	{ 0xA300,0xE3, BYTE_LEN, 0 },
	{ 0xA301,0x24, BYTE_LEN, 0 },
	{ 0xA302,0xC7, BYTE_LEN, 0 },
	{ 0xA303,0x39, BYTE_LEN, 0 },
	{ 0xA304,0xD3, BYTE_LEN, 0 },
	{ 0xA305,0x21, BYTE_LEN, 0 },
	{ 0xA306,0x8e, BYTE_LEN, 0 },
	{ 0xA307,0x72, BYTE_LEN, 0 },
	{ 0xA308,0x96, BYTE_LEN, 0 },
	{ 0xA309,0x83, BYTE_LEN, 0 },
	{ 0xA30A,0x9a, BYTE_LEN, 0 },
	{ 0xA30B,0xC9, BYTE_LEN, 0 },
	{ 0xA30C,0x2c, BYTE_LEN, 0 },
	{ 0xA30D,0x26, BYTE_LEN, 0 },
	{ 0xA30E,0x32, BYTE_LEN, 0 },
	{ 0xA30F,0xA5, BYTE_LEN, 0 },
	{ 0xA310,0x11, BYTE_LEN, 0 },
	{ 0xA311,0x4e, BYTE_LEN, 0 },
	{ 0xA312,0x6f, BYTE_LEN, 0 },
	{ 0xA313,0x6c, BYTE_LEN, 0 },
	{ 0xA314,0x23, BYTE_LEN, 0 },
	{ 0xA315,0x1a, BYTE_LEN, 0 },
	{ 0xA316,0xBb, BYTE_LEN, 0 },
	{ 0xA317,0x5c, BYTE_LEN, 0 },
	{ 0xA318,0xA5, BYTE_LEN, 0 },
	{ 0xA319,0x29, BYTE_LEN, 0 },
	{ 0xA31A,0x56, BYTE_LEN, 0 },
	{ 0xA31B,0x89, BYTE_LEN, 0 },
	{ 0xA31C,0x4b, BYTE_LEN, 0 },
	{ 0xA31D,0x66, BYTE_LEN, 0 },
	{ 0xA31E,0x52, BYTE_LEN, 0 },
	{ 0xA31F,0xC3, BYTE_LEN, 0 },
	{ 0xA320,0x99, BYTE_LEN, 0 },
	{ 0xA321,0xBe, BYTE_LEN, 0 },
	{ 0xA322,0x2c, BYTE_LEN, 0 },
	{ 0xA323,0xC5, BYTE_LEN, 0 },
	{ 0xA324,0x24, BYTE_LEN, 0 },
	{ 0xA325,0x1a, BYTE_LEN, 0 },
	{ 0xA326,0x21, BYTE_LEN, 0 },
	{ 0xA327,0xC9, BYTE_LEN, 0 },
	{ 0xA328,0x51, BYTE_LEN, 0 },
	{ 0xA329,0xEc, BYTE_LEN, 0 },
	{ 0xA32A,0x12, BYTE_LEN, 0 },
	{ 0xA32B,0x99, BYTE_LEN, 0 },
	{ 0xA32C,0xC2, BYTE_LEN, 0 },
	{ 0xA32D,0xA0, BYTE_LEN, 0 },
	{ 0xA32E,0x45, BYTE_LEN, 0 },
	{ 0xA32F,0x26, BYTE_LEN, 0 },
	{ 0xA330,0x0d, BYTE_LEN, 0 },
	{ 0xA331,0x09, BYTE_LEN, 0 },
	{ 0xA332,0xC8, BYTE_LEN, 0 },
	{ 0xA333,0x42, BYTE_LEN, 0 },
	{ 0xA334,0x5e, BYTE_LEN, 0 },
	{ 0xA335,0x32, BYTE_LEN, 0 },
	{ 0xA336,0x16, BYTE_LEN, 0 },
	{ 0xA337,0xBf, BYTE_LEN, 0 },
	{ 0xA338,0x0c, BYTE_LEN, 0 },
	{ 0xA339,0xA6, BYTE_LEN, 0 },
	{ 0xA33A,0x2c, BYTE_LEN, 0 },
	{ 0xA33B,0x2d, BYTE_LEN, 0 },
	{ 0xA33C,0x49, BYTE_LEN, 0 },
	{ 0xA33D,0x88, BYTE_LEN, 0 },
	{ 0xA33E,0x3f, BYTE_LEN, 0 },
	{ 0xA33F,0x0e, BYTE_LEN, 0 },
	{ 0xA340,0xB2, BYTE_LEN, 0 },
	{ 0xA341,0x12, BYTE_LEN, 0 },
	{ 0xA342,0xB0, BYTE_LEN, 0 },
	{ 0xA343,0xF0, BYTE_LEN, 0 },
	{ 0xA344,0xC5, BYTE_LEN, 0 },
	{ 0xA345,0x32, BYTE_LEN, 0 },
	{ 0xA346,0x75, BYTE_LEN, 0 },
	{ 0xA347,0xF9, BYTE_LEN, 0 },
	{ 0xA348,0x89, BYTE_LEN, 0 },
	{ 0xA349,0x46, BYTE_LEN, 0 },
	{ 0xA34A,0x1e, BYTE_LEN, 0 },
	{ 0xA34B,0x92, BYTE_LEN, 0 },
	{ 0xA34C,0x11, BYTE_LEN, 0 },
	{ 0xA34D,0x9e, BYTE_LEN, 0 },
	{ 0xA34E,0xB4, BYTE_LEN, 0 },
	{ 0xA34F,0x45, BYTE_LEN, 0 },
	{ 0xA350,0x31, BYTE_LEN, 0 },
	{ 0xA351,0xAe, BYTE_LEN, 0 },
	{ 0xA352,0xA9, BYTE_LEN, 0 },
	{ 0xA353,0x4c, BYTE_LEN, 0 },
	{ 0xA354,0x59, BYTE_LEN, 0 },
	{ 0xA355,0x8a, BYTE_LEN, 0 },
	{ 0xA356,0xA2, BYTE_LEN, 0 },
	{ 0xA357,0x13, BYTE_LEN, 0 },
	{ 0xA358,0xA2, BYTE_LEN, 0 },
	{ 0xA359,0x84, BYTE_LEN, 0 },
	{ 0xA35A,0xA5, BYTE_LEN, 0 },
	{ 0xA35B,0x31, BYTE_LEN, 0 },
	{ 0xA35C,0xA2, BYTE_LEN, 0 },
	{ 0xA35D,0x21, BYTE_LEN, 0 },
	{ 0xA35E,0xCe, BYTE_LEN, 0 },
	{ 0xA35F,0x6f, BYTE_LEN, 0 },
	{ 0xA360,0x2e, BYTE_LEN, 0 },
	{ 0xA361,0xE3, BYTE_LEN, 0 },
	{ 0xA362,0x17, BYTE_LEN, 0 },
	{ 0xA363,0xBa, BYTE_LEN, 0 },
	{ 0xA364,0xF0, BYTE_LEN, 0 },
	{ 0xA365,0x65, BYTE_LEN, 0 },
	{ 0xA366,0x32, BYTE_LEN, 0 },
	{ 0xA367,0xB7, BYTE_LEN, 0 },
	{ 0xA368,0xB9, BYTE_LEN, 0 },
	{ 0xA369,0x4d, BYTE_LEN, 0 },
	{ 0xA36A,0x74, BYTE_LEN, 0 },
	{ 0xA36B,0xB0, BYTE_LEN, 0 },
	{ 0xA36C,0x93, BYTE_LEN, 0 },
	{ 0xA36D,0x9c, BYTE_LEN, 0 },
	{ 0xA36E,0xDc, BYTE_LEN, 0 },
	{ 0xA36F,0xCc, BYTE_LEN, 0 },
	{ 0xA370,0x06, BYTE_LEN, 0 },
	{ 0xA371,0x37, BYTE_LEN, 0 },
	{ 0xA372,0xC4, BYTE_LEN, 0 },
	{ 0xA373,0x91, BYTE_LEN, 0 },
	{ 0xA374,0x8e, BYTE_LEN, 0 },
	{ 0xA375,0x72, BYTE_LEN, 0 },
	{ 0xA376,0x4a, BYTE_LEN, 0 },
	{ 0xA377,0x23, BYTE_LEN, 0 },
	{ 0xA378,0x1c, BYTE_LEN, 0 },
	{ 0xA379,0xE1, BYTE_LEN, 0 },
	{ 0xA37A,0xD0, BYTE_LEN, 0 },
	{ 0xA37B,0x46, BYTE_LEN, 0 },
	{ 0xA37C,0x36, BYTE_LEN, 0 },
	{ 0xA37D,0xB4, BYTE_LEN, 0 },
	{ 0xA37E,0x01, BYTE_LEN, 0 },
	{ 0xA37F,0xCe, BYTE_LEN, 0 },
	{ 0xA380,0x70, BYTE_LEN, 0 },
	{ 0xA381,0x4e, BYTE_LEN, 0 },
	{ 0xA382,0xF3, BYTE_LEN, 0 },
	{ 0xA383,0x14, BYTE_LEN, 0 },
	{ 0xA384,0xB7, BYTE_LEN, 0 },
	{ 0xA385,0xC0, BYTE_LEN, 0 },
	{ 0xA386,0x05, BYTE_LEN, 0 },
	{ 0xA387,0x2d, BYTE_LEN, 0 },
	{ 0xA388,0x4f, BYTE_LEN, 0 },
	{ 0xA389,0x71, BYTE_LEN, 0 },
	{ 0xA38A,0x0b, BYTE_LEN, 0 },
	{ 0xA38B,0x5c, BYTE_LEN, 0 },
	{ 0xA38C,0xD0, BYTE_LEN, 0 },
	{ 0xA38D,0x62, BYTE_LEN, 0 },
	{ 0xA38E,0x16, BYTE_LEN, 0 },
	{ 0xA38F,0xB5, BYTE_LEN, 0 },
	{ 0xA390,0xC4, BYTE_LEN, 0 },
	{ 0xA391,0xC5, BYTE_LEN, 0 },
	{ 0xA392,0x2d, BYTE_LEN, 0 },
	{ 0xA393,0x4d, BYTE_LEN, 0 },
	{ 0xA394,0xC1, BYTE_LEN, 0 },
	{ 0xA395,0x8b, BYTE_LEN, 0 },
	{ 0xA396,0x5f, BYTE_LEN, 0 },
	{ 0xA397,0xF6, BYTE_LEN, 0 },
	{ 0xA398,0x62, BYTE_LEN, 0 },
	{ 0xA399,0x17, BYTE_LEN, 0 },
	{ 0xA39A,0xB9, BYTE_LEN, 0 },
	{ 0xA39B,0xE0, BYTE_LEN, 0 },
	{ 0xA39C,0x85, BYTE_LEN, 0 },
	{ 0xA39D,0x2f, BYTE_LEN, 0 },
	{ 0xA39E,0x7f, BYTE_LEN, 0 },
	{ 0xA39F,0x99, BYTE_LEN, 0 },
	{ 0xA3A0,0xCb, BYTE_LEN, 0 },
	{ 0xA3A1,0x5c, BYTE_LEN, 0 },
	{ 0xA3A2,0xF0, BYTE_LEN, 0 },
	{ 0xA3A3,0x72, BYTE_LEN, 0 },
	{ 0xA3A4,0x16, BYTE_LEN, 0 },
	{ 0xA3A5,0xAe, BYTE_LEN, 0 },
	{ 0xA3A6,0x5c, BYTE_LEN, 0 },
	{ 0xA3A7,0x65, BYTE_LEN, 0 },
	{ 0xA3A8,0x2b, BYTE_LEN, 0 },
	{ 0xA3A9,0x68, BYTE_LEN, 0 },
	{ 0xA3AA,0xC9, BYTE_LEN, 0 },
	{ 0xA3AB,0x8b, BYTE_LEN, 0 },
	{ 0xA3AC,0x5b, BYTE_LEN, 0 },
	{ 0xA3AD,0xCe, BYTE_LEN, 0 },
	{ 0xA3AE,0x12, BYTE_LEN, 0 },
	{ 0xA3AF,0x16, BYTE_LEN, 0 },
	{ 0xA3B0,0xA6, BYTE_LEN, 0 },
	{ 0xA3B1,0xF0, BYTE_LEN, 0 },
	{ 0xA3B2,0xE4, BYTE_LEN, 0 },
	{ 0xA3B3,0x26, BYTE_LEN, 0 },
	{ 0xA3B4,0x3e, BYTE_LEN, 0 },
	{ 0xA3B5,0x71, BYTE_LEN, 0 },
	{ 0xA3B6,0x8a, BYTE_LEN, 0 },
	{ 0xA3B7,0x58, BYTE_LEN, 0 },
	{ 0xA3B8,0xC8, BYTE_LEN, 0 },
	{ 0xA3B9,0x72, BYTE_LEN, 0 },
	{ 0xA3BA,0x95, BYTE_LEN, 0 },
	{ 0xA3BB,0xA5, BYTE_LEN, 0 },
	{ 0xA3BC,0xC8, BYTE_LEN, 0 },
	{ 0xA3BD,0x84, BYTE_LEN, 0 },
	{ 0xA3BE,0x23, BYTE_LEN, 0 },
	{ 0xA3BF,0x15, BYTE_LEN, 0 },
	{ 0xA3C0,0xE9, BYTE_LEN, 0 },
	{ 0xA3C1,0x48, BYTE_LEN, 0 },
	{ 0xA3C2,0x4d, BYTE_LEN, 0 },
	{ 0xA3C3,0x9c, BYTE_LEN, 0 },
	{ 0xA3C4,0x52, BYTE_LEN, 0 },
	{ 0xA3C5,0x95, BYTE_LEN, 0 },
	{ 0xA3C6,0xA4, BYTE_LEN, 0 },
	{ 0xA3C7,0x00, BYTE_LEN, 0 },
	{ 0xA3C8,0x65, BYTE_LEN, 0 },
	{ 0xA3C9,0x24, BYTE_LEN, 0 },
	{ 0xA3CA,0x0b, BYTE_LEN, 0 },
	{ 0xA3CB,0x11, BYTE_LEN, 0 },
	{ 0xA3CC,0x48, BYTE_LEN, 0 },
	{ 0xA3CD,0x42, BYTE_LEN, 0 },
	{ 0xA3CE,0x46, BYTE_LEN, 0 },
	{ 0xA3CF,0xF2, BYTE_LEN, 0 },
	{ 0xA3D0,0x93, BYTE_LEN, 0 },
	{ 0xA3D1,0xA3, BYTE_LEN, 0 },
	{ 0xA3D2,0x30, BYTE_LEN, 0 },
	{ 0xA3D3,0x25, BYTE_LEN, 0 },
	{ 0xA3D4,0x28, BYTE_LEN, 0 },
	{ 0xA3D5,0x22, BYTE_LEN, 0 },
	{ 0xA3D6,0x31, BYTE_LEN, 0 },
	{ 0xA3D7,0x48, BYTE_LEN, 0 },
	{ 0xA3D8,0x3f, BYTE_LEN, 0 },
	{ 0xA3D9,0x06, BYTE_LEN, 0 },
	{ 0xA3DA,0xE2, BYTE_LEN, 0 },
	{ 0xA3DB,0x91, BYTE_LEN, 0 },
	{ 0xA3DC,0x9e, BYTE_LEN, 0 },
	{ 0xA3DD,0x18, BYTE_LEN, 0 },
	{ 0xA3DE,0x25, BYTE_LEN, 0 },
	{ 0xA3DF,0x2b, BYTE_LEN, 0 },
	{ 0xA3E0,0x4b, BYTE_LEN, 0 },
	{ 0xA3E1,0x69, BYTE_LEN, 0 },
	{ 0xA3E2,0x89, BYTE_LEN, 0 },
	{ 0xA3E3,0x44, BYTE_LEN, 0 },
	{ 0xA3E4,0x10, BYTE_LEN, 0 },
	{ 0xA3E5,0xE2, BYTE_LEN, 0 },
	{ 0xA3E6,0x10, BYTE_LEN, 0 },
	{ 0xA3E7,0x93, BYTE_LEN, 0 },
	{ 0xA3E8,0x00, BYTE_LEN, 0 },
	{ 0xA3E9,0x45, BYTE_LEN, 0 },
	{ 0xA3EA,0x29, BYTE_LEN, 0 },
	{ 0xA3EB,0x67, BYTE_LEN, 0 },
	{ 0xA3EC,0xE9, BYTE_LEN, 0 },
	{ 0xA3ED,0x8a, BYTE_LEN, 0 },
	{ 0xA3EE,0x50, BYTE_LEN, 0 },
	{ 0xA3EF,0x5c, BYTE_LEN, 0 },
	{ 0xA3F0,0x42, BYTE_LEN, 0 },
	{ 0xA3F1,0x12, BYTE_LEN, 0 },
	{ 0xA3F2,0x94, BYTE_LEN, 0 },
	{ 0xA3F3,0xE0, BYTE_LEN, 0 },
	{ 0xA3F4,0xC4, BYTE_LEN, 0 },
	{ 0xA3F5,0x29, BYTE_LEN, 0 },
	{ 0xA3F6,0x52, BYTE_LEN, 0 },
	{ 0xA3F7,0x71, BYTE_LEN, 0 },
	{ 0xA3F8,0x4b, BYTE_LEN, 0 },
	{ 0xA3F9,0x5c, BYTE_LEN, 0 },
	{ 0xA3FA,0xB8, BYTE_LEN, 0 },
	{ 0xA3FB,0x92, BYTE_LEN, 0 },
	{ 0xA3FC,0x14, BYTE_LEN, 0 },
	{ 0xA3FD,0xA1, BYTE_LEN, 0 },
	{ 0xA3FE,0x14, BYTE_LEN, 0 },
	{ 0xA3FF,0x05, BYTE_LEN, 0 },
	{ 0xA400,0x2a, BYTE_LEN, 0 },
	{ 0xA401,0x60, BYTE_LEN, 0 },
	{ 0xA402,0xC1, BYTE_LEN, 0 },
	{ 0xA403,0x4a, BYTE_LEN, 0 },
	{ 0xA404,0x5d, BYTE_LEN, 0 },
	{ 0xA405,0xF4, BYTE_LEN, 0 },
	{ 0xA406,0x22, BYTE_LEN, 0 },
	{ 0xA407,0x97, BYTE_LEN, 0 },
	{ 0xA408,0xB3, BYTE_LEN, 0 },
	{ 0xA409,0x90, BYTE_LEN, 0 },
	{ 0xA40A,0xC5, BYTE_LEN, 0 },
	{ 0xA40B,0x2c, BYTE_LEN, 0 },
	{ 0xA40C,0x68, BYTE_LEN, 0 },
	{ 0xA40D,0x61, BYTE_LEN, 0 },
	{ 0xA40E,0xCb, BYTE_LEN, 0 },
	{ 0xA40F,0x58, BYTE_LEN, 0 },
	{ 0xA410,0xAe, BYTE_LEN, 0 },
	{ 0xA411,0xB2, BYTE_LEN, 0 },
	{ 0xA412,0x96, BYTE_LEN, 0 },
	{ 0xA413,0xB4, BYTE_LEN, 0 },
	{ 0xA414,0x70, BYTE_LEN, 0 },
	{ 0xA415,0xA5, BYTE_LEN, 0 },
	{ 0xA416,0x2b, BYTE_LEN, 0 },
	{ 0xA417,0x5e, BYTE_LEN, 0 },
	{ 0xA418,0x11, BYTE_LEN, 0 },
	{ 0xA419,0x4b, BYTE_LEN, 0 },
	{ 0xA41A,0x58, BYTE_LEN, 0 },
	{ 0xA41B,0x96, BYTE_LEN, 0 },
	{ 0xA41C,0x02, BYTE_LEN, 0 },
	{ 0xA41D,0x00, BYTE_LEN, 0 },
	{ 0xA41E,0x00, BYTE_LEN, 0 },
	{ 0xA41F,0x00, BYTE_LEN, 0 },
	{ 0xA420,0x00, BYTE_LEN, 0 },
	{ 0xA421,0x0a, BYTE_LEN, 0 },

	{ 0x0068,0x5F, BYTE_LEN, 0 },
};
/* FIH-SW3-MM-UW-write OTP setting-00-*/

struct isx006_i2c_reg_conf isx006_SHD_MAX_2nd_settings[] = {
        //2009/12/28
        // ISX006 KMOT ES2 no.12 Module(Index3) 
        // PreSHD/SHD1/2/3 inifile
        // After Gamma 70%
        // SHD3 A+TLD
        { 0x0068, 0x50, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain off
        
        { 0x9000, 0x8282, WORD_LEN, 0 },    
        { 0x9002, 0x03, BYTE_LEN, 0 },
        { 0x9003, 0x0c, BYTE_LEN, 0 },
        { 0x9004, 0x0c, BYTE_LEN, 0 },
        { 0x9005, 0x30, BYTE_LEN, 0 },
        { 0x9006, 0x20, BYTE_LEN, 0 },
        { 0x9007, 0x00, BYTE_LEN, 0 },
        { 0x9008, 0x41, BYTE_LEN, 0 },
        { 0x9009, 0x80, BYTE_LEN, 0 },
        { 0x900A, 0x04, BYTE_LEN, 0 },
        { 0x900B, 0x02, BYTE_LEN, 0 },
        { 0x900C, 0x12, BYTE_LEN, 0 },
        { 0x900D, 0x08, BYTE_LEN, 0 },
        { 0x900E, 0x50, BYTE_LEN, 0 },
        { 0x900F, 0x20, BYTE_LEN, 0 },
        { 0x9010, 0x20, BYTE_LEN, 0 },
        { 0x9011, 0x01, BYTE_LEN, 0 },
        { 0x9012, 0x81, BYTE_LEN, 0 },
        { 0x9013, 0x05, BYTE_LEN, 0 },
        { 0x9014, 0x04, BYTE_LEN, 0 },
        { 0x9015, 0x16, BYTE_LEN, 0 },
        { 0x9016, 0x0c, BYTE_LEN, 0 },
        { 0x9017, 0x30, BYTE_LEN, 0 },
        { 0x9018, 0x30, BYTE_LEN, 0 },
        { 0x9019, 0xc0, BYTE_LEN, 0 },
        { 0x901A, 0x80, BYTE_LEN, 0 },
        { 0x901B, 0x00, BYTE_LEN, 0 },
        { 0x901C, 0x04, BYTE_LEN, 0 },
        { 0x901D, 0x01, BYTE_LEN, 0 },
        { 0x901E, 0x12, BYTE_LEN, 0 },
        { 0x901F, 0x08, BYTE_LEN, 0 },
        { 0x9020, 0x48, BYTE_LEN, 0 },
        { 0x9021, 0x20, BYTE_LEN, 0 },
        { 0x9022, 0x40, BYTE_LEN, 0 },
        { 0x9023, 0x81, BYTE_LEN, 0 },
        { 0x9024, 0x80, BYTE_LEN, 0 },
        { 0x9025, 0x04, BYTE_LEN, 0 },
        { 0x9026, 0x04, BYTE_LEN, 0 },
        { 0x9027, 0x16, BYTE_LEN, 0 },
        { 0x9028, 0x10, BYTE_LEN, 0 },
        { 0x9029, 0x58, BYTE_LEN, 0 },
        { 0x902A, 0x30, BYTE_LEN, 0 },
        { 0x902B, 0x00, BYTE_LEN, 0 },
        { 0x902C, 0xc1, BYTE_LEN, 0 },
        { 0x902D, 0x00, BYTE_LEN, 0 },
        { 0x902E, 0x04, BYTE_LEN, 0 },
        { 0x902F, 0x00, BYTE_LEN, 0 },
        { 0x9030, 0x0c, BYTE_LEN, 0 },
        { 0x9031, 0x04, BYTE_LEN, 0 },
        { 0x9032, 0x38, BYTE_LEN, 0 },
        { 0x9033, 0x20, BYTE_LEN, 0 },
        { 0x9034, 0x20, BYTE_LEN, 0 },
        { 0x9035, 0xc1, BYTE_LEN, 0 },
        { 0x9036, 0x00, BYTE_LEN, 0 },
        { 0x9037, 0x04, BYTE_LEN, 0 },
        { 0x9038, 0x04, BYTE_LEN, 0 },
        { 0x9039, 0x12, BYTE_LEN, 0 },
        { 0x903A, 0x0c, BYTE_LEN, 0 },
        { 0x903B, 0x48, BYTE_LEN, 0 },
        { 0x903C, 0x30, BYTE_LEN, 0 },
        { 0x903D, 0x20, BYTE_LEN, 0 },
        { 0x903E, 0x01, BYTE_LEN, 0 },
        { 0x903F, 0x00, BYTE_LEN, 0 },
        { 0x9040, 0x03, BYTE_LEN, 0 },
        { 0x9041, 0x00, BYTE_LEN, 0 },
        { 0x9042, 0x0c, BYTE_LEN, 0 },
        { 0x9043, 0x10, BYTE_LEN, 0 },
        { 0x9044, 0x30, BYTE_LEN, 0 },
        { 0x9045, 0x10, BYTE_LEN, 0 },
        { 0x9046, 0x80, BYTE_LEN, 0 },
        { 0x9047, 0x80, BYTE_LEN, 0 },
        { 0x9048, 0x00, BYTE_LEN, 0 },
        { 0x9049, 0x02, BYTE_LEN, 0 },
        { 0x904A, 0x03, BYTE_LEN, 0 },
        { 0x904B, 0x0c, BYTE_LEN, 0 },
        { 0x904C, 0x04, BYTE_LEN, 0 },
        { 0x904D, 0x40, BYTE_LEN, 0 },
        { 0x904E, 0x30, BYTE_LEN, 0 },
        { 0x904F, 0x20, BYTE_LEN, 0 },
        { 0x9050, 0xc1, BYTE_LEN, 0 },
        { 0x9051, 0x80, BYTE_LEN, 0 },
        { 0x9052, 0x04, BYTE_LEN, 0 },
        { 0x9053, 0x02, BYTE_LEN, 0 },
        { 0x9054, 0x0a, BYTE_LEN, 0 },
        { 0x9055, 0x08, BYTE_LEN, 0 },
        { 0x9056, 0x28, BYTE_LEN, 0 },
        { 0x9057, 0x30, BYTE_LEN, 0 },
        { 0x9058, 0x80, BYTE_LEN, 0 },
        { 0x9059, 0xc0, BYTE_LEN, 0 },
        { 0x905A, 0x00, BYTE_LEN, 0 },
        { 0x905B, 0x02, BYTE_LEN, 0 },
        { 0x905C, 0x02, BYTE_LEN, 0 },
        { 0x905D, 0x04, BYTE_LEN, 0 },
        { 0x905E, 0x04, BYTE_LEN, 0 },
        { 0x905F, 0x20, BYTE_LEN, 0 },
        { 0x9060, 0x30, BYTE_LEN, 0 },
        { 0x9061, 0xc0, BYTE_LEN, 0 },
        { 0x9062, 0x80, BYTE_LEN, 0 },
        { 0x9063, 0x00, BYTE_LEN, 0 },
        { 0x9064, 0x04, BYTE_LEN, 0 },
        { 0x9065, 0x02, BYTE_LEN, 0 },
        { 0x9066, 0x10, BYTE_LEN, 0 },
        { 0x9067, 0x0c, BYTE_LEN, 0 },
        { 0x9068, 0x18, BYTE_LEN, 0 },
        { 0x9069, 0x30, BYTE_LEN, 0 },
        { 0x906A, 0x60, BYTE_LEN, 0 },
        { 0x906B, 0x80, BYTE_LEN, 0 },
        { 0x906C, 0x80, BYTE_LEN, 0 },
        { 0x906D, 0x00, BYTE_LEN, 0 },
        { 0x906E, 0x03, BYTE_LEN, 0 },
        { 0x906F, 0x00, BYTE_LEN, 0 },
        { 0x9070, 0x08, BYTE_LEN, 0 },
        { 0x9071, 0x00, BYTE_LEN, 0 },
        { 0x9072, 0x00, BYTE_LEN, 0 },
        { 0x9073, 0x40, BYTE_LEN, 0 },
        { 0x9074, 0x80, BYTE_LEN, 0 },
        { 0x9075, 0x80, BYTE_LEN, 0 },
        { 0x9076, 0x01, BYTE_LEN, 0 },
        { 0x9077, 0x01, BYTE_LEN, 0 },
        { 0x9078, 0x0e, BYTE_LEN, 0 },
        { 0x9079, 0x04, BYTE_LEN, 0 },
        { 0x907A, 0x38, BYTE_LEN, 0 },
        { 0x907B, 0x30, BYTE_LEN, 0 },
        { 0x907C, 0x40, BYTE_LEN, 0 },
        { 0x907D, 0xc0, BYTE_LEN, 0 },
        { 0x907E, 0x00, BYTE_LEN, 0 },
        { 0x907F, 0x01, BYTE_LEN, 0 },
        { 0x9080, 0x03, BYTE_LEN, 0 },
        { 0x9081, 0x02, BYTE_LEN, 0 },
        { 0x9082, 0x08, BYTE_LEN, 0 },
        { 0x9083, 0x00, BYTE_LEN, 0 },
        { 0x9084, 0x20, BYTE_LEN, 0 },
        { 0x9085, 0xe0, BYTE_LEN, 0 },
        { 0x9086, 0x7f, BYTE_LEN, 0 },
        { 0x9087, 0x00, BYTE_LEN, 0 },
        { 0x9088, 0x00, BYTE_LEN, 0 },
        { 0x9089, 0x02, BYTE_LEN, 0 },
        { 0x908A, 0x06, BYTE_LEN, 0 },
        { 0x908B, 0x00, BYTE_LEN, 0 },
        { 0x908C, 0x28, BYTE_LEN, 0 },
        { 0x908D, 0x00, BYTE_LEN, 0 },
        { 0x908E, 0xa0, BYTE_LEN, 0 },
        { 0x908F, 0xc0, BYTE_LEN, 0 },
        { 0x9090, 0x80, BYTE_LEN, 0 },
        { 0x9091, 0x00, BYTE_LEN, 0 },
        { 0x9092, 0x03, BYTE_LEN, 0 },
        { 0x9093, 0x02, BYTE_LEN, 0 },
        { 0x9094, 0x10, BYTE_LEN, 0 },
        { 0x9095, 0x08, BYTE_LEN, 0 },
        { 0x9096, 0x40, BYTE_LEN, 0 },
        { 0x9097, 0xe0, BYTE_LEN, 0 },
        { 0x9098, 0xff, BYTE_LEN, 0 },
        { 0x9099, 0x00, BYTE_LEN, 0 },
        { 0x909A, 0x00, BYTE_LEN, 0 },
        { 0x909B, 0x04, BYTE_LEN, 0 },
        { 0x909C, 0x02, BYTE_LEN, 0 },
        { 0x909D, 0x0c, BYTE_LEN, 0 },
        { 0x909E, 0x18, BYTE_LEN, 0 },
        { 0x909F, 0x20, BYTE_LEN, 0 },
        { 0x90A0, 0x80, BYTE_LEN, 0 },
        { 0x90A1, 0x80, BYTE_LEN, 0 },
        { 0x90A2, 0x00, BYTE_LEN, 0 },
        { 0x90A3, 0x02, BYTE_LEN, 0 },
        { 0x90A4, 0x03, BYTE_LEN, 0 },
        { 0x90A5, 0x04, BYTE_LEN, 0 },
        { 0x90A6, 0x0c, BYTE_LEN, 0 },
        { 0x90A7, 0x10, BYTE_LEN, 0 },
        { 0x90A8, 0x20, BYTE_LEN, 0 },
        { 0x90A9, 0x60, BYTE_LEN, 0 },
        { 0x90AA, 0x40, BYTE_LEN, 0 },
        { 0x90AB, 0x81, BYTE_LEN, 0 },
        { 0x90AC, 0x01, BYTE_LEN, 0 },
        { 0x90AD, 0x04, BYTE_LEN, 0 },
        { 0x90AE, 0x02, BYTE_LEN, 0 },
        { 0x90AF, 0x0c, BYTE_LEN, 0 },
        { 0x90B0, 0x18, BYTE_LEN, 0 },
        { 0x90B1, 0x20, BYTE_LEN, 0 },
        { 0x90B2, 0x80, BYTE_LEN, 0 },
        { 0x90B3, 0x80, BYTE_LEN, 0 },
        { 0x90B4, 0x80, BYTE_LEN, 0 },
        { 0x90B5, 0x01, BYTE_LEN, 0 },
        { 0x90B6, 0x02, BYTE_LEN, 0 },
        { 0x90B7, 0x06, BYTE_LEN, 0 },
        { 0x90B8, 0x04, BYTE_LEN, 0 },
        { 0x90B9, 0x18, BYTE_LEN, 0 },
        { 0x90BA, 0x10, BYTE_LEN, 0 },
        { 0x90BB, 0x60, BYTE_LEN, 0 },
        { 0x90BC, 0xc0, BYTE_LEN, 0 },
        { 0x90BD, 0x00, BYTE_LEN, 0 },
        { 0x90BE, 0x02, BYTE_LEN, 0 },
        { 0x90BF, 0x04, BYTE_LEN, 0 },
        { 0x90C0, 0x06, BYTE_LEN, 0 },
        { 0x90C1, 0x10, BYTE_LEN, 0 },
        { 0x90C2, 0x10, BYTE_LEN, 0 },
        { 0x90C3, 0x20, BYTE_LEN, 0 },
        { 0x90C4, 0x80, BYTE_LEN, 0 },
        { 0x90C5, 0x40, BYTE_LEN, 0 },
        { 0x90C6, 0x00, BYTE_LEN, 0 },
        { 0x90C7, 0x03, BYTE_LEN, 0 },
        { 0x90C8, 0x02, BYTE_LEN, 0 },
        { 0x90C9, 0x08, BYTE_LEN, 0 },
        { 0x90CA, 0x08, BYTE_LEN, 0 },
        { 0x90CB, 0x20, BYTE_LEN, 0 },
        { 0x90CC, 0x40, BYTE_LEN, 0 },
        { 0x90CD, 0x60, BYTE_LEN, 0 },
        { 0x90CE, 0x00, BYTE_LEN, 0 },
        { 0x90CF, 0x81, BYTE_LEN, 0 },
        { 0x90D0, 0x01, BYTE_LEN, 0 },
        { 0x90D1, 0x03, BYTE_LEN, 0 },
        { 0x90D2, 0x06, BYTE_LEN, 0 },
        { 0x90D3, 0x0c, BYTE_LEN, 0 },
        { 0x90D4, 0x20, BYTE_LEN, 0 },
        { 0x90D5, 0x50, BYTE_LEN, 0 },
        { 0x90D6, 0xc0, BYTE_LEN, 0 },
        { 0x90D7, 0x40, BYTE_LEN, 0 },
        { 0x90D8, 0x81, BYTE_LEN, 0 },
        { 0x90D9, 0x02, BYTE_LEN, 0 },
        { 0x90DA, 0x03, BYTE_LEN, 0 },
        { 0x90DB, 0x08, BYTE_LEN, 0 },
        { 0x90DC, 0x10, BYTE_LEN, 0 },
        { 0x90DD, 0x28, BYTE_LEN, 0 },
        { 0x90DE, 0x40, BYTE_LEN, 0 },
        { 0x90DF, 0xa0, BYTE_LEN, 0 },
        { 0x90E0, 0x00, BYTE_LEN, 0 },
        { 0x90E1, 0x81, BYTE_LEN, 0 },
        { 0x90E2, 0x01, BYTE_LEN, 0 },
        { 0x90E3, 0x04, BYTE_LEN, 0 },
        { 0x90E4, 0x06, BYTE_LEN, 0 },
        { 0x90E5, 0x0c, BYTE_LEN, 0 },
        { 0x90E6, 0x18, BYTE_LEN, 0 },
        { 0x90E7, 0x30, BYTE_LEN, 0 },
        { 0x90E8, 0x80, BYTE_LEN, 0 },
        { 0x90E9, 0x40, BYTE_LEN, 0 },
        { 0x90EA, 0x01, BYTE_LEN, 0 },
        { 0x90EB, 0x03, BYTE_LEN, 0 },
        { 0x90EC, 0x05, BYTE_LEN, 0 },
        { 0x90ED, 0x0a, BYTE_LEN, 0 },
        { 0x90EE, 0x0c, BYTE_LEN, 0 },
        { 0x90EF, 0x20, BYTE_LEN, 0 },
        { 0x90F0, 0x40, BYTE_LEN, 0 },
        { 0x90F1, 0xa0, BYTE_LEN, 0 },
        { 0x90F2, 0x00, BYTE_LEN, 0 },
        { 0x90F3, 0x81, BYTE_LEN, 0 },
        { 0x90F4, 0x02, BYTE_LEN, 0 },
        { 0x90F5, 0x01, BYTE_LEN, 0 },
        { 0x90F6, 0xec, BYTE_LEN, 0 },
        { 0x90F7, 0x07, BYTE_LEN, 0 },
        { 0x90F8, 0xb0, BYTE_LEN, 0 },
        { 0x90F9, 0x1f, BYTE_LEN, 0 },
        { 0x90FA, 0xa0, BYTE_LEN, 0 },
        { 0x90FB, 0xbe, BYTE_LEN, 0 },
        { 0x90FC, 0x00, BYTE_LEN, 0 },
        { 0x90FD, 0xfb, BYTE_LEN, 0 },
        { 0x90FE, 0x01, BYTE_LEN, 0 },
        { 0x90FF, 0xf0, BYTE_LEN, 0 },
        { 0x9100, 0x0b, BYTE_LEN, 0 },
        { 0x9101, 0xa8, BYTE_LEN, 0 },
        { 0x9102, 0x2f, BYTE_LEN, 0 },
        { 0x9103, 0xe0, BYTE_LEN, 0 },
        { 0x9104, 0xfe, BYTE_LEN, 0 },
        { 0x9105, 0xff, BYTE_LEN, 0 },
        { 0x9106, 0xfa, BYTE_LEN, 0 },
        { 0x9107, 0xff, BYTE_LEN, 0 },
        { 0x9108, 0xeb, BYTE_LEN, 0 },
        { 0x9109, 0x07, BYTE_LEN, 0 },
        { 0x910A, 0xb0, BYTE_LEN, 0 },
        { 0x910B, 0x1f, BYTE_LEN, 0 },
        { 0x910C, 0xc0, BYTE_LEN, 0 },
        { 0x910D, 0x7e, BYTE_LEN, 0 },
        { 0x910E, 0x80, BYTE_LEN, 0 },
        { 0x910F, 0xfa, BYTE_LEN, 0 },
        { 0x9110, 0x02, BYTE_LEN, 0 },
        { 0x9111, 0xec, BYTE_LEN, 0 },
        { 0x9112, 0x07, BYTE_LEN, 0 },
        { 0x9113, 0xc0, BYTE_LEN, 0 },
        { 0x9114, 0x2f, BYTE_LEN, 0 },
        { 0x9115, 0xa0, BYTE_LEN, 0 },
        { 0x9116, 0xbe, BYTE_LEN, 0 },
        { 0x9117, 0x80, BYTE_LEN, 0 },
        { 0x9118, 0xfb, BYTE_LEN, 0 },
        { 0x9119, 0xff, BYTE_LEN, 0 },
        { 0x911A, 0xeb, BYTE_LEN, 0 },
        { 0x911B, 0xff, BYTE_LEN, 0 },
        { 0x911C, 0xaf, BYTE_LEN, 0 },
        { 0x911D, 0x3f, BYTE_LEN, 0 },
        { 0x911E, 0xc0, BYTE_LEN, 0 },
        { 0x911F, 0xfe, BYTE_LEN, 0 },
        { 0x9120, 0x00, BYTE_LEN, 0 },
        { 0x9121, 0xfb, BYTE_LEN, 0 },
        { 0x9122, 0x01, BYTE_LEN, 0 },
        { 0x9123, 0xf2, BYTE_LEN, 0 },
        { 0x9124, 0x03, BYTE_LEN, 0 },
        { 0x9125, 0xb0, BYTE_LEN, 0 },
        { 0x9126, 0x0f, BYTE_LEN, 0 },
        { 0x9127, 0xc0, BYTE_LEN, 0 },
        { 0x9128, 0x3e, BYTE_LEN, 0 },
        { 0x9129, 0x80, BYTE_LEN, 0 },
        { 0x912A, 0xfc, BYTE_LEN, 0 },
        { 0x912B, 0x00, BYTE_LEN, 0 },
        { 0x912C, 0xf0, BYTE_LEN, 0 },
        { 0x912D, 0x03, BYTE_LEN, 0 },
        { 0x912E, 0xc0, BYTE_LEN, 0 },
        { 0x912F, 0x0f, BYTE_LEN, 0 },
        { 0x9130, 0x00, BYTE_LEN, 0 },
        { 0x9131, 0xbf, BYTE_LEN, 0 },
        { 0x9132, 0x80, BYTE_LEN, 0 },
        { 0x9133, 0xfc, BYTE_LEN, 0 },
        { 0x9134, 0x02, BYTE_LEN, 0 },
        { 0x9135, 0xf2, BYTE_LEN, 0 },
        { 0x9136, 0x0b, BYTE_LEN, 0 },
        { 0x9137, 0xc0, BYTE_LEN, 0 },
        { 0x9138, 0x0f, BYTE_LEN, 0 },
        { 0x9139, 0x00, BYTE_LEN, 0 },
        { 0x913A, 0xff, BYTE_LEN, 0 },
        { 0x913B, 0xff, BYTE_LEN, 0 },
        { 0x913C, 0xfb, BYTE_LEN, 0 },
        { 0x913D, 0xff, BYTE_LEN, 0 },
        { 0x913E, 0xf1, BYTE_LEN, 0 },
        { 0x913F, 0xff, BYTE_LEN, 0 },
        { 0x9140, 0xcf, BYTE_LEN, 0 },
        { 0x9141, 0x1f, BYTE_LEN, 0 },
        { 0x9142, 0xe0, BYTE_LEN, 0 },
        { 0x9143, 0x7e, BYTE_LEN, 0 },
        { 0x9144, 0x80, BYTE_LEN, 0 },
        { 0x9145, 0xfb, BYTE_LEN, 0 },
        { 0x9146, 0x04, BYTE_LEN, 0 },
        { 0x9147, 0xf6, BYTE_LEN, 0 },
        { 0x9148, 0x13, BYTE_LEN, 0 },
        { 0x9149, 0xd8, BYTE_LEN, 0 },
        { 0x914A, 0x1f, BYTE_LEN, 0 },
        { 0x914B, 0x60, BYTE_LEN, 0 },
        { 0x914C, 0x7f, BYTE_LEN, 0 },
        { 0x914D, 0x80, BYTE_LEN, 0 },
        { 0x914E, 0xfc, BYTE_LEN, 0 },
        { 0x914F, 0x00, BYTE_LEN, 0 },
        { 0x9150, 0xf2, BYTE_LEN, 0 },
        { 0x9151, 0x03, BYTE_LEN, 0 },
        { 0x9152, 0xd8, BYTE_LEN, 0 },
        { 0x9153, 0x1f, BYTE_LEN, 0 },
        { 0x9154, 0xe0, BYTE_LEN, 0 },
        { 0x9155, 0x7e, BYTE_LEN, 0 },
        { 0x9156, 0x80, BYTE_LEN, 0 },
        { 0x9157, 0xfc, BYTE_LEN, 0 },
        { 0x9158, 0x01, BYTE_LEN, 0 },
        { 0x9159, 0xf2, BYTE_LEN, 0 },
        { 0x915A, 0x0b, BYTE_LEN, 0 },
        { 0x915B, 0xc0, BYTE_LEN, 0 },
        { 0x915C, 0x2f, BYTE_LEN, 0 },
        { 0x915D, 0x00, BYTE_LEN, 0 },
        { 0x915E, 0xbf, BYTE_LEN, 0 },
        { 0x915F, 0x00, BYTE_LEN, 0 },
        { 0x9160, 0xfd, BYTE_LEN, 0 },
        { 0x9161, 0x01, BYTE_LEN, 0 },
        { 0x9162, 0xfa, BYTE_LEN, 0 },
        { 0x9163, 0x07, BYTE_LEN, 0 },
        { 0x9164, 0xe8, BYTE_LEN, 0 },
        { 0x9165, 0xef, BYTE_LEN, 0 },
        { 0x9166, 0x7f, BYTE_LEN, 0 },
        { 0x9167, 0x7f, BYTE_LEN, 0 },
        { 0x9168, 0x00, BYTE_LEN, 0 },
        { 0x9169, 0xfe, BYTE_LEN, 0 },
        { 0x916A, 0x02, BYTE_LEN, 0 },
        { 0x916B, 0xfa, BYTE_LEN, 0 },
        { 0x916C, 0x0b, BYTE_LEN, 0 },
        { 0x916D, 0xe8, BYTE_LEN, 0 },
        { 0x916E, 0x4f, BYTE_LEN, 0 },
        { 0x916F, 0x60, BYTE_LEN, 0 },
        { 0x9170, 0x3f, BYTE_LEN, 0 },
        { 0x9171, 0x81, BYTE_LEN, 0 },
        { 0x9172, 0xfd, BYTE_LEN, 0 },
        { 0x9173, 0x03, BYTE_LEN, 0 },
        { 0x9174, 0xfc, BYTE_LEN, 0 },
        { 0x9175, 0x07, BYTE_LEN, 0 },
        { 0x9176, 0xf0, BYTE_LEN, 0 },
        { 0x9177, 0x0f, BYTE_LEN, 0 },
        { 0x9178, 0xe0, BYTE_LEN, 0 },
        { 0x9179, 0x7f, BYTE_LEN, 0 },
        { 0x917A, 0x00, BYTE_LEN, 0 },
        { 0x917B, 0xff, BYTE_LEN, 0 },
        { 0x917C, 0x01, BYTE_LEN, 0 },
        { 0x917D, 0xf8, BYTE_LEN, 0 },
        { 0x917E, 0x0b, BYTE_LEN, 0 },
        { 0x917F, 0xf0, BYTE_LEN, 0 },
        { 0x9180, 0x2f, BYTE_LEN, 0 },
        { 0x9181, 0xc0, BYTE_LEN, 0 },
        { 0x9182, 0xbf, BYTE_LEN, 0 },
        { 0x9183, 0x81, BYTE_LEN, 0 },
        { 0x9184, 0x00, BYTE_LEN, 0 },
        { 0x9185, 0x06, BYTE_LEN, 0 },
        { 0x9186, 0x02, BYTE_LEN, 0 },
        { 0x9187, 0x10, BYTE_LEN, 0 },
        { 0x9188, 0x00, BYTE_LEN, 0 },
        { 0x9189, 0x40, BYTE_LEN, 0 },
        { 0x918A, 0x80, BYTE_LEN, 0 },
        { 0x918B, 0x80, BYTE_LEN, 0 },
        { 0x918C, 0x00, BYTE_LEN, 0 },
        { 0x918D, 0x02, BYTE_LEN, 0 },
        { 0x918E, 0x02, BYTE_LEN, 0 },
        { 0x918F, 0x06, BYTE_LEN, 0 },
        { 0x9190, 0x0c, BYTE_LEN, 0 },
        { 0x9191, 0x00, BYTE_LEN, 0 },
        { 0x9192, 0x30, BYTE_LEN, 0 },
        { 0x9193, 0x20, BYTE_LEN, 0 },
        { 0x9194, 0xc0, BYTE_LEN, 0 },
        { 0x9195, 0x80, BYTE_LEN, 0 },
        { 0x9196, 0x00, BYTE_LEN, 0 },
        { 0x9197, 0x08, BYTE_LEN, 0 },
        { 0x9198, 0xfe, BYTE_LEN, 0 },
        { 0x9199, 0x23, BYTE_LEN, 0 },
        { 0x919A, 0xf8, BYTE_LEN, 0 },
        { 0x919B, 0x6f, BYTE_LEN, 0 },
        { 0x919C, 0xa0, BYTE_LEN, 0 },
        { 0x919D, 0x80, BYTE_LEN, 0 },
        { 0x919E, 0x00, BYTE_LEN, 0 },
        { 0x919F, 0x02, BYTE_LEN, 0 },
        { 0x91A0, 0x02, BYTE_LEN, 0 },
        { 0x91A1, 0x0e, BYTE_LEN, 0 },
        { 0x91A2, 0x10, BYTE_LEN, 0 },
        { 0x91A3, 0x30, BYTE_LEN, 0 },
        { 0x91A4, 0x40, BYTE_LEN, 0 },
        { 0x91A5, 0xa0, BYTE_LEN, 0 },
        { 0x91A6, 0x00, BYTE_LEN, 0 },
        { 0x91A7, 0x01, BYTE_LEN, 0 },
        { 0x91A8, 0x01, BYTE_LEN, 0 },
        { 0x91A9, 0x04, BYTE_LEN, 0 },
        { 0x91AA, 0x04, BYTE_LEN, 0 },
        { 0x91AB, 0x1c, BYTE_LEN, 0 },
        { 0x91AC, 0x20, BYTE_LEN, 0 },
        { 0x91AD, 0x70, BYTE_LEN, 0 },
        { 0x91AE, 0x80, BYTE_LEN, 0 },
        { 0x91AF, 0x40, BYTE_LEN, 0 },
        { 0x91B0, 0x81, BYTE_LEN, 0 },
        { 0x91B1, 0x02, BYTE_LEN, 0 },
        { 0x91B2, 0x06, BYTE_LEN, 0 },
        { 0x91B3, 0x0c, BYTE_LEN, 0 },
        { 0x91B4, 0x10, BYTE_LEN, 0 },
        { 0x91B5, 0x38, BYTE_LEN, 0 },
        { 0x91B6, 0x30, BYTE_LEN, 0 },
        { 0x91B7, 0xe0, BYTE_LEN, 0 },
        { 0x91B8, 0x00, BYTE_LEN, 0 },
        { 0x91B9, 0x81, BYTE_LEN, 0 },
        { 0x91BA, 0x03, BYTE_LEN, 0 },
        { 0x91BB, 0x02, BYTE_LEN, 0 },
        { 0x91BC, 0x0a, BYTE_LEN, 0 },
        { 0x91BD, 0x08, BYTE_LEN, 0 },
        { 0x91BE, 0x28, BYTE_LEN, 0 },
        { 0x91BF, 0x60, BYTE_LEN, 0 },
        { 0x91C0, 0xc0, BYTE_LEN, 0 },
        { 0x91C1, 0x80, BYTE_LEN, 0 },
        { 0x91C2, 0x01, BYTE_LEN, 0 },
        { 0x91C3, 0x03, BYTE_LEN, 0 },
        { 0x91C4, 0x06, BYTE_LEN, 0 },
        { 0x91C5, 0x06, BYTE_LEN, 0 },
        { 0x91C6, 0x18, BYTE_LEN, 0 },
        { 0x91C7, 0x40, BYTE_LEN, 0 },
        { 0x91C8, 0x40, BYTE_LEN, 0 },
        { 0x91C9, 0xe0, BYTE_LEN, 0 },
        { 0x91CA, 0x40, BYTE_LEN, 0 },
        { 0x91CB, 0x81, BYTE_LEN, 0 },
        { 0x91CC, 0x03, BYTE_LEN, 0 },
        { 0x91CD, 0x03, BYTE_LEN, 0 },
        { 0x91CE, 0x10, BYTE_LEN, 0 },
        { 0x91CF, 0x10, BYTE_LEN, 0 },
        { 0x91D0, 0x30, BYTE_LEN, 0 },
        { 0x91D1, 0x40, BYTE_LEN, 0 },
        { 0x91D2, 0xc0, BYTE_LEN, 0 },
        { 0x91D3, 0x80, BYTE_LEN, 0 },
        { 0x91D4, 0x01, BYTE_LEN, 0 },
        { 0x91D5, 0x03, BYTE_LEN, 0 },
        { 0x91D6, 0x06, BYTE_LEN, 0 },
        { 0x91D7, 0x0c, BYTE_LEN, 0 },
        { 0x91D8, 0x18, BYTE_LEN, 0 },
        { 0x91D9, 0x18, BYTE_LEN, 0 },
        { 0x91DA, 0x60, BYTE_LEN, 0 },
        { 0x91DB, 0x00, BYTE_LEN, 0 },
        { 0x91DC, 0x01, BYTE_LEN, 0 },
        { 0x91DD, 0x81, BYTE_LEN, 0 },
        { 0x91DE, 0x03, BYTE_LEN, 0 },
        { 0x91DF, 0x05, BYTE_LEN, 0 },
        { 0x91E0, 0x0e, BYTE_LEN, 0 },
        { 0x91E1, 0x0c, BYTE_LEN, 0 },
        { 0x91E2, 0x40, BYTE_LEN, 0 },
        { 0x91E3, 0x40, BYTE_LEN, 0 },
        { 0x91E4, 0xc0, BYTE_LEN, 0 },
        { 0x91E5, 0x00, BYTE_LEN, 0 },
        { 0x91E6, 0x01, BYTE_LEN, 0 },
        { 0x91E7, 0x03, BYTE_LEN, 0 },
        
        { 0xA000, 0x9191, WORD_LEN, 0 },
        { 0xA002, 0x84, BYTE_LEN, 0 },
        { 0xA003, 0xe1, BYTE_LEN, 0 },
        { 0xA004, 0x0d, BYTE_LEN, 0 },
        { 0xA005, 0x64, BYTE_LEN, 0 },
        { 0xA006, 0x92, BYTE_LEN, 0 },
        { 0xA007, 0xa3, BYTE_LEN, 0 },
        { 0xA008, 0x98, BYTE_LEN, 0 },
        { 0xA009, 0xe3, BYTE_LEN, 0 },
        { 0xA00A, 0xec, BYTE_LEN, 0 },
        { 0xA00B, 0x25, BYTE_LEN, 0 },
        { 0xA00C, 0x37, BYTE_LEN, 0 },
        { 0xA00D, 0x79, BYTE_LEN, 0 },
        { 0xA00E, 0xb1, BYTE_LEN, 0 },
        { 0xA00F, 0xcd, BYTE_LEN, 0 },
        { 0xA010, 0x5f, BYTE_LEN, 0 },
        { 0xA011, 0x7e, BYTE_LEN, 0 },
        { 0xA012, 0x13, BYTE_LEN, 0 },
        { 0xA013, 0x99, BYTE_LEN, 0 },
        { 0xA014, 0xe9, BYTE_LEN, 0 },
        { 0xA015, 0x64, BYTE_LEN, 0 },
        { 0xA016, 0xe6, BYTE_LEN, 0 },
        { 0xA017, 0x3b, BYTE_LEN, 0 },
        { 0xA018, 0x87, BYTE_LEN, 0 },
        { 0xA019, 0x61, BYTE_LEN, 0 },
        { 0xA01A, 0x8e, BYTE_LEN, 0 },
        { 0xA01B, 0x66, BYTE_LEN, 0 },
        { 0xA01C, 0xa8, BYTE_LEN, 0 },
        { 0xA01D, 0xb3, BYTE_LEN, 0 },
        { 0xA01E, 0x99, BYTE_LEN, 0 },
        { 0xA01F, 0xea, BYTE_LEN, 0 },
        { 0xA020, 0x18, BYTE_LEN, 0 },
        { 0xA021, 0x06, BYTE_LEN, 0 },
        { 0xA022, 0x38, BYTE_LEN, 0 },
        { 0xA023, 0x77, BYTE_LEN, 0 },
        { 0xA024, 0x81, BYTE_LEN, 0 },
        { 0xA025, 0x0d, BYTE_LEN, 0 },
        { 0xA026, 0x5d, BYTE_LEN, 0 },
        { 0xA027, 0x5a, BYTE_LEN, 0 },
        { 0xA028, 0xc3, BYTE_LEN, 0 },
        { 0xA029, 0x97, BYTE_LEN, 0 },
        { 0xA02A, 0xdb, BYTE_LEN, 0 },
        { 0xA02B, 0x3c, BYTE_LEN, 0 },
        { 0xA02C, 0xa6, BYTE_LEN, 0 },
        { 0xA02D, 0x39, BYTE_LEN, 0 },
        { 0xA02E, 0xa7, BYTE_LEN, 0 },
        { 0xA02F, 0x71, BYTE_LEN, 0 },
        { 0xA030, 0x8f, BYTE_LEN, 0 },
        { 0xA031, 0x69, BYTE_LEN, 0 },
        { 0xA032, 0xdc, BYTE_LEN, 0 },
        { 0xA033, 0xe3, BYTE_LEN, 0 },
        { 0xA034, 0x97, BYTE_LEN, 0 },
        { 0xA035, 0xdb, BYTE_LEN, 0 },
        { 0xA036, 0xdc, BYTE_LEN, 0 },
        { 0xA037, 0x65, BYTE_LEN, 0 },
        { 0xA038, 0x35, BYTE_LEN, 0 },
        { 0xA039, 0x59, BYTE_LEN, 0 },
        { 0xA03A, 0x19, BYTE_LEN, 0 },
        { 0xA03B, 0xcc, BYTE_LEN, 0 },
        { 0xA03C, 0x52, BYTE_LEN, 0 },
        { 0xA03D, 0xe4, BYTE_LEN, 0 },
        { 0xA03E, 0x82, BYTE_LEN, 0 },
        { 0xA03F, 0x94, BYTE_LEN, 0 },
        { 0xA040, 0xb7, BYTE_LEN, 0 },
        { 0xA041, 0x40, BYTE_LEN, 0 },
        { 0xA042, 0x05, BYTE_LEN, 0 },
        { 0xA043, 0x2f, BYTE_LEN, 0 },
        { 0xA044, 0x62, BYTE_LEN, 0 },
        { 0xA045, 0x81, BYTE_LEN, 0 },
        { 0xA046, 0x0c, BYTE_LEN, 0 },
        { 0xA047, 0x61, BYTE_LEN, 0 },
        { 0xA048, 0x78, BYTE_LEN, 0 },
        { 0xA049, 0xe3, BYTE_LEN, 0 },
        { 0xA04A, 0x98, BYTE_LEN, 0 },
        { 0xA04B, 0xe6, BYTE_LEN, 0 },
        { 0xA04C, 0x80, BYTE_LEN, 0 },
        { 0xA04D, 0x05, BYTE_LEN, 0 },
        { 0xA04E, 0x32, BYTE_LEN, 0 },
        { 0xA04F, 0x54, BYTE_LEN, 0 },
        { 0xA050, 0xe1, BYTE_LEN, 0 },
        { 0xA051, 0x4b, BYTE_LEN, 0 },
        { 0xA052, 0x4f, BYTE_LEN, 0 },
        { 0xA053, 0xb4, BYTE_LEN, 0 },
        { 0xA054, 0xd2, BYTE_LEN, 0 },
        { 0xA055, 0x12, BYTE_LEN, 0 },
        { 0xA056, 0xa1, BYTE_LEN, 0 },
        { 0xA057, 0xa4, BYTE_LEN, 0 },
        { 0xA058, 0x64, BYTE_LEN, 0 },
        { 0xA059, 0x27, BYTE_LEN, 0 },
        { 0xA05A, 0x31, BYTE_LEN, 0 },
        { 0xA05B, 0x49, BYTE_LEN, 0 },
        { 0xA05C, 0x0a, BYTE_LEN, 0 },
        { 0xA05D, 0x51, BYTE_LEN, 0 },
        { 0xA05E, 0xca, BYTE_LEN, 0 },
        { 0xA05F, 0x02, BYTE_LEN, 0 },
        { 0xA060, 0x96, BYTE_LEN, 0 },
        { 0xA061, 0xc6, BYTE_LEN, 0 },
        { 0xA062, 0xc4, BYTE_LEN, 0 },
        { 0xA063, 0xc5, BYTE_LEN, 0 },
        { 0xA064, 0x34, BYTE_LEN, 0 },
        { 0xA065, 0x4f, BYTE_LEN, 0 },
        { 0xA066, 0xa9, BYTE_LEN, 0 },
        { 0xA067, 0x8b, BYTE_LEN, 0 },
        { 0xA068, 0x50, BYTE_LEN, 0 },
        { 0xA069, 0xc0, BYTE_LEN, 0 },
        { 0xA06A, 0x72, BYTE_LEN, 0 },
        { 0xA06B, 0x12, BYTE_LEN, 0 },
        { 0xA06C, 0x9c, BYTE_LEN, 0 },
        { 0xA06D, 0x40, BYTE_LEN, 0 },
        { 0xA06E, 0x24, BYTE_LEN, 0 },
        { 0xA06F, 0x23, BYTE_LEN, 0 },
        { 0xA070, 0x0a, BYTE_LEN, 0 },
        { 0xA071, 0x89, BYTE_LEN, 0 },
        { 0xA072, 0x48, BYTE_LEN, 0 },
        { 0xA073, 0x45, BYTE_LEN, 0 },
        { 0xA074, 0x3e, BYTE_LEN, 0 },
        { 0xA075, 0x02, BYTE_LEN, 0 },
        { 0xA076, 0x13, BYTE_LEN, 0 },
        { 0xA077, 0xa2, BYTE_LEN, 0 },
        { 0xA078, 0x38, BYTE_LEN, 0 },
        { 0xA079, 0x45, BYTE_LEN, 0 },
        { 0xA07A, 0x2e, BYTE_LEN, 0 },
        { 0xA07B, 0x5d, BYTE_LEN, 0 },
        { 0xA07C, 0x51, BYTE_LEN, 0 },
        { 0xA07D, 0x0c, BYTE_LEN, 0 },
        { 0xA07E, 0x51, BYTE_LEN, 0 },
        { 0xA07F, 0xc6, BYTE_LEN, 0 },
        { 0xA080, 0x92, BYTE_LEN, 0 },
        { 0xA081, 0x13, BYTE_LEN, 0 },
        { 0xA082, 0xa8, BYTE_LEN, 0 },
        { 0xA083, 0x68, BYTE_LEN, 0 },
        { 0xA084, 0xa4, BYTE_LEN, 0 },
        { 0xA085, 0x24, BYTE_LEN, 0 },
        { 0xA086, 0x03, BYTE_LEN, 0 },
        { 0xA087, 0x29, BYTE_LEN, 0 },
        { 0xA088, 0x88, BYTE_LEN, 0 },
        { 0xA089, 0x3f, BYTE_LEN, 0 },
        { 0xA08A, 0xfc, BYTE_LEN, 0 },
        { 0xA08B, 0x71, BYTE_LEN, 0 },
        { 0xA08C, 0x10, BYTE_LEN, 0 },
        { 0xA08D, 0x86, BYTE_LEN, 0 },
        { 0xA08E, 0x90, BYTE_LEN, 0 },
        { 0xA08F, 0x44, BYTE_LEN, 0 },
        { 0xA090, 0x26, BYTE_LEN, 0 },
        { 0xA091, 0x45, BYTE_LEN, 0 },
        { 0xA092, 0x21, BYTE_LEN, 0 },
        { 0xA093, 0x4b, BYTE_LEN, 0 },
        { 0xA094, 0x54, BYTE_LEN, 0 },
        { 0xA095, 0xf4, BYTE_LEN, 0 },
        { 0xA096, 0x62, BYTE_LEN, 0 },
        { 0xA097, 0x94, BYTE_LEN, 0 },
        { 0xA098, 0xb1, BYTE_LEN, 0 },
        { 0xA099, 0xf0, BYTE_LEN, 0 },
        { 0xA09A, 0x44, BYTE_LEN, 0 },
        { 0xA09B, 0x2a, BYTE_LEN, 0 },
        { 0xA09C, 0x1d, BYTE_LEN, 0 },
        { 0xA09D, 0x39, BYTE_LEN, 0 },
        { 0xA09E, 0x89, BYTE_LEN, 0 },
        { 0xA09F, 0x41, BYTE_LEN, 0 },
        { 0xA0A0, 0x0e, BYTE_LEN, 0 },
        { 0xA0A1, 0x12, BYTE_LEN, 0 },
        { 0xA0A2, 0x90, BYTE_LEN, 0 },
        { 0xA0A3, 0x80, BYTE_LEN, 0 },
        { 0xA0A4, 0x2c, BYTE_LEN, 0 },
        { 0xA0A5, 0xc4, BYTE_LEN, 0 },
        { 0xA0A6, 0x21, BYTE_LEN, 0 },
        { 0xA0A7, 0x28, BYTE_LEN, 0 },
        { 0xA0A8, 0xa9, BYTE_LEN, 0 },
        { 0xA0A9, 0x09, BYTE_LEN, 0 },
        { 0xA0AA, 0x52, BYTE_LEN, 0 },
        { 0xA0AB, 0xcc, BYTE_LEN, 0 },
        { 0xA0AC, 0x32, BYTE_LEN, 0 },
        { 0xA0AD, 0x15, BYTE_LEN, 0 },
        { 0xA0AE, 0xbd, BYTE_LEN, 0 },
        { 0xA0AF, 0x54, BYTE_LEN, 0 },
        { 0xA0B0, 0xa5, BYTE_LEN, 0 },
        { 0xA0B1, 0x2e, BYTE_LEN, 0 },
        { 0xA0B2, 0x48, BYTE_LEN, 0 },
        { 0xA0B3, 0x09, BYTE_LEN, 0 },
        { 0xA0B4, 0x8b, BYTE_LEN, 0 },
        { 0xA0B5, 0x4b, BYTE_LEN, 0 },
        { 0xA0B6, 0x76, BYTE_LEN, 0 },
        { 0xA0B7, 0x82, BYTE_LEN, 0 },
        { 0xA0B8, 0x91, BYTE_LEN, 0 },
        { 0xA0B9, 0x8e, BYTE_LEN, 0 },
        { 0xA0BA, 0x4c, BYTE_LEN, 0 },
        { 0xA0BB, 0xc4, BYTE_LEN, 0 },
        { 0xA0BC, 0x22, BYTE_LEN, 0 },
        { 0xA0BD, 0x1e, BYTE_LEN, 0 },
        { 0xA0BE, 0x29, BYTE_LEN, 0 },
        { 0xA0BF, 0x09, BYTE_LEN, 0 },
        { 0xA0C0, 0x4e, BYTE_LEN, 0 },
        { 0xA0C1, 0x94, BYTE_LEN, 0 },
        { 0xA0C2, 0x42, BYTE_LEN, 0 },
        { 0xA0C3, 0x95, BYTE_LEN, 0 },
        { 0xA0C4, 0xb9, BYTE_LEN, 0 },
        { 0xA0C5, 0x8c, BYTE_LEN, 0 },
        { 0xA0C6, 0x45, BYTE_LEN, 0 },
        { 0xA0C7, 0x31, BYTE_LEN, 0 },
        { 0xA0C8, 0x6a, BYTE_LEN, 0 },
        { 0xA0C9, 0x89, BYTE_LEN, 0 },
        { 0xA0CA, 0x4c, BYTE_LEN, 0 },
        { 0xA0CB, 0x57, BYTE_LEN, 0 },
        { 0xA0CC, 0xfc, BYTE_LEN, 0 },
        { 0xA0CD, 0x62, BYTE_LEN, 0 },
        { 0xA0CE, 0x94, BYTE_LEN, 0 },
        { 0xA0CF, 0xaf, BYTE_LEN, 0 },
        { 0xA0D0, 0xe4, BYTE_LEN, 0 },
        { 0xA0D1, 0x44, BYTE_LEN, 0 },
        { 0xA0D2, 0x29, BYTE_LEN, 0 },
        { 0xA0D3, 0x35, BYTE_LEN, 0 },
        { 0xA0D4, 0x19, BYTE_LEN, 0 },
        { 0xA0D5, 0x0a, BYTE_LEN, 0 },
        { 0xA0D6, 0x4f, BYTE_LEN, 0 },
        { 0xA0D7, 0xa2, BYTE_LEN, 0 },
        { 0xA0D8, 0xe2, BYTE_LEN, 0 },
        { 0xA0D9, 0x94, BYTE_LEN, 0 },
        { 0xA0DA, 0xb5, BYTE_LEN, 0 },
        { 0xA0DB, 0xa4, BYTE_LEN, 0 },
        { 0xA0DC, 0xc5, BYTE_LEN, 0 },
        { 0xA0DD, 0x31, BYTE_LEN, 0 },
        { 0xA0DE, 0x7a, BYTE_LEN, 0 },
        { 0xA0DF, 0x29, BYTE_LEN, 0 },
        { 0xA0E0, 0x8d, BYTE_LEN, 0 },
        { 0xA0E1, 0x61, BYTE_LEN, 0 },
        { 0xA0E2, 0x78, BYTE_LEN, 0 },
        { 0xA0E3, 0x03, BYTE_LEN, 0 },
        { 0xA0E4, 0x18, BYTE_LEN, 0 },
        { 0xA0E5, 0xd8, BYTE_LEN, 0 },
        { 0xA0E6, 0x90, BYTE_LEN, 0 },
        { 0xA0E7, 0x85, BYTE_LEN, 0 },
        { 0xA0E8, 0x31, BYTE_LEN, 0 },
        { 0xA0E9, 0x58, BYTE_LEN, 0 },
        { 0xA0EA, 0xc9, BYTE_LEN, 0 },
        { 0xA0EB, 0x8b, BYTE_LEN, 0 },
        { 0xA0EC, 0x55, BYTE_LEN, 0 },
        { 0xA0ED, 0xe8, BYTE_LEN, 0 },
        { 0xA0EE, 0xb2, BYTE_LEN, 0 },
        { 0xA0EF, 0x15, BYTE_LEN, 0 },
        { 0xA0F0, 0xc0, BYTE_LEN, 0 },
        { 0xA0F1, 0xac, BYTE_LEN, 0 },
        { 0xA0F2, 0x25, BYTE_LEN, 0 },
        { 0xA0F3, 0x33, BYTE_LEN, 0 },
        { 0xA0F4, 0x8f, BYTE_LEN, 0 },
        { 0xA0F5, 0x19, BYTE_LEN, 0 },
        { 0xA0F6, 0x8e, BYTE_LEN, 0 },
        { 0xA0F7, 0x66, BYTE_LEN, 0 },
        { 0xA0F8, 0xa4, BYTE_LEN, 0 },
        { 0xA0F9, 0x23, BYTE_LEN, 0 },
        { 0xA0FA, 0x9a, BYTE_LEN, 0 },
        { 0xA0FB, 0xed, BYTE_LEN, 0 },
        { 0xA0FC, 0x94, BYTE_LEN, 0 },
        { 0xA0FD, 0xe6, BYTE_LEN, 0 },
        { 0xA0FE, 0x3b, BYTE_LEN, 0 },
        { 0xA0FF, 0x92, BYTE_LEN, 0 },
        { 0xA100, 0x41, BYTE_LEN, 0 },
        { 0xA101, 0x0e, BYTE_LEN, 0 },
        { 0xA102, 0x61, BYTE_LEN, 0 },
        { 0xA103, 0x70, BYTE_LEN, 0 },
        { 0xA104, 0x33, BYTE_LEN, 0 },
        { 0xA105, 0x98, BYTE_LEN, 0 },
        { 0xA106, 0xdb, BYTE_LEN, 0 },
        { 0xA107, 0x28, BYTE_LEN, 0 },
        { 0xA108, 0x06, BYTE_LEN, 0 },
        { 0xA109, 0x38, BYTE_LEN, 0 },
        { 0xA10A, 0x9b, BYTE_LEN, 0 },
        { 0xA10B, 0xb1, BYTE_LEN, 0 },
        { 0xA10C, 0xce, BYTE_LEN, 0 },
        { 0xA10D, 0x6c, BYTE_LEN, 0 },
        { 0xA10E, 0xe6, BYTE_LEN, 0 },
        { 0xA10F, 0x23, BYTE_LEN, 0 },
        { 0xA110, 0x9b, BYTE_LEN, 0 },
        { 0xA111, 0xf9, BYTE_LEN, 0 },
        { 0xA112, 0x20, BYTE_LEN, 0 },
        { 0xA113, 0xe6, BYTE_LEN, 0 },
        { 0xA114, 0x37, BYTE_LEN, 0 },
        { 0xA115, 0x97, BYTE_LEN, 0 },
        { 0xA116, 0x71, BYTE_LEN, 0 },
        { 0xA117, 0x8e, BYTE_LEN, 0 },
        { 0xA118, 0x64, BYTE_LEN, 0 },
        { 0xA119, 0x96, BYTE_LEN, 0 },
        { 0xA11A, 0x63, BYTE_LEN, 0 },
        { 0xA11B, 0x18, BYTE_LEN, 0 },
        { 0xA11C, 0xdf, BYTE_LEN, 0 },
        { 0xA11D, 0x18, BYTE_LEN, 0 },
        { 0xA11E, 0x26, BYTE_LEN, 0 },
        { 0xA11F, 0x38, BYTE_LEN, 0 },
        { 0xA120, 0x8d, BYTE_LEN, 0 },
        { 0xA121, 0x31, BYTE_LEN, 0 },
        { 0xA122, 0x4e, BYTE_LEN, 0 },
        { 0xA123, 0x67, BYTE_LEN, 0 },
        { 0xA124, 0xb2, BYTE_LEN, 0 },
        { 0xA125, 0x43, BYTE_LEN, 0 },
        { 0xA126, 0x1a, BYTE_LEN, 0 },
        { 0xA127, 0xf1, BYTE_LEN, 0 },
        { 0xA128, 0x44, BYTE_LEN, 0 },
        { 0xA129, 0x26, BYTE_LEN, 0 },
        { 0xA12A, 0x3a, BYTE_LEN, 0 },
        { 0xA12B, 0x68, BYTE_LEN, 0 },
        { 0xA12C, 0x21, BYTE_LEN, 0 },
        { 0xA12D, 0x4c, BYTE_LEN, 0 },
        { 0xA12E, 0x5d, BYTE_LEN, 0 },
        { 0xA12F, 0x20, BYTE_LEN, 0 },
        { 0xA130, 0x53, BYTE_LEN, 0 },
        { 0xA131, 0x17, BYTE_LEN, 0 },
        { 0xA132, 0xc5, BYTE_LEN, 0 },
        { 0xA133, 0xb0, BYTE_LEN, 0 },
        { 0xA134, 0xc5, BYTE_LEN, 0 },
        { 0xA135, 0x2f, BYTE_LEN, 0 },
        { 0xA136, 0x6c, BYTE_LEN, 0 },
        { 0xA137, 0xf1, BYTE_LEN, 0 },
        { 0xA138, 0x4b, BYTE_LEN, 0 },
        { 0xA139, 0x5d, BYTE_LEN, 0 },
        { 0xA13A, 0x06, BYTE_LEN, 0 },
        { 0xA13B, 0x63, BYTE_LEN, 0 },
        { 0xA13C, 0x18, BYTE_LEN, 0 },
        { 0xA13D, 0xcb, BYTE_LEN, 0 },
        { 0xA13E, 0x1c, BYTE_LEN, 0 },
        { 0xA13F, 0x86, BYTE_LEN, 0 },
        { 0xA140, 0x33, BYTE_LEN, 0 },
        { 0xA141, 0x72, BYTE_LEN, 0 },
        { 0xA142, 0x39, BYTE_LEN, 0 },
        { 0xA143, 0x4c, BYTE_LEN, 0 },
        { 0xA144, 0x5f, BYTE_LEN, 0 },
        { 0xA145, 0x32, BYTE_LEN, 0 },
        { 0xA146, 0x13, BYTE_LEN, 0 },
        { 0xA147, 0x98, BYTE_LEN, 0 },
        { 0xA148, 0xcd, BYTE_LEN, 0 },
        { 0xA149, 0xc8, BYTE_LEN, 0 },
        { 0xA14A, 0x05, BYTE_LEN, 0 },
        { 0xA14B, 0x31, BYTE_LEN, 0 },
        { 0xA14C, 0x69, BYTE_LEN, 0 },
        { 0xA14D, 0xd9, BYTE_LEN, 0 },
        { 0xA14E, 0x0b, BYTE_LEN, 0 },
        { 0xA14F, 0x5a, BYTE_LEN, 0 },
        { 0xA150, 0xf0, BYTE_LEN, 0 },
        { 0xA151, 0x22, BYTE_LEN, 0 },
        { 0xA152, 0x17, BYTE_LEN, 0 },
        { 0xA153, 0xc0, BYTE_LEN, 0 },
        { 0xA154, 0x0c, BYTE_LEN, 0 },
        { 0xA155, 0x86, BYTE_LEN, 0 },
        { 0xA156, 0x32, BYTE_LEN, 0 },
        { 0xA157, 0x96, BYTE_LEN, 0 },
        { 0xA158, 0x51, BYTE_LEN, 0 },
        { 0xA159, 0x4d, BYTE_LEN, 0 },
        { 0xA15A, 0x64, BYTE_LEN, 0 },
        { 0xA15B, 0x50, BYTE_LEN, 0 },
        { 0xA15C, 0x73, BYTE_LEN, 0 },
        { 0xA15D, 0x16, BYTE_LEN, 0 },
        { 0xA15E, 0xbf, BYTE_LEN, 0 },
        { 0xA15F, 0x88, BYTE_LEN, 0 },
        { 0xA160, 0x05, BYTE_LEN, 0 },
        { 0xA161, 0x2f, BYTE_LEN, 0 },
        { 0xA162, 0x4a, BYTE_LEN, 0 },
        { 0xA163, 0xe1, BYTE_LEN, 0 },
        { 0xA164, 0x4a, BYTE_LEN, 0 },
        { 0xA165, 0x50, BYTE_LEN, 0 },
        { 0xA166, 0x9e, BYTE_LEN, 0 },
        { 0xA167, 0x12, BYTE_LEN, 0 },
        { 0xA168, 0x14, BYTE_LEN, 0 },
        { 0xA169, 0xa6, BYTE_LEN, 0 },
        { 0xA16A, 0x20, BYTE_LEN, 0 },
        { 0xA16B, 0x85, BYTE_LEN, 0 },
        { 0xA16C, 0x2a, BYTE_LEN, 0 },
        { 0xA16D, 0x58, BYTE_LEN, 0 },
        { 0xA16E, 0x31, BYTE_LEN, 0 },
        { 0xA16F, 0x8b, BYTE_LEN, 0 },
        { 0xA170, 0x5d, BYTE_LEN, 0 },
        { 0xA171, 0x0e, BYTE_LEN, 0 },
        { 0xA172, 0xf3, BYTE_LEN, 0 },
        { 0xA173, 0x97, BYTE_LEN, 0 },
        { 0xA174, 0xc8, BYTE_LEN, 0 },
        { 0xA175, 0x30, BYTE_LEN, 0 },
        { 0xA176, 0x45, BYTE_LEN, 0 },
        { 0xA177, 0x2c, BYTE_LEN, 0 },
        { 0xA178, 0x44, BYTE_LEN, 0 },
        { 0xA179, 0xb1, BYTE_LEN, 0 },
        { 0xA17A, 0x8a, BYTE_LEN, 0 },
        { 0xA17B, 0x4c, BYTE_LEN, 0 },
        { 0xA17C, 0x80, BYTE_LEN, 0 },
        { 0xA17D, 0x72, BYTE_LEN, 0 },
        { 0xA17E, 0x12, BYTE_LEN, 0 },
        { 0xA17F, 0x98, BYTE_LEN, 0 },
        { 0xA180, 0x94, BYTE_LEN, 0 },
        { 0xA181, 0x84, BYTE_LEN, 0 },
        { 0xA182, 0x25, BYTE_LEN, 0 },
        { 0xA183, 0x2d, BYTE_LEN, 0 },
        { 0xA184, 0xa9, BYTE_LEN, 0 },
        { 0xA185, 0x49, BYTE_LEN, 0 },
        { 0xA186, 0x4f, BYTE_LEN, 0 },
        { 0xA187, 0x90, BYTE_LEN, 0 },
        { 0xA188, 0x62, BYTE_LEN, 0 },
        { 0xA189, 0x15, BYTE_LEN, 0 },
        { 0xA18A, 0xb1, BYTE_LEN, 0 },
        { 0xA18B, 0x90, BYTE_LEN, 0 },
        { 0xA18C, 0x05, BYTE_LEN, 0 },
        { 0xA18D, 0x2e, BYTE_LEN, 0 },
        { 0xA18E, 0x3c, BYTE_LEN, 0 },
        { 0xA18F, 0x71, BYTE_LEN, 0 },
        { 0xA190, 0x0a, BYTE_LEN, 0 },
        { 0xA191, 0x4d, BYTE_LEN, 0 },
        { 0xA192, 0x86, BYTE_LEN, 0 },
        { 0xA193, 0xf2, BYTE_LEN, 0 },
        { 0xA194, 0x91, BYTE_LEN, 0 },
        { 0xA195, 0x94, BYTE_LEN, 0 },
        { 0xA196, 0x34, BYTE_LEN, 0 },
        { 0xA197, 0x44, BYTE_LEN, 0 },
        { 0xA198, 0x22, BYTE_LEN, 0 },
        { 0xA199, 0x0b, BYTE_LEN, 0 },
        { 0xA19A, 0x69, BYTE_LEN, 0 },
        { 0xA19B, 0x08, BYTE_LEN, 0 },
        { 0xA19C, 0x45, BYTE_LEN, 0 },
        { 0xA19D, 0x2e, BYTE_LEN, 0 },
        { 0xA19E, 0xc2, BYTE_LEN, 0 },
        { 0xA19F, 0x92, BYTE_LEN, 0 },
        { 0xA1A0, 0x98, BYTE_LEN, 0 },
        { 0xA1A1, 0x14, BYTE_LEN, 0 },
        { 0xA1A2, 0xc5, BYTE_LEN, 0 },
        { 0xA1A3, 0x29, BYTE_LEN, 0 },
        { 0xA1A4, 0x50, BYTE_LEN, 0 },
        { 0xA1A5, 0xe1, BYTE_LEN, 0 },
        { 0xA1A6, 0x0a, BYTE_LEN, 0 },
        { 0xA1A7, 0x4c, BYTE_LEN, 0 },
        { 0xA1A8, 0x7e, BYTE_LEN, 0 },
        { 0xA1A9, 0xa2, BYTE_LEN, 0 },
        { 0xA1AA, 0x92, BYTE_LEN, 0 },
        { 0xA1AB, 0x9b, BYTE_LEN, 0 },
        { 0xA1AC, 0x4c, BYTE_LEN, 0 },
        { 0xA1AD, 0x64, BYTE_LEN, 0 },
        { 0xA1AE, 0x23, BYTE_LEN, 0 },
        { 0xA1AF, 0x01, BYTE_LEN, 0 },
        { 0xA1B0, 0x21, BYTE_LEN, 0 },
        { 0xA1B1, 0xc8, BYTE_LEN, 0 },
        { 0xA1B2, 0x3f, BYTE_LEN, 0 },
        { 0xA1B3, 0xfe, BYTE_LEN, 0 },
        { 0xA1B4, 0x81, BYTE_LEN, 0 },
        { 0xA1B5, 0x10, BYTE_LEN, 0 },
        { 0xA1B6, 0x84, BYTE_LEN, 0 },
        { 0xA1B7, 0x84, BYTE_LEN, 0 },
        { 0xA1B8, 0x84, BYTE_LEN, 0 },
        { 0xA1B9, 0x24, BYTE_LEN, 0 },
        { 0xA1BA, 0x3d, BYTE_LEN, 0 },
        { 0xA1BB, 0x21, BYTE_LEN, 0 },
        { 0xA1BC, 0x0a, BYTE_LEN, 0 },
        { 0xA1BD, 0x51, BYTE_LEN, 0 },
        { 0xA1BE, 0xa0, BYTE_LEN, 0 },
        { 0xA1BF, 0x22, BYTE_LEN, 0 },
        { 0xA1C0, 0x13, BYTE_LEN, 0 },
        { 0xA1C1, 0xa0, BYTE_LEN, 0 },
        { 0xA1C2, 0xb0, BYTE_LEN, 0 },
        { 0xA1C3, 0x04, BYTE_LEN, 0 },
        { 0xA1C4, 0x27, BYTE_LEN, 0 },
        { 0xA1C5, 0x14, BYTE_LEN, 0 },
        { 0xA1C6, 0xe1, BYTE_LEN, 0 },
        { 0xA1C7, 0x88, BYTE_LEN, 0 },
        { 0xA1C8, 0x40, BYTE_LEN, 0 },
        { 0xA1C9, 0x0a, BYTE_LEN, 0 },
        { 0xA1CA, 0x02, BYTE_LEN, 0 },
        { 0xA1CB, 0x10, BYTE_LEN, 0 },
        { 0xA1CC, 0x80, BYTE_LEN, 0 },
        { 0xA1CD, 0x24, BYTE_LEN, 0 },
        { 0xA1CE, 0x24, BYTE_LEN, 0 },
        { 0xA1CF, 0x21, BYTE_LEN, 0 },
        { 0xA1D0, 0x21, BYTE_LEN, 0 },
        { 0xA1D1, 0x21, BYTE_LEN, 0 },
        { 0xA1D2, 0x09, BYTE_LEN, 0 },
        { 0xA1D3, 0x4f, BYTE_LEN, 0 },
        { 0xA1D4, 0x8a, BYTE_LEN, 0 },
        { 0xA1D5, 0x32, BYTE_LEN, 0 },
        { 0xA1D6, 0x94, BYTE_LEN, 0 },
        { 0xA1D7, 0xa8, BYTE_LEN, 0 },
        { 0xA1D8, 0x08, BYTE_LEN, 0 },
        { 0xA1D9, 0xe5, BYTE_LEN, 0 },
        { 0xA1DA, 0x29, BYTE_LEN, 0 },
        { 0xA1DB, 0x39, BYTE_LEN, 0 },
        { 0xA1DC, 0x21, BYTE_LEN, 0 },
        { 0xA1DD, 0xca, BYTE_LEN, 0 },
        { 0xA1DE, 0x48, BYTE_LEN, 0 },
        { 0xA1DF, 0x56, BYTE_LEN, 0 },
        { 0xA1E0, 0x02, BYTE_LEN, 0 },
        { 0xA1E1, 0x11, BYTE_LEN, 0 },
        { 0xA1E2, 0x8b, BYTE_LEN, 0 },
        { 0xA1E3, 0x34, BYTE_LEN, 0 },
        { 0xA1E4, 0x24, BYTE_LEN, 0 },
        { 0xA1E5, 0x22, BYTE_LEN, 0 },
        { 0xA1E6, 0x16, BYTE_LEN, 0 },
        { 0xA1E7, 0xd1, BYTE_LEN, 0 },
        { 0xA1E8, 0x48, BYTE_LEN, 0 },
        { 0xA1E9, 0x4b, BYTE_LEN, 0 },
        { 0xA1EA, 0x68, BYTE_LEN, 0 },
        { 0xA1EB, 0x22, BYTE_LEN, 0 },
        { 0xA1EC, 0x14, BYTE_LEN, 0 },
        { 0xA1ED, 0xa8, BYTE_LEN, 0 },
        { 0xA1EE, 0x30, BYTE_LEN, 0 },
        { 0xA1EF, 0xe5, BYTE_LEN, 0 },
        { 0xA1F0, 0x2b, BYTE_LEN, 0 },
        { 0xA1F1, 0x57, BYTE_LEN, 0 },
        { 0xA1F2, 0x11, BYTE_LEN, 0 },
        { 0xA1F3, 0x4b, BYTE_LEN, 0 },
        { 0xA1F4, 0x53, BYTE_LEN, 0 },
        { 0xA1F5, 0xae, BYTE_LEN, 0 },
        { 0xA1F6, 0x92, BYTE_LEN, 0 },
        { 0xA1F7, 0x93, BYTE_LEN, 0 },
        { 0xA1F8, 0xa1, BYTE_LEN, 0 },
        { 0xA1F9, 0xb0, BYTE_LEN, 0 },
        { 0xA1FA, 0xa4, BYTE_LEN, 0 },
        { 0xA1FB, 0x26, BYTE_LEN, 0 },
        { 0xA1FC, 0x29, BYTE_LEN, 0 },
        { 0xA1FD, 0x91, BYTE_LEN, 0 },
        { 0xA1FE, 0x09, BYTE_LEN, 0 },
        { 0xA1FF, 0x4c, BYTE_LEN, 0 },
        { 0xA200, 0x74, BYTE_LEN, 0 },
        { 0xA201, 0xd2, BYTE_LEN, 0 },
        { 0xA202, 0x93, BYTE_LEN, 0 },
        { 0xA203, 0xa5, BYTE_LEN, 0 },
        { 0xA204, 0x44, BYTE_LEN, 0 },
        { 0xA205, 0xa5, BYTE_LEN, 0 },
        { 0xA206, 0x2c, BYTE_LEN, 0 },
        { 0xA207, 0x5d, BYTE_LEN, 0 },
        { 0xA208, 0xa9, BYTE_LEN, 0 },
        { 0xA209, 0x0b, BYTE_LEN, 0 },
        { 0xA20A, 0x5d, BYTE_LEN, 0 },
        { 0xA20B, 0x06, BYTE_LEN, 0 },
        { 0xA20C, 0xf3, BYTE_LEN, 0 },
        { 0xA20D, 0x96, BYTE_LEN, 0 },
        { 0xA20E, 0xbe, BYTE_LEN, 0 },
        { 0xA20F, 0x50, BYTE_LEN, 0 },
        { 0xA210, 0x45, BYTE_LEN, 0 },
        { 0xA211, 0x2c, BYTE_LEN, 0 },
        { 0xA212, 0x49, BYTE_LEN, 0 },
        { 0xA213, 0xb1, BYTE_LEN, 0 },
        { 0xA214, 0x4a, BYTE_LEN, 0 },
        { 0xA215, 0x51, BYTE_LEN, 0 },
        { 0xA216, 0xa8, BYTE_LEN, 0 },
        { 0xA217, 0x82, BYTE_LEN, 0 },
        { 0xA218, 0x94, BYTE_LEN, 0 },
        { 0xA219, 0xad, BYTE_LEN, 0 },
        { 0xA21A, 0x50, BYTE_LEN, 0 },
        { 0xA21B, 0x85, BYTE_LEN, 0 },
        { 0xA21C, 0x2d, BYTE_LEN, 0 },
        { 0xA21D, 0x70, BYTE_LEN, 0 },
        { 0xA21E, 0x69, BYTE_LEN, 0 },
        { 0xA21F, 0xcc, BYTE_LEN, 0 },
        { 0xA220, 0x5d, BYTE_LEN, 0 },
        { 0xA221, 0x2c, BYTE_LEN, 0 },
        { 0xA222, 0xb3, BYTE_LEN, 0 },
        { 0xA223, 0x18, BYTE_LEN, 0 },
        { 0xA224, 0xcf, BYTE_LEN, 0 },
        { 0xA225, 0x3c, BYTE_LEN, 0 },
        { 0xA226, 0x46, BYTE_LEN, 0 },
        { 0xA227, 0x34, BYTE_LEN, 0 },
        { 0xA228, 0x80, BYTE_LEN, 0 },
        { 0xA229, 0x89, BYTE_LEN, 0 },
        { 0xA22A, 0xcc, BYTE_LEN, 0 },
        { 0xA22B, 0x5c, BYTE_LEN, 0 },
        { 0xA22C, 0x0a, BYTE_LEN, 0 },
        { 0xA22D, 0xd3, BYTE_LEN, 0 },
        { 0xA22E, 0x16, BYTE_LEN, 0 },
        { 0xA22F, 0xc1, BYTE_LEN, 0 },
        { 0xA230, 0xc8, BYTE_LEN, 0 },
        { 0xA231, 0x25, BYTE_LEN, 0 },
        { 0xA232, 0x31, BYTE_LEN, 0 },
        { 0xA233, 0x7f, BYTE_LEN, 0 },
        { 0xA234, 0xe9, BYTE_LEN, 0 },
        { 0xA235, 0x0c, BYTE_LEN, 0 },
        { 0xA236, 0x64, BYTE_LEN, 0 },
        { 0xA237, 0x64, BYTE_LEN, 0 },
        { 0xA238, 0xd3, BYTE_LEN, 0 },
        { 0xA239, 0x18, BYTE_LEN, 0 },
        { 0xA23A, 0xd7, BYTE_LEN, 0 },
        { 0xA23B, 0xc4, BYTE_LEN, 0 },
        { 0xA23C, 0xa5, BYTE_LEN, 0 },
        { 0xA23D, 0x30, BYTE_LEN, 0 },
        { 0xA23E, 0x82, BYTE_LEN, 0 },
        { 0xA23F, 0xa9, BYTE_LEN, 0 },
        { 0xA240, 0x4c, BYTE_LEN, 0 },
        { 0xA241, 0x60, BYTE_LEN, 0 },
        { 0xA242, 0x24, BYTE_LEN, 0 },
        { 0xA243, 0x53, BYTE_LEN, 0 },
        { 0xA244, 0x17, BYTE_LEN, 0 },
        { 0xA245, 0xc4, BYTE_LEN, 0 },
        { 0xA246, 0xc8, BYTE_LEN, 0 },
        { 0xA247, 0xc5, BYTE_LEN, 0 },
        { 0xA248, 0x30, BYTE_LEN, 0 },
        { 0xA249, 0x75, BYTE_LEN, 0 },
        { 0xA24A, 0x61, BYTE_LEN, 0 },
        { 0xA24B, 0x0c, BYTE_LEN, 0 },
        { 0xA24C, 0x60, BYTE_LEN, 0 },
        { 0xA24D, 0x3c, BYTE_LEN, 0 },
        { 0xA24E, 0x33, BYTE_LEN, 0 },
        { 0xA24F, 0x98, BYTE_LEN, 0 },
        { 0xA250, 0xd1, BYTE_LEN, 0 },
        { 0xA251, 0xbc, BYTE_LEN, 0 },
        { 0xA252, 0xc5, BYTE_LEN, 0 },
        { 0xA253, 0x31, BYTE_LEN, 0 },
        
        { 0xA254, 0x97, BYTE_LEN, 0 },
        { 0xA255, 0x21, BYTE_LEN, 0 },
        { 0xA256, 0x4d, BYTE_LEN, 0 },
        { 0xA257, 0x68, BYTE_LEN, 0 },
        { 0xA258, 0x28, BYTE_LEN, 0 },
        { 0xA259, 0x03, BYTE_LEN, 0 },
        { 0xA25A, 0x19, BYTE_LEN, 0 },
        { 0xA25B, 0xcc, BYTE_LEN, 0 },
        { 0xA25C, 0xa8, BYTE_LEN, 0 },
        { 0xA25D, 0x86, BYTE_LEN, 0 },
        { 0xA25E, 0x36, BYTE_LEN, 0 },
        { 0xA25F, 0xa3, BYTE_LEN, 0 },
        { 0xA260, 0x61, BYTE_LEN, 0 },
        { 0xA261, 0x8d, BYTE_LEN, 0 },
        { 0xA262, 0x6b, BYTE_LEN, 0 },
        { 0xA263, 0x36, BYTE_LEN, 0 },
        { 0xA264, 0xd3, BYTE_LEN, 0 },
        { 0xA265, 0x18, BYTE_LEN, 0 },
        { 0xA266, 0xc5, BYTE_LEN, 0 },
        { 0xA267, 0x48, BYTE_LEN, 0 },
        { 0xA268, 0xa6, BYTE_LEN, 0 },
        { 0xA269, 0x34, BYTE_LEN, 0 },
        { 0xA26A, 0xc1, BYTE_LEN, 0 },
        { 0xA26B, 0x09, BYTE_LEN, 0 },
        { 0xA26C, 0x4e, BYTE_LEN, 0 },
        { 0xA26D, 0x64, BYTE_LEN, 0 },
        { 0xA26E, 0x10, BYTE_LEN, 0 },
        { 0xA26F, 0x73, BYTE_LEN, 0 },
        { 0xA270, 0x16, BYTE_LEN, 0 },
        { 0xA271, 0xac, BYTE_LEN, 0 },
        { 0xA272, 0x5c, BYTE_LEN, 0 },
        { 0xA273, 0xa5, BYTE_LEN, 0 },
        { 0xA274, 0x2b, BYTE_LEN, 0 },
        { 0xA275, 0x71, BYTE_LEN, 0 },
        { 0xA276, 0xb9, BYTE_LEN, 0 },
        { 0xA277, 0x0c, BYTE_LEN, 0 },
        { 0xA278, 0x69, BYTE_LEN, 0 },
        { 0xA279, 0xe0, BYTE_LEN, 0 },
        { 0xA27A, 0x02, BYTE_LEN, 0 },
        { 0xA27B, 0x16, BYTE_LEN, 0 },
        { 0xA27C, 0xa3, BYTE_LEN, 0 },
        { 0xA27D, 0xcc, BYTE_LEN, 0 },
        { 0xA27E, 0xc4, BYTE_LEN, 0 },
        { 0xA27F, 0x25, BYTE_LEN, 0 },
        { 0xA280, 0x39, BYTE_LEN, 0 },
        { 0xA281, 0x79, BYTE_LEN, 0 },
        { 0xA282, 0xca, BYTE_LEN, 0 },
        { 0xA283, 0x5b, BYTE_LEN, 0 },
        { 0xA284, 0x08, BYTE_LEN, 0 },
        { 0xA285, 0xa3, BYTE_LEN, 0 },
        { 0xA286, 0x95, BYTE_LEN, 0 },
        { 0xA287, 0xa5, BYTE_LEN, 0 },
        { 0xA288, 0xb0, BYTE_LEN, 0 },
        { 0xA289, 0x64, BYTE_LEN, 0 },
        { 0xA28A, 0x22, BYTE_LEN, 0 },
        { 0xA28B, 0x0d, BYTE_LEN, 0 },
        { 0xA28C, 0xc9, BYTE_LEN, 0 },
        { 0xA28D, 0xc8, BYTE_LEN, 0 },
        { 0xA28E, 0x4d, BYTE_LEN, 0 },
        { 0xA28F, 0xb4, BYTE_LEN, 0 },
        { 0xA290, 0xe2, BYTE_LEN, 0 },
        { 0xA291, 0x16, BYTE_LEN, 0 },
        { 0xA292, 0xa6, BYTE_LEN, 0 },
        { 0xA293, 0x00, BYTE_LEN, 0 },
        { 0xA294, 0xc5, BYTE_LEN, 0 },
        { 0xA295, 0x23, BYTE_LEN, 0 },
        { 0xA296, 0x04, BYTE_LEN, 0 },
        { 0xA297, 0xf9, BYTE_LEN, 0 },
        { 0xA298, 0xc7, BYTE_LEN, 0 },
        { 0xA299, 0x42, BYTE_LEN, 0 },
        { 0xA29A, 0x52, BYTE_LEN, 0 },
        { 0xA29B, 0x12, BYTE_LEN, 0 },
        { 0xA29C, 0x15, BYTE_LEN, 0 },
        { 0xA29D, 0xb1, BYTE_LEN, 0 },
        { 0xA29E, 0x34, BYTE_LEN, 0 },
        { 0xA29F, 0x25, BYTE_LEN, 0 },
        { 0xA2A0, 0x28, BYTE_LEN, 0 },
        { 0xA2A1, 0x20, BYTE_LEN, 0 },
        { 0xA2A2, 0x31, BYTE_LEN, 0 },
        { 0xA2A3, 0x08, BYTE_LEN, 0 },
        { 0xA2A4, 0x40, BYTE_LEN, 0 },
        { 0xA2A5, 0x18, BYTE_LEN, 0 },
        { 0xA2A6, 0xc2, BYTE_LEN, 0 },
        { 0xA2A7, 0x92, BYTE_LEN, 0 },
        { 0xA2A8, 0xa9, BYTE_LEN, 0 },
        { 0xA2A9, 0x8c, BYTE_LEN, 0 },
        { 0xA2AA, 0x65, BYTE_LEN, 0 },
        { 0xA2AB, 0x2b, BYTE_LEN, 0 },
        { 0xA2AC, 0x4c, BYTE_LEN, 0 },
        { 0xA2AD, 0x81, BYTE_LEN, 0 },
        { 0xA2AE, 0x09, BYTE_LEN, 0 },
        { 0xA2AF, 0x46, BYTE_LEN, 0 },
        { 0xA2B0, 0x26, BYTE_LEN, 0 },
        { 0xA2B1, 0xf2, BYTE_LEN, 0 },
        { 0xA2B2, 0x91, BYTE_LEN, 0 },
        { 0xA2B3, 0x9e, BYTE_LEN, 0 },
        { 0xA2B4, 0x74, BYTE_LEN, 0 },
        { 0xA2B5, 0xe5, BYTE_LEN, 0 },
        { 0xA2B6, 0x2d, BYTE_LEN, 0 },
        { 0xA2B7, 0x73, BYTE_LEN, 0 },
        { 0xA2B8, 0x21, BYTE_LEN, 0 },
        { 0xA2B9, 0x0b, BYTE_LEN, 0 },
        { 0xA2BA, 0x53, BYTE_LEN, 0 },
        { 0xA2BB, 0x78, BYTE_LEN, 0 },
        { 0xA2BC, 0x72, BYTE_LEN, 0 },
        { 0xA2BD, 0x93, BYTE_LEN, 0 },
        { 0xA2BE, 0xa0, BYTE_LEN, 0 },
        { 0xA2BF, 0x58, BYTE_LEN, 0 },
        { 0xA2C0, 0x45, BYTE_LEN, 0 },
        { 0xA2C1, 0x2e, BYTE_LEN, 0 },
        { 0xA2C2, 0x85, BYTE_LEN, 0 },
        { 0xA2C3, 0xb9, BYTE_LEN, 0 },
        { 0xA2C4, 0x8c, BYTE_LEN, 0 },
        { 0xA2C5, 0x63, BYTE_LEN, 0 },
        { 0xA2C6, 0xde, BYTE_LEN, 0 },
        { 0xA2C7, 0x02, BYTE_LEN, 0 },
        { 0xA2C8, 0x96, BYTE_LEN, 0 },
        { 0xA2C9, 0xae, BYTE_LEN, 0 },
        { 0xA2CA, 0x98, BYTE_LEN, 0 },
        { 0xA2CB, 0x45, BYTE_LEN, 0 },
        { 0xA2CC, 0x2f, BYTE_LEN, 0 },
        { 0xA2CD, 0x9e, BYTE_LEN, 0 },
        { 0xA2CE, 0x59, BYTE_LEN, 0 },
        { 0xA2CF, 0xcd, BYTE_LEN, 0 },
        { 0xA2D0, 0x6c, BYTE_LEN, 0 },
        { 0xA2D1, 0x6c, BYTE_LEN, 0 },
        { 0xA2D2, 0x23, BYTE_LEN, 0 },
        { 0xA2D3, 0x1a, BYTE_LEN, 0 },
        { 0xA2D4, 0xca, BYTE_LEN, 0 },
        { 0xA2D5, 0x4c, BYTE_LEN, 0 },
        { 0xA2D6, 0x66, BYTE_LEN, 0 },
        { 0xA2D7, 0x33, BYTE_LEN, 0 },
        { 0xA2D8, 0xae, BYTE_LEN, 0 },
        { 0xA2D9, 0x39, BYTE_LEN, 0 },
        { 0xA2DA, 0x0e, BYTE_LEN, 0 },
        { 0xA2DB, 0x72, BYTE_LEN, 0 },
        { 0xA2DC, 0x30, BYTE_LEN, 0 },
        { 0xA2DD, 0x63, BYTE_LEN, 0 },
        { 0xA2DE, 0x9a, BYTE_LEN, 0 },
        { 0xA2DF, 0xd2, BYTE_LEN, 0 },
        { 0xA2E0, 0x64, BYTE_LEN, 0 },
        { 0xA2E1, 0x26, BYTE_LEN, 0 },
        { 0xA2E2, 0x33, BYTE_LEN, 0 },
        { 0xA2E3, 0x9f, BYTE_LEN, 0 },
        { 0xA2E4, 0x81, BYTE_LEN, 0 },
        { 0xA2E5, 0xcd, BYTE_LEN, 0 },
        { 0xA2E6, 0x6d, BYTE_LEN, 0 },
        { 0xA2E7, 0x50, BYTE_LEN, 0 },
        { 0xA2E8, 0x03, BYTE_LEN, 0 },
        { 0xA2E9, 0x13, BYTE_LEN, 0 },
        { 0xA2EA, 0xbc, BYTE_LEN, 0 },
        { 0xA2EB, 0x44, BYTE_LEN, 0 },
        { 0xA2EC, 0x14, BYTE_LEN, 0 },
        { 0xA2ED, 0xa6, BYTE_LEN, 0 },
        
        { 0xA2EE, 0xcd, BYTE_LEN, 0 },
        { 0xA2EF, 0xb9, BYTE_LEN, 0 },
        { 0xA2F0, 0x0e, BYTE_LEN, 0 },
        { 0xA2F1, 0x74, BYTE_LEN, 0 },
        { 0xA2F2, 0x7c, BYTE_LEN, 0 },
        { 0xA2F3, 0x83, BYTE_LEN, 0 },
        { 0xA2F4, 0x1b, BYTE_LEN, 0 },
        { 0xA2F5, 0xe0, BYTE_LEN, 0 },
        { 0xA2F6, 0x4c, BYTE_LEN, 0 },
        { 0xA2F7, 0xa7, BYTE_LEN, 0 },
        { 0xA2F8, 0x3b, BYTE_LEN, 0 },
        { 0xA2F9, 0xc8, BYTE_LEN, 0 },
        { 0xA2FA, 0x21, BYTE_LEN, 0 },
        { 0xA2FB, 0x8f, BYTE_LEN, 0 },
        { 0xA2FC, 0x78, BYTE_LEN, 0 },
        { 0xA2FD, 0x90, BYTE_LEN, 0 },
        { 0xA2FE, 0x43, BYTE_LEN, 0 },
        { 0xA2FF, 0x1b, BYTE_LEN, 0 },
        { 0xA300, 0xd7, BYTE_LEN, 0 },
        { 0xA301, 0xd8, BYTE_LEN, 0 },
        { 0xA302, 0x86, BYTE_LEN, 0 },
        { 0xA303, 0x39, BYTE_LEN, 0 },
        { 0xA304, 0xeb, BYTE_LEN, 0 },
        { 0xA305, 0x59, BYTE_LEN, 0 },
        { 0xA306, 0xcf, BYTE_LEN, 0 },
        { 0xA307, 0x70, BYTE_LEN, 0 },
        { 0xA308, 0x68, BYTE_LEN, 0 },
        { 0xA309, 0x83, BYTE_LEN, 0 },
        { 0xA30A, 0x98, BYTE_LEN, 0 },
        { 0xA30B, 0xb9, BYTE_LEN, 0 },
        { 0xA30C, 0xb8, BYTE_LEN, 0 },
        { 0xA30D, 0xa5, BYTE_LEN, 0 },
        { 0xA30E, 0x2e, BYTE_LEN, 0 },
        { 0xA30F, 0x8c, BYTE_LEN, 0 },
        { 0xA310, 0xc9, BYTE_LEN, 0 },
        { 0xA311, 0x8d, BYTE_LEN, 0 },
        { 0xA312, 0x72, BYTE_LEN, 0 },
        { 0xA313, 0x34, BYTE_LEN, 0 },
        { 0xA314, 0x33, BYTE_LEN, 0 },
        { 0xA315, 0x98, BYTE_LEN, 0 },
        { 0xA316, 0xae, BYTE_LEN, 0 },
        { 0xA317, 0x0c, BYTE_LEN, 0 },
        { 0xA318, 0x45, BYTE_LEN, 0 },
        { 0xA319, 0x27, BYTE_LEN, 0 },
        { 0xA31A, 0x46, BYTE_LEN, 0 },
        { 0xA31B, 0x09, BYTE_LEN, 0 },
        { 0xA31C, 0x4b, BYTE_LEN, 0 },
        { 0xA31D, 0x62, BYTE_LEN, 0 },
        { 0xA31E, 0x46, BYTE_LEN, 0 },
        { 0xA31F, 0x03, BYTE_LEN, 0 },
        { 0xA320, 0x98, BYTE_LEN, 0 },
        { 0xA321, 0xb3, BYTE_LEN, 0 },
        { 0xA322, 0xf0, BYTE_LEN, 0 },
        { 0xA323, 0x44, BYTE_LEN, 0 },
        { 0xA324, 0x23, BYTE_LEN, 0 },
        { 0xA325, 0x10, BYTE_LEN, 0 },
        { 0xA326, 0xe9, BYTE_LEN, 0 },
        { 0xA327, 0x48, BYTE_LEN, 0 },
        { 0xA328, 0x50, BYTE_LEN, 0 },
        { 0xA329, 0xdc, BYTE_LEN, 0 },
        { 0xA32A, 0x92, BYTE_LEN, 0 },
        { 0xA32B, 0x98, BYTE_LEN, 0 },
        { 0xA32C, 0xb7, BYTE_LEN, 0 },
        { 0xA32D, 0x64, BYTE_LEN, 0 },
        { 0xA32E, 0x25, BYTE_LEN, 0 },
        { 0xA32F, 0x25, BYTE_LEN, 0 },
        { 0xA330, 0x07, BYTE_LEN, 0 },
        { 0xA331, 0xf1, BYTE_LEN, 0 },
        { 0xA332, 0xc7, BYTE_LEN, 0 },
        { 0xA333, 0x42, BYTE_LEN, 0 },
        { 0xA334, 0x60, BYTE_LEN, 0 },
        { 0xA335, 0x22, BYTE_LEN, 0 },
        { 0xA336, 0x96, BYTE_LEN, 0 },
        { 0xA337, 0xbc, BYTE_LEN, 0 },
        { 0xA338, 0xc0, BYTE_LEN, 0 },
        { 0xA339, 0x65, BYTE_LEN, 0 },
        { 0xA33A, 0x2b, BYTE_LEN, 0 },
        { 0xA33B, 0x2c, BYTE_LEN, 0 },
        { 0xA33C, 0x51, BYTE_LEN, 0 },
        { 0xA33D, 0x48, BYTE_LEN, 0 },
        { 0xA33E, 0x40, BYTE_LEN, 0 },
        { 0xA33F, 0x1c, BYTE_LEN, 0 },
        { 0xA340, 0x32, BYTE_LEN, 0 },
        { 0xA341, 0x13, BYTE_LEN, 0 },
        { 0xA342, 0xb2, BYTE_LEN, 0 },
        { 0xA343, 0xe8, BYTE_LEN, 0 },
        { 0xA344, 0x65, BYTE_LEN, 0 },
        { 0xA345, 0x30, BYTE_LEN, 0 },
        { 0xA346, 0x6b, BYTE_LEN, 0 },
        { 0xA347, 0x11, BYTE_LEN, 0 },
        { 0xA348, 0x4a, BYTE_LEN, 0 },
        { 0xA349, 0x48, BYTE_LEN, 0 },
        { 0xA34A, 0x30, BYTE_LEN, 0 },
        { 0xA34B, 0x62, BYTE_LEN, 0 },
        { 0xA34C, 0x92, BYTE_LEN, 0 },
        { 0xA34D, 0xa4, BYTE_LEN, 0 },
        { 0xA34E, 0xcc, BYTE_LEN, 0 },
        { 0xA34F, 0x45, BYTE_LEN, 0 },
        { 0xA350, 0x31, BYTE_LEN, 0 },
        { 0xA351, 0xa1, BYTE_LEN, 0 },
        { 0xA352, 0x59, BYTE_LEN, 0 },
        { 0xA353, 0x0c, BYTE_LEN, 0 },
        { 0xA354, 0x5a, BYTE_LEN, 0 },
        { 0xA355, 0x9e, BYTE_LEN, 0 },
        { 0xA356, 0x72, BYTE_LEN, 0 },
        { 0xA357, 0x94, BYTE_LEN, 0 },
        { 0xA358, 0xa9, BYTE_LEN, 0 },
        { 0xA359, 0xac, BYTE_LEN, 0 },
        { 0xA35A, 0xc5, BYTE_LEN, 0 },
        { 0xA35B, 0x31, BYTE_LEN, 0 },
        { 0xA35C, 0xa6, BYTE_LEN, 0 },
        { 0xA35D, 0x71, BYTE_LEN, 0 },
        { 0xA35E, 0x0e, BYTE_LEN, 0 },
        { 0xA35F, 0x70, BYTE_LEN, 0 },
        { 0xA360, 0x2e, BYTE_LEN, 0 },
        { 0xA361, 0x13, BYTE_LEN, 0 },
        { 0xA362, 0x18, BYTE_LEN, 0 },
        { 0xA363, 0xbd, BYTE_LEN, 0 },
        { 0xA364, 0x08, BYTE_LEN, 0 },
        { 0xA365, 0x26, BYTE_LEN, 0 },
        { 0xA366, 0x33, BYTE_LEN, 0 },
        { 0xA367, 0xc2, BYTE_LEN, 0 },
        { 0xA368, 0x91, BYTE_LEN, 0 },
        { 0xA369, 0xce, BYTE_LEN, 0 },
        { 0xA36A, 0x7b, BYTE_LEN, 0 },
        { 0xA36B, 0xe2, BYTE_LEN, 0 },
        { 0xA36C, 0x73, BYTE_LEN, 0 },
        { 0xA36D, 0x1d, BYTE_LEN, 0 },
        { 0xA36E, 0xe1, BYTE_LEN, 0 },
        { 0xA36F, 0xf4, BYTE_LEN, 0 },
        { 0xA370, 0x66, BYTE_LEN, 0 },
        { 0xA371, 0x38, BYTE_LEN, 0 },
        { 0xA372, 0xd8, BYTE_LEN, 0 },
        { 0xA373, 0x91, BYTE_LEN, 0 },
        { 0xA374, 0x4f, BYTE_LEN, 0 },
        { 0xA375, 0x7c, BYTE_LEN, 0 },
        { 0xA376, 0xa4, BYTE_LEN, 0 },
        { 0xA377, 0x13, BYTE_LEN, 0 },
        { 0xA378, 0x1e, BYTE_LEN, 0 },
        { 0xA379, 0xed, BYTE_LEN, 0 },
        { 0xA37A, 0x28, BYTE_LEN, 0 },
        { 0xA37B, 0x07, BYTE_LEN, 0 },
        { 0xA37C, 0x39, BYTE_LEN, 0 },
        { 0xA37D, 0xca, BYTE_LEN, 0 },
        { 0xA37E, 0xd1, BYTE_LEN, 0 },
        { 0xA37F, 0x4e, BYTE_LEN, 0 },
        { 0xA380, 0x78, BYTE_LEN, 0 },
        { 0xA381, 0x96, BYTE_LEN, 0 },
        { 0xA382, 0xb3, BYTE_LEN, 0 },
        { 0xA383, 0x98, BYTE_LEN, 0 },
        { 0xA384, 0xc9, BYTE_LEN, 0 },
        { 0xA385, 0x38, BYTE_LEN, 0 },
        { 0xA386, 0x46, BYTE_LEN, 0 },
        { 0xA387, 0x30, BYTE_LEN, 0 },
        { 0xA388, 0x8b, BYTE_LEN, 0 },
        { 0xA389, 0x99, BYTE_LEN, 0 },
        { 0xA38A, 0x8c, BYTE_LEN, 0 },
        { 0xA38B, 0x63, BYTE_LEN, 0 },
        { 0xA38C, 0x04, BYTE_LEN, 0 },
        { 0xA38D, 0xc3, BYTE_LEN, 0 },
        { 0xA38E, 0x17, BYTE_LEN, 0 },
        { 0xA38F, 0xc4, BYTE_LEN, 0 },
        { 0xA390, 0x64, BYTE_LEN, 0 },
        { 0xA391, 0x46, BYTE_LEN, 0 },
        { 0xA392, 0x33, BYTE_LEN, 0 },
        { 0xA393, 0x88, BYTE_LEN, 0 },
        { 0xA394, 0xf1, BYTE_LEN, 0 },
        { 0xA395, 0x4c, BYTE_LEN, 0 },
        { 0xA396, 0x67, BYTE_LEN, 0 },
        { 0xA397, 0x10, BYTE_LEN, 0 },
        { 0xA398, 0xb3, BYTE_LEN, 0 },
        { 0xA399, 0x17, BYTE_LEN, 0 },
        { 0xA39A, 0xbb, BYTE_LEN, 0 },
        { 0xA39B, 0x00, BYTE_LEN, 0 },
        { 0xA39C, 0x66, BYTE_LEN, 0 },
        { 0xA39D, 0x32, BYTE_LEN, 0 },
        { 0xA39E, 0xa6, BYTE_LEN, 0 },
        { 0xA39F, 0x21, BYTE_LEN, 0 },
        { 0xA3A0, 0x0d, BYTE_LEN, 0 },
        { 0xA3A1, 0x61, BYTE_LEN, 0 },
        { 0xA3A2, 0xf6, BYTE_LEN, 0 },
        { 0xA3A3, 0xa2, BYTE_LEN, 0 },
        { 0xA3A4, 0x15, BYTE_LEN, 0 },
        { 0xA3A5, 0xa6, BYTE_LEN, 0 },
        { 0xA3A6, 0x20, BYTE_LEN, 0 },
        { 0xA3A7, 0xe5, BYTE_LEN, 0 },
        { 0xA3A8, 0x29, BYTE_LEN, 0 },
        { 0xA3A9, 0x60, BYTE_LEN, 0 },
        { 0xA3AA, 0x11, BYTE_LEN, 0 },
        { 0xA3AB, 0x8c, BYTE_LEN, 0 },
        { 0xA3AC, 0x63, BYTE_LEN, 0 },
        { 0xA3AD, 0xc8, BYTE_LEN, 0 },
        { 0xA3AE, 0x72, BYTE_LEN, 0 },
        { 0xA3AF, 0x95, BYTE_LEN, 0 },
        { 0xA3B0, 0x9f, BYTE_LEN, 0 },
        { 0xA3B1, 0xbc, BYTE_LEN, 0 },
        { 0xA3B2, 0x24, BYTE_LEN, 0 },
        { 0xA3B3, 0x25, BYTE_LEN, 0 },
        { 0xA3B4, 0x30, BYTE_LEN, 0 },
        { 0xA3B5, 0x09, BYTE_LEN, 0 },
        { 0xA3B6, 0x8a, BYTE_LEN, 0 },
        { 0xA3B7, 0x57, BYTE_LEN, 0 },
        { 0xA3B8, 0xe2, BYTE_LEN, 0 },
        { 0xA3B9, 0x22, BYTE_LEN, 0 },
        { 0xA3BA, 0x95, BYTE_LEN, 0 },
        { 0xA3BB, 0xa2, BYTE_LEN, 0 },
        { 0xA3BC, 0xa4, BYTE_LEN, 0 },
        { 0xA3BD, 0x64, BYTE_LEN, 0 },
        { 0xA3BE, 0x22, BYTE_LEN, 0 },
        { 0xA3BF, 0x0d, BYTE_LEN, 0 },
        { 0xA3C0, 0xa9, BYTE_LEN, 0 },
        { 0xA3C1, 0x88, BYTE_LEN, 0 },
        { 0xA3C2, 0x4b, BYTE_LEN, 0 },
        { 0xA3C3, 0x96, BYTE_LEN, 0 },
        { 0xA3C4, 0xa2, BYTE_LEN, 0 },
        { 0xA3C5, 0x15, BYTE_LEN, 0 },
        { 0xA3C6, 0xa1, BYTE_LEN, 0 },
        { 0xA3C7, 0xe0, BYTE_LEN, 0 },
        { 0xA3C8, 0x84, BYTE_LEN, 0 },
        { 0xA3C9, 0x23, BYTE_LEN, 0 },
        { 0xA3CA, 0x05, BYTE_LEN, 0 },
        { 0xA3CB, 0x01, BYTE_LEN, 0 },
        { 0xA3CC, 0x88, BYTE_LEN, 0 },
        { 0xA3CD, 0x41, BYTE_LEN, 0 },
        { 0xA3CE, 0x42, BYTE_LEN, 0 },
        { 0xA3CF, 0x12, BYTE_LEN, 0 },
        { 0xA3D0, 0x14, BYTE_LEN, 0 },
        { 0xA3D1, 0xa6, BYTE_LEN, 0 },
        { 0xA3D2, 0x10, BYTE_LEN, 0 },
        { 0xA3D3, 0x45, BYTE_LEN, 0 },
        { 0xA3D4, 0x27, BYTE_LEN, 0 },
        { 0xA3D5, 0x1d, BYTE_LEN, 0 },
        { 0xA3D6, 0x31, BYTE_LEN, 0 },
        { 0xA3D7, 0xc8, BYTE_LEN, 0 },
        { 0xA3D8, 0x3f, BYTE_LEN, 0 },
        { 0xA3D9, 0x0e, BYTE_LEN, 0 },
        { 0xA3DA, 0x12, BYTE_LEN, 0 },
        { 0xA3DB, 0x92, BYTE_LEN, 0 },
        { 0xA3DC, 0x9f, BYTE_LEN, 0 },
        { 0xA3DD, 0x28, BYTE_LEN, 0 },
        { 0xA3DE, 0xe5, BYTE_LEN, 0 },
        { 0xA3DF, 0x2a, BYTE_LEN, 0 },
        { 0xA3E0, 0x49, BYTE_LEN, 0 },
        { 0xA3E1, 0x69, BYTE_LEN, 0 },
        { 0xA3E2, 0x89, BYTE_LEN, 0 },
        { 0xA3E3, 0x45, BYTE_LEN, 0 },
        { 0xA3E4, 0x1c, BYTE_LEN, 0 },
        { 0xA3E5, 0x72, BYTE_LEN, 0 },
        { 0xA3E6, 0x11, BYTE_LEN, 0 },
        { 0xA3E7, 0x97, BYTE_LEN, 0 },
        { 0xA3E8, 0x1c, BYTE_LEN, 0 },
        { 0xA3E9, 0x65, BYTE_LEN, 0 },
        { 0xA3EA, 0x2a, BYTE_LEN, 0 },
        { 0xA3EB, 0x71, BYTE_LEN, 0 },
        { 0xA3EC, 0x11, BYTE_LEN, 0 },
        { 0xA3ED, 0x4b, BYTE_LEN, 0 },
        { 0xA3EE, 0x51, BYTE_LEN, 0 },
        { 0xA3EF, 0x62, BYTE_LEN, 0 },
        { 0xA3F0, 0xb2, BYTE_LEN, 0 },
        { 0xA3F1, 0x92, BYTE_LEN, 0 },
        { 0xA3F2, 0x99, BYTE_LEN, 0 },
        { 0xA3F3, 0x00, BYTE_LEN, 0 },
        { 0xA3F4, 0xe5, BYTE_LEN, 0 },
        { 0xA3F5, 0x2a, BYTE_LEN, 0 },
        { 0xA3F6, 0x67, BYTE_LEN, 0 },
        { 0xA3F7, 0x81, BYTE_LEN, 0 },
        { 0xA3F8, 0x8c, BYTE_LEN, 0 },
        { 0xA3F9, 0x61, BYTE_LEN, 0 },
        { 0xA3FA, 0xc6, BYTE_LEN, 0 },
        { 0xA3FB, 0x32, BYTE_LEN, 0 },
        { 0xA3FC, 0x95, BYTE_LEN, 0 },
        { 0xA3FD, 0xa5, BYTE_LEN, 0 },
        { 0xA3FE, 0x30, BYTE_LEN, 0 },
        { 0xA3FF, 0x45, BYTE_LEN, 0 },
        { 0xA400, 0x2b, BYTE_LEN, 0 },
        { 0xA401, 0x77, BYTE_LEN, 0 },
        { 0xA402, 0x09, BYTE_LEN, 0 },
        { 0xA403, 0x8c, BYTE_LEN, 0 },
        { 0xA404, 0x6a, BYTE_LEN, 0 },
        { 0xA405, 0x54, BYTE_LEN, 0 },
        { 0xA406, 0x43, BYTE_LEN, 0 },
        { 0xA407, 0x19, BYTE_LEN, 0 },
        { 0xA408, 0xc1, BYTE_LEN, 0 },
        { 0xA409, 0xdc, BYTE_LEN, 0 },
        { 0xA40A, 0x45, BYTE_LEN, 0 },
        { 0xA40B, 0x2f, BYTE_LEN, 0 },
        { 0xA40C, 0x87, BYTE_LEN, 0 },
        { 0xA40D, 0xd9, BYTE_LEN, 0 },
        { 0xA40E, 0x0c, BYTE_LEN, 0 },
        { 0xA40F, 0x67, BYTE_LEN, 0 },
        { 0xA410, 0x28, BYTE_LEN, 0 },
        { 0xA411, 0x03, BYTE_LEN, 0 },
        { 0xA412, 0x1a, BYTE_LEN, 0 },
        { 0xA413, 0xcc, BYTE_LEN, 0 },
        { 0xA414, 0x1c, BYTE_LEN, 0 },
        { 0xA415, 0xc6, BYTE_LEN, 0 },
        { 0xA416, 0x2f, BYTE_LEN, 0 },
        { 0xA417, 0x80, BYTE_LEN, 0 },
        { 0xA418, 0x51, BYTE_LEN, 0 },
        { 0xA419, 0x4c, BYTE_LEN, 0 },
        { 0xA41A, 0x64, BYTE_LEN, 0 },
        { 0xA41B, 0x06, BYTE_LEN, 0 },
        { 0xA41C, 0x03, BYTE_LEN, 0 },
        { 0xA41D, 0x00, BYTE_LEN, 0 },
        { 0xA41E, 0x00, BYTE_LEN, 0 },
        { 0xA41F, 0x00, BYTE_LEN, 0 },
        { 0xA420, 0x00, BYTE_LEN, 0 },
        { 0xA421, 0x0a, BYTE_LEN, 0 },
        
        { 0x0068, 0x5F, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain on
};

struct isx006_i2c_reg_conf isx006_SHD_MIN_2nd_settings[] = {
        //2009/12/28
        // ISX006 KMOT ES2 no.2 Module(Index1) 
        // PreSHD/SHD1/2/3 inifile
        // After Gamma 70%
        // SHD3 A+TLD
        { 0x0068, 0x50, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain off
        
        { 0x9000, 0x8282, WORD_LEN, 0 },
        { 0x9002, 0x01, BYTE_LEN, 0 },
        { 0x9003, 0x0e, BYTE_LEN, 0 },
        { 0x9004, 0x04, BYTE_LEN, 0 },
        { 0x9005, 0x38, BYTE_LEN, 0 },
        { 0x9006, 0x20, BYTE_LEN, 0 },
        { 0x9007, 0x40, BYTE_LEN, 0 },
        { 0x9008, 0x01, BYTE_LEN, 0 },
        { 0x9009, 0x81, BYTE_LEN, 0 },
        { 0x900A, 0x04, BYTE_LEN, 0 },
        { 0x900B, 0x02, BYTE_LEN, 0 },
        { 0x900C, 0x14, BYTE_LEN, 0 },
        { 0x900D, 0x04, BYTE_LEN, 0 },
        { 0x900E, 0x50, BYTE_LEN, 0 },
        { 0x900F, 0x10, BYTE_LEN, 0 },
        { 0x9010, 0x60, BYTE_LEN, 0 },
        { 0x9011, 0x01, BYTE_LEN, 0 },
        { 0x9012, 0x01, BYTE_LEN, 0 },
        { 0x9013, 0x05, BYTE_LEN, 0 },
        { 0x9014, 0x04, BYTE_LEN, 0 },
        { 0x9015, 0x14, BYTE_LEN, 0 },
        { 0x9016, 0x04, BYTE_LEN, 0 },
        { 0x9017, 0x38, BYTE_LEN, 0 },
        { 0x9018, 0x10, BYTE_LEN, 0 },
        { 0x9019, 0xe0, BYTE_LEN, 0 },
        { 0x901A, 0x80, BYTE_LEN, 0 },
        { 0x901B, 0x00, BYTE_LEN, 0 },
        { 0x901C, 0x05, BYTE_LEN, 0 },
        { 0x901D, 0x04, BYTE_LEN, 0 },
        { 0x901E, 0x12, BYTE_LEN, 0 },
        { 0x901F, 0x08, BYTE_LEN, 0 },
        { 0x9020, 0x50, BYTE_LEN, 0 },
        { 0x9021, 0x10, BYTE_LEN, 0 },
        { 0x9022, 0x40, BYTE_LEN, 0 },
        { 0x9023, 0x41, BYTE_LEN, 0 },
        { 0x9024, 0x80, BYTE_LEN, 0 },
        { 0x9025, 0x05, BYTE_LEN, 0 },
        { 0x9026, 0x04, BYTE_LEN, 0 },
        { 0x9027, 0x14, BYTE_LEN, 0 },
        { 0x9028, 0x10, BYTE_LEN, 0 },
        { 0x9029, 0x50, BYTE_LEN, 0 },
        { 0x902A, 0x20, BYTE_LEN, 0 },
        { 0x902B, 0xe0, BYTE_LEN, 0 },
        { 0x902C, 0x80, BYTE_LEN, 0 },
        { 0x902D, 0x80, BYTE_LEN, 0 },
        { 0x902E, 0x03, BYTE_LEN, 0 },
        { 0x902F, 0x01, BYTE_LEN, 0 },
        { 0x9030, 0x12, BYTE_LEN, 0 },
        { 0x9031, 0x08, BYTE_LEN, 0 },
        { 0x9032, 0x40, BYTE_LEN, 0 },
        { 0x9033, 0x30, BYTE_LEN, 0 },
        { 0x9034, 0xe0, BYTE_LEN, 0 },
        { 0x9035, 0x80, BYTE_LEN, 0 },
        { 0x9036, 0x80, BYTE_LEN, 0 },
        { 0x9037, 0x03, BYTE_LEN, 0 },
        { 0x9038, 0x04, BYTE_LEN, 0 },
        { 0x9039, 0x14, BYTE_LEN, 0 },
        { 0x903A, 0x00, BYTE_LEN, 0 },
        { 0x903B, 0x48, BYTE_LEN, 0 },
        { 0x903C, 0x00, BYTE_LEN, 0 },
        { 0x903D, 0x20, BYTE_LEN, 0 },
        { 0x903E, 0x81, BYTE_LEN, 0 },
        { 0x903F, 0x00, BYTE_LEN, 0 },
        { 0x9040, 0x03, BYTE_LEN, 0 },
        { 0x9041, 0x02, BYTE_LEN, 0 },
        { 0x9042, 0x0c, BYTE_LEN, 0 },
        { 0x9043, 0x08, BYTE_LEN, 0 },
        { 0x9044, 0x30, BYTE_LEN, 0 },
        { 0x9045, 0x30, BYTE_LEN, 0 },
        { 0x9046, 0xa0, BYTE_LEN, 0 },
        { 0x9047, 0x80, BYTE_LEN, 0 },
        { 0x9048, 0x80, BYTE_LEN, 0 },
        { 0x9049, 0x02, BYTE_LEN, 0 },
        { 0x904A, 0x01, BYTE_LEN, 0 },
        { 0x904B, 0x0e, BYTE_LEN, 0 },
        { 0x904C, 0x08, BYTE_LEN, 0 },
        { 0x904D, 0x40, BYTE_LEN, 0 },
        { 0x904E, 0x30, BYTE_LEN, 0 },
        { 0x904F, 0x40, BYTE_LEN, 0 },
        { 0x9050, 0xc1, BYTE_LEN, 0 },
        { 0x9051, 0x00, BYTE_LEN, 0 },
        { 0x9052, 0x05, BYTE_LEN, 0 },
        { 0x9053, 0x04, BYTE_LEN, 0 },
        { 0x9054, 0x0a, BYTE_LEN, 0 },
        { 0x9055, 0x10, BYTE_LEN, 0 },
        { 0x9056, 0x28, BYTE_LEN, 0 },
        { 0x9057, 0x00, BYTE_LEN, 0 },
        { 0x9058, 0x80, BYTE_LEN, 0 },
        { 0x9059, 0x00, BYTE_LEN, 0 },
        { 0x905A, 0x81, BYTE_LEN, 0 },
        { 0x905B, 0x01, BYTE_LEN, 0 },
        { 0x905C, 0x02, BYTE_LEN, 0 },
        { 0x905D, 0x06, BYTE_LEN, 0 },
        { 0x905E, 0x08, BYTE_LEN, 0 },
        { 0x905F, 0x20, BYTE_LEN, 0 },
        { 0x9060, 0x10, BYTE_LEN, 0 },
        { 0x9061, 0xa0, BYTE_LEN, 0 },
        { 0x9062, 0x40, BYTE_LEN, 0 },
        { 0x9063, 0x00, BYTE_LEN, 0 },
        { 0x9064, 0x04, BYTE_LEN, 0 },
        { 0x9065, 0x01, BYTE_LEN, 0 },
        { 0x9066, 0x10, BYTE_LEN, 0 },
        { 0x9067, 0x08, BYTE_LEN, 0 },
        { 0x9068, 0x28, BYTE_LEN, 0 },
        { 0x9069, 0x20, BYTE_LEN, 0 },
        { 0x906A, 0xa0, BYTE_LEN, 0 },
        { 0x906B, 0x40, BYTE_LEN, 0 },
        { 0x906C, 0x80, BYTE_LEN, 0 },
        { 0x906D, 0x01, BYTE_LEN, 0 },
        { 0x906E, 0x02, BYTE_LEN, 0 },
        { 0x906F, 0x04, BYTE_LEN, 0 },
        { 0x9070, 0x08, BYTE_LEN, 0 },
        { 0x9071, 0x08, BYTE_LEN, 0 },
        { 0x9072, 0x10, BYTE_LEN, 0 },
        { 0x9073, 0x40, BYTE_LEN, 0 },
        { 0x9074, 0xc0, BYTE_LEN, 0 },
        { 0x9075, 0xff, BYTE_LEN, 0 },
        { 0x9076, 0x02, BYTE_LEN, 0 },
        { 0x9077, 0x00, BYTE_LEN, 0 },
        { 0x9078, 0x10, BYTE_LEN, 0 },
        { 0x9079, 0x00, BYTE_LEN, 0 },
        { 0x907A, 0x40, BYTE_LEN, 0 },
        { 0x907B, 0x50, BYTE_LEN, 0 },
        { 0x907C, 0x80, BYTE_LEN, 0 },
        { 0x907D, 0x40, BYTE_LEN, 0 },
        { 0x907E, 0x01, BYTE_LEN, 0 },
        { 0x907F, 0x02, BYTE_LEN, 0 },
        { 0x9080, 0x04, BYTE_LEN, 0 },
        { 0x9081, 0x04, BYTE_LEN, 0 },
        { 0x9082, 0x08, BYTE_LEN, 0 },
        { 0x9083, 0x10, BYTE_LEN, 0 },
        { 0x9084, 0x10, BYTE_LEN, 0 },
        { 0x9085, 0x00, BYTE_LEN, 0 },
        { 0x9086, 0x00, BYTE_LEN, 0 },
        { 0x9087, 0x80, BYTE_LEN, 0 },
        { 0x9088, 0x00, BYTE_LEN, 0 },
        { 0x9089, 0x01, BYTE_LEN, 0 },
        { 0x908A, 0x06, BYTE_LEN, 0 },
        { 0x908B, 0x04, BYTE_LEN, 0 },
        { 0x908C, 0x30, BYTE_LEN, 0 },
        { 0x908D, 0x10, BYTE_LEN, 0 },
        { 0x908E, 0xc0, BYTE_LEN, 0 },
        { 0x908F, 0x80, BYTE_LEN, 0 },
        { 0x9090, 0x00, BYTE_LEN, 0 },
        { 0x9091, 0x02, BYTE_LEN, 0 },
        { 0x9092, 0x02, BYTE_LEN, 0 },
        { 0x9093, 0x08, BYTE_LEN, 0 },
        { 0x9094, 0x08, BYTE_LEN, 0 },
        { 0x9095, 0x10, BYTE_LEN, 0 },
        { 0x9096, 0x30, BYTE_LEN, 0 },
        { 0x9097, 0x20, BYTE_LEN, 0 },
        { 0x9098, 0x00, BYTE_LEN, 0 },
        { 0x9099, 0x81, BYTE_LEN, 0 },
        { 0x909A, 0x00, BYTE_LEN, 0 },
        { 0x909B, 0x03, BYTE_LEN, 0 },
        { 0x909C, 0x02, BYTE_LEN, 0 },
        { 0x909D, 0x08, BYTE_LEN, 0 },
        { 0x909E, 0x18, BYTE_LEN, 0 },
        { 0x909F, 0x30, BYTE_LEN, 0 },
        { 0x90A0, 0xa0, BYTE_LEN, 0 },
        { 0x90A1, 0xc0, BYTE_LEN, 0 },
        { 0x90A2, 0x80, BYTE_LEN, 0 },
        { 0x90A3, 0x02, BYTE_LEN, 0 },
        { 0x90A4, 0x04, BYTE_LEN, 0 },
        { 0x90A5, 0x0a, BYTE_LEN, 0 },
        { 0x90A6, 0x10, BYTE_LEN, 0 },
        { 0x90A7, 0x28, BYTE_LEN, 0 },
        { 0x90A8, 0x10, BYTE_LEN, 0 },
        { 0x90A9, 0x60, BYTE_LEN, 0 },
        { 0x90AA, 0xc0, BYTE_LEN, 0 },
        { 0x90AB, 0x80, BYTE_LEN, 0 },
        { 0x90AC, 0x01, BYTE_LEN, 0 },
        { 0x90AD, 0x04, BYTE_LEN, 0 },
        { 0x90AE, 0x08, BYTE_LEN, 0 },
        { 0x90AF, 0x0c, BYTE_LEN, 0 },
        { 0x90B0, 0x10, BYTE_LEN, 0 },
        { 0x90B1, 0x30, BYTE_LEN, 0 },
        { 0x90B2, 0x80, BYTE_LEN, 0 },
        { 0x90B3, 0x00, BYTE_LEN, 0 },
        { 0x90B4, 0x81, BYTE_LEN, 0 },
        { 0x90B5, 0x02, BYTE_LEN, 0 },
        { 0x90B6, 0x04, BYTE_LEN, 0 },
        { 0x90B7, 0x0a, BYTE_LEN, 0 },
        { 0x90B8, 0x08, BYTE_LEN, 0 },
        { 0x90B9, 0x18, BYTE_LEN, 0 },
        { 0x90BA, 0x20, BYTE_LEN, 0 },
        { 0x90BB, 0x60, BYTE_LEN, 0 },
        { 0x90BC, 0x00, BYTE_LEN, 0 },
        { 0x90BD, 0x01, BYTE_LEN, 0 },
        { 0x90BE, 0x02, BYTE_LEN, 0 },
        { 0x90BF, 0x05, BYTE_LEN, 0 },
        { 0x90C0, 0x0a, BYTE_LEN, 0 },
        { 0x90C1, 0x18, BYTE_LEN, 0 },
        { 0x90C2, 0x28, BYTE_LEN, 0 },
        { 0x90C3, 0x20, BYTE_LEN, 0 },
        { 0x90C4, 0x80, BYTE_LEN, 0 },
        { 0x90C5, 0xc0, BYTE_LEN, 0 },
        { 0x90C6, 0x80, BYTE_LEN, 0 },
        { 0x90C7, 0x02, BYTE_LEN, 0 },
        { 0x90C8, 0x03, BYTE_LEN, 0 },
        { 0x90C9, 0x0c, BYTE_LEN, 0 },
        { 0x90CA, 0x0c, BYTE_LEN, 0 },
        { 0x90CB, 0x30, BYTE_LEN, 0 },
        { 0x90CC, 0x40, BYTE_LEN, 0 },
        { 0x90CD, 0x80, BYTE_LEN, 0 },
        { 0x90CE, 0x00, BYTE_LEN, 0 },
        { 0x90CF, 0x01, BYTE_LEN, 0 },
        { 0x90D0, 0x02, BYTE_LEN, 0 },
        { 0x90D1, 0x04, BYTE_LEN, 0 },
        { 0x90D2, 0x0c, BYTE_LEN, 0 },
        { 0x90D3, 0x08, BYTE_LEN, 0 },
        { 0x90D4, 0x30, BYTE_LEN, 0 },
        { 0x90D5, 0x60, BYTE_LEN, 0 },
        { 0x90D6, 0xc0, BYTE_LEN, 0 },
        { 0x90D7, 0x80, BYTE_LEN, 0 },
        { 0x90D8, 0x81, BYTE_LEN, 0 },
        { 0x90D9, 0x03, BYTE_LEN, 0 },
        { 0x90DA, 0x05, BYTE_LEN, 0 },
        { 0x90DB, 0x0a, BYTE_LEN, 0 },
        { 0x90DC, 0x18, BYTE_LEN, 0 },
        { 0x90DD, 0x30, BYTE_LEN, 0 },
        { 0x90DE, 0x60, BYTE_LEN, 0 },
        { 0x90DF, 0xc0, BYTE_LEN, 0 },
        { 0x90E0, 0x00, BYTE_LEN, 0 },
        { 0x90E1, 0x01, BYTE_LEN, 0 },
        { 0x90E2, 0x02, BYTE_LEN, 0 },
        { 0x90E3, 0x04, BYTE_LEN, 0 },
        { 0x90E4, 0x08, BYTE_LEN, 0 },
        { 0x90E5, 0x10, BYTE_LEN, 0 },
        { 0x90E6, 0x30, BYTE_LEN, 0 },
        { 0x90E7, 0x20, BYTE_LEN, 0 },
        { 0x90E8, 0xc0, BYTE_LEN, 0 },
        { 0x90E9, 0x80, BYTE_LEN, 0 },
        { 0x90EA, 0x01, BYTE_LEN, 0 },
        { 0x90EB, 0x03, BYTE_LEN, 0 },
        { 0x90EC, 0x06, BYTE_LEN, 0 },
        { 0x90ED, 0x0e, BYTE_LEN, 0 },
        { 0x90EE, 0x14, BYTE_LEN, 0 },
        { 0x90EF, 0x28, BYTE_LEN, 0 },
        { 0x90F0, 0x60, BYTE_LEN, 0 },
        { 0x90F1, 0xc0, BYTE_LEN, 0 },
        { 0x90F2, 0x80, BYTE_LEN, 0 },
        { 0x90F3, 0x01, BYTE_LEN, 0 },
        { 0x90F4, 0x03, BYTE_LEN, 0 },
        { 0x90F5, 0x02, BYTE_LEN, 0 },
        { 0x90F6, 0xe8, BYTE_LEN, 0 },
        { 0x90F7, 0x0b, BYTE_LEN, 0 },
        { 0x90F8, 0xa0, BYTE_LEN, 0 },
        { 0x90F9, 0x4f, BYTE_LEN, 0 },
        { 0x90FA, 0x60, BYTE_LEN, 0 },
        { 0x90FB, 0x3e, BYTE_LEN, 0 },
        { 0x90FC, 0x80, BYTE_LEN, 0 },
        { 0x90FD, 0xfa, BYTE_LEN, 0 },
        { 0x90FE, 0x00, BYTE_LEN, 0 },
        { 0x90FF, 0xec, BYTE_LEN, 0 },
        { 0x9100, 0x07, BYTE_LEN, 0 },
        { 0x9101, 0xc0, BYTE_LEN, 0 },
        { 0x9102, 0x0f, BYTE_LEN, 0 },
        { 0x9103, 0x80, BYTE_LEN, 0 },
        { 0x9104, 0x7e, BYTE_LEN, 0 },
        { 0x9105, 0x00, BYTE_LEN, 0 },
        { 0x9106, 0xfd, BYTE_LEN, 0 },
        { 0x9107, 0x01, BYTE_LEN, 0 },
        { 0x9108, 0xf4, BYTE_LEN, 0 },
        { 0x9109, 0x0b, BYTE_LEN, 0 },
        { 0x910A, 0xa0, BYTE_LEN, 0 },
        { 0x910B, 0x2f, BYTE_LEN, 0 },
        { 0x910C, 0x80, BYTE_LEN, 0 },
        { 0x910D, 0x3e, BYTE_LEN, 0 },
        { 0x910E, 0x81, BYTE_LEN, 0 },
        { 0x910F, 0xf9, BYTE_LEN, 0 },
        { 0x9110, 0x00, BYTE_LEN, 0 },
        { 0x9111, 0xea, BYTE_LEN, 0 },
        { 0x9112, 0x03, BYTE_LEN, 0 },
        { 0x9113, 0xb0, BYTE_LEN, 0 },
        { 0x9114, 0x1f, BYTE_LEN, 0 },
        { 0x9115, 0x00, BYTE_LEN, 0 },
        { 0x9116, 0x3f, BYTE_LEN, 0 },
        { 0x9117, 0x00, BYTE_LEN, 0 },
        { 0x9118, 0xfa, BYTE_LEN, 0 },
        { 0x9119, 0x01, BYTE_LEN, 0 },
        { 0x911A, 0xf4, BYTE_LEN, 0 },
        { 0x911B, 0x07, BYTE_LEN, 0 },
        { 0x911C, 0xd0, BYTE_LEN, 0 },
        { 0x911D, 0x2f, BYTE_LEN, 0 },
        { 0x911E, 0x80, BYTE_LEN, 0 },
        { 0x911F, 0xbe, BYTE_LEN, 0 },
        { 0x9120, 0x00, BYTE_LEN, 0 },
        { 0x9121, 0xfa, BYTE_LEN, 0 },
        { 0x9122, 0x02, BYTE_LEN, 0 },
        { 0x9123, 0xec, BYTE_LEN, 0 },
        { 0x9124, 0x0b, BYTE_LEN, 0 },
        { 0x9125, 0x98, BYTE_LEN, 0 },
        { 0x9126, 0x0f, BYTE_LEN, 0 },
        { 0x9127, 0x00, BYTE_LEN, 0 },
        { 0x9128, 0x7f, BYTE_LEN, 0 },
        { 0x9129, 0x80, BYTE_LEN, 0 },
        { 0x912A, 0xfa, BYTE_LEN, 0 },
        { 0x912B, 0x01, BYTE_LEN, 0 },
        { 0x912C, 0xec, BYTE_LEN, 0 },
        { 0x912D, 0x03, BYTE_LEN, 0 },
        { 0x912E, 0xa8, BYTE_LEN, 0 },
        { 0x912F, 0x0f, BYTE_LEN, 0 },
        { 0x9130, 0xa0, BYTE_LEN, 0 },
        { 0x9131, 0x3e, BYTE_LEN, 0 },
        { 0x9132, 0x01, BYTE_LEN, 0 },
        { 0x9133, 0xfb, BYTE_LEN, 0 },
        { 0x9134, 0x04, BYTE_LEN, 0 },
        { 0x9135, 0xec, BYTE_LEN, 0 },
        { 0x9136, 0x07, BYTE_LEN, 0 },
        { 0x9137, 0xb8, BYTE_LEN, 0 },
        { 0x9138, 0x1f, BYTE_LEN, 0 },
        { 0x9139, 0x40, BYTE_LEN, 0 },
        { 0x913A, 0x7f, BYTE_LEN, 0 },
        { 0x913B, 0x80, BYTE_LEN, 0 },
        { 0x913C, 0xfb, BYTE_LEN, 0 },
        { 0x913D, 0x00, BYTE_LEN, 0 },
        { 0x913E, 0xf4, BYTE_LEN, 0 },
        { 0x913F, 0x07, BYTE_LEN, 0 },
        { 0x9140, 0xc8, BYTE_LEN, 0 },
        { 0x9141, 0xff, BYTE_LEN, 0 },
        { 0x9142, 0x3f, BYTE_LEN, 0 },
        { 0x9143, 0xff, BYTE_LEN, 0 },
        { 0x9144, 0xff, BYTE_LEN, 0 },
        { 0x9145, 0xfc, BYTE_LEN, 0 },
        { 0x9146, 0x02, BYTE_LEN, 0 },
        { 0x9147, 0xf2, BYTE_LEN, 0 },
        { 0x9148, 0x0b, BYTE_LEN, 0 },
        { 0x9149, 0xc8, BYTE_LEN, 0 },
        { 0x914A, 0x3f, BYTE_LEN, 0 },
        { 0x914B, 0x40, BYTE_LEN, 0 },
        { 0x914C, 0x3f, BYTE_LEN, 0 },
        { 0x914D, 0x80, BYTE_LEN, 0 },
        { 0x914E, 0xfd, BYTE_LEN, 0 },
        { 0x914F, 0x00, BYTE_LEN, 0 },
        { 0x9150, 0xf2, BYTE_LEN, 0 },
        { 0x9151, 0xfb, BYTE_LEN, 0 },
        { 0x9152, 0xd7, BYTE_LEN, 0 },
        { 0x9153, 0xff, BYTE_LEN, 0 },
        { 0x9154, 0x7f, BYTE_LEN, 0 },
        { 0x9155, 0x7f, BYTE_LEN, 0 },
        { 0x9156, 0x80, BYTE_LEN, 0 },
        { 0x9157, 0xfd, BYTE_LEN, 0 },
        { 0x9158, 0x01, BYTE_LEN, 0 },
        { 0x9159, 0xf6, BYTE_LEN, 0 },
        { 0x915A, 0x17, BYTE_LEN, 0 },
        { 0x915B, 0xd8, BYTE_LEN, 0 },
        { 0x915C, 0x5f, BYTE_LEN, 0 },
        { 0x915D, 0x60, BYTE_LEN, 0 },
        { 0x915E, 0xbf, BYTE_LEN, 0 },
        { 0x915F, 0x00, BYTE_LEN, 0 },
        { 0x9160, 0xfd, BYTE_LEN, 0 },
        { 0x9161, 0x01, BYTE_LEN, 0 },
        { 0x9162, 0xf6, BYTE_LEN, 0 },
        { 0x9163, 0xff, BYTE_LEN, 0 },
        { 0x9164, 0xe7, BYTE_LEN, 0 },
        { 0x9165, 0x0f, BYTE_LEN, 0 },
        { 0x9166, 0x80, BYTE_LEN, 0 },
        { 0x9167, 0xbf, BYTE_LEN, 0 },
        { 0x9168, 0x80, BYTE_LEN, 0 },
        { 0x9169, 0xfd, BYTE_LEN, 0 },
        { 0x916A, 0x02, BYTE_LEN, 0 },
        { 0x916B, 0xfc, BYTE_LEN, 0 },
        { 0x916C, 0x0b, BYTE_LEN, 0 },
        { 0x916D, 0xf0, BYTE_LEN, 0 },
        { 0x916E, 0x5f, BYTE_LEN, 0 },
        { 0x916F, 0xc0, BYTE_LEN, 0 },
        { 0x9170, 0x7f, BYTE_LEN, 0 },
        { 0x9171, 0x01, BYTE_LEN, 0 },
        { 0x9172, 0xff, BYTE_LEN, 0 },
        { 0x9173, 0x04, BYTE_LEN, 0 },
        { 0x9174, 0xfe, BYTE_LEN, 0 },
        { 0x9175, 0x0b, BYTE_LEN, 0 },
        { 0x9176, 0xf0, BYTE_LEN, 0 },
        { 0x9177, 0x0f, BYTE_LEN, 0 },
        { 0x9178, 0xe0, BYTE_LEN, 0 },
        { 0x9179, 0xff, BYTE_LEN, 0 },
        { 0x917A, 0x00, BYTE_LEN, 0 },
        { 0x917B, 0xff, BYTE_LEN, 0 },
        { 0x917C, 0x01, BYTE_LEN, 0 },
        { 0x917D, 0xfe, BYTE_LEN, 0 },
        { 0x917E, 0x0f, BYTE_LEN, 0 },
        { 0x917F, 0xf8, BYTE_LEN, 0 },
        { 0x9180, 0x3f, BYTE_LEN, 0 },
        { 0x9181, 0xe0, BYTE_LEN, 0 },
        { 0x9182, 0xbf, BYTE_LEN, 0 },
        { 0x9183, 0x01, BYTE_LEN, 0 },
        { 0x9184, 0x01, BYTE_LEN, 0 },
        { 0x9185, 0x06, BYTE_LEN, 0 },
        { 0x9186, 0x04, BYTE_LEN, 0 },
        { 0x9187, 0x14, BYTE_LEN, 0 },
        { 0x9188, 0x08, BYTE_LEN, 0 },
        { 0x9189, 0x50, BYTE_LEN, 0 },
        { 0x918A, 0x20, BYTE_LEN, 0 },
        { 0x918B, 0xc0, BYTE_LEN, 0 },
        { 0x918C, 0x00, BYTE_LEN, 0 },
        { 0x918D, 0x01, BYTE_LEN, 0 },
        { 0x918E, 0x03, BYTE_LEN, 0 },
        { 0x918F, 0x02, BYTE_LEN, 0 },
        { 0x9190, 0x10, BYTE_LEN, 0 },
        { 0x9191, 0x20, BYTE_LEN, 0 },
        { 0x9192, 0x40, BYTE_LEN, 0 },
        { 0x9193, 0x40, BYTE_LEN, 0 },
        { 0x9194, 0x00, BYTE_LEN, 0 },
        { 0x9195, 0x01, BYTE_LEN, 0 },
        { 0x9196, 0x01, BYTE_LEN, 0 },
        { 0x9197, 0x06, BYTE_LEN, 0 },
        { 0x9198, 0x06, BYTE_LEN, 0 },
        { 0x9199, 0x18, BYTE_LEN, 0 },
        { 0x919A, 0x18, BYTE_LEN, 0 },
        { 0x919B, 0x60, BYTE_LEN, 0 },
        { 0x919C, 0xa0, BYTE_LEN, 0 },
        { 0x919D, 0x00, BYTE_LEN, 0 },
        { 0x919E, 0x81, BYTE_LEN, 0 },
        { 0x919F, 0x02, BYTE_LEN, 0 },
        { 0x91A0, 0x04, BYTE_LEN, 0 },
        { 0x91A1, 0x0a, BYTE_LEN, 0 },
        { 0x91A2, 0x14, BYTE_LEN, 0 },
        { 0x91A3, 0x28, BYTE_LEN, 0 },
        { 0x91A4, 0x50, BYTE_LEN, 0 },
        { 0x91A5, 0xa0, BYTE_LEN, 0 },
        { 0x91A6, 0x00, BYTE_LEN, 0 },
        { 0x91A7, 0x81, BYTE_LEN, 0 },
        { 0x91A8, 0x03, BYTE_LEN, 0 },
        { 0x91A9, 0x04, BYTE_LEN, 0 },
        { 0x91AA, 0x0e, BYTE_LEN, 0 },
        { 0x91AB, 0x1c, BYTE_LEN, 0 },
        { 0x91AC, 0x30, BYTE_LEN, 0 },
        { 0x91AD, 0x70, BYTE_LEN, 0 },
        { 0x91AE, 0xc0, BYTE_LEN, 0 },
        { 0x91AF, 0xc0, BYTE_LEN, 0 },
        { 0x91B0, 0x01, BYTE_LEN, 0 },
        { 0x91B1, 0x03, BYTE_LEN, 0 },
        { 0x91B2, 0x05, BYTE_LEN, 0 },
        { 0x91B3, 0x0e, BYTE_LEN, 0 },
        { 0x91B4, 0x10, BYTE_LEN, 0 },
        { 0x91B5, 0x50, BYTE_LEN, 0 },
        { 0x91B6, 0x50, BYTE_LEN, 0 },
        { 0x91B7, 0xe0, BYTE_LEN, 0 },
        { 0x91B8, 0x40, BYTE_LEN, 0 },
        { 0x91B9, 0x81, BYTE_LEN, 0 },
        { 0x91BA, 0x02, BYTE_LEN, 0 },
        { 0x91BB, 0x05, BYTE_LEN, 0 },
        { 0x91BC, 0x0a, BYTE_LEN, 0 },
        { 0x91BD, 0x14, BYTE_LEN, 0 },
        { 0x91BE, 0x28, BYTE_LEN, 0 },
        { 0x91BF, 0x80, BYTE_LEN, 0 },
        { 0x91C0, 0xa0, BYTE_LEN, 0 },
        { 0x91C1, 0x00, BYTE_LEN, 0 },
        { 0x91C2, 0x82, BYTE_LEN, 0 },
        { 0x91C3, 0x02, BYTE_LEN, 0 },
        { 0x91C4, 0x06, BYTE_LEN, 0 },
        { 0x91C5, 0x0e, BYTE_LEN, 0 },
        { 0x91C6, 0x14, BYTE_LEN, 0 },
        { 0x91C7, 0x48, BYTE_LEN, 0 },
        { 0x91C8, 0x60, BYTE_LEN, 0 },
        { 0x91C9, 0xa0, BYTE_LEN, 0 },
        { 0x91CA, 0x41, BYTE_LEN, 0 },
        { 0x91CB, 0x81, BYTE_LEN, 0 },
        { 0x91CC, 0x03, BYTE_LEN, 0 },
        { 0x91CD, 0x05, BYTE_LEN, 0 },
        { 0x91CE, 0x12, BYTE_LEN, 0 },
        { 0x91CF, 0x10, BYTE_LEN, 0 },
        { 0x91D0, 0x20, BYTE_LEN, 0 },
        { 0x91D1, 0x40, BYTE_LEN, 0 },
        { 0x91D2, 0x80, BYTE_LEN, 0 },
        { 0x91D3, 0x00, BYTE_LEN, 0 },
        { 0x91D4, 0x82, BYTE_LEN, 0 },
        { 0x91D5, 0x02, BYTE_LEN, 0 },
        { 0x91D6, 0x08, BYTE_LEN, 0 },
        { 0x91D7, 0x0a, BYTE_LEN, 0 },
        { 0x91D8, 0x18, BYTE_LEN, 0 },
        { 0x91D9, 0x38, BYTE_LEN, 0 },
        { 0x91DA, 0x50, BYTE_LEN, 0 },
        { 0x91DB, 0x20, BYTE_LEN, 0 },
        { 0x91DC, 0x81, BYTE_LEN, 0 },
        { 0x91DD, 0x81, BYTE_LEN, 0 },
        { 0x91DE, 0x06, BYTE_LEN, 0 },
        { 0x91DF, 0x05, BYTE_LEN, 0 },
        { 0x91E0, 0x0e, BYTE_LEN, 0 },
        { 0x91E1, 0x14, BYTE_LEN, 0 },
        { 0x91E2, 0x48, BYTE_LEN, 0 },
        { 0x91E3, 0x40, BYTE_LEN, 0 },
        { 0x91E4, 0x80, BYTE_LEN, 0 },
        { 0x91E5, 0x00, BYTE_LEN, 0 },
        { 0x91E6, 0x01, BYTE_LEN, 0 },
        { 0x91E7, 0x02, BYTE_LEN, 0 },
        
        { 0xA000, 0x9191, WORD_LEN, 0 },
        { 0xA002, 0x76, BYTE_LEN, 0 },
        { 0xA003, 0xf1, BYTE_LEN, 0 },
        { 0xA004, 0x0d, BYTE_LEN, 0 },
        { 0xA005, 0x62, BYTE_LEN, 0 },
        { 0xA006, 0xaa, BYTE_LEN, 0 },
        { 0xA007, 0x63, BYTE_LEN, 0 },
        { 0xA008, 0x18, BYTE_LEN, 0 },
        { 0xA009, 0xec, BYTE_LEN, 0 },
        { 0xA00A, 0xe4, BYTE_LEN, 0 },
        { 0xA00B, 0xe5, BYTE_LEN, 0 },
        { 0xA00C, 0x38, BYTE_LEN, 0 },
        { 0xA00D, 0x74, BYTE_LEN, 0 },
        { 0xA00E, 0x29, BYTE_LEN, 0 },
        { 0xA00F, 0x4e, BYTE_LEN, 0 },
        { 0xA010, 0x5e, BYTE_LEN, 0 },
        { 0xA011, 0x98, BYTE_LEN, 0 },
        { 0xA012, 0x83, BYTE_LEN, 0 },
        { 0xA013, 0x98, BYTE_LEN, 0 },
        { 0xA014, 0xef, BYTE_LEN, 0 },
        { 0xA015, 0x50, BYTE_LEN, 0 },
        { 0xA016, 0x26, BYTE_LEN, 0 },
        { 0xA017, 0x3d, BYTE_LEN, 0 },
        { 0xA018, 0x8e, BYTE_LEN, 0 },
        { 0xA019, 0x01, BYTE_LEN, 0 },
        { 0xA01A, 0xcf, BYTE_LEN, 0 },
        { 0xA01B, 0x64, BYTE_LEN, 0 },
        { 0xA01C, 0xc4, BYTE_LEN, 0 },
        { 0xA01D, 0x53, BYTE_LEN, 0 },
        { 0xA01E, 0x19, BYTE_LEN, 0 },
        { 0xA01F, 0xf2, BYTE_LEN, 0 },
        { 0xA020, 0x10, BYTE_LEN, 0 },
        { 0xA021, 0x66, BYTE_LEN, 0 },
        { 0xA022, 0x3a, BYTE_LEN, 0 },
        { 0xA023, 0x76, BYTE_LEN, 0 },
        { 0xA024, 0xe9, BYTE_LEN, 0 },
        { 0xA025, 0x0d, BYTE_LEN, 0 },
        { 0xA026, 0x5c, BYTE_LEN, 0 },
        { 0xA027, 0x70, BYTE_LEN, 0 },
        { 0xA028, 0x63, BYTE_LEN, 0 },
        { 0xA029, 0x97, BYTE_LEN, 0 },
        { 0xA02A, 0xe0, BYTE_LEN, 0 },
        { 0xA02B, 0x1c, BYTE_LEN, 0 },
        { 0xA02C, 0x46, BYTE_LEN, 0 },
        { 0xA02D, 0x3b, BYTE_LEN, 0 },
        { 0xA02E, 0x9e, BYTE_LEN, 0 },
        { 0xA02F, 0xa1, BYTE_LEN, 0 },
        { 0xA030, 0xcf, BYTE_LEN, 0 },
        { 0xA031, 0x67, BYTE_LEN, 0 },
        { 0xA032, 0xee, BYTE_LEN, 0 },
        { 0xA033, 0xd3, BYTE_LEN, 0 },
        { 0xA034, 0x97, BYTE_LEN, 0 },
        { 0xA035, 0xe2, BYTE_LEN, 0 },
        { 0xA036, 0xd0, BYTE_LEN, 0 },
        { 0xA037, 0xc5, BYTE_LEN, 0 },
        { 0xA038, 0x36, BYTE_LEN, 0 },
        { 0xA039, 0x57, BYTE_LEN, 0 },
        { 0xA03A, 0x89, BYTE_LEN, 0 },
        { 0xA03B, 0x4c, BYTE_LEN, 0 },
        { 0xA03C, 0x52, BYTE_LEN, 0 },
        { 0xA03D, 0xf4, BYTE_LEN, 0 },
        { 0xA03E, 0x62, BYTE_LEN, 0 },
        { 0xA03F, 0x94, BYTE_LEN, 0 },
        { 0xA040, 0xb9, BYTE_LEN, 0 },
        { 0xA041, 0x2c, BYTE_LEN, 0 },
        { 0xA042, 0x85, BYTE_LEN, 0 },
        { 0xA043, 0x2f, BYTE_LEN, 0 },
        { 0xA044, 0x5b, BYTE_LEN, 0 },
        { 0xA045, 0xb9, BYTE_LEN, 0 },
        { 0xA046, 0xcc, BYTE_LEN, 0 },
        { 0xA047, 0x5e, BYTE_LEN, 0 },
        { 0xA048, 0x88, BYTE_LEN, 0 },
        { 0xA049, 0x33, BYTE_LEN, 0 },
        { 0xA04A, 0x18, BYTE_LEN, 0 },
        { 0xA04B, 0xe9, BYTE_LEN, 0 },
        { 0xA04C, 0x88, BYTE_LEN, 0 },
        { 0xA04D, 0x85, BYTE_LEN, 0 },
        { 0xA04E, 0x33, BYTE_LEN, 0 },
        { 0xA04F, 0x53, BYTE_LEN, 0 },
        { 0xA050, 0x21, BYTE_LEN, 0 },
        { 0xA051, 0xcc, BYTE_LEN, 0 },
        { 0xA052, 0x4e, BYTE_LEN, 0 },
        { 0xA053, 0xc0, BYTE_LEN, 0 },
        { 0xA054, 0xc2, BYTE_LEN, 0 },
        { 0xA055, 0x92, BYTE_LEN, 0 },
        { 0xA056, 0xa3, BYTE_LEN, 0 },
        { 0xA057, 0x9c, BYTE_LEN, 0 },
        { 0xA058, 0xe4, BYTE_LEN, 0 },
        { 0xA059, 0x27, BYTE_LEN, 0 },
        { 0xA05A, 0x2f, BYTE_LEN, 0 },
        { 0xA05B, 0x59, BYTE_LEN, 0 },
        { 0xA05C, 0x4a, BYTE_LEN, 0 },
        { 0xA05D, 0x50, BYTE_LEN, 0 },
        { 0xA05E, 0xd2, BYTE_LEN, 0 },
        { 0xA05F, 0xb2, BYTE_LEN, 0 },
        { 0xA060, 0x15, BYTE_LEN, 0 },
        { 0xA061, 0xca, BYTE_LEN, 0 },
        { 0xA062, 0xa4, BYTE_LEN, 0 },
        { 0xA063, 0xa5, BYTE_LEN, 0 },
        { 0xA064, 0x35, BYTE_LEN, 0 },
        { 0xA065, 0x52, BYTE_LEN, 0 },
        { 0xA066, 0x09, BYTE_LEN, 0 },
        { 0xA067, 0x8c, BYTE_LEN, 0 },
        { 0xA068, 0x50, BYTE_LEN, 0 },
        { 0xA069, 0xd0, BYTE_LEN, 0 },
        { 0xA06A, 0x62, BYTE_LEN, 0 },
        { 0xA06B, 0x92, BYTE_LEN, 0 },
        { 0xA06C, 0x9e, BYTE_LEN, 0 },
        { 0xA06D, 0x40, BYTE_LEN, 0 },
        { 0xA06E, 0x84, BYTE_LEN, 0 },
        { 0xA06F, 0x23, BYTE_LEN, 0 },
        { 0xA070, 0x0a, BYTE_LEN, 0 },
        { 0xA071, 0x99, BYTE_LEN, 0 },
        { 0xA072, 0xc8, BYTE_LEN, 0 },
        { 0xA073, 0x44, BYTE_LEN, 0 },
        { 0xA074, 0x40, BYTE_LEN, 0 },
        { 0xA075, 0xd2, BYTE_LEN, 0 },
        { 0xA076, 0x12, BYTE_LEN, 0 },
        { 0xA077, 0xa3, BYTE_LEN, 0 },
        { 0xA078, 0x28, BYTE_LEN, 0 },
        { 0xA079, 0xc5, BYTE_LEN, 0 },
        { 0xA07A, 0x2e, BYTE_LEN, 0 },
        { 0xA07B, 0x56, BYTE_LEN, 0 },
        { 0xA07C, 0x79, BYTE_LEN, 0 },
        { 0xA07D, 0x8c, BYTE_LEN, 0 },
        { 0xA07E, 0x51, BYTE_LEN, 0 },
        { 0xA07F, 0xe4, BYTE_LEN, 0 },
        { 0xA080, 0xa2, BYTE_LEN, 0 },
        { 0xA081, 0x93, BYTE_LEN, 0 },
        { 0xA082, 0xad, BYTE_LEN, 0 },
        { 0xA083, 0x6c, BYTE_LEN, 0 },
        { 0xA084, 0x44, BYTE_LEN, 0 },
        { 0xA085, 0x25, BYTE_LEN, 0 },
        { 0xA086, 0x03, BYTE_LEN, 0 },
        { 0xA087, 0x39, BYTE_LEN, 0 },
        { 0xA088, 0x88, BYTE_LEN, 0 },
        { 0xA089, 0x3f, BYTE_LEN, 0 },
        { 0xA08A, 0xfe, BYTE_LEN, 0 },
        { 0xA08B, 0x71, BYTE_LEN, 0 },
        { 0xA08C, 0x10, BYTE_LEN, 0 },
        { 0xA08D, 0x86, BYTE_LEN, 0 },
        { 0xA08E, 0x88, BYTE_LEN, 0 },
        { 0xA08F, 0x84, BYTE_LEN, 0 },
        { 0xA090, 0x26, BYTE_LEN, 0 },
        { 0xA091, 0x42, BYTE_LEN, 0 },
        { 0xA092, 0x49, BYTE_LEN, 0 },
        { 0xA093, 0xcb, BYTE_LEN, 0 },
        { 0xA094, 0x52, BYTE_LEN, 0 },
        { 0xA095, 0xfe, BYTE_LEN, 0 },
        { 0xA096, 0x92, BYTE_LEN, 0 },
        { 0xA097, 0x94, BYTE_LEN, 0 },
        { 0xA098, 0xb9, BYTE_LEN, 0 },
        { 0xA099, 0xf4, BYTE_LEN, 0 },
        { 0xA09A, 0x84, BYTE_LEN, 0 },
        { 0xA09B, 0x2b, BYTE_LEN, 0 },
        { 0xA09C, 0x1e, BYTE_LEN, 0 },
        { 0xA09D, 0x61, BYTE_LEN, 0 },
        { 0xA09E, 0x89, BYTE_LEN, 0 },
        { 0xA09F, 0x41, BYTE_LEN, 0 },
        { 0xA0A0, 0x12, BYTE_LEN, 0 },
        { 0xA0A1, 0x12, BYTE_LEN, 0 },
        { 0xA0A2, 0x10, BYTE_LEN, 0 },
        { 0xA0A3, 0x80, BYTE_LEN, 0 },
        { 0xA0A4, 0x28, BYTE_LEN, 0 },
        { 0xA0A5, 0xa4, BYTE_LEN, 0 },
        { 0xA0A6, 0x21, BYTE_LEN, 0 },
        { 0xA0A7, 0x25, BYTE_LEN, 0 },
        { 0xA0A8, 0xa9, BYTE_LEN, 0 },
        { 0xA0A9, 0x49, BYTE_LEN, 0 },
        { 0xA0AA, 0x51, BYTE_LEN, 0 },
        { 0xA0AB, 0xd0, BYTE_LEN, 0 },
        { 0xA0AC, 0xf2, BYTE_LEN, 0 },
        { 0xA0AD, 0x94, BYTE_LEN, 0 },
        { 0xA0AE, 0xbf, BYTE_LEN, 0 },
        { 0xA0AF, 0x5c, BYTE_LEN, 0 },
        { 0xA0B0, 0xc5, BYTE_LEN, 0 },
        { 0xA0B1, 0x30, BYTE_LEN, 0 },
        { 0xA0B2, 0x48, BYTE_LEN, 0 },
        { 0xA0B3, 0x69, BYTE_LEN, 0 },
        { 0xA0B4, 0x8b, BYTE_LEN, 0 },
        { 0xA0B5, 0x4b, BYTE_LEN, 0 },
        { 0xA0B6, 0x82, BYTE_LEN, 0 },
        { 0xA0B7, 0x82, BYTE_LEN, 0 },
        { 0xA0B8, 0x11, BYTE_LEN, 0 },
        { 0xA0B9, 0x90, BYTE_LEN, 0 },
        { 0xA0BA, 0x4c, BYTE_LEN, 0 },
        { 0xA0BB, 0xe4, BYTE_LEN, 0 },
        { 0xA0BC, 0x22, BYTE_LEN, 0 },
        { 0xA0BD, 0x1c, BYTE_LEN, 0 },
        { 0xA0BE, 0x21, BYTE_LEN, 0 },
        { 0xA0BF, 0x49, BYTE_LEN, 0 },
        { 0xA0C0, 0x4d, BYTE_LEN, 0 },
        { 0xA0C1, 0x94, BYTE_LEN, 0 },
        { 0xA0C2, 0x32, BYTE_LEN, 0 },
        { 0xA0C3, 0x15, BYTE_LEN, 0 },
        { 0xA0C4, 0xbc, BYTE_LEN, 0 },
        { 0xA0C5, 0x80, BYTE_LEN, 0 },
        { 0xA0C6, 0x25, BYTE_LEN, 0 },
        { 0xA0C7, 0x32, BYTE_LEN, 0 },
        { 0xA0C8, 0x6c, BYTE_LEN, 0 },
        { 0xA0C9, 0x39, BYTE_LEN, 0 },
        { 0xA0CA, 0x4d, BYTE_LEN, 0 },
        { 0xA0CB, 0x57, BYTE_LEN, 0 },
        { 0xA0CC, 0x1c, BYTE_LEN, 0 },
        { 0xA0CD, 0x53, BYTE_LEN, 0 },
        { 0xA0CE, 0x94, BYTE_LEN, 0 },
        { 0xA0CF, 0xb3, BYTE_LEN, 0 },
        { 0xA0D0, 0xdc, BYTE_LEN, 0 },
        { 0xA0D1, 0xe4, BYTE_LEN, 0 },
        { 0xA0D2, 0x29, BYTE_LEN, 0 },
        { 0xA0D3, 0x34, BYTE_LEN, 0 },
        { 0xA0D4, 0x41, BYTE_LEN, 0 },
        { 0xA0D5, 0xca, BYTE_LEN, 0 },
        { 0xA0D6, 0x4e, BYTE_LEN, 0 },
        { 0xA0D7, 0xa2, BYTE_LEN, 0 },
        { 0xA0D8, 0xc2, BYTE_LEN, 0 },
        { 0xA0D9, 0x94, BYTE_LEN, 0 },
        { 0xA0DA, 0xb7, BYTE_LEN, 0 },
        { 0xA0DB, 0xa0, BYTE_LEN, 0 },
        { 0xA0DC, 0x25, BYTE_LEN, 0 },
        { 0xA0DD, 0x33, BYTE_LEN, 0 },
        { 0xA0DE, 0x76, BYTE_LEN, 0 },
        { 0xA0DF, 0x99, BYTE_LEN, 0 },
        { 0xA0E0, 0x4d, BYTE_LEN, 0 },
        { 0xA0E1, 0x62, BYTE_LEN, 0 },
        { 0xA0E2, 0x96, BYTE_LEN, 0 },
        { 0xA0E3, 0x13, BYTE_LEN, 0 },
        { 0xA0E4, 0x98, BYTE_LEN, 0 },
        { 0xA0E5, 0xde, BYTE_LEN, 0 },
        { 0xA0E6, 0x8c, BYTE_LEN, 0 },
        { 0xA0E7, 0xc5, BYTE_LEN, 0 },
        { 0xA0E8, 0x32, BYTE_LEN, 0 },
        { 0xA0E9, 0x57, BYTE_LEN, 0 },
        { 0xA0EA, 0x19, BYTE_LEN, 0 },
        { 0xA0EB, 0x0c, BYTE_LEN, 0 },
        { 0xA0EC, 0x55, BYTE_LEN, 0 },
        { 0xA0ED, 0xfc, BYTE_LEN, 0 },
        { 0xA0EE, 0x92, BYTE_LEN, 0 },
        { 0xA0EF, 0x95, BYTE_LEN, 0 },
        { 0xA0F0, 0xc2, BYTE_LEN, 0 },
        { 0xA0F1, 0xa8, BYTE_LEN, 0 },
        { 0xA0F2, 0xc5, BYTE_LEN, 0 },
        { 0xA0F3, 0x33, BYTE_LEN, 0 },
        { 0xA0F4, 0x8d, BYTE_LEN, 0 },
        { 0xA0F5, 0x81, BYTE_LEN, 0 },
        { 0xA0F6, 0x4e, BYTE_LEN, 0 },
        { 0xA0F7, 0x65, BYTE_LEN, 0 },
        { 0xA0F8, 0xbe, BYTE_LEN, 0 },
        { 0xA0F9, 0x33, BYTE_LEN, 0 },
        { 0xA0FA, 0x1a, BYTE_LEN, 0 },
        { 0xA0FB, 0xf6, BYTE_LEN, 0 },
        { 0xA0FC, 0x94, BYTE_LEN, 0 },
        { 0xA0FD, 0xa6, BYTE_LEN, 0 },
        { 0xA0FE, 0x3d, BYTE_LEN, 0 },
        { 0xA0FF, 0x92, BYTE_LEN, 0 },
        { 0xA100, 0xc9, BYTE_LEN, 0 },
        { 0xA101, 0xce, BYTE_LEN, 0 },
        { 0xA102, 0x60, BYTE_LEN, 0 },
        { 0xA103, 0x8e, BYTE_LEN, 0 },
        { 0xA104, 0x13, BYTE_LEN, 0 },
        { 0xA105, 0x18, BYTE_LEN, 0 },
        { 0xA106, 0xe1, BYTE_LEN, 0 },
        { 0xA107, 0x24, BYTE_LEN, 0 },
        { 0xA108, 0x86, BYTE_LEN, 0 },
        { 0xA109, 0x39, BYTE_LEN, 0 },
        { 0xA10A, 0x9a, BYTE_LEN, 0 },
        { 0xA10B, 0xf9, BYTE_LEN, 0 },
        { 0xA10C, 0x8e, BYTE_LEN, 0 },
        { 0xA10D, 0x6c, BYTE_LEN, 0 },
        { 0xA10E, 0xfe, BYTE_LEN, 0 },
        { 0xA10F, 0xe3, BYTE_LEN, 0 },
        { 0xA110, 0x9a, BYTE_LEN, 0 },
        { 0xA111, 0xff, BYTE_LEN, 0 },
        { 0xA112, 0x08, BYTE_LEN, 0 },
        { 0xA113, 0xa6, BYTE_LEN, 0 },
        { 0xA114, 0x38, BYTE_LEN, 0 },
        { 0xA115, 0x97, BYTE_LEN, 0 },
        { 0xA116, 0xf1, BYTE_LEN, 0 },
        { 0xA117, 0x0e, BYTE_LEN, 0 },
        { 0xA118, 0x65, BYTE_LEN, 0 },
        { 0xA119, 0xbe, BYTE_LEN, 0 },
        { 0xA11A, 0x53, BYTE_LEN, 0 },
        { 0xA11B, 0x18, BYTE_LEN, 0 },
        { 0xA11C, 0xe8, BYTE_LEN, 0 },
        { 0xA11D, 0x14, BYTE_LEN, 0 },
        { 0xA11E, 0x86, BYTE_LEN, 0 },
        { 0xA11F, 0x39, BYTE_LEN, 0 },
        { 0xA120, 0x8c, BYTE_LEN, 0 },
        { 0xA121, 0x99, BYTE_LEN, 0 },
        { 0xA122, 0x0e, BYTE_LEN, 0 },
        { 0xA123, 0x67, BYTE_LEN, 0 },
        { 0xA124, 0xc4, BYTE_LEN, 0 },
        { 0xA125, 0x43, BYTE_LEN, 0 },
        { 0xA126, 0x9a, BYTE_LEN, 0 },
        { 0xA127, 0xf6, BYTE_LEN, 0 },
        { 0xA128, 0x44, BYTE_LEN, 0 },
        { 0xA129, 0x06, BYTE_LEN, 0 },
        { 0xA12A, 0x3b, BYTE_LEN, 0 },
        { 0xA12B, 0x62, BYTE_LEN, 0 },
        { 0xA12C, 0xb9, BYTE_LEN, 0 },
        { 0xA12D, 0x0b, BYTE_LEN, 0 },
        { 0xA12E, 0x5d, BYTE_LEN, 0 },
        { 0xA12F, 0x0e, BYTE_LEN, 0 },
        { 0xA130, 0x73, BYTE_LEN, 0 },
        { 0xA131, 0x17, BYTE_LEN, 0 },
        { 0xA132, 0xc3, BYTE_LEN, 0 },
        { 0xA133, 0xa4, BYTE_LEN, 0 },
        { 0xA134, 0x25, BYTE_LEN, 0 },
        { 0xA135, 0x2f, BYTE_LEN, 0 },
        { 0xA136, 0x68, BYTE_LEN, 0 },
        { 0xA137, 0xb9, BYTE_LEN, 0 },
        { 0xA138, 0x4b, BYTE_LEN, 0 },
        { 0xA139, 0x5c, BYTE_LEN, 0 },
        { 0xA13A, 0xfc, BYTE_LEN, 0 },
        { 0xA13B, 0xe2, BYTE_LEN, 0 },
        { 0xA13C, 0x97, BYTE_LEN, 0 },
        { 0xA13D, 0xc6, BYTE_LEN, 0 },
        { 0xA13E, 0x20, BYTE_LEN, 0 },
        { 0xA13F, 0x26, BYTE_LEN, 0 },
        { 0xA140, 0x33, BYTE_LEN, 0 },
        { 0xA141, 0x81, BYTE_LEN, 0 },
        { 0xA142, 0x99, BYTE_LEN, 0 },
        { 0xA143, 0x4c, BYTE_LEN, 0 },
        { 0xA144, 0x5f, BYTE_LEN, 0 },
        { 0xA145, 0x26, BYTE_LEN, 0 },
        { 0xA146, 0x13, BYTE_LEN, 0 },
        { 0xA147, 0x18, BYTE_LEN, 0 },
        { 0xA148, 0xcb, BYTE_LEN, 0 },
        { 0xA149, 0xd0, BYTE_LEN, 0 },
        { 0xA14A, 0x85, BYTE_LEN, 0 },
        { 0xA14B, 0x30, BYTE_LEN, 0 },
        { 0xA14C, 0x67, BYTE_LEN, 0 },
        { 0xA14D, 0xb9, BYTE_LEN, 0 },
        { 0xA14E, 0x0b, BYTE_LEN, 0 },
        { 0xA14F, 0x59, BYTE_LEN, 0 },
        { 0xA150, 0xe8, BYTE_LEN, 0 },
        { 0xA151, 0xe2, BYTE_LEN, 0 },
        { 0xA152, 0x96, BYTE_LEN, 0 },
        { 0xA153, 0xbd, BYTE_LEN, 0 },
        { 0xA154, 0xf4, BYTE_LEN, 0 },
        { 0xA155, 0x85, BYTE_LEN, 0 },
        { 0xA156, 0x31, BYTE_LEN, 0 },
        { 0xA157, 0x92, BYTE_LEN, 0 },
        { 0xA158, 0x19, BYTE_LEN, 0 },
        { 0xA159, 0x4d, BYTE_LEN, 0 },
        { 0xA15A, 0x64, BYTE_LEN, 0 },
        { 0xA15B, 0x46, BYTE_LEN, 0 },
        { 0xA15C, 0x73, BYTE_LEN, 0 },
        { 0xA15D, 0x16, BYTE_LEN, 0 },
        { 0xA15E, 0xbe, BYTE_LEN, 0 },
        { 0xA15F, 0x84, BYTE_LEN, 0 },
        { 0xA160, 0x85, BYTE_LEN, 0 },
        { 0xA161, 0x2e, BYTE_LEN, 0 },
        { 0xA162, 0x4a, BYTE_LEN, 0 },
        { 0xA163, 0xc9, BYTE_LEN, 0 },
        { 0xA164, 0x0a, BYTE_LEN, 0 },
        { 0xA165, 0x50, BYTE_LEN, 0 },
        { 0xA166, 0x96, BYTE_LEN, 0 },
        { 0xA167, 0x02, BYTE_LEN, 0 },
        { 0xA168, 0x14, BYTE_LEN, 0 },
        { 0xA169, 0xa4, BYTE_LEN, 0 },
        { 0xA16A, 0x18, BYTE_LEN, 0 },
        { 0xA16B, 0xe5, BYTE_LEN, 0 },
        { 0xA16C, 0x29, BYTE_LEN, 0 },
        { 0xA16D, 0x54, BYTE_LEN, 0 },
        { 0xA16E, 0xf9, BYTE_LEN, 0 },
        { 0xA16F, 0x4a, BYTE_LEN, 0 },
        { 0xA170, 0x5c, BYTE_LEN, 0 },
        { 0xA171, 0xfe, BYTE_LEN, 0 },
        { 0xA172, 0x82, BYTE_LEN, 0 },
        { 0xA173, 0x17, BYTE_LEN, 0 },
        { 0xA174, 0xc3, BYTE_LEN, 0 },
        { 0xA175, 0x38, BYTE_LEN, 0 },
        { 0xA176, 0x25, BYTE_LEN, 0 },
        { 0xA177, 0x2c, BYTE_LEN, 0 },
        { 0xA178, 0x44, BYTE_LEN, 0 },
        { 0xA179, 0x99, BYTE_LEN, 0 },
        { 0xA17A, 0x8a, BYTE_LEN, 0 },
        { 0xA17B, 0x4c, BYTE_LEN, 0 },
        { 0xA17C, 0x7a, BYTE_LEN, 0 },
        { 0xA17D, 0x72, BYTE_LEN, 0 },
        { 0xA17E, 0x92, BYTE_LEN, 0 },
        { 0xA17F, 0x97, BYTE_LEN, 0 },
        { 0xA180, 0x94, BYTE_LEN, 0 },
        { 0xA181, 0x44, BYTE_LEN, 0 },
        { 0xA182, 0x25, BYTE_LEN, 0 },
        { 0xA183, 0x2e, BYTE_LEN, 0 },
        { 0xA184, 0x99, BYTE_LEN, 0 },
        { 0xA185, 0x49, BYTE_LEN, 0 },
        { 0xA186, 0x4f, BYTE_LEN, 0 },
        { 0xA187, 0x8a, BYTE_LEN, 0 },
        { 0xA188, 0x12, BYTE_LEN, 0 },
        { 0xA189, 0x95, BYTE_LEN, 0 },
        { 0xA18A, 0xae, BYTE_LEN, 0 },
        { 0xA18B, 0x6c, BYTE_LEN, 0 },
        { 0xA18C, 0x45, BYTE_LEN, 0 },
        { 0xA18D, 0x2d, BYTE_LEN, 0 },
        { 0xA18E, 0x3d, BYTE_LEN, 0 },
        { 0xA18F, 0x79, BYTE_LEN, 0 },
        { 0xA190, 0x0a, BYTE_LEN, 0 },
        { 0xA191, 0x4d, BYTE_LEN, 0 },
        { 0xA192, 0x84, BYTE_LEN, 0 },
        { 0xA193, 0x02, BYTE_LEN, 0 },
        { 0xA194, 0x92, BYTE_LEN, 0 },
        { 0xA195, 0x94, BYTE_LEN, 0 },
        { 0xA196, 0x34, BYTE_LEN, 0 },
        { 0xA197, 0x64, BYTE_LEN, 0 },
        { 0xA198, 0x22, BYTE_LEN, 0 },
        { 0xA199, 0x0a, BYTE_LEN, 0 },
        { 0xA19A, 0x61, BYTE_LEN, 0 },
        { 0xA19B, 0xc8, BYTE_LEN, 0 },
        { 0xA19C, 0x44, BYTE_LEN, 0 },
        { 0xA19D, 0x2c, BYTE_LEN, 0 },
        { 0xA19E, 0xb2, BYTE_LEN, 0 },
        { 0xA19F, 0x12, BYTE_LEN, 0 },
        { 0xA1A0, 0x98, BYTE_LEN, 0 },
        { 0xA1A1, 0x10, BYTE_LEN, 0 },
        { 0xA1A2, 0x85, BYTE_LEN, 0 },
        { 0xA1A3, 0x29, BYTE_LEN, 0 },
        { 0xA1A4, 0x4c, BYTE_LEN, 0 },
        { 0xA1A5, 0xc1, BYTE_LEN, 0 },
        { 0xA1A6, 0x4a, BYTE_LEN, 0 },
        { 0xA1A7, 0x4d, BYTE_LEN, 0 },
        { 0xA1A8, 0x86, BYTE_LEN, 0 },
        { 0xA1A9, 0xe2, BYTE_LEN, 0 },
        { 0xA1AA, 0x12, BYTE_LEN, 0 },
        { 0xA1AB, 0x9c, BYTE_LEN, 0 },
        { 0xA1AC, 0x54, BYTE_LEN, 0 },
        { 0xA1AD, 0x84, BYTE_LEN, 0 },
        { 0xA1AE, 0x23, BYTE_LEN, 0 },
        { 0xA1AF, 0x01, BYTE_LEN, 0 },
        { 0xA1B0, 0x21, BYTE_LEN, 0 },
        { 0xA1B1, 0xc8, BYTE_LEN, 0 },
        { 0xA1B2, 0x3f, BYTE_LEN, 0 },
        { 0xA1B3, 0xfe, BYTE_LEN, 0 },
        { 0xA1B4, 0x91, BYTE_LEN, 0 },
        { 0xA1B5, 0x10, BYTE_LEN, 0 },
        { 0xA1B6, 0x84, BYTE_LEN, 0 },
        { 0xA1B7, 0x88, BYTE_LEN, 0 },
        { 0xA1B8, 0x64, BYTE_LEN, 0 },
        { 0xA1B9, 0x24, BYTE_LEN, 0 },
        { 0xA1BA, 0x3d, BYTE_LEN, 0 },
        { 0xA1BB, 0x19, BYTE_LEN, 0 },
        { 0xA1BC, 0x8a, BYTE_LEN, 0 },
        { 0xA1BD, 0x50, BYTE_LEN, 0 },
        { 0xA1BE, 0x98, BYTE_LEN, 0 },
        { 0xA1BF, 0x72, BYTE_LEN, 0 },
        { 0xA1C0, 0x13, BYTE_LEN, 0 },
        { 0xA1C1, 0xa2, BYTE_LEN, 0 },
        { 0xA1C2, 0xc0, BYTE_LEN, 0 },
        { 0xA1C3, 0x44, BYTE_LEN, 0 },
        { 0xA1C4, 0x27, BYTE_LEN, 0 },
        { 0xA1C5, 0x17, BYTE_LEN, 0 },
        { 0xA1C6, 0xe9, BYTE_LEN, 0 },
        { 0xA1C7, 0xc8, BYTE_LEN, 0 },
        { 0xA1C8, 0x40, BYTE_LEN, 0 },
        { 0xA1C9, 0x0a, BYTE_LEN, 0 },
        { 0xA1CA, 0x02, BYTE_LEN, 0 },
        { 0xA1CB, 0x10, BYTE_LEN, 0 },
        { 0xA1CC, 0x80, BYTE_LEN, 0 },
        { 0xA1CD, 0x2c, BYTE_LEN, 0 },
        { 0xA1CE, 0x24, BYTE_LEN, 0 },
        { 0xA1CF, 0x21, BYTE_LEN, 0 },
        { 0xA1D0, 0x23, BYTE_LEN, 0 },
        { 0xA1D1, 0x21, BYTE_LEN, 0 },
        { 0xA1D2, 0x49, BYTE_LEN, 0 },
        { 0xA1D3, 0x4f, BYTE_LEN, 0 },
        { 0xA1D4, 0x86, BYTE_LEN, 0 },
        { 0xA1D5, 0x22, BYTE_LEN, 0 },
        { 0xA1D6, 0x14, BYTE_LEN, 0 },
        { 0xA1D7, 0xa6, BYTE_LEN, 0 },
        { 0xA1D8, 0x10, BYTE_LEN, 0 },
        { 0xA1D9, 0x45, BYTE_LEN, 0 },
        { 0xA1DA, 0x2a, BYTE_LEN, 0 },
        { 0xA1DB, 0x3b, BYTE_LEN, 0 },
        { 0xA1DC, 0x29, BYTE_LEN, 0 },
        { 0xA1DD, 0x8a, BYTE_LEN, 0 },
        { 0xA1DE, 0x49, BYTE_LEN, 0 },
        { 0xA1DF, 0x58, BYTE_LEN, 0 },
        { 0xA1E0, 0x32, BYTE_LEN, 0 },
        { 0xA1E1, 0x91, BYTE_LEN, 0 },
        { 0xA1E2, 0x8a, BYTE_LEN, 0 },
        { 0xA1E3, 0x3c, BYTE_LEN, 0 },
        { 0xA1E4, 0xe4, BYTE_LEN, 0 },
        { 0xA1E5, 0x21, BYTE_LEN, 0 },
        { 0xA1E6, 0x19, BYTE_LEN, 0 },
        { 0xA1E7, 0xc9, BYTE_LEN, 0 },
        { 0xA1E8, 0x88, BYTE_LEN, 0 },
        { 0xA1E9, 0x4b, BYTE_LEN, 0 },
        { 0xA1EA, 0x66, BYTE_LEN, 0 },
        { 0xA1EB, 0x42, BYTE_LEN, 0 },
        { 0xA1EC, 0x94, BYTE_LEN, 0 },
        { 0xA1ED, 0xa7, BYTE_LEN, 0 },
        { 0xA1EE, 0x30, BYTE_LEN, 0 },
        { 0xA1EF, 0x65, BYTE_LEN, 0 },
        { 0xA1F0, 0x2b, BYTE_LEN, 0 },
        { 0xA1F1, 0x58, BYTE_LEN, 0 },
        { 0xA1F2, 0x39, BYTE_LEN, 0 },
        { 0xA1F3, 0x4b, BYTE_LEN, 0 },
        { 0xA1F4, 0x53, BYTE_LEN, 0 },
        { 0xA1F5, 0xb2, BYTE_LEN, 0 },
        { 0xA1F6, 0xb2, BYTE_LEN, 0 },
        { 0xA1F7, 0x93, BYTE_LEN, 0 },
        { 0xA1F8, 0xa1, BYTE_LEN, 0 },
        { 0xA1F9, 0xbc, BYTE_LEN, 0 },
        { 0xA1FA, 0x84, BYTE_LEN, 0 },
        { 0xA1FB, 0x26, BYTE_LEN, 0 },
        { 0xA1FC, 0x2b, BYTE_LEN, 0 },
        { 0xA1FD, 0x81, BYTE_LEN, 0 },
        { 0xA1FE, 0xc9, BYTE_LEN, 0 },
        { 0xA1FF, 0x4c, BYTE_LEN, 0 },
        { 0xA200, 0x70, BYTE_LEN, 0 },
        { 0xA201, 0x02, BYTE_LEN, 0 },
        { 0xA202, 0x14, BYTE_LEN, 0 },
        { 0xA203, 0xa5, BYTE_LEN, 0 },
        { 0xA204, 0x4c, BYTE_LEN, 0 },
        { 0xA205, 0x85, BYTE_LEN, 0 },
        { 0xA206, 0x2c, BYTE_LEN, 0 },
        { 0xA207, 0x5d, BYTE_LEN, 0 },
        { 0xA208, 0x91, BYTE_LEN, 0 },
        { 0xA209, 0xcb, BYTE_LEN, 0 },
        { 0xA20A, 0x5d, BYTE_LEN, 0 },
        { 0xA20B, 0x0a, BYTE_LEN, 0 },
        { 0xA20C, 0x03, BYTE_LEN, 0 },
        { 0xA20D, 0x17, BYTE_LEN, 0 },
        { 0xA20E, 0xbf, BYTE_LEN, 0 },
        { 0xA20F, 0x5c, BYTE_LEN, 0 },
        { 0xA210, 0x45, BYTE_LEN, 0 },
        { 0xA211, 0x2c, BYTE_LEN, 0 },
        { 0xA212, 0x4a, BYTE_LEN, 0 },
        { 0xA213, 0xa9, BYTE_LEN, 0 },
        { 0xA214, 0xca, BYTE_LEN, 0 },
        { 0xA215, 0x51, BYTE_LEN, 0 },
        { 0xA216, 0xa6, BYTE_LEN, 0 },
        { 0xA217, 0xc2, BYTE_LEN, 0 },
        { 0xA218, 0x14, BYTE_LEN, 0 },
        { 0xA219, 0xac, BYTE_LEN, 0 },
        { 0xA21A, 0x60, BYTE_LEN, 0 },
        { 0xA21B, 0x25, BYTE_LEN, 0 },
        { 0xA21C, 0x2d, BYTE_LEN, 0 },
        { 0xA21D, 0x73, BYTE_LEN, 0 },
        { 0xA21E, 0x51, BYTE_LEN, 0 },
        { 0xA21F, 0x0c, BYTE_LEN, 0 },
        { 0xA220, 0x5e, BYTE_LEN, 0 },
        { 0xA221, 0x22, BYTE_LEN, 0 },
        { 0xA222, 0x03, BYTE_LEN, 0 },
        { 0xA223, 0x99, BYTE_LEN, 0 },
        { 0xA224, 0xcf, BYTE_LEN, 0 },
        { 0xA225, 0x4c, BYTE_LEN, 0 },
        { 0xA226, 0x46, BYTE_LEN, 0 },
        { 0xA227, 0x34, BYTE_LEN, 0 },
        { 0xA228, 0x81, BYTE_LEN, 0 },
        { 0xA229, 0x89, BYTE_LEN, 0 },
        { 0xA22A, 0xcc, BYTE_LEN, 0 },
        { 0xA22B, 0x5c, BYTE_LEN, 0 },
        { 0xA22C, 0x08, BYTE_LEN, 0 },
        { 0xA22D, 0x03, BYTE_LEN, 0 },
        { 0xA22E, 0x17, BYTE_LEN, 0 },
        { 0xA22F, 0xc1, BYTE_LEN, 0 },
        { 0xA230, 0xd4, BYTE_LEN, 0 },
        { 0xA231, 0x05, BYTE_LEN, 0 },
        { 0xA232, 0x31, BYTE_LEN, 0 },
        { 0xA233, 0x82, BYTE_LEN, 0 },
        { 0xA234, 0xd1, BYTE_LEN, 0 },
        { 0xA235, 0x8c, BYTE_LEN, 0 },
        { 0xA236, 0x64, BYTE_LEN, 0 },
        { 0xA237, 0x5c, BYTE_LEN, 0 },
        { 0xA238, 0xc3, BYTE_LEN, 0 },
        { 0xA239, 0x18, BYTE_LEN, 0 },
        { 0xA23A, 0xd4, BYTE_LEN, 0 },
        { 0xA23B, 0xc8, BYTE_LEN, 0 },
        { 0xA23C, 0x45, BYTE_LEN, 0 },
        { 0xA23D, 0x30, BYTE_LEN, 0 },
        { 0xA23E, 0x86, BYTE_LEN, 0 },
        { 0xA23F, 0xa1, BYTE_LEN, 0 },
        { 0xA240, 0xcc, BYTE_LEN, 0 },
        { 0xA241, 0x60, BYTE_LEN, 0 },
        { 0xA242, 0x28, BYTE_LEN, 0 },
        { 0xA243, 0x73, BYTE_LEN, 0 },
        { 0xA244, 0x17, BYTE_LEN, 0 },
        { 0xA245, 0xc4, BYTE_LEN, 0 },
        { 0xA246, 0xd4, BYTE_LEN, 0 },
        { 0xA247, 0x05, BYTE_LEN, 0 },
        { 0xA248, 0x31, BYTE_LEN, 0 },
        { 0xA249, 0x79, BYTE_LEN, 0 },
        { 0xA24A, 0x61, BYTE_LEN, 0 },
        { 0xA24B, 0x0c, BYTE_LEN, 0 },
        { 0xA24C, 0x61, BYTE_LEN, 0 },
        { 0xA24D, 0x3a, BYTE_LEN, 0 },
        { 0xA24E, 0x63, BYTE_LEN, 0 },
        { 0xA24F, 0x18, BYTE_LEN, 0 },
        { 0xA250, 0xd0, BYTE_LEN, 0 },
        { 0xA251, 0xc8, BYTE_LEN, 0 },
        { 0xA252, 0x45, BYTE_LEN, 0 },
        { 0xA253, 0x31, BYTE_LEN, 0 },
        
        { 0xA254, 0x95, BYTE_LEN, 0 },
        { 0xA255, 0x41, BYTE_LEN, 0 },
        { 0xA256, 0x8d, BYTE_LEN, 0 },
        { 0xA257, 0x69, BYTE_LEN, 0 },
        { 0xA258, 0x2c, BYTE_LEN, 0 },
        { 0xA259, 0x13, BYTE_LEN, 0 },
        { 0xA25A, 0x99, BYTE_LEN, 0 },
        { 0xA25B, 0xcb, BYTE_LEN, 0 },
        { 0xA25C, 0xa0, BYTE_LEN, 0 },
        { 0xA25D, 0x46, BYTE_LEN, 0 },
        { 0xA25E, 0x36, BYTE_LEN, 0 },
        { 0xA25F, 0xab, BYTE_LEN, 0 },
        { 0xA260, 0xa1, BYTE_LEN, 0 },
        { 0xA261, 0xcd, BYTE_LEN, 0 },
        { 0xA262, 0x6d, BYTE_LEN, 0 },
        { 0xA263, 0x40, BYTE_LEN, 0 },
        { 0xA264, 0xd3, BYTE_LEN, 0 },
        { 0xA265, 0x18, BYTE_LEN, 0 },
        { 0xA266, 0xc4, BYTE_LEN, 0 },
        { 0xA267, 0x38, BYTE_LEN, 0 },
        { 0xA268, 0x66, BYTE_LEN, 0 },
        { 0xA269, 0x34, BYTE_LEN, 0 },
        { 0xA26A, 0xbc, BYTE_LEN, 0 },
        { 0xA26B, 0xf1, BYTE_LEN, 0 },
        { 0xA26C, 0x8d, BYTE_LEN, 0 },
        { 0xA26D, 0x66, BYTE_LEN, 0 },
        { 0xA26E, 0x1a, BYTE_LEN, 0 },
        { 0xA26F, 0x83, BYTE_LEN, 0 },
        { 0xA270, 0x16, BYTE_LEN, 0 },
        { 0xA271, 0xaa, BYTE_LEN, 0 },
        { 0xA272, 0x3c, BYTE_LEN, 0 },
        { 0xA273, 0xc5, BYTE_LEN, 0 },
        { 0xA274, 0x2a, BYTE_LEN, 0 },
        { 0xA275, 0x6a, BYTE_LEN, 0 },
        { 0xA276, 0x91, BYTE_LEN, 0 },
        { 0xA277, 0x0c, BYTE_LEN, 0 },
        { 0xA278, 0x68, BYTE_LEN, 0 },
        { 0xA279, 0xf0, BYTE_LEN, 0 },
        { 0xA27A, 0x32, BYTE_LEN, 0 },
        { 0xA27B, 0x96, BYTE_LEN, 0 },
        { 0xA27C, 0xa1, BYTE_LEN, 0 },
        { 0xA27D, 0xbc, BYTE_LEN, 0 },
        { 0xA27E, 0x04, BYTE_LEN, 0 },
        { 0xA27F, 0x25, BYTE_LEN, 0 },
        { 0xA280, 0x30, BYTE_LEN, 0 },
        { 0xA281, 0x31, BYTE_LEN, 0 },
        { 0xA282, 0x0a, BYTE_LEN, 0 },
        { 0xA283, 0x5a, BYTE_LEN, 0 },
        { 0xA284, 0xfc, BYTE_LEN, 0 },
        { 0xA285, 0x12, BYTE_LEN, 0 },
        { 0xA286, 0x16, BYTE_LEN, 0 },
        { 0xA287, 0xa6, BYTE_LEN, 0 },
        { 0xA288, 0xa8, BYTE_LEN, 0 },
        { 0xA289, 0x04, BYTE_LEN, 0 },
        { 0xA28A, 0x22, BYTE_LEN, 0 },
        { 0xA28B, 0x09, BYTE_LEN, 0 },
        { 0xA28C, 0x91, BYTE_LEN, 0 },
        { 0xA28D, 0x88, BYTE_LEN, 0 },
        { 0xA28E, 0x4b, BYTE_LEN, 0 },
        { 0xA28F, 0xa2, BYTE_LEN, 0 },
        { 0xA290, 0x82, BYTE_LEN, 0 },
        { 0xA291, 0x16, BYTE_LEN, 0 },
        { 0xA292, 0xaa, BYTE_LEN, 0 },
        { 0xA293, 0x04, BYTE_LEN, 0 },
        { 0xA294, 0xa5, BYTE_LEN, 0 },
        { 0xA295, 0x23, BYTE_LEN, 0 },
        { 0xA296, 0x04, BYTE_LEN, 0 },
        { 0xA297, 0xf1, BYTE_LEN, 0 },
        { 0xA298, 0x87, BYTE_LEN, 0 },
        { 0xA299, 0x41, BYTE_LEN, 0 },
        { 0xA29A, 0x46, BYTE_LEN, 0 },
        { 0xA29B, 0x82, BYTE_LEN, 0 },
        { 0xA29C, 0x94, BYTE_LEN, 0 },
        { 0xA29D, 0xad, BYTE_LEN, 0 },
        { 0xA29E, 0x58, BYTE_LEN, 0 },
        { 0xA29F, 0x85, BYTE_LEN, 0 },
        { 0xA2A0, 0x28, BYTE_LEN, 0 },
        { 0xA2A1, 0x1f, BYTE_LEN, 0 },
        { 0xA2A2, 0x31, BYTE_LEN, 0 },
        { 0xA2A3, 0x48, BYTE_LEN, 0 },
        { 0xA2A4, 0x40, BYTE_LEN, 0 },
        { 0xA2A5, 0x14, BYTE_LEN, 0 },
        { 0xA2A6, 0x62, BYTE_LEN, 0 },
        { 0xA2A7, 0x92, BYTE_LEN, 0 },
        { 0xA2A8, 0xa5, BYTE_LEN, 0 },
        { 0xA2A9, 0x78, BYTE_LEN, 0 },
        { 0xA2AA, 0x25, BYTE_LEN, 0 },
        { 0xA2AB, 0x2d, BYTE_LEN, 0 },
        { 0xA2AC, 0x53, BYTE_LEN, 0 },
        { 0xA2AD, 0x81, BYTE_LEN, 0 },
        { 0xA2AE, 0xc9, BYTE_LEN, 0 },
        { 0xA2AF, 0x45, BYTE_LEN, 0 },
        { 0xA2B0, 0x22, BYTE_LEN, 0 },
        { 0xA2B1, 0xb2, BYTE_LEN, 0 },
        { 0xA2B2, 0x91, BYTE_LEN, 0 },
        { 0xA2B3, 0x9b, BYTE_LEN, 0 },
        { 0xA2B4, 0x6c, BYTE_LEN, 0 },
        { 0xA2B5, 0x25, BYTE_LEN, 0 },
        { 0xA2B6, 0x2e, BYTE_LEN, 0 },
        { 0xA2B7, 0x84, BYTE_LEN, 0 },
        { 0xA2B8, 0x71, BYTE_LEN, 0 },
        { 0xA2B9, 0x8b, BYTE_LEN, 0 },
        { 0xA2BA, 0x53, BYTE_LEN, 0 },
        { 0xA2BB, 0x74, BYTE_LEN, 0 },
        { 0xA2BC, 0x52, BYTE_LEN, 0 },
        { 0xA2BD, 0x93, BYTE_LEN, 0 },
        { 0xA2BE, 0x9e, BYTE_LEN, 0 },
        { 0xA2BF, 0x54, BYTE_LEN, 0 },
        { 0xA2C0, 0x05, BYTE_LEN, 0 },
        { 0xA2C1, 0x2f, BYTE_LEN, 0 },
        { 0xA2C2, 0x8f, BYTE_LEN, 0 },
        { 0xA2C3, 0x59, BYTE_LEN, 0 },
        { 0xA2C4, 0x4d, BYTE_LEN, 0 },
        { 0xA2C5, 0x67, BYTE_LEN, 0 },
        { 0xA2C6, 0xec, BYTE_LEN, 0 },
        { 0xA2C7, 0x42, BYTE_LEN, 0 },
        { 0xA2C8, 0x16, BYTE_LEN, 0 },
        { 0xA2C9, 0xaf, BYTE_LEN, 0 },
        { 0xA2CA, 0x98, BYTE_LEN, 0 },
        { 0xA2CB, 0x85, BYTE_LEN, 0 },
        { 0xA2CC, 0x2f, BYTE_LEN, 0 },
        { 0xA2CD, 0xa8, BYTE_LEN, 0 },
        { 0xA2CE, 0xb1, BYTE_LEN, 0 },
        { 0xA2CF, 0x0d, BYTE_LEN, 0 },
        { 0xA2D0, 0x72, BYTE_LEN, 0 },
        { 0xA2D1, 0x92, BYTE_LEN, 0 },
        { 0xA2D2, 0x13, BYTE_LEN, 0 },
        { 0xA2D3, 0x1b, BYTE_LEN, 0 },
        { 0xA2D4, 0xcf, BYTE_LEN, 0 },
        { 0xA2D5, 0x64, BYTE_LEN, 0 },
        { 0xA2D6, 0x26, BYTE_LEN, 0 },
        { 0xA2D7, 0x34, BYTE_LEN, 0 },
        { 0xA2D8, 0xb7, BYTE_LEN, 0 },
        { 0xA2D9, 0x99, BYTE_LEN, 0 },
        { 0xA2DA, 0x0e, BYTE_LEN, 0 },
        { 0xA2DB, 0x74, BYTE_LEN, 0 },
        { 0xA2DC, 0x40, BYTE_LEN, 0 },
        { 0xA2DD, 0x83, BYTE_LEN, 0 },
        { 0xA2DE, 0x9b, BYTE_LEN, 0 },
        { 0xA2DF, 0xda, BYTE_LEN, 0 },
        { 0xA2E0, 0x94, BYTE_LEN, 0 },
        { 0xA2E1, 0x26, BYTE_LEN, 0 },
        { 0xA2E2, 0x34, BYTE_LEN, 0 },
        { 0xA2E3, 0xa8, BYTE_LEN, 0 },
        { 0xA2E4, 0xd1, BYTE_LEN, 0 },
        { 0xA2E5, 0x4d, BYTE_LEN, 0 },
        { 0xA2E6, 0x70, BYTE_LEN, 0 },
        { 0xA2E7, 0x56, BYTE_LEN, 0 },
        { 0xA2E8, 0x03, BYTE_LEN, 0 },
        { 0xA2E9, 0x13, BYTE_LEN, 0 },
        { 0xA2EA, 0xbc, BYTE_LEN, 0 },
        { 0xA2EB, 0x44, BYTE_LEN, 0 },
        { 0xA2EC, 0x14, BYTE_LEN, 0 },
        { 0xA2ED, 0xa6, BYTE_LEN, 0 },
        
        { 0xA2EE, 0xd2, BYTE_LEN, 0 },
        { 0xA2EF, 0x41, BYTE_LEN, 0 },
        { 0xA2F0, 0x0f, BYTE_LEN, 0 },
        { 0xA2F1, 0x7a, BYTE_LEN, 0 },
        { 0xA2F2, 0xa4, BYTE_LEN, 0 },
        { 0xA2F3, 0xd3, BYTE_LEN, 0 },
        { 0xA2F4, 0x9c, BYTE_LEN, 0 },
        { 0xA2F5, 0xe9, BYTE_LEN, 0 },
        { 0xA2F6, 0x98, BYTE_LEN, 0 },
        { 0xA2F7, 0x87, BYTE_LEN, 0 },
        { 0xA2F8, 0x3d, BYTE_LEN, 0 },
        { 0xA2F9, 0xe3, BYTE_LEN, 0 },
        { 0xA2FA, 0xb9, BYTE_LEN, 0 },
        { 0xA2FB, 0x0f, BYTE_LEN, 0 },
        { 0xA2FC, 0x7e, BYTE_LEN, 0 },
        { 0xA2FD, 0xc0, BYTE_LEN, 0 },
        { 0xA2FE, 0x73, BYTE_LEN, 0 },
        { 0xA2FF, 0x9c, BYTE_LEN, 0 },
        { 0xA300, 0xdf, BYTE_LEN, 0 },
        { 0xA301, 0x1c, BYTE_LEN, 0 },
        { 0xA302, 0xc7, BYTE_LEN, 0 },
        { 0xA303, 0x3b, BYTE_LEN, 0 },
        { 0xA304, 0xf7, BYTE_LEN, 0 },
        { 0xA305, 0xb9, BYTE_LEN, 0 },
        { 0xA306, 0x0f, BYTE_LEN, 0 },
        { 0xA307, 0x76, BYTE_LEN, 0 },
        { 0xA308, 0x8c, BYTE_LEN, 0 },
        { 0xA309, 0x93, BYTE_LEN, 0 },
        { 0xA30A, 0x99, BYTE_LEN, 0 },
        { 0xA30B, 0xbe, BYTE_LEN, 0 },
        { 0xA30C, 0xd0, BYTE_LEN, 0 },
        { 0xA30D, 0x85, BYTE_LEN, 0 },
        { 0xA30E, 0x2f, BYTE_LEN, 0 },
        { 0xA30F, 0x97, BYTE_LEN, 0 },
        { 0xA310, 0x21, BYTE_LEN, 0 },
        { 0xA311, 0xce, BYTE_LEN, 0 },
        { 0xA312, 0x74, BYTE_LEN, 0 },
        { 0xA313, 0x58, BYTE_LEN, 0 },
        { 0xA314, 0xf3, BYTE_LEN, 0 },
        { 0xA315, 0x18, BYTE_LEN, 0 },
        { 0xA316, 0xb2, BYTE_LEN, 0 },
        { 0xA317, 0x1c, BYTE_LEN, 0 },
        { 0xA318, 0xc5, BYTE_LEN, 0 },
        { 0xA319, 0x27, BYTE_LEN, 0 },
        { 0xA31A, 0x49, BYTE_LEN, 0 },
        { 0xA31B, 0x31, BYTE_LEN, 0 },
        { 0xA31C, 0x8b, BYTE_LEN, 0 },
        { 0xA31D, 0x64, BYTE_LEN, 0 },
        { 0xA31E, 0x5a, BYTE_LEN, 0 },
        { 0xA31F, 0xe3, BYTE_LEN, 0 },
        { 0xA320, 0x98, BYTE_LEN, 0 },
        { 0xA321, 0xb7, BYTE_LEN, 0 },
        { 0xA322, 0xfc, BYTE_LEN, 0 },
        { 0xA323, 0x84, BYTE_LEN, 0 },
        { 0xA324, 0x23, BYTE_LEN, 0 },
        { 0xA325, 0x12, BYTE_LEN, 0 },
        { 0xA326, 0xf1, BYTE_LEN, 0 },
        { 0xA327, 0xc8, BYTE_LEN, 0 },
        { 0xA328, 0x50, BYTE_LEN, 0 },
        { 0xA329, 0xe8, BYTE_LEN, 0 },
        { 0xA32A, 0x02, BYTE_LEN, 0 },
        { 0xA32B, 0x99, BYTE_LEN, 0 },
        { 0xA32C, 0xbe, BYTE_LEN, 0 },
        { 0xA32D, 0x84, BYTE_LEN, 0 },
        { 0xA32E, 0x85, BYTE_LEN, 0 },
        { 0xA32F, 0x25, BYTE_LEN, 0 },
        { 0xA330, 0x08, BYTE_LEN, 0 },
        { 0xA331, 0xf9, BYTE_LEN, 0 },
        { 0xA332, 0xc7, BYTE_LEN, 0 },
        { 0xA333, 0x42, BYTE_LEN, 0 },
        { 0xA334, 0x66, BYTE_LEN, 0 },
        { 0xA335, 0x82, BYTE_LEN, 0 },
        { 0xA336, 0x96, BYTE_LEN, 0 },
        { 0xA337, 0xc0, BYTE_LEN, 0 },
        { 0xA338, 0xfc, BYTE_LEN, 0 },
        { 0xA339, 0x45, BYTE_LEN, 0 },
        { 0xA33A, 0x2c, BYTE_LEN, 0 },
        { 0xA33B, 0x2e, BYTE_LEN, 0 },
        { 0xA33C, 0x51, BYTE_LEN, 0 },
        { 0xA33D, 0x08, BYTE_LEN, 0 },
        { 0xA33E, 0x40, BYTE_LEN, 0 },
        { 0xA33F, 0x1a, BYTE_LEN, 0 },
        { 0xA340, 0x52, BYTE_LEN, 0 },
        { 0xA341, 0x13, BYTE_LEN, 0 },
        { 0xA342, 0xb5, BYTE_LEN, 0 },
        { 0xA343, 0x08, BYTE_LEN, 0 },
        { 0xA344, 0xa6, BYTE_LEN, 0 },
        { 0xA345, 0x32, BYTE_LEN, 0 },
        { 0xA346, 0x76, BYTE_LEN, 0 },
        { 0xA347, 0x21, BYTE_LEN, 0 },
        { 0xA348, 0x4a, BYTE_LEN, 0 },
        { 0xA349, 0x48, BYTE_LEN, 0 },
        { 0xA34A, 0x2e, BYTE_LEN, 0 },
        { 0xA34B, 0x42, BYTE_LEN, 0 },
        { 0xA34C, 0x12, BYTE_LEN, 0 },
        { 0xA34D, 0xa5, BYTE_LEN, 0 },
        { 0xA34E, 0xe8, BYTE_LEN, 0 },
        { 0xA34F, 0xa5, BYTE_LEN, 0 },
        { 0xA350, 0x32, BYTE_LEN, 0 },
        { 0xA351, 0xb8, BYTE_LEN, 0 },
        { 0xA352, 0xc9, BYTE_LEN, 0 },
        { 0xA353, 0x0c, BYTE_LEN, 0 },
        { 0xA354, 0x5b, BYTE_LEN, 0 },
        { 0xA355, 0xa2, BYTE_LEN, 0 },
        { 0xA356, 0x82, BYTE_LEN, 0 },
        { 0xA357, 0x94, BYTE_LEN, 0 },
        { 0xA358, 0xa8, BYTE_LEN, 0 },
        { 0xA359, 0xbc, BYTE_LEN, 0 },
        { 0xA35A, 0x85, BYTE_LEN, 0 },
        { 0xA35B, 0x33, BYTE_LEN, 0 },
        { 0xA35C, 0xb7, BYTE_LEN, 0 },
        { 0xA35D, 0x19, BYTE_LEN, 0 },
        { 0xA35E, 0x0f, BYTE_LEN, 0 },
        { 0xA35F, 0x74, BYTE_LEN, 0 },
        { 0xA360, 0x40, BYTE_LEN, 0 },
        { 0xA361, 0x93, BYTE_LEN, 0 },
        { 0xA362, 0x18, BYTE_LEN, 0 },
        { 0xA363, 0xc0, BYTE_LEN, 0 },
        { 0xA364, 0x20, BYTE_LEN, 0 },
        { 0xA365, 0x46, BYTE_LEN, 0 },
        { 0xA366, 0x34, BYTE_LEN, 0 },
        { 0xA367, 0xd5, BYTE_LEN, 0 },
        { 0xA368, 0x29, BYTE_LEN, 0 },
        { 0xA369, 0x0f, BYTE_LEN, 0 },
        { 0xA36A, 0x82, BYTE_LEN, 0 },
        { 0xA36B, 0x0c, BYTE_LEN, 0 },
        { 0xA36C, 0xa4, BYTE_LEN, 0 },
        { 0xA36D, 0x9e, BYTE_LEN, 0 },
        { 0xA36E, 0xe9, BYTE_LEN, 0 },
        { 0xA36F, 0x2c, BYTE_LEN, 0 },
        { 0xA370, 0x67, BYTE_LEN, 0 },
        { 0xA371, 0x3a, BYTE_LEN, 0 },
        { 0xA372, 0xe8, BYTE_LEN, 0 },
        { 0xA373, 0x39, BYTE_LEN, 0 },
        { 0xA374, 0x10, BYTE_LEN, 0 },
        { 0xA375, 0x81, BYTE_LEN, 0 },
        { 0xA376, 0xba, BYTE_LEN, 0 },
        { 0xA377, 0x53, BYTE_LEN, 0 },
        { 0xA378, 0x9f, BYTE_LEN, 0 },
        { 0xA379, 0xf8, BYTE_LEN, 0 },
        { 0xA37A, 0x74, BYTE_LEN, 0 },
        { 0xA37B, 0xe7, BYTE_LEN, 0 },
        { 0xA37C, 0x3a, BYTE_LEN, 0 },
        { 0xA37D, 0xde, BYTE_LEN, 0 },
        { 0xA37E, 0x71, BYTE_LEN, 0 },
        { 0xA37F, 0xcf, BYTE_LEN, 0 },
        { 0xA380, 0x7c, BYTE_LEN, 0 },
        { 0xA381, 0xb6, BYTE_LEN, 0 },
        { 0xA382, 0x43, BYTE_LEN, 0 },
        { 0xA383, 0x98, BYTE_LEN, 0 },
        { 0xA384, 0xc9, BYTE_LEN, 0 },
        { 0xA385, 0x50, BYTE_LEN, 0 },
        { 0xA386, 0xa6, BYTE_LEN, 0 },
        { 0xA387, 0x2f, BYTE_LEN, 0 },
        { 0xA388, 0x84, BYTE_LEN, 0 },
        { 0xA389, 0x99, BYTE_LEN, 0 },
        { 0xA38A, 0x0c, BYTE_LEN, 0 },
        { 0xA38B, 0x65, BYTE_LEN, 0 },
        { 0xA38C, 0xfa, BYTE_LEN, 0 },
        { 0xA38D, 0x82, BYTE_LEN, 0 },
        { 0xA38E, 0x97, BYTE_LEN, 0 },
        { 0xA38F, 0xc0, BYTE_LEN, 0 },
        { 0xA390, 0x38, BYTE_LEN, 0 },
        { 0xA391, 0x66, BYTE_LEN, 0 },
        { 0xA392, 0x33, BYTE_LEN, 0 },
        { 0xA393, 0x98, BYTE_LEN, 0 },
        { 0xA394, 0x01, BYTE_LEN, 0 },
        { 0xA395, 0xcd, BYTE_LEN, 0 },
        { 0xA396, 0x67, BYTE_LEN, 0 },
        { 0xA397, 0x1a, BYTE_LEN, 0 },
        { 0xA398, 0x93, BYTE_LEN, 0 },
        { 0xA399, 0x17, BYTE_LEN, 0 },
        { 0xA39A, 0xb9, BYTE_LEN, 0 },
        { 0xA39B, 0xf0, BYTE_LEN, 0 },
        { 0xA39C, 0x65, BYTE_LEN, 0 },
        { 0xA39D, 0x31, BYTE_LEN, 0 },
        { 0xA39E, 0xa2, BYTE_LEN, 0 },
        { 0xA39F, 0x21, BYTE_LEN, 0 },
        { 0xA3A0, 0x0d, BYTE_LEN, 0 },
        { 0xA3A1, 0x61, BYTE_LEN, 0 },
        { 0xA3A2, 0xf4, BYTE_LEN, 0 },
        { 0xA3A3, 0xc2, BYTE_LEN, 0 },
        { 0xA3A4, 0x95, BYTE_LEN, 0 },
        { 0xA3A5, 0xa6, BYTE_LEN, 0 },
        { 0xA3A6, 0x20, BYTE_LEN, 0 },
        { 0xA3A7, 0xe5, BYTE_LEN, 0 },
        { 0xA3A8, 0x29, BYTE_LEN, 0 },
        { 0xA3A9, 0x5e, BYTE_LEN, 0 },
        { 0xA3AA, 0xe1, BYTE_LEN, 0 },
        { 0xA3AB, 0x0b, BYTE_LEN, 0 },
        { 0xA3AC, 0x61, BYTE_LEN, 0 },
        { 0xA3AD, 0xd0, BYTE_LEN, 0 },
        { 0xA3AE, 0x72, BYTE_LEN, 0 },
        { 0xA3AF, 0x15, BYTE_LEN, 0 },
        { 0xA3B0, 0x9f, BYTE_LEN, 0 },
        { 0xA3B1, 0xbc, BYTE_LEN, 0 },
        { 0xA3B2, 0x64, BYTE_LEN, 0 },
        { 0xA3B3, 0x25, BYTE_LEN, 0 },
        { 0xA3B4, 0x32, BYTE_LEN, 0 },
        { 0xA3B5, 0x11, BYTE_LEN, 0 },
        { 0xA3B6, 0x0a, BYTE_LEN, 0 },
        { 0xA3B7, 0x56, BYTE_LEN, 0 },
        { 0xA3B8, 0xc8, BYTE_LEN, 0 },
        { 0xA3B9, 0x02, BYTE_LEN, 0 },
        { 0xA3BA, 0x15, BYTE_LEN, 0 },
        { 0xA3BB, 0xa1, BYTE_LEN, 0 },
        { 0xA3BC, 0xa4, BYTE_LEN, 0 },
        { 0xA3BD, 0x44, BYTE_LEN, 0 },
        { 0xA3BE, 0x22, BYTE_LEN, 0 },
        { 0xA3BF, 0x0d, BYTE_LEN, 0 },
        { 0xA3C0, 0xa1, BYTE_LEN, 0 },
        { 0xA3C1, 0x88, BYTE_LEN, 0 },
        { 0xA3C2, 0x4b, BYTE_LEN, 0 },
        { 0xA3C3, 0x92, BYTE_LEN, 0 },
        { 0xA3C4, 0x52, BYTE_LEN, 0 },
        { 0xA3C5, 0x15, BYTE_LEN, 0 },
        { 0xA3C6, 0xa4, BYTE_LEN, 0 },
        { 0xA3C7, 0xf0, BYTE_LEN, 0 },
        { 0xA3C8, 0xa4, BYTE_LEN, 0 },
        { 0xA3C9, 0x23, BYTE_LEN, 0 },
        { 0xA3CA, 0x04, BYTE_LEN, 0 },
        { 0xA3CB, 0xf9, BYTE_LEN, 0 },
        { 0xA3CC, 0x87, BYTE_LEN, 0 },
        { 0xA3CD, 0x42, BYTE_LEN, 0 },
        { 0xA3CE, 0x4c, BYTE_LEN, 0 },
        { 0xA3CF, 0x42, BYTE_LEN, 0 },
        { 0xA3D0, 0x94, BYTE_LEN, 0 },
        { 0xA3D1, 0xa5, BYTE_LEN, 0 },
        { 0xA3D2, 0x24, BYTE_LEN, 0 },
        { 0xA3D3, 0xc5, BYTE_LEN, 0 },
        { 0xA3D4, 0x27, BYTE_LEN, 0 },
        { 0xA3D5, 0x20, BYTE_LEN, 0 },
        { 0xA3D6, 0x39, BYTE_LEN, 0 },
        { 0xA3D7, 0x08, BYTE_LEN, 0 },
        { 0xA3D8, 0x40, BYTE_LEN, 0 },
        { 0xA3D9, 0x1a, BYTE_LEN, 0 },
        { 0xA3DA, 0x62, BYTE_LEN, 0 },
        { 0xA3DB, 0x12, BYTE_LEN, 0 },
        { 0xA3DC, 0xa2, BYTE_LEN, 0 },
        { 0xA3DD, 0x2c, BYTE_LEN, 0 },
        { 0xA3DE, 0x05, BYTE_LEN, 0 },
        { 0xA3DF, 0x2b, BYTE_LEN, 0 },
        { 0xA3E0, 0x49, BYTE_LEN, 0 },
        { 0xA3E1, 0x81, BYTE_LEN, 0 },
        { 0xA3E2, 0x49, BYTE_LEN, 0 },
        { 0xA3E3, 0x46, BYTE_LEN, 0 },
        { 0xA3E4, 0x22, BYTE_LEN, 0 },
        { 0xA3E5, 0xa2, BYTE_LEN, 0 },
        { 0xA3E6, 0x11, BYTE_LEN, 0 },
        { 0xA3E7, 0x99, BYTE_LEN, 0 },
        { 0xA3E8, 0x2c, BYTE_LEN, 0 },
        { 0xA3E9, 0xc5, BYTE_LEN, 0 },
        { 0xA3EA, 0x2a, BYTE_LEN, 0 },
        { 0xA3EB, 0x6e, BYTE_LEN, 0 },
        { 0xA3EC, 0xe9, BYTE_LEN, 0 },
        { 0xA3ED, 0x8a, BYTE_LEN, 0 },
        { 0xA3EE, 0x51, BYTE_LEN, 0 },
        { 0xA3EF, 0x68, BYTE_LEN, 0 },
        { 0xA3F0, 0xe2, BYTE_LEN, 0 },
        { 0xA3F1, 0x12, BYTE_LEN, 0 },
        { 0xA3F2, 0x9b, BYTE_LEN, 0 },
        { 0xA3F3, 0x14, BYTE_LEN, 0 },
        { 0xA3F4, 0x65, BYTE_LEN, 0 },
        { 0xA3F5, 0x2b, BYTE_LEN, 0 },
        { 0xA3F6, 0x67, BYTE_LEN, 0 },
        { 0xA3F7, 0x81, BYTE_LEN, 0 },
        { 0xA3F8, 0x4c, BYTE_LEN, 0 },
        { 0xA3F9, 0x61, BYTE_LEN, 0 },
        { 0xA3FA, 0xca, BYTE_LEN, 0 },
        { 0xA3FB, 0x22, BYTE_LEN, 0 },
        { 0xA3FC, 0x15, BYTE_LEN, 0 },
        { 0xA3FD, 0xa6, BYTE_LEN, 0 },
        { 0xA3FE, 0x48, BYTE_LEN, 0 },
        { 0xA3FF, 0x05, BYTE_LEN, 0 },
        { 0xA400, 0x2c, BYTE_LEN, 0 },
        { 0xA401, 0x7e, BYTE_LEN, 0 },
        { 0xA402, 0x31, BYTE_LEN, 0 },
        { 0xA403, 0xcc, BYTE_LEN, 0 },
        { 0xA404, 0x6c, BYTE_LEN, 0 },
        { 0xA405, 0x5a, BYTE_LEN, 0 },
        { 0xA406, 0x33, BYTE_LEN, 0 },
        { 0xA407, 0x19, BYTE_LEN, 0 },
        { 0xA408, 0xc0, BYTE_LEN, 0 },
        { 0xA409, 0xec, BYTE_LEN, 0 },
        { 0xA40A, 0xe5, BYTE_LEN, 0 },
        { 0xA40B, 0x2f, BYTE_LEN, 0 },
        { 0xA40C, 0x8e, BYTE_LEN, 0 },
        { 0xA40D, 0x01, BYTE_LEN, 0 },
        { 0xA40E, 0x0d, BYTE_LEN, 0 },
        { 0xA40F, 0x67, BYTE_LEN, 0 },
        { 0xA410, 0x2e, BYTE_LEN, 0 },
        { 0xA411, 0x53, BYTE_LEN, 0 },
        { 0xA412, 0x9a, BYTE_LEN, 0 },
        { 0xA413, 0xcb, BYTE_LEN, 0 },
        { 0xA414, 0x1c, BYTE_LEN, 0 },
        { 0xA415, 0x46, BYTE_LEN, 0 },
        { 0xA416, 0x30, BYTE_LEN, 0 },
        { 0xA417, 0x85, BYTE_LEN, 0 },
        { 0xA418, 0x91, BYTE_LEN, 0 },
        { 0xA419, 0x0c, BYTE_LEN, 0 },
        { 0xA41A, 0x65, BYTE_LEN, 0 },
        { 0xA41B, 0x08, BYTE_LEN, 0 },
        { 0xA41C, 0x03, BYTE_LEN, 0 },
        { 0xA41D, 0x00, BYTE_LEN, 0 },
        { 0xA41E, 0x00, BYTE_LEN, 0 },
        { 0xA41F, 0x00, BYTE_LEN, 0 },
        { 0xA420, 0x00, BYTE_LEN, 0 },
        { 0xA421, 0x0a, BYTE_LEN, 0 },
        
        { 0x0068, 0x5F, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain on
};

struct isx006_i2c_reg_conf isx006_SHD_TYP_2nd_settings[] = {
        //2009/12/28
        // ISX006 KMOT ES2 no.15 Module(Index2) 
        // PreSHD/SHD1/2/3 inifile
        // After Gamma 70%
        // SHD3 A+TLD
        { 0x0068, 0x50, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain off
        
        { 0x9000, 0x8282, WORD_LEN, 0 },    
        { 0x9002, 0x02, BYTE_LEN, 0 },
        { 0x9003, 0x0e, BYTE_LEN, 0 },
        { 0x9004, 0x08, BYTE_LEN, 0 },
        { 0x9005, 0x38, BYTE_LEN, 0 },
        { 0x9006, 0x10, BYTE_LEN, 0 },
        { 0x9007, 0x20, BYTE_LEN, 0 },
        { 0x9008, 0x01, BYTE_LEN, 0 },
        { 0x9009, 0x00, BYTE_LEN, 0 },
        { 0x900A, 0x04, BYTE_LEN, 0 },
        { 0x900B, 0x01, BYTE_LEN, 0 },
        { 0x900C, 0x12, BYTE_LEN, 0 },
        { 0x900D, 0x04, BYTE_LEN, 0 },
        { 0x900E, 0x48, BYTE_LEN, 0 },
        { 0x900F, 0x10, BYTE_LEN, 0 },
        { 0x9010, 0x00, BYTE_LEN, 0 },
        { 0x9011, 0xc1, BYTE_LEN, 0 },
        { 0x9012, 0x80, BYTE_LEN, 0 },
        { 0x9013, 0x04, BYTE_LEN, 0 },
        { 0x9014, 0x03, BYTE_LEN, 0 },
        { 0x9015, 0x12, BYTE_LEN, 0 },
        { 0x9016, 0x08, BYTE_LEN, 0 },
        { 0x9017, 0x38, BYTE_LEN, 0 },
        { 0x9018, 0x20, BYTE_LEN, 0 },
        { 0x9019, 0xe0, BYTE_LEN, 0 },
        { 0x901A, 0x40, BYTE_LEN, 0 },
        { 0x901B, 0x80, BYTE_LEN, 0 },
        { 0x901C, 0x04, BYTE_LEN, 0 },
        { 0x901D, 0x00, BYTE_LEN, 0 },
        { 0x901E, 0x10, BYTE_LEN, 0 },
        { 0x901F, 0x04, BYTE_LEN, 0 },
        { 0x9020, 0x48, BYTE_LEN, 0 },
        { 0x9021, 0x10, BYTE_LEN, 0 },
        { 0x9022, 0x20, BYTE_LEN, 0 },
        { 0x9023, 0x41, BYTE_LEN, 0 },
        { 0x9024, 0x00, BYTE_LEN, 0 },
        { 0x9025, 0x04, BYTE_LEN, 0 },
        { 0x9026, 0x03, BYTE_LEN, 0 },
        { 0x9027, 0x12, BYTE_LEN, 0 },
        { 0x9028, 0x0c, BYTE_LEN, 0 },
        { 0x9029, 0x48, BYTE_LEN, 0 },
        { 0x902A, 0x10, BYTE_LEN, 0 },
        { 0x902B, 0xc0, BYTE_LEN, 0 },
        { 0x902C, 0x40, BYTE_LEN, 0 },
        { 0x902D, 0x00, BYTE_LEN, 0 },
        { 0x902E, 0x03, BYTE_LEN, 0 },
        { 0x902F, 0x03, BYTE_LEN, 0 },
        { 0x9030, 0x0c, BYTE_LEN, 0 },
        { 0x9031, 0x08, BYTE_LEN, 0 },
        { 0x9032, 0x38, BYTE_LEN, 0 },
        { 0x9033, 0x10, BYTE_LEN, 0 },
        { 0x9034, 0xa0, BYTE_LEN, 0 },
        { 0x9035, 0x80, BYTE_LEN, 0 },
        { 0x9036, 0x80, BYTE_LEN, 0 },
        { 0x9037, 0x03, BYTE_LEN, 0 },
        { 0x9038, 0x02, BYTE_LEN, 0 },
        { 0x9039, 0x10, BYTE_LEN, 0 },
        { 0x903A, 0x08, BYTE_LEN, 0 },
        { 0x903B, 0x40, BYTE_LEN, 0 },
        { 0x903C, 0x20, BYTE_LEN, 0 },
        { 0x903D, 0x00, BYTE_LEN, 0 },
        { 0x903E, 0x01, BYTE_LEN, 0 },
        { 0x903F, 0x00, BYTE_LEN, 0 },
        { 0x9040, 0x03, BYTE_LEN, 0 },
        { 0x9041, 0x00, BYTE_LEN, 0 },
        { 0x9042, 0x0c, BYTE_LEN, 0 },
        { 0x9043, 0x04, BYTE_LEN, 0 },
        { 0x9044, 0x30, BYTE_LEN, 0 },
        { 0x9045, 0x30, BYTE_LEN, 0 },
        { 0x9046, 0xa0, BYTE_LEN, 0 },
        { 0x9047, 0x80, BYTE_LEN, 0 },
        { 0x9048, 0x00, BYTE_LEN, 0 },
        { 0x9049, 0x03, BYTE_LEN, 0 },
        { 0x904A, 0x02, BYTE_LEN, 0 },
        { 0x904B, 0x0c, BYTE_LEN, 0 },
        { 0x904C, 0x04, BYTE_LEN, 0 },
        { 0x904D, 0x30, BYTE_LEN, 0 },
        { 0x904E, 0x10, BYTE_LEN, 0 },
        { 0x904F, 0xe0, BYTE_LEN, 0 },
        { 0x9050, 0x40, BYTE_LEN, 0 },
        { 0x9051, 0x80, BYTE_LEN, 0 },
        { 0x9052, 0x03, BYTE_LEN, 0 },
        { 0x9053, 0x02, BYTE_LEN, 0 },
        { 0x9054, 0x0a, BYTE_LEN, 0 },
        { 0x9055, 0x08, BYTE_LEN, 0 },
        { 0x9056, 0x28, BYTE_LEN, 0 },
        { 0x9057, 0x20, BYTE_LEN, 0 },
        { 0x9058, 0x80, BYTE_LEN, 0 },
        { 0x9059, 0x80, BYTE_LEN, 0 },
        { 0x905A, 0x00, BYTE_LEN, 0 },
        { 0x905B, 0x01, BYTE_LEN, 0 },
        { 0x905C, 0x01, BYTE_LEN, 0 },
        { 0x905D, 0x06, BYTE_LEN, 0 },
        { 0x905E, 0x0c, BYTE_LEN, 0 },
        { 0x905F, 0x18, BYTE_LEN, 0 },
        { 0x9060, 0xe0, BYTE_LEN, 0 },
        { 0x9061, 0x9f, BYTE_LEN, 0 },
        { 0x9062, 0x40, BYTE_LEN, 0 },
        { 0x9063, 0x00, BYTE_LEN, 0 },
        { 0x9064, 0x03, BYTE_LEN, 0 },
        { 0x9065, 0x01, BYTE_LEN, 0 },
        { 0x9066, 0x0c, BYTE_LEN, 0 },
        { 0x9067, 0x0c, BYTE_LEN, 0 },
        { 0x9068, 0x30, BYTE_LEN, 0 },
        { 0x9069, 0x30, BYTE_LEN, 0 },
        { 0x906A, 0xc0, BYTE_LEN, 0 },
        { 0x906B, 0x00, BYTE_LEN, 0 },
        { 0x906C, 0x01, BYTE_LEN, 0 },
        { 0x906D, 0x01, BYTE_LEN, 0 },
        { 0x906E, 0x02, BYTE_LEN, 0 },
        { 0x906F, 0x04, BYTE_LEN, 0 },
        { 0x9070, 0x04, BYTE_LEN, 0 },
        { 0x9071, 0x00, BYTE_LEN, 0 },
        { 0x9072, 0x10, BYTE_LEN, 0 },
        { 0x9073, 0x20, BYTE_LEN, 0 },
        { 0x9074, 0x00, BYTE_LEN, 0 },
        { 0x9075, 0x00, BYTE_LEN, 0 },
        { 0x9076, 0x02, BYTE_LEN, 0 },
        { 0x9077, 0x02, BYTE_LEN, 0 },
        { 0x9078, 0x0c, BYTE_LEN, 0 },
        { 0x9079, 0x08, BYTE_LEN, 0 },
        { 0x907A, 0x30, BYTE_LEN, 0 },
        { 0x907B, 0x30, BYTE_LEN, 0 },
        { 0x907C, 0x80, BYTE_LEN, 0 },
        { 0x907D, 0xc0, BYTE_LEN, 0 },
        { 0x907E, 0x00, BYTE_LEN, 0 },
        { 0x907F, 0x02, BYTE_LEN, 0 },
        { 0x9080, 0x03, BYTE_LEN, 0 },
        { 0x9081, 0x06, BYTE_LEN, 0 },
        { 0x9082, 0x08, BYTE_LEN, 0 },
        { 0x9083, 0x08, BYTE_LEN, 0 },
        { 0x9084, 0x20, BYTE_LEN, 0 },
        { 0x9085, 0x20, BYTE_LEN, 0 },
        { 0x9086, 0xc0, BYTE_LEN, 0 },
        { 0x9087, 0x00, BYTE_LEN, 0 },
        { 0x9088, 0x01, BYTE_LEN, 0 },
        { 0x9089, 0x03, BYTE_LEN, 0 },
        { 0x908A, 0x04, BYTE_LEN, 0 },
        { 0x908B, 0x08, BYTE_LEN, 0 },
        { 0x908C, 0x20, BYTE_LEN, 0 },
        { 0x908D, 0x20, BYTE_LEN, 0 },
        { 0x908E, 0x80, BYTE_LEN, 0 },
        { 0x908F, 0x40, BYTE_LEN, 0 },
        { 0x9090, 0x00, BYTE_LEN, 0 },
        { 0x9091, 0x02, BYTE_LEN, 0 },
        { 0x9092, 0x01, BYTE_LEN, 0 },
        { 0x9093, 0x08, BYTE_LEN, 0 },
        { 0x9094, 0x10, BYTE_LEN, 0 },
        { 0x9095, 0x08, BYTE_LEN, 0 },
        { 0x9096, 0x50, BYTE_LEN, 0 },
        { 0x9097, 0x20, BYTE_LEN, 0 },
        { 0x9098, 0xc0, BYTE_LEN, 0 },
        { 0x9099, 0x80, BYTE_LEN, 0 },
        { 0x909A, 0x00, BYTE_LEN, 0 },
        { 0x909B, 0x04, BYTE_LEN, 0 },
        { 0x909C, 0x02, BYTE_LEN, 0 },
        { 0x909D, 0x10, BYTE_LEN, 0 },
        { 0x909E, 0x18, BYTE_LEN, 0 },
        { 0x909F, 0x20, BYTE_LEN, 0 },
        { 0x90A0, 0x80, BYTE_LEN, 0 },
        { 0x90A1, 0x80, BYTE_LEN, 0 },
        { 0x90A2, 0x00, BYTE_LEN, 0 },
        { 0x90A3, 0x02, BYTE_LEN, 0 },
        { 0x90A4, 0x03, BYTE_LEN, 0 },
        { 0x90A5, 0x08, BYTE_LEN, 0 },
        { 0x90A6, 0x0c, BYTE_LEN, 0 },
        { 0x90A7, 0x20, BYTE_LEN, 0 },
        { 0x90A8, 0x40, BYTE_LEN, 0 },
        { 0x90A9, 0x80, BYTE_LEN, 0 },
        { 0x90AA, 0x00, BYTE_LEN, 0 },
        { 0x90AB, 0x01, BYTE_LEN, 0 },
        { 0x90AC, 0x02, BYTE_LEN, 0 },
        { 0x90AD, 0x02, BYTE_LEN, 0 },
        { 0x90AE, 0x06, BYTE_LEN, 0 },
        { 0x90AF, 0x0c, BYTE_LEN, 0 },
        { 0x90B0, 0x18, BYTE_LEN, 0 },
        { 0x90B1, 0x40, BYTE_LEN, 0 },
        { 0x90B2, 0x60, BYTE_LEN, 0 },
        { 0x90B3, 0xc0, BYTE_LEN, 0 },
        { 0x90B4, 0x00, BYTE_LEN, 0 },
        { 0x90B5, 0x02, BYTE_LEN, 0 },
        { 0x90B6, 0x03, BYTE_LEN, 0 },
        { 0x90B7, 0x08, BYTE_LEN, 0 },
        { 0x90B8, 0x0c, BYTE_LEN, 0 },
        { 0x90B9, 0x20, BYTE_LEN, 0 },
        { 0x90BA, 0x30, BYTE_LEN, 0 },
        { 0x90BB, 0x80, BYTE_LEN, 0 },
        { 0x90BC, 0x40, BYTE_LEN, 0 },
        { 0x90BD, 0x81, BYTE_LEN, 0 },
        { 0x90BE, 0x02, BYTE_LEN, 0 },
        { 0x90BF, 0x04, BYTE_LEN, 0 },
        { 0x90C0, 0x06, BYTE_LEN, 0 },
        { 0x90C1, 0x18, BYTE_LEN, 0 },
        { 0x90C2, 0x20, BYTE_LEN, 0 },
        { 0x90C3, 0x60, BYTE_LEN, 0 },
        { 0x90C4, 0x80, BYTE_LEN, 0 },
        { 0x90C5, 0x40, BYTE_LEN, 0 },
        { 0x90C6, 0x81, BYTE_LEN, 0 },
        { 0x90C7, 0x02, BYTE_LEN, 0 },
        { 0x90C8, 0x06, BYTE_LEN, 0 },
        { 0x90C9, 0x0a, BYTE_LEN, 0 },
        { 0x90CA, 0x18, BYTE_LEN, 0 },
        { 0x90CB, 0x28, BYTE_LEN, 0 },
        { 0x90CC, 0x20, BYTE_LEN, 0 },
        { 0x90CD, 0x80, BYTE_LEN, 0 },
        { 0x90CE, 0x80, BYTE_LEN, 0 },
        { 0x90CF, 0x00, BYTE_LEN, 0 },
        { 0x90D0, 0x02, BYTE_LEN, 0 },
        { 0x90D1, 0x03, BYTE_LEN, 0 },
        { 0x90D2, 0x08, BYTE_LEN, 0 },
        { 0x90D3, 0x10, BYTE_LEN, 0 },
        { 0x90D4, 0x20, BYTE_LEN, 0 },
        { 0x90D5, 0x60, BYTE_LEN, 0 },
        { 0x90D6, 0xa0, BYTE_LEN, 0 },
        { 0x90D7, 0x80, BYTE_LEN, 0 },
        { 0x90D8, 0x80, BYTE_LEN, 0 },
        { 0x90D9, 0x02, BYTE_LEN, 0 },
        { 0x90DA, 0x03, BYTE_LEN, 0 },
        { 0x90DB, 0x06, BYTE_LEN, 0 },
        { 0x90DC, 0x1c, BYTE_LEN, 0 },
        { 0x90DD, 0x30, BYTE_LEN, 0 },
        { 0x90DE, 0x70, BYTE_LEN, 0 },
        { 0x90DF, 0xc0, BYTE_LEN, 0 },
        { 0x90E0, 0x80, BYTE_LEN, 0 },
        { 0x90E1, 0x00, BYTE_LEN, 0 },
        { 0x90E2, 0x02, BYTE_LEN, 0 },
        { 0x90E3, 0x02, BYTE_LEN, 0 },
        { 0x90E4, 0x08, BYTE_LEN, 0 },
        { 0x90E5, 0x0c, BYTE_LEN, 0 },
        { 0x90E6, 0x20, BYTE_LEN, 0 },
        { 0x90E7, 0x40, BYTE_LEN, 0 },
        { 0x90E8, 0x80, BYTE_LEN, 0 },
        { 0x90E9, 0x80, BYTE_LEN, 0 },
        { 0x90EA, 0x81, BYTE_LEN, 0 },
        { 0x90EB, 0x02, BYTE_LEN, 0 },
        { 0x90EC, 0x02, BYTE_LEN, 0 },
        { 0x90ED, 0x0a, BYTE_LEN, 0 },
        { 0x90EE, 0x0c, BYTE_LEN, 0 },
        { 0x90EF, 0x18, BYTE_LEN, 0 },
        { 0x90F0, 0x70, BYTE_LEN, 0 },
        { 0x90F1, 0xc0, BYTE_LEN, 0 },
        { 0x90F2, 0xc0, BYTE_LEN, 0 },
        { 0x90F3, 0x01, BYTE_LEN, 0 },
        { 0x90F4, 0x03, BYTE_LEN, 0 },
        { 0x90F5, 0x00, BYTE_LEN, 0 },
        { 0x90F6, 0xf0, BYTE_LEN, 0 },
        { 0x90F7, 0x03, BYTE_LEN, 0 },
        { 0x90F8, 0xc0, BYTE_LEN, 0 },
        { 0x90F9, 0x1f, BYTE_LEN, 0 },
        { 0x90FA, 0xc0, BYTE_LEN, 0 },
        { 0x90FB, 0xfe, BYTE_LEN, 0 },
        { 0x90FC, 0xff, BYTE_LEN, 0 },
        { 0x90FD, 0xfc, BYTE_LEN, 0 },
        { 0x90FE, 0x01, BYTE_LEN, 0 },
        { 0x90FF, 0xec, BYTE_LEN, 0 },
        { 0x9100, 0xff, BYTE_LEN, 0 },
        { 0x9101, 0xbf, BYTE_LEN, 0 },
        { 0x9102, 0x0f, BYTE_LEN, 0 },
        { 0x9103, 0x20, BYTE_LEN, 0 },
        { 0x9104, 0x7f, BYTE_LEN, 0 },
        { 0x9105, 0x00, BYTE_LEN, 0 },
        { 0x9106, 0xfb, BYTE_LEN, 0 },
        { 0x9107, 0x01, BYTE_LEN, 0 },
        { 0x9108, 0xec, BYTE_LEN, 0 },
        { 0x9109, 0x03, BYTE_LEN, 0 },
        { 0x910A, 0xc0, BYTE_LEN, 0 },
        { 0x910B, 0x0f, BYTE_LEN, 0 },
        { 0x910C, 0x00, BYTE_LEN, 0 },
        { 0x910D, 0x7f, BYTE_LEN, 0 },
        { 0x910E, 0x00, BYTE_LEN, 0 },
        { 0x910F, 0xfb, BYTE_LEN, 0 },
        { 0x9110, 0xff, BYTE_LEN, 0 },
        { 0x9111, 0xf3, BYTE_LEN, 0 },
        { 0x9112, 0x07, BYTE_LEN, 0 },
        { 0x9113, 0xb0, BYTE_LEN, 0 },
        { 0x9114, 0xff, BYTE_LEN, 0 },
        { 0x9115, 0xff, BYTE_LEN, 0 },
        { 0x9116, 0x3e, BYTE_LEN, 0 },
        { 0x9117, 0x80, BYTE_LEN, 0 },
        { 0x9118, 0xfc, BYTE_LEN, 0 },
        { 0x9119, 0x01, BYTE_LEN, 0 },
        { 0x911A, 0xec, BYTE_LEN, 0 },
        { 0x911B, 0x07, BYTE_LEN, 0 },
        { 0x911C, 0xb0, BYTE_LEN, 0 },
        { 0x911D, 0x2f, BYTE_LEN, 0 },
        { 0x911E, 0x80, BYTE_LEN, 0 },
        { 0x911F, 0xbe, BYTE_LEN, 0 },
        { 0x9120, 0x00, BYTE_LEN, 0 },
        { 0x9121, 0xfa, BYTE_LEN, 0 },
        { 0x9122, 0x02, BYTE_LEN, 0 },
        { 0x9123, 0xec, BYTE_LEN, 0 },
        { 0x9124, 0x03, BYTE_LEN, 0 },
        { 0x9125, 0xc0, BYTE_LEN, 0 },
        { 0x9126, 0x0f, BYTE_LEN, 0 },
        { 0x9127, 0x80, BYTE_LEN, 0 },
        { 0x9128, 0xfe, BYTE_LEN, 0 },
        { 0x9129, 0x7f, BYTE_LEN, 0 },
        { 0x912A, 0xfa, BYTE_LEN, 0 },
        { 0x912B, 0x01, BYTE_LEN, 0 },
        { 0x912C, 0xf2, BYTE_LEN, 0 },
        { 0x912D, 0x03, BYTE_LEN, 0 },
        { 0x912E, 0xc0, BYTE_LEN, 0 },
        { 0x912F, 0x0f, BYTE_LEN, 0 },
        { 0x9130, 0x00, BYTE_LEN, 0 },
        { 0x9131, 0x7f, BYTE_LEN, 0 },
        { 0x9132, 0x00, BYTE_LEN, 0 },
        { 0x9133, 0xfc, BYTE_LEN, 0 },
        { 0x9134, 0x01, BYTE_LEN, 0 },
        { 0x9135, 0xf0, BYTE_LEN, 0 },
        { 0x9136, 0x07, BYTE_LEN, 0 },
        { 0x9137, 0xa8, BYTE_LEN, 0 },
        { 0x9138, 0x0f, BYTE_LEN, 0 },
        { 0x9139, 0xa0, BYTE_LEN, 0 },
        { 0x913A, 0xfe, BYTE_LEN, 0 },
        { 0x913B, 0xff, BYTE_LEN, 0 },
        { 0x913C, 0xfb, BYTE_LEN, 0 },
        { 0x913D, 0xfe, BYTE_LEN, 0 },
        { 0x913E, 0xf1, BYTE_LEN, 0 },
        { 0x913F, 0xfb, BYTE_LEN, 0 },
        { 0x9140, 0xb7, BYTE_LEN, 0 },
        { 0x9141, 0x1f, BYTE_LEN, 0 },
        { 0x9142, 0xa0, BYTE_LEN, 0 },
        { 0x9143, 0x7e, BYTE_LEN, 0 },
        { 0x9144, 0x80, BYTE_LEN, 0 },
        { 0x9145, 0xfa, BYTE_LEN, 0 },
        { 0x9146, 0x02, BYTE_LEN, 0 },
        { 0x9147, 0xee, BYTE_LEN, 0 },
        { 0x9148, 0x0b, BYTE_LEN, 0 },
        { 0x9149, 0xb8, BYTE_LEN, 0 },
        { 0x914A, 0x2f, BYTE_LEN, 0 },
        { 0x914B, 0xe0, BYTE_LEN, 0 },
        { 0x914C, 0x3e, BYTE_LEN, 0 },
        { 0x914D, 0x80, BYTE_LEN, 0 },
        { 0x914E, 0xfd, BYTE_LEN, 0 },
        { 0x914F, 0xff, BYTE_LEN, 0 },
        { 0x9150, 0xef, BYTE_LEN, 0 },
        { 0x9151, 0xff, BYTE_LEN, 0 },
        { 0x9152, 0xcf, BYTE_LEN, 0 },
        { 0x9153, 0x0f, BYTE_LEN, 0 },
        { 0x9154, 0xe0, BYTE_LEN, 0 },
        { 0x9155, 0x3e, BYTE_LEN, 0 },
        { 0x9156, 0x00, BYTE_LEN, 0 },
        { 0x9157, 0xfd, BYTE_LEN, 0 },
        { 0x9158, 0x00, BYTE_LEN, 0 },
        { 0x9159, 0xf4, BYTE_LEN, 0 },
        { 0x915A, 0x13, BYTE_LEN, 0 },
        { 0x915B, 0xe0, BYTE_LEN, 0 },
        { 0x915C, 0x4f, BYTE_LEN, 0 },
        { 0x915D, 0x80, BYTE_LEN, 0 },
        { 0x915E, 0x3f, BYTE_LEN, 0 },
        { 0x915F, 0x00, BYTE_LEN, 0 },
        { 0x9160, 0xfd, BYTE_LEN, 0 },
        { 0x9161, 0x00, BYTE_LEN, 0 },
        { 0x9162, 0xf8, BYTE_LEN, 0 },
        { 0x9163, 0xff, BYTE_LEN, 0 },
        { 0x9164, 0xef, BYTE_LEN, 0 },
        { 0x9165, 0xff, BYTE_LEN, 0 },
        { 0x9166, 0x7f, BYTE_LEN, 0 },
        { 0x9167, 0x3f, BYTE_LEN, 0 },
        { 0x9168, 0x00, BYTE_LEN, 0 },
        { 0x9169, 0xfe, BYTE_LEN, 0 },
        { 0x916A, 0x01, BYTE_LEN, 0 },
        { 0x916B, 0xf8, BYTE_LEN, 0 },
        { 0x916C, 0x07, BYTE_LEN, 0 },
        { 0x916D, 0xe0, BYTE_LEN, 0 },
        { 0x916E, 0x6f, BYTE_LEN, 0 },
        { 0x916F, 0x80, BYTE_LEN, 0 },
        { 0x9170, 0xbf, BYTE_LEN, 0 },
        { 0x9171, 0x01, BYTE_LEN, 0 },
        { 0x9172, 0xfe, BYTE_LEN, 0 },
        { 0x9173, 0x03, BYTE_LEN, 0 },
        { 0x9174, 0xfe, BYTE_LEN, 0 },
        { 0x9175, 0x0b, BYTE_LEN, 0 },
        { 0x9176, 0xf8, BYTE_LEN, 0 },
        { 0x9177, 0x0f, BYTE_LEN, 0 },
        { 0x9178, 0xe0, BYTE_LEN, 0 },
        { 0x9179, 0xff, BYTE_LEN, 0 },
        { 0x917A, 0x7f, BYTE_LEN, 0 },
        { 0x917B, 0xff, BYTE_LEN, 0 },
        { 0x917C, 0x02, BYTE_LEN, 0 },
        { 0x917D, 0x00, BYTE_LEN, 0 },
        { 0x917E, 0x08, BYTE_LEN, 0 },
        { 0x917F, 0xe8, BYTE_LEN, 0 },
        { 0x9180, 0x2f, BYTE_LEN, 0 },
        { 0x9181, 0xa0, BYTE_LEN, 0 },
        { 0x9182, 0x7f, BYTE_LEN, 0 },
        { 0x9183, 0x01, BYTE_LEN, 0 },
        { 0x9184, 0xff, BYTE_LEN, 0 },
        { 0x9185, 0x05, BYTE_LEN, 0 },
        { 0x9186, 0xfc, BYTE_LEN, 0 },
        { 0x9187, 0x13, BYTE_LEN, 0 },
        { 0x9188, 0x10, BYTE_LEN, 0 },
        { 0x9189, 0x30, BYTE_LEN, 0 },
        { 0x918A, 0x60, BYTE_LEN, 0 },
        { 0x918B, 0x80, BYTE_LEN, 0 },
        { 0x918C, 0x80, BYTE_LEN, 0 },
        { 0x918D, 0x00, BYTE_LEN, 0 },
        { 0x918E, 0x02, BYTE_LEN, 0 },
        { 0x918F, 0x0c, BYTE_LEN, 0 },
        { 0x9190, 0x00, BYTE_LEN, 0 },
        { 0x9191, 0x20, BYTE_LEN, 0 },
        { 0x9192, 0x30, BYTE_LEN, 0 },
        { 0x9193, 0x20, BYTE_LEN, 0 },
        { 0x9194, 0xc0, BYTE_LEN, 0 },
        { 0x9195, 0x80, BYTE_LEN, 0 },
        { 0x9196, 0x00, BYTE_LEN, 0 },
        { 0x9197, 0x07, BYTE_LEN, 0 },
        { 0x9198, 0x04, BYTE_LEN, 0 },
        { 0x9199, 0x1c, BYTE_LEN, 0 },
        { 0x919A, 0x10, BYTE_LEN, 0 },
        { 0x919B, 0x60, BYTE_LEN, 0 },
        { 0x919C, 0xa0, BYTE_LEN, 0 },
        { 0x919D, 0xc0, BYTE_LEN, 0 },
        { 0x919E, 0x80, BYTE_LEN, 0 },
        { 0x919F, 0x02, BYTE_LEN, 0 },
        { 0x91A0, 0x05, BYTE_LEN, 0 },
        { 0x91A1, 0x0c, BYTE_LEN, 0 },
        { 0x91A2, 0x0c, BYTE_LEN, 0 },
        { 0x91A3, 0x30, BYTE_LEN, 0 },
        { 0x91A4, 0x30, BYTE_LEN, 0 },
        { 0x91A5, 0x60, BYTE_LEN, 0 },
        { 0x91A6, 0xc0, BYTE_LEN, 0 },
        { 0x91A7, 0x80, BYTE_LEN, 0 },
        { 0x91A8, 0x02, BYTE_LEN, 0 },
        { 0x91A9, 0x03, BYTE_LEN, 0 },
        { 0x91AA, 0x0a, BYTE_LEN, 0 },
        { 0x91AB, 0x18, BYTE_LEN, 0 },
        { 0x91AC, 0x20, BYTE_LEN, 0 },
        { 0x91AD, 0x60, BYTE_LEN, 0 },
        { 0x91AE, 0x80, BYTE_LEN, 0 },
        { 0x91AF, 0xc0, BYTE_LEN, 0 },
        { 0x91B0, 0x01, BYTE_LEN, 0 },
        { 0x91B1, 0x02, BYTE_LEN, 0 },
        { 0x91B2, 0x05, BYTE_LEN, 0 },
        { 0x91B3, 0x16, BYTE_LEN, 0 },
        { 0x91B4, 0x14, BYTE_LEN, 0 },
        { 0x91B5, 0x48, BYTE_LEN, 0 },
        { 0x91B6, 0x40, BYTE_LEN, 0 },
        { 0x91B7, 0x00, BYTE_LEN, 0 },
        { 0x91B8, 0x01, BYTE_LEN, 0 },
        { 0x91B9, 0x81, BYTE_LEN, 0 },
        { 0x91BA, 0x04, BYTE_LEN, 0 },
        { 0x91BB, 0x04, BYTE_LEN, 0 },
        { 0x91BC, 0x0a, BYTE_LEN, 0 },
        { 0x91BD, 0x10, BYTE_LEN, 0 },
        { 0x91BE, 0x28, BYTE_LEN, 0 },
        { 0x91BF, 0x50, BYTE_LEN, 0 },
        { 0x91C0, 0x60, BYTE_LEN, 0 },
        { 0x91C1, 0x40, BYTE_LEN, 0 },
        { 0x91C2, 0x81, BYTE_LEN, 0 },
        { 0x91C3, 0x01, BYTE_LEN, 0 },
        { 0x91C4, 0x05, BYTE_LEN, 0 },
        { 0x91C5, 0x0e, BYTE_LEN, 0 },
        { 0x91C6, 0x10, BYTE_LEN, 0 },
        { 0x91C7, 0x40, BYTE_LEN, 0 },
        { 0x91C8, 0x40, BYTE_LEN, 0 },
        { 0x91C9, 0x00, BYTE_LEN, 0 },
        { 0x91CA, 0x01, BYTE_LEN, 0 },
        { 0x91CB, 0x81, BYTE_LEN, 0 },
        { 0x91CC, 0x02, BYTE_LEN, 0 },
        { 0x91CD, 0x04, BYTE_LEN, 0 },
        { 0x91CE, 0x0c, BYTE_LEN, 0 },
        { 0x91CF, 0x14, BYTE_LEN, 0 },
        { 0x91D0, 0x08, BYTE_LEN, 0 },
        { 0x91D1, 0x50, BYTE_LEN, 0 },
        { 0x91D2, 0x20, BYTE_LEN, 0 },
        { 0x91D3, 0x40, BYTE_LEN, 0 },
        { 0x91D4, 0x81, BYTE_LEN, 0 },
        { 0x91D5, 0x01, BYTE_LEN, 0 },
        { 0x91D6, 0x05, BYTE_LEN, 0 },
        { 0x91D7, 0x06, BYTE_LEN, 0 },
        { 0x91D8, 0x14, BYTE_LEN, 0 },
        { 0x91D9, 0x38, BYTE_LEN, 0 },
        { 0x91DA, 0x40, BYTE_LEN, 0 },
        { 0x91DB, 0x00, BYTE_LEN, 0 },
        { 0x91DC, 0x01, BYTE_LEN, 0 },
        { 0x91DD, 0x01, BYTE_LEN, 0 },
        { 0x91DE, 0x04, BYTE_LEN, 0 },
        { 0x91DF, 0x04, BYTE_LEN, 0 },
        { 0x91E0, 0x0a, BYTE_LEN, 0 },
        { 0x91E1, 0x10, BYTE_LEN, 0 },
        { 0x91E2, 0x30, BYTE_LEN, 0 },
        { 0x91E3, 0x50, BYTE_LEN, 0 },
        { 0x91E4, 0x20, BYTE_LEN, 0 },
        { 0x91E5, 0x40, BYTE_LEN, 0 },
        { 0x91E6, 0x81, BYTE_LEN, 0 },
        { 0x91E7, 0x00, BYTE_LEN, 0 },
        
        { 0xA000, 0x16, BYTE_LEN, 0 },
        { 0xA002, 0x7c, BYTE_LEN, 0 },
        { 0xA003, 0xe1, BYTE_LEN, 0 },
        { 0xA004, 0x4d, BYTE_LEN, 0 },
        { 0xA005, 0x63, BYTE_LEN, 0 },
        { 0xA006, 0x9e, BYTE_LEN, 0 },
        { 0xA007, 0x83, BYTE_LEN, 0 },
        { 0xA008, 0x18, BYTE_LEN, 0 },
        { 0xA009, 0xe7, BYTE_LEN, 0 },
        { 0xA00A, 0xdc, BYTE_LEN, 0 },
        { 0xA00B, 0x25, BYTE_LEN, 0 },
        { 0xA00C, 0x37, BYTE_LEN, 0 },
        { 0xA00D, 0x73, BYTE_LEN, 0 },
        { 0xA00E, 0xa9, BYTE_LEN, 0 },
        { 0xA00F, 0x4d, BYTE_LEN, 0 },
        { 0xA010, 0x5e, BYTE_LEN, 0 },
        { 0xA011, 0x7a, BYTE_LEN, 0 },
        { 0xA012, 0xa3, BYTE_LEN, 0 },
        { 0xA013, 0x18, BYTE_LEN, 0 },
        { 0xA014, 0xe7, BYTE_LEN, 0 },
        { 0xA015, 0x54, BYTE_LEN, 0 },
        { 0xA016, 0xc6, BYTE_LEN, 0 },
        { 0xA017, 0x3b, BYTE_LEN, 0 },
        { 0xA018, 0x8c, BYTE_LEN, 0 },
        { 0xA019, 0xa1, BYTE_LEN, 0 },
        { 0xA01A, 0x8e, BYTE_LEN, 0 },
        { 0xA01B, 0x66, BYTE_LEN, 0 },
        { 0xA01C, 0xbc, BYTE_LEN, 0 },
        { 0xA01D, 0x93, BYTE_LEN, 0 },
        { 0xA01E, 0x19, BYTE_LEN, 0 },
        { 0xA01F, 0xee, BYTE_LEN, 0 },
        { 0xA020, 0x10, BYTE_LEN, 0 },
        { 0xA021, 0xa6, BYTE_LEN, 0 },
        { 0xA022, 0x38, BYTE_LEN, 0 },
        { 0xA023, 0x74, BYTE_LEN, 0 },
        { 0xA024, 0x81, BYTE_LEN, 0 },
        { 0xA025, 0xcd, BYTE_LEN, 0 },
        { 0xA026, 0x5b, BYTE_LEN, 0 },
        { 0xA027, 0x52, BYTE_LEN, 0 },
        { 0xA028, 0x43, BYTE_LEN, 0 },
        { 0xA029, 0x97, BYTE_LEN, 0 },
        { 0xA02A, 0xd8, BYTE_LEN, 0 },
        { 0xA02B, 0x18, BYTE_LEN, 0 },
        { 0xA02C, 0xa6, BYTE_LEN, 0 },
        { 0xA02D, 0x38, BYTE_LEN, 0 },
        { 0xA02E, 0x9e, BYTE_LEN, 0 },
        { 0xA02F, 0x29, BYTE_LEN, 0 },
        { 0xA030, 0x0f, BYTE_LEN, 0 },
        { 0xA031, 0x68, BYTE_LEN, 0 },
        { 0xA032, 0xd6, BYTE_LEN, 0 },
        { 0xA033, 0x33, BYTE_LEN, 0 },
        { 0xA034, 0x18, BYTE_LEN, 0 },
        { 0xA035, 0xdf, BYTE_LEN, 0 },
        { 0xA036, 0xe0, BYTE_LEN, 0 },
        { 0xA037, 0xa5, BYTE_LEN, 0 },
        { 0xA038, 0x35, BYTE_LEN, 0 },
        { 0xA039, 0x59, BYTE_LEN, 0 },
        { 0xA03A, 0x29, BYTE_LEN, 0 },
        { 0xA03B, 0x8c, BYTE_LEN, 0 },
        { 0xA03C, 0x52, BYTE_LEN, 0 },
        { 0xA03D, 0xe0, BYTE_LEN, 0 },
        { 0xA03E, 0x52, BYTE_LEN, 0 },
        { 0xA03F, 0x14, BYTE_LEN, 0 },
        { 0xA040, 0xb4, BYTE_LEN, 0 },
        { 0xA041, 0x28, BYTE_LEN, 0 },
        { 0xA042, 0x05, BYTE_LEN, 0 },
        { 0xA043, 0x2e, BYTE_LEN, 0 },
        { 0xA044, 0x5a, BYTE_LEN, 0 },
        { 0xA045, 0x39, BYTE_LEN, 0 },
        { 0xA046, 0x8c, BYTE_LEN, 0 },
        { 0xA047, 0x5e, BYTE_LEN, 0 },
        { 0xA048, 0x66, BYTE_LEN, 0 },
        { 0xA049, 0x23, BYTE_LEN, 0 },
        { 0xA04A, 0x18, BYTE_LEN, 0 },
        { 0xA04B, 0xe1, BYTE_LEN, 0 },
        { 0xA04C, 0x98, BYTE_LEN, 0 },
        { 0xA04D, 0xe5, BYTE_LEN, 0 },
        { 0xA04E, 0x32, BYTE_LEN, 0 },
        { 0xA04F, 0x56, BYTE_LEN, 0 },
        { 0xA050, 0xf9, BYTE_LEN, 0 },
        { 0xA051, 0x8b, BYTE_LEN, 0 },
        { 0xA052, 0x4f, BYTE_LEN, 0 },
        { 0xA053, 0xb6, BYTE_LEN, 0 },
        { 0xA054, 0xd2, BYTE_LEN, 0 },
        { 0xA055, 0x12, BYTE_LEN, 0 },
        { 0xA056, 0xa1, BYTE_LEN, 0 },
        { 0xA057, 0x98, BYTE_LEN, 0 },
        { 0xA058, 0x44, BYTE_LEN, 0 },
        { 0xA059, 0x27, BYTE_LEN, 0 },
        { 0xA05A, 0x2d, BYTE_LEN, 0 },
        { 0xA05B, 0x19, BYTE_LEN, 0 },
        { 0xA05C, 0xca, BYTE_LEN, 0 },
        { 0xA05D, 0x4f, BYTE_LEN, 0 },
        { 0xA05E, 0xb8, BYTE_LEN, 0 },
        { 0xA05F, 0x82, BYTE_LEN, 0 },
        { 0xA060, 0x15, BYTE_LEN, 0 },
        { 0xA061, 0xc1, BYTE_LEN, 0 },
        { 0xA062, 0x9c, BYTE_LEN, 0 },
        { 0xA063, 0x45, BYTE_LEN, 0 },
        { 0xA064, 0x33, BYTE_LEN, 0 },
        { 0xA065, 0x57, BYTE_LEN, 0 },
        { 0xA066, 0xf1, BYTE_LEN, 0 },
        { 0xA067, 0x8b, BYTE_LEN, 0 },
        { 0xA068, 0x51, BYTE_LEN, 0 },
        { 0xA069, 0xca, BYTE_LEN, 0 },
        { 0xA06A, 0x92, BYTE_LEN, 0 },
        { 0xA06B, 0x92, BYTE_LEN, 0 },
        { 0xA06C, 0x9d, BYTE_LEN, 0 },
        { 0xA06D, 0x44, BYTE_LEN, 0 },
        { 0xA06E, 0x44, BYTE_LEN, 0 },
        { 0xA06F, 0x23, BYTE_LEN, 0 },
        { 0xA070, 0x09, BYTE_LEN, 0 },
        { 0xA071, 0x81, BYTE_LEN, 0 },
        { 0xA072, 0x88, BYTE_LEN, 0 },
        { 0xA073, 0x44, BYTE_LEN, 0 },
        { 0xA074, 0x36, BYTE_LEN, 0 },
        { 0xA075, 0x92, BYTE_LEN, 0 },
        { 0xA076, 0x92, BYTE_LEN, 0 },
        { 0xA077, 0x9e, BYTE_LEN, 0 },
        { 0xA078, 0x1c, BYTE_LEN, 0 },
        { 0xA079, 0x25, BYTE_LEN, 0 },
        { 0xA07A, 0x2d, BYTE_LEN, 0 },
        { 0xA07B, 0x55, BYTE_LEN, 0 },
        { 0xA07C, 0x01, BYTE_LEN, 0 },
        { 0xA07D, 0x4c, BYTE_LEN, 0 },
        { 0xA07E, 0x53, BYTE_LEN, 0 },
        { 0xA07F, 0xe4, BYTE_LEN, 0 },
        { 0xA080, 0xf2, BYTE_LEN, 0 },
        { 0xA081, 0x93, BYTE_LEN, 0 },
        { 0xA082, 0xad, BYTE_LEN, 0 },
        { 0xA083, 0x7c, BYTE_LEN, 0 },
        { 0xA084, 0x64, BYTE_LEN, 0 },
        { 0xA085, 0x25, BYTE_LEN, 0 },
        { 0xA086, 0x04, BYTE_LEN, 0 },
        { 0xA087, 0x41, BYTE_LEN, 0 },
        { 0xA088, 0x48, BYTE_LEN, 0 },
        { 0xA089, 0x3f, BYTE_LEN, 0 },
        { 0xA08A, 0xfa, BYTE_LEN, 0 },
        { 0xA08B, 0x61, BYTE_LEN, 0 },
        { 0xA08C, 0x90, BYTE_LEN, 0 },
        { 0xA08D, 0x84, BYTE_LEN, 0 },
        { 0xA08E, 0x80, BYTE_LEN, 0 },
        { 0xA08F, 0xc4, BYTE_LEN, 0 },
        { 0xA090, 0x25, BYTE_LEN, 0 },
        { 0xA091, 0x41, BYTE_LEN, 0 },
        { 0xA092, 0xe9, BYTE_LEN, 0 },
        { 0xA093, 0x0a, BYTE_LEN, 0 },
        { 0xA094, 0x53, BYTE_LEN, 0 },
        { 0xA095, 0xe4, BYTE_LEN, 0 },
        { 0xA096, 0xf2, BYTE_LEN, 0 },
        { 0xA097, 0x94, BYTE_LEN, 0 },
        { 0xA098, 0xb9, BYTE_LEN, 0 },
        { 0xA099, 0x08, BYTE_LEN, 0 },
        { 0xA09A, 0xa5, BYTE_LEN, 0 },
        { 0xA09B, 0x2b, BYTE_LEN, 0 },
        { 0xA09C, 0x22, BYTE_LEN, 0 },
        { 0xA09D, 0x79, BYTE_LEN, 0 },
        { 0xA09E, 0x09, BYTE_LEN, 0 },
        { 0xA09F, 0x42, BYTE_LEN, 0 },
        { 0xA0A0, 0x18, BYTE_LEN, 0 },
        { 0xA0A1, 0x22, BYTE_LEN, 0 },
        { 0xA0A2, 0x10, BYTE_LEN, 0 },
        { 0xA0A3, 0x81, BYTE_LEN, 0 },
        { 0xA0A4, 0x28, BYTE_LEN, 0 },
        { 0xA0A5, 0xa4, BYTE_LEN, 0 },
        { 0xA0A6, 0x21, BYTE_LEN, 0 },
        { 0xA0A7, 0x25, BYTE_LEN, 0 },
        { 0xA0A8, 0x89, BYTE_LEN, 0 },
        { 0xA0A9, 0x49, BYTE_LEN, 0 },
        { 0xA0AA, 0x51, BYTE_LEN, 0 },
        { 0xA0AB, 0xbe, BYTE_LEN, 0 },
        { 0xA0AC, 0xf2, BYTE_LEN, 0 },
        { 0xA0AD, 0x94, BYTE_LEN, 0 },
        { 0xA0AE, 0xb9, BYTE_LEN, 0 },
        { 0xA0AF, 0x74, BYTE_LEN, 0 },
        { 0xA0B0, 0x05, BYTE_LEN, 0 },
        { 0xA0B1, 0x31, BYTE_LEN, 0 },
        { 0xA0B2, 0x4e, BYTE_LEN, 0 },
        { 0xA0B3, 0x71, BYTE_LEN, 0 },
        { 0xA0B4, 0xcb, BYTE_LEN, 0 },
        { 0xA0B5, 0x4c, BYTE_LEN, 0 },
        { 0xA0B6, 0x86, BYTE_LEN, 0 },
        { 0xA0B7, 0xc2, BYTE_LEN, 0 },
        { 0xA0B8, 0x11, BYTE_LEN, 0 },
        { 0xA0B9, 0x92, BYTE_LEN, 0 },
        { 0xA0BA, 0x54, BYTE_LEN, 0 },
        { 0xA0BB, 0x44, BYTE_LEN, 0 },
        { 0xA0BC, 0x23, BYTE_LEN, 0 },
        { 0xA0BD, 0x1e, BYTE_LEN, 0 },
        { 0xA0BE, 0x29, BYTE_LEN, 0 },
        { 0xA0BF, 0xc9, BYTE_LEN, 0 },
        { 0xA0C0, 0x4d, BYTE_LEN, 0 },
        { 0xA0C1, 0x8e, BYTE_LEN, 0 },
        { 0xA0C2, 0x32, BYTE_LEN, 0 },
        { 0xA0C3, 0x95, BYTE_LEN, 0 },
        { 0xA0C4, 0xb8, BYTE_LEN, 0 },
        { 0xA0C5, 0x80, BYTE_LEN, 0 },
        { 0xA0C6, 0x25, BYTE_LEN, 0 },
        { 0xA0C7, 0x31, BYTE_LEN, 0 },
        { 0xA0C8, 0x75, BYTE_LEN, 0 },
        { 0xA0C9, 0x39, BYTE_LEN, 0 },
        { 0xA0CA, 0x4d, BYTE_LEN, 0 },
        { 0xA0CB, 0x59, BYTE_LEN, 0 },
        { 0xA0CC, 0x1c, BYTE_LEN, 0 },
        { 0xA0CD, 0xc3, BYTE_LEN, 0 },
        { 0xA0CE, 0x94, BYTE_LEN, 0 },
        { 0xA0CF, 0xb4, BYTE_LEN, 0 },
        { 0xA0D0, 0xf4, BYTE_LEN, 0 },
        { 0xA0D1, 0x44, BYTE_LEN, 0 },
        { 0xA0D2, 0x2a, BYTE_LEN, 0 },
        { 0xA0D3, 0x37, BYTE_LEN, 0 },
        { 0xA0D4, 0x49, BYTE_LEN, 0 },
        { 0xA0D5, 0x8a, BYTE_LEN, 0 },
        { 0xA0D6, 0x4f, BYTE_LEN, 0 },
        { 0xA0D7, 0xa4, BYTE_LEN, 0 },
        { 0xA0D8, 0xf2, BYTE_LEN, 0 },
        { 0xA0D9, 0x94, BYTE_LEN, 0 },
        { 0xA0DA, 0xb5, BYTE_LEN, 0 },
        { 0xA0DB, 0xa4, BYTE_LEN, 0 },
        { 0xA0DC, 0x65, BYTE_LEN, 0 },
        { 0xA0DD, 0x32, BYTE_LEN, 0 },
        { 0xA0DE, 0x79, BYTE_LEN, 0 },
        { 0xA0DF, 0x51, BYTE_LEN, 0 },
        { 0xA0E0, 0x4d, BYTE_LEN, 0 },
        { 0xA0E1, 0x65, BYTE_LEN, 0 },
        { 0xA0E2, 0xa2, BYTE_LEN, 0 },
        { 0xA0E3, 0xb3, BYTE_LEN, 0 },
        { 0xA0E4, 0x98, BYTE_LEN, 0 },
        { 0xA0E5, 0xe0, BYTE_LEN, 0 },
        { 0xA0E6, 0xb0, BYTE_LEN, 0 },
        { 0xA0E7, 0x05, BYTE_LEN, 0 },
        { 0xA0E8, 0x33, BYTE_LEN, 0 },
        { 0xA0E9, 0x5d, BYTE_LEN, 0 },
        { 0xA0EA, 0x11, BYTE_LEN, 0 },
        { 0xA0EB, 0x8c, BYTE_LEN, 0 },
        { 0xA0EC, 0x56, BYTE_LEN, 0 },
        { 0xA0ED, 0xf6, BYTE_LEN, 0 },
        { 0xA0EE, 0xf2, BYTE_LEN, 0 },
        { 0xA0EF, 0x95, BYTE_LEN, 0 },
        { 0xA0F0, 0xc1, BYTE_LEN, 0 },
        { 0xA0F1, 0xbc, BYTE_LEN, 0 },
        { 0xA0F2, 0x65, BYTE_LEN, 0 },
        { 0xA0F3, 0x33, BYTE_LEN, 0 },
        { 0xA0F4, 0x92, BYTE_LEN, 0 },
        { 0xA0F5, 0x49, BYTE_LEN, 0 },
        { 0xA0F6, 0xce, BYTE_LEN, 0 },
        { 0xA0F7, 0x66, BYTE_LEN, 0 },
        { 0xA0F8, 0xb2, BYTE_LEN, 0 },
        { 0xA0F9, 0xb3, BYTE_LEN, 0 },
        { 0xA0FA, 0x9a, BYTE_LEN, 0 },
        { 0xA0FB, 0xf6, BYTE_LEN, 0 },
        { 0xA0FC, 0xb4, BYTE_LEN, 0 },
        { 0xA0FD, 0xc6, BYTE_LEN, 0 },
        { 0xA0FE, 0x3d, BYTE_LEN, 0 },
        { 0xA0FF, 0x9c, BYTE_LEN, 0 },
        { 0xA100, 0xb9, BYTE_LEN, 0 },
        { 0xA101, 0x8e, BYTE_LEN, 0 },
        { 0xA102, 0x63, BYTE_LEN, 0 },
        { 0xA103, 0x88, BYTE_LEN, 0 },
        { 0xA104, 0xa3, BYTE_LEN, 0 },
        { 0xA105, 0x98, BYTE_LEN, 0 },
        { 0xA106, 0xdf, BYTE_LEN, 0 },
        { 0xA107, 0x38, BYTE_LEN, 0 },
        { 0xA108, 0xe6, BYTE_LEN, 0 },
        { 0xA109, 0x38, BYTE_LEN, 0 },
        { 0xA10A, 0xa0, BYTE_LEN, 0 },
        { 0xA10B, 0xe1, BYTE_LEN, 0 },
        { 0xA10C, 0x4e, BYTE_LEN, 0 },
        { 0xA10D, 0x6e, BYTE_LEN, 0 },
        { 0xA10E, 0xfc, BYTE_LEN, 0 },
        { 0xA10F, 0x73, BYTE_LEN, 0 },
        { 0xA110, 0x1b, BYTE_LEN, 0 },
        { 0xA111, 0xff, BYTE_LEN, 0 },
        { 0xA112, 0x34, BYTE_LEN, 0 },
        { 0xA113, 0x86, BYTE_LEN, 0 },
        { 0xA114, 0x39, BYTE_LEN, 0 },
        { 0xA115, 0x9f, BYTE_LEN, 0 },
        { 0xA116, 0x19, BYTE_LEN, 0 },
        { 0xA117, 0x0f, BYTE_LEN, 0 },
        { 0xA118, 0x68, BYTE_LEN, 0 },
        { 0xA119, 0xbe, BYTE_LEN, 0 },
        { 0xA11A, 0x33, BYTE_LEN, 0 },
        { 0xA11B, 0x19, BYTE_LEN, 0 },
        { 0xA11C, 0xe9, BYTE_LEN, 0 },
        { 0xA11D, 0x48, BYTE_LEN, 0 },
        { 0xA11E, 0xe6, BYTE_LEN, 0 },
        { 0xA11F, 0x39, BYTE_LEN, 0 },
        { 0xA120, 0x94, BYTE_LEN, 0 },
        { 0xA121, 0xa9, BYTE_LEN, 0 },
        { 0xA122, 0x4e, BYTE_LEN, 0 },
        { 0xA123, 0x69, BYTE_LEN, 0 },
        { 0xA124, 0xcc, BYTE_LEN, 0 },
        { 0xA125, 0xe3, BYTE_LEN, 0 },
        { 0xA126, 0x1a, BYTE_LEN, 0 },
        { 0xA127, 0xfa, BYTE_LEN, 0 },
        { 0xA128, 0x74, BYTE_LEN, 0 },
        { 0xA129, 0xe6, BYTE_LEN, 0 },
        { 0xA12A, 0x3b, BYTE_LEN, 0 },
        { 0xA12B, 0x63, BYTE_LEN, 0 },
        { 0xA12C, 0x01, BYTE_LEN, 0 },
        { 0xA12D, 0x8c, BYTE_LEN, 0 },
        { 0xA12E, 0x5d, BYTE_LEN, 0 },
        { 0xA12F, 0x24, BYTE_LEN, 0 },
        { 0xA130, 0x53, BYTE_LEN, 0 },
        { 0xA131, 0x97, BYTE_LEN, 0 },
        { 0xA132, 0xc6, BYTE_LEN, 0 },
        { 0xA133, 0xa0, BYTE_LEN, 0 },
        { 0xA134, 0xe5, BYTE_LEN, 0 },
        { 0xA135, 0x2f, BYTE_LEN, 0 },
        { 0xA136, 0x68, BYTE_LEN, 0 },
        { 0xA137, 0xc9, BYTE_LEN, 0 },
        { 0xA138, 0x4b, BYTE_LEN, 0 },
        { 0xA139, 0x5b, BYTE_LEN, 0 },
        { 0xA13A, 0xfe, BYTE_LEN, 0 },
        { 0xA13B, 0xf2, BYTE_LEN, 0 },
        { 0xA13C, 0x17, BYTE_LEN, 0 },
        { 0xA13D, 0xc9, BYTE_LEN, 0 },
        { 0xA13E, 0x24, BYTE_LEN, 0 },
        { 0xA13F, 0x26, BYTE_LEN, 0 },
        { 0xA140, 0x33, BYTE_LEN, 0 },
        { 0xA141, 0x7e, BYTE_LEN, 0 },
        { 0xA142, 0x79, BYTE_LEN, 0 },
        { 0xA143, 0x4c, BYTE_LEN, 0 },
        { 0xA144, 0x60, BYTE_LEN, 0 },
        { 0xA145, 0x3c, BYTE_LEN, 0 },
        { 0xA146, 0x23, BYTE_LEN, 0 },
        { 0xA147, 0x18, BYTE_LEN, 0 },
        { 0xA148, 0xcf, BYTE_LEN, 0 },
        { 0xA149, 0xc8, BYTE_LEN, 0 },
        { 0xA14A, 0x25, BYTE_LEN, 0 },
        { 0xA14B, 0x31, BYTE_LEN, 0 },
        { 0xA14C, 0x66, BYTE_LEN, 0 },
        { 0xA14D, 0xd1, BYTE_LEN, 0 },
        { 0xA14E, 0x4b, BYTE_LEN, 0 },
        { 0xA14F, 0x59, BYTE_LEN, 0 },
        { 0xA150, 0xe6, BYTE_LEN, 0 },
        { 0xA151, 0xa2, BYTE_LEN, 0 },
        { 0xA152, 0x16, BYTE_LEN, 0 },
        { 0xA153, 0xbd, BYTE_LEN, 0 },
        { 0xA154, 0xec, BYTE_LEN, 0 },
        { 0xA155, 0xa5, BYTE_LEN, 0 },
        { 0xA156, 0x31, BYTE_LEN, 0 },
        { 0xA157, 0x92, BYTE_LEN, 0 },
        { 0xA158, 0x19, BYTE_LEN, 0 },
        { 0xA159, 0x8d, BYTE_LEN, 0 },
        { 0xA15A, 0x64, BYTE_LEN, 0 },
        { 0xA15B, 0x46, BYTE_LEN, 0 },
        { 0xA15C, 0xe3, BYTE_LEN, 0 },
        { 0xA15D, 0x96, BYTE_LEN, 0 },
        { 0xA15E, 0xc2, BYTE_LEN, 0 },
        { 0xA15F, 0x98, BYTE_LEN, 0 },
        { 0xA160, 0x65, BYTE_LEN, 0 },
        { 0xA161, 0x2f, BYTE_LEN, 0 },
        { 0xA162, 0x4c, BYTE_LEN, 0 },
        { 0xA163, 0xe1, BYTE_LEN, 0 },
        { 0xA164, 0x4a, BYTE_LEN, 0 },
        { 0xA165, 0x50, BYTE_LEN, 0 },
        { 0xA166, 0x9a, BYTE_LEN, 0 },
        { 0xA167, 0xf2, BYTE_LEN, 0 },
        { 0xA168, 0x93, BYTE_LEN, 0 },
        { 0xA169, 0xa3, BYTE_LEN, 0 },
        { 0xA16A, 0x10, BYTE_LEN, 0 },
        { 0xA16B, 0xa5, BYTE_LEN, 0 },
        { 0xA16C, 0x29, BYTE_LEN, 0 },
        { 0xA16D, 0x54, BYTE_LEN, 0 },
        { 0xA16E, 0xf9, BYTE_LEN, 0 },
        { 0xA16F, 0x4a, BYTE_LEN, 0 },
        { 0xA170, 0x5c, BYTE_LEN, 0 },
        { 0xA171, 0xfc, BYTE_LEN, 0 },
        { 0xA172, 0x82, BYTE_LEN, 0 },
        { 0xA173, 0x17, BYTE_LEN, 0 },
        { 0xA174, 0xc3, BYTE_LEN, 0 },
        { 0xA175, 0x4c, BYTE_LEN, 0 },
        { 0xA176, 0x25, BYTE_LEN, 0 },
        { 0xA177, 0x2d, BYTE_LEN, 0 },
        { 0xA178, 0x47, BYTE_LEN, 0 },
        { 0xA179, 0xc9, BYTE_LEN, 0 },
        { 0xA17A, 0x0a, BYTE_LEN, 0 },
        { 0xA17B, 0x4d, BYTE_LEN, 0 },
        { 0xA17C, 0x80, BYTE_LEN, 0 },
        { 0xA17D, 0x82, BYTE_LEN, 0 },
        { 0xA17E, 0x92, BYTE_LEN, 0 },
        { 0xA17F, 0x97, BYTE_LEN, 0 },
        { 0xA180, 0x90, BYTE_LEN, 0 },
        { 0xA181, 0x24, BYTE_LEN, 0 },
        { 0xA182, 0x25, BYTE_LEN, 0 },
        { 0xA183, 0x2b, BYTE_LEN, 0 },
        { 0xA184, 0x89, BYTE_LEN, 0 },
        { 0xA185, 0x89, BYTE_LEN, 0 },
        { 0xA186, 0x4e, BYTE_LEN, 0 },
        { 0xA187, 0x84, BYTE_LEN, 0 },
        { 0xA188, 0x22, BYTE_LEN, 0 },
        { 0xA189, 0x95, BYTE_LEN, 0 },
        { 0xA18A, 0xad, BYTE_LEN, 0 },
        { 0xA18B, 0x7c, BYTE_LEN, 0 },
        { 0xA18C, 0x05, BYTE_LEN, 0 },
        { 0xA18D, 0x2d, BYTE_LEN, 0 },
        { 0xA18E, 0x44, BYTE_LEN, 0 },
        { 0xA18F, 0xb1, BYTE_LEN, 0 },
        { 0xA190, 0x0a, BYTE_LEN, 0 },
        { 0xA191, 0x4e, BYTE_LEN, 0 },
        { 0xA192, 0x8e, BYTE_LEN, 0 },
        { 0xA193, 0x22, BYTE_LEN, 0 },
        { 0xA194, 0x92, BYTE_LEN, 0 },
        { 0xA195, 0x95, BYTE_LEN, 0 },
        { 0xA196, 0x38, BYTE_LEN, 0 },
        { 0xA197, 0x64, BYTE_LEN, 0 },
        { 0xA198, 0x22, BYTE_LEN, 0 },
        { 0xA199, 0x0a, BYTE_LEN, 0 },
        { 0xA19A, 0x59, BYTE_LEN, 0 },
        { 0xA19B, 0x88, BYTE_LEN, 0 },
        { 0xA19C, 0x44, BYTE_LEN, 0 },
        { 0xA19D, 0x26, BYTE_LEN, 0 },
        { 0xA19E, 0x92, BYTE_LEN, 0 },
        { 0xA19F, 0x12, BYTE_LEN, 0 },
        { 0xA1A0, 0x96, BYTE_LEN, 0 },
        { 0xA1A1, 0x04, BYTE_LEN, 0 },
        { 0xA1A2, 0x25, BYTE_LEN, 0 },
        { 0xA1A3, 0x29, BYTE_LEN, 0 },
        { 0xA1A4, 0x4c, BYTE_LEN, 0 },
        { 0xA1A5, 0xb1, BYTE_LEN, 0 },
        { 0xA1A6, 0x0a, BYTE_LEN, 0 },
        { 0xA1A7, 0x4f, BYTE_LEN, 0 },
        { 0xA1A8, 0x96, BYTE_LEN, 0 },
        { 0xA1A9, 0x22, BYTE_LEN, 0 },
        { 0xA1AA, 0x93, BYTE_LEN, 0 },
        { 0xA1AB, 0x9f, BYTE_LEN, 0 },
        { 0xA1AC, 0x5c, BYTE_LEN, 0 },
        { 0xA1AD, 0xe4, BYTE_LEN, 0 },
        { 0xA1AE, 0x23, BYTE_LEN, 0 },
        { 0xA1AF, 0x02, BYTE_LEN, 0 },
        { 0xA1B0, 0x31, BYTE_LEN, 0 },
        { 0xA1B1, 0x88, BYTE_LEN, 0 },
        { 0xA1B2, 0x3f, BYTE_LEN, 0 },
        { 0xA1B3, 0xfe, BYTE_LEN, 0 },
        { 0xA1B4, 0x71, BYTE_LEN, 0 },
        { 0xA1B5, 0x10, BYTE_LEN, 0 },
        { 0xA1B6, 0x83, BYTE_LEN, 0 },
        { 0xA1B7, 0x7c, BYTE_LEN, 0 },
        { 0xA1B8, 0x04, BYTE_LEN, 0 },
        { 0xA1B9, 0x24, BYTE_LEN, 0 },
        { 0xA1BA, 0x3a, BYTE_LEN, 0 },
        { 0xA1BB, 0x01, BYTE_LEN, 0 },
        { 0xA1BC, 0x8a, BYTE_LEN, 0 },
        { 0xA1BD, 0x50, BYTE_LEN, 0 },
        { 0xA1BE, 0x96, BYTE_LEN, 0 },
        { 0xA1BF, 0x02, BYTE_LEN, 0 },
        { 0xA1C0, 0x94, BYTE_LEN, 0 },
        { 0xA1C1, 0xa5, BYTE_LEN, 0 },
        { 0xA1C2, 0xd8, BYTE_LEN, 0 },
        { 0xA1C3, 0xe4, BYTE_LEN, 0 },
        { 0xA1C4, 0x27, BYTE_LEN, 0 },
        { 0xA1C5, 0x1b, BYTE_LEN, 0 },
        { 0xA1C6, 0x11, BYTE_LEN, 0 },
        { 0xA1C7, 0x89, BYTE_LEN, 0 },
        { 0xA1C8, 0x41, BYTE_LEN, 0 },
        { 0xA1C9, 0x10, BYTE_LEN, 0 },
        { 0xA1CA, 0x12, BYTE_LEN, 0 },
        { 0xA1CB, 0x10, BYTE_LEN, 0 },
        { 0xA1CC, 0x80, BYTE_LEN, 0 },
        { 0xA1CD, 0x24, BYTE_LEN, 0 },
        { 0xA1CE, 0x04, BYTE_LEN, 0 },
        { 0xA1CF, 0x21, BYTE_LEN, 0 },
        { 0xA1D0, 0x21, BYTE_LEN, 0 },
        { 0xA1D1, 0x19, BYTE_LEN, 0 },
        { 0xA1D2, 0xc9, BYTE_LEN, 0 },
        { 0xA1D3, 0x4e, BYTE_LEN, 0 },
        { 0xA1D4, 0x84, BYTE_LEN, 0 },
        { 0xA1D5, 0x22, BYTE_LEN, 0 },
        { 0xA1D6, 0x14, BYTE_LEN, 0 },
        { 0xA1D7, 0xa6, BYTE_LEN, 0 },
        { 0xA1D8, 0x38, BYTE_LEN, 0 },
        { 0xA1D9, 0x25, BYTE_LEN, 0 },
        { 0xA1DA, 0x2b, BYTE_LEN, 0 },
        { 0xA1DB, 0x41, BYTE_LEN, 0 },
        { 0xA1DC, 0x59, BYTE_LEN, 0 },
        { 0xA1DD, 0x8a, BYTE_LEN, 0 },
        { 0xA1DE, 0x4a, BYTE_LEN, 0 },
        { 0xA1DF, 0x62, BYTE_LEN, 0 },
        { 0xA1E0, 0x62, BYTE_LEN, 0 },
        { 0xA1E1, 0x11, BYTE_LEN, 0 },
        { 0xA1E2, 0x8d, BYTE_LEN, 0 },
        { 0xA1E3, 0x44, BYTE_LEN, 0 },
        { 0xA1E4, 0x44, BYTE_LEN, 0 },
        { 0xA1E5, 0x22, BYTE_LEN, 0 },
        { 0xA1E6, 0x18, BYTE_LEN, 0 },
        { 0xA1E7, 0xd9, BYTE_LEN, 0 },
        { 0xA1E8, 0x08, BYTE_LEN, 0 },
        { 0xA1E9, 0x4b, BYTE_LEN, 0 },
        { 0xA1EA, 0x68, BYTE_LEN, 0 },
        { 0xA1EB, 0x52, BYTE_LEN, 0 },
        { 0xA1EC, 0x14, BYTE_LEN, 0 },
        { 0xA1ED, 0xa8, BYTE_LEN, 0 },
        { 0xA1EE, 0x3c, BYTE_LEN, 0 },
        { 0xA1EF, 0xa5, BYTE_LEN, 0 },
        { 0xA1F0, 0x2b, BYTE_LEN, 0 },
        { 0xA1F1, 0x65, BYTE_LEN, 0 },
        { 0xA1F2, 0x89, BYTE_LEN, 0 },
        { 0xA1F3, 0xcb, BYTE_LEN, 0 },
        { 0xA1F4, 0x55, BYTE_LEN, 0 },
        { 0xA1F5, 0xc2, BYTE_LEN, 0 },
        { 0xA1F6, 0x12, BYTE_LEN, 0 },
        { 0xA1F7, 0x14, BYTE_LEN, 0 },
        { 0xA1F8, 0xa5, BYTE_LEN, 0 },
        { 0xA1F9, 0xcc, BYTE_LEN, 0 },
        { 0xA1FA, 0x64, BYTE_LEN, 0 },
        { 0xA1FB, 0x27, BYTE_LEN, 0 },
        { 0xA1FC, 0x30, BYTE_LEN, 0 },
        { 0xA1FD, 0xa9, BYTE_LEN, 0 },
        { 0xA1FE, 0x49, BYTE_LEN, 0 },
        { 0xA1FF, 0x4d, BYTE_LEN, 0 },
        { 0xA200, 0x7a, BYTE_LEN, 0 },
        { 0xA201, 0x12, BYTE_LEN, 0 },
        { 0xA202, 0x94, BYTE_LEN, 0 },
        { 0xA203, 0xa6, BYTE_LEN, 0 },
        { 0xA204, 0x58, BYTE_LEN, 0 },
        { 0xA205, 0x05, BYTE_LEN, 0 },
        { 0xA206, 0x2d, BYTE_LEN, 0 },
        { 0xA207, 0x61, BYTE_LEN, 0 },
        { 0xA208, 0xb1, BYTE_LEN, 0 },
        { 0xA209, 0x8b, BYTE_LEN, 0 },
        { 0xA20A, 0x60, BYTE_LEN, 0 },
        { 0xA20B, 0x22, BYTE_LEN, 0 },
        { 0xA20C, 0xb3, BYTE_LEN, 0 },
        { 0xA20D, 0x97, BYTE_LEN, 0 },
        { 0xA20E, 0xc4, BYTE_LEN, 0 },
        { 0xA20F, 0x7c, BYTE_LEN, 0 },
        { 0xA210, 0x45, BYTE_LEN, 0 },
        { 0xA211, 0x2d, BYTE_LEN, 0 },
        { 0xA212, 0x51, BYTE_LEN, 0 },
        { 0xA213, 0xf1, BYTE_LEN, 0 },
        { 0xA214, 0x4a, BYTE_LEN, 0 },
        { 0xA215, 0x53, BYTE_LEN, 0 },
        { 0xA216, 0xb2, BYTE_LEN, 0 },
        { 0xA217, 0x02, BYTE_LEN, 0 },
        { 0xA218, 0x15, BYTE_LEN, 0 },
        { 0xA219, 0xaf, BYTE_LEN, 0 },
        { 0xA21A, 0x70, BYTE_LEN, 0 },
        { 0xA21B, 0xe5, BYTE_LEN, 0 },
        { 0xA21C, 0x2d, BYTE_LEN, 0 },
        { 0xA21D, 0x78, BYTE_LEN, 0 },
        { 0xA21E, 0x79, BYTE_LEN, 0 },
        { 0xA21F, 0xcc, BYTE_LEN, 0 },
        { 0xA220, 0x5f, BYTE_LEN, 0 },
        { 0xA221, 0x2e, BYTE_LEN, 0 },
        { 0xA222, 0x73, BYTE_LEN, 0 },
        { 0xA223, 0x99, BYTE_LEN, 0 },
        { 0xA224, 0xd4, BYTE_LEN, 0 },
        { 0xA225, 0x6c, BYTE_LEN, 0 },
        { 0xA226, 0xa6, BYTE_LEN, 0 },
        { 0xA227, 0x35, BYTE_LEN, 0 },
        { 0xA228, 0x8b, BYTE_LEN, 0 },
        { 0xA229, 0xe9, BYTE_LEN, 0 },
        { 0xA22A, 0x4c, BYTE_LEN, 0 },
        { 0xA22B, 0x5f, BYTE_LEN, 0 },
        { 0xA22C, 0x1e, BYTE_LEN, 0 },
        { 0xA22D, 0x83, BYTE_LEN, 0 },
        { 0xA22E, 0x17, BYTE_LEN, 0 },
        { 0xA22F, 0xc5, BYTE_LEN, 0 },
        { 0xA230, 0xf0, BYTE_LEN, 0 },
        { 0xA231, 0x05, BYTE_LEN, 0 },
        { 0xA232, 0x32, BYTE_LEN, 0 },
        { 0xA233, 0x89, BYTE_LEN, 0 },
        { 0xA234, 0x09, BYTE_LEN, 0 },
        { 0xA235, 0x0d, BYTE_LEN, 0 },
        { 0xA236, 0x67, BYTE_LEN, 0 },
        { 0xA237, 0x6a, BYTE_LEN, 0 },
        { 0xA238, 0x73, BYTE_LEN, 0 },
        { 0xA239, 0x19, BYTE_LEN, 0 },
        { 0xA23A, 0xd8, BYTE_LEN, 0 },
        { 0xA23B, 0xec, BYTE_LEN, 0 },
        { 0xA23C, 0x65, BYTE_LEN, 0 },
        { 0xA23D, 0x31, BYTE_LEN, 0 },
        { 0xA23E, 0x8e, BYTE_LEN, 0 },
        { 0xA23F, 0x09, BYTE_LEN, 0 },
        { 0xA240, 0x8d, BYTE_LEN, 0 },
        { 0xA241, 0x63, BYTE_LEN, 0 },
        { 0xA242, 0x42, BYTE_LEN, 0 },
        { 0xA243, 0x23, BYTE_LEN, 0 },
        { 0xA244, 0x98, BYTE_LEN, 0 },
        { 0xA245, 0xca, BYTE_LEN, 0 },
        { 0xA246, 0x00, BYTE_LEN, 0 },
        { 0xA247, 0x66, BYTE_LEN, 0 },
        { 0xA248, 0x32, BYTE_LEN, 0 },
        { 0xA249, 0x82, BYTE_LEN, 0 },
        { 0xA24A, 0xb1, BYTE_LEN, 0 },
        { 0xA24B, 0xcc, BYTE_LEN, 0 },
        { 0xA24C, 0x63, BYTE_LEN, 0 },
        { 0xA24D, 0x4e, BYTE_LEN, 0 },
        { 0xA24E, 0x13, BYTE_LEN, 0 },
        { 0xA24F, 0x19, BYTE_LEN, 0 },
        { 0xA250, 0xd5, BYTE_LEN, 0 },
        { 0xA251, 0xf8, BYTE_LEN, 0 },
        { 0xA252, 0xc5, BYTE_LEN, 0 },
        { 0xA253, 0x32, BYTE_LEN, 0 },
        
        { 0xA254, 0x91, BYTE_LEN, 0 },
        { 0xA255, 0x21, BYTE_LEN, 0 },
        { 0xA256, 0x0d, BYTE_LEN, 0 },
        { 0xA257, 0x68, BYTE_LEN, 0 },
        { 0xA258, 0x20, BYTE_LEN, 0 },
        { 0xA259, 0xd3, BYTE_LEN, 0 },
        { 0xA25A, 0x98, BYTE_LEN, 0 },
        { 0xA25B, 0xc9, BYTE_LEN, 0 },
        { 0xA25C, 0x90, BYTE_LEN, 0 },
        { 0xA25D, 0x26, BYTE_LEN, 0 },
        { 0xA25E, 0x36, BYTE_LEN, 0 },
        { 0xA25F, 0xa6, BYTE_LEN, 0 },
        { 0xA260, 0x79, BYTE_LEN, 0 },
        { 0xA261, 0xcd, BYTE_LEN, 0 },
        { 0xA262, 0x6b, BYTE_LEN, 0 },
        { 0xA263, 0x36, BYTE_LEN, 0 },
        { 0xA264, 0x93, BYTE_LEN, 0 },
        { 0xA265, 0x18, BYTE_LEN, 0 },
        { 0xA266, 0xc2, BYTE_LEN, 0 },
        { 0xA267, 0x2c, BYTE_LEN, 0 },
        { 0xA268, 0xa6, BYTE_LEN, 0 },
        { 0xA269, 0x33, BYTE_LEN, 0 },
        { 0xA26A, 0xb8, BYTE_LEN, 0 },
        { 0xA26B, 0xe1, BYTE_LEN, 0 },
        { 0xA26C, 0x4d, BYTE_LEN, 0 },
        { 0xA26D, 0x65, BYTE_LEN, 0 },
        { 0xA26E, 0x0e, BYTE_LEN, 0 },
        { 0xA26F, 0x53, BYTE_LEN, 0 },
        { 0xA270, 0x16, BYTE_LEN, 0 },
        { 0xA271, 0xaa, BYTE_LEN, 0 },
        { 0xA272, 0x38, BYTE_LEN, 0 },
        { 0xA273, 0xa5, BYTE_LEN, 0 },
        { 0xA274, 0x2a, BYTE_LEN, 0 },
        { 0xA275, 0x68, BYTE_LEN, 0 },
        { 0xA276, 0x69, BYTE_LEN, 0 },
        { 0xA277, 0x8c, BYTE_LEN, 0 },
        { 0xA278, 0x66, BYTE_LEN, 0 },
        { 0xA279, 0xe8, BYTE_LEN, 0 },
        { 0xA27A, 0x12, BYTE_LEN, 0 },
        { 0xA27B, 0x16, BYTE_LEN, 0 },
        { 0xA27C, 0xa2, BYTE_LEN, 0 },
        { 0xA27D, 0xc4, BYTE_LEN, 0 },
        { 0xA27E, 0x64, BYTE_LEN, 0 },
        { 0xA27F, 0x25, BYTE_LEN, 0 },
        { 0xA280, 0x33, BYTE_LEN, 0 },
        { 0xA281, 0x31, BYTE_LEN, 0 },
        { 0xA282, 0x4a, BYTE_LEN, 0 },
        { 0xA283, 0x59, BYTE_LEN, 0 },
        { 0xA284, 0xf0, BYTE_LEN, 0 },
        { 0xA285, 0x02, BYTE_LEN, 0 },
        { 0xA286, 0x96, BYTE_LEN, 0 },
        { 0xA287, 0xa6, BYTE_LEN, 0 },
        { 0xA288, 0xb4, BYTE_LEN, 0 },
        { 0xA289, 0x44, BYTE_LEN, 0 },
        { 0xA28A, 0x22, BYTE_LEN, 0 },
        { 0xA28B, 0x0a, BYTE_LEN, 0 },
        { 0xA28C, 0x99, BYTE_LEN, 0 },
        { 0xA28D, 0xc8, BYTE_LEN, 0 },
        { 0xA28E, 0x4b, BYTE_LEN, 0 },
        { 0xA28F, 0xa4, BYTE_LEN, 0 },
        { 0xA290, 0x42, BYTE_LEN, 0 },
        { 0xA291, 0x16, BYTE_LEN, 0 },
        { 0xA292, 0xab, BYTE_LEN, 0 },
        { 0xA293, 0x18, BYTE_LEN, 0 },
        { 0xA294, 0x25, BYTE_LEN, 0 },
        { 0xA295, 0x24, BYTE_LEN, 0 },
        { 0xA296, 0x06, BYTE_LEN, 0 },
        { 0xA297, 0xe9, BYTE_LEN, 0 },
        { 0xA298, 0xc7, BYTE_LEN, 0 },
        { 0xA299, 0x41, BYTE_LEN, 0 },
        { 0xA29A, 0x48, BYTE_LEN, 0 },
        { 0xA29B, 0xa2, BYTE_LEN, 0 },
        { 0xA29C, 0x94, BYTE_LEN, 0 },
        { 0xA29D, 0xac, BYTE_LEN, 0 },
        { 0xA29E, 0x60, BYTE_LEN, 0 },
        { 0xA29F, 0x05, BYTE_LEN, 0 },
        { 0xA2A0, 0x29, BYTE_LEN, 0 },
        { 0xA2A1, 0x24, BYTE_LEN, 0 },
        { 0xA2A2, 0x49, BYTE_LEN, 0 },
        { 0xA2A3, 0x88, BYTE_LEN, 0 },
        { 0xA2A4, 0x40, BYTE_LEN, 0 },
        { 0xA2A5, 0x16, BYTE_LEN, 0 },
        { 0xA2A6, 0x82, BYTE_LEN, 0 },
        { 0xA2A7, 0x12, BYTE_LEN, 0 },
        { 0xA2A8, 0xa6, BYTE_LEN, 0 },
        { 0xA2A9, 0x6c, BYTE_LEN, 0 },
        { 0xA2AA, 0x25, BYTE_LEN, 0 },
        { 0xA2AB, 0x2d, BYTE_LEN, 0 },
        { 0xA2AC, 0x55, BYTE_LEN, 0 },
        { 0xA2AD, 0xa9, BYTE_LEN, 0 },
        { 0xA2AE, 0x09, BYTE_LEN, 0 },
        { 0xA2AF, 0x47, BYTE_LEN, 0 },
        { 0xA2B0, 0x28, BYTE_LEN, 0 },
        { 0xA2B1, 0xd2, BYTE_LEN, 0 },
        { 0xA2B2, 0x91, BYTE_LEN, 0 },
        { 0xA2B3, 0x9c, BYTE_LEN, 0 },
        { 0xA2B4, 0x68, BYTE_LEN, 0 },
        { 0xA2B5, 0x85, BYTE_LEN, 0 },
        { 0xA2B6, 0x2d, BYTE_LEN, 0 },
        { 0xA2B7, 0x83, BYTE_LEN, 0 },
        { 0xA2B8, 0x79, BYTE_LEN, 0 },
        { 0xA2B9, 0x8b, BYTE_LEN, 0 },
        { 0xA2BA, 0x54, BYTE_LEN, 0 },
        { 0xA2BB, 0x82, BYTE_LEN, 0 },
        { 0xA2BC, 0xa2, BYTE_LEN, 0 },
        { 0xA2BD, 0x13, BYTE_LEN, 0 },
        { 0xA2BE, 0xa1, BYTE_LEN, 0 },
        { 0xA2BF, 0x58, BYTE_LEN, 0 },
        { 0xA2C0, 0xa5, BYTE_LEN, 0 },
        { 0xA2C1, 0x2e, BYTE_LEN, 0 },
        { 0xA2C2, 0x88, BYTE_LEN, 0 },
        { 0xA2C3, 0x41, BYTE_LEN, 0 },
        { 0xA2C4, 0xcd, BYTE_LEN, 0 },
        { 0xA2C5, 0x66, BYTE_LEN, 0 },
        { 0xA2C6, 0xf0, BYTE_LEN, 0 },
        { 0xA2C7, 0x62, BYTE_LEN, 0 },
        { 0xA2C8, 0x16, BYTE_LEN, 0 },
        { 0xA2C9, 0xb1, BYTE_LEN, 0 },
        { 0xA2CA, 0xa0, BYTE_LEN, 0 },
        { 0xA2CB, 0x85, BYTE_LEN, 0 },
        { 0xA2CC, 0x2f, BYTE_LEN, 0 },
        { 0xA2CD, 0xa4, BYTE_LEN, 0 },
        { 0xA2CE, 0x81, BYTE_LEN, 0 },
        { 0xA2CF, 0x4d, BYTE_LEN, 0 },
        { 0xA2D0, 0x70, BYTE_LEN, 0 },
        { 0xA2D1, 0x88, BYTE_LEN, 0 },
        { 0xA2D2, 0xf3, BYTE_LEN, 0 },
        { 0xA2D3, 0x1a, BYTE_LEN, 0 },
        { 0xA2D4, 0xcf, BYTE_LEN, 0 },
        { 0xA2D5, 0x6c, BYTE_LEN, 0 },
        { 0xA2D6, 0x26, BYTE_LEN, 0 },
        { 0xA2D7, 0x34, BYTE_LEN, 0 },
        { 0xA2D8, 0xb4, BYTE_LEN, 0 },
        { 0xA2D9, 0x89, BYTE_LEN, 0 },
        { 0xA2DA, 0xce, BYTE_LEN, 0 },
        { 0xA2DB, 0x73, BYTE_LEN, 0 },
        { 0xA2DC, 0x42, BYTE_LEN, 0 },
        { 0xA2DD, 0x63, BYTE_LEN, 0 },
        { 0xA2DE, 0x9b, BYTE_LEN, 0 },
        { 0xA2DF, 0xda, BYTE_LEN, 0 },
        { 0xA2E0, 0xa4, BYTE_LEN, 0 },
        { 0xA2E1, 0xe6, BYTE_LEN, 0 },
        { 0xA2E2, 0x34, BYTE_LEN, 0 },
        { 0xA2E3, 0xab, BYTE_LEN, 0 },
        { 0xA2E4, 0xd9, BYTE_LEN, 0 },
        { 0xA2E5, 0x4d, BYTE_LEN, 0 },
        { 0xA2E6, 0x71, BYTE_LEN, 0 },
        { 0xA2E7, 0x64, BYTE_LEN, 0 },
        { 0xA2E8, 0x03, BYTE_LEN, 0 },
        { 0xA2E9, 0x13, BYTE_LEN, 0 },
        { 0xA2EA, 0xbc, BYTE_LEN, 0 },
        { 0xA2EB, 0x44, BYTE_LEN, 0 },
        { 0xA2EC, 0x14, BYTE_LEN, 0 },
        { 0xA2ED, 0xa6, BYTE_LEN, 0 },
        
        { 0xA2EE, 0xc6, BYTE_LEN, 0 },
        { 0xA2EF, 0xc9, BYTE_LEN, 0 },
        { 0xA2F0, 0x4e, BYTE_LEN, 0 },
        { 0xA2F1, 0x75, BYTE_LEN, 0 },
        { 0xA2F2, 0x80, BYTE_LEN, 0 },
        { 0xA2F3, 0xc3, BYTE_LEN, 0 },
        { 0xA2F4, 0x9b, BYTE_LEN, 0 },
        { 0xA2F5, 0xe1, BYTE_LEN, 0 },
        { 0xA2F6, 0x60, BYTE_LEN, 0 },
        { 0xA2F7, 0xe7, BYTE_LEN, 0 },
        { 0xA2F8, 0x3c, BYTE_LEN, 0 },
        { 0xA2F9, 0xde, BYTE_LEN, 0 },
        { 0xA2FA, 0x31, BYTE_LEN, 0 },
        { 0xA2FB, 0x0f, BYTE_LEN, 0 },
        { 0xA2FC, 0x79, BYTE_LEN, 0 },
        { 0xA2FD, 0x96, BYTE_LEN, 0 },
        { 0xA2FE, 0x43, BYTE_LEN, 0 },
        { 0xA2FF, 0x1b, BYTE_LEN, 0 },
        { 0xA300, 0xd7, BYTE_LEN, 0 },
        { 0xA301, 0xd8, BYTE_LEN, 0 },
        { 0xA302, 0xa6, BYTE_LEN, 0 },
        { 0xA303, 0x39, BYTE_LEN, 0 },
        { 0xA304, 0xee, BYTE_LEN, 0 },
        { 0xA305, 0x99, BYTE_LEN, 0 },
        { 0xA306, 0x4f, BYTE_LEN, 0 },
        { 0xA307, 0x71, BYTE_LEN, 0 },
        { 0xA308, 0x64, BYTE_LEN, 0 },
        { 0xA309, 0x83, BYTE_LEN, 0 },
        { 0xA30A, 0x98, BYTE_LEN, 0 },
        { 0xA30B, 0xb8, BYTE_LEN, 0 },
        { 0xA30C, 0xa8, BYTE_LEN, 0 },
        { 0xA30D, 0x65, BYTE_LEN, 0 },
        { 0xA30E, 0x2e, BYTE_LEN, 0 },
        { 0xA30F, 0x8a, BYTE_LEN, 0 },
        { 0xA310, 0xc1, BYTE_LEN, 0 },
        { 0xA311, 0x4d, BYTE_LEN, 0 },
        { 0xA312, 0x72, BYTE_LEN, 0 },
        { 0xA313, 0x38, BYTE_LEN, 0 },
        { 0xA314, 0x13, BYTE_LEN, 0 },
        { 0xA315, 0x18, BYTE_LEN, 0 },
        { 0xA316, 0xae, BYTE_LEN, 0 },
        { 0xA317, 0x04, BYTE_LEN, 0 },
        { 0xA318, 0x25, BYTE_LEN, 0 },
        { 0xA319, 0x27, BYTE_LEN, 0 },
        { 0xA31A, 0x44, BYTE_LEN, 0 },
        { 0xA31B, 0xf1, BYTE_LEN, 0 },
        { 0xA31C, 0x8a, BYTE_LEN, 0 },
        { 0xA31D, 0x61, BYTE_LEN, 0 },
        { 0xA31E, 0x3e, BYTE_LEN, 0 },
        { 0xA31F, 0x23, BYTE_LEN, 0 },
        { 0xA320, 0x98, BYTE_LEN, 0 },
        { 0xA321, 0xb3, BYTE_LEN, 0 },
        { 0xA322, 0xec, BYTE_LEN, 0 },
        { 0xA323, 0x24, BYTE_LEN, 0 },
        { 0xA324, 0x23, BYTE_LEN, 0 },
        { 0xA325, 0x0f, BYTE_LEN, 0 },
        { 0xA326, 0xd1, BYTE_LEN, 0 },
        { 0xA327, 0x48, BYTE_LEN, 0 },
        { 0xA328, 0x4f, BYTE_LEN, 0 },
        { 0xA329, 0xd6, BYTE_LEN, 0 },
        { 0xA32A, 0x42, BYTE_LEN, 0 },
        { 0xA32B, 0x18, BYTE_LEN, 0 },
        { 0xA32C, 0xbb, BYTE_LEN, 0 },
        { 0xA32D, 0x74, BYTE_LEN, 0 },
        { 0xA32E, 0x85, BYTE_LEN, 0 },
        { 0xA32F, 0x25, BYTE_LEN, 0 },
        { 0xA330, 0x08, BYTE_LEN, 0 },
        { 0xA331, 0xe9, BYTE_LEN, 0 },
        { 0xA332, 0x07, BYTE_LEN, 0 },
        { 0xA333, 0x42, BYTE_LEN, 0 },
        { 0xA334, 0x5a, BYTE_LEN, 0 },
        { 0xA335, 0xf2, BYTE_LEN, 0 },
        { 0xA336, 0x95, BYTE_LEN, 0 },
        { 0xA337, 0xba, BYTE_LEN, 0 },
        { 0xA338, 0xe4, BYTE_LEN, 0 },
        { 0xA339, 0x25, BYTE_LEN, 0 },
        { 0xA33A, 0x2c, BYTE_LEN, 0 },
        { 0xA33B, 0x31, BYTE_LEN, 0 },
        { 0xA33C, 0x61, BYTE_LEN, 0 },
        { 0xA33D, 0x88, BYTE_LEN, 0 },
        { 0xA33E, 0x40, BYTE_LEN, 0 },
        { 0xA33F, 0x18, BYTE_LEN, 0 },
        { 0xA340, 0x02, BYTE_LEN, 0 },
        { 0xA341, 0x13, BYTE_LEN, 0 },
        { 0xA342, 0xb0, BYTE_LEN, 0 },
        { 0xA343, 0xd8, BYTE_LEN, 0 },
        { 0xA344, 0xc5, BYTE_LEN, 0 },
        { 0xA345, 0x31, BYTE_LEN, 0 },
        { 0xA346, 0x73, BYTE_LEN, 0 },
        { 0xA347, 0x31, BYTE_LEN, 0 },
        { 0xA348, 0x0a, BYTE_LEN, 0 },
        { 0xA349, 0x49, BYTE_LEN, 0 },
        { 0xA34A, 0x32, BYTE_LEN, 0 },
        { 0xA34B, 0x42, BYTE_LEN, 0 },
        { 0xA34C, 0x92, BYTE_LEN, 0 },
        { 0xA34D, 0xa3, BYTE_LEN, 0 },
        { 0xA34E, 0xc8, BYTE_LEN, 0 },
        { 0xA34F, 0x65, BYTE_LEN, 0 },
        { 0xA350, 0x31, BYTE_LEN, 0 },
        { 0xA351, 0xaa, BYTE_LEN, 0 },
        { 0xA352, 0x81, BYTE_LEN, 0 },
        { 0xA353, 0x8c, BYTE_LEN, 0 },
        { 0xA354, 0x5a, BYTE_LEN, 0 },
        { 0xA355, 0xa0, BYTE_LEN, 0 },
        { 0xA356, 0x82, BYTE_LEN, 0 },
        { 0xA357, 0x94, BYTE_LEN, 0 },
        { 0xA358, 0xa8, BYTE_LEN, 0 },
        { 0xA359, 0xac, BYTE_LEN, 0 },
        { 0xA35A, 0x65, BYTE_LEN, 0 },
        { 0xA35B, 0x32, BYTE_LEN, 0 },
        { 0xA35C, 0xac, BYTE_LEN, 0 },
        { 0xA35D, 0x91, BYTE_LEN, 0 },
        { 0xA35E, 0x8e, BYTE_LEN, 0 },
        { 0xA35F, 0x70, BYTE_LEN, 0 },
        { 0xA360, 0x2e, BYTE_LEN, 0 },
        { 0xA361, 0x13, BYTE_LEN, 0 },
        { 0xA362, 0x18, BYTE_LEN, 0 },
        { 0xA363, 0xbd, BYTE_LEN, 0 },
        { 0xA364, 0x0c, BYTE_LEN, 0 },
        { 0xA365, 0x66, BYTE_LEN, 0 },
        { 0xA366, 0x33, BYTE_LEN, 0 },
        { 0xA367, 0xca, BYTE_LEN, 0 },
        { 0xA368, 0xd1, BYTE_LEN, 0 },
        { 0xA369, 0xce, BYTE_LEN, 0 },
        { 0xA36A, 0x7b, BYTE_LEN, 0 },
        { 0xA36B, 0xe0, BYTE_LEN, 0 },
        { 0xA36C, 0x83, BYTE_LEN, 0 },
        { 0xA36D, 0x1d, BYTE_LEN, 0 },
        { 0xA36E, 0xe2, BYTE_LEN, 0 },
        { 0xA36F, 0xf8, BYTE_LEN, 0 },
        { 0xA370, 0xe6, BYTE_LEN, 0 },
        { 0xA371, 0x38, BYTE_LEN, 0 },
        { 0xA372, 0xdd, BYTE_LEN, 0 },
        { 0xA373, 0xf1, BYTE_LEN, 0 },
        { 0xA374, 0x4f, BYTE_LEN, 0 },
        { 0xA375, 0x7f, BYTE_LEN, 0 },
        { 0xA376, 0x96, BYTE_LEN, 0 },
        { 0xA377, 0x33, BYTE_LEN, 0 },
        { 0xA378, 0x1e, BYTE_LEN, 0 },
        { 0xA379, 0xf0, BYTE_LEN, 0 },
        { 0xA37A, 0x44, BYTE_LEN, 0 },
        { 0xA37B, 0xe7, BYTE_LEN, 0 },
        { 0xA37C, 0x39, BYTE_LEN, 0 },
        { 0xA37D, 0xd4, BYTE_LEN, 0 },
        { 0xA37E, 0x39, BYTE_LEN, 0 },
        { 0xA37F, 0x4f, BYTE_LEN, 0 },
        { 0xA380, 0x7c, BYTE_LEN, 0 },
        { 0xA381, 0xbc, BYTE_LEN, 0 },
        { 0xA382, 0xb3, BYTE_LEN, 0 },
        { 0xA383, 0x17, BYTE_LEN, 0 },
        { 0xA384, 0xc5, BYTE_LEN, 0 },
        { 0xA385, 0x1c, BYTE_LEN, 0 },
        { 0xA386, 0x06, BYTE_LEN, 0 },
        { 0xA387, 0x2f, BYTE_LEN, 0 },
        { 0xA388, 0x7b, BYTE_LEN, 0 },
        { 0xA389, 0x51, BYTE_LEN, 0 },
        { 0xA38A, 0xcc, BYTE_LEN, 0 },
        { 0xA38B, 0x61, BYTE_LEN, 0 },
        { 0xA38C, 0xf0, BYTE_LEN, 0 },
        { 0xA38D, 0x72, BYTE_LEN, 0 },
        { 0xA38E, 0x17, BYTE_LEN, 0 },
        { 0xA38F, 0xbe, BYTE_LEN, 0 },
        { 0xA390, 0x48, BYTE_LEN, 0 },
        { 0xA391, 0x46, BYTE_LEN, 0 },
        { 0xA392, 0x34, BYTE_LEN, 0 },
        { 0xA393, 0x9c, BYTE_LEN, 0 },
        { 0xA394, 0xa9, BYTE_LEN, 0 },
        { 0xA395, 0xcc, BYTE_LEN, 0 },
        { 0xA396, 0x64, BYTE_LEN, 0 },
        { 0xA397, 0x04, BYTE_LEN, 0 },
        { 0xA398, 0x23, BYTE_LEN, 0 },
        { 0xA399, 0x17, BYTE_LEN, 0 },
        { 0xA39A, 0xb8, BYTE_LEN, 0 },
        { 0xA39B, 0xd4, BYTE_LEN, 0 },
        { 0xA39C, 0x45, BYTE_LEN, 0 },
        { 0xA39D, 0x31, BYTE_LEN, 0 },
        { 0xA39E, 0xa6, BYTE_LEN, 0 },
        { 0xA39F, 0x49, BYTE_LEN, 0 },
        { 0xA3A0, 0xcd, BYTE_LEN, 0 },
        { 0xA3A1, 0x5f, BYTE_LEN, 0 },
        { 0xA3A2, 0xea, BYTE_LEN, 0 },
        { 0xA3A3, 0x72, BYTE_LEN, 0 },
        { 0xA3A4, 0x95, BYTE_LEN, 0 },
        { 0xA3A5, 0xa4, BYTE_LEN, 0 },
        { 0xA3A6, 0x18, BYTE_LEN, 0 },
        { 0xA3A7, 0x65, BYTE_LEN, 0 },
        { 0xA3A8, 0x29, BYTE_LEN, 0 },
        { 0xA3A9, 0x5d, BYTE_LEN, 0 },
        { 0xA3AA, 0xf1, BYTE_LEN, 0 },
        { 0xA3AB, 0xcb, BYTE_LEN, 0 },
        { 0xA3AC, 0x61, BYTE_LEN, 0 },
        { 0xA3AD, 0xbe, BYTE_LEN, 0 },
        { 0xA3AE, 0x12, BYTE_LEN, 0 },
        { 0xA3AF, 0x15, BYTE_LEN, 0 },
        { 0xA3B0, 0x9e, BYTE_LEN, 0 },
        { 0xA3B1, 0xb4, BYTE_LEN, 0 },
        { 0xA3B2, 0x04, BYTE_LEN, 0 },
        { 0xA3B3, 0x25, BYTE_LEN, 0 },
        { 0xA3B4, 0x2f, BYTE_LEN, 0 },
        { 0xA3B5, 0x01, BYTE_LEN, 0 },
        { 0xA3B6, 0x0a, BYTE_LEN, 0 },
        { 0xA3B7, 0x57, BYTE_LEN, 0 },
        { 0xA3B8, 0xd6, BYTE_LEN, 0 },
        { 0xA3B9, 0xf2, BYTE_LEN, 0 },
        { 0xA3BA, 0x14, BYTE_LEN, 0 },
        { 0xA3BB, 0xa0, BYTE_LEN, 0 },
        { 0xA3BC, 0xa0, BYTE_LEN, 0 },
        { 0xA3BD, 0x44, BYTE_LEN, 0 },
        { 0xA3BE, 0x22, BYTE_LEN, 0 },
        { 0xA3BF, 0x0c, BYTE_LEN, 0 },
        { 0xA3C0, 0xa9, BYTE_LEN, 0 },
        { 0xA3C1, 0x48, BYTE_LEN, 0 },
        { 0xA3C2, 0x4b, BYTE_LEN, 0 },
        { 0xA3C3, 0x8e, BYTE_LEN, 0 },
        { 0xA3C4, 0x32, BYTE_LEN, 0 },
        { 0xA3C5, 0x95, BYTE_LEN, 0 },
        { 0xA3C6, 0xa3, BYTE_LEN, 0 },
        { 0xA3C7, 0xec, BYTE_LEN, 0 },
        { 0xA3C8, 0x84, BYTE_LEN, 0 },
        { 0xA3C9, 0x23, BYTE_LEN, 0 },
        { 0xA3CA, 0x04, BYTE_LEN, 0 },
        { 0xA3CB, 0xf9, BYTE_LEN, 0 },
        { 0xA3CC, 0xc7, BYTE_LEN, 0 },
        { 0xA3CD, 0x41, BYTE_LEN, 0 },
        { 0xA3CE, 0x42, BYTE_LEN, 0 },
        { 0xA3CF, 0xf2, BYTE_LEN, 0 },
        { 0xA3D0, 0x93, BYTE_LEN, 0 },
        { 0xA3D1, 0xa3, BYTE_LEN, 0 },
        { 0xA3D2, 0x34, BYTE_LEN, 0 },
        { 0xA3D3, 0x25, BYTE_LEN, 0 },
        { 0xA3D4, 0x28, BYTE_LEN, 0 },
        { 0xA3D5, 0x22, BYTE_LEN, 0 },
        { 0xA3D6, 0x49, BYTE_LEN, 0 },
        { 0xA3D7, 0x08, BYTE_LEN, 0 },
        { 0xA3D8, 0x40, BYTE_LEN, 0 },
        { 0xA3D9, 0x0e, BYTE_LEN, 0 },
        { 0xA3DA, 0x22, BYTE_LEN, 0 },
        { 0xA3DB, 0x92, BYTE_LEN, 0 },
        { 0xA3DC, 0x9f, BYTE_LEN, 0 },
        { 0xA3DD, 0x1c, BYTE_LEN, 0 },
        { 0xA3DE, 0x45, BYTE_LEN, 0 },
        { 0xA3DF, 0x2b, BYTE_LEN, 0 },
        { 0xA3E0, 0x4c, BYTE_LEN, 0 },
        { 0xA3E1, 0x89, BYTE_LEN, 0 },
        { 0xA3E2, 0x09, BYTE_LEN, 0 },
        { 0xA3E3, 0x46, BYTE_LEN, 0 },
        { 0xA3E4, 0x22, BYTE_LEN, 0 },
        { 0xA3E5, 0x72, BYTE_LEN, 0 },
        { 0xA3E6, 0x11, BYTE_LEN, 0 },
        { 0xA3E7, 0x96, BYTE_LEN, 0 },
        { 0xA3E8, 0x20, BYTE_LEN, 0 },
        { 0xA3E9, 0xa5, BYTE_LEN, 0 },
        { 0xA3EA, 0x2a, BYTE_LEN, 0 },
        { 0xA3EB, 0x70, BYTE_LEN, 0 },
        { 0xA3EC, 0xf9, BYTE_LEN, 0 },
        { 0xA3ED, 0x8a, BYTE_LEN, 0 },
        { 0xA3EE, 0x51, BYTE_LEN, 0 },
        { 0xA3EF, 0x66, BYTE_LEN, 0 },
        { 0xA3F0, 0x02, BYTE_LEN, 0 },
        { 0xA3F1, 0x13, BYTE_LEN, 0 },
        { 0xA3F2, 0x9a, BYTE_LEN, 0 },
        { 0xA3F3, 0x04, BYTE_LEN, 0 },
        { 0xA3F4, 0x45, BYTE_LEN, 0 },
        { 0xA3F5, 0x2b, BYTE_LEN, 0 },
        { 0xA3F6, 0x67, BYTE_LEN, 0 },
        { 0xA3F7, 0x59, BYTE_LEN, 0 },
        { 0xA3F8, 0x0c, BYTE_LEN, 0 },
        { 0xA3F9, 0x60, BYTE_LEN, 0 },
        { 0xA3FA, 0xc4, BYTE_LEN, 0 },
        { 0xA3FB, 0x12, BYTE_LEN, 0 },
        { 0xA3FC, 0x95, BYTE_LEN, 0 },
        { 0xA3FD, 0xa6, BYTE_LEN, 0 },
        { 0xA3FE, 0x40, BYTE_LEN, 0 },
        { 0xA3FF, 0xa5, BYTE_LEN, 0 },
        { 0xA400, 0x2b, BYTE_LEN, 0 },
        { 0xA401, 0x7e, BYTE_LEN, 0 },
        { 0xA402, 0x39, BYTE_LEN, 0 },
        { 0xA403, 0xcc, BYTE_LEN, 0 },
        { 0xA404, 0x67, BYTE_LEN, 0 },
        { 0xA405, 0x3e, BYTE_LEN, 0 },
        { 0xA406, 0xc3, BYTE_LEN, 0 },
        { 0xA407, 0x98, BYTE_LEN, 0 },
        { 0xA408, 0xbd, BYTE_LEN, 0 },
        { 0xA409, 0xdc, BYTE_LEN, 0 },
        { 0xA40A, 0x85, BYTE_LEN, 0 },
        { 0xA40B, 0x2f, BYTE_LEN, 0 },
        { 0xA40C, 0x8d, BYTE_LEN, 0 },
        { 0xA40D, 0x29, BYTE_LEN, 0 },
        { 0xA40E, 0x0d, BYTE_LEN, 0 },
        { 0xA40F, 0x69, BYTE_LEN, 0 },
        { 0xA410, 0x0e, BYTE_LEN, 0 },
        { 0xA411, 0x73, BYTE_LEN, 0 },
        { 0xA412, 0x19, BYTE_LEN, 0 },
        { 0xA413, 0xc9, BYTE_LEN, 0 },
        { 0xA414, 0x0c, BYTE_LEN, 0 },
        { 0xA415, 0x06, BYTE_LEN, 0 },
        { 0xA416, 0x30, BYTE_LEN, 0 },
        { 0xA417, 0x83, BYTE_LEN, 0 },
        { 0xA418, 0x91, BYTE_LEN, 0 },
        { 0xA419, 0x8c, BYTE_LEN, 0 },
        { 0xA41A, 0x67, BYTE_LEN, 0 },
        { 0xA41B, 0x1a, BYTE_LEN, 0 },
        { 0xA41C, 0x03, BYTE_LEN, 0 },
        { 0xA41D, 0x00, BYTE_LEN, 0 },
        { 0xA41E, 0x00, BYTE_LEN, 0 },
        { 0xA41F, 0x00, BYTE_LEN, 0 },
        { 0xA420, 0x00, BYTE_LEN, 0 },
        { 0xA421, 0x04, BYTE_LEN, 0 },
        
        { 0x0068, 0x5F, BYTE_LEN, 0 }, //cxc, 0xshd, 0xinp, 0xgain on
};


/* FIH-SW3-MM-UW-flash tuning-04+*/
int16_t x_8[] = {   
    0,
    -68,
    -133,
    -194,
    -253,
    -309,
    -363,
    -415,
    -464,
    -511,
    -557,
    -601,
    -644,
    -685,
    -724,
    -763,
    -800,
    -836,
    -871,
    -905,
    -938,
    -969,
    -1001,
    -1031,
    -1060,
    -1089,
    -1117,
    -1144,
    -1171,
    -1196,
    -1222,
    -1246,
    -1271,
    -1294,
    -1317,
    -1340,
    -1362,
    -1383,
    -1405,
    -1425,
    -1446,
    -1465,
    -1485,
    -1504,
    -1523,
    -1541,
    -1559,
    -1577,
    -1594,
    -1611,
    -1628,
    -1644,
    -1660,
    -1676,
    -1692,
    -1707,
    -1722,
    -1737,
    -1752,
    -1766,
    -1780,
    -1794,
    -1808,
    -1821,
    -1834,
    -1847,
    -1860,
    -1873,
    -1885,
    -1897,
    -1909,
    -1921,
    -1933,
    -1944,
    -1956,
    -1967,
    -1978,
    -1989,
    -2000,
    -2010,
    -2021,
    -2031,
    -2041,
    -2051,
    -2061,
    -2071,
    -2081,
    -2090,
    -2099,
    -2109,
    -2118,
    -2127,
    -2136,
    -2145,
    -2153,
    -2162,
    -2170,
    -2179,
    -2187,
    -2195,
    -2203,
    -2211,
    -2219,
    -2227,
    -2234,
    -2242,
    -2249,
    -2257,
    -2264,
    -2271,
    -2279,
    -2286,
    -2293,
    -2299,
    -2306,
    -2313,
    -2320,
    -2326,
    -2333,
    -2339,
    -2346,
    -2352,
    -2358,
    -2364,
    -2371,
    -2377,
    -2383,
    -2389,
    -2394,
    -2400,
    -2406,
    -2412,
    -2417,
    -2423,
    -2428,
    -2434,
    -2439,
    -2444,
    -2450,
    -2455,
    -2460,
    -2465,
    -2470,
    -2475,
    -2480,
    -2485,
    -2490,
    -2495,
    -2499,
    -2504,
    -2509,
    -2513,
    -2518,
    -2522,
    -2527,
    -2531,
    -2536,
    -2540,
    -2544,
    -2549,
    -2553,
    -2557,
    -2561,
    -2565,
    -2570,
    -2574,
    -2578,
    -2581,
    -2585,
    -2589,
    -2593,
    -2597,
    -2601,
    -2604,
    -2608,
    -2612,
    -2615,
    -2619,
    -2623,
    -2626,
    -2630,
    -2633,
    -2637,
    -2640,
    -2643,
    -2647,
    -2650,
    -2653,
    -2657,
    -2660,
    -2663,
    -2666,
    -2669,
    -2673,
    -2676,
    -2679,
    -2682,
    -2685,
    -2688,
    -2691,
    -2694,
    -2696,
    -2699,
    -2702,
    -2705,
    -2708,
    -2711,
    -2713,
    -2716,
    -2719,
    -2722,
    -2724,
    -2727,
    -2729,
    -2732,
    -2735,
    -2737,
    -2740,
    -2742,
    -2745,
    -2747,
    -2750,
    -2752,
    -2754,
    -2757,
    -2759,
    -2762,
    -2764,
    -2766,
    -2769,
    -2771,
    -2773,
    -2775,
    -2777,
    -2780,
    -2782,
    -2784,
    -2786,
    -2788,
    -2790,
    -2793,
    -2795,
    -2797,
    -2799,
    -2801,
    -2803,
    -2805,
    -2807,
    -2809,
    -2811,
    -2813,
    -2814,
    -2816,
    -2818,
    -2820,
    -2822,
    -2824,
    -2826,
    -2827,
    -2829,
    -2831,
    -2833,
    -2834,
    -2836,
    -2838,
    -2840,
    -2841,
    -2843,
    -2845,
    -2846,
    -2848,
    -2850,
    -2851,
    -2853,
    -2854,
    -2856,
    -2858,
    -2859,
    -2861,
    -2862,
    -2864,
    -2865,
    -2867,
    -2868,
    -2870,
    -2871,
    -2873,
    -2874,
    -2875,
    -2877,
    -2878,
    -2880,
    -2881,
    -2882,
    -2884,
    -2885,
    -2887,
    -2888,
    -2889,
    -2890,
    -2892,
    -2893,
    -2894,
    -2896,
    -2897,
    -2898,
    -2899,
    -2901,
    -2902,
    -2903,
    -2904,
    -2905,
    -2907,
    -2908,
    -2909,
    -2910,
    -2911,
    -2912,
    -2914,
    -2915,
    -2916,
    -2917,
    -2918,
    -2919,
    -2920,
    -2921,
    -2922,
    -2923,
    -2925,
    -2926,
    -2927,
    -2928,
    -2929,
    -2930,
    -2931,
    -2932,
    -2933,
    -2934,
    -2935,
    -2936,
    -2937,
    -2938,
    -2938,
    -2939,
    -2940,
    -2941,
    -2942,
    -2943,
    -2944,
    -2945,
    -2946,
    -2947,
    -2948,
    -2948,
    -2949,
    -2950,
    -2951,
    -2952,
    -2953,
    -2954,
    -2954,
    -2955,
    -2956,
    -2957,
    -2958,
    -2958,
    -2959,
    -2960,
    -2961,
    -2962,
    -2962,
    -2963,
    -2964,
    -2965,
    -2965,
    -2966,
    -2967,
    -2968,
    -2968,
    -2969,
    -2970,
    -2971,
    -2971,
    -2972,
    -2973,
    -2973,
    -2974,
    -2975,
    -2975,
    -2976,
    -2977,
    -2977,
    -2978,
    -2979,
    -2979,
    -2980,
    -2981,
    -2981,
    -2982,
    -2983,
    -2983,
    -2984,
    -2984,
    -2985,
    -2986,
    -2986,
    -2987,
    -2987,
    -2988,
    -2989,
    -2989,
    -2990,
    -2990,
    -2991,
    -2991,
    -2992,
    -2993,
    -2993,
    -2994,
    -2994,
    -2995,
    -2995,
    -2996,
    -2996,
    -2997,
    -2997,
    -2998,
    -2998,
    -2999,
    -2999,
    -3000,
    -3000,
    -3001,
    -3001,
    -3002,
    -3002,
    -3003,
    -3003,
    -3004,
    -3004,
    -3005,
    -3005,
    -3006,
    -3006,
    -3007,
    -3007,
    -3007,
    -3008,
    -3008,
    -3009,
    -3009,
    -3010,
    -3010,
    -3011,
    -3011,
    -3011,
    -3012,
    -3012,
    -3013,
    -3013,
    -3013,
    -3014,
    -3014,
    -3015,
    -3015,
    -3015,
    -3016,
    -3016,
    -3017,
    -3017,
    -3017,
    -3018,
    -3018,
    -3018,
    -3019,
    -3019,
    -3020,
    -3020,
    -3020,
    -3021,
    -3021,
    -3021,
    -3022,
    -3022,
    -3022,
    -3023,
    -3023,
    -3023,
    -3024,
    -3024,
    -3024,
    -3025,
    -3025,
    -3025,
    -3026,
    -3026,
    -3026,
    -3027,
    -3027,
    -3027,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3028,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3029,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3030,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3031,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3032,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3033,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3034,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3035,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3036,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3037,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3038,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3039,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
    -3040,
};
/* FIH-SW3-MM-UW-flash tuning-04-*/

/* FIH-SW3-MM-UW-read vendor id-00+*/
/* FIH-SW3-MM-SL-PatchForCameraFeature-01*{ */
struct isx006_reg isx006_regs = {
    .reg_init = &isx006_init_settings[0],
    .reg_init_size = ARRAY_SIZE(isx006_init_settings),

    .reg_preload2 = &isx006_preload2_settings[0],
    .reg_preload2_size = ARRAY_SIZE(isx006_preload2_settings),   

    .reg_preload3 = &isx006_preload3_settings[0],
    .reg_preload3_size = ARRAY_SIZE(isx006_preload3_settings),   

    //KMOT setting
    .reg_preload2_2nd = &isx006_preload2_2nd_settings[0],
    .reg_preload2_2nd_size = ARRAY_SIZE(isx006_preload2_2nd_settings),   

    .reg_preload3_2nd = &isx006_preload3_2nd_settings[0],
    .reg_preload3_2nd_size = ARRAY_SIZE(isx006_preload3_2nd_settings),   

    .reg_preload3_reload = &isx006_preload3_reload_settings[0],
    .reg_preload3_reload_size = ARRAY_SIZE(isx006_preload3_reload_settings),  

    //Scene
    .reg_sport = &isx006_sport_settings[0],
    .reg_sport_size = ARRAY_SIZE(isx006_sport_settings),

    .reg_bench_snow = &isx006_bench_snow_settings[0],
    .reg_bench_snow_size = ARRAY_SIZE(isx006_bench_snow_settings),

    .reg_night = &isx006_night_settings[0],
    .reg_night_size = ARRAY_SIZE(isx006_night_settings),

    .reg_auto_scene = &isx006_auto_scene_settings[0],
    .reg_auto_scene_size = ARRAY_SIZE(isx006_auto_scene_settings),

    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
    .reg_landscape = &isx006_landscape_settings[0],
    .reg_landscape_size = ARRAY_SIZE(isx006_landscape_settings),

    .reg_document = &isx006_document_settings[0],
    .reg_document_size = ARRAY_SIZE(isx006_document_settings),
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}          
    /* FIH-SW3-MM-UW-write OTP setting-00+*/
    .reg_SHD_MAX = &isx006_SHD_MAX_settings[0],
    .reg_SHD_MAX_size = ARRAY_SIZE(isx006_SHD_MAX_settings),	

    .reg_SHD_MIN = &isx006_SHD_MIN_settings[0],
    .reg_SHD_MIN_size = ARRAY_SIZE(isx006_SHD_MIN_settings),		

    .reg_SHD_TYP = &isx006_SHD_TYP_settings[0],
    .reg_SHD_TYP_size = ARRAY_SIZE(isx006_SHD_TYP_settings),	
    /* FIH-SW3-MM-UW-write OTP setting-00-*/

    .reg_SHD_MAX_2nd = &isx006_SHD_MAX_2nd_settings[0],
    .reg_SHD_MAX_2nd_size = ARRAY_SIZE(isx006_SHD_MAX_2nd_settings),	

    .reg_SHD_MIN_2nd = &isx006_SHD_MIN_2nd_settings[0],
    .reg_SHD_MIN_2nd_size = ARRAY_SIZE(isx006_SHD_MIN_2nd_settings),		

    .reg_SHD_TYP_2nd = &isx006_SHD_TYP_2nd_settings[0],
    .reg_SHD_TYP_2nd_size = ARRAY_SIZE(isx006_SHD_TYP_2nd_settings),
};
/* FIH-SW3-MM-SL-PatchForCameraFeature-01*} */
/* FIH-SW3-MM-UW-read vendor id-00-*/

