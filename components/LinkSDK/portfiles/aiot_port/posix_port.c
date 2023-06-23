/*
 * 这个移植示例适用于`Linux`这类支持pthread的POSIX设备，它实现了移植SDK所需要的接口。
 * 移植接口大体可以分为两类：网络接口(TCP)、系统接口(OS)
 *
 * + 网络接口：TCP/UDP的socket适配，请勿在此实现TLS传输，TLS实现已封装在SDK内部。
 * + 系统接口：包含内存管理、随机数、系统时间、互斥锁等功能移植。
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <ipmib.h>
#include <errno.h>
#include <sys/types.h>
#include <windows.h>

#include <errno.h>
#include <signal.h>
#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"

/* socket建联时间默认最大值 */
#define CORE_SYSDEP_DEFAULT_CONNECT_TIMEOUT_MS (10 * 1000)

typedef struct {
    int fd;
    core_sysdep_socket_type_t socket_type;
    char *host;
    char backup_ip[16];
    uint16_t port;
    uint32_t connect_timeout_ms;
} core_network_handle_t;

void *core_sysdep_malloc(uint32_t size, char *name)
{
    void *res = malloc(size);
    if(res == NULL) {
        printf("sysdep malloc failed \n");
    }
    return res;
}

void core_sysdep_free(void *ptr)
{
    free(ptr);
}

uint64_t core_sysdep_time(void)
{
    struct timeval time;

    memset(&time, 0, sizeof(struct timeval));
    gettimeofday(&time, NULL);

    return ((uint64_t)time.tv_sec * 1000 + (uint64_t)time.tv_usec / 1000);
}

void core_sysdep_sleep(uint64_t time_ms)
{
    usleep(time_ms * 1000);
}

static void *core_sysdep_network_init(void)
{
    core_network_handle_t *handle = malloc(sizeof(core_network_handle_t));
    if (handle == NULL) {
        return NULL;
    }
    memset(handle, 0, sizeof(core_network_handle_t));
    handle->connect_timeout_ms = CORE_SYSDEP_DEFAULT_CONNECT_TIMEOUT_MS;

    return handle;
}

static int32_t core_sysdep_network_setopt(void *handle, core_sysdep_network_option_t option, void *data)
{
    core_network_handle_t *network_handle = (core_network_handle_t *)handle;

    if (handle == NULL || data == NULL) {
        return STATE_PORT_INPUT_NULL_POINTER;
    }

    if (option >= CORE_SYSDEP_NETWORK_MAX) {
        return STATE_PORT_INPUT_OUT_RANGE;
    }

    switch (option) {
        case CORE_SYSDEP_NETWORK_SOCKET_TYPE: {
            network_handle->socket_type = *(core_sysdep_socket_type_t *)data;
        }
        break;
        case CORE_SYSDEP_NETWORK_HOST: {
            network_handle->host = malloc(strlen(data) + 1);
            if (network_handle->host == NULL) {
                printf("malloc failed\n");
                return STATE_PORT_MALLOC_FAILED;
            }
            memset(network_handle->host, 0, strlen(data) + 1);
            memcpy(network_handle->host, data, strlen(data));
        }
        break;
        case CORE_SYSDEP_NETWORK_BACKUP_IP: {
            memcpy(network_handle->backup_ip, data, strlen(data));
        }
        break;
        case CORE_SYSDEP_NETWORK_PORT: {
            network_handle->port = *(uint16_t *)data;
        }
        break;
        case CORE_SYSDEP_NETWORK_CONNECT_TIMEOUT_MS: {
            network_handle->connect_timeout_ms = *(uint32_t *)data;
        }
        break;
        default: {
            break;
        }
    }

    return STATE_SUCCESS;
}

static void _port_uint2str(uint16_t input, char *output)
{
    uint8_t i = 0, j = 0;
    char temp[6] = {0};

    do {
        temp[i++] = input % 10 + '0';
    } while ((input /= 10) > 0);

    do {
        output[--i] = temp[j++];
    } while (i > 0);
}

