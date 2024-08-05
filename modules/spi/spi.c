#include "spi.h"

void SPI_Transmit_Bytes(volatile SPI_Base_TypeDef * SPI, char * data, int size) {
    while (size--) {
        SPI_Transmit_Byte(SPI, *data++);
    }
}

void SPI_Transmit_Byte(volatile SPI_Base_TypeDef * SPI, char data) {
    SPI->DR = data;
    while (!SPI->SR.TXE) __asm__ volatile("nop");
}
