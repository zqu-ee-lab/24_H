/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-25 20:06:51
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:03:49
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_CAR.c
 * @Description: the dirver of the car
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "DEV_CAR.h"
// #include "ENCODER.h"
#include <stdint.h>
#include "ti_msp_dl_config.h"
#include <math.h>

#define MY_DEGREE_2_PI (57.29577951308232)

#if BRUSHED_MOTOR & ACKERMANN_STEERING

Wheel_t Wheel_Left, Wheel_Right;

// ! maybe need to change this function
void Car_Inverse(void)
{
	DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_PIN |
													 GPIO_Motor_Direction_Motor_Right_Front_PIN |
													 GPIO_Motor_Direction_Motor_Left_Back_PIN |
													 GPIO_Motor_Direction_Motor_Left_Front_PIN);
}

void DEV_CAR_Init(void)
{
	Encoder_Init();
	Wheel_Left.target_speed = 0;
	Wheel_Right.target_speed = 0;
	PID_Initialize(&Wheel_Left.PID, 0.1, 0.1, 0.1, 0, 1000, -1000);
	PID_Initialize(&Wheel_Right.PID, 0.1, 0.1, 0.1, 0, 1000, -1000);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, 0, GPIO_PWM_Motor_Left_C0_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, 0, GPIO_PWM_Motor_Left_C1_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, 0, GPIO_PWM_Motor_Right_C0_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, 0, GPIO_PWM_Motor_Right_C1_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Servo_INST, PWM_DIR_ORIGINAL_VALUE, PWM_DIR_CC_INDEX);
}

void DEV_CAR_Set_Speed(double speed, double radius)
{
	if (speed < 0)
	{
		Car_Inverse();
		speed = -speed;
	}
	static double Local_Tan = 0;
	Local_Tan = Car_Length / radius;

	uint16_t Speed_Left = speed * (radius + Car_Width / 2) / (radius);
	uint16_t Speed_Right = speed * (radius - Car_Width / 2) / (radius);

	static double Local_Angle = 0;
	Local_Angle = atan(Local_Tan) * MY_DEGREE_2_PI;

	// DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, CCR_Left, GPIO_PWM_Motor_Left_C0_IDX);
	// DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, CCR_Left, GPIO_PWM_Motor_Left_C1_IDX);
	// DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, CCR_Right, GPIO_PWM_Motor_Right_C0_IDX);
	// DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, CCR_Right, GPIO_PWM_Motor_Right_C1_IDX);

	Wheel_Left.target_speed = Speed_Left;
	Wheel_Right.target_speed = Speed_Right;
	// ! maybe need to change this function
	DL_Timer_setCaptureCompareValue(PWM_Servo_INST, (uint32_t)(Local_Angle * K_Servo), PWM_DIR_CC_INDEX);
}

#elif BRUSHED_MOTOR & (!ACKERMANN_STEERING)

#define DIR_BACK 0
#define DIR_FRONT 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

/**
 * @description: pull high the pins of the motor driver to brake the motor
 * @param {void}
 * @return {*}
 */
void DEV_CAR_Init(void)
{
	Car_Set_Direction(1, BRAKE);
	Car_Set_Direction(2, BRAKE);
	Car_Set_Direction(3, BRAKE);
	Car_Set_Direction(4, BRAKE);
}

/**
 * @description: set the direction of the car
 * @param {int} No_ the number of the motor
 * @param {int} dir the direction of the motor
 * @return {*}
 */
void Car_Set_Direction(int No_, int dir)
{
	switch (No_)
	{
	case 1:
		if (FORWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_PIN);
		}
		else if (BACKWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
		}
		else if (BRAKE == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_PIN);
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
		}
		else if (STOP == dir)
		{
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
		}
		break;
	case 2:
		if (FORWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_1_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_PIN);
		}
		else if (BACKWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_1_PIN);
		}
		else if (BRAKE == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_PIN);
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_1_PIN);
		}
		else if (STOP == dir)
		{
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Left_Back_1_PIN);
		}
		break;
	case 3:
		if (FORWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_1_PIN);
		}
		else if (BACKWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_1_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_PIN);
		}
		else if (BRAKE == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_PIN);
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_1_PIN);
		}
		else if (STOP == dir)
		{
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Front_1_PIN);
		}
		break;
	case 4:
		if (FORWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_1_PIN);
		}
		else if (BACKWARD == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_1_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_PIN);
		}
		else if (BRAKE == dir)
		{
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_PIN);
			DL_GPIO_setPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_1_PIN);
		}
		else if (STOP == dir)
		{
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_PIN);
			DL_GPIO_clearPins(GPIO_Motor_Direction_PORT, GPIO_Motor_Direction_Motor_Right_Back_1_PIN);
		}
		break;
	default:
		break;
	}
}

/**
 * @description: set the speed of the car
 * @param {int32_t} CCR__ the speed array of the four motors
 * @return {*}
 */
