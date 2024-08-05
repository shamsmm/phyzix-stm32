    .section .text.os
    .global PendSVC

    .extern tasks
    .extern current_task
    .extern os_next_task
    .thumb_func
    .syntax unified
PendSVC:
    // Store current context
    mrs r1, psp
    stmdb r1!, {r4-r11}

    push {r1}
    bl os_current_task_sp
    pop {r1}

    str r1, [r0]

    // Get the next task
    bl os_next_task_sp

    // Restore the next task context
    ldr r1, [r0]
    ldmia r1!, {r4-r11}

    // Set PSP to the new task's stack pointer
    msr psp, r1

    // Return to thread mode using the PSP
    ldr r0, =0xFFFFFFFD
    bx r0