/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-07-31 18:24:00
 * @FilePath: \keil\Hardware\TIME.c
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include "ti_msp_dl_config.h"
#include "TIME.h"
#include <stdlib.h>
#include "DEV_Grayscale.h"
#include "APP_include.h"

extern volatile struct angle Angle; // the angle of the car

void (*task)(void);

void TIMG0_IRQHandler(void)
{
	switch (DL_TimerG_getPendingInterrupt(TIMG0)) // get the interrupt flag
	{
	case DL_TIMER_IIDX_ZERO: // interrupt flag of timer 0
		if (NULL != task)
		{
			gray_value = read_grayscale();
			task();
		}
		break;
	default:
		break;
	}
}
