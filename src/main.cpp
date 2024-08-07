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
#include "spi/spi.h"
#include "app/Application.h"

_Alignas(8) uint32_t update_task_stack[0x200];
_Alignas(8) uint32_t render_task_stack[0x200];
_Alignas(8) uint32_t game_task_stack[0x200];

void App_Configure_Hardware();

int main() {
    App_Configure_Hardware();
    printf("Hardware configured successfully.\n");

    delay(500);

    printf("OS initializing threads...\n");
    os_init_scheduler(&game_task_stack[0x200 - 8]);
    os_init_task_default(update_task_stack, 0x200, Application::update, 2);
    os_init_task_default(render_task_stack, 0x200, Application::render, 1);
    os_init_task_default(game_task_stack, 0x200, Application::game, 0);
    printf("OS initializing threads done.\n");

    printf("OS context switching to first task using svc call.\n");
    SVC_CALL(0);

    return 0;
}

void App_SPI_Configure_Hardware() {
    SPI1->CR1.MSTR = 1;
    SPI1->CR1.BR = 0;
    SPI1->CR1.BIDIMODE = 1;
    SPI1->CR1.BIDIOE = 1;
    SPI1->CR1.SSI = 1;
    SPI1->CR1.SSM = 1;
    SPI1->CR1.SPE = 1;
}

void App_Configure_Hardware() {
    // Use PLL for 128MHz clock
    RCC_PLL_System_Clock_Generic(PLL_Speed_128Mhz);

    // Enable various faults
    system_faults_configure();

    // Enable Systick with one Tick every 10ms
    SysTickControlAndStatus->CLKSOURCE = 1;
    SysTickReloadValue = 640000; // Clock source is AHB which is 64MHz
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

    App_SPI_Configure_Hardware();

    // Initialize screen
    ST7735_Init(2);
    fillScreen(BLACK);
}