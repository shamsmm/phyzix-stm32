#ifndef C0_BLUEPILL_H
#define C0_BLUEPILL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio/gpio.h"
#include "rcc/rcc.h"
#include "adc/adc.h"
#include "uart/uart.h"

#define PORTA (volatile GPIO_Base_TypeDef *) 0x40010800
#define PORTB (volatile GPIO_Base_TypeDef *) 0x40010C00
#define PORTC (volatile GPIO_Base_TypeDef *) 0x40011000

#define TIM1 (volatile unsigned long *) 0x40012C00
#define TIM2 (volatile unsigned long *) 0x40000000

const static UART USART1 = {(volatile unsigned long *) 0x40013800};

const static GPIO_Pins_Configuration_TypeDef OUTPUT = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_Pins_Configuration_TypeDef OUTPUT_OPEN_DRAIN = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_OPEN_DRAIN};
const static GPIO_Pins_Configuration_TypeDef OUTPUT_MEDIUM_SPEED = {GPIO_MODE_OUTPUT_10MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_Pins_Configuration_TypeDef OUTPUT_SLOW_SPEED = {GPIO_MODE_OUTPUT_2MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_Pins_Configuration_TypeDef ALTERNATE = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL};
const static GPIO_Pins_Configuration_TypeDef ALTERNATE_OPEN_DRAIN = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN};

const static GPIO_Pins_Configuration_TypeDef INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOATING};
const static GPIO_Pins_Configuration_TypeDef ANALOG_INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG};
const static GPIO_Pins_Configuration_TypeDef INPUT_PULLUP = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, HIGH, 1};
const static GPIO_Pins_Configuration_TypeDef INPUT_PULLDOWN = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, LOW, 1};

const static GPIO_Pin_TypeDef PC13 = {PORTC, 13};
const static GPIO_Pin_TypeDef PC14 = {PORTC, 14};
const static GPIO_Pin_TypeDef PC15 = {PORTC, 15};

const static GPIO_Pin_TypeDef PA0 = {PORTA, 0, 0, 1};
const static GPIO_Pin_TypeDef PA1 = {PORTA, 1, 1, 1};
const static GPIO_Pin_TypeDef PA2 = {PORTA, 2, 2, 1};
const static GPIO_Pin_TypeDef PA3 = {PORTA, 3, 3};
const static GPIO_Pin_TypeDef PA4 = {PORTA, 4, 4};
const static GPIO_Pin_TypeDef PA5 = {PORTA, 5, 5};
const static GPIO_Pin_TypeDef PA6 = {PORTA, 6, 6};
const static GPIO_Pin_TypeDef PA7 = {PORTA, 7, 7};
const static GPIO_Pin_TypeDef PA8 = {PORTA, 8};
const static GPIO_Pin_TypeDef PA9 = {PORTA, 9};
const static GPIO_Pin_TypeDef PA10 = {PORTA, 10};

const static GPIO_Pin_TypeDef PB0 = {PORTB, 0, 8, 1};
const static GPIO_Pin_TypeDef PB1 = {PORTB, 1, 9, 1};
const static GPIO_Pin_TypeDef PB2 = {PORTB, 2};
const static GPIO_Pin_TypeDef PB3 = {PORTB, 3};
const static GPIO_Pin_TypeDef PB4 = {PORTB, 4};
const static GPIO_Pin_TypeDef PB5 = {PORTB, 5};
const static GPIO_Pin_TypeDef PB6 = {PORTB, 6};
const static GPIO_Pin_TypeDef PB7 = {PORTB, 7};
const static GPIO_Pin_TypeDef PB8 = {PORTB, 8};
const static GPIO_Pin_TypeDef PB9 = {PORTB, 9};
const static GPIO_Pin_TypeDef PB10 = {PORTB, 10};
const static GPIO_Pin_TypeDef PB11 = {PORTB, 11};
const static GPIO_Pin_TypeDef PB12 = {PORTB, 12};
const static GPIO_Pin_TypeDef PB13 = {PORTB, 13};
const static GPIO_Pin_TypeDef PB14 = {PORTB, 14};
const static GPIO_Pin_TypeDef PB15 = {PORTB, 15};
const static GPIO_Byte_TypeDef PA0PA7 = {PORTA, 0};

const static GPIO_Byte_TypeDef PB0PB7 = {PORTB, 0};
const static GPIO_Byte_TypeDef PB8PB15 = {PORTB, 8};
const static GPIO_Port_TypeDef PB0PB15 = {PORTB};

const static ClockConfigurationTypeDef BLUEPILL_ALL_APB2_INTERFACES_CLOCK = {RCC_APB2ENR, IOPAEN | IOPBEN | IOPCEN | ADC1EN | ADC2EN | USART1EN | 1 << 12};
const static ClockConfigurationTypeDef BLUEPILL_ALL_APB1_INTERFACES_CLOCK = {RCC_APB1ENR, 1 | (1 << 21)};

unsigned short analogRead(GPIO_Pin_TypeDef gpio);

void enablePLLAsSystemClock72MHz();

void enablePLLAsSystemClock128MHz();

#ifdef __cplusplus
}
#endif
#endif //C0_BLUEPILL_H
