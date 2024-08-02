/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:03:00
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_Grayscale.h
 * @Description: 
 * 
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved. 
 */
#ifndef DEV__GRAYSCALE_H__
#define DEV__GRAYSCALE_H__
#include <stdbool.h>
#include <stdint.h>
extern volatile uint8_t not_on_drak_line_flag;
extern volatile uint8_t on_drak_line_flag;
extern volatile uint8_t in_middle_flag;
int read_grayscale(void);
bool read_special_state(int num);


#endif // DEV__GRAYSCALE_H__