#include "bluepill.h"

void RCC_PLL_System_Clock_Generic(ClockSpeedTypeDef speed) {
    if (speed == PLL_Speed_128Mhz)
        RCC_PLL_System_Clock(16);
    else if (speed == PLL_Speed_72Mhz)
        RCC_PLL_System_Clock(9);
}