/**
 * @file 
 * utils_timer.h
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

#ifndef __UTILS_TIMER_H__
#define __UTILS_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct timer_s {
    uint64_t end_time;
}timer_t;

void qtf_timer_init(timer_t *timer);

void qtf_timer_countdown_ms(timer_t *timer, uint32_t timeout_ms);

void qtf_timer_countdown_sec(timer_t *timer, uint32_t timeout_sec);

bool qtf_timer_expired(timer_t *timer);

uint32_t qtf_timer_left_ms(timer_t *timer);

uint64_t qtf_timer_now_sec(void);

#ifdef __cplusplus
} /*"C" */
#endif

#endif /* __UTILS_TIMER_H__ */