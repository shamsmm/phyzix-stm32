#include <stdint.h>
#include <stdio.h>
#include "os.h"
#include "os_conf.h"
#include "system/system.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"
#include "timer/systick.h"

volatile uint32_t Tick = 0;

uint32_t current_task = 0;
uint32_t * initial_task_sp;
uint32_t os_preemption_status = 0;

TCB_TypeDef tasks[TASK_COUNT];

void os_enable_preemption() {
    os_preemption_status = 1;
}

void os_disable_preemption() {
    os_preemption_status = 0;
}

uint32_t ** os_current_task_sp() {
    return &tasks[current_task].stack_pointer;
}

uint32_t ** os_next_task_sp() {
    current_task = (current_task + 1) % TASK_COUNT;
    return os_current_task_sp();
}

void os_schedule() {
    *((volatile uint32_t *)0xE000ED04) = 0x10000000;
}

void os_init_task_default(uint32_t * stack, uint32_t stack_size, void (* task)(), uint32_t id) {
    stack[stack_size - 1] = 0x01000000;  // xPSR (Thumb state)
    stack[stack_size - 2] = (uint32_t) task & ~0x01UL;  // PC (task entry point)
    stack[stack_size - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[id].stack_pointer = &stack[stack_size - 8 - 8];  // Initial stack pointer
}

void os_init_scheduler(uint32_t * stack) {
    initial_task_sp = stack;
}

void SysTickHandler() {
    Tick++;

    if (os_preemption_status)
        os_schedule();
}

void SVCHandler() {
    __asm__ volatile ("msr psp, %0" : : "r" (initial_task_sp));

    __asm__ volatile ("ldr r0, =0xFFFFFFFD");

    os_enable_preemption();

    __asm__ volatile ("bx r0");
}