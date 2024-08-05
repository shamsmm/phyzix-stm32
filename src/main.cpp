#include <cstdio>
#include "gpio/gpio.h"
#include "rcc/rcc.h"
#include "bluepill/bluepill.h"
#include "timer/systick.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"
#include "os/os.h"
#include "system/system.h"
#include "main.h"


_Alignas(8) uint32_t task1_stack[0x200];
_Alignas(8) uint32_t task2_stack[0x200];
_Alignas(8) uint32_t task3_stack[0x200];
_Alignas(8) uint32_t task4_stack[0x200];


void task1() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        sprintf(buffer, "T1: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 0, buffer, Font_11x18, RED,BLACK);
        os_schedule();
    }
}

void task2() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        counter++;
        sprintf(buffer, "T2: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 18 + 1, buffer, Font_11x18, RED,BLACK);
        os_schedule();
    }
}

void task3() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        counter++;
        counter++;
        sprintf(buffer, "T3: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 18 * 2 + 1, buffer, Font_11x18, RED,BLACK);
        os_schedule();
    }
}

void task4() {
    while(1) {
        GPIO_WritePin(PC13, LOW);
        delay(1000);
        GPIO_WritePin(PC13, HIGH);
        delay(1000);
    }
}

void APP_Configure_Hardware();

int main() {
    APP_Configure_Hardware();
    printf("Hardware configured successfully.\n");

    printf("OS initializing tasks...\n");
    os_init_scheduler(&task1_stack[0x200 - 8]);
    os_init_task_default(task1_stack, 0x200, task1, 0);
    os_init_task_default(task2_stack, 0x200, task2, 1);
    os_init_task_default(task3_stack, 0x200, task3, 2);
    os_init_task_default(task4_stack, 0x200, task4, 3);
    printf("OS initializing tasks done.\n");

    printf("OS context switching to first task using svc call.\n");
    __asm__ volatile ("svc %0" : : "I" (0));

    return 0;
}

void APP_Configure_Hardware() {
    // Use PLL for 128MHz clock
    RCC_PLL_System_Clock_Generic(PLL_Speed_128Mhz);

    // Enable various faults
    system_faults_configure();

    // Enable Systick
#if defined(SYSTICK_CLKSOURCE_EXTERNAL)
    SysTickReloadValue = 8000; // Clock source is external 8MHz
#elif defined(SYSTICK_CLKSOURCE_INTERNAL)
    SysTickControlAndStatus->CLKSOURCE = 1;
    SysTickReloadValue = 640000; // Clock source is AHB which is 64MHz
#endif
    SysTickControlAndStatus->TICKINT = 1;
    SysTickControlAndStatus->ENABLE = 1;

    // Enable Clocking to mostly used peripherals
    RCC_Clocks_Enable(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    RCC_Clocks_Enable(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);

    // GPIO and UART pins
    GPIO_PinMode(PA8, ALTERNATE); // To expose system clock
    GPIO_PinMode(PA9, ALTERNATE); // TX and RX
    GPIO_PinMode(PA10, ALTERNATE); // TX and RX
    GPIO_PinMode(PC13, OUTPUT); // LED

    // Enable UART
    UART_Enable(USART1, 64000000, 9600);

    // LCD pins (configured internally in module)
    GPIO_PinMode(PA2, OUTPUT);
    GPIO_PinMode(PB6, OUTPUT);
    GPIO_PinMode(PB11, OUTPUT);

    GPIO_PinMode(PA7, ALTERNATE);
    GPIO_PinMode(PA5, ALTERNATE);

    // Initialize screen
    ST7735_Init(0);
    fillScreen(BLACK);
}