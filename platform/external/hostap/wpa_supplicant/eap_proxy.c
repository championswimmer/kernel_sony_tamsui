/*
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary
 */

/* ALL QMI EAP functionality */
#ifdef SIM_AKA_QUALCOMM

#include "includes.h"
#include "common.h"
#include "qmi_uim_srvc.h"
#include "qmi_client.h"
#include "qmi_idl_lib.h"
#include "user_identity_module_v01.h"
#include "eap_proxy.h"
#include "eap_config.h"

#define IMSI_LENGTH 15
#define WPA_UIM_QMI_EVENT_MASK_CARD_STATUS        \
					(1 << QMI_UIM_EVENT_CARD_STATUS_BIT_V01)
#define WPA_UIM_QMI_EVENT_READ_TRANSPARENT_REQ    \
					(1 << QMI_UIM_READ_TRANSPARENT_REQ_V01)

/* Default timeout (in milli-seconds) for synchronous QMI message */
#define WPA_UIM_QMI_DEFAULT_TIMEOUT               10000

#ifdef SIM_AKA_IDENTITY_IMSI
typedef struct
{
  uim_card_state_enum_v01			card_state;
  uim_card_error_code_enum_v01			card_error_code;
  u8						app_state;
  u8						app_type;
} wpa_uim_card_info_type;

typedef struct
{
  int                                   card_ready_idx;
  wpa_uim_card_info_type                card_info[QMI_UIM_CARDS_MAX_V01];
  qmi_client_type                       qmi_uim_svc_client_ptr;
  int                                   qmi_msg_lib_handle;
} wpa_uim_struct_type;

/* Global variable with the card status */
wpa_uim_struct_type   wpa_uim;
#endif /* SIM_AKA_IDENTITY_IMSI */


static int eap_proxy_qmi_init_handle;
static qmi_client_type qmi_uim_svc_client_ptr;
static int eap_auth_session_flag = FALSE;

static void eap_proxy_eapol_sm_set_bool(eap_proxy_sm *sm,
			 enum eapol_bool_var var, Boolean value);
static Boolean eap_proxy_eapol_sm_get_bool(eap_proxy_sm *sm,
					enum eapol_bool_var var);

/* Call-back function to process an authenticationr result indication from
 * QMI EAP service */
static void handle_qmi_eap_ind(int userHandle, qmi_service_id_type serviceId,
			void *userData, qmi_eap_indication_id_type indId,
					qmi_eap_indication_data_type *indData);

static void handle_qmi_resp_timeout(void *eloop_ctx, void *timeout_ctx);

/* Call-back function to process an EAP response from QMI EAP service */
static void handle_qmi_eap_reply(int userHandle, qmi_service_id_type serviceId,
			int sysErrCode, int qmiErrCode, void *userData,
	qmi_eap_async_rsp_id_type rspId, qmi_eap_async_rsp_data_type *rspData);

static u8 *eap_proxy_getKey(eap_proxy_sm *eap_proxy);
static eap_proxy_status eap_proxy_qmi_response_wait(eap_proxy_sm *eap_proxy);
static int eap_proxy_is_state_changed(eap_proxy_sm *sm);
static eap_proxy_status eap_proxy_process(eap_proxy_sm  *eap_proxy,
					u8 *eapReqData, int eapReqDataLen, struct eap_sm *eap_sm);
static char bin_to_hexchar(u8 ch);

static void wpa_qmi_client_indication_cb
(
	qmi_client_type                user_handle,
	unsigned long                  msg_id,
	unsigned char                 *ind_buf_ptr,
	int                            ind_buf_len,
	void                          *ind_cb_data
);
static void dump_buff(u8 *buff, int len);
#ifdef CONFIG_CTRL_IFACE
static const char *eap_proxy_sm_state_txt(int state);
#endif /* CONFIG_CTRL_IFACE */
static Boolean eap_proxy_build_identity(eap_proxy_sm *eap_proxy, u8 id);

#ifdef SIM_AKA_IDENTITY_IMSI
static char *imsi;
static int card_mnc_len = -1;

static Boolean wpa_qmi_register_events();
static Boolean wpa_qmi_read_card_imsi();
static Boolean wpa_qmi_read_card_status();

#endif
#define EAP_SUB_TYPE_SIM_START     0x0a
#define EAP_SUB_TYPE_AKA_IDENTITY  0x05
#define EAP_RESP_TYPE_NAK             3

/* Call-back function to process QMI system events */
void handle_qmi_sys_events(qmi_sys_event_type  eventId,
const qmi_sys_event_info_type *eventInfo, void *userData)
{

/*  Based on the qmi sys events we need to update our qmi and eap states.*/
	wpa_printf(MSG_INFO, "handleQmiSysEvent\n");
	wpa_printf(MSG_INFO, "Event Id=%d;\n", eventId);
}

#ifdef SIM_AKA_IDENTITY_IMSI
static void wpa_qmi_client_indication_cb
(
	qmi_client_type                user_handle,
	unsigned long                  msg_id,
	unsigned char                 *ind_buf_ptr,
	int                            ind_buf_len,
	void                          *ind_cb_data
)
{
	/* we currently not need the card status changes */
	/* Making this a dummy CB handler */
}

static Boolean wpa_qmi_register_events()
{
	qmi_client_error_type               qmi_err_code      = 0;
	uim_get_card_status_resp_msg_v01   *qmi_response_ptr  = NULL;
	uim_event_reg_req_msg_v01           event_reg_params;

	qmi_response_ptr = (uim_get_card_status_resp_msg_v01 *)
			os_malloc(sizeof(uim_get_card_status_resp_msg_v01));
	if (qmi_response_ptr == NULL) {
		wpa_printf(MSG_ERROR,
			"Couldn't allocate memory for qmi_response_ptr\n");
		return FALSE;
	}

	/* Register for events first */
	os_memset(qmi_response_ptr, 0,
			sizeof(uim_get_card_status_resp_msg_v01));
	os_memset(&event_reg_params, 0, sizeof(uim_event_reg_req_msg_v01));

	event_reg_params.event_mask |= (WPA_UIM_QMI_EVENT_MASK_CARD_STATUS);

	qmi_err_code = qmi_client_send_msg_sync(wpa_uim.qmi_uim_svc_client_ptr,
						QMI_UIM_EVENT_REG_REQ_V01,
						(void *) &event_reg_params,
						sizeof(uim_event_reg_req_msg_v01),
						(void *) qmi_response_ptr,
						sizeof(*qmi_response_ptr),
						WPA_UIM_QMI_DEFAULT_TIMEOUT);
	wpa_printf(MSG_ERROR, " QMI_UIM_EVENT_REG_REQ_V01, qmi_err_code: %d\n",
				qmi_err_code);
	if (qmi_err_code != QMI_NO_ERR) {
		wpa_printf(MSG_ERROR,
			"Error for QMI_UIM_EVENT_REG_REQ_V01, qmi_err_code: 0x%x\n",
			qmi_err_code);
		free(qmi_response_ptr);
		return FALSE;
	}
	/* Free the allocated response buffer */
	if (qmi_response_ptr)
	{
		free(qmi_response_ptr);
		qmi_response_ptr = NULL;
	}

	if (wpa_qmi_read_card_status())
		return TRUE;
	else {
		wpa_printf(MSG_ERROR,
				"Error while reading SIM card status\n");
		return FALSE;
	}
}

