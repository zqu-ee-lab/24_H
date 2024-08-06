/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-12 20:37:32
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-04 19:33:35
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\24_H\M0G3507spmr\M0G3507spmr\APP\main.c
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */

/*
 * ......................................&&.........................
 * ....................................&&&..........................
 * .................................&&&&............................
 * ...............................&&&&..............................
 * .............................&&&&&&..............................
 * ...........................&&&&&&....&&&..&&&&&&&&&&&&&&&........
 * ..................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&..............
 * ................&...&&&&&&&&&&&&&&&&&&&&&&&&&&&&.................
 * .......................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&.........
 * ...................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&...............
 * ..................&&&   &&&&&&&&&&&&&&&&&&&&&&&&&&&&&............
 * ...............&&&&&@  &&&&&&&&&&..&&&&&&&&&&&&&&&&&&&...........
 * ..............&&&&&&&&&&&&&&&.&&....&&&&&&&&&&&&&..&&&&&.........
 * ..........&&&&&&&&&&&&&&&&&&...&.....&&&&&&&&&&&&&...&&&&........
 * ........&&&&&&&&&&&&&&&&&&&.........&&&&&&&&&&&&&&&....&&&.......
 * .......&&&&&&&&.....................&&&&&&&&&&&&&&&&.....&&......
 * ........&&&&&.....................&&&&&&&&&&&&&&&&&&.............
 * ..........&...................&&&&&&&&&&&&&&&&&&&&&&&............
 * ................&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&............
 * ..................&&&&&&&&&&&&&&&&&&&&&&&&&&&&..&&&&&............
 * ..............&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&....&&&&&............
 * ...........&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&......&&&&............
 * .........&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&.........&&&&............
 * .......&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&...........&&&&............
 * ......&&&&&&&&&&&&&&&&&&&...&&&&&&...............&&&.............
 * .....&&&&&&&&&&&&&&&&............................&&..............
 * ....&&&&&&&&&&&&&&&.................&&...........................
 * ...&&&&&&&&&&&&&&&.....................&&&&......................
 * ...&&&&&&&&&&.&&&........................&&&&&...................
 * ..&&&&&&&&&&&..&&..........................&&&&&&&...............
 * ..&&&&&&&&&&&&...&............&&&.....&&&&...&&&&&&&.............
 * ..&&&&&&&&&&&&&.................&&&.....&&&&&&&&&&&&&&...........
 * ..&&&&&&&&&&&&&&&&..............&&&&&&&&&&&&&&&&&&&&&&&&.........
 * ..&&.&&&&&&&&&&&&&&&&&.........&&&&&&&&&&&&&&&&&&&&&&&&&&&.......
 * ...&&..&&&&&&&&&&&&.........&&&&&&&&&&&&&&&&...&&&&&&&&&&&&......
 * ....&..&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&...........&&&&&&&&.....
 * .......&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&..............&&&&&&&....
 * .......&&&&&.&&&&&&&&&&&&&&&&&&..&&&&&&&&...&..........&&&&&&....
 * ........&&&.....&&&&&&&&&&&&&.....&&&&&&&&&&...........&..&&&&...
 * .......&&&........&&&.&&&&&&&&&.....&&&&&.................&&&&...
 * .......&&&...............&&&&&&&.......&&&&&&&&............&&&...
 * ........&&...................&&&&&&.........................&&&..
 * .........&.....................&&&&........................&&....
 * ...............................&&&.......................&&......
 * ................................&&......................&&.......
 * .................................&&..............................
 * ..................................&..............................
 *
 * @Author: jar-chou 2722642511@qq.com
 * @Date: 2023-09-06 13:02:19
 * @LastEditors: jar-chou 2722642511@qq.com
 * @LastEditTime: 2023-09-07 13:50:25
 * @FilePath: c:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\APP\main.c
 * @Description: 龙王保佑此文件无bug！！！
 */
#include "ti_msp_dl_config.h"
#include "EXTI.h"
#include "UART.h"
#include "LED.h"
#include "delay.h"
#include "OLED.h"
#include "Servo.h"
#include "ADC.h"
#include "DEV_I2C.h"
#include "oled_draw.h"
#include "oled_buffer.h"
#include <stdio.h>
#include "DEV_Grayscale.h"
#include "buffer.h"
#include "UI_.h"
#include "DEV_CAR.h"

volatile struct angle Angle; // the angle of the car
// void follow_line(int);
int main(void)
{
	// initialize the bsp
	SYSCFG_DL_init();
	// initialize interruption
	UART_NVIC_Init();
	NVIC_ClearPendingIRQ(TIMG0_INT_IRQn); // clear the timer interrupt flag
	NVIC_EnableIRQ(TIMG0_INT_IRQn);		  // open the timer interrupt
	EXTI_Init();
	// initialize the driver of motors
	DEV_CAR_Init();

	// initialize the OLED driver lib
	OLED_Init();
	delay_ms(1000);
	OLED_CLS();

	/// initialize the parameter of PID controllers
	init_task();

	// initialize UI pages and their callback functions
	test1();
	UI_updata();
	UpdateScreenDisplay();

	// oled update indexs
	int i = 0;
	// define img buffer
	char str[70] = {0};
	// LED_ON();
	while (1)
	{
		const char TOFSENSE[] = {0x55, 0x53};
		const char TOFSENSE1[] = {0x55, 0x52};
		uint8_t check_sum = 0;
		if (BUFF_pop_by_Protocol(&U2_buffer, TOFSENSE1, 2, (void *)Angle.data, 20) == 20)
		{
			check_sum = (0x55 + 0x52 + Angle.data[5] + Angle.data[4] + Angle.data[3] + Angle.data[2]);
			if (Angle.data[8] == check_sum)
			{
				Angle.w = -((Angle.data[5] << 8) + Angle.data[4]);
				Angle.value_w = (double)Angle.w / 32768 * 2000;
				// sprintf(str, "angle_w:%4.2f   ", (Angle.value_w));
				// DrawString(5, 0, str);
			}
			char *p = (char *)Angle.data + 9;
			if (0x55 == p[0] && (0x53 == p[1]))
			{
				p += 2;
				check_sum = (0x55 + 0x53 + p[5] + p[4] + p[7] + p[6]);
				if (p[8] == check_sum)
				{
					Angle.z = -((p[5] << 8) + p[4]);
					Angle.value = (double)Angle.z / 32768 * 180;
					// sprintf(str, "angle:%4.2f   ", (Angle.value));
					// DrawString(6, 0, str);
				}
			}
		}

		// gray_value = read_grayscale();
		// sprintf(str, "gray:%2d", (gray_value));
		// DrawString(4, 0, str);

		// update the screen display
		if ((++i) == 10)
		{
			i = 0;
			UpdateScreenDisplay();
		}

		// update the UI pages
		uint8_t key = bsp_GetKey();
		switch (key)
		{
		case KEY_0_DOWN:
			UI_enter();
			break;
		case KEY_0_LONG:
			UI_back();
			break;
		case KEY_1_DOWN:
			UI_next();
			break;
		case KEY_2_DOWN:
			UI_prev();
			break;
		default:
			break;
		}

		// turn off the led after 1s
		if (!(led_state && (--led_state)))
		{
			LED_OFF();
		}

		// DrawNum(7, 0, not_on_drak_line_flag, 1);
		// DrawNum(7, 8, on_drak_line_flag, 1);

		delay_ms(20);
	}
}
