/*
 * lws-minimal-ws-client
 *
 * Copyright (C) 2018 Andy Green <andy@warmcat.com>
 *
 * This file is made available under the Creative Commons CC0 1.0
 * Universal Public Domain Dedication.
 *
 * This demonstrates the a minimal ws client using lws.
 *
 * It connects to https://libwebsockets.org/ and makes a
 * wss connection to the dumb-increment protocol there.  While
 * connected, it prints the numbers it is being sent by
 * dumb-increment protocol.
 */

#include <libwebsockets.h>
#include <string.h>
#include <signal.h>

#define MAX_PAYLOAD_SIZE 1000

#define TEST_CA_CRT_RSA                                                 \
"-----BEGIN CERTIFICATE-----\r\n"                                       \
"MIIDhzCCAm+gAwIBAgIBADANBgkqhkiG9w0BAQUFADA7MQswCQYDVQQGEwJOTDER\r\n"  \
"MA8GA1UEChMIUG9sYXJTU0wxGTAXBgNVBAMTEFBvbGFyU1NMIFRlc3QgQ0EwHhcN\r\n"  \
"MTEwMjEyMTQ0NDAwWhcNMjEwMjEyMTQ0NDAwWjA7MQswCQYDVQQGEwJOTDERMA8G\r\n"  \
"A1UEChMIUG9sYXJTU0wxGTAXBgNVBAMTEFBvbGFyU1NMIFRlc3QgQ0EwggEiMA0G\r\n"  \
"CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDA3zf8F7vglp0/ht6WMn1EpRagzSHx\r\n"  \
"mdTs6st8GFgIlKXsm8WL3xoemTiZhx57wI053zhdcHgH057Zk+i5clHFzqMwUqny\r\n"  \
"50BwFMtEonILwuVA+T7lpg6z+exKY8C4KQB0nFc7qKUEkHHxvYPZP9al4jwqj+8n\r\n"  \
"YMPGn8u67GB9t+aEMr5P+1gmIgNb1LTV+/Xjli5wwOQuvfwu7uJBVcA0Ln0kcmnL\r\n"  \
"R7EUQIN9Z/SG9jGr8XmksrUuEvmEF/Bibyc+E1ixVA0hmnM3oTDPb5Lc9un8rNsu\r\n"  \
"KNF+AksjoBXyOGVkCeoMbo4bF6BxyLObyavpw/LPh5aPgAIynplYb6LVAgMBAAGj\r\n"  \
"gZUwgZIwDAYDVR0TBAUwAwEB/zAdBgNVHQ4EFgQUtFrkpbPe0lL2udWmlQ/rPrzH\r\n"  \
"/f8wYwYDVR0jBFwwWoAUtFrkpbPe0lL2udWmlQ/rPrzH/f+hP6Q9MDsxCzAJBgNV\r\n"  \
"BAYTAk5MMREwDwYDVQQKEwhQb2xhclNTTDEZMBcGA1UEAxMQUG9sYXJTU0wgVGVz\r\n"  \
"dCBDQYIBADANBgkqhkiG9w0BAQUFAAOCAQEAuP1U2ABUkIslsCfdlc2i94QHHYeJ\r\n"  \
"SsR4EdgHtdciUI5I62J6Mom+Y0dT/7a+8S6MVMCZP6C5NyNyXw1GWY/YR82XTJ8H\r\n"  \
"DBJiCTok5DbZ6SzaONBzdWHXwWwmi5vg1dxn7YxrM9d0IjxM27WNKs4sDQhZBQkF\r\n"  \
"pjmfs2cb4oPl4Y9T9meTx/lvdkRYEug61Jfn6cA+qHpyPYdTH+UshITnmp5/Ztkf\r\n"  \
"m/UTSLBNFNHesiTZeH31NcxYGdHSme9Nc/gfidRa0FLOCfWxRlFqAI47zG9jAQCZ\r\n"  \
"7Z2mCGDNMhjQc+BYcdnl0lPXjdDK6V0qCg1dVewhUBcW5gZKzV7e9+DpVA==\r\n"      \
"-----END CERTIFICATE-----\r\n"
const char mbedtls_test_ca_crt_rsa[] = TEST_CA_CRT_RSA;

/**
 * 会话上下文对象，结构根据需要自定义
 */
struct session_data {
    int msg_count;
    unsigned char buf[LWS_PRE + MAX_PAYLOAD_SIZE];
    int len;
};

static int interrupted, rx_seen, test;
static struct lws *client_wsi;

int ssl_connection = LCCSCF_USE_SSL;

