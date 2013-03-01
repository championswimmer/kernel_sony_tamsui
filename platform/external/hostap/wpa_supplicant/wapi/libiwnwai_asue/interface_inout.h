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
// @file interface_inout.h
// @brief This header file contains data structures and function declarations of interface of this lib


#ifndef _INTERFACE_INOUT_H_
#define _INTERFACE_INOUT_H_

#ifdef  __cplusplus
extern "C" {
#endif


typedef enum
{
	AUTH_TYPE_NONE_WAPI = 0,	/*no WAPI	*/
	AUTH_TYPE_WAPI,			/*Certificate*/
	AUTH_TYPE_WAPI_PSK,		/*Pre-PSK*/
}AUTH_TYPE;

typedef enum
{
	KEY_TYPE_ASCII = 0,			/*ascii		*/
	KEY_TYPE_HEX,				/*HEX*/
}KEY_TYPE;

typedef struct
{
	AUTH_TYPE authType;		/*Authentication type*/
	union
	{
		struct
		{
			KEY_TYPE kt;				/*Key type*/
			unsigned int  kl;			/*key length*/
			unsigned char kv[128];/*value*/
		};
		struct
		{
			unsigned char as[2048];	/*ASU Certificate*/
			unsigned char user[2048];/*User Certificate*/
		};
	}para;
}CNTAP_PARA;

typedef enum
{
	CONN_ASSOC = 0,
	CONN_DISASSOC,
}CONN_STATUS;
typedef struct
{
	unsigned char v[6];
	unsigned char pad[2];
}MAC_ADDRESS;

/**
 * WAI_CNTAPPARA_SET - Set WIE to driver
 * @CNTAP_PARA: Pointer to  struct CNTAP_PARA
 * Returns: 0 on success, -1 on failure
 *
 * set WIE to driver
 *
 */
int WAI_CNTAPPARA_SET(const CNTAP_PARA* pPar);

void WAI_Msg_Input(CONN_STATUS action, const MAC_ADDRESS* pBSSID, const MAC_ADDRESS* pLocalMAC, unsigned char *assoc_ie, unsigned char assoc_ie_len);

unsigned long WAI_RX_packets_indication(const u8* pbuf, int length);

int WIFI_lib_init();

int WIFI_lib_exit();


int lib_get_wapi_state(void);



typedef void (*OS_timer_expired)(const int pdata);
void* OS_timer_setup(int deltaTimer, int repeated, OS_timer_expired pfunction, const void* pdata);
void OS_timer_clean(void* pTimer);
void WIFI_Action_Deauth();
unsigned long WIFI_TX_packet(const char* pbuf, int length);
int WIFI_unicast_key_set(const char* pKeyValue, int keylength, int key_idx);
int WIFI_group_key_set(const unsigned char* pKeyValue, int keylength, int key_idx, const unsigned char* keyIV);
int WIFI_WAI_IE_set(const unsigned char* pbuf, int length);
unsigned char WIFI_get_rand_byte();

#ifdef  __cplusplus
}
#endif

#endif /* _INTERFACE_INOUT_H_  */
