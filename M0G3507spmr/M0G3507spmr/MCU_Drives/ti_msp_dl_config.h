/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_Motor_Left */
#define PWM_Motor_Left_INST                                                TIMA0
#define PWM_Motor_Left_INST_IRQHandler                          TIMA0_IRQHandler
#define PWM_Motor_Left_INST_INT_IRQN                            (TIMA0_INT_IRQn)
#define PWM_Motor_Left_INST_CLK_FREQ                                    32000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_Motor_Left_C1_PORT                                        GPIOA
#define GPIO_PWM_Motor_Left_C1_PIN                                 DL_GPIO_PIN_9
#define GPIO_PWM_Motor_Left_C1_IOMUX                             (IOMUX_PINCM20)
#define GPIO_PWM_Motor_Left_C1_IOMUX_FUNC             IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_PWM_Motor_Left_C1_IDX                           DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_PWM_Motor_Left_C2_PORT                                        GPIOA
#define GPIO_PWM_Motor_Left_C2_PIN                                DL_GPIO_PIN_10
#define GPIO_PWM_Motor_Left_C2_IOMUX                             (IOMUX_PINCM21)
#define GPIO_PWM_Motor_Left_C2_IOMUX_FUNC             IOMUX_PINCM21_PF_TIMA0_CCP2
#define GPIO_PWM_Motor_Left_C2_IDX                           DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_PWM_Motor_Left_C3_PORT                                        GPIOB
#define GPIO_PWM_Motor_Left_C3_PIN                                DL_GPIO_PIN_24
#define GPIO_PWM_Motor_Left_C3_IOMUX                             (IOMUX_PINCM52)
#define GPIO_PWM_Motor_Left_C3_IOMUX_FUNC             IOMUX_PINCM52_PF_TIMA0_CCP3
#define GPIO_PWM_Motor_Left_C3_IDX                           DL_TIMER_CC_3_INDEX

/* Defines for PWM_Motor_Right */
#define PWM_Motor_Right_INST                                               TIMG6
#define PWM_Motor_Right_INST_IRQHandler                         TIMG6_IRQHandler
#define PWM_Motor_Right_INST_INT_IRQN                           (TIMG6_INT_IRQn)
#define PWM_Motor_Right_INST_CLK_FREQ                                   32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_Motor_Right_C0_PORT                                       GPIOB
#define GPIO_PWM_Motor_Right_C0_PIN                               DL_GPIO_PIN_10
#define GPIO_PWM_Motor_Right_C0_IOMUX                            (IOMUX_PINCM27)
#define GPIO_PWM_Motor_Right_C0_IOMUX_FUNC             IOMUX_PINCM27_PF_TIMG6_CCP0
#define GPIO_PWM_Motor_Right_C0_IDX                          DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_Motor_Right_C1_PORT                                       GPIOB
#define GPIO_PWM_Motor_Right_C1_PIN                               DL_GPIO_PIN_11
#define GPIO_PWM_Motor_Right_C1_IOMUX                            (IOMUX_PINCM28)
#define GPIO_PWM_Motor_Right_C1_IOMUX_FUNC             IOMUX_PINCM28_PF_TIMG6_CCP1
#define GPIO_PWM_Motor_Right_C1_IDX                          DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (1599U)




/* Defines for I2C0 */
#define I2C0_INST                                                           I2C0
#define I2C0_INST_IRQHandler                                     I2C0_IRQHandler
#define I2C0_INST_INT_IRQN                                         I2C0_INT_IRQn
#define I2C0_BUS_SPEED_HZ                                                 800000
#define GPIO_I2C0_SDA_PORT                                                 GPIOA
#define GPIO_I2C0_SDA_PIN                                         DL_GPIO_PIN_28
#define GPIO_I2C0_IOMUX_SDA                                       (IOMUX_PINCM3)
#define GPIO_I2C0_IOMUX_SDA_FUNC                        IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C0_SCL_PORT                                                 GPIOA
#define GPIO_I2C0_SCL_PIN                                         DL_GPIO_PIN_11
#define GPIO_I2C0_IOMUX_SCL                                      (IOMUX_PINCM22)
#define GPIO_I2C0_IOMUX_SCL_FUNC                       IOMUX_PINCM22_PF_I2C0_SCL


