TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    lib/core/adopt.c \
    lib/core/alloc.c \
    lib/core/connect.c \
    lib/core/context.c \
    lib/core/dummy-callback.c \
    lib/core/libwebsockets.c \
    lib/core/output.c \
    lib/core/pollfd.c \
    lib/core/service.c \
    lib/event-libs/poll/poll.c \
    lib/misc/base64-decode.c \
    lib/misc/jws/jwk.c \
    lib/misc/jws/jws.c \
    lib/misc/lejp.c \
    lib/misc/lws-ring.c \
    lib/misc/peer-limits.c \
    lib/misc/sha-1.c \
    lib/plat/windows/windows-fds.c \
    lib/plat/windows/windows-file.c \
    lib/plat/windows/windows-init.c \
    lib/plat/windows/windows-misc.c \
    lib/plat/windows/windows-pipe.c \
    lib/plat/windows/windows-service.c \
    lib/plat/windows/windows-sockets.c \
    lib/roles/h1/ops-h1.c \
    lib/roles/h2/hpack.c \
    lib/roles/h2/http2.c \
    lib/roles/h2/ops-h2.c \
    lib/roles/http/client/client-handshake.c \
    lib/roles/http/client/client.c \
    lib/roles/http/header.c \
    lib/roles/http/server/parsers.c \
    lib/roles/http/server/ranges.c \
    lib/roles/http/server/rewrite.c \
    lib/roles/http/server/server.c \
    lib/roles/listen/ops-listen.c \
    lib/roles/pipe/ops-pipe.c \
    lib/roles/raw-file/ops-raw-file.c \
    lib/roles/raw-skt/ops-raw-skt.c \
    lib/roles/ws/client-parser-ws.c \
    lib/roles/ws/client-ws.c \
    lib/roles/ws/ext/extension.c \
    lib/roles/ws/ops-ws.c \
    lib/roles/ws/server-ws.c \
    lib/tls/mbedtls/lws-genhash.c \
    lib/tls/mbedtls/lws-genrsa.c \
    lib/tls/mbedtls/mbedtls-client.c \
    lib/tls/mbedtls/mbedtls-server.c \
    lib/tls/mbedtls/ssl.c \
    lib/tls/mbedtls/wrapper/library/ssl_cert.c \
    lib/tls/mbedtls/wrapper/library/ssl_lib.c \
    lib/tls/mbedtls/wrapper/library/ssl_methods.c \
    lib/tls/mbedtls/wrapper/library/ssl_pkey.c \
    lib/tls/mbedtls/wrapper/library/ssl_stack.c \
    lib/tls/mbedtls/wrapper/library/ssl_x509.c \
    lib/tls/mbedtls/wrapper/platform/ssl_pm.c \
    lib/tls/mbedtls/wrapper/platform/ssl_port.c \
    lib/tls/tls-client.c \
    lib/tls/tls-server.c \
    lib/tls/tls.c \
    mbedtls/aes.c \
    mbedtls/aesni.c \
    mbedtls/arc4.c \
    mbedtls/aria.c \
    mbedtls/asn1parse.c \
    mbedtls/asn1write.c \
    mbedtls/base64.c \
    mbedtls/bignum.c \
    mbedtls/blowfish.c \
    mbedtls/camellia.c \
    mbedtls/ccm.c \
    mbedtls/certs.c \
    mbedtls/chacha20.c \
    mbedtls/chachapoly.c \
    mbedtls/cipher.c \
    mbedtls/cipher_wrap.c \
    mbedtls/cmac.c \
    mbedtls/ctr_drbg.c \
    mbedtls/debug.c \
    mbedtls/des.c \
    mbedtls/dhm.c \
    mbedtls/ecdh.c \
    mbedtls/ecdsa.c \
    mbedtls/ecjpake.c \
    mbedtls/ecp.c \
    mbedtls/ecp_curves.c \
    mbedtls/entropy.c \
    mbedtls/entropy_poll.c \
    mbedtls/error.c \
    mbedtls/gcm.c \
    mbedtls/havege.c \
    mbedtls/hkdf.c \
    mbedtls/hmac_drbg.c \
    mbedtls/md.c \
    mbedtls/md2.c \
    mbedtls/md4.c \
    mbedtls/md5.c \
    mbedtls/md_wrap.c \
    mbedtls/memory_buffer_alloc.c \
    mbedtls/net_sockets.c \
    mbedtls/nist_kw.c \
    mbedtls/oid.c \
    mbedtls/padlock.c \
    mbedtls/pem.c \
    mbedtls/pk.c \
    mbedtls/pk_wrap.c \
    mbedtls/pkcs11.c \
    mbedtls/pkcs12.c \
    mbedtls/pkcs5.c \
    mbedtls/pkparse.c \
    mbedtls/pkwrite.c \
    mbedtls/platform.c \
    mbedtls/platform_util.c \
    mbedtls/poly1305.c \
    mbedtls/ripemd160.c \
    mbedtls/rsa.c \
    mbedtls/rsa_internal.c \
    mbedtls/selftest.c \
    mbedtls/sha1.c \
    mbedtls/sha256.c \
    mbedtls/sha512.c \
    mbedtls/ssl_cache.c \
    mbedtls/ssl_ciphersuites.c \
    mbedtls/ssl_cli.c \
    mbedtls/ssl_cookie.c \
    mbedtls/ssl_srv.c \
    mbedtls/ssl_ticket.c \
    mbedtls/ssl_tls.c \
    mbedtls/threading.c \
    mbedtls/timing.c \
    mbedtls/version.c \
    mbedtls/version_features.c \
    mbedtls/x509.c \
    mbedtls/x509_create.c \
    mbedtls/x509_crl.c \
    mbedtls/x509_crt.c \
    mbedtls/x509_csr.c \
    mbedtls/x509write_crt.c \
    mbedtls/x509write_csr.c \
    mbedtls/xtea.c \
    minimal-examples/ws-client/minimal-ws-client-rx/minimal-ws-client.c



DISTFILES += \
    minimal-examples/ws-client/minimal-ws-client-ping/libwebsockets.org.cer



HEADERS += \
    config/lws_config.h \
    config/lws_config_private.h \
    mbedtls/mbedtls/config.h

INCLUDEPATH += \
    . \
    include \
    lib/tls/mbedtls \
    lib/tls/mbedtls/wrapper/include \
    lib/tls/mbedtls/wrapper/include/internal  \
    lib/tls/mbedtls/wrapper/include/openssl \
    lib/tls/mbedtls/wrapper/include/platform  \
    lib/tls \
    config \
    mbedtls \
    lib/core \
    lib/event-libs \
    lib/event-libs/libevent \
    lib/event-libs/libuv \
    lib/event-libs/poll \
    lib/misc \
    lib/misc/lwsac \
    lib/plat/windows \
    lib/roles/h1 \
    lib/roles/http/compression \
    lib/roles/http \
    lib/roles \
    lib/roles/ws/ext \
    lib/roles/ws \
    lib/tls/mbedtls/wrapper/include/interna \
    lib \


LIBS += -lws2_32


