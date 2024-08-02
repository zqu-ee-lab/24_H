/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:06:47
 * @FilePath: \keil\Hardware\EXTI.h
 * @Description: 
 * 
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved. 
 */
#ifndef __EXTI_H__
#define __EXTI_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"

volatile extern uint64_t the_std_time;

#define long_press_time (uint32_t)1000
#define Filter_time (uint32_t)150

void EXTI_Init(void);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);

/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	GPIO_Regs* const Port;	/* 按键端口 */
    const uint32_t Pin;		/* 按键引脚 */

    uint8_t no__;

	uint32_t start_time;
    uint32_t end_time;
    uint8_t status;
}KEY_T;

/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE	10
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		/* 键值缓冲区 */
	uint8_t Read;					/* 缓冲区读指针1 */
	uint8_t Write;					/* 缓冲区写指针 */
	uint8_t Read2;					/* 缓冲区读指针2 */
}KEY_FIFO_T;

typedef enum
{
	KEY_NONE = 0,			/* 0 表示按键事件 */

	KEY_0_DOWN,				/* 0键按下 */
	KEY_0_UP,				/* 0键弹起 */
	KEY_0_LONG,				/* 0键长按 */

	KEY_1_DOWN,				/* 1键按下 */
	KEY_1_UP,				/* 1键弹起 */
	KEY_1_LONG,				/* 1键长按 */

	KEY_2_DOWN,				/* 2键按下 */
	KEY_2_UP,				/* 2键弹起 */
	KEY_2_LONG,				/* 2键长按 */

}KEY_ENUM;

#endif

