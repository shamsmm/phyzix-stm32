#ifndef C0_OS_H
#define C0_OS_H

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t Tick;

typedef struct TCB {
    uint32_t * stack_pointer;
} TCB_TypeDef;

void os_enable_preemption();
void os_disable_preemption();
void os_init_task_default(uint32_t * stack, uint32_t stack_size, void (* task)(), uint32_t id);
void os_init_scheduler(uint32_t * stack);
void os_schedule();

#define OS_TASK_LOCK()      extern uint32_t os_preemption_status;\
                            uint32_t preemption_status = os_preemption_status;\
                            os_disable_preemption()

#define OS_TASK_UNLOCK()  if (preemption_status)\
                            os_enable_preemption()

#ifdef __cplusplus
}
#endif
#endif //C0_OS_H
