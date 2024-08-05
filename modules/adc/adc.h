#ifndef C0_ADC_H
#define C0_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio/gpio.h"

#define ADC_SR 0
#define ADC_CR1 1
#define ADC_CR2 2
#define ADC_SMPR1 3
#define ADC_SMPR2 4
#define ADC_JOFR1 5
#define ADC_JOFR2 6
#define ADC_JOFR3 7
#define ADC_JOFR4 8
#define ADC_HTR 9
#define ADC_LTR 10
#define ADC_SQR1 11
#define ADC_SQR2 12
#define ADC_SQR3 13
#define ADC_JSQR 14
#define ADC_JDR1 15
#define ADC_JDR2 16
#define ADC_JDR3 17
#define ADC_JDR4 18
#define ADC_DR 19

typedef enum ADC_Channel {
    CHANNEL0,
    CHANNEL1,
    CHANNEL2,
    CHANNEL3,
    CHANNEL4,
    CHANNEL5,
    CHANNEL6,
    CHANNEL7,
    CHANNEL8,
    CHANNEL9,
    CHANNEL10,
    CHANNEL11,
    CHANNEL12,
    CHANNEL13,
    CHANNEL14,
    CHANNEL15,
    CHANNEL16,
    CHANNEL17,
    NC = 100,
} ADC_Channel_TypeDef;

typedef struct ADC_CONFIGURATION {
    volatile unsigned long * interface;
} ADC_CONFIGURATION;

void enableContinuousADC(ADC_CONFIGURATION conf);

unsigned short analogReadInterface(ADC_CONFIGURATION conf, ADC_Channel_TypeDef channel);

#ifdef __cplusplus
}
#endif
#endif //C0_ADC_H