static Boolean wpa_qmi_read_card_status()
{
	unsigned int                        i = 0, j = 0;
	Boolean                             card_found = FALSE;
	qmi_client_error_type               qmi_err_code      = 0;
	uim_get_card_status_resp_msg_v01   *qmi_response_ptr  = NULL;

	qmi_response_ptr = (uim_get_card_status_resp_msg_v01 *)
		os_malloc(sizeof(uim_get_card_status_resp_msg_v01));
	if (qmi_response_ptr == NULL) {
		wpa_printf(MSG_ERROR,
			"Couldn't allocate memory for qmi_response_ptr !\n");
		return FALSE;
	}

	os_memset(qmi_response_ptr,
				0,
				sizeof(uim_get_card_status_resp_msg_v01));
	qmi_err_code = qmi_client_send_msg_sync(wpa_uim.qmi_uim_svc_client_ptr,
						QMI_UIM_GET_CARD_STATUS_REQ_V01,
						NULL,
						0,
						(void *) qmi_response_ptr,
						sizeof(*qmi_response_ptr),
						WPA_UIM_QMI_DEFAULT_TIMEOUT);
	wpa_printf(MSG_ERROR, "QMI_UIM_GET_CARD_STATUS_REQ_V01, qmi_err_code: %d\n",
		   qmi_err_code);
	if (qmi_err_code != QMI_NO_ERR) {
		wpa_printf(MSG_ERROR,
			"Error for QMI_UIM_GET_CARD_STATUS_REQ_V01, qmi_err_code: 0x%x\n",
			qmi_err_code);
		free(qmi_response_ptr);
		return FALSE;
	}

	/* Updated global card status if needed */
	if (!qmi_response_ptr->card_status_valid ||
	  (qmi_response_ptr->resp.result != QMI_RESULT_SUCCESS_V01)) {
		wpa_printf(MSG_ERROR, "card_status is not valid !\n");
		free(qmi_response_ptr);
		return FALSE;
	}
	/* Update global in case of new card state or error code */
	for (i = 0;
		i < QMI_UIM_CARDS_MAX_V01 &&
		i < qmi_response_ptr->card_status.card_info_len; i++) {
		wpa_printf(MSG_ERROR, "card_info[i].card_state: 0x%x\n",
			qmi_response_ptr->card_status.card_info[i].card_state);
		wpa_printf(MSG_ERROR, "card_info[i].error_code: 0x%x\n",
			qmi_response_ptr->card_status.card_info[i].error_code);

		wpa_uim.card_info[i].card_state =
			qmi_response_ptr->card_status.card_info[i].card_state;

		wpa_uim.card_info[i].card_error_code =
			qmi_response_ptr->card_status.card_info[i].error_code;


		if (qmi_response_ptr->card_status.card_info[i].card_state ==
			UIM_CARD_STATE_PRESENT_V01) {
			for (j = 0 ; j < QMI_UIM_APPS_MAX_V01 ; j++) {
				wpa_uim.card_info[i].app_type =
					qmi_response_ptr->card_status.card_info[i].app_info[j].app_type;

				wpa_uim.card_info[i].app_state =
					qmi_response_ptr->card_status.card_info[i].app_info[j].app_state;

				if (((qmi_response_ptr->card_status.card_info[i].app_info[j].app_type == 1) ||
				(qmi_response_ptr->card_status.card_info[i].app_info[j].app_type == 2)) &&
				(qmi_response_ptr->card_status.card_info[i].app_info[j].app_state ==
				UIM_APP_STATE_READY_V01)) {
					wpa_printf(MSG_ERROR, "card READY\n");
					wpa_printf(MSG_ERROR, "card_info[i].app_type : 0x%x\n",
					qmi_response_ptr->card_status.card_info[i].app_info[j].app_type);
					wpa_printf(MSG_ERROR, "card_info[i].app_state : 0x%x\n",
					qmi_response_ptr->card_status.card_info[i].app_info[j].app_state);
					card_found = TRUE;
					break;
				}
			}
		}

		if (card_found) {
			wpa_printf(MSG_ERROR, "card found\n");
			break;
		}
	}

	if ((!card_found) || (i ==QMI_UIM_CARDS_MAX_V01) ||
		(j == QMI_UIM_APPS_MAX_V01)) {
		if (qmi_response_ptr) {
			free(qmi_response_ptr);
			qmi_response_ptr = NULL;
		}
		wpa_printf(MSG_ERROR, "SIM/USIM not ready\n");
		return FALSE;
	}

	wpa_uim.card_ready_idx = i;

	/* Free the allocated response buffer */
	if (qmi_response_ptr) {
		free(qmi_response_ptr);
		qmi_response_ptr = NULL;
	}

	return TRUE;
} /* wpa_qmi_read_card_status */

