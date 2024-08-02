/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gPWM_Motor_LeftBackup;
DL_TimerG_backupConfig gPWM_Motor_RightBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_Motor_Left_init();
    SYSCFG_DL_PWM_Motor_Right_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_I2C0_init();
    SYSCFG_DL_UART2_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWM_Motor_LeftBackup.backupRdy 	= false;
	gPWM_Motor_RightBackup.backupRdy 	= false;



}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(PWM_Motor_Left_INST, &gPWM_Motor_LeftBackup);
	retStatus &= DL_TimerG_saveConfiguration(PWM_Motor_Right_INST, &gPWM_Motor_RightBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(PWM_Motor_Left_INST, &gPWM_Motor_LeftBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(PWM_Motor_Right_INST, &gPWM_Motor_RightBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(PWM_Motor_Left_INST);
    DL_TimerG_reset(PWM_Motor_Right_INST);
    DL_TimerG_reset(TIMER_0_INST);
    DL_I2C_reset(I2C0_INST);
    DL_UART_Main_reset(UART2_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(PWM_Motor_Left_INST);
    DL_TimerG_enablePower(PWM_Motor_Right_INST);
    DL_TimerG_enablePower(TIMER_0_INST);
    DL_I2C_enablePower(I2C0_INST);
    DL_UART_Main_enablePower(UART2_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Motor_Left_C1_IOMUX,GPIO_PWM_Motor_Left_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Motor_Left_C1_PORT, GPIO_PWM_Motor_Left_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Motor_Left_C2_IOMUX,GPIO_PWM_Motor_Left_C2_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Motor_Left_C2_PORT, GPIO_PWM_Motor_Left_C2_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Motor_Left_C3_IOMUX,GPIO_PWM_Motor_Left_C3_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Motor_Left_C3_PORT, GPIO_PWM_Motor_Left_C3_PIN);
    
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_Motor_Left_C1_IOMUX, GPIO_PWM_Motor_Left_C1_IOMUX_FUNC);
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_Motor_Left_C2_IOMUX, GPIO_PWM_Motor_Left_C2_IOMUX_FUNC);
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_Motor_Left_C3_IOMUX, GPIO_PWM_Motor_Left_C3_IOMUX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Motor_Right_C0_IOMUX,GPIO_PWM_Motor_Right_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Motor_Right_C0_PORT, GPIO_PWM_Motor_Right_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Motor_Right_C1_IOMUX,GPIO_PWM_Motor_Right_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Motor_Right_C1_PORT, GPIO_PWM_Motor_Right_C1_PIN);
    
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_Motor_Right_C0_IOMUX, GPIO_PWM_Motor_Right_C0_IOMUX_FUNC);
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_Motor_Right_C1_IOMUX, GPIO_PWM_Motor_Right_C1_IOMUX_FUNC);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C0_IOMUX_SDA,
        GPIO_I2C0_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C0_IOMUX_SCL,
        GPIO_I2C0_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C0_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C0_IOMUX_SCL);

    
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_UART2_IOMUX_TX, GPIO_UART2_IOMUX_TX_FUNC);
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_UART2_IOMUX_RX, GPIO_UART2_IOMUX_RX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_LED_Pin_LED_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_buzzer_PIN_BUZZER_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_22_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_24_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_25_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_26_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_27_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_29_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_30_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PINA_31_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PIN_2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Grayscale_PIN_3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Key_Key_0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Key_Key_1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Key_Key_2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Right_Back_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Right_Front_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Left_Back_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Left_Front_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Right_Back_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Right_Front_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Left_Back_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_Direction_Motor_Left_Front_1_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_GRP_0_PIN_0_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_GRP_0_PIN_1_IOMUX);

    DL_GPIO_clearPins(GPIOB, GPIO_LED_Pin_LED_PIN |
		GPIO_buzzer_PIN_BUZZER_PIN);
    DL_GPIO_setPins(GPIOB, GPIO_Motor_Direction_Motor_Right_Back_PIN |
		GPIO_Motor_Direction_Motor_Right_Front_PIN |
		GPIO_Motor_Direction_Motor_Left_Back_PIN |
		GPIO_Motor_Direction_Motor_Left_Front_PIN |
		GPIO_Motor_Direction_Motor_Right_Back_1_PIN |
		GPIO_Motor_Direction_Motor_Right_Front_1_PIN |
		GPIO_Motor_Direction_Motor_Left_Back_1_PIN |
		GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_LED_Pin_LED_PIN |
		GPIO_buzzer_PIN_BUZZER_PIN |
		GPIO_Motor_Direction_Motor_Right_Back_PIN |
		GPIO_Motor_Direction_Motor_Right_Front_PIN |
		GPIO_Motor_Direction_Motor_Left_Back_PIN |
		GPIO_Motor_Direction_Motor_Left_Front_PIN |
		GPIO_Motor_Direction_Motor_Right_Back_1_PIN |
		GPIO_Motor_Direction_Motor_Right_Front_1_PIN |
		GPIO_Motor_Direction_Motor_Left_Back_1_PIN |
		GPIO_Motor_Direction_Motor_Left_Front_1_PIN);
    DL_GPIO_setUpperPinsPolarity(GPIOB, DL_GPIO_PIN_21_EDGE_RISE_FALL |
		DL_GPIO_PIN_23_EDGE_RISE_FALL |
		DL_GPIO_PIN_25_EDGE_RISE_FALL);
    DL_GPIO_clearInterruptStatus(GPIOB, GPIO_Key_Key_0_PIN |
		GPIO_Key_Key_1_PIN |
		GPIO_Key_Key_2_PIN);
    DL_GPIO_enableInterrupt(GPIOB, GPIO_Key_Key_0_PIN |
		GPIO_Key_Key_1_PIN |
		GPIO_Key_Key_2_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    DL_SYSCTL_setHFCLKDividerForMFPCLK(DL_SYSCTL_HFCLK_MFPCLK_DIVIDER_2);
    DL_SYSCTL_enableMFCLK();
    DL_SYSCTL_enableMFPCLK();
	DL_SYSCTL_setMFPCLKSource(DL_SYSCTL_MFPCLK_SOURCE_HFCLK);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOB_INT_IRQn, 1);

}


