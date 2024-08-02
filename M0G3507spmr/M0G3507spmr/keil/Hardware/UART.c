/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-11 16:46:28
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:29:01
 * @FilePath: \keil\Hardware\UART.c
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "UART.h"
#include "ti_msp_dl_config.h"
#include "buffer.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

struct Buff U3_buffer, U2_buffer, U0_buffer, U1_buffer;

uint8_t Data_UART_0, Data_UART_1, Data_UART_2, Data_UART_3;

void UART_NVIC_Init(void)
{
	// Iinitial_BUFF(&U0_buffer, BUFFER_SIZE_U0);
	// Iinitial_BUFF(&U1_buffer, BUFFER_SIZE_U1);
	Iinitial_BUFF(&U2_buffer, BUFFER_SIZE_U2);
	// Iinitial_BUFF(&U3_buffer, BUFFER_SIZE_U3);

	// NVIC_EnableIRQ(UART0_INT_IRQn);		  // interrupt enable
	// NVIC_EnableIRQ(UART1_INT_IRQn);		  // interrupt enable
	NVIC_EnableIRQ(UART2_INT_IRQn);		  // interrupt enable
	// NVIC_EnableIRQ(UART3_INT_IRQn);		  // interrupt enable
	// NVIC_ClearPendingIRQ(UART0_INT_IRQn); // clear the interrupt flag
	// NVIC_ClearPendingIRQ(UART1_INT_IRQn); // clear the interrupt flag
	NVIC_ClearPendingIRQ(UART2_INT_IRQn); // clear the interrupt flag
	// NVIC_ClearPendingIRQ(UART3_INT_IRQn); // clear the interrupt flag
}

/*
*********************************************************************************************************
*	函 数 名: App_Printf
*	功能说明: 线程安全的printf方式
*	形    参: 同printf的参数。
*             在C中，当无法列出传递函数的所有实参的类型和数目时,可以用省略号指定参数表
*	返 回 值: 放回打印的字符数，如果返回-1，说明有其他线程正在使用printf
*********************************************************************************************************
*/
int App_Printf(char *format, ...)
{
	static uint8_t App_Printf_Flag = 0;
	static int len = 0;
	if(App_Printf_Flag == 1)
	{
		return -1;
	}
	App_Printf_Flag = 1;
	char buf_str[200 + 1];
	va_list v_args;

	va_start(v_args, format);
	(void)vsnprintf((char *)&buf_str[0],
					(size_t)sizeof(buf_str),
					(char const *)format,
					v_args);
	va_end(v_args);

	len = strlen(buf_str);
	Usart_SendArray(PRINTF_USE_UART, (const uint8_t *)buf_str, len);
	App_Printf_Flag = 0;
	return len;
}

void UART2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(UART2_INT_IRQn);
	switch (DL_UART_Main_getPendingInterrupt(UART2))
	{
	case DL_UART_MAIN_IIDX_RX:
		Data_UART_2 = DL_UART_Main_receiveData(UART2);
		Write_BUFF(&Data_UART_2, &U2_buffer);
		break;
	default:
		break;
	}
}

/*****************  发送一个字节 **********************/
void Usart_SendByte(UART_Regs *pUSARTx, uint8_t ch)
{
	/* 鍙戦€佷竴涓瓧鑺傛暟鎹埌USART */
	DL_UART_transmitDataBlocking(pUSARTx, ch);
	;
}
/****************** 发送一个数组 ************************/
void Usart_SendArray(UART_Regs *pUSARTx, const uint8_t *array, uint16_t num)
{
	uint8_t i;

	for (i = 0; i < num; i++)
	{
		/* 按字节一个一个发送 */
		Usart_SendByte(pUSARTx, array[i]);
	}
}