static int32_t _core_sysdep_network_connect(char *host, uint16_t port, int family, int socktype, int protocol,
        uint32_t timeout_ms, int *fd_out)
{
    int32_t res = STATE_SUCCESS;
    int fd = 0;
    char service[6] = {0};
    struct addrinfo hints;
    struct addrinfo *addrInfoList = NULL, *pos = NULL;
    u_long flags = 1;
    WSADATA wsaData;

    WSAStartup(0x202, &wsaData);
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = family; /* only IPv4 */
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;
    hints.ai_flags = 0;
    _port_uint2str(port, service);

    // signal( SIGPIPE, SIG_IGN );

    res = getaddrinfo(host, service, &hints, &addrInfoList);
    if (res == 0) {
        for (pos = addrInfoList; pos != NULL; pos = pos->ai_next) {
            fd = socket(pos->ai_family, pos->ai_socktype, pos->ai_protocol);
            if (fd < 0) {
                printf("create socket error\n");
                res = STATE_PORT_NETWORK_SOCKET_CREATE_FAILED;
                continue;
            }

            // res = ioctlsocket(fd, FIONBIO, &flags);
            res = -1;

            // res = fcntl(fd, F_GETFL);
            // if (res != -1) {
            //     res = fcntl(fd, F_SETFL, sock_option | O_NONBLOCK);
            // }

            if (res == -1) {
                /* block connect */
                if (connect(fd, pos->ai_addr, pos->ai_addrlen) == 0) {
                    *fd_out = fd;
                    res = STATE_SUCCESS;
                    break;
                } else {
                    res = STATE_PORT_NETWORK_CONNECT_FAILED;
                }
            } else {
                /* non-block connect */
                fd_set write_sets;
                struct timeval timeselect;

                FD_ZERO(&write_sets);
                FD_SET(fd, &write_sets);

                timeselect.tv_sec = timeout_ms / 1000;
                timeselect.tv_usec = timeout_ms % 1000 * 1000;

                if (connect(fd, pos->ai_addr, pos->ai_addrlen) == 0) {
                    *fd_out = fd;
                    res = STATE_SUCCESS;
                    break;
                } else if (errno != EINPROGRESS) {
                    res = STATE_PORT_NETWORK_CONNECT_FAILED;
                } else {
                    res = select(fd + 1, NULL, &write_sets, NULL, &timeselect);
                    if (res == 0) {
                        res = STATE_MQTT_LOG_CONNECT_TIMEOUT;
                    } else if (res < 0) {
                        res = STATE_PORT_NETWORK_CONNECT_FAILED;
                    } else {
                        if (FD_ISSET(fd, &write_sets)) {
                            res = connect(fd, pos->ai_addr, pos->ai_addrlen);
                            if ((res != 0 && errno == EISCONN) || res == 0) {
                                *fd_out = fd;
                                res = STATE_SUCCESS;
                                break;
                            } else {
                                res = STATE_PORT_NETWORK_CONNECT_FAILED;
                            }
                        }
                    }
                }
            }

            close(fd);
            printf("connect error, errno: %d\n", errno);
        }
    } else {
        res = STATE_PORT_NETWORK_DNS_FAILED;
    }

    if (res < 0) {
        printf("fail to establish tcp\n");
    } else {
        printf("success to establish tcp, fd=%d\n", *fd_out);
        // struct sockaddr_in loc_addr;
        // socklen_t len = sizeof(sizeof(loc_addr));
        // char buf[1024] = {0};
        // memset(&loc_addr, 0, len);
        // if (-1 == getsockname(*fd_out, (struct sockaddr *)&loc_addr, &len)) {// 获取socket绑定的本地address信息
        //     memset(buf, 0, sizeof(buf));
        //     snprintf(buf, sizeof(buf), "get socket name failed. errno: %d, error: %s", errno, strerror(errno));
        //     perror(buf);
        //     //safe_close(*fd_out);
        //     exit(-1);
        // }

        // if (loc_addr.sin_family == AF_INET) {// 打印信息
        //     printf("local port: %u\n", ntohs(loc_addr.sin_port));
        // }
        res = STATE_SUCCESS;
    }

    if(addrInfoList) {
        freeaddrinfo(addrInfoList);
    }

    return res;
}

static int32_t _core_sysdep_network_tcp_establish(core_network_handle_t *network_handle)
{
    int32_t res = STATE_SUCCESS;

    printf("establish tcp connection with server(host='%s', port=[%u])\n", network_handle->host, network_handle->port);

    res = _core_sysdep_network_connect(network_handle->host, network_handle->port,
                                       AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, network_handle->connect_timeout_ms, &network_handle->fd);
    if (res == STATE_PORT_NETWORK_DNS_FAILED && strlen(network_handle->backup_ip) > 0) {
        printf("using backup ip: %s\n", network_handle->backup_ip);
        res = _core_sysdep_network_connect(network_handle->backup_ip, network_handle->port,
                                           AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, network_handle->connect_timeout_ms, &network_handle->fd);
    }

    return res;
}

