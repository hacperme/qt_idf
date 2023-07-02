/**
 * @file 
 * qt_idf_tls.h
 * 
 * @brief 
 * 
 * @author hacper (git@hacperme.com)
 * @date 02/07/2023
 * 
 * =================================================================================
 * Copyright (c) 2023 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
 * Quectel Wireless Solution Proprietary and Confidential.
 * =================================================================================
 * 
 * =================================================================================
 * 		EDIT HISTORY FOR MODULE
 * This section contains comments describing changes made to the module.
 * WHEN		WHO				WHAT, WHERE, WHY
 * ------------		-------		--------------------------------------------------
 * 02/07/2023		hacper		create
 * =================================================================================
 */

#ifndef __QT_IDF_TLS_H__
#define __QT_IDF_TLS_H__

#include <stdint.h>

typedef enum
{
    QTF_TLS_AUTH_MODE_CERT = 0,
    QTF_TLS_AUTH_MODE_PSK,
    QTF_TLS_AUTH_MODE_MAX
}qtf_tls_auth_mode_t;

typedef enum
{
    QTF_TLS_VERIFY_MODE_NONE = 0,
    QTF_TLS_VERIFY_MODE_OPTIONAL,
    QTF_TLS_VERIFY_MODE_REQUIRED,
    QTF_TLS_VERIFY_MODE_MAX
}qtf_tls_verify_mode_t;

typedef struct
{
    qtf_tls_auth_mode_t auth_mode;
    qtf_tls_verify_mode_t verify_mode;
    uint32_t hanshake_timeout_ms;
    const char *ca_cert;
    uint32_t ca_cert_len;
    const char *client_cert;
    uint32_t client_cert_len;
    const char *client_key;
    uint32_t client_key_len;
    const char *client_key_passwd;
    uint32_t client_key_passwd_len;
    const char *psk;
    uint32_t psk_len;
    const char *psk_id;
}qtf_tls_conn_param_t;


void *qtf_tls_connect(const char *host, uint16_t port, qtf_tls_conn_param_t *param);
int qtf_tls_send(void *handle, const void *buf, uint32_t len, uint32_t timeout_ms);
int qtf_tls_recv(void *handle, void *buf, uint32_t len, uint32_t timeout_ms);
int qtf_tls_close(void *handle);


#endif /* __QT_IDF_TLS_H__ */
