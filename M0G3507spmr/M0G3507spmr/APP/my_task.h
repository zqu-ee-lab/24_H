/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:38:50
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:32:45
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\APP\my_task.h
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#ifndef _MY_TASK_H__
#define _MY_TASK_H__

#include "APP_include.h"

extern int8_t task1_index;
extern int8_t task2_index;
extern int8_t task3_index;
extern int8_t task4_index;
extern int8_t task5_index;

void init_task(void);

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void turn_angle_tuning(void);

#endif