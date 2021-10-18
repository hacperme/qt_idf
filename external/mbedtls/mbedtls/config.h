/*
 *  Configuration template
 *
 *  Copyright (C) 2006-2018, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

/*
 * This set of compile-time options may be used to enable
 * or disable features selectively, and reduce the global
 * memory footprint.
 */
#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* System support */
#define MBEDTLS_HAVE_ASM            // 需要编译器可以处理汇编代码
#define MBEDTLS_HAVE_TIME
#define MBEDTLS_HAVE_TIME_DATE
#define MBEDTLS_PLATFORM_MEMORY
//#define MBEDTLS_PLATFORM_NO_STD_FUNCTIONS
//#define MBEDTLS_CHECK_PARAMS

/* mbed TLS feature support */
#define MBEDTLS_AES_ROM_TABLES      // 将 AES 表存储在 ROM 中以节省 RAM 占用
//#define MBEDTLS_AES_FEWER_TABLES
//#define MBEDTLS_CAMELLIA_SMALL_MEMORY
#define MBEDTLS_CIPHER_MODE_CBC         // 为对称密码启用密码块链接模式（CBC）。如果使用了 CBC 密码套件则需要启用
//#define MBEDTLS_CIPHER_MODE_CFB
//#define MBEDTLS_CIPHER_MODE_CTR
//#define MBEDTLS_CIPHER_MODE_OFB
//#define MBEDTLS_CIPHER_MODE_XTS
#define MBEDTLS_CIPHER_PADDING_PKCS7            // 在密码层中启用填充模式。如果禁用所有填充模式，则只有完整块可以与 CBC 一起使用
//#define MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS
//#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN
//#define MBEDTLS_CIPHER_PADDING_ZEROS
//#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED        // 在椭圆曲线模块中启用特定的曲线
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#define MBEDTLS_ECP_DP_BP512R1_ENABLED
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#define MBEDTLS_ECP_DP_CURVE448_ENABLED
//#define MBEDTLS_ECP_NIST_OPTIM          // 为每个 NIST 启用特定的实例，使相应曲线上的操作快 4 到 8 倍，缺点是 ROM 占用大。可以选择性优化
#define MBEDTLS_ECP_RESTARTABLE
#define MBEDTLS_ECDSA_DETERMINISTIC         // 启用确定性 ECDSA（RFC 6979），防止签名时缺少熵而导致签名密钥泄露。建议启用
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED
#define MBEDTLS_PK_PARSE_EC_EXTENDED
//#define MBEDTLS_ERROR_STRERROR_DUMMY
#define MBEDTLS_GENPRIME
#define MBEDTLS_FS_IO
//#define MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES
//#define MBEDTLS_NO_PLATFORM_ENTROPY         // 如果您的平台不支持 /dev/urandom 或 Windows CryptoAPI 等标准，则需要启用该配置。
//#define MBEDTLS_ENTROPY_FORCE_SHA256
//#define MBEDTLS_ENTROPY_NV_SEED
//#define MBEDTLS_MEMORY_DEBUG
//#define MBEDTLS_MEMORY_BACKTRACE
//#define MBEDTLS_PK_RSA_ALT_SUPPORT
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
//#define MBEDTLS_RSA_NO_CRT
//#define MBEDTLS_SELF_TEST                   //算法自检功能，在调试的时候打开
//#define MBEDTLS_SHA256_SMALLER
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES
//#define MBEDTLS_SSL_ASYNC_PRIVATE
#define MBEDTLS_SSL_DEBUG_ALL
//#define MBEDTLS_SSL_ENCRYPT_THEN_MAC
//#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET
//#define MBEDTLS_SSL_FALLBACK_SCSV
//#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
//#define MBEDTLS_SSL_HW_RECORD_ACCEL
//#define MBEDTLS_SSL_CBC_RECORD_SPLITTING
//#define MBEDTLS_SSL_RENEGOTIATION
//#define MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO
//#define MBEDTLS_SSL_SRV_RESPECT_CLIENT_PREFERENCE
//#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_PROTO_SSL3
#define MBEDTLS_SSL_PROTO_TLS1
#define MBEDTLS_SSL_PROTO_TLS1_1
#define MBEDTLS_SSL_PROTO_TLS1_2
//#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_ALPN
//#define MBEDTLS_SSL_DTLS_ANTI_REPLAY
//#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
//#define MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
//#define MBEDTLS_SSL_DTLS_BADMAC_LIMIT
//#define MBEDTLS_SSL_SESSION_TICKETS
//#define MBEDTLS_SSL_EXPORT_KEYS
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
//#define MBEDTLS_SSL_TRUNCATED_HMAC
//#define MBEDTLS_VERSION_FEATURES                            // 版本功能信息相关
//#define MBEDTLS_X509_ALLOW_EXTENSIONS_NON_V3
//#define MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
//#define MBEDTLS_X509_CHECK_KEY_USAGE
//#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
//#define MBEDTLS_X509_RSASSA_PSS_SUPPORT