/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_Motor_LeftClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gPWM_Motor_LeftConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 2000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_Motor_Left_init(void) {

    DL_TimerA_setClockConfig(
        PWM_Motor_Left_INST, (DL_TimerA_ClockConfig *) &gPWM_Motor_LeftClockConfig);

    DL_TimerA_initPWMMode(
        PWM_Motor_Left_INST, (DL_TimerA_PWMConfig *) &gPWM_Motor_LeftConfig);

    DL_TimerA_setCaptureCompareValue(PWM_Motor_Left_INST, 1500, DL_TIMER_CC_1_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(PWM_Motor_Left_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_Motor_Left_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptureCompareValue(PWM_Motor_Left_INST, 1500, DL_TIMER_CC_2_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(PWM_Motor_Left_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_Motor_Left_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptureCompareValue(PWM_Motor_Left_INST, 1500, DL_TIMER_CC_3_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(PWM_Motor_Left_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_Motor_Left_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_enableClock(PWM_Motor_Left_INST);


    
    DL_TimerA_setCCPDirection(PWM_Motor_Left_INST , DL_TIMER_CC1_OUTPUT | DL_TIMER_CC2_OUTPUT | DL_TIMER_CC3_OUTPUT );

}
/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_Motor_RightClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_Motor_RightConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 2000,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_Motor_Right_init(void) {

    DL_TimerG_setClockConfig(
        PWM_Motor_Right_INST, (DL_TimerG_ClockConfig *) &gPWM_Motor_RightClockConfig);

    DL_TimerG_initPWMMode(
        PWM_Motor_Right_INST, (DL_TimerG_PWMConfig *) &gPWM_Motor_RightConfig);

    DL_TimerG_setCaptureCompareValue(PWM_Motor_Right_INST, 1500, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_Motor_Right_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_Motor_Right_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptureCompareValue(PWM_Motor_Right_INST, 1500, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_Motor_Right_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_Motor_Right_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_enableClock(PWM_Motor_Right_INST);


    
    DL_TimerG_setCCPDirection(PWM_Motor_Right_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   160000 Hz = 32000000 Hz / (1 * (199 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 199U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (10ms * 160000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_0_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_0_INST);




}


static const DL_I2C_ClockConfig gI2C0ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C0_init(void) {

    DL_I2C_setClockConfig(I2C0_INST,
        (DL_I2C_ClockConfig *) &gI2C0ClockConfig);
    DL_I2C_disableAnalogGlitchFilter(I2C0_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C0_INST);
    /* Set frequency to 800000 Hz*/
    DL_I2C_setTimerPeriod(I2C0_INST, 3);
    DL_I2C_setControllerTXFIFOThreshold(I2C0_INST, DL_I2C_TX_FIFO_LEVEL_BYTES_2);
    DL_I2C_setControllerRXFIFOThreshold(I2C0_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C0_INST);

    /* Configure Interrupts */
    DL_I2C_enableInterrupt(I2C0_INST,
                           DL_I2C_INTERRUPT_TIMEOUT_A);

    NVIC_SetPriority(I2C0_INST_INT_IRQN, 1);

    /* Enable module */
    DL_I2C_enableController(I2C0_INST);

    DL_I2C_enableTimeoutA(I2C0_INST);
    DL_I2C_setTimeoutACount(I2C0_INST, 2);


}


static const DL_UART_Main_ClockConfig gUART2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART2_init(void)
{
    DL_UART_Main_setClockConfig(UART2_INST, (DL_UART_Main_ClockConfig *) &gUART2ClockConfig);

    DL_UART_Main_init(UART2_INST, (DL_UART_Main_Config *) &gUART2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART2_INST, UART2_IBRD_32_MHZ_115200_BAUD, UART2_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART2_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART2_INST_INT_IRQN, 0);


    DL_UART_Main_enable(UART2_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /*
     * Initializes the SysTick period to 1.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    DL_SYSTICK_config(32000);
}

