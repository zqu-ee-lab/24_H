#ifndef _DELAY_H
#define _DELAY_H

#include <stdint.h>
#include "ti_msp_dl_config.h"

extern volatile const uint64_t *p_the_std_time;
extern const uint32_t systick_period;
void delay_ms(unsigned int ms);
/**
 * @brief Get the current time in microseconds
 */
static inline uint64_t micros(void)
{
    return *p_the_std_time * 1000 + (1000 * (systick_period - SysTick->VAL)) / systick_period;
}
/**
 * @brief Get the current time in milliseconds
 * 
 */
static inline uint64_t millis(void)
{
    return *p_the_std_time;
}

#endif
