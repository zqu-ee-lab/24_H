/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-25 20:06:38
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:06:14
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_CAR.h
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#ifndef __DEV_CAR_H
#define __DEV_CAR_H

#include "ti_msp_dl_config.h"
#include "PID.h"
#include <math.h>

#define BRUSHED_MOTOR 1
#define BRUSHLESS_MOTOR 0
#define ACKERMANN_STEERING 0

// unit: mm
#define Car_Length (180.)
#define Car_Width (120.)



#if ACKERMANN_STEERING

extern Wheel_t Wheel_Left, Wheel_Right;

#define PWM_DIR_ORIGINAL_VALUE 1500

#define PWM_DIR_CC_INDEX GPIO_PWM_Servo_C3_IDX

// 线性近似，舵机占空比和小车转向角度的关系
#define K_Servo (11.111111)

#endif // ! ACKERMANN_STEERING

#if (!ACKERMANN_STEERING)

#define Pythagorean(a, b) sqrt((a) * (a) + (b) * (b))

#endif // ! (!ACKERMANN_STEERING)

#if (BRUSHED_MOTOR & (!ACKERMANN_STEERING))


#endif // ! (BRUSHED_MOTOR & (!ACKERMANN_STEERING))

#if BRUSHLESS_MOTOR

#define STEPPER_USE_UART UART3_INST // ! need to be implemented

#define K_speed 1000

#endif // ! BRUSHLESS_MOTOR

void DEV_CAR_Init(void);
void DEV_CAR_Set_Speed(int32_t CCR_[]);
#define FORWARD 1
#define BACKWARD 0
#define BRAKE 2
#define STOP 3
void Car_Set_Direction(int No_, int dir);
#endif // !__DEV_CAR_H