/**
 * @file 
 * qt_idf_tls.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qt_idf_tls.h"
#include "dlg/dlg.h"

#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
#include "mbedtls/platform.h"
#include "mbedtls/timing.h"
#include "mbedtls/entropy.h"
#include "mbedtls/error.h"


typedef struct
{
    mbedtls_net_context      socket_fd;
    mbedtls_entropy_context  entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_context      ssl;
    mbedtls_ssl_config       ssl_conf;
    mbedtls_x509_crt         ca_cert;
    mbedtls_x509_crt         client_cert;
    mbedtls_pk_context       private_key;
}qtf_tls_handle_t;

#if defined(MBEDTLS_DEBUG_C)
#define DEBUG_LEVEL 0
static void _ssl_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    dlg_debug("[mbedTLS]:[%s]:[%d]: %s\r\n", (file), line, (str));
}

#endif

static int _mbedtls_tcp_connect(mbedtls_net_context *ctx, const char *host, uint16_t port)
{
    int ret = 0;
    char port_str[6] = {0};

    snprintf(port_str, sizeof(port_str), "%d", port);

    ret = mbedtls_net_connect(ctx, host, port_str, MBEDTLS_NET_PROTO_TCP);
    if(ret != 0)
    {
        dlg_error("mbedtls_net_connect connect failed returned 0x%04x errno: %d", ret < 0 ? -ret : ret, errno);
       
        return ret;
    }

    ret = mbedtls_net_set_block(ctx);
    if(ret != 0)
    {
        dlg_error("mbedtls_net_set_block failed returned 0x%04x errno: %d", ret < 0 ? -ret : ret, errno);
        return ret;
    }

    return 0;
}

static int _tls_net_init(qtf_tls_handle_t *handle, qtf_tls_conn_param_t *param)
{
    int ret = -1;

    mbedtls_net_init(&(handle->socket_fd));
    mbedtls_ssl_init(&(handle->ssl));
    mbedtls_ssl_config_init(&(handle->ssl_conf));
    mbedtls_ctr_drbg_init(&(handle->ctr_drbg));
    
    mbedtls_entropy_init(&(handle->entropy));

#if defined(MBEDTLS_DEBUG_C)
    mbedtls_debug_set_threshold(DEBUG_LEVEL);
    mbedtls_ssl_conf_dbg(&handle->ssl_conf, _ssl_debug, NULL);
#endif

    ret = mbedtls_ctr_drbg_seed(&(handle->ctr_drbg), mbedtls_entropy_func, &(handle->entropy), NULL, 0);
    if (ret != 0)
    {
        dlg_error("mbedtls_ctr_drbg_seed failed");
        goto error;
    }

    if(param->auth_mode == QTF_TLS_AUTH_MODE_CERT)
    {
        if(param->ca_cert && param->ca_cert_len)
        {
            mbedtls_x509_crt_init(&(handle->ca_cert));
            ret = mbedtls_x509_crt_parse(&(handle->ca_cert), (const unsigned char *)param->ca_cert, param->ca_cert_len+1);
            if (ret != 0)
            {
                dlg_error("mbedtls_x509_crt_parse failed");
                goto error;
            }
        }
        else
        {
            if(param->verify_mode != QTF_TLS_VERIFY_MODE_NONE)
            {
                dlg_error("invalid ca cert");
                goto error;
            }
            dlg_info("verify mode is none");
        }
        
        mbedtls_ssl_conf_ca_chain(&(handle->ssl_conf), &(handle->ca_cert), NULL);

        if (param->client_cert && param->client_cert_len && param->client_key && param->client_key_len)
        {
            mbedtls_x509_crt_init(&(handle->client_cert));
            mbedtls_pk_init(&(handle->private_key));
            ret = mbedtls_x509_crt_parse(&(handle->client_cert), (const unsigned char *)param->client_cert, param->client_cert_len + 1);
            if (ret != 0)
            {
                dlg_error("mbedtls_x509_crt_parse failed");
                goto error;
            }

            ret = mbedtls_pk_parse_key(&(handle->private_key), (const unsigned char *)param->client_key,
                                       param->client_key_len + 1, (const unsigned char *)param->client_key_passwd, param->client_key_passwd_len + 1, NULL, NULL);
            if (ret != 0)
            {
                dlg_error("mbedtls_pk_parse_key failed");
                goto error;
            }
            ret = mbedtls_ssl_conf_own_cert(&(handle->ssl_conf), &(handle->client_cert), &(handle->private_key));
            if (ret != 0)
            {
                dlg_error("mbedtls_ssl_conf_own_cert failed");
                goto error;
            }
        }
    }
    else if(param->auth_mode == QTF_TLS_AUTH_MODE_PSK)
    {
        if(param->psk && param->psk_len && param->psk_id)
        {
            ret = mbedtls_ssl_conf_psk(&(handle->ssl_conf), (const unsigned char *)param->psk, param->psk_len,
                                       (const unsigned char *)param->psk_id, strlen(param->psk_id));
            if (ret != 0)
            {
                dlg_error("mbedtls_ssl_conf_psk failed");
                goto error;
            }
        }
        else
        {
            dlg_error("invalid psk");
            goto error;
        }
    }
    else
    {
        dlg_error("invalid auth mode");
        goto error;
    }

    


    return ret;

error:
    
    return ret;

}

static int __tls_net_deinit(qtf_tls_handle_t *handle)
{
    mbedtls_net_free(&(handle->socket_fd));
    mbedtls_ssl_free(&(handle->ssl));
    mbedtls_ssl_config_free(&(handle->ssl_conf));
    mbedtls_ctr_drbg_free(&(handle->ctr_drbg));
    mbedtls_entropy_free(&(handle->entropy));
    mbedtls_x509_crt_free(&(handle->ca_cert));
    mbedtls_x509_crt_free(&(handle->client_cert));
    mbedtls_pk_free(&(handle->private_key));

    return 0;
}

void *qtf_tls_connect(const char *host, uint16_t port, qtf_tls_conn_param_t *param)
{
    qtf_tls_handle_t *handle = NULL;
    int ret = 0;

    if(!host || !param)
    {
        dlg_error("invalid param");
        goto error;
    }

    handle = (qtf_tls_handle_t *)malloc(sizeof(qtf_tls_handle_t));
    if(!handle)
    {
        dlg_error("malloc failed");
        goto error;
    }

    ret = _tls_net_init(handle, param);
    if(ret != 0)
    {
        dlg_error("tls net init failed");
        goto error;
    }

    dlg_info("Connecting to %s:%d...", host, port);

    ret = _mbedtls_tcp_connect(&(handle->socket_fd), host, port);
    if (ret != 0)
    {
        dlg_error("mbedtls_tcp_connect failed");
        goto error;
    }

    mbedtls_ssl_config_defaults(&(handle->ssl_conf), MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);

    mbedtls_ssl_conf_read_timeout(&(handle->ssl_conf), param->hanshake_timeout_ms);

    mbedtls_ssl_conf_authmode(&(handle->ssl_conf), param->verify_mode);

    mbedtls_ssl_conf_max_version(&(handle->ssl_conf), MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);
    mbedtls_ssl_conf_min_version(&(handle->ssl_conf), MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);

    mbedtls_ssl_conf_rng(&(handle->ssl_conf), mbedtls_ctr_drbg_random, &(handle->ctr_drbg));

    // todo: config ciphersuites

    // todo: config max_tls_fragment

    ret = mbedtls_ssl_setup(&(handle->ssl), &(handle->ssl_conf));
    if (ret != 0)
    {
        dlg_error("mbedtls_ssl_setup failed");
        goto error;
    }

    mbedtls_ssl_set_bio(&(handle->ssl), &(handle->socket_fd), mbedtls_net_send, mbedtls_net_recv, mbedtls_net_recv_timeout);

    ret = mbedtls_ssl_set_hostname(&(handle->ssl), host);
    if (ret != 0)
    {
        dlg_error("mbedtls_ssl_set_hostname failed");
        goto error;
    }

    // hanshake
    while ((ret = mbedtls_ssl_handshake(&(handle->ssl))) != 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            dlg_error("mbedtls_ssl_handshake failed 0x%04x", ret < 0 ? -ret : ret);
            goto error;
        }
    }

    ret = mbedtls_ssl_get_verify_result(&(handle->ssl));
    if (ret != 0)
    {
        dlg_error("mbedtls_ssl_get_verify_result ret: %x\r\n", (unsigned int)&ret);
        goto error;
    }

    return handle;

error:

    if(handle)
    {
        __tls_net_deinit(handle);
        free(handle);
    }

    return NULL;
}

int qtf_tls_send(void *handle, const void *buf, uint32_t len, uint32_t timeout_ms)
{
    qtf_tls_handle_t *tls_handle = (qtf_tls_handle_t *)handle;
    int ret = 0;

    if(!handle || !buf || !len)
    {
        dlg_error("invalid param");
        return -1;
    }

    while ((ret = mbedtls_ssl_write(&(tls_handle->ssl), (const unsigned char *)buf, len)) <= 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            dlg_error("mbedtls_ssl_write failed 0x%04x", ret < 0 ? -ret : ret);
            return -1;
        }
    }

    return ret;
}
int qtf_tls_recv(void *handle, void *buf, uint32_t len, uint32_t timeout_ms)
{
    qtf_tls_handle_t *tls_handle = (qtf_tls_handle_t *)handle;
    int ret = 0;

    if(!handle || !buf || !len)
    {
        dlg_error("invalid param");
        return -1;
    }

    while ((ret = mbedtls_ssl_read(&(tls_handle->ssl), (unsigned char *)buf, len)) <= 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            dlg_error("mbedtls_ssl_read failed 0x%04x", ret < 0 ? -ret : ret);
            return -1;
        }
    }

    return ret;
}
int qtf_tls_close(void *handle)
{
    qtf_tls_handle_t *tls_handle = (qtf_tls_handle_t *)handle;

    if(!handle)
    {
        dlg_error("invalid param");
        return -1;
    }

    __tls_net_deinit(tls_handle);
    free(tls_handle);

    return 0;
}
