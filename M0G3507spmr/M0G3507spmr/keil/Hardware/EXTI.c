/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 10:57:25
 * @FilePath: \keil\Hardware\EXTI.c
 * @Description: 
 * 
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved. 
 */
#include "EXTI.h"
#include <ti/driverlib/m0p/dl_interrupt.h>
#include "ti_msp_dl_config.h"

KEY_FIFO_T s_tKey = {0}; /* 按键FIFO结构体变量 */

KEY_T Key_0 = {GPIOB, GPIO_Key_Key_0_PIN, 0, 0, 0, 1};
KEY_T Key_1 = {GPIOB, GPIO_Key_Key_1_PIN, 1, 0, 0, 1};
KEY_T Key_2 = {GPIOB, GPIO_Key_Key_2_PIN, 2, 0, 0, 1};

KEY_T *const s_tBtn[3] = {&Key_0, &Key_1, &Key_2};

void EXTI_Init(void)
{
	NVIC_EnableIRQ(GPIOA_INT_IRQn);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_PutKey
*	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
*	形    参:  _KeyCode : 按键代码
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_GetKey
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参:  无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
uint8_t bsp_GetKey(void)
{
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_GetKey2
*	功能说明: 从按键FIFO缓冲区读取一个键值。独立的读指针。
*	形    参:  无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
uint8_t bsp_GetKey2(void)
{
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE)
		{
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_GetKeyState
*	功能说明: 读取按键的状态
*	形    参:  _ucKeyID : 按键ID，从0开始
*	返 回 值: 1 表示按下， 0 表示未按下
*********************************************************************************************************
*/
uint8_t bsp_GetKeyState(uint8_t _ucKeyID)
{
	return s_tBtn[_ucKeyID]->status;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_ClearKey
*	功能说明: 清空按键FIFO缓冲区
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	s_tKey.Read = s_tKey.Write;
}

void GROUP1_IRQHandler(void)
{
	/*
	 * Get the pending interrupt for the GPIOB port and store for
	 * comparisons later
	 */
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,
													   GPIO_Key_Key_0_PIN | GPIO_Key_Key_1_PIN | GPIO_Key_Key_2_PIN);

	/*
	 * Bitwise AND the pending interrupt with the pin you want to check,
	 * then check if it is equal to the pins. Clear the interrupt status.
	 */
	if ((gpioB & GPIO_Key_Key_0_PIN) == GPIO_Key_Key_0_PIN)
	{
		if (DL_GPIO_readPins(GPIOB, GPIO_Key_Key_0_PIN))
		{
			Key_0.status = 1;
			Key_0.end_time = the_std_time;
			if (Key_0.end_time - Key_0.start_time > long_press_time)
			{
				Key_0.status = 2;
				bsp_PutKey(KEY_0_LONG);
			}
			else if (Key_0.end_time - Key_0.start_time > Filter_time)
			{
				bsp_PutKey(KEY_0_DOWN);
			}
		}
		else
		{
			Key_0.status = 0;
			Key_0.start_time = the_std_time;
		}
		DL_GPIO_clearInterruptStatus(GPIOB, GPIO_Key_Key_0_PIN);
	}
	if ((gpioB & GPIO_Key_Key_1_PIN) == GPIO_Key_Key_1_PIN)
	{
		if (DL_GPIO_readPins(GPIOB, GPIO_Key_Key_1_PIN))
		{
			Key_1.status = 1;
			Key_1.end_time = the_std_time;
			if (Key_1.end_time - Key_1.start_time > long_press_time)
			{
				Key_1.status = 2;
				bsp_PutKey(KEY_1_LONG);
			}
			else if (Key_1.end_time - Key_1.start_time > Filter_time)
			{
				bsp_PutKey(KEY_1_DOWN);
			}
		}
		else
		{
			Key_1.status = 0;
			Key_1.start_time = the_std_time;
		}
		DL_GPIO_clearInterruptStatus(GPIOB, GPIO_Key_Key_1_PIN);
	}
	if ((gpioB & GPIO_Key_Key_2_PIN) == GPIO_Key_Key_2_PIN)
	{
		if (DL_GPIO_readPins(GPIOB, GPIO_Key_Key_2_PIN))
		{
			Key_2.status = 1;
			Key_2.end_time = the_std_time;
			if (Key_2.end_time - Key_2.start_time > long_press_time)
			{
				Key_2.status = 2;
				bsp_PutKey(KEY_2_LONG);
			}
			else if (Key_2.end_time - Key_2.start_time > Filter_time)
			{
				bsp_PutKey(KEY_2_DOWN);
			}
		}
		else
		{
			Key_2.status = 0;
			Key_2.start_time = the_std_time;
		}
		DL_GPIO_clearInterruptStatus(GPIOB, GPIO_Key_Key_2_PIN);
	}
}