/**
 * @file 
 * qt_idf_tcp.c
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

#ifdef __cplusplus
extern "C" {
#endif

#include "qt_idf_tcp.h"
#include "utils_timer.h"
#include "dlg/dlg.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

void *qtf_tcp_connect(const char *host, int port)
{
    WORD    sockVersion = MAKEWORD(2, 2);
    WSADATA data;

    int             ret;
    struct addrinfo hints, *addr_list, *cur;
    SOCKET          fd;
    char            port_str[6] = {0};

    if (WSAStartup(sockVersion, &data) != 0)
    {
        dlg_error("WSAStartup failed");
        return NULL;
    }

    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    snprintf(port_str, sizeof(port_str), "%d", port);

    ret = getaddrinfo(host, port_str, &hints, &addr_list);
    if (ret != 0)
    {
        dlg_error("getaddrinfo failed: %d, errno:%d", ret, errno);
        return NULL;
    }

    for (cur = addr_list; cur != NULL; cur = cur->ai_next) {
        fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if (fd == INVALID_SOCKET) {
            ret = 0;
            continue;
        }

        if (connect(fd, cur->ai_addr, cur->ai_addrlen) == 0) {
            ret = fd;
            break;
        }

        closesocket(fd);
        ret = 0;
    }

     if (0 == ret)
     {
        dlg_error("connect to %s:%d failed: %d", host, port, ret);
     }
     else
     {
        dlg_info("connect to %s:%d success: %d", host, port, ret);
     }

    freeaddrinfo(addr_list);

    return (void *)ret;
}

int qtf_tcp_send(void *ctx, const char *data, int len, int timeout_ms)
{
    int ret = 1;
    timer_t timer;
    fd_set sets;
    uint32_t left_ms;
    struct timeval timeout;
    uint32_t len_sent = 0;

    qtf_timer_init(&timer);
    qtf_timer_countdown_ms(&timer, timeout_ms);

    do
    {
        left_ms = qtf_timer_left_ms(&timer);
        if (left_ms > 0)
        {
            FD_ZERO(&sets);
            FD_SET((SOCKET)ctx, &sets);
            timeout.tv_sec = left_ms / 1000;
            timeout.tv_usec = (left_ms % 1000) * 1000;

            ret = select((SOCKET)ctx + 1, NULL, &sets, NULL, &timeout);
            if (ret > 0)
            {
                if (FD_ISSET((SOCKET)ctx, &sets) == 0)
                {
                    ret = 0;
                    continue;
                }
            }
            else if (ret == 0)
            {
                dlg_error("select timeout");
                break;
            }
            else
            {
                if (errno == EINTR)
                {
                    continue;
                }

                dlg_error("select failed: %d, errno:%d", ret, errno);
                ret = -1;
                break;
            }
        }

        if (ret > 0)
        {
            ret = send((SOCKET)ctx, data + len_sent, len - len_sent, 0);
            if (ret < 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }

                dlg_error("send failed: %d, errno:%d", ret, errno);
                ret = -1;
                break;
            }
            else
            {
                len_sent += ret;
            }
        }

    } while (len_sent < len && !qtf_timer_expired(&timer));

    if (len_sent > 0)
    {
        dlg_info("send %d bytes", len_sent);
        return len_sent;
    }

    return -1;
}

int qtf_tcp_recv(void *ctx, char *buffer, int len, int timeout_ms)
{
    int ret = 1;
    timer_t timer;
    fd_set sets;
    uint32_t left_ms;
    struct timeval timeout;
    uint32_t len_recv = 0;

    qtf_timer_init(&timer);
    qtf_timer_countdown_ms(&timer, timeout_ms);

    do
    {
        left_ms = qtf_timer_left_ms(&timer);
        if (left_ms > 0)
        {
            FD_ZERO(&sets);
            FD_SET((SOCKET)ctx, &sets);
            timeout.tv_sec = left_ms / 1000;
            timeout.tv_usec = (left_ms % 1000) * 1000;

            ret = select((SOCKET)ctx + 1, &sets, NULL, NULL, &timeout);
            if (ret > 0)
            {
                if (FD_ISSET((SOCKET)ctx, &sets) == 0)
                {
                    ret = 0;
                    continue;
                }
            }
            else if (ret == 0)
            {
                dlg_error("select timeout");
                break;
            }
            else
            {
                if (errno == EINTR)
                {
                    continue;
                }

                dlg_error("select failed: %d, errno:%d", ret, errno);
                ret = -1;
                break;
            }
        }

        if (ret > 0)
        {
            ret = recv((SOCKET)ctx, buffer + len_recv, len - len_recv, 0);
            if (ret < 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }

                dlg_error("recv failed: %d, errno:%d", ret, errno);
                ret = -1;
                break;
            }
            else if (ret == 0)
            {
                struct sockaddr_in peer;
                int                sLen      = sizeof(peer);
                int                peer_port = 0;
                getpeername((SOCKET)ctx, (struct sockaddr *)&peer, &sLen);
                peer_port = ntohs(peer.sin_port);
                dlg_info("peer %s:%d closed", inet_ntoa(peer.sin_addr), peer_port);
                ret = -1;
                break;
            }
            else
            {
                len_recv += ret;
            }
        }

    } while (!qtf_timer_expired(&timer) && len_recv < len);

    if (len_recv > 0)
    {
        dlg_info("recv %d bytes", len_recv);
        return len_recv;
    }

    return -1;
}

void qtf_tcp_close(void *ctx)
{
    SOCKET fd = (SOCKET)ctx;
    if(fd > 0)
    {
        shutdown(fd, SD_BOTH);
        closesocket(fd);
    }
    
    WSACleanup();
}


#ifdef __cplusplus
} /*"C" */
#endif
