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
    QTF_TLS_VERSION_TLS1_2 = 0,     // TLS v1.2
    QTF_TLS_VERSION_TLS1_3,         // TLS v1.3
    QTF_TLS_VERSION_TLS1_2_1_3,     // TLS v1.2 and TLS v1.3
    QTF_TLS_VERSION_MAX
}qtf_tls_version_t;

typedef enum
{
    QTF_TLS_VERIFY_MODE_NONE = 0,
    QTF_TLS_VERIFY_MODE_OPTIONAL,
    QTF_TLS_VERIFY_MODE_REQUIRED,
    QTF_TLS_VERIFY_MODE_MAX
}qtf_tls_verify_mode_t;

typedef enum
{
    QTF_TLS_DEBUG_LEVEL_NONE = 0,
    QTF_TLS_DEBUG_LEVEL_ERROR,
    QTF_TLS_DEBUG_LEVEL_STATE,
    QTF_TLS_DEBUG_LEVEL_INFO,
    QTF_TLS_DEBUG_LEVEL_VERBOSE,
}qtf_tls_debug_level_t;

typedef enum
{
    QTF_TLS_MAX_FRAG_LEN_NO_USE = 0,
    QTF_TLS_MAX_FRAG_LEN_512,
    QTF_TLS_MAX_FRAG_LEN_1024,
    QTF_TLS_MAX_FRAG_LEN_2048,
    QTF_TLS_MAX_FRAG_LEN_4096,
}qtf_tls_max_frag_len_t;

typedef struct
{
    qtf_tls_auth_mode_t auth_mode;
    qtf_tls_verify_mode_t verify_mode;
    qtf_tls_version_t tls_version;
    qtf_tls_debug_level_t debug_level;
    qtf_tls_max_frag_len_t max_frag_len;
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