static Boolean wpa_qmi_read_card_imsi()
{
	int									length;
	unsigned char                      *data;
	int                                 src  = 0, dst  = 0;
	Boolean                             card_found = FALSE,
										qmi_status = TRUE;
	qmi_client_error_type               qmi_err_code      = 0;
	uim_read_transparent_req_msg_v01   *qmi_read_trans_req_ptr = NULL;
	uim_read_transparent_resp_msg_v01  *qmi_read_trans_resp_ptr = NULL;

	qmi_read_trans_req_ptr = (uim_read_transparent_req_msg_v01 *)
					os_malloc(sizeof(uim_read_transparent_req_msg_v01));
	if (qmi_read_trans_req_ptr == NULL) {
		wpa_printf(MSG_ERROR,
			"Couldn't allocate memory for qmi_read_trans_req_ptr !\n");
		return FALSE;
	}
	qmi_read_trans_resp_ptr = (uim_read_transparent_resp_msg_v01 *)
					os_malloc(sizeof(uim_read_transparent_resp_msg_v01));
	if (qmi_read_trans_resp_ptr == NULL) {
		wpa_printf(MSG_ERROR,
			"Couldn't allocate memory for qmi_read_trans_resp_ptr !\n");

		if (qmi_read_trans_req_ptr) {
			free(qmi_read_trans_req_ptr);
			qmi_read_trans_req_ptr = NULL;
		}
		return FALSE;
	}

	os_memset(qmi_read_trans_resp_ptr, 0,
			sizeof(uim_read_transparent_resp_msg_v01));
	os_memset(qmi_read_trans_req_ptr, 0,
			sizeof(uim_read_transparent_req_msg_v01));

	qmi_read_trans_req_ptr->read_transparent.length = 0;
	qmi_read_trans_req_ptr->read_transparent.offset = 0;
	qmi_read_trans_req_ptr->file_id.file_id = 0x6F07;
	qmi_read_trans_req_ptr->file_id.path_len = 4;
	qmi_read_trans_req_ptr->session_information.session_type =
				QMI_UIM_SESSION_TYPE_PRI_GW_PROV;
	qmi_read_trans_req_ptr->session_information.aid_len = 0;

	/* For USIM*/
	if ((wpa_uim.card_info[wpa_uim.card_ready_idx].app_type ==
		UIM_APP_TYPE_USIM_V01)) {
		qmi_read_trans_req_ptr->file_id.path[0] = 0x00;
		qmi_read_trans_req_ptr->file_id.path[1] = 0x3F;
		qmi_read_trans_req_ptr->file_id.path[2] = 0xFF;
		qmi_read_trans_req_ptr->file_id.path[3] = 0x7F;

	} else /* For SIM*/
	if ((wpa_uim.card_info[wpa_uim.card_ready_idx].app_type ==
		UIM_APP_TYPE_SIM_V01)) {
		qmi_read_trans_req_ptr->file_id.path[0] = 0x00;
		qmi_read_trans_req_ptr->file_id.path[1] = 0x3F;
		qmi_read_trans_req_ptr->file_id.path[2] = 0x20;
		qmi_read_trans_req_ptr->file_id.path[3] = 0x7F;
	}
	else {
		if (qmi_read_trans_req_ptr) {
			free(qmi_read_trans_req_ptr);
			qmi_read_trans_req_ptr = NULL;
		}
		if (qmi_read_trans_resp_ptr) {
			free(qmi_read_trans_resp_ptr);
			qmi_read_trans_resp_ptr = NULL;
		}
		return FALSE;
	}

	qmi_err_code = qmi_client_send_msg_sync(wpa_uim.qmi_uim_svc_client_ptr,
					QMI_UIM_READ_TRANSPARENT_REQ_V01,
					(void *)qmi_read_trans_req_ptr,
					sizeof(*qmi_read_trans_req_ptr),
					(void *) qmi_read_trans_resp_ptr,
					sizeof(*qmi_read_trans_resp_ptr),
					WPA_UIM_QMI_DEFAULT_TIMEOUT);

	if (QMI_NO_ERR == qmi_err_code) {
		if (qmi_read_trans_resp_ptr->read_result_valid) {
			length = qmi_read_trans_resp_ptr->read_result.content_len;
			data = qmi_read_trans_resp_ptr->read_result.content;

			/* Received IMSI is in the 3GPP format
			   converting it into ascii string */
			imsi = os_malloc((2 * length));
			os_memset(imsi, 0, (2 * length));
			for (src = 1, dst = 0;
					(src <= length) && (dst < (length * 2));
					src++) {
				if (src > 1) {
					imsi[dst] = bin_to_hexchar(data[src] & 0x0F);
					dst++;
				}
				/* Process upper part of byte for all bytes */
				imsi[dst] = bin_to_hexchar(data[src] >> 4);
				dst++;
			}
		} else {
			wpa_printf(MSG_ERROR,
					"IMSI read failure read_result_valid = %d\n",
					qmi_read_trans_resp_ptr->read_result_valid);
			qmi_status = FALSE;
		}
	} else {
		wpa_printf(MSG_ERROR,
				"Unable to read IMSI from UIM service qmi_err_code=%x\n",
				qmi_err_code);
		qmi_status = FALSE;
	}

	/* READ EF_AD */
	/* if qmi_status is FALSE, UIM read for mnc may not be required - To Do */
	qmi_read_trans_req_ptr->file_id.file_id = 0x6FAD;
	qmi_err_code = qmi_client_send_msg_sync(wpa_uim.qmi_uim_svc_client_ptr,
					QMI_UIM_READ_TRANSPARENT_REQ_V01,
					(void *)qmi_read_trans_req_ptr,
					sizeof(*qmi_read_trans_req_ptr),
					(void *) qmi_read_trans_resp_ptr,
					sizeof(*qmi_read_trans_resp_ptr),
					WPA_UIM_QMI_DEFAULT_TIMEOUT);
	if (QMI_NO_ERR == qmi_err_code) {
		if (qmi_read_trans_resp_ptr->read_result_valid) {
			length  =
				qmi_read_trans_resp_ptr->read_result.content_len;
			data    =
				qmi_read_trans_resp_ptr->read_result.content;

			card_mnc_len = data[3];
		}
	}
	else{
		qmi_status = FALSE;
		wpa_printf(MSG_ERROR,
					"MNC read failed=%x\n",qmi_err_code);
	}

	/* Free the allocated read request buffer */
	if (qmi_read_trans_req_ptr) {
		free(qmi_read_trans_req_ptr);
		qmi_read_trans_req_ptr = NULL;
	}

	/* Free the allocated read response buffer */
	if (qmi_read_trans_resp_ptr) {
		free(qmi_read_trans_resp_ptr);
		qmi_read_trans_resp_ptr = NULL;
	}
	return qmi_status;
} /* wpa_qmi_read_card_imsi */
#endif /* SIM_AKA_IDENTITY_IMSI */

