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

#include "mt9v115_front.h"
struct reg_struct_type mt9v115_front_init_settings_array[] = {
#if 0
//[**********Step1*************]
{ 0x001A, 0x0105, 16, 00},//FIELD_WR= RESET_AND_MISC_CONTROL, RESET_PSEUDO_PIN, 1// this bit is self-clearing, it is not necessary to re-write a zero
//[**********Step2*************]
//[PLL_settings_parallel]
{ 0x001A, 0x0105, 16, 50},
{ 0x0010, 0x0216,16,0},// FIELD_WR= PLL_DIVIDERS, 0x0216 	
//DELAY=50    // ms
{ 0x0012, 0x0B00,16,0}, 	// FIELD_WR= PLL_P_DIVIDERS, 0x0B00
{ 0x0014, 0x2047,16,0}, 	// FIELD_WR= PLL_CONTROL,PLL_ENABLE,1   //
{ 0x0014, 0x2046,16,0}, 	// FIELD_WR= PLL_CONTROL,PLL_BYPASS,0
{ 0x0018, 0x4505,16,0}, 	// FIELD_WR= STANDBY_CONTROL_AND_STATUS,POWER_UP_STOP_MCU,1
{ 0x0018, 0x4504,16,100}, 	// FIELD_WR= STANDBY_CONTROL_AND_STATUS,STANDBY_SOFT,0
//DELAY=100   // ms
{ 0x0018, 0x4e00,16,0},  	//FIELD_WR= STANDBY_CONTROL_AND_STATUS,POWER_UP_STOP_MCU,0
{ 0x001A, 0x0520,16,0},  	//FIELD_WR= RESET_AND_MISC_CONTROL, 0x0520
{ 0x001A, 0x0564,16,200}, 	//FIELD_WR= RESET_AND_MISC_CONTROL, 0x0564
//DELAY= 200
{ 0x0012, 0x0200,16,0}, 	//FIELD_WR= PLL_P_DIVIDERS, 0x0200 	
{ 0x001E, 0x0100,16,0},  	// PAD_SLEW   // TODO:  it is configurable depended on system needed.
               
//[Timing_settings]
{0x300A, 0x01F9   ,16,0},	//frame_length_lines = 958 > 505
{0x300C, 0x02D6	,16,0}, 	//line_length_pck = 726
{0x3010, 0x0012	,16,0}, 	//fine_correction = 18
{0x9803, 0x07	,8,0},    //stat_fd_zone_height = 7
{0xA06E, 0x0098   ,16,0}, 	//cam_fd_config_fdperiod_50hz = 152
{0xA070, 0x007E   ,16,0},	//cam_fd_config_fdperiod_60hz = 126
{0xA072, 0x11	,8,0},//cam_fd_config_search_f1_50 = 17
{0xA073, 0x13	,8,0},//cam_fd_config_search_f2_50 = 19
{0xA074, 0x14	,8,0},//cam_fd_config_search_f1_60 = 20
{0xA075, 0x16	,8,0},//cam_fd_config_search_f2_60 = 22
{0xA076, 0x0014	,16,0},	//cam_fd_config_max_fdzone_50hz = 13(7.5fps) > 33(3fps) > 20(5fps)
{0xA078, 0x0018,	16,0},	//cam_fd_config_max_fdzone_60hz = 16 > 40 > 24
{0xA01A, 0x0014	,16,0},	//cam_ae_config_target_fdzone =   13 > 33 > 20

//[**********Step3*************]
//[Step3-Recommended]
//[Char_settings]
{0x3168,0x84F8,16,0}, 
{0x316A,0x028A,16,0},       //disable auto load for use with patch, Vrst_LO DAC Vrstlo=12(gain<=2), Vrstlo=8(gain>2) to fix Col FPn issue in low light
{0x316C,0xB477,16,0},       // txlo = -7 for low gain (blooming risk), LFW = 2.95 ke-, and min. gain = 1.3x
//{0x316C,0xB473,16,0},         txlo = -3 for low gain (blooming fix), LFW = 2.6 ke-, min. gain = 1.5x
{0x316E,0x828A ,16,0},         //eclipse setting recommended       
{0x3180,0x87FF ,16,0},          //DELTA_DK_CONTROL enabled       
//{0x31E0,0x0000 ,16,0},          //pix_def_ID keep off         
{0x3E02,0x0600,16,0},           
{0x3E04,0x221C,16,0},           
{0x3E06,0x3632,16,0},           
{0x3E08,0x3204,16,0},           
{0x3E0A,0x3106,16,0},          
{0x3E0C,0x3025,16,0},           
{0x3E0E,0x190B,16,0},           
{0x3E10,0x0700,16,0},           
{0x3E12,0x24FF,16,0},           
{0x3E14,0x3731,16,0},           
{0x3E16,0x0401,16,0},           
{0x3E18,0x211E,16,0},           
{0x3E1A,0x3633,16,0},          
{0x3E1C,0x3107,16,0},           
{0x3E1E,0x1A16,16,0},           
{0x3E20,0x312D,16,0},          
{0x3E22,0x3303,16,0},           
{0x3E24,0x1401,16,0},           
{0x3E26,0x0600,16,0},      //samp spare (Vaapix pulsing ON default)     
{0x3E30,0x0037,16,0},           
{0x3E32,0x1638,16,0},           
{0x3E90,0x0E05,16,0},           
{0x3E92,0x1310,16,0},           
{0x3E94,0x0904,16,0},           
{0x3E96,0x0B00,16,0},           
{0x3E98,0x130B,16,0},           
{0x3E9A,0x0C06,16,0},          
{0x3E9C,0x1411,16,0},           
{0x3E9E,0x0E01,16,0},           
{0x3ECC,0x4091,16,0},           
{0x3ECE,0x330D,16,0},          //CFPN Fix (was 0x430D) 
{0x3ED0,0x1817,16,0},          //ecl_en
{0x3ED2,0x8504,16,0},          //Vaapix_PD=1 to fix col FPn in high light      
//[enable patch1]
{0x0982, 0x0000,16,0},     	// ACCESS_CTL_STAT        	// REG= 0x0982, 0x0
{0x098A, 0x0000,16,0},     	// PHYSICAL_ADDRESS_ACCESS	// REG= 0x098A, 0x0                    // physical addressing mode
{0x824D, 0x0251,16,0},                                   	// REG_BURST= 0x824D, 0x0251, 0x0299   // overwrite SISR vectors
{0x824F, 0x0299,16,0},                                   	// REG= 0x098E, 0x0                    // back to logical addressing mode
{0x098E, 0x0000,16,0},     	// LOGICAL_ADDRESS_ACCESS 
 //[disable patch1]
{0x0982, 0x0000,16,0},   	// ACCESS_CTL_STAT        	// REG= 0x0982, 0x0
{0x098A, 0x0000,16,0},   	// PHYSICAL_ADDRESS_ACCESS	// REG= 0x098A, 0x0                    // physical addressing mode
{0x824D, 0xD1F2,16,0},                                 	// REG_BURST= 0x824D, 0xD1F2, 0xD2AD   // restore ROM SISR vectors
{0x824F, 0xD2AD,16,0},                                 	// REG= 0x098E, 0x0                    // back to logical addressing mode
{0x098E, 0x0000,16,0},   	// LOGICAL_ADDRESS_ACCESS 
//[patch1 thresholds]
{0x0982, 0x0000,16,0}, 	// ACCESS_CTL_STAT        	// REG= 0x0982, 0x0
{0x098A, 0x0000,16,0}, 	// PHYSICAL_ADDRESS_ACCESS	// REG= 0x098A, 0x0                    // physical addressing mode
{0x8340, 0x0048,16,0},                               	// REG_BURST= 0x8340, 72, 64, 0, 64, 0x1817, 0x1857    // gain*time thresholds, dark, bright, current, Vtxhi boost gain threshold, DAC_LD_4_5 bright, DAC_LD_4_5 dark
{0x8342, 0x0040,16,0},                               	// REG= 0x098E, 0x0                    // back to logical addressing mode
{0x8344, 0x0000,16,0},                               
{0x8346, 0x0040,16,0},                               
{0x8348, 0x1817,16,0},                               
{0x834A, 0x1857,16,0},                               
{0x098E, 0x0000,16,0}, 	// LOGICAL_ADDRESS_ACCESS 
//[a391soc_patch1]
{0x0982, 0x0000,16,0}, 	// ACCESS_CTL_STAT        	// REG= 0x0982, 0x0
{0x098A, 0x0000,16,0}, 	// PHYSICAL_ADDRESS_ACCESS	// REG= 0x098A, 0x0
{0x8251, 0x3C3C,16,0},                               	// REG_BURST= 0x8251, 0x3C3C, 0xBDD1, 0xF2D6, 0x15C1, 0x126, 0x3ADC, 0xA30, 0xED02
{0x8253, 0xBDD1,16,0},                               	// REG_BURST= 0x8261, 0xDC08, 0xED00, 0xFC01, 0xFCBD, 0xF5FC, 0x30EC, 0x2FD, 0x344
{0x8255, 0xF2D6,16,0},                               	// REG_BURST= 0x8271, 0xB303, 0x4025, 0xDCC, 0x3180, 0xED00, 0xCCA0, 0xBD, 0xFBFB
{0x8257, 0x15C1,16,0},                               	// REG_BURST= 0x8281, 0x2013, 0xFC03, 0x44B3, 0x342, 0x220B, 0xCC31, 0x80ED, 0xCC
{0x8259, 0x0126,16,0},                               	// REG_BURST= 0x8291, 0xA000, 0xBDFC, 0x1738, 0x3839, 0x3CD6, 0x15C1, 0x126, 0x70FC
{0x825B, 0x3ADC,16,0},                               	// REG_BURST= 0x82A1, 0x344, 0xB303, 0x4025, 0x13FC, 0x7E26, 0x83FF, 0xFF27, 0xBFC
{0x825D, 0x0A30,16,0},                               	// REG_BURST= 0x82B1, 0x7E26, 0xFD03, 0x4CCC, 0xFFFF, 0x2013, 0xFC03, 0x44B3, 0x342
{0x825F, 0xED02,16,0},                               	// REG_BURST= 0x82C1, 0x220E, 0xFC7E, 0x2683, 0xFFFF, 0x2606, 0xFC03, 0x4CFD, 0x7E26
{0x8261, 0xDC08,16,0},                               	// REG_BURST= 0x82D1, 0xFC7E, 0x2683, 0xFFFF, 0x2605, 0xFC03, 0x4A20, 0x3FC, 0x348
{0x8263, 0xED00,16,0},                               	// REG_BURST= 0x82E1, 0xFD7E, 0xD0FC, 0x7ED2, 0x5F84, 0xF030, 0xED00, 0xDC0A, 0xB303
{0x8265, 0xFC01,16,0},                               	// REG_BURST= 0x82F1, 0x4625, 0x10EC, 0x27, 0xCFD, 0x34E, 0xFC7E, 0xD284, 0xFED
{0x8267, 0xFCBD,16,0},                               	// REG_BURST= 0x8301, 0x20, 0x19DC, 0xAB3, 0x346, 0x2415, 0xEC00, 0x8300, 0x26
{0x8269, 0xF5FC,16,0},                               	// REG_BURST= 0x8311, 0xEFC, 0x7ED2, 0x840F, 0xFA03, 0x4FBA, 0x34E, 0xFD7E, 0xD2BD
{0x826B, 0x30EC,16,0},                               	// REG_BURST= 0x8321, 0xD2AD, 0x3839
{0x826D, 0x02FD,16,0},                               	// REG= 0x098E, 0x0                    // back to logical addressing mode
{0x826F, 0x0344,16,0},                               
{0x8271, 0xB303,16,0},                               
{0x8273, 0x4025,16,0},                               
{0x8275, 0x0DCC,16,0},                               
{0x8277, 0x3180,16,0},                               
{0x8279, 0xED00,16,0},                               
{0x827B, 0xCCA0,16,0},                               
{0x827D, 0x00BD,16,0},                               
{0x827F, 0xFBFB,16,0},                               
{0x8281, 0x2013,16,0},                               
{0x8283, 0xFC03,16,0},                               
{0x8285, 0x44B3,16,0},                               
{0x8287, 0x0342,16,0},                               
{0x8289, 0x220B,16,0},                               
{0x828B, 0xCC31,16,0},                               
{0x828D, 0x80ED,16,0},                               
{0x828F, 0x00CC,16,0},                               
{0x8291, 0xA000,16,0},                               
{0x8293, 0xBDFC,16,0},                               
{0x8295, 0x1738,16,0},                               
{0x8297, 0x3839,16,0},                               
{0x8299, 0x3CD6,16,0},                               
{0x829B, 0x15C1,16,0},                               
{0x829D, 0x0126,16,0},                               
{0x829F, 0x70FC,16,0},                               
{0x82A1, 0x0344,16,0},                               
{0x82A3, 0xB303,16,0},                               
{0x82A5, 0x4025,16,0},                               
{0x82A7, 0x13FC,16,0},                               
{0x82A9, 0x7E26,16,0},                               
{0x82AB, 0x83FF,16,0},                               
{0x82AD, 0xFF27,16,0},                               
{0x82AF, 0x0BFC,16,0},                               
{0x82B1, 0x7E26,16,0},                               
{0x82B3, 0xFD03,16,0},                               
{0x82B5, 0x4CCC,16,0},                               
{0x82B7, 0xFFFF,16,0},                               
{0x82B9, 0x2013,16,0},                               
{0x82BB, 0xFC03,16,0},                               
{0x82BD, 0x44B3,16,0},                               
{0x82BF, 0x0342,16,0},                               
{0x82C1, 0x220E,16,0},                               
{0x82C3, 0xFC7E,16,0},                               
{0x82C5, 0x2683,16,0},                               
{0x82C7, 0xFFFF,16,0},                               
{0x82C9, 0x2606,16,0},                               
{0x82CB, 0xFC03,16,0},                               
{0x82CD, 0x4CFD,16,0},                               
{0x82CF, 0x7E26,16,0},                               
{0x82D1, 0xFC7E,16,0},                               
{0x82D3, 0x2683,16,0},                               
{0x82D5, 0xFFFF,16,0},                               
{0x82D7, 0x2605,16,0},                               
{0x82D9, 0xFC03,16,0},                               
{0x82DB, 0x4A20,16,0},                               
{0x82DD, 0x03FC,16,0},                               
{0x82DF, 0x0348,16,0},                               
{0x82E1, 0xFD7E,16,0},                               
{0x82E3, 0xD0FC,16,0},                               
{0x82E5, 0x7ED2,16,0},                               
{0x82E7, 0x5F84,16,0},                               
{0x82E9, 0xF030,16,0},                               
{0x82EB, 0xED00,16,0},                               
{0x82ED, 0xDC0A,16,0},                               
{0x82EF, 0xB303,16,0},                               
{0x82F1, 0x4625,16,0},                               
{0x82F3, 0x10EC,16,0},                               
{0x82F5, 0x0027,16,0},                               
{0x82F7, 0x0CFD,16,0},                               
{0x82F9, 0x034E,16,0},                               
{0x82FB, 0xFC7E,16,0},                               
{0x82FD, 0xD284,16,0},                               
{0x82FF, 0x0FED,16,0},                               
{0x8301, 0x0020,16,0},                               
{0x8303, 0x19DC,16,0},                               
{0x8305, 0x0AB3,16,0},                               
{0x8307, 0x0346,16,0},                               
{0x8309, 0x2415,16,0},                               
{0x830B, 0xEC00,16,0},                               
{0x830D, 0x8300,16,0},                               
{0x830F, 0x0026,16,0},                               
{0x8311, 0x0EFC,16,0},                               
{0x8313, 0x7ED2,16,0},                               
{0x8315, 0x840F,16,0},                               
{0x8317, 0xFA03,16,0},                               
{0x8319, 0x4FBA,16,0},                               
{0x831B, 0x034E,16,0},                               
{0x831D, 0xFD7E,16,0},                               
{0x831F, 0xD2BD,16,0},                               
{0x8321, 0xD2AD,16,0},                               
{0x8323, 0x3839,16,0},                               
{0x098E, 0x0000,16,0},	// LOGICAL_ADDRESS_ACCESS 
//Adding the settings for 400x320.

//[400x320]
{0x098E, 0x8400,16,0},   		 // LOGICAL_ADDRESS_ACCESS [SEQ_CMD]
{ 0x8400, 0x01,8,0},   		 // SEQ_CMD
{0xA000, 0x0190,16,0},   		 // CAM_IMAGE_WIDTH
{ 0xA002, 0x0140,16,0},   		 // CAM_IMAGE_HEIGHT
{0x8400, 0x02,8,0}  		 // SEQ_CMD
#else
// LOAD=PLL_settings_serial
{ 0x001A, 0x0124, 16, 50}, 	// RESET_AND_MISC_CONTROL             // FIELD_WR= RESET_AND_MISC_CONTROL, RESET_PSEUDO_PIN, 1   
//DELAY=50                                                      // DELAY=50                                                
{ 0x0010, 0x0216, 16, 0}, 	// PLL_DIVIDERS                       // FIELD_WR= PLL_DIVIDERS, 0x0216 // REG= 0x0010, 0x0216   
{ 0x0012, 0x0B00, 16, 0}, 	// PLL_P_DIVIDERS                     // FIELD_WR= PLL_P_DIVIDERS, 0x0B00                        
{ 0x0014, 0x2047, 16, 0}, 	// PLL_CONTROL                        // FIELD_WR= PLL_CONTROL,PLL_ENABLE,1                      
{ 0x0014, 0x2046, 16, 0}, 	// PLL_CONTROL                        // FIELD_WR= PLL_CONTROL,PLL_BYPASS,0                      
{ 0x0018, 0x4505, 16, 0}, 	// STANDBY_CONTROL_AND_STATUS         // FIELD_WR= STANDBY_CONTROL_AND_STATUS,POWER_UP_STOP_MCU,1
{ 0x0018, 0x4504, 16, 100}, 	// STANDBY_CONTROL_AND_STATUS         // FIELD_WR= STANDBY_CONTROL_AND_STATUS,STANDBY_SOFT,0     
//DELAY=100         					      // DELAY=100                                               
{ 0x0018, 0x0000, 16, 0}, 	// STANDBY_CONTROL_AND_STATUS         // FIELD_WR= STANDBY_CONTROL_AND_STATUS,POWER_UP_STOP_MCU,0
{ 0x0042, 0xFFF3, 16, 0}, 	// COMMAND_RW                         // FIELD_WR= COMMAND_RW, 0xFFF3                            
{ 0x3C00, 0x5004, 16, 0}, 	// TX_CONTROL                         // FIELD_WR= TX_CONTROL, SEL_OUT_SOURCE, 4                 
{ 0x001A, 0x0520, 16, 0}, 	// RESET_AND_MISC_CONTROL             // FIELD_WR= RESET_AND_MISC_CONTROL, 0x0520                
{ 0x001A, 0x0564, 16, 200}, 	// RESET_AND_MISC_CONTROL             // FIELD_WR= RESET_AND_MISC_CONTROL, 0x0564                
//DELAY=200                                                     // DELAY= 200                                              
{ 0x0012, 0x0200, 16, 0}, 	// PLL_P_DIVIDERS                     // FIELD_WR= PLL_P_DIVIDERS, 0x0200                        
// [Timing_settings]
{ 0x300A, 0x01F9, 16, 0},		//frame_length_lines = 958 > 505
{ 0x300C, 0x02D6, 16, 0},		//line_length_pck = 726
{ 0x3010, 0x0012, 16, 0},		//fine_correction = 18
{ 0x9803, 0x07	, 8, 0},	//stat_fd_zone_height = 7
{ 0xA06E, 0x0098, 16, 0},		//cam_fd_config_fdperiod_50hz = 152
{ 0xA070, 0x007E, 16, 0},		//cam_fd_config_fdperiod_60hz = 126
{ 0xA072, 0x11	, 8, 0},	//cam_fd_config_search_f1_50 = 17
{ 0xA073, 0x13	, 8, 0},	//cam_fd_config_search_f2_50 = 19
{ 0xA074, 0x14	, 8, 0},	//cam_fd_config_search_f1_60 = 20
{ 0xA075, 0x16	, 8, 0},	//cam_fd_config_search_f2_60 = 22
{ 0xA076, 0x0014, 16, 0},		//cam_fd_config_max_fdzone_50hz = 13(7.5fps) > 33(3fps) > 20(5fps)
{ 0xA078, 0x0018, 16, 0},		//cam_fd_config_max_fdzone_60hz = 16 > 40 > 24
{ 0xA01A, 0x0014, 16, 0},		//cam_ae_config_target_fdzone =   13 > 33 > 20
//LOAD = Step3-Recommended	//Char settings
// [Char_settings]
{0x3168,0x84F8, 16, 0},
{0x316A,0x028A, 16, 0},          //disable auto load for use with patch, Vrst_LO DAC Vrstlo=12(gain<=2), Vrstlo=8(gain>2) to fix Col FPn issue in low light
{0x316C,0xB477, 16, 0},          // txlo = -7 for low gain (blooming risk), LFW = 2.95 ke-, and min. gain = 1.3x
{0x316E,0x828A, 16, 0},          //eclipse setting recommended       
{0x3180,0x87FF, 16, 0},           //DELTA_DK_CONTROL enabled       
{0x3E02,0x0600, 16, 0},           
{0x3E04,0x221C, 16, 0},           
{0x3E06,0x3632, 16, 0},           
{0x3E08,0x3204, 16, 0},           
{0x3E0A,0x3106, 16, 0},          
{0x3E0C,0x3025, 16, 0},           
{0x3E0E,0x190B, 16, 0},           
{0x3E10,0x0700, 16, 0},           
{0x3E12,0x24FF, 16, 0},           
{0x3E14,0x3731, 16, 0},           
{0x3E16,0x0401, 16, 0},           
{0x3E18,0x211E, 16, 0},           
{0x3E1A,0x3633, 16, 0},          
{0x3E1C,0x3107, 16, 0},           
{0x3E1E,0x1A16, 16, 0},           
{0x3E20,0x312D, 16, 0},          
{0x3E22,0x3303, 16, 0},           
{0x3E24,0x1401, 16, 0},           
{0x3E26,0x0600, 16, 0},            //samp spare (Vaapix pulsing ON default)     
{0x3E30,0x0037, 16, 0},           
{0x3E32,0x1638, 16, 0},           
{0x3E90,0x0E05, 16, 0},           
{0x3E92,0x1310, 16, 0},           
{0x3E94,0x0904, 16, 0},           
{0x3E96,0x0B00, 16, 0},           
{0x3E98,0x130B, 16, 0},           
{0x3E9A,0x0C06, 16, 0},          
{0x3E9C,0x1411, 16, 0},           
{0x3E9E,0x0E01, 16, 0},           
{0x3ECC,0x4091, 16, 0},           
{0x3ECE,0x330D, 16, 0},          //CFPN Fix (was 0x430D) 
{0x3ED0,0x1817, 16, 0},          //ecl_en
{0x3ED2,0x8504, 16, 0},          //Vaapix_PD=1 to fix col FPn in high light      
//LOAD=load_and_go patch1
// [a391soc_patch1]
{ 0x0982, 0x0000, 16, 0}, 	// ACCESS_CTL_STAT
{ 0x098A, 0x0000, 16, 0}, 	// PHYSICAL_ADDRESS_ACCESS
{ 0x8251, 0x3C3C, 16, 0},
{ 0x8253, 0xBDD1, 16, 0},
{ 0x8255, 0xF2D6, 16, 0},
{ 0x8257, 0x15C1, 16, 0},
{ 0x8259, 0x0126, 16, 0},
{ 0x825B, 0x3ADC, 16, 0},
{ 0x825D, 0x0A30, 16, 0},
{ 0x825F, 0xED02, 16, 0},
{ 0x8261, 0xDC08, 16, 0},
{ 0x8263, 0xED00, 16, 0},
{ 0x8265, 0xFC01, 16, 0},
{ 0x8267, 0xFCBD, 16, 0},
{ 0x8269, 0xF5FC, 16, 0},
{ 0x826B, 0x30EC, 16, 0},
{ 0x826D, 0x02FD, 16, 0},
{ 0x826F, 0x0344, 16, 0},
{ 0x8271, 0xB303, 16, 0},
{ 0x8273, 0x4025, 16, 0},
{ 0x8275, 0x0DCC, 16, 0},
{ 0x8277, 0x3180, 16, 0},
{ 0x8279, 0xED00, 16, 0},
{ 0x827B, 0xCCA0, 16, 0},
{ 0x827D, 0x00BD, 16, 0},
{ 0x827F, 0xFBFB, 16, 0},
{ 0x8281, 0x2013, 16, 0},
{ 0x8283, 0xFC03, 16, 0},
{ 0x8285, 0x44B3, 16, 0},
{ 0x8287, 0x0342, 16, 0},
{ 0x8289, 0x220B, 16, 0},
{ 0x828B, 0xCC31, 16, 0},
{ 0x828D, 0x80ED, 16, 0},
{ 0x828F, 0x00CC, 16, 0},
{ 0x8291, 0xA000, 16, 0},
{ 0x8293, 0xBDFC, 16, 0},
{ 0x8295, 0x1738, 16, 0},
{ 0x8297, 0x3839, 16, 0},
{ 0x8299, 0x3CD6, 16, 0},
{ 0x829B, 0x15C1, 16, 0},
{ 0x829D, 0x0126, 16, 0},
{ 0x829F, 0x70FC, 16, 0},
{ 0x82A1, 0x0344, 16, 0},
{ 0x82A3, 0xB303, 16, 0},
{ 0x82A5, 0x4025, 16, 0},
{ 0x82A7, 0x13FC, 16, 0},
{ 0x82A9, 0x7E26, 16, 0},
{ 0x82AB, 0x83FF, 16, 0},
{ 0x82AD, 0xFF27, 16, 0},
{ 0x82AF, 0x0BFC, 16, 0},
{ 0x82B1, 0x7E26, 16, 0},
{ 0x82B3, 0xFD03, 16, 0},
{ 0x82B5, 0x4CCC, 16, 0},
{ 0x82B7, 0xFFFF, 16, 0},
{ 0x82B9, 0x2013, 16, 0},
{ 0x82BB, 0xFC03, 16, 0},
{ 0x82BD, 0x44B3, 16, 0},
{ 0x82BF, 0x0342, 16, 0},
{ 0x82C1, 0x220E, 16, 0},
{ 0x82C3, 0xFC7E, 16, 0},
{ 0x82C5, 0x2683, 16, 0},
{ 0x82C7, 0xFFFF, 16, 0},
{ 0x82C9, 0x2606, 16, 0},
{ 0x82CB, 0xFC03, 16, 0},
{ 0x82CD, 0x4CFD, 16, 0},
{ 0x82CF, 0x7E26, 16, 0},
{ 0x82D1, 0xFC7E, 16, 0},
{ 0x82D3, 0x2683, 16, 0},
{ 0x82D5, 0xFFFF, 16, 0},
{ 0x82D7, 0x2605, 16, 0},
{ 0x82D9, 0xFC03, 16, 0},
{ 0x82DB, 0x4A20, 16, 0},
{ 0x82DD, 0x03FC, 16, 0},
{ 0x82DF, 0x0348, 16, 0},
{ 0x82E1, 0xFD7E, 16, 0},
{ 0x82E3, 0xD0FC, 16, 0},
{ 0x82E5, 0x7ED2, 16, 0},
{ 0x82E7, 0x5F84, 16, 0},
{ 0x82E9, 0xF030, 16, 0},
{ 0x82EB, 0xED00, 16, 0},
{ 0x82ED, 0xDC0A, 16, 0},
{ 0x82EF, 0xB303, 16, 0},
{ 0x82F1, 0x4625, 16, 0},
{ 0x82F3, 0x10EC, 16, 0},
{ 0x82F5, 0x0027, 16, 0},
{ 0x82F7, 0x0CFD, 16, 0},
{ 0x82F9, 0x034E, 16, 0},
{ 0x82FB, 0xFC7E, 16, 0},
{ 0x82FD, 0xD284, 16, 0},
{ 0x82FF, 0x0FED, 16, 0},
{ 0x8301, 0x0020, 16, 0},
{ 0x8303, 0x19DC, 16, 0},
{ 0x8305, 0x0AB3, 16, 0},
{ 0x8307, 0x0346, 16, 0},
{ 0x8309, 0x2415, 16, 0},
{ 0x830B, 0xEC00, 16, 0},
{ 0x830D, 0x8300, 16, 0},
{ 0x830F, 0x0026, 16, 0},
{ 0x8311, 0x0EFC, 16, 0},
{ 0x8313, 0x7ED2, 16, 0},
{ 0x8315, 0x840F, 16, 0},
{ 0x8317, 0xFA03, 16, 0},
{ 0x8319, 0x4FBA, 16, 0},
{ 0x831B, 0x034E, 16, 0},
{ 0x831D, 0xFD7E, 16, 0},
{ 0x831F, 0xD2BD, 16, 0},
{ 0x8321, 0xD2AD, 16, 0},
{ 0x8323, 0x3839, 16, 0},
{ 0x098E, 0x0000, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS
//LOAD=patch1 thresholds                
// [patch1 thresholds]
{ 0x0982, 0x0000, 16, 0}, 	// ACCESS_CTL_STAT
{ 0x098A, 0x0000, 16, 0}, 	// PHYSICAL_ADDRESS_ACCESS
{ 0x8340, 0x0048, 16, 0},
{ 0x8342, 0x0040, 16, 0},
{ 0x8344, 0x0000, 16, 0},
{ 0x8346, 0x0040, 16, 0},
{ 0x8348, 0x1817, 16, 0},
{ 0x834A, 0x1857, 16, 0},
{ 0x098E, 0x0000, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS
//LOAD=enable patch1
//[enable patch1]
{ 0x0982, 0x0000, 16, 0}, 	// ACCESS_CTL_STAT
{ 0x098A, 0x0000, 16, 0}, 	// PHYSICAL_ADDRESS_ACCESS
{ 0x824D, 0x0251, 16, 0},
{ 0x824F, 0x0299, 16, 0},
{ 0x098E, 0x0000, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS
// LOAD = Step4-PGA		//PGA
// //TODO:  QTech to provide Lens info and lens shading correction settings..
// LOAD = Step5-AWB_CCM		//AWB & CCM
// [SAM DeSatCCM lumLev5A_defaultD65_nWA4]
{ 0x098E, 0x202F, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS [CAM_AWB_CONFIG_CCM_L_0]
{ 0xA02F, 0x01C5, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_0
{ 0xA031, 0xFEED, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_1
{ 0xA033, 0x004D, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_2
{ 0xA035, 0xFFCD, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_3
{ 0xA037, 0x011B, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_4
{ 0xA039, 0x0017, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_5
{ 0xA03B, 0xFF9F, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_6
{ 0xA03D, 0xFF22, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_7
{ 0xA03F, 0x023D, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_8
{ 0xA045, 0x000E, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_0
{ 0xA047, 0x0079, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_1
{ 0xA049, 0xFF78, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_2
{ 0xA04B, 0xFFD9, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_3
{ 0xA04D, 0x0064, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_4
{ 0xA04F, 0xFFC1, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_5
{ 0xA051, 0x004D, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_6
{ 0xA053, 0x0064, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_7
{ 0xA055, 0xFF4E, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_8
//[PA AWB]
{ 0x098E, 0x2041, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS [CAM_AWB_CONFIG_CCM_L_9]
{ 0xA041, 0x001D, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_9
{ 0xA043, 0x0046, 16, 0}, 	// CAM_AWB_CONFIG_CCM_L_10
{ 0xA057, 0x0010, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_9
{ 0xA059, 0xFFE0, 16, 0}, 	// CAM_AWB_CONFIG_CCM_RL_10
{ 0xA065, 0x03 	, 8, 0},// CAM_AWB_CONFIG_X_SCALE
{ 0x2112, 0x051E, 16, 0}, 	// AWB_WEIGHT_R0
{ 0x2114, 0x0000, 16, 0}, 	// AWB_WEIGHT_R1
{ 0x2116, 0xAE40, 16, 0}, 	// AWB_WEIGHT_R2
{ 0x2118, 0x7AE1, 16, 0}, 	// AWB_WEIGHT_R3
{ 0x211A, 0x1996, 16, 0}, 	// AWB_WEIGHT_R4
{ 0x211C, 0x0F5A, 16, 0}, 	// AWB_WEIGHT_R5
{ 0x211E, 0xFDD8, 16, 0}, 	// AWB_WEIGHT_R6
{ 0x2120, 0x5000, 16, 0}, 	// AWB_WEIGHT_R7
//LOAD = Step6-CPIPE_Calibration	//Color Pipe Calibration settings, if any
// [Step6-CPIPE_Calibration]
{ 0x9418, 0x2E 	, 8, 0},// AWB_B_SCENE_RATIO_LOWER
// LOAD = Step7-CPIPE_Preference	//Color Pipe preference settings, if any
// LOAD=NR
{ 0x326E, 0x0006, 16, 0}, 	// LOW_PASS_YUV_FILTER
{ 0x33F4, 0x000B, 16, 0}, 	// KERNEL_CONFIG
{ 0x098E, 0xA07A, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS [CAM_LL_CONFIG_AP_THRESH_START]
{ 0xA07A, 0x10 	, 8, 0},// CAM_LL_CONFIG_AP_THRESH_START
{ 0xA07C, 0x04 	, 8, 0},// CAM_LL_CONFIG_AP_GAIN_START
{ 0xA081, 0x1E 	, 8, 0},// CAM_LL_CONFIG_DM_EDGE_TH_START
{ 0xA082, 0x50 	, 8, 0},// CAM_LL_CONFIG_DM_EDGE_TH_STOP
{ 0xA0B1, 0x10 	, 8, 0},// CAM_LL_CONFIG_NR_RED_START
{ 0xA0B2, 0x2D 	, 8, 0},// CAM_LL_CONFIG_NR_RED_STOP
{ 0xA0B3, 0x10 	, 8, 0},// CAM_LL_CONFIG_NR_GREEN_START
{ 0xA0B4, 0x2D 	, 8, 0},// CAM_LL_CONFIG_NR_GREEN_STOP
{ 0xA0B5, 0x10 	, 8, 0},// CAM_LL_CONFIG_NR_BLUE_START
{ 0xA0B6, 0x2D 	, 8, 0},// CAM_LL_CONFIG_NR_BLUE_STOP
{ 0xA0B7, 0x10 	, 8, 0},// CAM_LL_CONFIG_NR_MIN_MAX_START
{ 0xA0B8, 0x2D 	, 8, 0},// CAM_LL_CONFIG_NR_MIN_MAX_STOP
{ 0xA05F, 0x80 	, 8, 0},// CAM_AWB_CONFIG_START_SATURATION
{ 0xA060, 0x05 	, 8, 0},// CAM_AWB_CONFIG_END_SATURATION
{ 0xA0B9, 0x0026, 16, 0}, 	// CAM_LL_CONFIG_START_GAIN_METRIC
{ 0xA0BB, 0x00B4, 16, 0}, 	// CAM_LL_CONFIG_STOP_GAIN_METRIC
{ 0xA07E, 0x001E, 16, 0}, 	// CAM_LL_CONFIG_CDC_THRESHOLD_BM
{ 0xA083, 0x03E8, 16, 0}, 	// CAM_LL_CONFIG_FTB_AVG_YSUM_START
{ 0xA085, 0x0096, 16, 0}, 	// CAM_LL_CONFIG_FTB_AVG_YSUM_STOP
{ 0x9C00, 0xFF 	, 8, 0},// LL_MODE
// LOAD=Gamma
{ 0x098E, 0xA087, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS [CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_0]
{ 0xA087, 0x00 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_0
{ 0xA088, 0x07 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_1
{ 0xA089, 0x16 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_2
{ 0xA08A, 0x30 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_3
{ 0xA08B, 0x52 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_4
{ 0xA08C, 0x6D 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_5
{ 0xA08D, 0x86 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_6
{ 0xA08E, 0x9B 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_7
{ 0xA08F, 0xAB 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_8
{ 0xA090, 0xB9 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_9
{ 0xA091, 0xC5 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_10
{ 0xA092, 0xCF 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_11
{ 0xA093, 0xD8 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_12
{ 0xA094, 0xE0 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_13
{ 0xA095, 0xE7 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_14
{ 0xA096, 0xEE 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_15
{ 0xA097, 0xF4 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_16
{ 0xA098, 0xFA 	, 8, 0},// CAM_LL_CONFIG_GAMMA_CONTRAST_CURVE_17
{ 0xA0AD, 0x0005, 16, 0}, 	// CAM_LL_CONFIG_GAMMA_START_BM
{ 0xA0AF, 0x0021, 16, 0}, 	// CAM_LL_CONFIG_GAMMA_STOP_BM
// LOAD=AE preferred
{ 0x098E, 0xA020, 16, 0}, 	// LOGICAL_ADDRESS_ACCESS [CAM_AE_CONFIG_BASE_TARGET]
{ 0xA020, 0x3C 	, 8, 0},// CAM_AE_CONFIG_BASE_TARGET
{ 0xA027, 0x002A, 16, 0}, 	// CAM_AE_CONFIG_MIN_VIRT_AGAIN
{ 0xA029, 0x0180, 16, 0}, 	// CAM_AE_CONFIG_MAX_VIRT_AGAIN
{ 0xA01C, 0x0140, 16, 0}, 	// CAM_AE_CONFIG_TARGET_AGAIN
{ 0xA023, 0x0080, 16, 0}, 	// CAM_AE_CONFIG_MIN_VIRT_DGAIN
{ 0xA025, 0x0080, 16, 0}, 	// CAM_AE_CONFIG_MAX_VIRT_DGAIN
{ 0xA01E, 0x0100, 16, 0}, 	// CAM_AE_CONFIG_TARGET_DGAIN
// FD
{ 0x8C03, 0x01, 8, 0}, 	// FD_STAT_MIN
{ 0x8C04, 0x03, 8, 0}, 	// FD_STAT_MAX
{ 0x8C05, 0x05, 8, 0}, 	// FD_MIN_AMPLITUDE
// LOAD = Step8-Features		//Ports, special features, etc., if any
{ 0x0018, 0x0002, 16, 0} 	// STANDBY_CONTROL_AND_STATUS  // FIELD_WR = STANDBY_CONTROL_AND_STATUS, 0x0002	//release power up stop, keep FW PLL startup
#endif
};

//==========================================================================================
// Capture Configuration Update setting
//==========================================================================================
struct reg_struct_type mt9v115_front_capture[] =
{
 { 0, 0, 0, 0}
};
//==========================================================================================
// Preview Configuration Update setting
//==========================================================================================
struct reg_struct_type mt9v115_front_preview[] =
{
 { 0, 0, 0, 0}
};
//==========================================================================================
// White Balance Configuration Update setting
//==========================================================================================
struct reg_struct_type mt9v115_front_WB_Auto[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_WB_Incandescent[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_WB_Fluorescent[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_WB_Cloudy[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_WB_Daylight[] =
{
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
struct reg_struct_type *mt9v115_front_WB[MT9V115_FRONT_WB_MAX] =
{
 mt9v115_front_WB_Auto,
 mt9v115_front_WB_Auto,
 mt9v115_front_WB_Incandescent,
 mt9v115_front_WB_Fluorescent,
 mt9v115_front_WB_Daylight,
 mt9v115_front_WB_Cloudy,
};

//==========================================================================================
// Brightness Configuration Update setting
//==========================================================================================
struct reg_struct_type mt9v115_front_brightness_0[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_brightness_1[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_brightness_2[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_brightness_3[] =
{
 { 0, 0, 0, 0}
};

struct reg_struct_type mt9v115_front_brightness_4[] =
{
 { 0, 0, 0, 0}
};
struct reg_struct_type *mt9v115_front_brightness[MT9V115_FRONT_BRIGHTNESS_MAX] =
{
 mt9v115_front_brightness_0,
 mt9v115_front_brightness_1,
 mt9v115_front_brightness_2,
 mt9v115_front_brightness_3,
 mt9v115_front_brightness_4,
};


//==========================================================================================
// Effect Configuration Update setting
//==========================================================================================
struct reg_struct_type MT9V115_FRONT_effect_NONE[]=
{
 { 0, 0, 0, 0}
};
 
struct reg_struct_type MT9V115_FRONT_effect_MONO[]=
{
 { 0, 0, 0, 0}
};
 
struct reg_struct_type MT9V115_FRONT_effect_NEGATIVE[]=
{
 { 0, 0, 0, 0}
};
struct reg_struct_type MT9V115_FRONT_effect_SEPIA[]=
{
 { 0, 0, 0, 0}
};
 
struct reg_struct_type MT9V115_FRONT_effect_AQUA[]=
{
 { 0, 0, 0, 0}
};
 
struct reg_struct_type MT9V115_FRONT_effect_SKETCH[]=
{
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
struct reg_struct_type *mt9v115_front_effect[MT9V115_FRONT_EFFECT_MAX] =
{
 MT9V115_FRONT_effect_NONE,
 MT9V115_FRONT_effect_MONO,
 MT9V115_FRONT_effect_NEGATIVE,
 MT9V115_FRONT_effect_NONE,
 MT9V115_FRONT_effect_SEPIA,
 MT9V115_FRONT_effect_SKETCH,
 MT9V115_FRONT_effect_NONE,
 MT9V115_FRONT_effect_NONE,
 MT9V115_FRONT_effect_AQUA,
 MT9V115_FRONT_effect_NONE,
};


//==========================================================================================
// Exposure mode Configuration Update setting
//==========================================================================================
struct reg_struct_type mt9v115_front_exposure_default[]=
{
 //================================================================================================
 // 1. Spot mode : Default weighted (center based)
 //================================================================================================
 { 0, 0, 0, 0}
};
struct reg_struct_type mt9v115_front_exposure_average[]=
{
 //================================================================================================
 // 2. Spot mode : Average weighted 
 //================================================================================================
 { 0, 0, 0, 0}
};
struct reg_struct_type mt9v115_front_exposure_center[]=
{
 //================================================================================================
 // 3. Spot mode : Center spot weighted 
 //================================================================================================
 { 0, 0, 0, 0}
};

/*
1: frame-average
2: center-weighted
3: spot-metering
*/
struct reg_struct_type *mt9v115_front_exposure[MT9V115_FRONT_EXPOSURE_MAX] =
{
 mt9v115_front_exposure_default,
 mt9v115_front_exposure_average,
 mt9v115_front_exposure_center,
};

int32_t mt9v115_front_array_length = sizeof(mt9v115_front_init_settings_array) /
 sizeof(mt9v115_front_init_settings_array[0]);



