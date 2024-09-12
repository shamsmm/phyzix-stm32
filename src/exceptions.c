#include "gpio/gpio.h"
#include "bluepill/bluepill.h"

#define PANIC_BLINK(profile) \
    GPIO_PinMode(PC13, OUTPUT); \
    uint32_t i = 0; \
    while(1) { \
        i += 1; \
        i %= 8; \
        GPIO_WritePin(PC13, (profile >> i) & 1 ? HIGH : LOW); \
        for (uint32_t j = 0; j < 1000000; ++j) __asm__ volatile("nop"); \
    }

_Noreturn void HardFaultException(void) {
    PANIC_BLINK(0b10101010);
}

_Noreturn void MemManageException(void) {
    PANIC_BLINK(0b1001001);
}

_Noreturn void BusFaultException(void) {
    PANIC_BLINK(0b1000001);
}

_Noreturn void UsageFaultException(void) {
    PANIC_BLINK(0b10000000);
}