eap_proxy_sm *eap_proxy_init(void *eapol_ctx, struct eapol_callbacks *eapol_cb)
{
	int qmiErrorCode;
	int qmiRetCode;
	eap_proxy_sm *eap_proxy;
	qmi_idl_service_object_type    qmi_client_service_obj;

	eap_proxy =  os_malloc(sizeof(eap_proxy_sm));
	if (NULL == eap_proxy) {
		wpa_printf(MSG_ERROR, "Error memory alloc  for eap_proxy"
						"eap_proxy_init\n");
		return NULL;
	}
	os_memset(eap_proxy, 0, sizeof(*eap_proxy));

	eap_proxy->ctx = eapol_ctx;
	eap_proxy->eapol_cb = eapol_cb;
	eap_proxy->proxy_state = EAP_PROXY_INITIALIZE;
	eap_proxy->qmi_state = QMI_STATE_IDLE;
	eap_proxy->key = NULL;
	eap_proxy->iskey_valid = FALSE;
	eap_proxy->is_state_changed = FALSE;
	eap_proxy->isEap = FALSE;
	eap_proxy->eap_type = EAP_TYPE_NONE;

	/* initialize QMI */
	eap_proxy_qmi_init_handle = qmi_init(handle_qmi_sys_events, NULL);
	if (eap_proxy_qmi_init_handle < 0) {
		wpa_printf(MSG_ERROR, "Error in qmi_init\n");
		os_free(eap_proxy);
		return NULL;
	}

	/* initialize the QMI connection */
	qmiRetCode = qmi_dev_connection_init(QMI_PORT_RMNET_1, &qmiErrorCode);
	if (QMI_NO_ERR != qmiRetCode) {
		wpa_printf(MSG_ERROR, "Error in qmi_connection_init\n");
		os_free(eap_proxy);
		return NULL;
	}

	/* initialize the QMI EAP Service */
	eap_proxy->qmihandle = qmi_eap_srvc_init_client(QMI_PORT_RMNET_1,
							&handle_qmi_eap_ind,
							eap_proxy, &qmiErrorCode);

	if (0 > eap_proxy->qmihandle) {
		wpa_printf(MSG_ERROR, "Unable to initialize service client;"
					" error_ret=%d; error_code=%d\n",
					eap_proxy->qmihandle, qmiErrorCode);
		os_free(eap_proxy);
		return NULL;
	}

#ifdef SIM_AKA_IDENTITY_IMSI
	/* Init QMI_UIM service for EAP-SIM/AKA */
	qmi_client_service_obj = uim_get_service_object_v01();
	qmiErrorCode = qmi_client_init(QMI_PORT_RMNET_1,
							qmi_client_service_obj,
							wpa_qmi_client_indication_cb,
							qmi_client_service_obj,
							&wpa_uim.qmi_uim_svc_client_ptr);
		if ((wpa_uim.qmi_uim_svc_client_ptr == NULL) ||
			(qmiErrorCode > 0)) {
			wpa_printf(MSG_ERROR,
				"Could not register with QMI UIM Service,"
				"qmi_uim_svc_client_ptr: %p,qmi_err_code: %d\n",
				wpa_uim.qmi_uim_svc_client_ptr, qmiErrorCode);
				wpa_uim.qmi_uim_svc_client_ptr = NULL;
			os_free(eap_proxy);
			return NULL;
		}

	/* Read IMSI value from card */
	wpa_qmi_register_events();
#endif /* SIM_AKA_IDENTITY_IMSI */

	eap_proxy->proxy_state = EAP_PROXY_IDLE;
	eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapSuccess, FALSE);
	eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapFail, FALSE);
	eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapRestart, FALSE);
	eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapResp, FALSE);
	eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapNoResp, FALSE);

	return eap_proxy;
}


void eap_proxy_deinit(eap_proxy_sm *eap_proxy)
{
	int qmiRetCode;
	int qmiErrorCode;

	if (NULL == eap_proxy)
		return;

	eap_proxy->proxy_state = EAP_PROXY_DISABLED;

		if (TRUE == eap_auth_session_flag) {
			/* end the current EAP session */
			qmiRetCode = qmi_eap_auth_end_eap_session(
						eap_proxy->qmihandle,
						&qmiErrorCode);
			if (QMI_NO_ERR != qmiRetCode) {
				wpa_printf(MSG_ERROR, "Unable to end the EAP session;"
						" error_ret=%d; error_code=%d\n",
						qmiRetCode, qmiErrorCode);
			} else {
				wpa_printf(MSG_ERROR, "Ended the QMI EAP session\n");
				eap_auth_session_flag = FALSE;
			}
		}
	if (NULL != eap_proxy->key)
		os_free(eap_proxy->key);

	/* Release QMI */
	qmi_release(eap_proxy_qmi_init_handle);

	eap_proxy->iskey_valid = FALSE;
	eap_proxy->is_state_changed = FALSE;

	os_free(eap_proxy);
	eap_proxy = NULL;
	wpa_printf(MSG_INFO, "eap_proxy Deinitialzed\n");
}

/* Call-back function to process an authentication result indication
*  from QMI EAP service */
static void handle_qmi_eap_ind
(
	int userHandle, qmi_service_id_type serviceId,
	void *userData, qmi_eap_indication_id_type indId,
	qmi_eap_indication_data_type *indData
)
{
	eap_proxy_sm *sm = (eap_proxy_sm *)userData;

	if (NULL == sm || (QMI_EAP_SERVICE != serviceId)) {
		wpa_printf(MSG_ERROR, "Bad param: serviceId=%d\n", serviceId);
		return;
	}

	if (sm->qmihandle != userHandle) {
		wpa_printf(MSG_ERROR, "User handle is invalid: cached=%d;"
				" given=%d\n", sm->qmihandle, userHandle);
		return;
	}

	switch (indId) {
	case QMI_EAP_SRVC_INVALID_IND_MSG:
		sm->srvc_result = EAP_PROXY_QMI_SRVC_FAILURE;
		break;

	case QMI_EAP_SRVC_SESSION_RESULT_IND_MSG:
		if (NULL != indData) {
			sm->srvc_result = EAP_PROXY_QMI_SRVC_SUCCESS;
		} else {
			wpa_printf(MSG_ERROR, "Receving a NULL auth result\n");
			sm->srvc_result = EAP_PROXY_QMI_SRVC_FAILURE;
		}
		break;

	default:
		wpa_printf(MSG_ERROR, "An unexpected indication Id=%d"
							" is given\n", indId);
	break;
	}
	return;
}


static void handle_qmi_resp_timeout(void *eloop_ctx, void *timeout_ctx)
{
	eap_proxy_sm *eap_proxy = (eap_proxy_sm *)timeout_ctx;
	wpa_printf(MSG_ERROR, "handle_qmi_resp_timeout\n");
	eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
	wpa_printf(MSG_ERROR,
		"handle_qmi_resp_timeout !QMI STATE %d TIME_OUT\n",
		eap_proxy->qmi_state);

}


