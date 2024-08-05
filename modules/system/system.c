#include <stdint.h>
#include "system.h"

void system_faults_configure() {
    uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

    *pSHCSR |= ( 1 << 16); //mem manage
    *pSHCSR |= ( 1 << 17); //bus fault
    *pSHCSR |= ( 1 << 18); //usage fault
}

//void system_svc_call(uint8_t svc_number) {
//    __asm__ volatile ("svc %0" : : "I" (svc_number));
//}