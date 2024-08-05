#ifndef C0_GPIO_H
#define C0_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "adc/adc.h"
#include "common/common.h"

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT_10MHz 1
#define GPIO_MODE_OUTPUT_2MHz 2
#define GPIO_MODE_OUTPUT_50MHz 3

#define GPIO_CNF_INPUT_ANALOG 0
#define GPIO_CNF_INPUT_FLOATING 1
#define GPIO_CNF_INPUT_PULLED_UP_OR_DOWN 2

#define GPIO_CNF_OUTPUT_PUSH_PULL 0
#define GPIO_CNF_OUTPUT_OPEN_DRAIN 1
#define GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL 2
#define GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN 3

typedef enum GPIO_Level {
    HIGH = 1,
    LOW = 0,
} GPIO_Level_TypeDef;

typedef struct GPIO_Base {
    unsigned long CRL: 32;
    unsigned long CRH: 32;
    unsigned long IDR: 16;
    unsigned long ODR: 16;
    unsigned long BSRR: 16;
    unsigned long BRR: 16;
} GPIO_Base_TypeDef;

typedef struct GPIO_Pin {
    volatile GPIO_Base_TypeDef * GPIO;
    uint8_t pin: 4;
    Optional_7_Bits_TypeDef adc_channel;
} GPIO_Pin_TypeDef;

typedef struct GPIO_Byte {
    volatile GPIO_Base_TypeDef * GPIO;
    uint8_t offset: 4;
} GPIO_Byte_TypeDef;

typedef struct GPIO_Port {
    volatile GPIO_Base_TypeDef * GPIO;
} GPIO_Port_TypeDef;


typedef struct GPIO_Pins_Configuration {
    uint8_t mode;
    uint8_t cnf;
    Optional_7_Bits_TypeDef odr;
} GPIO_Pins_Configuration_TypeDef;

void GPIO_WritePin(GPIO_Pin_TypeDef pin, GPIO_Level_TypeDef state);

void GPIO_WriteByte(GPIO_Byte_TypeDef byte, uint8_t data);

void GPIO_WritePort(GPIO_Port_TypeDef port, unsigned short data);

GPIO_Level_TypeDef GPIO_PinRead(GPIO_Pin_TypeDef pin);

uint8_t GPIO_ByteRead(GPIO_Byte_TypeDef byte);

short GPIO_PortRead(GPIO_Port_TypeDef port);

void GPIO_PinSet(GPIO_Pin_TypeDef pin);

void GPIO_PinReset(GPIO_Pin_TypeDef pin);

void GPIO_PinMode(GPIO_Pin_TypeDef pin, GPIO_Pins_Configuration_TypeDef conf);

void GPIO_ByteMode(GPIO_Byte_TypeDef byte, GPIO_Pins_Configuration_TypeDef conf);

void GPIO_PortMode(GPIO_Port_TypeDef port, GPIO_Pins_Configuration_TypeDef conf);


#ifdef __cplusplus
}
#endif
#endif //C0_GPIO_H