static int
callback_dumb_increment(struct lws *wsi, enum lws_callback_reasons reason,
	      void *user, void *in, size_t len)
{
    printf("reason=%d\n",reason);
    struct session_data *data = (struct session_data *) user;
	switch (reason) {

	/* because we are protocols[0] ... */
	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
			 in ? (char *)in : "(null)");
		client_wsi = NULL;
		break;

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		lwsl_user("%s: established\n", __func__);
        lws_callback_on_writable( wsi );
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		lwsl_user("RX: %s\n", (const char *)in);
		rx_seen++;
		if (test && rx_seen == 10)
			interrupted = 1;
        lws_callback_on_writable(wsi);
		break;

	case LWS_CALLBACK_CLIENT_CLOSED:
        lwsl_user("LWS_CALLBACK_CLIENT_CLOSED\n");
        client_wsi = NULL;
		break;

    case LWS_CALLBACK_CLIENT_WRITEABLE:
        lwsl_user("11111111111111\n");
        if ( data->msg_count < 11 )
       {
           // 前面LWS_PRE个字节必须留给LWS
           memset(data->buf, 0, sizeof(data->buf));
           char *msg = (char *)&data->buf[LWS_PRE];
           data->len = sprintf(msg, "123 %d", ++data->msg_count);
           lwsl_notice("Tx: %s\n", msg);
           // 通过WebSocket发送文本消息
           lws_write(wsi, &data->buf[LWS_PRE], data->len, LWS_WRITE_TEXT);

       }
       else
       {
           // 退出客户端
           client_wsi = NULL;
       }

    break;
        /* rate-limited client connect retries */

        case LWS_CALLBACK_USER:
            lwsl_notice("%s: LWS_CALLBACK_USER\n", __func__);
//    try:
//            if (connect_client())
//                lws_timed_callback_vh_protocol(lws_get_vhost(wsi),
//                                   lws_get_protocol(wsi),
//                                   LWS_CALLBACK_USER, 1);
            break;
	default:
		break;
	}

	return lws_callback_http_dummy(wsi, reason, user, in, len);
}

static const struct lws_protocols protocols[] = {
	{
        "wss",
		callback_dumb_increment,
        sizeof( struct session_data ),
        200,
	},
	{ NULL, NULL, 0, 0 }
};

static void
sigint_handler(int sig)
{
     printf("interrupted=%d\n",interrupted);
	interrupted = 1;
}

 void log_function_cus(int level, const char *line)
 {
     printf("123-%d-%s", level, line);
 }


int main(int argc, const char **argv)
{
	struct lws_context_creation_info info;
	struct lws_client_connect_info i;
	struct lws_context *context;
	const char *p;
	int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE
		/* for LLL_ verbosity above NOTICE to be built into lws, lws
		 * must have been configured with -DCMAKE_BUILD_TYPE=DEBUG
		 * instead of =RELEASE */
		/* | LLL_INFO */ /* | LLL_PARSER */ /* | LLL_HEADER */
		/* | LLL_EXT */ /* | LLL_CLIENT */ /* | LLL_LATENCY */
		/* | LLL_DEBUG */;

	signal(SIGINT, sigint_handler);
	if ((p = lws_cmdline_option(argc, argv, "-d")))
		logs = atoi(p);

	test = !!lws_cmdline_option(argc, argv, "-t");

	lws_set_log_level(logs, NULL);
	lwsl_user("LWS minimal ws client rx [-d <logs>] [--h2] [-t (test)]\n");

	memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
	info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
	info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
	info.protocols = protocols;
#if defined(LWS_WITH_MBEDTLS)
	/*
	 * OpenSSL uses the system trust store.  mbedTLS has to be told which
	 * CA to trust explicitly.
	 */
//    info.client_ssl_ca_filepath = "E:\\workspace\\libwebsocket_with_qt\\minimal-examples\\ws-client\\minimal-ws-client-ping\\libwebsockets.org.cer";
//    info.client_ssl_ca_filepath = NULL;
    info.client_ssl_ca_mem = mbedtls_test_ca_crt_rsa;
    info.client_ssl_ca_mem_len = strlen(mbedtls_test_ca_crt_rsa)+1;
#endif

	context = lws_create_context(&info);
	if (!context) {
		lwsl_err("lws init failed\n");
		return 1;
	}

	memset(&i, 0, sizeof i); /* otherwise uninitialized garbage */
	i.context = context;
    i.port = 443;
    i.address = "xvstc.xiaoyastar.com";
    i.path = "/ws02/ws/ws-voice?param=%7B%22osAccessToken%22%3A%22eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJvcy5jbGllbnQuMDAwMzY4IiwidWlkIjo4MzM3OTg5OCwic3YiOiIyIiwicHJvZHVjdElkIjoiU19QUk9EMV8xMTcxIiwiZXhwIjoxNjI3NTUyOTkwLCJkZXZpY2VJZCI6IjExNTMwXzAwXzEwMDUzMF9hNDVmYWRhYzlkZmYifQ.Y6vzYQveO4nrpVvvqisG2D4VPGXLBZRp6sqGTxAjcqY%22%2C%22dt%22%3A39590%2C%22device%22%3A%7B%22sn%22%3A%2211530_00_100530_a45fadac9dff%22%2C%22os%22%3A%22rtos%22%7D%2C%22product%22%3A%7B%22id%22%3A%22S_PROD1_1171%22%7D%2C%22version%22%3A%7B%22os%22%3A%221.6.42%22%2C%22app%22%3A%221.6.42%22%7D%7D&sid=%7B%22sid%22%3A%224a47b5f7-1dc91b43-3a923786%22%7D&sig=694ef0176fb0785d64fe26d91ad24936";
    i.host = i.address;
	i.origin = i.address;
    ssl_connection |= LCCSCF_ALLOW_SELFSIGNED;
    i.ssl_connection = ssl_connection;
	i.protocol = protocols[0].name; /* "dumb-increment-protocol" */
	i.pwsi = &client_wsi;

	if (lws_cmdline_option(argc, argv, "--h2"))
		i.alpn = "h2";

	lws_client_connect_via_info(&i);

    while (n >= 0 && client_wsi && !interrupted){
        n = lws_service(context, 1000);
//        printf("n=%d\n",n);
//        printf("client_wsi=%d\n",client_wsi);

    }

	lws_context_destroy(context);

	lwsl_user("Completed %s\n", rx_seen > 10 ? "OK" : "Failed");

	return rx_seen > 10;
}
