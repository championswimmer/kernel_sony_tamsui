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

#ifndef S5K5CA_H
#define S5K5CA_H
#include <linux/types.h>
#include <mach/board.h>

/* 16bit address - 8 bit context register structure */
struct reg_struct_type {
	uint16_t	reg_addr;
	uint16_t	reg_val;
	uint16_t	reg_type;
	uint16_t	timer;
};

enum s5k5ca_test_mode_t {
	TEST_OFF,
	TEST_1,
	TEST_2,
	TEST_3
};

enum s5k5ca_resolution_t {
	QTR_SIZE,
	FULL_SIZE,
	INVALID_SIZE
};
#define S5K5CA_BRIGHTNESS_MAX 5
#define S5K5CA_WB_MAX 6
#define S5K5CA_EXPOSURE_MAX 3
#define S5K5CA_EFFECT_MAX 10
#define S5K5CA_ISO_MAX 8
#define S5K5CA_SCENE_MAX 19
#define S5K5CA_FPS_MAX 2

extern struct reg_struct_type *s5k5ca_init_settings_array;
extern struct reg_struct_type s5k5ca_truly_init_array[];
extern struct reg_struct_type s5k5ca_mcnex_init_array[];

extern struct reg_struct_type s5k5ca_WB_Auto[];
extern struct reg_struct_type s5k5ca_WB_Fluorescent[];
extern struct reg_struct_type s5k5ca_WB_Incandescent[];
extern struct reg_struct_type s5k5ca_WB_Cloudy[];
extern struct reg_struct_type s5k5ca_WB_Daylight[];
extern struct reg_struct_type s5k5ca_preview[];
extern struct reg_struct_type s5k5ca_capture[];
extern struct reg_struct_type s5k5ca_capture_Night_Mode[];
extern struct reg_struct_type S5K5CA_effect_NONE[];
extern struct reg_struct_type S5K5CA_effect_MONO[];
extern struct reg_struct_type S5K5CA_effect_NEGATIVE[];
extern struct reg_struct_type S5K5CA_effect_SEPIA[];
extern struct reg_struct_type S5K5CA_effect_AQUA[];
extern struct reg_struct_type S5K5CA_effect_SKETCH[];
extern struct reg_struct_type *s5k5ca_WB[S5K5CA_WB_MAX];
extern struct reg_struct_type *s5k5ca_brightness[S5K5CA_BRIGHTNESS_MAX];
extern struct reg_struct_type *s5k5ca_exposure[S5K5CA_EXPOSURE_MAX];
extern struct reg_struct_type *s5k5ca_effect[S5K5CA_EFFECT_MAX];
extern struct reg_struct_type *s5k5ca_iso[S5K5CA_ISO_MAX];
extern struct reg_struct_type *s5k5ca_scene[S5K5CA_SCENE_MAX];
extern struct reg_struct_type *s5k5ca_fps[S5K5CA_FPS_MAX];
#endif

