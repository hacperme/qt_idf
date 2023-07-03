/**
 * @file 
 * utils_timer.c
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

#include "utils_timer.h"

#include <windows.h>
#include <time.h>

void qtf_timer_init(timer_t *timer)
{
    timer->end_time = 0;
}

void qtf_timer_countdown_ms(timer_t *timer, uint32_t timeout_ms)
{
#if _WIN32_WINNT >= 0x0600
    timer->end_time = GetTickCount64() + timeout_ms;
#else
    timer->end_time = GetTickCount() + timeout_ms;
#endif
}

void qtf_timer_countdown_sec(timer_t *timer, uint32_t timeout_sec)
{
#if _WIN32_WINNT >= 0x0600
    timer->end_time = GetTickCount64() + (uint64_t)timeout_sec * 1000;
#else
    timer->end_time = GetTickCount() + (uint64_t)timeout_sec * 1000;
#endif
}

bool qtf_timer_expired(timer_t *timer)
{
#if _WIN32_WINNT >= 0x0600
    return GetTickCount64() >= timer->end_time;
#else
    return GetTickCount() >= timer->end_time;
#endif
}

uint32_t qtf_timer_left_ms(timer_t *timer)
{
#if _WIN32_WINNT >= 0x0600
    uint64_t now = GetTickCount64();
#else
    uint64_t now = GetTickCount();
#endif
    if (now >= timer->end_time) {
        return 0;
    } else {
        return (uint32_t)(timer->end_time - now);
    }
}

uint64_t qtf_timer_now_sec(void)
{
    return (uint64_t)time(NULL);
}

#ifdef __cplusplus
} /*"C" */
#endif
