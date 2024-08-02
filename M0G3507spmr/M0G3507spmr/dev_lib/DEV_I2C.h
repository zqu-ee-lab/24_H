/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-14 19:14:30
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-07-30 10:57:27
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_I2C.h
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef DEV_I2C__H_
#define DEV_I2C__H_

#include <ti/driverlib/dl_i2c.h>
#include "ti_msp_dl_config.h"
#include "buffer.h"
#include <string.h>

#define timeout_I2C 100

enum I2cControllerStatus {
    I2C_STATUS_IDLE = 0,
    I2C_STATUS_TX_STARTED,
    I2C_STATUS_TX_INPROGRESS,
    I2C_STATUS_TX_COMPLETE,
    I2C_STATUS_RX_STARTED,
    I2C_STATUS_RX_INPROGRESS,
    I2C_STATUS_RX_COMPLETE,
    I2C_STATUS_ERROR,
};

struct I2C_Device {
    I2C_Regs*  I2C_Controller;
    IRQn_Type  I2C_IRQ;
    enum I2cControllerStatus gStatus;
    uint8_t gTxPacket[256];
    int gTxCount;
    int gTxLen;
    struct Buff *gRxBuffer;
    uint8_t gAddr;
};

extern struct I2C_Device gI2C1_Device,gI2C0_Device;

int I2C_WriteArray_With_Blocking(struct I2C_Device *this, uint8_t *data, uint8_t len);
int I2C_WriteArray2Register_With_Blocking(struct I2C_Device *this, uint8_t* Register_addr, uint8_t addr_len, uint8_t *data, uint8_t len);
void I2C__init__(struct I2C_Device* this);

#endif // DEV_I2C__H_