void DEV_CAR_Set_Speed(int32_t CCR__[])
{
	static int32_t CCR_[4];
	CCR_[0] = CCR__[0];
	CCR_[1] = CCR__[1];
	CCR_[2] = CCR__[2];
	CCR_[3] = CCR__[3];

	if (CCR_[0] < 0)
	{
		Car_Set_Direction(1, BACKWARD);
		CCR_[0] = -CCR_[0];
	}
	else if (0 == CCR_[0])
	{
		Car_Set_Direction(1, BRAKE);
	}
	else
	{
		Car_Set_Direction(1, FORWARD);
	}

	if (CCR_[1] < 0)
	{
		Car_Set_Direction(2, BACKWARD);
		CCR_[1] = -CCR_[1];
	}
	else if (0 == CCR_[1])
	{
		Car_Set_Direction(2, BRAKE);
	}
	else
	{
		Car_Set_Direction(2, FORWARD);
	}

	if (CCR_[2] < 0)
	{
		Car_Set_Direction(3, BACKWARD);
		CCR_[2] = -CCR_[2];
	}
	else if (0 == CCR_[2])
	{
		Car_Set_Direction(3, BRAKE);
	}
	else
	{
		Car_Set_Direction(3, FORWARD);
	}

	if (CCR_[3] < 0)
	{
		Car_Set_Direction(4, BACKWARD);
		CCR_[3] = -CCR_[3];
	}
	else if (CCR_[3] == 0)
	{
		Car_Set_Direction(4, BRAKE);
	}
	else
	{
		Car_Set_Direction(4, FORWARD);
	}

	CCR_[0] = 2000 - CCR_[0];
	CCR_[1] = 2000 - CCR_[1];
	CCR_[2] = 2000 - CCR_[2];
	CCR_[3] = 2000 - CCR_[3];

	DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, CCR_[0], GPIO_PWM_Motor_Left_C1_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Left_INST, CCR_[1], GPIO_PWM_Motor_Left_C2_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, CCR_[2], GPIO_PWM_Motor_Right_C1_IDX);
	DL_Timer_setCaptureCompareValue(PWM_Motor_Right_INST, CCR_[3], GPIO_PWM_Motor_Right_C0_IDX);
}

#elif BRUSHLESS_MOTOR & (!ACKERMANN_STEERING)

#include "Stepper.h"

struct Steeper_t *Stepper_Left_Front = NULL;
struct Steeper_t *Stepper_Left_Back = NULL;
struct Steeper_t *Stepper_Right_Front = NULL;
struct Steeper_t *Stepper_Right_Back = NULL;

void DEV_CAR_Init(void)
{
	// ! need to be implemented
	Stepper_Left_Front = Stepper_Init(STEPPER_USE_UART, 0x01, NULL, Stepper_Check_Way_0X6B, Stepper_FOC_Version_5_0);
	Stepper_Left_Back = Stepper_Init(STEPPER_USE_UART, 0x02, NULL, Stepper_Check_Way_0X6B, Stepper_FOC_Version_5_0);
	Stepper_Right_Front = Stepper_Init(STEPPER_USE_UART, 0x03, NULL, Stepper_Check_Way_0X6B, Stepper_FOC_Version_5_0);
	Stepper_Right_Back = Stepper_Init(STEPPER_USE_UART, 0x04, NULL, Stepper_Check_Way_0X6B, Stepper_FOC_Version_5_0);
}

void DEV_CAR_Set_Speed(double Speed, double radius)
{
	Speed = K_speed * Speed;
	if (0.1 > fabs(radius))
	{
		if (radius > 0)
		{
			Stepper_Left_Front->Speed_Control(Stepper_Left_Front, Stepper_Forward, Speed, true);
			Stepper_Left_Back->Speed_Control(Stepper_Left_Back, Stepper_Forward, Speed, true);
			Stepper_Right_Front->Speed_Control(Stepper_Right_Front, Stepper_Backward, Speed, true);
			Stepper_Right_Back->Speed_Control(Stepper_Right_Back, Stepper_Backward, Speed, true);
		}
		else
		{
			Stepper_Left_Front->Speed_Control(Stepper_Left_Front, Stepper_Backward, Speed, true);
			Stepper_Left_Back->Speed_Control(Stepper_Left_Back, Stepper_Backward, Speed, true);
			Stepper_Right_Front->Speed_Control(Stepper_Right_Front, Stepper_Forward, Speed, true);
			Stepper_Right_Back->Speed_Control(Stepper_Right_Back, Stepper_Forward, Speed, true);
		}
	}
	else
	{
		// ! need to be implemented
		static uint32_t Speed_Left_Front = 0, Speed_Right_Front = 0, Speed_Left_Back = 0, Speed_Right_Back = 0;

		Speed_Left_Front = Speed * (Pythagorean(radius + (Car_Width / 2), (Car_Length / 2))) / (radius);
		Speed_Right_Front = Speed * (Pythagorean(radius - (Car_Width / 2), (Car_Length / 2))) / (radius);
		Speed_Left_Back = Speed_Left_Front;
		Speed_Right_Back = Speed_Right_Front;

		Stepper_Left_Front->Speed_Control(Stepper_Left_Front, Speed_Left_Front > 0 ? Stepper_Forward : Stepper_Backward, Speed_Left_Front, true);
		Stepper_Left_Back->Speed_Control(Stepper_Left_Back, Speed_Left_Back > 0 ? Stepper_Forward : Stepper_Backward, Speed_Left_Back, true);
		Stepper_Right_Front->Speed_Control(Stepper_Right_Front, Speed_Right_Front > 0 ? Stepper_Forward : Stepper_Backward, Speed_Right_Front, true);
		Stepper_Right_Back->Speed_Control(Stepper_Right_Back, Speed_Right_Back > 0 ? Stepper_Forward : Stepper_Backward, Speed_Right_Back, true);
	}
}

#endif
