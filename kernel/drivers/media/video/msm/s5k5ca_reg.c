/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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

#include "s5k5ca.h"
struct reg_struct_type s5k5ca_truly_init_array[] = {
#include "s5k5ca_yuv_1101.h"
//#include "s5k5ca_truly_init.h"
{0,0,0,0},
};
struct reg_struct_type s5k5ca_mcnex_init_array[] = {
#if 1
#include "s5k5ca_yuv_mcnex_init_20121130.h"
//#include "s5k5ca_yuv_mcnex_init_version2_110.h"
//#include "s5k5ca_yuv_mcnex_init.h"
#else
#include "s5k5ca_bayer_mcnex_init.h"
#endif
    { 0, 0, 0, 0},
};

struct reg_struct_type *s5k5ca_init_settings_array;

#if 0
struct reg_struct_type s5k5ca_init_settings_array[] = {
#if 1
#include "s5k5ca_yuv_mcnex_init.h"
#else
#include "s5k5ca_bayer_mcnex_init.h"
#endif
};
#endif
//==========================================================================================
// Capture Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_capture[] =
{
	//============================================================                                                 
	// Capture Configuration Update setting                                              
	//============================================================ 

	//WRITE	7000035E	00b0	//#REG_0TC_CCFG_usWidth
	//WRITE	70000360	0090	//#REG_0TC_CCFG_usHeight

	//$MIPI[Width:2048,Height:1536,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 
	{0x0028, 0x7000 ,16,0},
	{0x002A, 0x0244 ,16,0},
	{0x0F12, 0x0000 ,16,0}, //REG_TC_GP_ActiveCapConfig
	                       
	{0x002A, 0x0230 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_NewConfigSync
	                       
	{0x002A, 0x0246 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_CapConfigChanged
	                       
	{0x002A, 0x0224 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnableCapture

	{0x0028, 0xD000 ,16,0},
	{0x002A, 0xB0A0 ,16,0},
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change
	                       
	{0x0028, 0x7000 ,16,0},
	{0x002A, 0x0226 ,16,0},
	{0x0F12, 0x0001 ,16,300}, //REG_TC_GP_EnableCaptureChanged
	{ 0, 0, 0, 0}
};
//==========================================================================================
// Capture Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_capture_Night_Mode[] =
{
	//============================================================                                                 
	// Capture Configuration Update setting                                              
	//============================================================ 

	//WRITE	7000035E	00b0	//#REG_0TC_CCFG_usWidth
	//WRITE	70000360	0090	//#REG_0TC_CCFG_usHeight

	//$MIPI[Width:2048,Height:1536,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 
	{0x0028, 0x7000 ,16,0},
	{0x002A, 0x0244 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_ActiveCapConfig
	                       
	{0x002A, 0x0230 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_NewConfigSync
	                       
	{0x002A, 0x0246 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_CapConfigChanged
	                       
	{0x002A, 0x0224 ,16,0},
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnableCapture

	{0x0028, 0xD000 ,16,0},
	{0x002A, 0xB0A0 ,16,0},
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change
	                       
	{0x0028, 0x7000 ,16,0},
	{0x002A, 0x0226 ,16,0},
	{0x0F12, 0x0001 ,16,250}, //REG_TC_GP_EnableCaptureChanged
	{ 0, 0, 0, 0}
};
//==========================================================================================
// Preview Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_preview[] =
{

	//$MIPI[Width:1024,Height:768,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 

	////////////////////////////////////////////////////////
	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x023C ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, //REG_TC_GP_ActivePrevConfig

	{0x002A, 0x0240 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevOpenAfterChange
	                        
	{0x002A, 0x0230 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_NewConfigSync

	{0x002A, 0x023E ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevConfigChanged

	{0x002A, 0x0220 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_EnablePreview

	{0x0028, 0xD000 ,16,0}, 
	{0x002A, 0xB0A0 ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change

	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x0222 ,16,0}, 
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnablePreviewChanged
	{ 0, 0, 0, 0}
};
//==========================================================================================
// White Balance Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_WB_Auto[] =
{
 //{0xfcfc,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x04D2,16,0},  
 {0x0f12,0x067F,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_WB_Incandescent[] =
{
 //{0xfcfc,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002A,0x04D2,16,0},
 {0x0F12,0x0677,16,0}, //#REG_TC_DBG_AutoAlgEnBits,AWBOff
 {0x002A,0x04A0,16,0},
 {0x0f12,0x0400,16,0}, //03D0
 {0x0f12,0x0001,16,0}, //0001
 {0x0f12,0x0400,16,0}, //0400
 {0x0f12,0x0001,16,0}, //0001
 {0x0f12,0x0940,16,0}, //0920
 {0x0f12,0x0001,16,0}, //0001 
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_WB_Fluorescent[] =
{
 //{0xfcfc,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002A,0x04D2,16,0},
 {0x0F12,0x0677,16,0}, //#REG_TC_DBG_AutoAlgEnBits,AWBOff
 {0x002A,0x04A0,16,0},
 {0x0f12,0x0575,16,0},
 {0x0f12,0x0001,16,0},
 {0x0f12,0x0400,16,0},
 {0x0f12,0x0001,16,0},
 {0x0f12,0x0800,16,0},
 {0x0f12,0x0001,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_WB_Cloudy[] =
{
 //{0xfcfc,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002A,0x04D2,16,0},
 {0x0F12,0x0677,16,0}, //#REG_TC_DBG_AutoAlgEnBits,AWBOff
 {0x002A,0x04A0,16,0},
 {0x0f12,0x0740,16,0}, 
 {0x0f12,0x0001,16,0}, //0001 
 {0x0f12,0x0400,16,0}, //0400 
 {0x0f12,0x0001,16,0}, //0001 
 {0x0f12,0x0580,16,0}, //0485 
 {0x0f12,0x0001,16,0}, //0001 
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_WB_Daylight[] =
{
 //{0xfcfc,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002A,0x04D2,16,0},
 {0x0F12,0x0677,16,0}, //#REG_TC_DBG_AutoAlgEnBits,AWBOff
 {0x002A,0x04A0,16,0},
 {0x0F12,0x05A0,16,0}, //#REG_SF_USER_Rgain
 {0x0F12,0x0001,16,0},
 {0x0F12,0x0400,16,0}, //#REG_SF_USER_Ggain
 {0x0F12,0x0001,16,0},
 {0x0F12,0x05D0,16,0}, //#REG_SF_USER_Bgain
 {0x0F12,0x0001,16,0},
 { 0, 0, 0, 0}
};
/*
1: auto
2: ?
3: incandescent
4: fluorescent
5: daylight
6: cloudy
*/
struct reg_struct_type *s5k5ca_WB[S5K5CA_WB_MAX] =
{
 s5k5ca_WB_Auto,
 s5k5ca_WB_Auto,
 s5k5ca_WB_Incandescent,
 s5k5ca_WB_Fluorescent,
 s5k5ca_WB_Daylight,
 s5k5ca_WB_Cloudy,
};

//==========================================================================================
// Brightness Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_brightness_0[] =
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x020C,16,0},  
 {0x0F12,0xFFB8,16,0},
 //{0x0F12,0x0000,16,0},
 //{0x002A,0x0F70,16,0},
 //{0x0F12,0x002F,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_brightness_1[] =
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x020C,16,0},  
 {0x0F12,0xFFDC,16,0},
 //{0x0F12,0x0000,16,0},
 //{0x002A,0x0F70,16,0},
 //{0x0F12,0x0038,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_brightness_2[] =
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x020C,16,0},  
 {0x0F12,0x0000,16,0},
 //{0x0F12,0x0000,16,0},
 //{0x002A,0x0F70,16,0},
 //{0x0F12,0x0040,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_brightness_3[] =
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x020C,16,0},  
 {0x0F12,0x0020,16,0},
 //{0x0F12,0x0000,16,0},
 //{0x002A,0x0F70,16,0},
 //{0x0F12,0x0043,16,0},
 { 0, 0, 0, 0}
};

struct reg_struct_type s5k5ca_brightness_4[] =
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x020C,16,0},  
 {0x0F12,0x0040,16,0},
 //{0x0F12,0x0000,16,0},
 //{0x002A,0x0F70,16,0},
 //{0x0F12,0x0046,16,0},
 { 0, 0, 0, 0}
};
struct reg_struct_type *s5k5ca_brightness[S5K5CA_BRIGHTNESS_MAX] =
{
 s5k5ca_brightness_0,
 s5k5ca_brightness_1,
 s5k5ca_brightness_2,
 s5k5ca_brightness_3,
 s5k5ca_brightness_4,
};


//==========================================================================================
// Effect Configuration Update setting
//==========================================================================================
struct reg_struct_type S5K5CA_effect_NONE[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0000,16,0},
 { 0, 0, 0, 0}
};
 
struct reg_struct_type S5K5CA_effect_MONO[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0001,16,0},
 { 0, 0, 0, 0}
};
 
struct reg_struct_type S5K5CA_effect_NEGATIVE[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0}, 
 {0x0F12,0x0000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0003,16,0},
 { 0, 0, 0, 0}
};
struct reg_struct_type S5K5CA_effect_SEPIA[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0}, 
 {0x0F12,0x0000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0004,16,0},
 { 0, 0, 0, 0}
};
 
struct reg_struct_type S5K5CA_effect_AQUA[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0},
 {0x0F12,0x0000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0005,16,0},
 { 0, 0, 0, 0}
};
 
struct reg_struct_type S5K5CA_effect_SKETCH[]=
{
 //{0xFCFC,0xd000,16,0},
 {0x0028,0x7000,16,0},
 {0x002a,0x021E,16,0},
 {0x0F12,0x0000,16,0},
 {0x002a,0x021E,16,0},  
 {0x0F12,0x0006,16,0},
 { 0, 0, 0, 0}
};
/*
0: CAMERA_EFFECT_OFF
1: CAMERA_EFFECT_MONO
2: CAMERA_EFFECT_NEGATIVE
3: CAMERA_EFFECT_SOLARIZE
4: CAMERA_EFFECT_SEPIA
5: CAMERA_EFFECT_POSTERIZE
6: CAMERA_EFFECT_WHITEBOARD
7: CAMERA_EFFECT_BLACKBOARD
8: CAMERA_EFFECT_AQUA
9: CAMERA_EFFECT_MAX
*/
struct reg_struct_type *s5k5ca_effect[S5K5CA_EFFECT_MAX] =
{
 S5K5CA_effect_NONE,
 S5K5CA_effect_MONO,
 S5K5CA_effect_NEGATIVE,
 S5K5CA_effect_NONE,
 S5K5CA_effect_SEPIA,
 S5K5CA_effect_SKETCH,
 S5K5CA_effect_NONE,
 S5K5CA_effect_NONE,
 S5K5CA_effect_AQUA,
 S5K5CA_effect_NONE,
};


//==========================================================================================
// Exposure mode Configuration Update setting
//==========================================================================================
struct reg_struct_type s5k5ca_exposure_default[]=
{
 //================================================================================================
 // 1. Spot mode : Default weighted (center based)
 //================================================================================================
 { 0x0028, 0x7000, 16, 0}, // Set page
 { 0x002A, 0x0F7E, 16, 0}, // Set address

 // Set table
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_0_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_1_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_2_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_3_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_4_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_5_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_6_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_7_
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_8_
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_9_
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_10
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_11
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_12
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_13
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_14
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_15
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_16
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_17
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_18
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_19
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_20
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_21
 { 0x0F12, 0x0303, 16, 0}, //#ae_WeightTbl_16_22
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_23
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_24
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_25
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_26
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_27
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_28
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_29
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_30
 { 0x0F12, 0x0101, 16, 0}, //#ae_WeightTbl_16_31
 { 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_exposure_average[]=
{
 //================================================================================================
 // 2. Spot mode : Average weighted 
 //================================================================================================
 { 0x0028, 0x7000, 16, 0}, // Set page
 { 0x002A, 0x0F7E, 16, 0}, // Set address

 // Set table
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_0_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_1_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_2_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_3_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_4_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_5_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_6_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_7_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_8_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_9_
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_10
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_11
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_12
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_13
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_14
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_15
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_16
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_17
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_18
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_19
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_20
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_21
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_22
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_23
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_24
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_25
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_26
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_27
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_28
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_29
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_30
 { 0x0F12, 0x0101, 16, 0}, // #ae_WeightTbl_16_31
 { 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_exposure_center[]=
{
 //================================================================================================
 // 3. Spot mode : Center spot weighted 
 //================================================================================================
 { 0x0028, 0x7000, 16, 0}, // Set page
 { 0x002A, 0x0F7E, 16, 0}, // Set address

 // Set table
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_0_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_1_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_2_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_3_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_4_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_5_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_6_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_7_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_8_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_9_
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_10
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_11
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_12
 { 0x0F12, 0x0f00, 16, 0}, // #ae_WeightTbl_16_13
 { 0x0F12, 0x000f, 16, 0}, // #ae_WeightTbl_16_14
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_15
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_16
 { 0x0F12, 0x0f00, 16, 0}, // #ae_WeightTbl_16_17
 { 0x0F12, 0x000f, 16, 0}, // #ae_WeightTbl_16_18
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_19
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_20
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_21
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_22
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_23
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_24
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_25
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_26
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_27
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_28
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_29
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_30
 { 0x0F12, 0x0000, 16, 0}, // #ae_WeightTbl_16_31
 { 0, 0, 0, 0}
};

/*
1: frame-average
2: center-weighted
3: spot-metering
*/
struct reg_struct_type *s5k5ca_exposure[S5K5CA_EXPOSURE_MAX] =
{
 s5k5ca_exposure_default,
 s5k5ca_exposure_average,
 s5k5ca_exposure_center,
};

//==========================================================================================
// ISO Configuration Update setting
//==========================================================================================
struct reg_struct_type S5K5CA_iso_AUTO[]=
{
   
	{0x0028 ,0x7000,16,0},
	{0x002A ,0x04B4,16,0},
	{0x0F12 ,0x0000,16,0}, //REG_SF_USER_IsoType 0: ISO Auto 1: ISO Clasic 2: ISO Sport
	{0x0F12 ,0x0000,16,0}, //REG_SF_USER_IsoVal
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoChanged 
	{0,0,0,0}
};
struct reg_struct_type S5K5CA_iso_DEBLUR[]=
{
	{0,0,0,0}
};	
struct reg_struct_type S5K5CA_iso_100[]=
{
	{0x0028 ,0x7000,16,0},
	{0x002A ,0x04B4,16,0},
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoType 0: ISO Auto 1: ISO Clasic 2: ISO Sport
	{0x0F12 ,0x0064,16,0}, //REG_SF_USER_IsoVal
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoChanged 
	{0,0,0,0}
};
	
struct reg_struct_type S5K5CA_iso_200[]=
{
	{0x0028 ,0x7000,16,0},
	{0x002A ,0x04B4,16,0},
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoType 0: ISO Auto 1: ISO Clasic 2: ISO Sport
	{0x0F12 ,0x00C8,16,0}, //REG_SF_USER_IsoVal
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoChanged 
	{0,0,0,0}
};
struct reg_struct_type S5K5CA_iso_400[]=
{
	{0x0028 ,0x7000,16,0},
	{0x002A ,0x04B4,16,0},
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoType 0: ISO Auto 1: ISO Clasic 2: ISO Sport
	{0x0F12 ,0x0190,16,0}, //REG_SF_USER_IsoVal
	{0x0F12 ,0x0001,16,0}, //REG_SF_USER_IsoChanged 
	{0,0,0,0}
};
struct reg_struct_type S5K5CA_iso_800[]=
{
	
	{0,0,0,0}
};
struct reg_struct_type S5K5CA_iso_1600[]=
{
	
	{0,0,0,0}
};
struct reg_struct_type S5K5CA_iso_MAX[]=
{
	
	{0,0,0,0}
};
struct reg_struct_type *s5k5ca_iso[S5K5CA_ISO_MAX] =
{
	S5K5CA_iso_AUTO,
	S5K5CA_iso_DEBLUR,	
	S5K5CA_iso_100,
	S5K5CA_iso_200,
	S5K5CA_iso_400,	
	S5K5CA_iso_800,
	S5K5CA_iso_1600,
	S5K5CA_iso_MAX,
};

struct reg_struct_type s5k5ca_scene_normal[]=
{
//Truely-------------
#if 0
//================================================================================================
//	1. Scene - Normal (Recover to Original setting-Must match initial setting)
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002a, 0x246E, 16, 0},
{ 0x0f12, 0x0001, 16, 0},

{ 0x002A, 0x0842, 16, 0},
{ 0x0F12, 0x7850, 16, 0},
{ 0x0F12, 0x2878, 16, 0},
{ 0x002A, 0x0912, 16, 0},
{ 0x0F12, 0x643C, 16, 0},
{ 0x0F12, 0x2864, 16, 0},
{ 0x002A, 0x09E2, 16, 0},
{ 0x0F12, 0x3C2A, 16, 0},
{ 0x0F12, 0x283C, 16, 0},
{ 0x002A, 0x0AB2, 16, 0},
{ 0x0F12, 0x2228, 16, 0},
{ 0x0F12, 0x2822, 16, 0},
{ 0x002A, 0x0B82, 16, 0},
{ 0x0F12, 0x191C, 16, 0},
{ 0x0F12, 0x2819, 16, 0},

{ 0x0028, 0x7000, 16, 0},
{ 0x002A, 0x020C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0210, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x0F12, 0x0000, 16, 0},   

{ 0x002A, 0x0838, 16, 0},
{ 0x0F12, 0x083C, 16, 0},

{ 0x002A, 0x0530, 16, 0},
{ 0x0F12, 0x3A98, 16, 0},
{ 0x002A, 0x0534, 16, 0},
{ 0x0F12, 0x7EF4, 16, 0},
{ 0x002A, 0x167C, 16, 0},
{ 0x0F12, 0x9C40, 16, 0},
{ 0x002A, 0x1680, 16, 0},
{ 0x0F12, 0xF424, 16, 0},
{ 0x0F12, 0x0000, 16, 0},

{ 0x002A, 0x0538, 16, 0},
{ 0x0F12, 0x9C40, 16, 0},
{ 0x002A, 0x053C, 16, 0},
{ 0x0F12, 0xD055, 16, 0},
{ 0x002A, 0x1684, 16, 0},
{ 0x0F12, 0x0360, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x0F12, 0x3880, 16, 0},
{ 0x0F12, 0x0001, 16, 0},

{ 0x002A, 0x0540, 16, 0},
{ 0x0F12, 0x0170, 16, 0},
{ 0x0F12, 0x0250, 16, 0},
{ 0x002A, 0x168C, 16, 0},
{ 0x0F12, 0x0380, 16, 0},
{ 0x0F12, 0x0800, 16, 0},

{ 0x002A, 0x0544, 16, 0},
{ 0x0F12, 0x0100, 16, 0},

{ 0x002A, 0x0208, 16, 0},
{ 0x0F12, 0x0001, 16, 0},

{ 0x002A, 0x023C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0240, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0230, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x023E, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0220, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x0028, 0xD000, 16, 0},  
{ 0x002A, 0xB0A0, 16, 0},  
{ 0x0F12, 0x0000, 16, 0},  // Clear cont. clock befor config change
{ 0x002A, 0x0222, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0, 0, 0, 0}
//McNex---------------
#else
//================================================================================================
//     1. Scene - Normal (Recover to Original setting-Must match initial setting)
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002a, 0x246E, 16, 0},
{ 0x0f12, 0x0001, 16, 0},
 
{ 0x002A, 0x0842, 16, 0},
{ 0x0F12, 0x7850, 16, 0},
{ 0x0F12, 0x2878, 16, 0},
{ 0x002A, 0x0912, 16, 0},
{ 0x0F12, 0x643C, 16, 0},
{ 0x0F12, 0x2864, 16, 0},
{ 0x002A, 0x09E2, 16, 0},
{ 0x0F12, 0x3C2A, 16, 0},
{ 0x0F12, 0x283C, 16, 0},
{ 0x002A, 0x0AB2, 16, 0},
{ 0x0F12, 0x2228, 16, 0},
{ 0x0F12, 0x2822, 16, 0},
{ 0x002A, 0x0B82, 16, 0},
{ 0x0F12, 0x191C, 16, 0},
{ 0x0F12, 0x2819, 16, 0},
 
{ 0x0028, 0x7000, 16, 0},
{ 0x002A, 0x020C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0210, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x0F12, 0x0000, 16, 0},   
 
{ 0x002A, 0x0838, 16, 0},
{ 0x0F12, 0x083C, 16, 0},
 
{ 0x002A, 0x0530, 16, 0},
{ 0x0F12, 0x3A98, 16, 0},
{ 0x002A, 0x0534, 16, 0},
{ 0x0F12, 0x7EF4, 16, 0},
{ 0x002A, 0x167C, 16, 0},
{ 0x0F12, 0x9C40, 16, 0},
{ 0x002A, 0x1680, 16, 0},
{ 0x0F12, 0xF424, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
 
// Set capture, exposure time
{       0x002A, 0x0538, 16,       0},
{       0x0F12, 0x3A98, 16,        0}, // #lt_uCapMaxExp1   30ms
{       0x0F12, 0x0000, 16,        0},
{       0x0F12, 0x7EF4, 16,        0}, // #lt_uCapMaxExp2      65ms
{       0x0F12, 0x0000, 16,        0},
{       0x002A, 0x1684, 16,       0},
{       0x0F12, 0x9C40, 16,        0}, // #evt1_lt_uCapMaxExp3 80ms
{       0x0F12, 0x0000, 16,        0},
{       0x0F12, 0xF424, 16,        0}, // #evt1_lt_uCapMaxExp4 125ms
{       0x0F12, 0x0000, 16,        0},
 
{ 0x002A, 0x0540, 16, 0},
{ 0x0F12, 0x0170, 16, 0},
{ 0x0F12, 0x0250, 16, 0},
{ 0x002A, 0x168C, 16, 0},
{ 0x0F12, 0x0380, 16, 0},
{ 0x0F12, 0x0800, 16, 0},
 
{ 0x002A, 0x0544, 16, 0},
{ 0x0F12, 0x0100, 16, 0},
 
{ 0x002A, 0x0208, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
 
{ 0x002A, 0x023C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0240, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0230, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x023E, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0220, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x0028, 0xD000, 16, 0},  
{ 0x002A, 0xB0A0, 16, 0},  
{ 0x0F12, 0x0000, 16, 0},  // Clear cont. clock before config change
{ 0x002A, 0x0222, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0, 0, 0, 0}
#endif
};
struct reg_struct_type s5k5ca_scene_landscape[]=
{

//================================================================================================
//	2. Scene - Landscape
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002A, 0x020C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0210, 16, 0},
{ 0x0F12, 0x001E, 16, 0},
{ 0x002A, 0x0842, 16, 0},
{ 0x0F12, 0x6444, 16, 0},
{ 0x0F12, 0x465A, 16, 0},
{ 0x002A, 0x0912, 16, 0},
{ 0x0F12, 0x4B3A, 16, 0},
{ 0x0F12, 0x463F, 16, 0},
{ 0x002A, 0x09E2, 16, 0},
{ 0x0F12, 0x1A2D, 16, 0},
{ 0x0F12, 0x4628, 16, 0},
{ 0x002A, 0x0AB2, 16, 0},
{ 0x0F12, 0x1328, 16, 0},
{ 0x0F12, 0x3213, 16, 0},
{ 0x002A, 0x0B82, 16, 0},
{ 0x0F12, 0x0819, 16, 0},
{ 0x0F12, 0x3204, 16, 0},
{ 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_scene_night[]=
{
//================================================================================================
//	3. Scene - Night
//================================================================================================
 // Set preview exposure time
 {0x0028, 0x7000,16, 0},
 {0x002A, 0x0530,16, 0},
 {0x0F12, 0x3415,16, 0},
 {0x002A, 0x0534,16, 0},
 {0x0F12, 0x682A,16, 0},
 {0x002A, 0x167C,16, 0},
 {0x0F12, 0x8235,16, 0},
 {0x002A, 0x1680,16, 0},
 {0x0F12, 0x1A80,16, 0},
 {0x0F12, 0x0006,16, 0},
 // Set capture, exposure time
 {0x002A, 0x0538,16, 0},
 {0x0F12, 0x3415,16, 0},
 {0x002A, 0x053C,16, 0},
 {0x0F12, 0x682A,16, 0},
 {0x002A, 0x1684,16, 0},
 {0x0F12, 0x8235,16, 0},
 {0x002A, 0x1688,16, 0},
 {0x0F12, 0x1A80,16, 0},
 {0x0F12, 0x0006,16, 0},
 // Set gain        
 {0x002A, 0x0540,16, 0},
 {0x0F12, 0x0180,16, 0},
 {0x0F12, 0x0250,16, 0},
 {0x002A, 0x168C,16, 0},
 {0x0F12, 0x0340,16, 0},
 {0x0F12, 0x0820,16, 0},
 
 {0x002A, 0x0544,16, 0},
 {0x0F12, 0x0100,16, 0},



 {0x0028, 0x7000 ,16,0}, 
 {0x002A, 0x023C ,16,0}, 
 {0x0F12, 0x0002 ,16,0}, //REG_TC_GP_ActivePrevConfig

	{0x002A, 0x0240 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevOpenAfterChange
	                        
	{0x002A, 0x0230 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_NewConfigSync

	{0x002A, 0x023E ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevConfigChanged

	{0x002A, 0x0220 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_EnablePreview

	{0x0028, 0xD000 ,16,0}, 
	{0x002A, 0xB0A0 ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change

	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x0222 ,16,0}, 
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnablePreviewChanged
	
	
{ 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_scene_portrait[]=
{

//================================================================================================
//	4. Scene - Portrait
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002A, 0x020C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0210, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x0F12, 0xFFCC, 16, 0},
{ 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_scene_sports[]=
{

//================================================================================================
//	5. Scene - Sports                                                                           
//================================================================================================
{ 0x0028, 0x7000, 16, 0},           
{ 0x002A, 0x0530, 16, 0},
{ 0x0F12, 0x1A0A, 16, 0},
{ 0x002A, 0x0534, 16, 0},
{ 0x0F12, 0x4e20, 16, 0},
{ 0x002A, 0x167C, 16, 0},
{ 0x0F12, 0x682A, 16, 0},
{ 0x002A, 0x1680, 16, 0},
{ 0x0F12, 0x8235, 16, 0},
{ 0x0F12, 0x0000, 16, 0},

{ 0x002A, 0x0538, 16, 0},
{ 0x0F12, 0x1A0A, 16, 0},
{ 0x002A, 0x053C, 16, 0},
{ 0x0F12, 0x4e20, 16, 0},
{ 0x002A, 0x1684, 16, 0},
{ 0x0F12, 0x682A, 16, 0},
{ 0x002A, 0x1688, 16, 0},
{ 0x0F12, 0x8235, 16, 0},
{ 0x0F12, 0x0000, 16, 0},

{ 0x002A, 0x0540, 16, 0},
{ 0x0F12, 0x0300, 16, 0},
{ 0x0F12, 0x0380, 16, 0},
{ 0x002A, 0x168C, 16, 0},
{ 0x0F12, 0x0480, 16, 0},
{ 0x0F12, 0x0800, 16, 0},
        
{ 0x002A, 0x0544, 16, 0},
{ 0x0F12, 0x0100, 16, 0},

{ 0x002A, 0x023C, 16, 0},
{ 0x0F12, 0x0000, 16, 0},
{ 0x002A, 0x0240, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0230, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x023E, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x002A, 0x0220, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0x0028, 0xD000, 16, 0},  
{ 0x002A, 0xB0A0, 16, 0},  
{ 0x0F12, 0x0000, 16, 0},  // Clear cont. clock befor config change
{ 0x002A, 0x0222, 16, 0},
{ 0x0F12, 0x0001, 16, 0},
{ 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_scene_sunset[]=
{

//================================================================================================
//	6. Scene - Sunset                                                                          
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002a, 0x246E, 16, 0},
{ 0x0f12, 0x0000, 16, 0},
        
{ 0x002a, 0x04A0, 16, 0},
{ 0x0f12, 0x05E0, 16, 0},
{ 0x0f12, 0x0001, 16, 0},
{ 0x0f12, 0x0400, 16, 0},
{ 0x0f12, 0x0001, 16, 0},
{ 0x0f12, 0x0520, 16, 0},
{ 0x0f12, 0x0001, 16, 0},
{ 0, 0, 0, 0}
};
struct reg_struct_type s5k5ca_scene_text[]=
{

//================================================================================================
//	7. Scene - Text                                                                        
//================================================================================================
{ 0x0028, 0x7000, 16, 0},
{ 0x002A, 0x0842, 16, 0},
{ 0x0F12, 0x5C44, 16, 0},
{ 0x0F12, 0x4656, 16, 0},
{ 0x002A, 0x0912, 16, 0},
{ 0x0F12, 0x433A, 16, 0},
{ 0x0F12, 0x463B, 16, 0},
{ 0x002A, 0x09E2, 16, 0},
{ 0x0F12, 0x122D, 16, 0},
{ 0x0F12, 0x4624, 16, 0},
{ 0x002A, 0x0AB2, 16, 0},
{ 0x0F12, 0x0B28, 16, 0},
{ 0x0F12, 0x320F, 16, 0},
{ 0x002A, 0x0B82, 16, 0},
{ 0x0F12, 0x0010, 16, 0},
{ 0x0F12, 0x3200, 16, 0},

 { 0, 0, 0, 0}
};
/*
  CAMERA_BESTSHOT_OFF = 0,
  CAMERA_BESTSHOT_AUTO = 1,
  CAMERA_BESTSHOT_LANDSCAPE = 2,
  CAMERA_BESTSHOT_SNOW,
  CAMERA_BESTSHOT_BEACH,
  CAMERA_BESTSHOT_SUNSET = 5,
  CAMERA_BESTSHOT_NIGHT,
  CAMERA_BESTSHOT_PORTRAIT,
  CAMERA_BESTSHOT_BACKLIGHT,
  CAMERA_BESTSHOT_SPORTS,
  CAMERA_BESTSHOT_ANTISHAKE = 10,
  CAMERA_BESTSHOT_FLOWERS,
  CAMERA_BESTSHOT_CANDLELIGHT,
  CAMERA_BESTSHOT_FIREWORKS,
  CAMERA_BESTSHOT_PARTY,
  CAMERA_BESTSHOT_NIGHT_PORTRAIT = 15,
  CAMERA_BESTSHOT_THEATRE,
  CAMERA_BESTSHOT_ACTION,
  CAMERA_BESTSHOT_AR,
  CAMERA_BESTSHOT_MAX = 19
*/
struct reg_struct_type *s5k5ca_scene[S5K5CA_SCENE_MAX] =
{
 s5k5ca_scene_normal,
 s5k5ca_scene_normal,
 s5k5ca_scene_landscape,
 NULL,
 NULL,
 s5k5ca_scene_sunset,
 s5k5ca_scene_night,
 s5k5ca_scene_portrait,
 NULL,
 s5k5ca_scene_sports,
 s5k5ca_scene_text,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
};
struct reg_struct_type S5K5CA_fps_15[]=
{
    //$MIPI[Width:1024,Height:768,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 

	////////////////////////////////////////////////////////
	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x023C ,16,0}, 
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_ActivePrevConfig

	{0x002A, 0x0240 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevOpenAfterChange
	                        
	{0x002A, 0x0230 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_NewConfigSync

	{0x002A, 0x023E ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevConfigChanged

	{0x002A, 0x0220 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_EnablePreview

	{0x0028, 0xD000 ,16,0}, 
	{0x002A, 0xB0A0 ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change

	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x0222 ,16,0}, 
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnablePreviewChanged
	{ 0, 0, 0, 0}
};
struct reg_struct_type S5K5CA_fps_30[]=
{
    //$MIPI[Width:1024,Height:768,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 

	////////////////////////////////////////////////////////
	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x023C ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, //REG_TC_GP_ActivePrevConfig

	{0x002A, 0x0240 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevOpenAfterChange
	                        
	{0x002A, 0x0230 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_NewConfigSync

	{0x002A, 0x023E ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_PrevConfigChanged

	{0x002A, 0x0220 ,16,0}, 
	{0x0F12, 0x0001 ,16,0},  //REG_TC_GP_EnablePreview

	{0x0028, 0xD000 ,16,0}, 
	{0x002A, 0xB0A0 ,16,0}, 
	{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change

	{0x0028, 0x7000 ,16,0}, 
	{0x002A, 0x0222 ,16,0}, 
	{0x0F12, 0x0001 ,16,0}, //REG_TC_GP_EnablePreviewChanged
    { 0, 0, 0, 0},
};

struct reg_struct_type *s5k5ca_fps[S5K5CA_FPS_MAX] =
{
	S5K5CA_fps_15,
	S5K5CA_fps_30,
};