/* Call-back function to process an EAP response from QMI EAP service */
static void handle_qmi_eap_reply(
	int userHandle, qmi_service_id_type serviceId, int sysErrCode,
	int qmiErrCode, void *userData, qmi_eap_async_rsp_id_type rspId,
	qmi_eap_async_rsp_data_type *rspData
)
{
	eap_proxy_sm *eap_proxy = (eap_proxy_sm *)userData;
	u8 *resp_data;
	u32 length;

	if (QMI_STATE_RESP_PENDING == eap_proxy->qmi_state) {
		/*First Cancel the Timer*/
		eloop_cancel_timeout(handle_qmi_resp_timeout, NULL, eap_proxy);

		if (NULL == eap_proxy || QMI_EAP_SERVICE != serviceId ||
				QMI_EAP_SEND_EAP_PKT_RSP_ID != rspId) {
			wpa_printf(MSG_ERROR, "Bad Param: serviceId=%d;"
				 " rspId=%d\n", serviceId, rspId);
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
			return;
		}

		if (eap_proxy->qmihandle != userHandle) {
			wpa_printf(MSG_ERROR, "User handle is invalid:"
				 " cached=%d; given=%d\n", eap_proxy->qmihandle,
								 userHandle);
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
			return;
		}

		if (QMI_NO_ERR != sysErrCode) {
			wpa_printf(MSG_ERROR, "An error is encountered with"
				" the request: sysErrorCode=%d; qmiErrCode=%d\n",
							sysErrCode, qmiErrCode);
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
			return;
		}

		if (NULL == rspData) {
			wpa_printf(MSG_ERROR, "Response data is NULL\n");
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
			return;
		}

		/* ensure the reply packet exists  */
		if (!rspData->eap_send_pkt_resp.resp_data) {
			wpa_printf(MSG_ERROR, "Reply packet is NULL\n");
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;
			return;
		}

		length = rspData->eap_send_pkt_resp.length;
		eap_proxy->qmi_resp_data.eap_send_pkt_resp.length = length;
/* allocate a buffer to store the response data; size is EAP resp len field */
		eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data =
				os_malloc(rspData->eap_send_pkt_resp.length);

		resp_data =
		(u8 *)eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data;

		if (NULL == resp_data) {
			wpa_printf(MSG_ERROR, "Unable to allocate memory for"
							 " reply packet\n");
			eap_proxy->qmi_state = QMI_STATE_RESP_TIME_OUT;

			return;
		}

		/* copy the response data to the allocated buffer */
		os_memcpy(resp_data,
			rspData->eap_send_pkt_resp.resp_data, length);
		eap_proxy->qmi_state = QMI_STATE_RESP_RECEIVED;

		dump_buff(resp_data, length);

	}
	return;
}

static  Boolean eap_proxy_build_NAK(eap_proxy_sm  *eap_proxy,
				    u8 id, struct eap_sm *eap_sm)

{
	struct wpabuf *nak_buf;
	struct eap_hdr *resp;
	unsigned int len = 0, auth_supp_cnt = 0;
	u8 *pos, *temp;
	int idx;
	struct eap_method_type *m;
	struct eap_peer_config *config = eap_get_config(eap_sm);

	resp = os_malloc(len);
	if (resp == NULL)
		return FALSE;

	resp->code = EAP_CODE_RESPONSE;
	resp->identifier = id;

	pos = (u8 *)(resp + 1);
	*pos++ = EAP_RESP_TYPE_NAK;

	if (config == NULL || config->eap_methods == NULL) {
		*pos = 0;
		wpa_printf(MSG_ERROR, "Proxy Config NULL\n");
	}

	m = config->eap_methods;
	for (idx = 0; m[idx].vendor != EAP_VENDOR_IETF ||
			 m[idx].method != EAP_TYPE_NONE; idx++) {
#ifdef SIM_AKA_IDENTITY_IMSI
		if (!((wpa_uim.card_info[wpa_uim.card_ready_idx].app_type ==
			UIM_APP_TYPE_SIM_V01) && ((m[idx].method == EAP_TYPE_AKA)))) {
			*pos++ = m[idx].method;
		} else {
			*pos++ = 0;
		}
#else
		*pos++ = m[idx].method;
#endif /* SIM_AKA_IDENTITY_IMSI */

		auth_supp_cnt++;

		wpa_printf(MSG_ERROR, "Proxy Config NOT NULL %d %d\n", idx, m[idx].method);
	}

	len = sizeof(struct eap_hdr) + 1 + auth_supp_cnt;

	temp = (u8 *)(resp + 1);

	for (idx = 0; idx < len; idx++)
		wpa_printf(MSG_ERROR, "Temp buff %d %d %d \n", idx, temp[idx], len);

	resp->length = host_to_be16(len);


	eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data = (u8 *)resp;
	eap_proxy->qmi_resp_data.eap_send_pkt_resp.length = len;

	return TRUE;

}


static  eap_proxy_status eap_proxy_process(eap_proxy_sm  *eap_proxy,
					u8 *eapReqData, int eapReqDataLen, struct eap_sm *eap_sm)
{
	struct eap_hdr *hdr;
	int qmiErrorCode;
	eap_proxy_status proxy_status = EAP_PROXY_SUCCESS;

	if (eap_proxy->qmi_state != QMI_STATE_IDLE) {
		wpa_printf(MSG_ERROR, "Error in QMI state=%d\n",
					 eap_proxy->qmi_state);
		return EAP_PROXY_FAILURE;
	}
	hdr = (struct eap_hdr *)eapReqData;
	if ((EAP_CODE_REQUEST == hdr->code) &&
		(EAP_TYPE_IDENTITY == eapReqData[4])) {
		if (eap_proxy_build_identity(eap_proxy, hdr->identifier)) {
			eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapResp, TRUE);
			eap_proxy->proxy_state = EAP_PROXY_IDENTITY;
			eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapReq, FALSE);
			eap_proxy->is_state_changed = TRUE;
			return EAP_PROXY_SUCCESS;
		}
		else {
			wpa_printf(MSG_ERROR, "Error in build identity\n");
			return EAP_PROXY_FAILURE;
		}
	}
#ifdef SIM_AKA_IDENTITY_IMSI
	if ((EAP_CODE_REQUEST == hdr->code) &&
		((EAP_SUB_TYPE_SIM_START == eapReqData[5]) ||
		(EAP_SUB_TYPE_AKA_IDENTITY == eapReqData[5]))) {

		if (!eap_allowed_method(eap_sm,
			EAP_VENDOR_IETF , eapReqData[4])) {
			wpa_printf(MSG_ERROR, "Unsupported authentication method %d\n",
						eapReqData[4]);
			if (eap_proxy_build_NAK(eap_proxy,
				hdr->identifier, eap_sm)) {

				eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapResp, TRUE);
				eap_proxy->proxy_state = EAP_PROXY_IDENTITY;
				eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapReq, FALSE);
				eap_proxy->is_state_changed = TRUE;
				return EAP_PROXY_SUCCESS;
			} else {
				wpa_printf(MSG_ERROR, "Error in build NAK response\n");
				return EAP_PROXY_FAILURE;
			}
		}

	}
