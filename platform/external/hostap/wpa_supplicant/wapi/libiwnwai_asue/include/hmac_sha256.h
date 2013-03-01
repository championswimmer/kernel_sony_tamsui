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
// @file hmac_sha256.h
// @brief This header file contains data structures and function declarations of sha256&hmac

#ifndef _SHA256_H_
#define _SHA256_H_

int mhash_sha256(unsigned char* data, unsigned length, unsigned char* digest);
int ecc_hmac_sha256(unsigned char* t, int tl, unsigned char* k, unsigned kl, unsigned char* o, unsigned ol);
void KD_hmac_sha256(unsigned char* text, unsigned text_len, unsigned char* key, unsigned key_len, unsigned char* output, unsigned length);

#define hmac_sha256(_t, _tl, _k, _kl, _d, _dl) \
    ecc_hmac_sha256(_t, _tl, _k, _kl, _d, _dl)

#endif /* _SHA256_H_ */
