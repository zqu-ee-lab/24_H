/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-07-30 15:58:55
 * @FilePath: \keil\Hardware\LED.h
 * @Description: 
 * 
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved. 
 */
#ifndef _LED_H
#define _LED_H

#include <stdint.h>

void LED_ON();
void LED_OFF();

extern uint8_t led_state;

#endif