/* Defines for UART2 */
#define UART2_INST                                                         UART2
#define UART2_INST_IRQHandler                                   UART2_IRQHandler
#define UART2_INST_INT_IRQN                                       UART2_INT_IRQn
#define GPIO_UART2_RX_PORT                                                 GPIOB
#define GPIO_UART2_TX_PORT                                                 GPIOB
#define GPIO_UART2_RX_PIN                                         DL_GPIO_PIN_16
#define GPIO_UART2_TX_PIN                                         DL_GPIO_PIN_15
#define GPIO_UART2_IOMUX_RX                                      (IOMUX_PINCM33)
#define GPIO_UART2_IOMUX_TX                                      (IOMUX_PINCM32)
#define GPIO_UART2_IOMUX_RX_FUNC                       IOMUX_PINCM33_PF_UART2_RX
#define GPIO_UART2_IOMUX_TX_FUNC                       IOMUX_PINCM32_PF_UART2_TX
#define UART2_BAUD_RATE                                                 (115200)
#define UART2_IBRD_32_MHZ_115200_BAUD                                       (17)
#define UART2_FBRD_32_MHZ_115200_BAUD                                       (23)





/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOB)

/* Defines for Pin_LED: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_LED_Pin_LED_PIN                                    (DL_GPIO_PIN_26)
#define GPIO_LED_Pin_LED_IOMUX                                   (IOMUX_PINCM57)
/* Port definition for Pin Group GPIO_buzzer */
#define GPIO_buzzer_PORT                                                 (GPIOB)

/* Defines for PIN_BUZZER: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_buzzer_PIN_BUZZER_PIN                              (DL_GPIO_PIN_27)
#define GPIO_buzzer_PIN_BUZZER_IOMUX                             (IOMUX_PINCM58)
/* Port definition for Pin Group GPIO_Grayscale */
#define GPIO_Grayscale_PORT                                              (GPIOA)

/* Defines for PINA_22: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_Grayscale_PINA_22_PIN                              (DL_GPIO_PIN_22)
#define GPIO_Grayscale_PINA_22_IOMUX                             (IOMUX_PINCM47)
/* Defines for PINA_24: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_Grayscale_PINA_24_PIN                              (DL_GPIO_PIN_24)
#define GPIO_Grayscale_PINA_24_IOMUX                             (IOMUX_PINCM54)
/* Defines for PINA_25: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_Grayscale_PINA_25_PIN                              (DL_GPIO_PIN_25)
#define GPIO_Grayscale_PINA_25_IOMUX                             (IOMUX_PINCM55)
/* Defines for PINA_26: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_Grayscale_PINA_26_PIN                              (DL_GPIO_PIN_26)
#define GPIO_Grayscale_PINA_26_IOMUX                             (IOMUX_PINCM59)
/* Defines for PINA_27: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_Grayscale_PINA_27_PIN                              (DL_GPIO_PIN_27)
#define GPIO_Grayscale_PINA_27_IOMUX                             (IOMUX_PINCM60)
/* Defines for PINA_29: GPIOA.29 with pinCMx 4 on package pin 36 */
#define GPIO_Grayscale_PINA_29_PIN                              (DL_GPIO_PIN_29)
#define GPIO_Grayscale_PINA_29_IOMUX                              (IOMUX_PINCM4)
/* Defines for PINA_30: GPIOA.30 with pinCMx 5 on package pin 37 */
#define GPIO_Grayscale_PINA_30_PIN                              (DL_GPIO_PIN_30)
#define GPIO_Grayscale_PINA_30_IOMUX                              (IOMUX_PINCM5)
/* Defines for PINA_31: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_Grayscale_PINA_31_PIN                              (DL_GPIO_PIN_31)
#define GPIO_Grayscale_PINA_31_IOMUX                              (IOMUX_PINCM6)
/* Defines for PIN_2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_Grayscale_PIN_2_PIN                                (DL_GPIO_PIN_15)
#define GPIO_Grayscale_PIN_2_IOMUX                               (IOMUX_PINCM37)
/* Defines for PIN_3: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_Grayscale_PIN_3_PIN                                (DL_GPIO_PIN_16)
#define GPIO_Grayscale_PIN_3_IOMUX                               (IOMUX_PINCM38)
/* Port definition for Pin Group GPIO_Key */
#define GPIO_Key_PORT                                                    (GPIOB)

