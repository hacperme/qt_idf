/**
 * @file      nr_micro_shell_commands.c
 * @author    Nrush
 * @version   V0.1
 * @date      28 Oct 2019
 * *****************************************************************************
 * @attention
 * 
 * MIT License
 * 
 * Copyright (C) 2019 Nrush. or its affiliates.  All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Includes ------------------------------------------------------------------*/

#include "nr_micro_shell.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "miniaudio.h"
#include "qrencode.h"
#include "qrspec.h"
#include "dlg/dlg.h"
#include <uECC.h>
#include "qt_idf_tls.h"

extern void shell_lvgl_cmd(int argc, char *argv);
extern void shell_cbor_cmd(int argc, char *argv);
extern void shell_hmac_cmd(int argc, char *argv);

/**
 * @brief help command
 */
void shell_help_cmd(int argc, char *argv)
{
	unsigned int i = 0;

	for (i = 0; nr_shell.static_cmd[i].fp != NULL; i++)
	{
		shell_printf("%s", nr_shell.static_cmd[i].cmd);
		shell_printf("\r\n");
	}
}

/**
 * @brief test command
 */
void shell_test_cmd(int argc, char *argv)
{
	unsigned int i;
	shell_printf("test command:\r\n");
	for (i = 0; i < argc; i++)
	{
		shell_printf("paras %d: %s\r\n", i, &(argv[(int)argv[i]]));
	}
}


ma_engine engine;
ma_sound sound;
/**
 * @brief audio test command
 */
void shell_audio_cmd(int argc, char *argv)
{
	ma_result result;
	if (argc < 2)
	{
		shell_printf("Usage: audio <init|deinit|play|stop|resume|volume|state>\r\n");
		return;
	}

	if (strcmp(&(argv[(int)argv[1]]), "init") == 0)
	{
		result = ma_engine_init(NULL, &engine);
		if (result != MA_SUCCESS)
		{
			shell_printf("Failed to initialize the engine.\r\n");
			return; // Failed to initialize the engine.
		}
		shell_printf("init\r\n");
	}
	else if (strcmp(&(argv[(int)argv[1]]), "deinit") == 0)
	{
		ma_sound_uninit(&sound);
		ma_engine_uninit(&engine);
		shell_printf("deinit\r\n");
	}
	else if (strcmp(&(argv[(int)argv[1]]), "play") == 0)
	{
		shell_printf("play %s\r\n", &(argv[(int)argv[2]]));

		result = ma_sound_init_from_file(&engine, &(argv[(int)argv[2]]), 0, NULL, NULL, &sound);
		if (result != MA_SUCCESS)
		{
			shell_printf("Failed to initialize the sound.\r\n");
			return;
		}

		ma_sound_start(&sound);
	}
	else if (strcmp(&(argv[(int)argv[1]]), "stop") == 0)
	{
		shell_printf("stop\r\n");
		ma_sound_stop(&sound);
	}
	else if (strcmp(&(argv[(int)argv[1]]), "resume") == 0)
	{
		shell_printf("resume\r\n");
		ma_sound_start(&sound);
	}
	else if (strcmp(&(argv[(int)argv[1]]), "volume") == 0)
	{
		float volume = 0;
		volume = atof(&(argv[(int)argv[2]]));
		shell_printf("volume:%f\r\n", volume);
		ma_sound_set_volume(&sound, volume);
	}
	else if (strcmp(&(argv[(int)argv[1]]), "state") == 0)
	{
		shell_printf("%s\r\n", (ma_sound_at_end(&sound)==MA_FALSE) ? "playing" : "end");
	}
	else
	{
		shell_printf("Usage: audio <init|deinit|play|stop|resume|volume|state>\r\n");
	}
}

void shell_ecctest_cmd(int argc, char *argv)
{
	const struct uECC_Curve_t *curve = uECC_secp160r1();
	uint8_t private1[21];
	uint8_t private2[21];

	uint8_t public1[40];
	uint8_t public2[40];

	uint8_t secret1[20];
	uint8_t secret2[20];

	uECC_make_key(public1, private1, curve);
	uECC_make_key(public2, private2, curve);
	int r = uECC_shared_secret(public2, private1, secret1, curve);
	if (!r)
	{
		dlg_error("shared_secret() failed (1)\n");
		return;
	}
	r = uECC_shared_secret(public1, private2, secret2, curve);
	if (!r)
	{
		dlg_error("shared_secret() failed (1)\n");
		return;
	}

	if (memcmp(secret1, secret2, 20) != 0)
	{
		dlg_error("Shared secrets are not identical!\n");
	}
	else
	{
		dlg_info("Shared secrets are identical\n");
	}
}

