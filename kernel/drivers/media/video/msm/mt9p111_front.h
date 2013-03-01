/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of Code Aurora Forum, Inc. nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

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
 */

#ifndef MT9P111_FRONT_H
#define MT9P111_FRONT_H
#include <linux/types.h>
#include <mach/board.h>

/* 16bit address - 8 bit context register structure */
struct reg_struct_type {
	uint16_t	reg_addr;
	uint16_t	reg_val;
	uint16_t	reg_type;
	uint16_t	timer;
};

enum mt9p111_front_test_mode_t {
	TEST_OFF,
	TEST_1,
	TEST_2,
	TEST_3
};

enum mt9p111_front_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};
#define MT9P111_FRONT_BRIGHTNESS_MAX 5
#define MT9P111_FRONT_WB_MAX 6
#define MT9P111_FRONT_EXPOSURE_MAX 3
#define MT9P111_FRONT_EFFECT_MAX 10

extern struct reg_struct_type mt9p111_front_init_settings_array[];
extern int32_t mt9p111_front_array_length;
extern struct reg_struct_type mt9p111_front_WB_Auto[];
extern struct reg_struct_type mt9p111_front_WB_Fluorescent[];
extern struct reg_struct_type mt9p111_front_WB_Incandescent[];
extern struct reg_struct_type mt9p111_front_WB_Cloudy[];
extern struct reg_struct_type mt9p111_front_WB_Daylight[];
extern struct reg_struct_type mt9p111_front_preview[];
extern struct reg_struct_type mt9p111_front_capture[];
extern struct reg_struct_type MT9P111_FRONT_effect_NONE[];
extern struct reg_struct_type MT9P111_FRONT_effect_MONO[];
extern struct reg_struct_type MT9P111_FRONT_effect_NEGATIVE[];
extern struct reg_struct_type MT9P111_FRONT_effect_SEPIA[];
extern struct reg_struct_type MT9P111_FRONT_effect_AQUA[];
extern struct reg_struct_type MT9P111_FRONT_effect_SKETCH[];
extern struct reg_struct_type *mt9p111_front_WB[MT9P111_FRONT_WB_MAX];
extern struct reg_struct_type *mt9p111_front_brightness[MT9P111_FRONT_BRIGHTNESS_MAX];
extern struct reg_struct_type *mt9p111_front_exposure[MT9P111_FRONT_EXPOSURE_MAX];
extern struct reg_struct_type *mt9p111_front_effect[MT9P111_FRONT_EFFECT_MAX];
#endif


