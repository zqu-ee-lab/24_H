/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-07-31 15:52:11
 * @FilePath: \keil\Hardware\OLED.h
 * @Description: the OLED driver header file
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#ifndef __OLED_H__
#define __OLED_H__

#include "ti_msp_dl_config.h"
#include <stdint.h>

void OLED_I2C_Init(void);

int I2C_WriteByte(uint8_t addr, uint8_t data);

void WriteCmd(unsigned char I2C_Command);

void WriteData(unsigned char I2C_Data);

void OLED_Init(void);

void OLED_FILL(uint8_t BMP[8][128]);

void OLED_CLS(void);

void OLED_ON(void);

void OLED_OFF(void);

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

#endif