#endif /* SIM_AKA_IDENTITY_IMSI */

	dump_buff(eapReqData, eapReqDataLen);
	eap_proxy->qmiTransactionId = qmi_eap_auth_send_eap_packet(
			eap_proxy->qmihandle, &handle_qmi_eap_reply,
			eap_proxy, eapReqData, eapReqDataLen, &qmiErrorCode);

	if (0 <= eap_proxy->qmiTransactionId) {
		switch (hdr->code) {
		case EAP_CODE_SUCCESS:
			eap_proxy->proxy_state = EAP_PROXY_AUTH_SUCCESS;
			eap_proxy_getKey(eap_proxy);
			eap_proxy_eapol_sm_set_bool(eap_proxy,
					 EAPOL_eapSuccess, TRUE);
	/*
	 * RFC 4137 does not clear eapReq here, but this seems to be required
	 * to avoid processing the same request twice when state machine is
	 * initialized.
	 */
			eap_proxy_eapol_sm_set_bool(eap_proxy,
							EAPOL_eapReq, FALSE);

	/*
	 * RFC 4137 does not set eapNoResp here, but this seems to be required
	 * to get EAPOL Supplicant backend state machine into SUCCESS state. In
	 * addition, either eapResp or eapNoResp is required to be set after
	 * processing the received EAP frame.
	 */
			eap_proxy_eapol_sm_set_bool(eap_proxy,
						EAPOL_eapNoResp, TRUE);
			eap_proxy->is_state_changed = TRUE;

			/* Retrieve the keys  and store*/
			break;

		case EAP_CODE_FAILURE:
			eap_proxy->proxy_state = EAP_PROXY_AUTH_FAILURE;
			eap_proxy_eapol_sm_set_bool(eap_proxy,
						EAPOL_eapFail, TRUE);

	/*
	 * RFC 4137 does not clear eapReq here, but this seems to be required
	 * to avoid processing the same request twice when state machine is
	 * initialized.
	*/
			eap_proxy_eapol_sm_set_bool(eap_proxy,
						EAPOL_eapReq, FALSE);

	/*
	 * RFC 4137 does not set eapNoResp here. However, either eapResp or
	 * eapNoResp is required to be set after processing the received EAP
	 * frame.
	 */
			eap_proxy_eapol_sm_set_bool(eap_proxy,
						EAPOL_eapNoResp, TRUE);

			eap_proxy->is_state_changed = TRUE;
			break;

		case EAP_CODE_REQUEST:
					eap_proxy->qmi_state = QMI_STATE_RESP_PENDING;
					eap_proxy->proxy_state = EAP_PROXY_SEND_RESPONSE;
			if (EAP_PROXY_SUCCESS !=
				eap_proxy_qmi_response_wait(eap_proxy)) {
				eap_proxy->proxy_state = EAP_PROXY_DISCARD;
				eap_proxy_eapol_sm_set_bool(eap_proxy,
							EAPOL_eapNoResp, TRUE);
				return EAP_PROXY_FAILURE;
			} else {
				eap_proxy_eapol_sm_set_bool(eap_proxy,
							EAPOL_eapResp, TRUE);
				eap_proxy->proxy_state =
						EAP_PROXY_SEND_RESPONSE;
			}

			eap_proxy_eapol_sm_set_bool(eap_proxy,
						EAPOL_eapReq, FALSE);
			eap_proxy->is_state_changed = TRUE;
			break;

		default:
			wpa_printf(MSG_ERROR, "Error in sending EAP packet;"
					 " error_code=%d\n", qmiErrorCode);
			eap_proxy->proxy_state = EAP_PROXY_DISCARD;
			eap_proxy_eapol_sm_set_bool(eap_proxy,
				EAPOL_eapNoResp, TRUE);
			return EAP_PROXY_FAILURE;
		}
	} else {
		wpa_printf(MSG_ERROR, "Error in sending EAP packet;"
					 " error_code=%d\n", qmiErrorCode);
		eap_proxy->proxy_state = EAP_PROXY_DISCARD;
		eap_proxy_eapol_sm_set_bool(eap_proxy, EAPOL_eapNoResp, TRUE);
		return EAP_PROXY_FAILURE;
	}

	return EAP_PROXY_SUCCESS;
}



static u8 *eap_proxy_getKey(eap_proxy_sm *eap_proxy)
{
	int qmiErrorCode;
	int qmiRetCode;

	if (NULL == eap_proxy->key)
		eap_proxy->key = os_malloc(EAP_PROXY_KEYING_DATA_LEN);

	if (NULL == eap_proxy->key)
		return NULL;

	qmiRetCode = qmi_eap_auth_get_session_keys(eap_proxy->qmihandle,
		eap_proxy->key, EAP_PROXY_KEYING_DATA_LEN, &qmiErrorCode);

	/* see if the MSK is acquired successfully */
	if (QMI_NO_ERR != qmiRetCode) {
		wpa_printf(MSG_ERROR, "Unable to get session keys;"
				 " qmiErrorCode=%d", qmiErrorCode);
		os_free(eap_proxy->key);
		return NULL;
	}
	eap_proxy->iskey_valid = TRUE;
	eap_proxy->proxy_state = EAP_PROXY_AUTH_SUCCESS;

	wpa_printf(MSG_ERROR, "eap_proxy_getkey EAP KEYS ");
	dump_buff(eap_proxy->key, EAP_PROXY_KEYING_DATA_LEN);
	return eap_proxy->key;
}

/**
 * eap_key_available - Get key availability (eapKeyAvailable variable)
 * @sm: Pointer to EAP state machine allocated with eap_sm_init()
 * Returns: 1 if EAP keying material is available, 0 if not
 */
int eap_proxy_key_available(eap_proxy_sm *sm)
{
	return  sm ? sm->iskey_valid : 0;
}

/**
 * eap_key_available - Get key availability (eapKeyAvailable variable)
 * @sm: Pointer to EAP state machine allocated with eap_sm_init()
 * Returns: 1 if EAP keying material is available, 0 if not
 */
static int eap_proxy_is_state_changed(eap_proxy_sm *sm)
{
	if (NULL == sm)
		return 0;

	if (TRUE == sm->is_state_changed) {
		sm->is_state_changed = FALSE;
		return 1;
	} else {
		return 0;
	}
}


/**
 * eap_get_eapKeyData - Get master session key (MSK) from EAP state machine
 * @sm: Pointer to EAP state machine allocated with eap_sm_init()
 * @len: Pointer to variable that will be set to number of bytes in the key
 * Returns: Pointer to the EAP keying data or %NULL on failure
 *
 * Fetch EAP keying material (MSK, eapKeyData) from the EAP state machine. The
 * key is available only after a successful authentication. EAP state machine
 * continues to manage the key data and the caller must not change or free the
 * returned data.
 */
const u8 *eap_proxy_get_eapKeyData(eap_proxy_sm *sm, size_t *len)
{
	if (sm == NULL || sm->key == NULL) {
		*len = 0;
		return NULL;
	}

	*len = EAP_PROXY_KEYING_DATA_LEN;
	return sm->key;
}

