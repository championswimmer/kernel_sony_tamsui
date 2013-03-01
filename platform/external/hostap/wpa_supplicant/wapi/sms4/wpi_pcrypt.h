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
#ifndef _WAPI_PCRYPT_H
#define _WAPI_PCRYPT_H
int wpi_encrypt(unsigned char * pofbiv_in,
				unsigned char * pbw_in,
				unsigned int plbw_in,
				unsigned char * pkey,
				unsigned char * pcw_out);

int wpi_decrypt(unsigned char * pofbiv_in,
				unsigned char * pcw_in,
				unsigned int plcw_in,
				unsigned char * prkey_in,
				unsigned char * pbw_out);

int wpi_pmac(unsigned char * pmaciv_in,
				unsigned char * pmac_in,
				unsigned int pmacpc_in,
				unsigned char * pkey,
				unsigned char * pmac_out);

#endif