/* mbed TLS modules */
#define MBEDTLS_AES_C              // 启用 AES 加密。PEM_PARSE 使用 AES 来解密被加密的密钥。通过启用 AES 来支持 *_WITH_AES_* 类型的加密套件
//#define MBEDTLS_ARC4_C
#define MBEDTLS_ASN1_PARSE_C       // 使能通用的 ASN1 解析器。ASN1: 一种描述数字对象的方法和标准，需要启用
#define MBEDTLS_ASN1_WRITE_C       // 启用通用 ASN1 编写器
#define MBEDTLS_BASE64_C           // 启用 base64 组件，PEM 证书解析需要使用
#define MBEDTLS_BIGNUM_C           // 启用大整数库 （multi-precision integer library）
//#define MBEDTLS_BLOWFISH_C
//#define MBEDTLS_CAMELLIA_C
//#define MBEDTLS_ARIA_C
//#define MBEDTLS_CCM_C
#define MBEDTLS_CERTS_C
//#define MBEDTLS_CHACHA20_C
//#define MBEDTLS_CHACHAPOLY_C
#define MBEDTLS_CIPHER_C          // 启用通用密码层
//#define MBEDTLS_CMAC_C
#define MBEDTLS_CTR_DRBG_C        // 启用基于 CTR_DRBG AES-256 的随机生成器
#define MBEDTLS_DEBUG_C         // 开启调试功能
#define MBEDTLS_DES_C
#define MBEDTLS_DHM_C
#define MBEDTLS_ECDH_C          // 启用椭圆曲线 Diffie-Hellman 库。用于支持 *_ECDHE_ECDSA_*、*_ECDHE_RSA_*、*_DHE_PSK_* 类型的密码套件
#define MBEDTLS_ECDSA_C         // 用于支持 *_ECDHE_ECDSA_* 类型的密码套件
#define MBEDTLS_ECJPAKE_C
#define MBEDTLS_ECP_C           // 启用 GF(p) 椭圆曲线
#define MBEDTLS_ENTROPY_C       // 启用特定于平台的熵代码。需要启用
#define MBEDTLS_ERROR_C
//#define MBEDTLS_GCM_C
//#define MBEDTLS_HAVEGE_C
//#define MBEDTLS_HKDF_C
#define MBEDTLS_HMAC_DRBG_C         // 启用随机字节发生器
//#define MBEDTLS_NIST_KW_C
#define MBEDTLS_MD_C            //启用通用消息摘要层，需要启用
//#define MBEDTLS_MD2_C
//#define MBEDTLS_MD4_C
#define MBEDTLS_MD5_C
//#define MBEDTLS_MEMORY_BUFFER_ALLOC_C
#define MBEDTLS_NET_C
#define MBEDTLS_OID_C           // 启用OID数据库，此模块在OID和内部值之间进行转换，需要启用
#define MBEDTLS_PEM_PARSE_C     // 启用对 PEM 文件解码解析的支持
#define MBEDTLS_PEM_WRITE_C     // 此模块添加了对编码/写入PEM文件的支持
#define MBEDTLS_PK_C            // 启用通用公共（非对称）密钥层，需要启用
#define MBEDTLS_PK_PARSE_C      // 启用通用公共（非对称）密钥解析器，需要启用
#define MBEDTLS_PK_WRITE_C      // 启用通用公钥写入功能。嵌入式系统一般不需要
//#define MBEDTLS_PKCS5_C
//#define MBEDTLS_PKCS11_C
//#define MBEDTLS_PKCS12_C
#define MBEDTLS_PLATFORM_C     // 使能平台抽象层，用于重定义实现 free、printf 等函数
//#define MBEDTLS_POLY1305_C
//#define MBEDTLS_RIPEMD160_C
#define MBEDTLS_RSA_C
#define MBEDTLS_SHA1_C              // 启用 SHA1 加密哈希算法。TLS 1.1/1.2 需要使用
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C
//#define MBEDTLS_SSL_CACHE_C
//#define MBEDTLS_SSL_COOKIE_C
//#define MBEDTLS_SSL_TICKET_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_PKCS1_V21
#define MBEDTLS_SSL_TLS_C
// #define MBEDTLS_THREADING_C
#define MBEDTLS_TIMING_C
//#define MBEDTLS_VERSION_C           //该模块提供运行时版本信息
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CRL_PARSE_C
#define MBEDTLS_X509_CSR_PARSE_C
//#define MBEDTLS_X509_CREATE_C
//#define MBEDTLS_X509_CRT_WRITE_C
//#define MBEDTLS_X509_CSR_WRITE_C
//#define MBEDTLS_XTEA_C


// 添加用户宏定义开关

// #define MBEDTLS_DEPRECATED_REMOVED                  // 去除废弃的功能方法
#define MBEDTLS_ENTROPY_MAX_SOURCES 2               // 最大的熵源数量，最小为2
#define MBEDTLS_ECP_FIXED_POINT_OPTIM 0             // 默认1，启用定点加速。启用后，将加速点乘运算大约 3 到 4 倍，成本是峰值内存占用增加约 2 倍。可以配置为 0，牺牲速度来节省 RAM 占用
#define MBEDTLS_ECP_WINDOW_SIZE 2                   // 用于点乘的最大窗口大小，默认为 6，选值范围： 2-7，可以适当减小，减小会影响速度
#define MBEDTLS_ECP_MAX_BITS         384            // GF(p) 椭圆曲线最大位，默认为 521
#define MBEDTLS_MPI_WINDOW_SIZE        2            // MPI 用于模幂运算的最大窗口数量，默认为6，选值范围：1-6，可适当调小
#define MBEDTLS_MPI_MAX_SIZE         384            // 可用的 MPI 最大字节数，默认为 1024，可以根据适当调小

#include "check_config.h"

#endif /* MBEDTLS_CONFIG_H */
