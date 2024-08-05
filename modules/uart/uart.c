#include "uart.h"
#include "rcc/rcc.h"

#define UE 13
#define TE 3
#define RE 2

void UART_Enable(UART uart, unsigned int clock, unsigned int baud) {
    unsigned short mantissa = clock / (16 * baud);
    uint8_t div = (uint8_t) ((mantissa - ((long) clock / (16 * baud))) * 16);
    *(uart.interface + USART_BRR) |= mantissa << 4 | div;
    *(uart.interface + USART_CR1) |= 1 << UE | 1 << TE;
}

void UART_Transmit(UART uart, char data) {
    *(uart.interface + USART_DR) = data;
    while(!(*(uart.interface + USART_SR) >> 6 & 1))
        __asm__ volatile("nop");
}

void UART_Transmit_Line(UART uart, const char* data) {
    int i = 0;

    while (*(data + i) != '\0') {
        *(uart.interface + USART_DR) = *(data + i++);
        while(!(*(uart.interface + USART_SR) >> 6 & 1))
            __asm__ volatile("nop");
    }
}

void UART_Transmit_Number(UART uart, unsigned short data) {
    if (data == 0) {
        UART_Transmit(uart, '0');
        return;
    }

    char buffer[10];

    uint8_t i = 0;

    while (data != 0) {
        buffer[i++] = (char) (data % 10) + 48;
        data /= 10;
    }

    for (uint8_t j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    buffer[i] = '\0';

    UART_Transmit_Line(uart, buffer);
}