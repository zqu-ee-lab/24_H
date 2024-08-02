/*
 * @Author: JAR_CHOW
 * @Date: 2024-07-14 19:14:10
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 11:01:04
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\DEV_I2C.c
 * @Description: the driver of I2C
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */
#include "DEV_I2C.h"

struct Buff I2C1_buffer, I2C0_buffer;


struct I2C_Device gI2C0_Device = {
	.I2C_Controller = I2C0,
	.I2C_IRQ = I2C0_INST_INT_IRQN,
	.gStatus = I2C_STATUS_IDLE,
	.gAddr = 0x3C,
	.gRxBuffer = &I2C0_buffer,
	.gTxPacket = {0},
	.gTxCount = 0,
	.gTxLen = 0,
};

void I2C__init__(struct I2C_Device *this)
{
	Iinitial_BUFF(this->gRxBuffer, 64);
	NVIC_ClearPendingIRQ(this->I2C_IRQ);
	NVIC_EnableIRQ(this->I2C_IRQ);
}

// 向OLED寄存器地址写一个byte的数据
int I2C_WriteArray_With_Blocking(struct I2C_Device *this, uint8_t *data, uint8_t len)
{
	uint8_t index = 0;
	int timeout = timeout_I2C;
	/* Wait for I2C to be Idle */
	while (!(DL_I2C_getControllerStatus(this->I2C_Controller) & DL_I2C_CONTROLLER_STATUS_IDLE) && timeout--)
		;

	/* Send the packet to the controller.
	 * This function will send Start + Stop automatically.
	 */
	DL_I2C_startControllerTransfer(this->I2C_Controller, this->gAddr,
								   DL_I2C_CONTROLLER_DIRECTION_TX, len);
	this->gStatus = I2C_STATUS_TX_STARTED;
	while ((len - index) > 0)
	{
		index += DL_I2C_fillControllerTXFIFO(this->I2C_Controller, &data[index], (len - index));
		timeout = timeout_I2C * 10;
		while ((!DL_I2C_isControllerTXFIFOEmpty(this->I2C_Controller)) && timeout--)
			;
		if (this->gStatus == I2C_STATUS_ERROR)
		{
			DL_I2C_flushControllerTXFIFO(this->I2C_Controller);		// clear TX FIFO
			return -1;
		}
	}
	/* Poll until the Controller writes all bytes */
	timeout = timeout_I2C;
	while ((DL_I2C_getControllerStatus(this->I2C_Controller) &
			DL_I2C_CONTROLLER_STATUS_BUSY_BUS) &&
		   timeout--)
		if (this->gStatus == I2C_STATUS_ERROR)
			return 0;

	/* Trap if there was an error */
	if (DL_I2C_getControllerStatus(this->I2C_Controller) &
		DL_I2C_CONTROLLER_STATUS_ERROR)
	{
		/* LED will remain high if there is an error */
//		__BKPT(0);
		return -1;
	}
	return 0;
}

int I2C_WriteArray2Register_With_Blocking(struct I2C_Device *this, uint8_t *Register_addr, uint8_t addr_len, uint8_t *data, uint8_t len)
{
	uint8_t index = 0;
	/* Wait for I2C to be Idle */
	int timeout = timeout_I2C;
	while (!(DL_I2C_getControllerStatus(this->I2C_Controller) & DL_I2C_CONTROLLER_STATUS_IDLE) && timeout--)
		;

	/* Send the packet to the controller.
	 * This function will send Start + Stop automatically.
	 */
	DL_I2C_startControllerTransfer(this->I2C_Controller, this->gAddr,
								   DL_I2C_CONTROLLER_DIRECTION_TX, addr_len + len);
	this->gStatus = I2C_STATUS_TX_STARTED;
	while ((addr_len - index) > 0)
	{
		index += DL_I2C_fillControllerTXFIFO(this->I2C_Controller, &Register_addr[index], (addr_len - index));
		timeout = timeout_I2C * 10;
		while (!(DL_I2C_isControllerTXFIFOEmpty(this->I2C_Controller)) && timeout--)
			;
		if (I2C_STATUS_ERROR == this->gStatus)
		{
			this->gStatus = I2C_STATUS_ERROR;
			DL_I2C_flushControllerTXFIFO(this->I2C_Controller);		// clear TX FIFO
			return -1;
		}
	}
	index = 0;
	while ((len - index) > 0)
	{
		index += DL_I2C_fillControllerTXFIFO(this->I2C_Controller, &data[index], (len - index));
		timeout = timeout_I2C * 10;
		while (!(DL_I2C_isControllerTXFIFOEmpty(this->I2C_Controller)) && timeout--)
			;
		if (-1 == timeout)
		{
			this->gStatus = I2C_STATUS_ERROR;
			DL_I2C_flushControllerTXFIFO(this->I2C_Controller);		// clear TX FIFO
			return -1;
		}
	}
	/* Poll until the Controller writes all bytes */
	timeout = timeout_I2C;
	while ((DL_I2C_getControllerStatus(this->I2C_Controller) &
			DL_I2C_CONTROLLER_STATUS_BUSY_BUS) &&
		   timeout--)
		if (this->gStatus == I2C_STATUS_ERROR)
			return 0;

	/* Trap if there was an error */
	if (DL_I2C_getControllerStatus(this->I2C_Controller) &
		DL_I2C_CONTROLLER_STATUS_ERROR)
	{
		/* LED will remain high if there is an error */
//		__BKPT(0);
		return -1;
	}
	return 0;
}

void I2C0_IRQHandler(void)
{
	switch (DL_I2C_getPendingInterrupt(gI2C0_Device.I2C_Controller))
	{
	case DL_I2C_IIDX_TIMEOUT_A:
		gI2C0_Device.gStatus = I2C_STATUS_ERROR;
		break;
	case DL_I2C_IIDX_CONTROLLER_ARBITRATION_LOST:
		gI2C0_Device.gStatus = I2C_STATUS_ERROR;
		break;
	default:
		break;
	}
}