static int32_t _core_sysdep_network_udp_server_establish(core_network_handle_t *network_handle)
{
    int32_t sockfd;
    struct sockaddr_in servaddr;
    char opt_val = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("create socket error, errno: %d\n", errno);
        perror("create socket error");
        return STATE_PORT_NETWORK_SOCKET_CREATE_FAILED;
    }

    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val))) {
        printf("setsockopt(SO_REUSEADDR) falied, errno: %d\n", errno);
        perror("setsockopt(SO_REUSEADDR) error");
        close(sockfd);
        return STATE_PORT_NETWORK_SOCKET_CONFIG_FAILED;
    }

    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(network_handle->port);

    if (-1 == bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in))) {
        printf("bind(%d) falied, errno: %d\n", (int)sockfd, errno);
        perror("bind(%d) error");
        close(sockfd);
        return STATE_PORT_NETWORK_SOCKET_BIND_FAILED;
    }

    network_handle->fd = sockfd;
    printf("success to establish udp, fd=%d\n", (int)sockfd);

    return 0;
}

static int32_t core_sysdep_network_establish(void *handle)
{
    core_network_handle_t *network_handle = (core_network_handle_t *)handle;
    if (handle == NULL) {
        return STATE_PORT_INPUT_NULL_POINTER;
    }

    if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_CLIENT) {
        if (network_handle->host == NULL) {
            return STATE_PORT_MISSING_HOST;
        }
        return _core_sysdep_network_tcp_establish(network_handle);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_SERVER) {
        return STATE_PORT_TCP_SERVER_NOT_IMPLEMENT;
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_CLIENT) {
        if (network_handle->host == NULL) {
            return STATE_PORT_MISSING_HOST;
        }
        return  _core_sysdep_network_connect(network_handle->host, network_handle->port,
                                             AF_UNSPEC, SOCK_DGRAM, IPPROTO_UDP, network_handle->connect_timeout_ms, &network_handle->fd);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_SERVER) {
        return _core_sysdep_network_udp_server_establish(network_handle);
    }

    printf("unknown nwk type or tcp host absent\n");
    return STATE_PORT_NETWORK_UNKNOWN_SOCKET_TYPE;
}

static int32_t _core_sysdep_network_recv(core_network_handle_t *network_handle, uint8_t *buffer, uint32_t len,
        uint32_t timeout_ms)
{
    int res = 0;
    int32_t recv_bytes = 0;
    ssize_t recv_res = 0;
    uint64_t timestart_ms = 0, timenow_ms = 0, timeselect_ms = 0;
    fd_set recv_sets;
    struct timeval timestart, timenow, timeselect;

    FD_ZERO(&recv_sets);
    FD_SET(network_handle->fd, &recv_sets);

    /* Start Time */
    gettimeofday(&timestart, NULL);
    timestart_ms = timestart.tv_sec * 1000 + timestart.tv_usec / 1000;
    timenow_ms = timestart_ms;

    do {
        gettimeofday(&timenow, NULL);
        timenow_ms = timenow.tv_sec * 1000 + timenow.tv_usec / 1000;

        if (timenow_ms - timestart_ms >= timenow_ms ||
            timeout_ms - (timenow_ms - timestart_ms) > timeout_ms) {
            break;
        }

        timeselect_ms = timeout_ms - (timenow_ms - timestart_ms);
        timeselect.tv_sec = timeselect_ms / 1000;
        timeselect.tv_usec = timeselect_ms % 1000 * 1000;

        res = select(network_handle->fd + 1, &recv_sets, NULL, NULL, &timeselect);
        if (res == 0) {
            /* printf("_core_sysdep_network_recv, nwk select timeout\n"); */
            continue;
        } else if (res < 0) {
            printf("_core_sysdep_network_recv, errno: %d\n", errno);
            perror("_core_sysdep_network_recv, nwk select failed: ");
            return STATE_PORT_NETWORK_SELECT_FAILED;
        } else {
            if (FD_ISSET(network_handle->fd, &recv_sets)) {
                recv_res = recv(network_handle->fd, (char *)buffer + recv_bytes, len - recv_bytes, 0);
                if (recv_res == 0) {
                    printf("_core_sysdep_network_recv, nwk connection closed\n");
                    return STATE_PORT_NETWORK_RECV_CONNECTION_CLOSED;
                } else if (recv_res < 0) {
                    printf("_core_sysdep_network_recv, errno: %d\n", errno);
                    perror("_core_sysdep_network_recv, nwk recv error: ");
                    if (errno == EINTR) {
                        continue;
                    }
                    return STATE_PORT_NETWORK_RECV_FAILED;
                } else {
                    recv_bytes += recv_res;
                    /* printf("recv_bytes: %d, len: %d\n",recv_bytes,len); */
                    if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_CLIENT || recv_bytes == len) {
                        break;
                    }
                }
            }
        }
    } while (((timenow_ms - timestart_ms) < timeout_ms) && (recv_bytes < len));

    /* printf("%s: recv over\n",__FUNCTION__); */
    return recv_bytes;
}

