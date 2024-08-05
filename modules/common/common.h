#ifndef C0_COMMON_H
#define C0_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct Optional_7_Bits {
    uint8_t value    : 7;
    uint8_t exists   : 1;
} Optional_7_Bits_TypeDef;


#ifdef __cplusplus
}
#endif
#endif //C0_COMMON_H
