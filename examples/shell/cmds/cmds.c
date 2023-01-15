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
#include <ctype.h>

extern void shell_lvgl_cmd(int argc, char *argv);

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

#ifdef NR_SHELL_USING_EXPORT_CMD
NR_SHELL_CMD_EXPORT(test, shell_test_cmd);
#else
const static_cmd_st static_cmd[] =
	{
		{"help", shell_help_cmd, NULL},
		{"test", shell_test_cmd, NULL},
		{"lvgl", shell_lvgl_cmd, "lvgl test command"},
		{"\0", NULL, NULL}};
#endif

/******************* (C) COPYRIGHT 2019 Nrush *****END OF FILE*****************/
