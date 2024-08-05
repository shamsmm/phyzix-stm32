#include "i2c.h"

void I2C_Init() {
    I2C_CR1->SWREST = 1;
    I2C_CR1->SWREST = 0;
    I2C_CR1->PE = 0;

    I2C_CR2->FREQ = 32; // Set APB1 frequency to 32MHz as set by RCC
    I2C_CCR->CCR = 160; // 2 * CCR * T_APB1 = 1/100KHz
//    I2C_TRISE->TRISE = 0;

    I2C_CR1->PE = 1;
}

void I2C_Read(char address) {
    while (I2C_SR2->BUSY);

    I2C_CR1->ACK = 1;
    I2C_CR1->START = 1;

    while(!I2C_SR1->SB);

    I2C_DR = address << 1 | 1; // Slave Address is 7 bits and first bit is read
    while (!I2C_SR1->ADDR || !I2C_SR2->MSL); // Reading from both SR1 and SR2 is required to clear ADDR flag

    while (!I2C_SR1->TxE);
}

void I2C_Start_Raw(char address) {
    while (I2C_SR2->BUSY);

    I2C_CR1->ACK = 1;
    I2C_CR1->START = 1;

    while(!I2C_SR1->SB);

    I2C_DR = address;
    while (!I2C_SR1->ADDR || !I2C_SR2->MSL); // Reading from both SR1 and SR2 is required to clear ADDR flag

    while (!I2C_SR1->TxE);
}

void I2C_Start(char address) {
    while (I2C_SR2->BUSY);

    I2C_CR1->ACK = 1;
    I2C_CR1->START = 1;

    while(!I2C_SR1->SB);

    I2C_DR = address << 1; // Slave Address is 7 bits and first bit is read or write
    while (!I2C_SR1->ADDR || !I2C_SR2->MSL); // Reading from both SR1 and SR2 is required to clear ADDR flag

    while (!I2C_SR1->TxE);
}
void I2C_Send(char data) {
    I2C_DR = data; // Data
    while (!I2C_SR1->BTF);
}
void I2C_End() {
//    I2C_CR1->ACK = 0;
    I2C_CR1->STOP = 1;
}

void I2C_Send_Byte(char address, char data) {
    while (I2C_SR2->BUSY);

    I2C_CR1->ACK = 1;
    I2C_CR1->START = 1;

    while(!I2C_SR1->SB);

    I2C_DR = address << 1; // Slave Address is 7 bits and first bit is read or write
    while (!I2C_SR1->ADDR || !I2C_SR2->MSL); // Reading from both SR1 and SR2 is required to clear ADDR flag

    while (!I2C_SR1->TxE);
    I2C_DR = data; // Data
    while (!I2C_SR1->BTF);
    I2C_CR1->STOP = 1;
}

void I2C_Send_2_Bytes(char address, short data) {
    while (I2C_SR2->BUSY);

    I2C_CR1->ACK = 1;
    I2C_CR1->START = 1;

    while(!I2C_SR1->SB);

    I2C_DR = address << 1; // Slave Address is 7 bits and first bit is read or write
    while (!I2C_SR1->ADDR || !I2C_SR2->MSL); // Reading from both SR1 and SR2 is required to clear ADDR flag

    while (!I2C_SR1->TxE);
    I2C_DR = data; // Data
    while (!I2C_SR1->BTF);
    I2C_DR = data >> 8; // Data
    while (!I2C_SR1->BTF);
    I2C_CR1->STOP = 1;
}