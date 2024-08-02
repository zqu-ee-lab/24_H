/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:09:27
 * @FilePath: \keil\Hardware\OLED.c
 * @Description: the OLED driver
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */

#include <ti/driverlib/dl_i2c.h>
#include "OLED.h"
#include "delay.h"
#include "OLED_Font.h"
#include "DEV_I2C.h"
#include "string.h"

#define OLED_ADDR 0x3C

void OLED_I2C_Init(void)
{
	I2C__init__(&gI2C0_Device);
}

// 向OLED寄存器地址写一个byte的数据
int I2C_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t buff[2] = {0};
	buff[0] = addr;
	buff[1] = data;

	I2C_WriteArray_With_Blocking(&gI2C0_Device, buff, 2);
	return 0;
}

// 写指令
void WriteCmd(unsigned char I2C_Command)
{
	I2C_WriteByte(0x00, I2C_Command);
}

// 写数据
void WriteData(unsigned char I2C_Data)
{
	I2C_WriteByte(0x40, I2C_Data);
}

/**
 * @brief  OLED写多个数据
 * @param  dat 要写入的数据数组
 * @param  len 要写入的数据长度
 * @retval 无
 */
static inline void OLED_WriteMultiData(uint8_t *dat, uint8_t len)
{
	uint8_t date[1] = {0x40};
	date[0] = 0x40;
	I2C_WriteArray2Register_With_Blocking(&gI2C0_Device, date, 1, dat, len);
}

// 厂家初始化代码
void OLED_Init(void)
{
	OLED_I2C_Init();
	delay_ms(100);
	WriteCmd(0xAE); // display off
	WriteCmd(0x20); // Set Memory Addressing Mode
	WriteCmd(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8); // Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); // áá?èμ÷?ú 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); // 0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

/**
 * @brief  OLED设置光标位置
 * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
 * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
 * @retval 无
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	X += 2;
	WriteCmd(0xB0 | Y);					// 设置Y位置
	WriteCmd(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
	WriteCmd(0x00 | (X & 0x0F));		// 设置X位置低4位
}

/**
 * @brief  OLED显示缓冲区的图片
 * @param  BMP 要显示的图片数组
 * @retval 无
 */
void OLED_FILL(uint8_t BMP[8][128])
{
	uint8_t i = 0;

	for (i = 0; i < 8; i++)
	{
		OLED_SetCursor(i, 0);
		OLED_WriteMultiData(BMP[i], 128);
	}
}

// 清屏
void OLED_CLS(void)
{
	uint8_t space[128] = {0};
	uint8_t j;
	for (j = 0; j < 8; j++)
	{
		WriteCmd(0xb0 + j);
		WriteCmd(0x00);
		WriteCmd(0x10);
		OLED_WriteMultiData(space, 128);
	}
}

// 将OLED从休眠中唤醒
void OLED_ON(void)
{
	WriteCmd(0xAF);
	WriteCmd(0x8D);
	WriteCmd(0x14);
}

// 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
void OLED_OFF(void)
{
	WriteCmd(0xAE);
	WriteCmd(0x8D);
	WriteCmd(0x10);
}

/**
 * @brief  OLED显示一个字符
 * @param  Line 行位置，范围：1~4
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的一个字符，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8); // 设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		WriteData(OLED_F8x16[Char - ' '][i]); // 显示上半部分内容
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8); // 设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		WriteData(OLED_F8x16[Char - ' '][i + 8]); // 显示下半部分内容
	}
}

/**
 * @brief  OLED显示字符串
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  String 要显示的字符串，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}
