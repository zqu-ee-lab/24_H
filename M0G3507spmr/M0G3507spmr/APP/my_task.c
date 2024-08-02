/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 09:11:43
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:57:13
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\APP\my_task.c
 * @Description: the task of the car, all the task is programmed by state machine. if you have any question, it is welcome to contact me by email.
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "my_task.h"
#include "APP_include.h"
#include "LED.h"
#include "PID.h"
#include "DEV_Grayscale.h"
#include "DEV_CAR.h"
#include <stdint.h>

#define ANGULAR_VELOCITY_VERSION

static int32_t CCR[4] = {0};

int8_t task1_index = 0;
int8_t task2_index = 0;
int8_t task3_index = 0;
int8_t task4_index = 0;
int8_t task5_index = 0;

struct PID pid_follow_line;
struct PID pid_follow_line_fast;
struct PID pid_follow_angle;
struct PID pid_turn_angle;

double Aim_Angle = 0;

int Follow_Angle_Count = 0;
const int Max_Follow_Angle_Count = 95;
const int ACCELERATION_TIME = 15;
int Follow_Line_Count = 0;
const int Max_Follow_Line_Count = 150;

#define follow_line_FAST(Dir) follow_line(Dir)

void follow_angle_FAST(void)
{
#ifdef ANGULAR_VELOCITY_VERSION
	const double K_P = 39.0, K_D = 3.45;
	const int Max_Speed = 1600;
	const int Min_Speed = 850;
	static int Speed = 0;
	Follow_Angle_Count++;
	if (Follow_Angle_Count > Max_Follow_Angle_Count)
	{
		Follow_Angle_Count = Max_Follow_Angle_Count;
	}
	if (Follow_Angle_Count < ACCELERATION_TIME)
	{
		Speed = (int)(Max_Speed - Min_Speed) * ((double)Follow_Angle_Count / ACCELERATION_TIME) + Min_Speed;
	}
	else
	{
		Speed = (int)(Max_Speed - Min_Speed) * ((double)(Max_Follow_Angle_Count - Follow_Angle_Count) / Max_Follow_Angle_Count) + Min_Speed;
	}
	double diff = Aim_Angle - Angle.value;
	if (diff > 180)
	{
		diff = diff - 360;
	}
	else if (diff < -180)
	{
		diff = diff + 360;
	}
	int output = K_P * (diff)-K_D * (Angle.value_w);
#else
	int output = PID_Realize_angle(&pid_follow_angle, (Aim_Angle - Angle.value));
#endif
	CCR[0] = Speed + output;
	CCR[1] = Speed + output;
	CCR[2] = Speed - output;
	CCR[3] = Speed - output;

	DEV_CAR_Set_Speed(CCR);
}

#define turn_angle_FAST() turn_angle()

void init_task(void)
{
	PID_Initialize(&pid_follow_line_fast, 42., 0.4, .1, 0, 100, -100);
	PID_Initialize(&pid_follow_line, 33., 0.3, .1, 0, 100, -100);
	PID_Initialize(&pid_follow_angle, 20, 0.0, 0.0, 0, 100, -100);
	PID_Initialize(&pid_turn_angle, 0.1, 0.1, 0.1, 0, 100, -100);
}

#define FOLLOW_LINE_DIR_LEFT 1
#define FOLLOW_LINE_DIR_RIGHT 0
void follow_line(int Dir)
{
	int output = (int)PID_Realize(&pid_follow_line, gray_value);
	if (Dir) // 左边转弯巡线
	{
		CCR[0] = 350 + output;
		CCR[1] = 350 + output;
		CCR[2] = 750 - output;
		CCR[3] = 750 - output;
	}
	else // 右边转弯巡线
	{
		CCR[0] = 750 + output;
		CCR[1] = 750 + output;
		CCR[2] = 350 - output;
		CCR[3] = 350 - output;
	}
	static double MAX_CCR = 0;
	for (int i = 0; i < 4; i++)
	{
		if (CCR[i] > MAX_CCR)
			MAX_CCR = CCR[i];
	}
	if (MAX_CCR > 1150)
	{
		for (int i = 0; i < 4; i++)
		{
			CCR[i] = CCR[i] * 1150 / MAX_CCR;
		}
	}
	DEV_CAR_Set_Speed(CCR);
}

