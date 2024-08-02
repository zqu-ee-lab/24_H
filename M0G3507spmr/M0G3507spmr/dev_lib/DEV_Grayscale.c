/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-29 15:20:52
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-01 12:35:03
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_Grayscale.c
 * @Description: the driver of the grayscale sensor
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "DEV_Grayscale.h"
#include "ti_msp_dl_config.h"

volatile uint8_t not_on_drak_line_flag = 1;
volatile uint8_t on_drak_line_flag = 1;
volatile int gray_value = 0;

GPIO_Regs *const Grayscale_Port[10] = {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA};
const uint32_t Grayscale_Pin[10] = {DL_GPIO_PIN_14, DL_GPIO_PIN_22, DL_GPIO_PIN_24, DL_GPIO_PIN_25, DL_GPIO_PIN_26, DL_GPIO_PIN_27, DL_GPIO_PIN_29, DL_GPIO_PIN_30, DL_GPIO_PIN_31, DL_GPIO_PIN_13};

volatile uint8_t in_middle_flag = 0;

int read_grayscale(void)
{
    int reval = 0;
    int flag = 0;
    int flag1 = 0;
    for (int i = 0; i < 4; i++)
    {
        if (DL_GPIO_readPins(Grayscale_Port[i + 5], Grayscale_Pin[i + 5]))
        {
            reval += (1 << i);
            if (i == 0)
            {
                flag1 = 1;
            }
        }
        else
            flag = 1;

        if (DL_GPIO_readPins(Grayscale_Port[4 - i], Grayscale_Pin[4 - i]))
        {
            reval -= (1 << i);
            if (i == 0)
            {
                flag1 = 1;
            }
        }
        else
            flag = 1;
    }

    if (flag)
    {
        not_on_drak_line_flag = 0;
        on_drak_line_flag = 1;
    }
    else
    {
        not_on_drak_line_flag = 1;
        on_drak_line_flag = 0;
    }
    if (flag1)
    {
        in_middle_flag = 1;
    }
    else
    {
        in_middle_flag = 0;
    }
    return reval;
}

bool read_special_state(int num)
{
    return DL_GPIO_readPins(Grayscale_Port[num], Grayscale_Pin[num]);
}