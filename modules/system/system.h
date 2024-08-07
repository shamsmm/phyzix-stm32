#ifndef C0_SYSTEM_H
#define C0_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#define SVC_CALL(n) __asm__ volatile ("svc %0" : : "I" (n))
void system_svc_call(uint8_t);
void system_faults_configure();

#ifdef __cplusplus
}
#endif
#endif //C0_SYSTEM_H