void shell_libqrcodetest_cmd(int argc, char *argv)
{
	/*
						##############  ##  ##  ##      ##  ##############
						##          ##  ####      ######    ##          ##
						##  ######  ##  ##  ##  ####  ####  ##  ######  ##
						##  ######  ##        ####  ####    ##  ######  ##
						##  ######  ##    ##      ####  ##  ##  ######  ##
						##          ##  ##    ##    ######  ##          ##
						##############  ##  ##  ##  ##  ##  ##############
										####    ##    ##
							######  ##  ######  ##  ############    ######
						######    ##    ##      ####  ##      ##    ##
						##      ##  ########        ####  ##    ####  ####
						####  ##  ##  ####      ##      ##  ##        ####
							##    ######  ##  ##########  ################
						##  ######      ##    ####    ####    ##    ##
						##          ##    ##  ##          ##########  ####
						##  ######          ##      ##  ##  ######      ##
						##  ##    ######      ####  ##  ##############
										##        ####  ##      ##  ##
						##############            ########  ##  ##  ######
						##          ##        ##      ####      ####  ##
						##  ######  ##  ##  ##      ##################
						##  ######  ##  ####      ####      ##  ####    ##
						##  ######  ##  ####  ##########    ####  ##    ##
						##          ##    ######    ####  ##  ####      ##
						##############        ##    ##  ##    ##    ######
	*/
	QRcode *qrcode = NULL;
	char *data = "hello world";
	int version = 0;
	int width = 0;
	version = QRspec_getMinimumVersion(strlen(data), QR_ECLEVEL_H);
	qrcode = QRcode_encodeString((const char *)data, version, QR_ECLEVEL_H, QR_MODE_8, 1);
	if(qrcode)
	{	
		width = qrcode->width;

		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if(qrcode->data[i*width+j] & 0x01)
				{
					shell_printf("##");
				}
				else
				{
					
					shell_printf("  ");
				}
			}
			shell_printf("\r\n");
			
		}
		

		QRcode_free(qrcode);
	}
}

void shell_tlstest_cmd(int argc, char *argv)
{
	qtf_tls_conn_param_t tls_param = {0};
	void *tls_handle = NULL;
	char recv_buf[1024] = {0};
	int ret = 0;
	const char *test_ca_cert =
		{

			"-----BEGIN CERTIFICATE-----\r\n"
			"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\r\n"
			"A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\r\n"
			"b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\r\n"
			"MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\r\n"
			"YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\r\n"
			"aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\r\n"
			"jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\r\n"
			"xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\r\n"
			"1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\r\n"
			"snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\r\n"
			"U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\r\n"
			"9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\r\n"
			"BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\r\n"
			"AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\r\n"
			"yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\r\n"
			"38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\r\n"
			"AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\r\n"
			"DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\r\n"
			"HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\r\n"
			"-----END CERTIFICATE-----"};
	tls_param.auth_mode = QTF_TLS_AUTH_MODE_CERT;
	tls_param.verify_mode = QTF_TLS_VERIFY_MODE_REQUIRED;
	tls_param.hanshake_timeout_ms = 10000;
	tls_param.ca_cert = test_ca_cert;
	tls_param.ca_cert_len = strlen(test_ca_cert);
	tls_param.client_cert = NULL;
	tls_param.client_cert_len = 0;
	tls_param.client_key = NULL;
	tls_param.client_key_len = 0;
	tls_param.client_key_passwd = NULL;
	tls_param.client_key_passwd_len = 0;
	tls_param.psk = NULL;
	tls_param.psk_len = 0;
	tls_param.psk_id = NULL;

	tls_handle = qtf_tls_connect("a1ox6SbM4ri.iot-as-mqtt.cn-shanghai.aliyuncs.com", 443, &tls_param);
	if(tls_handle)
	{
		shell_printf("tls connect success\r\n");
	}
	else
	{
		shell_printf("tls connect failed\r\n");
		return;
	}

	ret = qtf_tls_send(tls_handle, "hello world", strlen("hello world"), 1000);
	if(ret > 0)
	{
		shell_printf("tls send success\r\n");
	}
	else
	{
		shell_printf("tls send failed\r\n");
		qtf_tls_close(tls_handle);
		return;
	}

	ret = qtf_tls_recv(tls_handle, recv_buf, sizeof(recv_buf), 1000);
	if(ret > 0)
	{
		shell_printf("tls recv success\r\n");
		shell_printf("recv:%s\r\n", recv_buf);
	}
	else
	{
		shell_printf("tls recv failed\r\n");
		qtf_tls_close(tls_handle);
		return;
	}

	qtf_tls_close(tls_handle);

}


#ifdef NR_SHELL_USING_EXPORT_CMD
NR_SHELL_CMD_EXPORT(test, shell_test_cmd);
#else
const static_cmd_st static_cmd[] =
	{
		{"help", shell_help_cmd, NULL},
		{"test", shell_test_cmd, NULL},
		{"lvgl", shell_lvgl_cmd, "lvgl test command"},
		{"audio", shell_audio_cmd, "audio test command"},
		{"cbor", shell_cbor_cmd,"cbor test command"},
		{"hmac", shell_hmac_cmd,"hmac test command"},
		{"qrtest", shell_libqrcodetest_cmd,"qrcode test command"},
		{"ecctest", shell_ecctest_cmd,"ecc test command"},
		{"tlstest", shell_tlstest_cmd,"tls test command"},
		{"\0", NULL, NULL}};
#endif

/******************* (C) COPYRIGHT 2019 Nrush *****END OF FILE*****************/
