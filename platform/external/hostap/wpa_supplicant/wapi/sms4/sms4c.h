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
#ifndef _SMS4C_H
#define _SMS4C_H
// SMS4 encrypt/decrypt function
// Input: input data, Output: output result, rk: ring key
void SMS4Crypt(unsigned char *Input, unsigned char *Output, unsigned int *rk);


// SMS4 Key extension generator
// Key:encryption key, rk:private key, CryptFlag:encrypt/decrypt flag
void SMS4KeyExt(unsigned char *Key, unsigned int *rk, unsigned int CryptFlag);


#endif
