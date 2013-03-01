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

#include "mt9v115.h"

/* MTD-SW-MM-SL-FinuTuneFrontCamera-00*{ */
//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*{
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02+{
//Div2-SW6-MM-MC-PortingMt9v115NewSetting_0701-00*{
struct fih_i2c_reg_conf mt9v115_init_settings_array[] = {
  //{ Reg_address, Reg_Value, size, DelayTime}
    /* Porting revision = 0701 */
    { 0x001A, 0x0106, WORD_LEN, 0 },//0xB566
    { 0x0010, 0x052C, WORD_LEN, 0 },
    { 0x0012, 0x0800, WORD_LEN, 0 },//For 400kHz I2C clock.
    { 0x0014, 0x2047, WORD_LEN, 0 },    
    { 0x0014, 0x2046, WORD_LEN, 0 },    
    { 0x0018, 0x4505, WORD_LEN, 0 },    
    { 0x0018, 0x4504, WORD_LEN, 64 },   
    { 0x0042, 0xFFF3, WORD_LEN, 0 },// COMMAND_RW
    { 0x3C00, 0x0004, WORD_LEN, 0 },// TX_CONTROL
    { 0x001A, 0x0520, WORD_LEN, 0 },// RESET_AND_MISC_CONTROL
    { 0x001A, 0x0564, WORD_LEN, 32 },// RESET_AND_MISC_CONTROL
    { 0x0012, 0x0200, WORD_LEN, 0 },// PLL_P_DIVIDERS
    { 0x300A, 0x01F9, WORD_LEN, 0 },// FRAME_LENGTH_LINES
    { 0x300C, 0x02D6, WORD_LEN, 0 },// LINE_LENGTH_PCK
    { 0x3010, 0x0012, WORD_LEN, 0 },// FINE_CORRECTION
    { 0x3040, 0x0041, WORD_LEN, 0 },// READ_MODE
    { 0x098E, 0x9803, WORD_LEN, 0 },// LOGICAL_ADDRESS_ACCESS [STAT_FD_ZONE_HEIGHT]
    { 0x9803, 0x0730, WORD_LEN, 0 },// STAT_FD_ZONE_HEIGHT
    { 0xA06E, 0x0098, WORD_LEN, 0 },// CAM_FD_CONFIG_FDPERIOD_50HZ
    { 0xA070, 0x007E, WORD_LEN, 0 },// CAM_FD_CONFIG_FDPERIOD_60HZ
    { 0xA072, 0x1113, WORD_LEN, 0 },// CAM_FD_CONFIG_SEARCH_F1_50
    { 0xA074, 0x1416, WORD_LEN, 0 },// CAM_FD_CONFIG_SEARCH_F1_60
    { 0xA076, 0x000D, WORD_LEN, 0 },// CAM_FD_CONFIG_MAX_FDZONE_50HZ
    { 0xA078, 0x0010, WORD_LEN, 0 },// CAM_FD_CONFIG_MAX_FDZONE_60HZ
    { 0xA01A, 0x000D, WORD_LEN, 0 }// CAM_AE_CONFIG_TARGET_FDZONE
};
//Div2-SW6-MM-MC-PortingMt9v115NewSetting_0701-00*}
//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*}

//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+{
struct fih_i2c_reg_conf mt9v115_sub_init_settings_array[] = {
    //Char_settings
    { 0x3168, 0x84F8, WORD_LEN, 0 },
    { 0x316A, 0x028A, WORD_LEN, 0 },
    { 0x316C, 0xB477, WORD_LEN, 0 },
    { 0x316E, 0x8268, WORD_LEN, 0 },
    { 0x3180, 0x87FF, WORD_LEN, 0 },
    { 0x3E02, 0x0600, WORD_LEN, 0 },
    { 0x3E04, 0x221C, WORD_LEN, 0 },
    { 0x3E06, 0x3632, WORD_LEN, 0 },
    { 0x3E08, 0x3204, WORD_LEN, 0 },
    { 0x3E0A, 0x3106, WORD_LEN, 0 },
    { 0x3E0C, 0x3025, WORD_LEN, 0 },
    { 0x3E0E, 0x190B, WORD_LEN, 0 },
    { 0x3E10, 0x0700, WORD_LEN, 0 },
    { 0x3E12, 0x24FF, WORD_LEN, 0 },
    { 0x3E14, 0x3731, WORD_LEN, 0 },
    { 0x3E16, 0x0401, WORD_LEN, 0 },
    { 0x3E18, 0x211E, WORD_LEN, 0 },
    { 0x3E1A, 0x3633, WORD_LEN, 0 },
    { 0x3E1C, 0x3107, WORD_LEN, 0 },
    { 0x3E1E, 0x1A16, WORD_LEN, 0 },
    { 0x3E20, 0x312D, WORD_LEN, 0 },
    { 0x3E22, 0x3303, WORD_LEN, 0 },
    { 0x3E24, 0x1401, WORD_LEN, 0 },
    { 0x3E26, 0x0600, WORD_LEN, 0 },
    { 0x3E30, 0x0037, WORD_LEN, 0 },
    { 0x3E32, 0x1638, WORD_LEN, 0 },
    { 0x3E90, 0x0E05, WORD_LEN, 0 },
    { 0x3E92, 0x1310, WORD_LEN, 0 },
    { 0x3E94, 0x0904, WORD_LEN, 0 },
    { 0x3E96, 0x0B00, WORD_LEN, 0 },
    { 0x3E98, 0x130B, WORD_LEN, 0 },
    { 0x3E9A, 0x0C06, WORD_LEN, 0 },
    { 0x3E9C, 0x1411, WORD_LEN, 0 },
    { 0x3E9E, 0x0E01, WORD_LEN, 0 },
    { 0x3ECC, 0x4091, WORD_LEN, 0 },
    { 0x3ECE, 0x430D, WORD_LEN, 0 },
    { 0x3ED0, 0x1817, WORD_LEN, 0 },
    { 0x3ED2, 0x8504, WORD_LEN, 0 },
    //load_and_go patch1
    { 0x0982, 0x0000, WORD_LEN, 0 },
    { 0x098A, 0x0000, WORD_LEN, 0 },
    { 0x8251, 0x3C3C, WORD_LEN, 0 },
    { 0x8253, 0xBDD1, WORD_LEN, 0 },
    { 0x8255, 0xF2D6, WORD_LEN, 0 },
    { 0x8257, 0x15C1, WORD_LEN, 0 },
    { 0x8259, 0x0126, WORD_LEN, 0 },
    { 0x825B, 0x3ADC, WORD_LEN, 0 },
    { 0x825D, 0x0A30, WORD_LEN, 0 },
    { 0x825F, 0xED02, WORD_LEN, 0 },
    { 0x8261, 0xDC08, WORD_LEN, 0 },
    { 0x8263, 0xED00, WORD_LEN, 0 },
    { 0x8265, 0xFC01, WORD_LEN, 0 },
    { 0x8267, 0xFCBD, WORD_LEN, 0 },
    { 0x8269, 0xF5FC, WORD_LEN, 0 },
    { 0x826B, 0x30EC, WORD_LEN, 0 },
    { 0x826D, 0x02FD, WORD_LEN, 0 },
    { 0x826F, 0x0344, WORD_LEN, 0 },
    { 0x8271, 0xB303, WORD_LEN, 0 },
    { 0x8273, 0x4025, WORD_LEN, 0 },
    { 0x8275, 0x0DCC, WORD_LEN, 0 },
    { 0x8277, 0x3180, WORD_LEN, 0 },
    { 0x8279, 0xED00, WORD_LEN, 0 },
    { 0x827B, 0xCCA0, WORD_LEN, 0 },
    { 0x827D, 0x00BD, WORD_LEN, 0 },
    { 0x827F, 0xFBFB, WORD_LEN, 0 },
    { 0x8281, 0x2013, WORD_LEN, 0 },
    { 0x8283, 0xFC03, WORD_LEN, 0 },
    { 0x8285, 0x44B3, WORD_LEN, 0 },
    { 0x8287, 0x0342, WORD_LEN, 0 },
    { 0x8289, 0x220B, WORD_LEN, 0 },
    { 0x828B, 0xCC31, WORD_LEN, 0 },
    { 0x828D, 0x80ED, WORD_LEN, 0 },
    { 0x828F, 0x00CC, WORD_LEN, 0 },
    { 0x8291, 0xA000, WORD_LEN, 0 },
    { 0x8293, 0xBDFC, WORD_LEN, 0 },
    { 0x8295, 0x1738, WORD_LEN, 0 },
    { 0x8297, 0x3839, WORD_LEN, 0 },
    { 0x8299, 0x3CD6, WORD_LEN, 0 },
    { 0x829B, 0x15C1, WORD_LEN, 0 },
    { 0x829D, 0x0126, WORD_LEN, 0 },
    { 0x829F, 0x70FC, WORD_LEN, 0 },
    { 0x82A1, 0x0344, WORD_LEN, 0 },
    { 0x82A3, 0xB303, WORD_LEN, 0 },
    { 0x82A5, 0x4025, WORD_LEN, 0 },
    { 0x82A7, 0x13FC, WORD_LEN, 0 },
    { 0x82A9, 0x7E26, WORD_LEN, 0 },
    { 0x82AB, 0x83FF, WORD_LEN, 0 },
    { 0x82AD, 0xFF27, WORD_LEN, 0 },
    { 0x82AF, 0x0BFC, WORD_LEN, 0 },
    { 0x82B1, 0x7E26, WORD_LEN, 0 },
    { 0x82B3, 0xFD03, WORD_LEN, 0 },
    { 0x82B5, 0x4CCC, WORD_LEN, 0 },
    { 0x82B7, 0xFFFF, WORD_LEN, 0 },
    { 0x82B9, 0x2013, WORD_LEN, 0 },
    { 0x82BB, 0xFC03, WORD_LEN, 0 },
    { 0x82BD, 0x44B3, WORD_LEN, 0 },
    { 0x82BF, 0x0342, WORD_LEN, 0 },
    { 0x82C1, 0x220E, WORD_LEN, 0 },
    { 0x82C3, 0xFC7E, WORD_LEN, 0 },
    { 0x82C5, 0x2683, WORD_LEN, 0 },
    { 0x82C7, 0xFFFF, WORD_LEN, 0 },
    { 0x82C9, 0x2606, WORD_LEN, 0 },
    { 0x82CB, 0xFC03, WORD_LEN, 0 },
    { 0x82CD, 0x4CFD, WORD_LEN, 0 },
    { 0x82CF, 0x7E26, WORD_LEN, 0 },
    { 0x82D1, 0xFC7E, WORD_LEN, 0 },
    { 0x82D3, 0x2683, WORD_LEN, 0 },
    { 0x82D5, 0xFFFF, WORD_LEN, 0 },
    { 0x82D7, 0x2605, WORD_LEN, 0 },
    { 0x82D9, 0xFC03, WORD_LEN, 0 },
    { 0x82DB, 0x4A20, WORD_LEN, 0 },
    { 0x82DD, 0x03FC, WORD_LEN, 0 },
    { 0x82DF, 0x0348, WORD_LEN, 0 },
    { 0x82E1, 0xFD7E, WORD_LEN, 0 },
    { 0x82E3, 0xD0FC, WORD_LEN, 0 },
    { 0x82E5, 0x7ED2, WORD_LEN, 0 },
    { 0x82E7, 0x5F84, WORD_LEN, 0 },
    { 0x82E9, 0xF030, WORD_LEN, 0 },
    { 0x82EB, 0xED00, WORD_LEN, 0 },
    { 0x82ED, 0xDC0A, WORD_LEN, 0 },
    { 0x82EF, 0xB303, WORD_LEN, 0 },
    { 0x82F1, 0x4625, WORD_LEN, 0 },
    { 0x82F3, 0x10EC, WORD_LEN, 0 },
    { 0x82F5, 0x0027, WORD_LEN, 0 },
    { 0x82F7, 0x0CFD, WORD_LEN, 0 },
    { 0x82F9, 0x034E, WORD_LEN, 0 },
    { 0x82FB, 0xFC7E, WORD_LEN, 0 },
    { 0x82FD, 0xD284, WORD_LEN, 0 },
    { 0x82FF, 0x0FED, WORD_LEN, 0 },
    { 0x8301, 0x0020, WORD_LEN, 0 },
    { 0x8303, 0x19DC, WORD_LEN, 0 },
    { 0x8305, 0x0AB3, WORD_LEN, 0 },
    { 0x8307, 0x0346, WORD_LEN, 0 },
    { 0x8309, 0x2415, WORD_LEN, 0 },
    { 0x830B, 0xEC00, WORD_LEN, 0 },
    { 0x830D, 0x8300, WORD_LEN, 0 },
    { 0x830F, 0x0026, WORD_LEN, 0 },
    { 0x8311, 0x0EFC, WORD_LEN, 0 },
    { 0x8313, 0x7ED2, WORD_LEN, 0 },
    { 0x8315, 0x840F, WORD_LEN, 0 },
    { 0x8317, 0xFA03, WORD_LEN, 0 },
    { 0x8319, 0x4FBA, WORD_LEN, 0 },
    { 0x831B, 0x034E, WORD_LEN, 0 },
    { 0x831D, 0xFD7E, WORD_LEN, 0 },
    { 0x831F, 0xD2BD, WORD_LEN, 0 },
    { 0x8321, 0xD2AD, WORD_LEN, 0 },
    { 0x8323, 0x3839, WORD_LEN, 0 },
    { 0x098E, 0x0000, WORD_LEN, 0 },
    //patch1 thresholds
    { 0x0982, 0x0000, WORD_LEN, 0 },
    { 0x098A, 0x0000, WORD_LEN, 0 },
    { 0x8340, 0x0048, WORD_LEN, 0 },
    { 0x8342, 0x0040, WORD_LEN, 0 },
    { 0x8344, 0x0000, WORD_LEN, 0 },
    { 0x8346, 0x0040, WORD_LEN, 0 },
    { 0x8348, 0x1817, WORD_LEN, 0 },
    { 0x834A, 0x1857, WORD_LEN, 0 },
    { 0x098E, 0x0000, WORD_LEN, 0 },
    //enable patch1
    { 0x0982, 0x0000, WORD_LEN, 0 },
    { 0x098A, 0x0000, WORD_LEN, 0 },
    { 0x824D, 0x0251, WORD_LEN, 0 },
    { 0x824F, 0x0299, WORD_LEN, 0 },
    { 0x098E, 0x0000, WORD_LEN, 0 },
    //Lens Correction 85%
    { 0x3210, 0x00B8, WORD_LEN, 0 },
    { 0x3640, 0x0030, WORD_LEN, 0 },
    { 0x3642, 0x3608, WORD_LEN, 0 },
    { 0x3644, 0x24F0, WORD_LEN, 0 },
    { 0x3646, 0xFC0D, WORD_LEN, 0 },
    { 0x3648, 0xB94C, WORD_LEN, 0 },
    { 0x364A, 0x0090, WORD_LEN, 0 },
    { 0x364C, 0x26A8, WORD_LEN, 0 },
    { 0x364E, 0x3250, WORD_LEN, 0 },
    { 0x3650, 0xA5AD, WORD_LEN, 0 },
    { 0x3652, 0xB82A, WORD_LEN, 0 },
    { 0x3654, 0x0090, WORD_LEN, 0 },
    { 0x3656, 0x88AC, WORD_LEN, 0 },
    { 0x3658, 0x0190, WORD_LEN, 0 },
    { 0x365A, 0xA76B, WORD_LEN, 0 },
    { 0x365C, 0x872C, WORD_LEN, 0 },
    { 0x365E, 0x01F0, WORD_LEN, 0 },
    { 0x3660, 0x0D0A, WORD_LEN, 0 },
    { 0x3662, 0x26B0, WORD_LEN, 0 },
    { 0x3664, 0xF10D, WORD_LEN, 0 },
    { 0x3666, 0x988C, WORD_LEN, 0 },
    { 0x3680, 0x670B, WORD_LEN, 0 },
    { 0x3682, 0xEDC9, WORD_LEN, 0 },
    { 0x3684, 0x720A, WORD_LEN, 0 },
    { 0x3686, 0xD92D, WORD_LEN, 0 },
    { 0x3688, 0xDCED, WORD_LEN, 0 },
    { 0x368A, 0x54EB, WORD_LEN, 0 },
    { 0x368C, 0x1084, WORD_LEN, 0 },
    { 0x368E, 0x3408, WORD_LEN, 0 },
    { 0x3690, 0xE00D, WORD_LEN, 0 },
    { 0x3692, 0x8E6E, WORD_LEN, 0 },
    { 0x3694, 0x230B, WORD_LEN, 0 },
    { 0x3696, 0x8826, WORD_LEN, 0 },
    { 0x3698, 0x418A, WORD_LEN, 0 },
    { 0x369A, 0xC6CD, WORD_LEN, 0 },
    { 0x369C, 0x950B, WORD_LEN, 0 },
    { 0x369E, 0x510B, WORD_LEN, 0 },
    { 0x36A0, 0xE5A4, WORD_LEN, 0 },
    { 0x36A2, 0x48EB, WORD_LEN, 0 },
    { 0x36A4, 0xE9AD, WORD_LEN, 0 },
    { 0x36A6, 0xAE4D, WORD_LEN, 0 },
    { 0x36C0, 0x1AB0, WORD_LEN, 0 },
    { 0x36C2, 0xA1AE, WORD_LEN, 0 },
    { 0x36C4, 0x9650, WORD_LEN, 0 },
    { 0x36C6, 0xCB0E, WORD_LEN, 0 },
    { 0x36C8, 0x3AF1, WORD_LEN, 0 },
    { 0x36CA, 0x2330, WORD_LEN, 0 },
    { 0x36CC, 0xCC2C, WORD_LEN, 0 },
    { 0x36CE, 0x7C0E, WORD_LEN, 0 },
    { 0x36D0, 0xCCCC, WORD_LEN, 0 },
    { 0x36D2, 0x57AE, WORD_LEN, 0 },
    { 0x36D4, 0x0D10, WORD_LEN, 0 },
    { 0x36D6, 0x336D, WORD_LEN, 0 },
    { 0x36D8, 0x8A4E, WORD_LEN, 0 },
    { 0x36DA, 0xE590, WORD_LEN, 0 },
    { 0x36DC, 0x8AB0, WORD_LEN, 0 },
    { 0x36DE, 0x1670, WORD_LEN, 0 },
    { 0x36E0, 0xE24E, WORD_LEN, 0 },
    { 0x36E2, 0x9C2E, WORD_LEN, 0 },
    { 0x36E4, 0x196E, WORD_LEN, 0 },
    { 0x36E6, 0x0470, WORD_LEN, 0 },
    { 0x3700, 0xF98A, WORD_LEN, 0 },
    { 0x3702, 0x060A, WORD_LEN, 0 },
    { 0x3704, 0x45CA, WORD_LEN, 0 },
    { 0x3706, 0xE64A, WORD_LEN, 0 },
    { 0x3708, 0x7ACD, WORD_LEN, 0 },
    { 0x370A, 0xB64C, WORD_LEN, 0 },
    { 0x370C, 0x9D0D, WORD_LEN, 0 },
    { 0x370E, 0x87ED, WORD_LEN, 0 },
    { 0x3710, 0x2F8E, WORD_LEN, 0 },
    { 0x3712, 0x0BF0, WORD_LEN, 0 },
    { 0x3714, 0xAF6A, WORD_LEN, 0 },
    { 0x3716, 0x83ED, WORD_LEN, 0 },
    { 0x3718, 0x576C, WORD_LEN, 0 },
    { 0x371A, 0x088D, WORD_LEN, 0 },
    { 0x371C, 0xDD8F, WORD_LEN, 0 },
    { 0x371E, 0x080C, WORD_LEN, 0 },
    { 0x3720, 0x950D, WORD_LEN, 0 },
    { 0x3722, 0xAE6E, WORD_LEN, 0 },
    { 0x3724, 0x08EF, WORD_LEN, 0 },
    { 0x3726, 0x0670, WORD_LEN, 0 },
    { 0x3740, 0xE86D, WORD_LEN, 0 },
    { 0x3742, 0x4E4E, WORD_LEN, 0 },
    { 0x3744, 0x2B92, WORD_LEN, 0 },
    { 0x3746, 0x5F2F, WORD_LEN, 0 },
    { 0x3748, 0x83D4, WORD_LEN, 0 },
    { 0x374A, 0x30A9, WORD_LEN, 0 },
    { 0x374C, 0x9CCD, WORD_LEN, 0 },
    { 0x374E, 0xD2AF, WORD_LEN, 0 },
    { 0x3750, 0xBF30, WORD_LEN, 0 },
    { 0x3752, 0xC872, WORD_LEN, 0 },
    { 0x3754, 0xCBAF, WORD_LEN, 0 },
    { 0x3756, 0x90B0, WORD_LEN, 0 },
    { 0x3758, 0x222B, WORD_LEN, 0 },
    { 0x375A, 0x3C72, WORD_LEN, 0 },
    { 0x375C, 0x11D1, WORD_LEN, 0 },
    { 0x375E, 0xAAAC, WORD_LEN, 0 },
    { 0x3760, 0x30D0, WORD_LEN, 0 },
    { 0x3762, 0x5EB0, WORD_LEN, 0 },
    { 0x3764, 0xF051, WORD_LEN, 0 },
    { 0x3766, 0xA4F3, WORD_LEN, 0 },
    { 0x3782, 0x00F0, WORD_LEN, 0 },
    { 0x3784, 0x0144, WORD_LEN, 0 },
    { 0x3210, 0x00B8, WORD_LEN, 0 },
    { 0x3210, 0x00B8, WORD_LEN, 0 },
	//AWB_CCM
    { 0x9416, 0x3895, WORD_LEN, 0 },
    { 0x9418, 0x1561, WORD_LEN, 0 },
    { 0x2110, 0x0024, WORD_LEN, 0 },
	//Load = Color Correction Matrices for AAC
    { 0xA02F, 0x0201, WORD_LEN, 0 },
    { 0xA031, 0xFEC9, WORD_LEN, 0 },
    { 0xA033, 0x0036, WORD_LEN, 0 },
    { 0xA035, 0xFFCB, WORD_LEN, 0 },
    { 0xA037, 0x0133, WORD_LEN, 0 },
    { 0xA039, 0x0001, WORD_LEN, 0 },
    { 0xA03B, 0xFFA4, WORD_LEN, 0 },
    { 0xA03D, 0xFF10, WORD_LEN, 0 },
    { 0xA03F, 0x024C, WORD_LEN, 0 },
    { 0xA041, 0x001B, WORD_LEN, 0 },
    { 0xA043, 0x004B, WORD_LEN, 0 },
    { 0xA045, 0xFFEC, WORD_LEN, 0 },
    { 0xA047, 0x008A, WORD_LEN, 0 },
    { 0xA049, 0xFF8A, WORD_LEN, 0 },
    { 0xA04B, 0xFFDD, WORD_LEN, 0 },
    { 0xA04D, 0x0044, WORD_LEN, 0 },
    { 0xA04F, 0xFFDF, WORD_LEN, 0 },
    { 0xA051, 0x0049, WORD_LEN, 0 },
    { 0xA053, 0x0071, WORD_LEN, 0 },
    { 0xA055, 0xFF46, WORD_LEN, 0 },
    { 0xA057, 0x0011, WORD_LEN, 0 },
    { 0xA059, 0xFFD8, WORD_LEN, 0 },
    { 0xA061, 0x003C, WORD_LEN, 0 },
    { 0xA063, 0x0035, WORD_LEN, 0 },
    { 0xA065, 0x0302, WORD_LEN, 0 },
    { 0x2112, 0x9C2B, WORD_LEN, 0 },
    { 0x2114, 0xF7D9, WORD_LEN, 0 },
    { 0x2116, 0x1FC9, WORD_LEN, 0 },
    { 0x2118, 0x2CA4, WORD_LEN, 0 },
    { 0x211A, 0xFB9A, WORD_LEN, 0 },
    { 0x211C, 0xDF46, WORD_LEN, 0 },
    { 0x211E, 0xCBEE, WORD_LEN, 0 },
    { 0x2120, 0x00C7, WORD_LEN, 0 },
    //Load = Color Correction for AAC
    { 0x098E, 0xA06D, WORD_LEN, 0 },
    { 0xA06D, 0x7400, WORD_LEN, 0 },
    { 0x098E, 0xA068, WORD_LEN, 0 },
    { 0xA068, 0x7080, WORD_LEN, 0 },
    //PA Settings
    { 0xA020, 0x4600, WORD_LEN, 0 },
    { 0xA07A, 0x0114, WORD_LEN, 0 },// 0x1114 0827 improve sharpness //FIH-SW3-MM-UW-fine tune+
    { 0xA081, 0x1E50, WORD_LEN, 0 },
    { 0xA0B1, 0x105A, WORD_LEN, 0 },
    { 0xA0B3, 0x105A, WORD_LEN, 0 },
    { 0xA0B5, 0x105A, WORD_LEN, 0 },
    { 0xA0B7, 0x1050, WORD_LEN, 0 },
    { 0xA05F, 0x9600, WORD_LEN, 0 },// 0x6400 0829 scott fine tune //FIH-SW3-MM-UW-fine tune+
    { 0xA0B9, 0x0028, WORD_LEN, 0 },
    { 0xA0BB, 0x0080, WORD_LEN, 0 },
    { 0xA085, 0x0008, WORD_LEN, 0 },
    { 0xA07C, 0x0701, WORD_LEN, 0 },// 0x0401 0829 improve sharpness //FIH-SW3-MM-UW-fine tune+
    //AE Settings
    { 0x9003, 0x2001, WORD_LEN, 0 },
    { 0xA027, 0x002A, WORD_LEN, 0 },
    { 0xA029, 0x0110, WORD_LEN, 0 },
    { 0xA01C, 0x0060, WORD_LEN, 0 },
    { 0xA023, 0x0080, WORD_LEN, 0 },
    { 0xA025, 0x0080, WORD_LEN, 0 },
    { 0xA01E, 0x0080, WORD_LEN, 0 },
    //CPIPE_Preference
    { 0x326E, 0x0006, WORD_LEN, 0 },
    { 0x33F4, 0x000B, WORD_LEN, 0 },
    { 0x35A2, 0x00B2, WORD_LEN, 0 },
    { 0x35A4, 0x0594, WORD_LEN, 0 },
    { 0xA087, 0x000D, WORD_LEN, 0 },
    { 0xA089, 0x223A, WORD_LEN, 0 },
    { 0xA08B, 0x5972, WORD_LEN, 0 },
    { 0xA08D, 0x8799, WORD_LEN, 0 },
    { 0xA08F, 0xA8B5, WORD_LEN, 0 },
    { 0xA091, 0xC1CB, WORD_LEN, 0 },
    { 0xA093, 0xD4DD, WORD_LEN, 0 },
    { 0xA095, 0xE5EC, WORD_LEN, 0 },
    { 0xA097, 0xF3F9, WORD_LEN, 0 },
    { 0xA099, 0xFF00, WORD_LEN, 0 },
    { 0xA0AD, 0x0003, WORD_LEN, 0 },
    { 0xA0AF, 0x0008, WORD_LEN, 0 },
    { 0x9003, 0x2001, WORD_LEN, 0 },
    { 0x8C00, 0x0201, WORD_LEN, 0 },
    { 0x8C03, 0x0103, WORD_LEN, 0 },
    { 0x8C05, 0x0500, WORD_LEN, 0 },
    { 0x329E, 0x0000, WORD_LEN, 0 },
    { 0x0018, 0x0002, WORD_LEN, 0 } // STANDBY_CONTROL_AND_STATUS
};
//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+}
/* MTD-SW-MM-SL-FinuTuneFrontCamera-00*} */

/*MM-UW-improve camera performance-00+*/
struct fih_i2c_reg_conf mt9v115_stream_start_array[] = {
    { 0x8400, 0x02, BYTE_LEN, 0 },
    { 0x8401, 0x02, BYTE_POLL, 0 }//State polling (start streaming)
};

struct fih_i2c_reg_conf mt9v115_stream_stop_array[] = {
    { 0x8400, 0x01, BYTE_LEN, 0 },
    { 0x8401, 0x01, BYTE_POLL, 0 }//State polling (1: stop streaming)
};
/*MM-UW-improve camera performance-00-*/

#if 1//FIH-SW-MM-MC-PortingNewSettingFor15And30FPS-00*{
struct fih_i2c_reg_conf mt9v115_fps_30_settings_array [] = {
    { 0x300A, 0x01F9, WORD_LEN, 0 },
    { 0x098E, 0x2076, WORD_LEN, 0 },
    { 0xA076, 0x0003, WORD_LEN, 0 },
    { 0xA078, 0x0004, WORD_LEN, 0 },
    { 0xA01A, 0x0003, WORD_LEN, 0 }
};

struct fih_i2c_reg_conf mt9v115_fps_15_settings_array [] = {
    { 0x300A, 0x03BE, WORD_LEN, 0 },
    { 0x098E, 0x2076, WORD_LEN, 0 },
    { 0xA076, 0x0006, WORD_LEN, 0 },
    { 0xA078, 0x0007, WORD_LEN, 0 },
    { 0xA01A, 0x0006, WORD_LEN, 0 }
};
#else
/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+{ */	
struct fih_i2c_reg_conf mt9v115_fps_30_settings_array [] = {
    { 0x300A, 0x01F9, WORD_LEN, 0 },
    { 0x300C, 0x02D6, WORD_LEN, 0 },
    { 0x3010, 0x0012, WORD_LEN, 0 },
    { 0x3040, 0x0041, WORD_LEN, 0 },
    { 0x9803, 0x07,   BYTE_LEN, 0 },
    { 0xA06E, 0x0098, WORD_LEN, 0 },
    { 0xA070, 0x007E, WORD_LEN, 0 },
    { 0xA072, 0x11,   BYTE_LEN, 0 },
    { 0xA073, 0x13,   BYTE_LEN, 0 },
    { 0xA074, 0x14,   BYTE_LEN, 0 },
    { 0xA075, 0x16,   BYTE_LEN, 0 },
    /* FIH-SW3-MM-SL-SetFPSForRecordMMS-02*{ */	
    { 0xA076, 0x0003, WORD_LEN, 0 },
    { 0xA078, 0x0004, WORD_LEN, 0 },
    { 0xA01A, 0x0003, WORD_LEN, 0 }
	/* FIH-SW3-MM-SL-SetFPSForRecordMMS-02*} */	
};

struct fih_i2c_reg_conf mt9v115_fps_15_settings_array [] = {
    { 0x300A, 0x03FA, WORD_LEN, 0 },
    { 0x300C, 0x02D6, WORD_LEN, 0 },
    { 0x3010, 0x0012, WORD_LEN, 0 },
    { 0x3040, 0x0041, WORD_LEN, 0 },
    { 0x9803, 0x07,   BYTE_LEN, 0 },
    { 0xA06E, 0x0098, WORD_LEN, 0 },
    { 0xA070, 0x007E, WORD_LEN, 0 },
    { 0xA072, 0x11,   BYTE_LEN, 0 },
    { 0xA073, 0x13,   BYTE_LEN, 0 },
    { 0xA074, 0x14,   BYTE_LEN, 0 },
    { 0xA075, 0x16,   BYTE_LEN, 0 },
    { 0xA076, 0x06,   BYTE_LEN, 0 },
    { 0xA078, 0x08,   BYTE_LEN, 0 },
    { 0xA01A, 0x06,   BYTE_LEN, 0 }
};
/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+} */	
#endif//FIH-SW-MM-MC-PortingNewSettingFor15And30FPS-00*}

struct mt9v115_reg mt9v115_regs = {
    .reg_init_tbl = mt9v115_init_settings_array,
    .reg_init_tbl_size = ARRAY_SIZE(mt9v115_init_settings_array),

    .reg_sub_init_tbl = mt9v115_sub_init_settings_array,//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+
    .reg_sub_init_tbl_size = ARRAY_SIZE(mt9v115_sub_init_settings_array),//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+

    .reg_start_tbl = mt9v115_stream_start_array,
    .reg_start_tbl_size = ARRAY_SIZE(mt9v115_stream_start_array),

    .reg_stop_tbl = mt9v115_stream_stop_array,
    .reg_stop_tbl_size = ARRAY_SIZE(mt9v115_stream_stop_array),

	/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+{ */	
	.reg_fps_15_tbl = mt9v115_fps_15_settings_array,
	.reg_fps_15_tbl_size = ARRAY_SIZE(mt9v115_fps_15_settings_array),

	.reg_fps_30_tbl = mt9v115_fps_30_settings_array,
	.reg_fps_30_tbl_size = ARRAY_SIZE(mt9v115_fps_30_settings_array),	
	/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01+} */    
};
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02+}