static int32_t _core_sysdep_network_udp_server_recv(core_network_handle_t *network_handle, uint8_t *buffer,
        uint32_t len, uint32_t timeout_ms, core_sysdep_addr_t *addr)
{
    int res;
    struct sockaddr_in cliaddr;
    socklen_t addr_len = sizeof(cliaddr);
    fd_set read_fds;
    struct timeval timeout = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};

    FD_ZERO(&read_fds);
    FD_SET(network_handle->fd, &read_fds);

    res = select(network_handle->fd + 1, &read_fds, NULL, NULL, &timeout);
    if (res == 0) {
        printf("select timeout\n");
        return 0;
    } else if (res < 0) {
        printf("_linux_nwk_udp_read select errno: %d\n", errno);
        perror("_linux_nwk_udp_read select error: ");
        return STATE_PORT_NETWORK_SELECT_FAILED;
    }

    res = recvfrom(network_handle->fd, (char *)buffer, len, 0, (struct sockaddr *)&cliaddr, &addr_len);
    if (res >= 0) {
        if (NULL != addr) {
            addr->port = ntohs(cliaddr.sin_port);
            strcpy((char *)addr->addr, inet_ntoa(cliaddr.sin_addr));
        }

        return res;
    } else {
        printf("_linux_nwk_udp_read errno: %d\n", errno);
        perror("_linux_nwk_udp_read error: ");
        return STATE_PORT_NETWORK_RECV_FAILED;
    }
}

static int32_t core_sysdep_network_recv(void *handle, uint8_t *buffer, uint32_t len, uint32_t timeout_ms,
                                        core_sysdep_addr_t *addr)
{
    core_network_handle_t *network_handle = (core_network_handle_t *)handle;

    if (handle == NULL || buffer == NULL) {
        return STATE_PORT_INPUT_NULL_POINTER;
    }

    if (len == 0 || timeout_ms == 0) {
        return STATE_PORT_INPUT_OUT_RANGE;
    }

    if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_CLIENT) {
        return _core_sysdep_network_recv(network_handle, buffer, len, timeout_ms);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_SERVER) {
        return STATE_PORT_TCP_SERVER_NOT_IMPLEMENT;
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_CLIENT) {
        return _core_sysdep_network_recv(network_handle, buffer, len, timeout_ms);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_SERVER) {
        return _core_sysdep_network_udp_server_recv(network_handle, buffer, len, timeout_ms, addr);
    }

    printf("unknown nwk type\n");

    return STATE_PORT_NETWORK_UNKNOWN_SOCKET_TYPE;
}

