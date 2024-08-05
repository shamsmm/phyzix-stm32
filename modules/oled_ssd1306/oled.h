#ifndef C0_OLED_H
#define C0_OLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "graphics/fonts.h"
#include "i2c/i2c.h"

#define OLED_7Bit_ADDRESS 0x3C
#define CONTROL_BYTE 0x00
#define DATA_BYTE 0x40

void OLED_I2C_Init();
void OLED_I2C_Draw(const char * ptr, int length);
void OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr);

#ifdef __cplusplus
}
#endif
#endif //C0_OLED_H
