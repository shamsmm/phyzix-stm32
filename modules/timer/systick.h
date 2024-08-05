#ifndef C0_SYSTICK_H
#define C0_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#define SysTickControlAndStatus ((volatile SysTickControlAndStatusTypeDef*) 0xE000E010)
#define SysTickReloadValue *((volatile unsigned long*) 0xE000E014)
#define SysTickCurrentValue *((volatile unsigned long*) 0xE000E018)

typedef struct SysTickControlAndStatusTypeDef {
    unsigned long ENABLE   :1,
                  TICKINT  :1,
                  CLKSOURCE:1,
                           :13,
                  COUNTFLAG:1,
                           :15;
} SysTickControlAndStatusTypeDef;

void delay(int milliseconds);

#ifdef __cplusplus
}
#endif
#endif //C0_SYSTICK_H
