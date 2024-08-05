#ifndef C0_LCD_1602_H
#define C0_LCD_1602_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../i2c/i2c.h"

extern void delay(int);

void LCD_1602_I2C_Init();
void LCD_1602_I2C_Write(char * ptr);

#ifdef __cplusplus
}
#endif
#endif //C0_LCD_1602_H