void follow_angle(void)
{
#ifdef ANGULAR_VELOCITY_VERSION
	const double K_P = 39.0, K_D = 2.35;
	double diff = Aim_Angle - Angle.value;
	if (diff > 180)
	{
		diff = diff - 360;
	}
	else if (diff < -180)
	{
		diff = diff + 360;
	}
	int output = K_P * (diff)-K_D * (Angle.value_w);
#else
	int output = PID_Realize_angle(&pid_follow_angle, (Aim_Angle - Angle.value));
#endif
	CCR[0] = 850 + output;
	CCR[1] = 850 + output;
	CCR[2] = 850 - output;
	CCR[3] = 850 - output;

	DEV_CAR_Set_Speed(CCR);
}

void turn_angle(void)
{
#ifdef ANGULAR_VELOCITY_VERSION
	const double K_P = 32.2, K_D = 2.84, K_I = 0.1;
	const int MAX_ITEM = 50;
	static int I_item = 0;
	double diff = Aim_Angle - Angle.value;
	if (diff > 180)
	{
		diff = diff - 360;
	}
	else if (diff < -180)
	{
		diff = diff + 360;
	}
	I_item += K_I * diff;
	if (I_item > MAX_ITEM)
		I_item = MAX_ITEM;
	else if (I_item < (-MAX_ITEM))
		I_item = -MAX_ITEM;
	int output = K_P * (diff)-K_D * (Angle.value_w) + I_item;
#else
	int output = PID_Realize_angle(&pid_turn_angle, (Aim_Angle - Angle.value));
#endif
	CCR[0] = +(output);
	CCR[1] = +(output);
	CCR[2] = -(output);
	CCR[3] = -(output);
	int max_ = 0;
	for (int i = 0; i < 4; i++)
	{
		if (CCR[i] > 0)
			CCR[i] += 230;
		else if (CCR[i] < 0)
			CCR[i] -= 230;
		if (abs(CCR[i]) > max_)
			max_ = abs(CCR[i]);
		if (CCR[i] > 800)
			CCR[i] = 800;
		else if (CCR[i] < -800)
			CCR[i] = -800;
	}

	DEV_CAR_Set_Speed(CCR);
}

/**
 * @description: go straight to the black line
 */
void task1(void)
{
	switch (task1_index)
	{
	case 0:
		if (not_on_drak_line_flag) // 未到黑线处就一直直走
		{
			Aim_Angle = 0;
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task = NULL;
			task1_index = -1;
		}
		break;
	default:
		break;
	}
	return;
}

/**
 * @description: 走0字形
 */