/**
 * eap_get_eapKeyData - Get EAP response data
 * @sm: Pointer to EAP state machine allocated with eap_sm_init()
 * @len: Pointer to variable that will be set to the length of the response
 * Returns: Pointer to the EAP response (eapRespData) or %NULL on failure
 *
 * Fetch EAP response (eapRespData) from the EAP state machine. This data is
 * available when EAP state machine has processed an incoming EAP request. The
 * EAP state machine does not maintain a reference to the response after this
 * function is called and the caller is responsible for freeing the data.
 */
u8 *eap_proxy_get_eapRespData(eap_proxy_sm *eap_proxy, size_t *len)
{
	u8 *resp;
	if (NULL == eap_proxy) {
		*len = 0;
		return NULL;
	}

	if (NULL == eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data) {
		*len = 0;
		return NULL;
	}

	resp = eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data;
	*len = eap_proxy->qmi_resp_data.eap_send_pkt_resp.length;
	eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data = NULL;
	eap_proxy->qmi_resp_data.eap_send_pkt_resp.length = 0;

	return resp;
}


static eap_proxy_status eap_proxy_qmi_response_wait(eap_proxy_sm *eap_proxy)
{

	eloop_register_timeout(0, QMI_RESP_TIME_OUT, handle_qmi_resp_timeout,
				     NULL, eap_proxy);
	do {
		os_sleep(0, 2000);

		if ((QMI_STATE_RESP_RECEIVED == eap_proxy->qmi_state) ||
		   (QMI_STATE_RESP_TIME_OUT == eap_proxy->qmi_state))
			break;
	} while (1);

	if (QMI_STATE_RESP_TIME_OUT == eap_proxy->qmi_state) {
		eloop_cancel_timeout(handle_qmi_resp_timeout, NULL, eap_proxy);
		wpa_printf(MSG_ERROR, "QMI state Response Time out\n");
		eap_proxy->proxy_state = EAP_PROXY_DISCARD;
		return EAP_PROXY_FAILURE;
	}
	eap_proxy->qmi_state = QMI_STATE_IDLE;

	return EAP_PROXY_SUCCESS;
}


static void eap_proxy_eapol_sm_set_bool(eap_proxy_sm *sm,
			enum eapol_bool_var var, Boolean value)
{
	sm->eapol_cb->set_bool(sm->ctx, var, value);
}


static Boolean eap_proxy_eapol_sm_get_bool(eap_proxy_sm *sm,
			 enum eapol_bool_var var)
{
	return  sm->eapol_cb->get_bool(sm->ctx, var);
}


int eap_proxy_sm_step(eap_proxy_sm *sm, struct eap_sm *eap_sm)
{
	int status = 0;
	if (((EAP_PROXY_IDLE == sm->proxy_state) || ( EAP_PROXY_AUTH_SUCCESS == sm->proxy_state) ||
                      ( EAP_PROXY_AUTH_FAILURE == sm->proxy_state)) && (TRUE == sm->isEap))
		eap_proxy_eapol_sm_set_bool(sm, EAPOL_eapRestart, FALSE);


	if ((sm->proxy_state != EAP_PROXY_INITIALIZE) &&
				 (sm->proxy_state != EAP_PROXY_DISABLED)) {
		if (TRUE == sm->isEap) {
			if(!eap_proxy_process(sm, sm->eapReqData,
						 sm->eapReqDataLen,eap_sm)) {
				sm->proxy_state = EAP_PROXY_AUTH_FAILURE;
				eap_proxy_eapol_sm_set_bool(sm, EAPOL_eapRestart, TRUE);
			}
			sm->isEap = FALSE;
		}
	}
	return eap_proxy_is_state_changed(sm);
}


eap_proxy_status eap_proxy_packet_update(eap_proxy_sm  *eap_proxy,
				u8 *eapReqData, int eapReqDataLen)
{
	eap_proxy->eapReqData = eapReqData;
	eap_proxy->eapReqDataLen = eapReqDataLen;
	eap_proxy->isEap = TRUE;
	return EAP_PROXY_SUCCESS;
}


static void dump_buff(u8 *buff, int len)
{
	int i ;

	wpa_printf(MSG_DEBUG, "----QMI EAP Buffer----LEN %d\n", len);
	for (i = 0; i < len; i++) {
		if (0 == i%8)
			wpa_printf(MSG_DEBUG, " \n");
		wpa_printf(MSG_DEBUG, "0x%x  ", buff[i]);
	}
	return;
}
static char bin_to_hexchar(u8 ch)
{
	if (ch < 0x0a) {
		return ch + '0';
	}
	return ch + 'a' - 10;
}

#ifdef SIM_AKA_IDENTITY_IMSI
static int imsi_append_3gpp_realm(u8 **identity, u8 imsi_len)
{
	const char *realm_3gpp = "@wlan.mnc000.mcc000.3gppnetwork.org";
	u8 *full_id = NULL;
	size_t full_id_len = 0;
	int mnc_len;

	full_id = os_malloc(imsi_len + os_strlen(realm_3gpp));
	if (full_id == NULL) {
		wpa_printf(MSG_WARNING, "Failed to allocate buffer for "
					"3GPP realm");
		return -1;
	}
	os_memset(full_id, 0, (imsi_len + os_strlen(realm_3gpp)));
	os_memcpy(full_id , *identity , imsi_len);
	os_memcpy(full_id + imsi_len ,
		realm_3gpp, os_strlen(realm_3gpp));
		full_id_len = imsi_len + os_strlen(realm_3gpp);

	/* MCC */
	full_id[imsi_len + 16] = full_id[1];
	full_id[imsi_len + 17] = full_id[2];
	full_id[imsi_len + 18] = full_id[3];

	/* MNC (2 or 3 digits) */
	mnc_len = card_mnc_len;
	if (mnc_len < 0) {
		wpa_printf(MSG_INFO, "Failed to get MNC length from (U)SIM "
		"assuming 3");
		mnc_len = 3;
	}

	if (mnc_len == 2) {
		full_id[imsi_len + 10] = full_id[4];
		full_id[imsi_len + 11] = full_id[5];
	} else if (mnc_len == 3) {
		full_id[imsi_len +  9] = full_id[4];
		full_id[imsi_len + 10] = full_id[5];
		full_id[imsi_len + 11] = full_id[6];
	}
	os_free(*identity);
	*identity = full_id;
	return full_id_len;
}
#endif /* SIM_AKA_IDENTITY_IMSI */

