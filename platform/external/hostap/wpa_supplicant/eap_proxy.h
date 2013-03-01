/*
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

/* ALL QMI EAP functionality */
#ifndef EAP_PROXY_H
#define EAP_PROXY_H

#ifdef SIM_AKA_QUALCOMM

#include "eap_i.h"
#include "eloop.h"
#include "qmi.h"
#include "qmi_eap_srvc.h"
#include "eapol_supp_sm.h"

/*msec Response Timeout*/
#define QMI_RESP_TIME_OUT 300
#define EAP_PROXY_KEYING_DATA_LEN 64

typedef enum {
  QMI_STATE_IDLE = 0x00,
  QMI_STATE_RESP_PENDING  = 0x01,
  QMI_STATE_RESP_RECEIVED = 0x02,
  QMI_STATE_RESP_TIME_OUT = 0x03
} qmi_state_e ;

typedef enum {
  EAP_PROXY_QMI_SRVC_NO_RESULT,
  EAP_PROXY_QMI_SRVC_SUCCESS,
  EAP_PROXY_QMI_SRVC_FAILURE
} eap_proxy_qmi_srv_result ;

/* should match the EAP_state  of eap_i.h */
typedef enum {
 EAP_PROXY_INITIALIZE, EAP_PROXY_DISABLED, EAP_PROXY_IDLE, EAP_PROXY_RECEIVED,
 EAP_PROXY_GET_METHOD, EAP_PROXY_METHOD, EAP_PROXY_SEND_RESPONSE,
 EAP_PROXY_DISCARD, EAP_PROXY_IDENTITY, EAP_PROXY_NOTIFICATION,
 EAP_PROXY_RETRANSMIT,
 EAP_PROXY_AUTH_SUCCESS,  EAP_PROXY_AUTH_FAILURE
} eap_proxy_state ;


typedef enum {
   EAP_PROXY_FAILURE = 0x00,
   EAP_PROXY_SUCCESS
} eap_proxy_status ;

typedef struct eap_proxy_qmi_s {
   int qmihandle;
   int qmiTransactionId;
   qmi_state_e qmi_state;
   eap_proxy_qmi_srv_result srvc_result;
   qmi_eap_async_rsp_data_type qmi_resp_data;
   eap_proxy_state  proxy_state;
   Boolean iskey_valid;
   u8 *key;
   Boolean is_state_changed;
   void *ctx;
   struct eapol_callbacks *eapol_cb;
   u8 *eapReqData;
   size_t eapReqDataLen;
   Boolean isEap;
   int eap_type;
} eap_proxy_sm;


eap_proxy_sm
*eap_proxy_init(void *eapol_ctx, struct eapol_callbacks *eapol_cb);

void eap_proxy_deinit(eap_proxy_sm *eap_proxy);

int eap_proxy_key_available(eap_proxy_sm *sm);

const u8 *eap_proxy_get_eapKeyData(eap_proxy_sm *sm, size_t *len);

u8 *eap_proxy_get_eapRespData(eap_proxy_sm *sm, size_t *len);

int  eap_proxy_sm_step(eap_proxy_sm *sm, struct eap_sm *eap_sm);

eap_proxy_status
eap_proxy_packet_update(eap_proxy_sm *eap_proxy, u8 *eapReqData,
						int eapReqDataLen);

#ifdef CONFIG_CTRL_IFACE
int eap_proxy_sm_get_status(eap_proxy_sm *sm, char *buf, size_t buflen,
						int verbose);
#endif /* CONFIG_CTRL_IFACE */

#endif /* SIM_AKA_QUALCOMM */
#endif
