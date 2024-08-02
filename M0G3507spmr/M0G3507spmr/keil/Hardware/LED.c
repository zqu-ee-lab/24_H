/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-07-31 15:52:11
 * @FilePath: \keil\Hardware\LED.c
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "LED.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

uint8_t led_state = 0;

void LED_ON()
{
	DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_Pin_LED_PIN);
	led_state = 50;
	DL_GPIO_setPins(GPIO_buzzer_PORT, GPIO_buzzer_PIN_BUZZER_PIN);
}

void LED_OFF()
{
	DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_Pin_LED_PIN);
	DL_GPIO_clearPins(GPIO_buzzer_PORT, GPIO_buzzer_PIN_BUZZER_PIN);
}
