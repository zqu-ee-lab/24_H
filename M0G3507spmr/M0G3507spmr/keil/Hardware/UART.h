/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-11 16:46:28
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:28:04
 * @FilePath: \keil\Hardware\UART.h
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include <stdarg.h>

void UART_NVIC_Init(void);

void Usart_SendArray(UART_Regs *pUSARTx, const uint8_t *array, uint16_t num);

#define PRINTF_USE_UART UART0

int App_Printf(char *format, ...);

#define PRINTF(format, ...) App_Printf(format, ##__VA_ARGS__)

#endif