void task2(void)
{
	static uint8_t count_time = 0;
	static int diff = 0;
	static int last_count_time = 0;
	count_time++;
	switch (task2_index)
	{
	case 0: // 直走到黑线处
		if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			Aim_Angle = 0;
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task2_index++;
			count_time = 0;
			on_drak_line_flag = 1;
			Aim_Angle = 0;
		}
		break;
	case 1: // 向右寻线
		diff = Angle.value + 180;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (count_time < WAITING_TIME) // 新手保护期
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag) // 在黑线上就一直向右寻线
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else if (abs(diff) > 90) // 如果角度偏离太多就转弯
		{
			Aim_Angle = Angle.value + 90;
			turn_angle();
		}
		else // 否则进入下一个case, 判断是否可以出弯
		{
			task2_index++;
			count_time = 0;
			last_count_time = 0;
			Aim_Angle = 180;
		}
		break;
	case 2:					 // 出弯
		if (count_time < 13) // filter dirty data
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else
		{
			if (last_count_time > 4) // if the car is not on the black line for a long time, enter the next case
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task2_index++;
				count_time = 0;
				Aim_Angle = 180;
				last_count_time = 0;
				count_time = 0;
			}
			else // otherwise, return to the previous case
			{
				task2_index--;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	case 3: // turn the car to the right angle which is 180
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else
		{
			task2_index++;
			count_time = 0;
			not_on_drak_line_flag = 1;
			Aim_Angle = 180;
		}
		break;
	case 4:							   // go straight to the black line
		if (count_time < WAITING_TIME) // 新手保护期
		{
			follow_angle();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag) // 如果不在黑线上就一直直走
		{
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task2_index++;
			count_time = 0;
			on_drak_line_flag = 1;
			Aim_Angle = 180;
			last_count_time = 0;
		}
		break;
	case 5: // after the car is on the black line, adjust the car to the right angle which is 0
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else
		{
			task2_index++;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 6: // follow the black line to the end
		diff = Angle.value;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value + 90;
			turn_angle();
		}
		else
		{
			task2_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 7: // judge whether the car is on the end of the black line,if not, return to the previous case, otherwise, stop this task
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task2_index = -1;
				count_time = 0;
				Aim_Angle = 0;
				last_count_time = 0;
				count_time = 0;
				task = NULL;
			}
			else
			{
				task2_index = 6;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	default:
		break;
	}
	return;
}

/**
 * @description: 走8字形
 */
void task3(void)
{
	static uint8_t count_time = 0;
	static uint8_t last_count_time = 0;
	static uint8_t turn_count = 0;
	count_time++;
	int diff = 0;
	switch (task3_index)
	{
	case 0:	// turn the car to the right angle which is atan(80/100) 
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			last_count_time = 0;
			task3_index++;
			count_time = 0;
		}
		break;
	case 1:	// go straight to the black line
		if (count_time < WAITING_TIME)
		{
			follow_angle();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task3_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 2:	// turn the car to the right angle which is 0
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task3_index++;
			count_time = 0;
			last_count_time = 0;
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
		}
		break;
	case 3:	// follow the black line to the left
		diff = Angle.value + 180;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_LEFT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag)
		{
			follow_line(FOLLOW_LINE_DIR_LEFT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value - 90;
			turn_angle();
		}
		else
		{
			task3_index++;
			count_time = 0;
			Aim_Angle = -SPECIAL_ANGLE + 180;
			last_count_time = 0;
		}
		break;
	case 4:	// judge whether the car is on the end of the black line,if not, return to the previous case, otherwise, enter the next case
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_LEFT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task3_index++;
				count_time = 0;
				Aim_Angle = -SPECIAL_ANGLE + 180;
				last_count_time = 0;
			}
			else
			{
				task3_index = 3;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	case 5:	// turn the car to the right angle which is 180 - atan(80/100)
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task3_index++;
			count_time = 0;
		}
		break;
	case 6:	// go straight to the black line
		if (count_time < WAITING_TIME)
		{
			follow_angle();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task3_index++;
			Aim_Angle = 180;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 7:	// turn the car to the right angle which is 180
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task3_index++;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 8:	// follow the black line to the end
		diff = Angle.value;
		if (count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value + 90;
			turn_angle();
		}
		else
		{
			task3_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 9:	// judge whether the car is on the end of the black line,if not, return to the previous case, otherwise, stop this task
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task3_index = -1;
				count_time = 0;
				Aim_Angle = 0;
				last_count_time = 0;
				count_time = 0;
				task = NULL;
			}
			else
			{
				task3_index = 8;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	default:
		break;
	}
	return;
}

/**
 * @description: 走四次8字形
 */
