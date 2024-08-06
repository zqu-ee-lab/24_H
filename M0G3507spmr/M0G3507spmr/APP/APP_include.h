/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:36:20
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-03 22:55:31
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\24_H\M0G3507spmr\M0G3507spmr\APP\APP_include.h
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _APP_INCLUDE_____
#define _APP_INCLUDE_____

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "buffer.h"
#include "delay.h"
#include "TIME.h"

extern volatile int gray_value;
extern volatile uint8_t state;
extern volatile struct angle Angle; // the angle of the car
extern void (*task)(void);
extern uint8_t Waiting_Out_Black_Line_Time;

void init_task(void);

extern double Aim_Angle;

// atan(80/100) 
#define SPECIAL_ANGLE (38.659808254090095 - .91)

#define WAITING_TIME 40
#define WAITING_TIME_FAST 40

#define WAITING_TIME_TURN 120

struct angle
{
	uint8_t data[20];
	int16_t z;
	double value;
	int16_t w;
	double value_w;
};

#endif
