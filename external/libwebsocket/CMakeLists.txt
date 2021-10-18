cmake_minimum_required(VERSION 3.5)


project(libwebsocket LANGUAGES C)

set(libwebsocket_src 
	lib/core/adopt.c 
	lib/core/alloc.c 
	lib/core/connect.c 
	lib/core/context.c 
	lib/core/dummy-callback.c 
	lib/core/libwebsockets.c 
	lib/core/output.c 
	lib/core/pollfd.c 
	lib/core/service.c 
	lib/event-libs/poll/poll.c 
	lib/misc/base64-decode.c 
	lib/misc/jws/jwk.c 
	lib/misc/jws/jws.c 
	lib/misc/lejp.c 
	lib/misc/lws-ring.c 
	lib/misc/peer-limits.c 
	lib/misc/sha-1.c 
	lib/plat/windows/windows-fds.c 
	lib/plat/windows/windows-file.c 
	lib/plat/windows/windows-init.c 
	lib/plat/windows/windows-misc.c 
	lib/plat/windows/windows-pipe.c 
	lib/plat/windows/windows-service.c 
	lib/plat/windows/windows-sockets.c 
	lib/roles/h1/ops-h1.c 
	lib/roles/h2/hpack.c 
	lib/roles/h2/http2.c 
	lib/roles/h2/ops-h2.c 
	lib/roles/http/client/client-handshake.c 
	lib/roles/http/client/client.c 
	lib/roles/http/header.c 
	lib/roles/http/server/parsers.c 
	lib/roles/http/server/ranges.c 
	lib/roles/http/server/rewrite.c 
	lib/roles/http/server/server.c 
	lib/roles/listen/ops-listen.c 
	lib/roles/pipe/ops-pipe.c 
	lib/roles/raw-file/ops-raw-file.c 
	lib/roles/raw-skt/ops-raw-skt.c 
	lib/roles/ws/client-parser-ws.c 
	lib/roles/ws/client-ws.c 
	lib/roles/ws/ext/extension.c 
	lib/roles/ws/ops-ws.c 
	lib/roles/ws/server-ws.c 
	lib/tls/mbedtls/lws-genhash.c 
	lib/tls/mbedtls/lws-genrsa.c 
	lib/tls/mbedtls/mbedtls-client.c 
	lib/tls/mbedtls/mbedtls-server.c 
	lib/tls/mbedtls/ssl.c 
	lib/tls/mbedtls/wrapper/library/ssl_cert.c 
	lib/tls/mbedtls/wrapper/library/ssl_lib.c 
	lib/tls/mbedtls/wrapper/library/ssl_methods.c 
	lib/tls/mbedtls/wrapper/library/ssl_pkey.c 
	lib/tls/mbedtls/wrapper/library/ssl_stack.c 
	lib/tls/mbedtls/wrapper/library/ssl_x509.c 
	lib/tls/mbedtls/wrapper/platform/ssl_pm.c 
	lib/tls/mbedtls/wrapper/platform/ssl_port.c 
	lib/tls/tls-client.c 
	lib/tls/tls-server.c 
	lib/tls/tls.c 
)

add_library(libwebsocket STATIC ${libwebsocket_src})

target_link_libraries(libwebsocket mbedtls)

target_include_directories(libwebsocket PUBLIC
	include 
	lib/tls/mbedtls 
	lib/tls/mbedtls/wrapper/include 
	lib/tls/mbedtls/wrapper/include/internal  
	lib/tls/mbedtls/wrapper/include/openssl 
	lib/tls/mbedtls/wrapper/include/platform  
	lib/tls 
	config 
	lib/core 
	lib/event-libs 
	lib/event-libs/libevent 
	lib/event-libs/libuv 
	lib/event-libs/poll 
	lib/misc 
	lib/misc/lwsac 
	lib/plat/windows 
	lib/roles/h1 
	lib/roles/http/compression 
	lib/roles/http 
	lib/roles 
	lib/roles/ws/ext 
	lib/roles/ws 
	lib/tls/mbedtls/wrapper/include/interna 
	lib 
)

