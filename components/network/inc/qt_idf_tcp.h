/**
 * @file 
 * qt_idf_tcp.h
 * 
 * @brief 
 * 
 * @author hacper (git@hacperme.com)
 * @date 04/07/2023
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
 * 04/07/2023		hacper		create
 * =================================================================================
 */

#ifndef __QT_IDF_TCP_H__
#define __QT_IDF_TCP_H__

#ifdef __cplusplus
extern "C" {
#endif

void *qtf_tcp_connect(const char *host, int port);

int qtf_tcp_send(void *ctx, const char *data, int len, int timeout_ms);

int qtf_tcp_recv(void *ctx, char *buffer, int len, int timeout_ms);

void qtf_tcp_close(void *ctx);

#ifdef __cplusplus
}
#endif

#endif /* __QT_IDF_TCP_H__ */