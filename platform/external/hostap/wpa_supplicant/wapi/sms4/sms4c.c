// Copyright (c) 2004-2010 Atheros Communications Inc.
// All rights reserved.
//
//
// The software source and binaries included in this development package are
// licensed, not sold. You, or your company, received the package under one
// or more license agreements. The rights granted to you are specifically
// listed in these license agreement(s). All other rights remain with Atheros
// Communications, Inc., its subsidiaries, or the respective owner including
// those listed on the included copyright notices.  Distribution of any
// portion of this package must be in strict compliance with the license
// agreement(s) terms.
// </copyright>
//
// <summary>
//	WAPI supplicant for AR6002
// </summary>
//
//
//
#include "sms4const.h"
//#define LE     // defined for byte-order
#define ENCRYPT  0     // Constant for encrypt
#define DECRYPT  1     // Constant for decrypt


// SMS4 encrypt/decrypt function
// Input: input data, Output: output result, rk: ring key
void SMS4Crypt(unsigned char *Input, unsigned char *Output, unsigned int *rk)
{
	 unsigned int r, mid, x0, x1, x2, x3, *p;
	 p = (unsigned int *)Input;
	 x0 = p[0];
	 x1 = p[1];
	 x2 = p[2];
	 x3 = p[3];

#ifdef LE
	 x0 = Rotl(x0, 16); x0 = ((x0 & 0x00FF00FF) << 8) ^ ((x0 & 0xFF00FF00) >> 8);
	 x1 = Rotl(x1, 16); x1 = ((x1 & 0x00FF00FF) << 8) ^ ((x1 & 0xFF00FF00) >> 8);
	 x2 = Rotl(x2, 16); x2 = ((x2 & 0x00FF00FF) << 8) ^ ((x2 & 0xFF00FF00) >> 8);
	 x3 = Rotl(x3, 16); x3 = ((x3 & 0x00FF00FF) << 8) ^ ((x3 & 0xFF00FF00) >> 8);
#endif
#if 0
#ifdef LE
	printf("-------LITTLE_ENDIAN-----------(in %s)\n", __func__);
	printf("x0 = %08x\n", x0);printf("x1 = %08x\n", x1);
	printf("x2 = %08x\n", x2);printf("x3 = %08x\n", x3);
#else
	printf("-------LITTLE_ENDIAN-----------(in %s)\n", __func__);
	printf("x0 = %08x\n", x0);printf("x1 = %08x\n", x1);
	printf("x2 = %08x\n", x2);printf("x3 = %08x\n", x3);
#endif
#endif
	 for (r = 0; r < 32; r += 4)
	 {
		  mid = x1 ^ x2 ^ x3 ^ rk[r + 0];
		  mid = ByteSub(mid);
		  x0 ^= L1(mid);
		  mid = x2 ^ x3 ^ x0 ^ rk[r + 1];
		  mid = ByteSub(mid);
		  x1 ^= L1(mid);
		  mid = x3 ^ x0 ^ x1 ^ rk[r + 2];
		  mid = ByteSub(mid);
		  x2 ^= L1(mid);
		  mid = x0 ^ x1 ^ x2 ^ rk[r + 3];
		  mid = ByteSub(mid);
		  x3 ^= L1(mid);
	 }
#ifdef LE
	 x0 = Rotl(x0, 16); x0 = ((x0 & 0x00FF00FF) << 8) ^ ((x0 & 0xFF00FF00) >> 8);
	 x1 = Rotl(x1, 16); x1 = ((x1 & 0x00FF00FF) << 8) ^ ((x1 & 0xFF00FF00) >> 8);
	 x2 = Rotl(x2, 16); x2 = ((x2 & 0x00FF00FF) << 8) ^ ((x2 & 0xFF00FF00) >> 8);
	 x3 = Rotl(x3, 16); x3 = ((x3 & 0x00FF00FF) << 8) ^ ((x3 & 0xFF00FF00) >> 8);
#endif
	 p = (unsigned int *)Output;
	 p[0] = x3;
	 p[1] = x2;
	 p[2] = x1;
	 p[3] = x0;
}

// SMS4 Key extension generator
// Key:encryption key, rk:private key, CryptFlag:encrypt/decrypt flag
void SMS4KeyExt(unsigned char *Key, unsigned int *rk, unsigned int CryptFlag)
{
	 unsigned int r, mid, x0, x1, x2, x3, *p;
	CryptFlag = CryptFlag;

	 p = (unsigned int *)Key;
	 x0 = p[0];
	 x1 = p[1];
	 x2 = p[2];
	 x3 = p[3];

#ifdef LE
	 x0 = Rotl(x0, 16); x0 = ((x0 & 0xFF00FF) << 8) ^ ((x0 & 0xFF00FF00) >> 8);
	 x1 = Rotl(x1, 16); x1 = ((x1 & 0xFF00FF) << 8) ^ ((x1 & 0xFF00FF00) >> 8);
	 x2 = Rotl(x2, 16); x2 = ((x2 & 0xFF00FF) << 8) ^ ((x2 & 0xFF00FF00) >> 8);
	 x3 = Rotl(x3, 16); x3 = ((x3 & 0xFF00FF) << 8) ^ ((x3 & 0xFF00FF00) >> 8);
#endif
#if 0
#ifdef LE
	printf("-------LITTLE_ENDIAN-----------(in %s)\n", __func__);
	printf("x0 = %08x\n", x0);printf("x1 = %08x\n", x1);
	printf("x2 = %08x\n", x2);printf("x3 = %08x\n", x3);
#else
	printf("-------LITTLE_ENDIAN-----------(in %s)\n", __func__);
	printf("x0 = %08x\n", x0);printf("x1 = %08x\n", x1);
	printf("x2 = %08x\n", x2);printf("x3 = %08x\n", x3);
#endif
#endif
	 x0 ^= 0xa3b1bac6;
	 x1 ^= 0x56aa3350;
	 x2 ^= 0x677d9197;
	 x3 ^= 0xb27022dc;
	 for (r = 0; r < 32; r += 4)
	 {
		  mid = x1 ^ x2 ^ x3 ^ CK[r + 0];
		#if 0
		  printf("mid1[%d]=%04x\n", r,mid);
		  printf("ByteSub(%d) (Sbox[(%d) >> 24 & 0xFF] << 24 ^ Sbox[(%d) >> 16 & 0xFF] << 16 ^ Sbox[(%d) >>  8 & 0xFF] <<  8 ^ Sbox[(%d) & 0xFF]\n",ByteSub(mid), mid, mid, mid, mid);
		#endif
		  mid = ByteSub(mid);
		  rk[r + 0] = x0 ^= L2(mid);
		  mid = x2 ^ x3 ^ x0 ^ CK[r + 1];
		  mid = ByteSub(mid);
		  rk[r + 1] = x1 ^= L2(mid);
		  mid = x3 ^ x0 ^ x1 ^ CK[r + 2];
		  mid = ByteSub(mid);
		  rk[r + 2] = x2 ^= L2(mid);
		  mid = x0 ^ x1 ^ x2 ^ CK[r + 3];
		  mid = ByteSub(mid);
		  rk[r + 3] = x3 ^= L2(mid);
	 }

#if 0
	 if (CryptFlag == DECRYPT)
	 {
		  for (r = 0; r < 16; r++)
			 mid = rk[r], rk[r] = rk[31 - r], rk[31 - r] = mid;
	 }
#endif
}
