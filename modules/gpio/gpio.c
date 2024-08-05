#include "gpio.h"

void GPIO_PinMode(const GPIO_Pin_TypeDef pin, GPIO_Pins_Configuration_TypeDef conf) {
    if (pin.pin < 8) {
        pin.GPIO->CRL &= ~(0b1111 << (pin.pin * 4));
        pin.GPIO->CRL |= (((conf.mode & 0b11) | (conf.cnf & 0b11) << 2) << (pin.pin * 4));
    } else {
        pin.GPIO->CRH &= ~(0b1111 << ((pin.pin - 8) * 4));
        pin.GPIO->CRH |= ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2) << ((pin.pin - 8) * 4);
    }

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN)
        GPIO_WritePin(pin, conf.odr.value);
}

void GPIO_ByteMode(GPIO_Byte_TypeDef byte, struct GPIO_Pins_Configuration conf) {
    uint8_t pattern = ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2);

    if (byte.offset != 8) {
        byte.GPIO->CRL &= ~(0xFFFFFFFF);
        byte.GPIO->CRL |=
                pattern << 0 |
                pattern << 4 |
                pattern << 8 |
                pattern << 12 |
                pattern << 16 |
                pattern << 20 |
                pattern << 24 |
                pattern << 28;
    } else {
        byte.GPIO->CRH &= ~(0xFFFFFFFF);
        byte.GPIO->CRH |=
                pattern << 0 |
                pattern << 4 |
                pattern << 8 |
                pattern << 12 |
                pattern << 16 |
                pattern << 20 |
                pattern << 24 |
                pattern << 28;
    }

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN){
        if (conf.odr.exists) {
            GPIO_WriteByte(byte, 0xFF);
        } else {
            GPIO_WriteByte(byte, 0x00);
        }
    }
}

void GPIO_PortMode(GPIO_Port_TypeDef port, struct GPIO_Pins_Configuration conf) {
    uint8_t pattern = ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2);

    port.GPIO->CRL &= ~(0xFFFFFFFF);
    port.GPIO->CRL |=
            pattern << 0 |
            pattern << 4 |
            pattern << 8 |
            pattern << 12 |
            pattern << 16 |
            pattern << 20 |
            pattern << 24 |
            pattern << 28;

    port.GPIO->CRH &= ~(0xFFFFFFFF);
    port.GPIO->CRH |=
            pattern << 0 |
            pattern << 4 |
            pattern << 8 |
            pattern << 12 |
            pattern << 16 |
            pattern << 20 |
            pattern << 24 |
            pattern << 28;

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN) {
        if (conf.odr.exists) {
            GPIO_WritePort(port, 0xFFFF);
        } else {
            GPIO_WritePort(port, 0x0000);
        }
    }
}

void GPIO_WritePort(GPIO_Port_TypeDef port, unsigned short data) {
    port.GPIO->ODR = data;
}

void GPIO_WriteByte(GPIO_Byte_TypeDef byte, uint8_t data) {
    byte.GPIO->ODR = (byte.GPIO->ODR & (~(0xFF) << byte.offset)) | (data << byte.offset);
}


void GPIO_WritePin(GPIO_Pin_TypeDef pin, GPIO_Level_TypeDef state) {
    switch (state) {
        case HIGH:
            GPIO_PinSet(pin);
            break;
        case LOW:
            GPIO_PinReset(pin);
            break;
    }
}

GPIO_Level_TypeDef GPIO_PinRead(GPIO_Pin_TypeDef pin) {
    return (pin.GPIO->IDR & (1 << pin.pin)) != 0 ? HIGH : LOW;
}

uint8_t GPIO_ByteRead(GPIO_Byte_TypeDef byte) {
    return (uint8_t) ((byte.GPIO->IDR >> byte.offset) & (0xFF));
}

short GPIO_PortRead(GPIO_Port_TypeDef port) {
    return (short) (port.GPIO->IDR & (0xFFFF));
}

void GPIO_PinSet(GPIO_Pin_TypeDef pin) {
    pin.GPIO->BSRR = 1 << pin.pin;
}

void GPIO_PinReset(GPIO_Pin_TypeDef pin) {
    pin.GPIO->BSRR = 1 << pin.pin << 16;
}

