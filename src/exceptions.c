_Noreturn void HardFaultException(void) {
    while(1) __asm__ volatile("nop");
}

_Noreturn void MemManageException(void) {
    while(1) __asm__ volatile("nop");
}

_Noreturn void BusFaultException(void) {
    while(1) __asm__ volatile("nop");
}

_Noreturn void UsageFaultException(void) {
    while(1) __asm__ volatile("nop");
}