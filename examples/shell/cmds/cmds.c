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

#ifdef NR_SHELL_USING_EXPORT_CMD
NR_SHELL_CMD_EXPORT(test, shell_test_cmd);
#else
const static_cmd_st static_cmd[] =
	{
		{"help", shell_help_cmd, NULL},
		{"test", shell_test_cmd, NULL},
		{"lvgl", shell_lvgl_cmd, "lvgl test command"},
		{"audio", shell_audio_cmd, "audio test command"},
		{"cbor",shell_cbor_cmd,"cbor test command"},
		{"hmac",shell_hmac_cmd,"hmac test command"},
		{"qrtest",shell_libqrcodetest_cmd,"qrcode test command"},
		{"\0", NULL, NULL}};
#endif

/******************* (C) COPYRIGHT 2019 Nrush *****END OF FILE*****************/