static Boolean eap_proxy_build_identity(eap_proxy_sm *eap_proxy, u8 id)
{
	struct eap_hdr *resp;
	unsigned int len;
	u8 identity_len, ret;
	u8 *pos;
	int qmiRetCode;
	int qmiErrorCode;
	int i;
#ifdef SIM_AKA_IDENTITY_IMSI
	unsigned char *identity;

	if(!wpa_qmi_read_card_status()) {
		wpa_printf(MSG_INFO, "Read Card Status failed, return\n");
		return FALSE;
	}

	if(!wpa_qmi_read_card_imsi()) {
		wpa_printf(MSG_INFO, "Read Card IMSI failed, return\n");
		return FALSE;
	}

	if (imsi == NULL) {
		wpa_printf(MSG_INFO, "IMSI not available, return\n");
		return FALSE;
	} else {
		identity = os_malloc(IMSI_LENGTH + 1);
		if (identity == NULL) {
			free(imsi);
			return FALSE;
		}
		os_memset(identity, 0, (IMSI_LENGTH + 1));

		wpa_printf(MSG_ERROR, " eap_type: %d\n", eap_proxy->eap_type);
		if (eap_proxy->eap_type == EAP_TYPE_SIM) {
			identity[0] = '1';
		} else if (eap_proxy->eap_type == EAP_TYPE_AKA) {
			identity[0] = '0';
		} else {
			/* Default value is set as SIM */
			identity[0] = '1';
		}
		os_memcpy(identity+1 , imsi , IMSI_LENGTH);
	}
	for (i = 0; i < 16; i++)
		wpa_printf(MSG_ERROR, "build_ident IMSI %d %d \n", identity[i],imsi[i]);

	identity_len = imsi_append_3gpp_realm(&identity, IMSI_LENGTH+1);

	for (i = 0;i < 35; i++)
		wpa_printf(MSG_ERROR, "build_identAFTER IMSI %d %d \n", identity[i],imsi[i]);

	wpa_printf(MSG_ERROR, " identity  - %20s length-%d\n ", identity, identity_len);
	len = sizeof(struct eap_hdr) + 1 + identity_len;
#else
	char identity[] = "anonymous";
	len = sizeof(struct eap_hdr) + 1 + sizeof(identity) - 1;
#endif

	resp = os_malloc(len);
	if (resp == NULL) {
#ifdef SIM_AKA_IDENTITY_IMSI
		if (imsi)
			os_free(imsi);
#endif
		return FALSE;
	}

	resp->code = EAP_CODE_RESPONSE;
	resp->identifier = id;
	resp->length = host_to_be16(len);
	pos = (u8 *)(resp + 1);
	*pos++ = EAP_TYPE_IDENTITY;

#ifdef SIM_AKA_IDENTITY_IMSI
	os_memcpy(pos, identity, identity_len);
	if (identity != NULL)
		os_free(identity);
	if (imsi)
		os_free(imsi);

#else
	os_memcpy(pos, identity, sizeof(identity)-1);
#endif
	eap_proxy->qmi_resp_data.eap_send_pkt_resp.resp_data = (u8 *)resp;
	eap_proxy->qmi_resp_data.eap_send_pkt_resp.length = len;

	wpa_printf(MSG_ERROR, " len %d\n ", len);

	if (TRUE == eap_auth_session_flag) {
		if (eap_proxy->qmihandle != 0) {
			qmiRetCode = qmi_eap_auth_end_eap_session(eap_proxy->qmihandle,
									&qmiErrorCode);
			if (QMI_NO_ERR != qmiRetCode) {
				wpa_printf(MSG_ERROR, "Unable to end the EAP session;"
						" error_ret=%d; error_code=%d\n", qmiRetCode,
						qmiErrorCode);
			}
			eap_auth_session_flag = FALSE;
		}
	}
	if (FALSE == eap_auth_session_flag) {
		if (eap_proxy->qmihandle != 0) {
			qmiRetCode = qmi_eap_auth_start_eap_session(eap_proxy->qmihandle,
								QMI_EAP_METHOD_MASK_UNSET, &qmiErrorCode);
			if (QMI_NO_ERR != qmiRetCode) {
				wpa_printf(MSG_ERROR, "Unable to start the EAP session;"
							" error_ret=%d; error_code=%d\n", qmiRetCode,
							qmiErrorCode);
			}
			eap_auth_session_flag = TRUE;
		}
	}

	return TRUE;
}



#ifdef CONFIG_CTRL_IFACE

/**
 * eap_proxyl_sm_get_status - Get EAP state machine status
 * @sm: Pointer to EAP state machine allocated with eap_sm_init()
 * @buf: Buffer for status information
 * @buflen: Maximum buffer length
 * @verbose: Whether to include verbose status information
 * Returns: Number of bytes written to buf.
 *
 * Query EAP state machine for status information. This function fills in a
 * text area with current status information from the EAPOL state machine. If
 * the buffer (buf) is not large enough, status information will be truncated
 * to fit the buffer.
 */
int eap_proxy_sm_get_status(eap_proxy_sm *sm, char *buf, size_t buflen,
								int verbose) {
	int len, ret;

	if (sm == NULL)
		return 0;

	len = os_snprintf(buf, buflen, "EAP state=%s\n",
			  eap_proxy_sm_state_txt(sm->proxy_state));
	if (len < 0 || (size_t)len >= buflen)
		return 0;

	if (sm->eap_type != EAP_TYPE_NONE) {
		char name[8] = "Unknown";

	if (sm->eap_type == EAP_TYPE_SIM)
		os_strncpy(name, "SIM", 4);
	else if (sm->eap_type == EAP_TYPE_AKA)
		os_strncpy(name, "AKA", 4);

		ret = os_snprintf(buf + len, buflen - len,
				"selectedMethod=%d (EAP-%s)\n",
					sm->eap_type, name);
		if (ret < 0 || (size_t)ret >= buflen - len)
			return len;
		len += ret;
	}

	return len;
}


static const char *eap_proxy_sm_state_txt(int state)
{
	switch (state) {
	case EAP_PROXY_INITIALIZE:
		return "INITIALIZE";
	case EAP_PROXY_DISABLED:
		return "DISABLED";
	case EAP_PROXY_IDLE:
		return "IDLE";
	case EAP_PROXY_RECEIVED:
		return "RECEIVED";
	case EAP_PROXY_GET_METHOD:
		return "GET_METHOD";
	case EAP_PROXY_METHOD:
		return "METHOD";
	case EAP_PROXY_SEND_RESPONSE:
		return "SEND_RESPONSE";
	case EAP_PROXY_DISCARD:
		return "DISCARD";
	case EAP_PROXY_IDENTITY:
		return "IDENTITY";
	case EAP_PROXY_NOTIFICATION:
		return "NOTIFICATION";
	case EAP_PROXY_RETRANSMIT:
		return "RETRANSMIT";
	case EAP_PROXY_AUTH_SUCCESS:
		return "SUCCESS";
	case EAP_PROXY_AUTH_FAILURE:
		return "FAILURE";
	default:
		return "UNKNOWN";
	}
}
#endif /* CONFIG_CTRL_IFACE */
#endif /* SIM_AKA_QUALCOMM */
