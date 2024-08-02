/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-12 19:42:50
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-01 09:12:22
 * @FilePath: \keil\Hardware\delay.c
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include "delay.h"
#include "ti_msp_dl_config.h"

volatile int delay_times = 0;
volatile uint64_t the_std_time = 0;

volatile const uint64_t *p_the_std_time = &the_std_time;
const uint32_t systick_period = CPUCLK_FREQ / 1000U;

void delay_ms(unsigned int ms)
{
	delay_times = ms;
	while (delay_times > 0)
		;
}

void SysTick_Handler(void)
{
	the_std_time++;
	if (delay_times != 0)
	{
		delay_times--;
	}
}
