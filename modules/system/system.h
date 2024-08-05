#ifndef C0_SYSTEM_H
#define C0_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

void system_faults_configure();
void system_svc_call(uint8_t);

#ifdef __cplusplus
}
#endif
#endif //C0_SYSTEM_H
