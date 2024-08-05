#ifndef C0_MPU_H
#define C0_MPU_H

#ifdef __cplusplus
extern "C" {
#endif

#define MPU ( (volatile MPU_Base_TypeDef *) 0xE000ED90)

//typedef struct MPU_CTRL {
//    unsigned long   ENABLE: 1,
//                    HFNMIENA: 1,
//                    PRIVDEFENA: 1,
//                    : 29;
//} MPU_CTRL_TypeDef;
//
//typedef struct MPU_RNR {
//    unsigned long   ENABLE: 1,
//            HFNMIENA: 1,
//            PRIVDEFENA: 1,
//            : 29;
//} MPU_RNR_TypeDef;


typedef struct MPU_Base {
    volatile unsigned long :32;
    volatile unsigned long CTRL;
    volatile unsigned long RNR;
    volatile unsigned long RBAR;
    volatile unsigned long RASR;
} MPU_Base_TypeDef;

#ifdef __cplusplus
}
#endif
#endif //C0_MPU_H
