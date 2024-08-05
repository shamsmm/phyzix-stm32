#ifndef C0_RCC_H
#define C0_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RCC (volatile unsigned long *) 0x40021000

#define RCC_APB2ENR 6
#define RCC_APB1ENR 7
#define RCC_CFGR 1

#define IOPAEN 1 << 2
#define IOPBEN 1 << 3
#define IOPCEN 1 << 4
#define ADC1EN 1 << 9
#define ADC2EN 1 << 10
#define USART1EN 1 << 14

typedef enum ClockSpeed {
    PLL_Speed_72Mhz = 72000000,
    PLL_Speed_128Mhz = 128000000
} ClockSpeedTypeDef;

typedef struct ClockConfiguration {
    char offset;
    unsigned long value;
} ClockConfigurationTypeDef;

void RCC_Clocks_Enable(ClockConfigurationTypeDef conf);

void RCC_PLL_System_Clock(uint8_t mul);

void RCC_PLL_System_Clock_Generic(ClockSpeedTypeDef speed);

#ifdef __cplusplus
}
#endif
#endif //C0_RCC_H
