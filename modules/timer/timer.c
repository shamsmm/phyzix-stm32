#include <stdint.h>

extern uint32_t Tick;

void delay(int milliseconds) {
    unsigned long initial = Tick;
    while (Tick - initial < milliseconds/10);
}