int32_t _core_sysdep_network_send(core_network_handle_t *network_handle, uint8_t *buffer, uint32_t len,
                                  uint32_t timeout_ms)
{
    int res = 0;
    int32_t send_bytes = 0;
    ssize_t send_res = 0;
    uint64_t timestart_ms = 0, timenow_ms = 0, timeselect_ms = 0;
    fd_set send_sets;
    struct timeval timestart, timenow, timeselect;

    FD_ZERO(&send_sets);
    FD_SET(network_handle->fd, &send_sets);

    /* Start Time */
    gettimeofday(&timestart, NULL);
    timestart_ms = timestart.tv_sec * 1000 + timestart.tv_usec / 1000;
    timenow_ms = timestart_ms;

    do {
        gettimeofday(&timenow, NULL);
        timenow_ms = timenow.tv_sec * 1000 + timenow.tv_usec / 1000;

        if (timenow_ms - timestart_ms >= timenow_ms ||
            timeout_ms - (timenow_ms - timestart_ms) > timeout_ms) {
            break;
        }

        timeselect_ms = timeout_ms - (timenow_ms - timestart_ms);
        timeselect.tv_sec = timeselect_ms / 1000;
        timeselect.tv_usec = timeselect_ms % 1000 * 1000;

        res = select(network_handle->fd + 1, NULL, &send_sets, NULL, &timeselect);
        if (res == 0) {
            printf("_core_sysdep_network_send, nwk select timeout\n");
            continue;
        } else if (res < 0) {
            printf("_core_sysdep_network_send, errno: %d\n", errno);
            perror("_core_sysdep_network_send, nwk select failed: ");
            return STATE_PORT_NETWORK_SELECT_FAILED;
        } else {
            if (FD_ISSET(network_handle->fd, &send_sets)) {
                send_res = send(network_handle->fd, (const char *)buffer + send_bytes, len - send_bytes, 0);
                if (send_res == 0) {
                    printf("_core_sysdep_network_send, nwk connection closed\n");
                    return STATE_PORT_NETWORK_SEND_CONNECTION_CLOSED;
                } else if (send_res < 0) {
                    printf("_core_sysdep_network_send, errno: %d\n", errno);
                    perror("_core_sysdep_network_send, nwk recv error: ");
                    if (errno == EINTR) {
                        continue;
                    }
                    return STATE_PORT_NETWORK_SEND_FAILED;
                } else {
                    send_bytes += send_res;
                    if (send_bytes == len) {
                        break;
                    }
                }
            }
        }
    } while (((timenow_ms - timestart_ms) < timeout_ms) && (send_bytes < len));

    return send_bytes;
}


int32_t _core_sysdep_network_udp_send(core_network_handle_t *network_handle, uint8_t *buffer, uint32_t len,
                                      uint32_t timeout_ms, core_sysdep_addr_t *addr)
{
    struct sockaddr_in cliaddr;
    fd_set write_fds;
    struct timeval timeout = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
    int res;

    if (addr == NULL) {
        printf("invalid parameter addr\n");
        return STATE_PORT_NETWORK_SEND_FAILED;
    }

    FD_ZERO(&write_fds);
    FD_SET(network_handle->fd, &write_fds);

    res = select(network_handle->fd + 1, NULL, &write_fds, NULL, &timeout);
    if (res == 0) {
        printf("select timeout\n");
        return 0;
    } else if (res < 0) {
        printf("_linux_nwk_udp_write select errno: %d\n", errno);
        perror("_linux_nwk_udp_write select error");
        return STATE_PORT_NETWORK_SELECT_FAILED;
    }

    // res = inet_pton(AF_INET, (char *)addr->addr, &cliaddr.sin_addr);
    cliaddr.sin_addr.s_addr = inet_addr(addr->addr);
    if (cliaddr.sin_addr.s_addr ==  INADDR_NONE) {
        printf("sys_nwk_write, addr error\r\n");
        return STATE_PORT_NETWORK_SEND_FAILED;
    }

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(addr->port);

    res = sendto(network_handle->fd, (const char *)buffer, len, 0, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr_in));
    if (res < 0) {
        printf("_linux_nwk_udp_write errno: %d\n", errno);
        perror("_linux_nwk_udp_write error");
        return STATE_PORT_NETWORK_SEND_FAILED;
    }

    return res;
}

static int32_t core_sysdep_network_send(void *handle, uint8_t *buffer, uint32_t len, uint32_t timeout_ms,
                                        core_sysdep_addr_t *addr)
{
    core_network_handle_t *network_handle = (core_network_handle_t *)handle;

    if (handle == NULL || buffer == NULL) {
        printf("invalid parameter\n");
        return STATE_PORT_INPUT_NULL_POINTER;
    }
    if (len == 0 || timeout_ms == 0) {
        return STATE_PORT_INPUT_OUT_RANGE;
    }

    if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_CLIENT) {
        return _core_sysdep_network_send(network_handle, buffer, len, timeout_ms);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_SERVER) {
        return STATE_PORT_TCP_SERVER_NOT_IMPLEMENT;
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_CLIENT) {
        return _core_sysdep_network_send(network_handle, buffer, len, timeout_ms);
    } else if (network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_SERVER) {
        return _core_sysdep_network_udp_send(network_handle, buffer, len, timeout_ms, addr);
    }

    printf("unknown nwk type\n");
    return STATE_PORT_NETWORK_UNKNOWN_SOCKET_TYPE;
}