/* Defines for Key_0: GPIOB.21 with pinCMx 49 on package pin 20 */
// pins affected by this interrupt request:["Key_0","Key_1","Key_2"]
#define GPIO_Key_INT_IRQN                                       (GPIOB_INT_IRQn)
#define GPIO_Key_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_Key_Key_0_IIDX                                 (DL_GPIO_IIDX_DIO21)
#define GPIO_Key_Key_0_PIN                                      (DL_GPIO_PIN_21)
#define GPIO_Key_Key_0_IOMUX                                     (IOMUX_PINCM49)
/* Defines for Key_1: GPIOB.23 with pinCMx 51 on package pin 22 */
#define GPIO_Key_Key_1_IIDX                                 (DL_GPIO_IIDX_DIO23)
#define GPIO_Key_Key_1_PIN                                      (DL_GPIO_PIN_23)
#define GPIO_Key_Key_1_IOMUX                                     (IOMUX_PINCM51)
/* Defines for Key_2: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_Key_Key_2_IIDX                                 (DL_GPIO_IIDX_DIO25)
#define GPIO_Key_Key_2_PIN                                      (DL_GPIO_PIN_25)
#define GPIO_Key_Key_2_IOMUX                                     (IOMUX_PINCM56)
/* Port definition for Pin Group GPIO_Motor_Direction */
#define GPIO_Motor_Direction_PORT                                        (GPIOB)

/* Defines for Motor_Right_Back: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_Motor_Direction_Motor_Right_Back_PIN               (DL_GPIO_PIN_18)
#define GPIO_Motor_Direction_Motor_Right_Back_IOMUX              (IOMUX_PINCM44)
/* Defines for Motor_Right_Front: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_Motor_Direction_Motor_Right_Front_PIN              (DL_GPIO_PIN_19)
#define GPIO_Motor_Direction_Motor_Right_Front_IOMUX             (IOMUX_PINCM45)
/* Defines for Motor_Left_Back: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_Motor_Direction_Motor_Left_Back_PIN                (DL_GPIO_PIN_17)
#define GPIO_Motor_Direction_Motor_Left_Back_IOMUX               (IOMUX_PINCM43)
/* Defines for Motor_Left_Front: GPIOB.13 with pinCMx 30 on package pin 1 */
#define GPIO_Motor_Direction_Motor_Left_Front_PIN               (DL_GPIO_PIN_13)
#define GPIO_Motor_Direction_Motor_Left_Front_IOMUX              (IOMUX_PINCM30)
/* Defines for Motor_Right_Back_1: GPIOB.9 with pinCMx 26 on package pin 61 */
#define GPIO_Motor_Direction_Motor_Right_Back_1_PIN              (DL_GPIO_PIN_9)
#define GPIO_Motor_Direction_Motor_Right_Back_1_IOMUX            (IOMUX_PINCM26)
/* Defines for Motor_Right_Front_1: GPIOB.8 with pinCMx 25 on package pin 60 */
#define GPIO_Motor_Direction_Motor_Right_Front_1_PIN             (DL_GPIO_PIN_8)
#define GPIO_Motor_Direction_Motor_Right_Front_1_IOMUX           (IOMUX_PINCM25)
/* Defines for Motor_Left_Back_1: GPIOB.14 with pinCMx 31 on package pin 2 */
#define GPIO_Motor_Direction_Motor_Left_Back_1_PIN              (DL_GPIO_PIN_14)
#define GPIO_Motor_Direction_Motor_Left_Back_1_IOMUX             (IOMUX_PINCM31)
/* Defines for Motor_Left_Front_1: GPIOB.7 with pinCMx 24 on package pin 59 */
#define GPIO_Motor_Direction_Motor_Left_Front_1_PIN              (DL_GPIO_PIN_7)
#define GPIO_Motor_Direction_Motor_Left_Front_1_IOMUX            (IOMUX_PINCM24)
/* Port definition for Pin Group GPIO_GRP_0 */
#define GPIO_GRP_0_PORT                                                  (GPIOA)

/* Defines for PIN_0: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_GRP_0_PIN_0_PIN                                     (DL_GPIO_PIN_1)
#define GPIO_GRP_0_PIN_0_IOMUX                                    (IOMUX_PINCM2)
/* Defines for PIN_1: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_GRP_0_PIN_1_PIN                                     (DL_GPIO_PIN_0)
#define GPIO_GRP_0_PIN_1_IOMUX                                    (IOMUX_PINCM1)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_Motor_Left_init(void);
void SYSCFG_DL_PWM_Motor_Right_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C0_init(void);
void SYSCFG_DL_UART2_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