void task4(void)
{
	static uint8_t count_time = 0;
	static uint8_t last_count_time = 0;
	static uint8_t turn_count = 0;
	count_time++;
	int diff = 0;
	if (task4_index >= 4 * 10)	// four times is over, stop this task
	{
		count_time = 0;
		last_count_time = 0;
		turn_count = 0;
		task4_index = -1;
		task = NULL;
		return;
	}
	switch ((task4_index % 10))
	{
	case 0:	// turn the car to the right angle which is atan(80/100)
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle_FAST();
		}
		else if (turn_count < 5)
		{
			turn_angle_FAST();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			last_count_time = 0;
			task4_index++;
			count_time = 0;
			Follow_Angle_Count = 0;
		}
		break;
	case 1:	// go straight to the black line
		if (count_time < WAITING_TIME)
		{
			follow_angle_FAST();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle_FAST();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task4_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 2:	// turn the car to the right angle which is 0
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && abs(diff) > 1.5)
		{
			last_count_time++;
			turn_angle_FAST();
		}
		else if (turn_count < 5)
		{
			turn_angle_FAST();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task4_index++;
			count_time = 0;
			last_count_time = 0;
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
		}
		break;
	case 3:	// follow the black line to the left
		diff = Angle.value + 180;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (count_time < WAITING_TIME)
		{
			follow_line_FAST(FOLLOW_LINE_DIR_LEFT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag)
		{
			follow_line_FAST(FOLLOW_LINE_DIR_LEFT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value - 90;
			turn_angle_FAST();
		}
		else
		{
			task4_index++;
			count_time = 0;
			Aim_Angle = -SPECIAL_ANGLE + 180;
			last_count_time = 0;
		}
		break;
	case 4:	// judge whether the car is on the end of the black line,if not, return to the previous case, otherwise, enter the next case
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line_FAST(FOLLOW_LINE_DIR_LEFT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task4_index++;
				count_time = 0;
				Aim_Angle = -SPECIAL_ANGLE + 180;
				last_count_time = 0;
				count_time = 0;
			}
			else
			{
				task4_index--;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	case 5:	// turn the car to the right angle which is 180 - atan(80/100)
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			turn_angle_FAST();
			last_count_time++;
		}
		else if (turn_count < 5)
		{
			turn_angle_FAST();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task4_index++;
			count_time = 0;
			Follow_Angle_Count = 0;
		}
		break;
	case 6:	// go straight to the black line
		if (count_time < WAITING_TIME)
		{
			follow_angle_FAST();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle_FAST();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task4_index++;
			Aim_Angle = 180;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 7:	// turn the car to the right angle which is 180
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle_FAST();
		}
		else if (turn_count < 5)
		{
			turn_angle_FAST();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task4_index++;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 8:	// follow the black line to the end
		diff = Angle.value;
		if (count_time < WAITING_TIME)
		{
			follow_line_FAST(FOLLOW_LINE_DIR_RIGHT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_line_FAST(FOLLOW_LINE_DIR_RIGHT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value + 90;
			turn_angle_FAST();
		}
		else
		{
			task4_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 9:	// judge whether the car is on the end of the black line,if not, return to the previous case, otherwise, start the 8-shape task again
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line_FAST(FOLLOW_LINE_DIR_LEFT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task4_index++;
				count_time = 0;
				Aim_Angle = SPECIAL_ANGLE;
				last_count_time = 0;
				count_time = 0;
			}
			else
			{
				task4_index--;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	default:
		break;
	}
	return;
}

/**
 * @description: this task is similar to task4, but the car will slower when it goes straight
 */
void task5(void)
{
	static uint8_t count_time = 0;
	static uint8_t last_count_time = 0;
	static uint8_t turn_count = 0;
	count_time++;
	int diff = 0;
	if (task5_index >= 4 * 10)
	{
		count_time = 0;
		last_count_time = 0;
		turn_count = 0;
		task5_index = -1;
		task = NULL;
		return;
	}
	switch ((task5_index % 10))
	{
	case 0:
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			last_count_time = 0;
			task5_index++;
			count_time = 0;
			Follow_Angle_Count = 0;
		}
		break;
	case 1:
		if (count_time < WAITING_TIME)
		{
			follow_angle();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task5_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 2:
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && abs(diff) > 1.5)
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task5_index++;
			count_time = 0;
			last_count_time = 0;
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
		}
		break;
	case 3:
		diff = Angle.value + 180;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_LEFT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag)
		{
			follow_line(FOLLOW_LINE_DIR_LEFT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value - 90;
			turn_angle();
		}
		else
		{
			task5_index++;
			count_time = 0;
			Aim_Angle = -SPECIAL_ANGLE + 180;
			last_count_time = 0;
		}
		break;
	case 4:
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_LEFT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task5_index++;
				count_time = 0;
				Aim_Angle = -SPECIAL_ANGLE + 180;
				last_count_time = 0;
				count_time = 0;
			}
			else
			{
				task5_index--;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	case 5:
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if ((last_count_time < WAITING_TIME_TURN) && (abs(diff) > 1.5))
		{
			turn_angle();
			last_count_time++;
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task5_index++;
			count_time = 0;
			Follow_Angle_Count = 0;
		}
		break;
	case 6:
		if (count_time < WAITING_TIME)
		{
			follow_angle();
			not_on_drak_line_flag = 1;
		}
		else if (not_on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_angle();
		}
		else
		{
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
			task5_index++;
			Aim_Angle = 180;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 7:
		diff = Angle.value - Aim_Angle;
		diff = diff > 180 ? diff - 360 : diff;
		diff = diff < -180 ? diff + 360 : diff;
		if (last_count_time < WAITING_TIME_TURN && (abs(diff) > 1.5))
		{
			last_count_time++;
			turn_angle();
		}
		else if (turn_count < 5)
		{
			turn_angle();
			turn_count++;
		}
		else
		{
			turn_count = 0;
			task5_index++;
			count_time = 0;
			last_count_time = 0;
		}
		break;
	case 8:
		diff = Angle.value;
		if (count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
			on_drak_line_flag = 1;
		}
		else if (on_drak_line_flag || count_time < WAITING_TIME)
		{
			follow_line(FOLLOW_LINE_DIR_RIGHT);
		}
		else if (abs(diff) > 90)
		{
			Aim_Angle = Angle.value + 90;
			turn_angle();
		}
		else
		{
			task5_index++;
			count_time = 0;
			Aim_Angle = 0;
			last_count_time = 0;
		}
		break;
	case 9:
		if ((count_time) < 13)
		{
			if (not_on_drak_line_flag)
				last_count_time++;
			count_time++;
			follow_line(FOLLOW_LINE_DIR_LEFT);
		}
		else
		{
			if (last_count_time > 4)
			{
				LED_ON();
				Car_Set_Direction(4, BRAKE);
				Car_Set_Direction(3, BRAKE);
				Car_Set_Direction(2, BRAKE);
				Car_Set_Direction(1, BRAKE);
				task5_index++;
				count_time = 0;
				Aim_Angle = SPECIAL_ANGLE;
				last_count_time = 0;
				count_time = 0;
			}
			else
			{
				task5_index--;
				last_count_time = 0;
				count_time = 0;
			}
		}
		break;
	default:
		break;
	}
	return;
}

/**
 * @description: this task is used to tune the PID parameters of the angle
 */
void turn_angle_tuning(void)
{
	Aim_Angle = -90;
	turn_angle();
	int diff = Angle.value - Aim_Angle;
	static int count = 0;
	diff = diff > 180 ? diff - 360 : diff;
	diff = diff < -180 ? diff + 360 : diff;
	if (abs(diff) < .4)
	{
		if ((++count) > 10)
		{
			count = 0;
			task = NULL;
			LED_ON();
			Car_Set_Direction(4, BRAKE);
			Car_Set_Direction(3, BRAKE);
			Car_Set_Direction(2, BRAKE);
			Car_Set_Direction(1, BRAKE);
		}
	}
}