static void _core_sysdep_network_tcp_disconnect(core_network_handle_t *network_handle)
{
    shutdown(network_handle->fd, 2);
    close(network_handle->fd);
    WSACleanup();
}

static int32_t core_sysdep_network_deinit(void **handle)
{
    core_network_handle_t *network_handle = NULL;

    if (handle == NULL || *handle == NULL) {
        return STATE_PORT_INPUT_NULL_POINTER;
    }

    network_handle = *(core_network_handle_t **)handle;

    /* Shutdown both send and receive operations. */
    if ((network_handle->socket_type == CORE_SYSDEP_SOCKET_TCP_CLIENT ||
         network_handle->socket_type == CORE_SYSDEP_SOCKET_UDP_CLIENT) && network_handle->host != NULL) {
        _core_sysdep_network_tcp_disconnect(network_handle);
    }

    if (network_handle->host != NULL) {
        free(network_handle->host);
        network_handle->host = NULL;
    }

    free(network_handle);
    *handle = NULL;

    return 0;
}

void core_sysdep_rand(uint8_t *output, uint32_t output_len)
{
    uint32_t idx = 0, bytes = 0, rand_num = 0;
    struct timeval time;

    memset(&time, 0, sizeof(struct timeval));
    gettimeofday(&time, NULL);

    srand((unsigned int)(time.tv_sec * 1000 + time.tv_usec / 1000) + rand());

    for (idx = 0; idx < output_len;) {
        if (output_len - idx < 4) {
            bytes = output_len - idx;
        } else {
            bytes = 4;
        }
        rand_num = rand();
        while (bytes-- > 0) {
            output[idx++] = (uint8_t)(rand_num >> bytes * 8);
        }
    }
}

void *core_sysdep_mutex_init(void)
{
    int res = 0;
    pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (NULL == mutex) {
        return NULL;
    }

    if (0 != (res = pthread_mutex_init(mutex, NULL))) {
        perror("create mutex failed\n");
        free(mutex);
        return NULL;
    }
    /* printf("init mutex: %p\n",mutex); */

    return (void *)mutex;
}

void core_sysdep_mutex_lock(void *mutex)
{
    int res = 0;
    if (mutex != NULL) {
        if (0 != (res = pthread_mutex_lock((pthread_mutex_t *)mutex))) {
            printf("lock mutex failed: - '%s' (%d)\n", strerror(res), res);
        }
    }
}

void core_sysdep_mutex_unlock(void *mutex)
{
    int res = 0;
    if (mutex != NULL) {
        if (0 != (res = pthread_mutex_unlock((pthread_mutex_t *)mutex))) {
            printf("unlock mutex failed - '%s' (%d)\n", strerror(res), res);
        }
    }
}

void core_sysdep_mutex_deinit(void **mutex)
{
    int err_num = 0;
    if (mutex != NULL) {
        /* printf("deinit mutex: %p\n",mutex); */
        if (0 != (err_num = pthread_mutex_destroy(*(pthread_mutex_t **)mutex))) {
            perror("destroy mutex failed\n");
        }
        free(*(pthread_mutex_t **)mutex);
        *mutex = NULL;
    }
}

aiot_sysdep_portfile_t g_aiot_sysdep_portfile = {
    .core_sysdep_malloc = core_sysdep_malloc,
    .core_sysdep_free = core_sysdep_free,
    .core_sysdep_time = core_sysdep_time,
    .core_sysdep_sleep = core_sysdep_sleep,
    .core_sysdep_network_init = core_sysdep_network_init,
    .core_sysdep_network_setopt = core_sysdep_network_setopt,
    .core_sysdep_network_establish = core_sysdep_network_establish,
    .core_sysdep_network_recv = core_sysdep_network_recv,
    .core_sysdep_network_send = core_sysdep_network_send,
    .core_sysdep_network_deinit = core_sysdep_network_deinit,
    .core_sysdep_rand = core_sysdep_rand,
    .core_sysdep_mutex_init = core_sysdep_mutex_init,
    .core_sysdep_mutex_lock = core_sysdep_mutex_lock,
    .core_sysdep_mutex_unlock = core_sysdep_mutex_unlock,
    .core_sysdep_mutex_deinit = core_sysdep_mutex_deinit,
};

