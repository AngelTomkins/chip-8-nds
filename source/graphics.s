.syntax unified
.arch armv5te
.cpu arm946e-s

.align 4
.arm
.section .itcm
.global asm_update_bg
asm_update_bg:
  push {r4-r8,lr}
  mov r2, #32
  1:
  ldmia r0!, {r3-r8,r12,lr}
  stmia r1!, {r3-r8,r12,lr}
  ldmia r0!, {r3-r8,r12,lr}
  stmia r1!, {r3-r8,r12,lr}
  add r1, r1, #(128-64)
  subs r2, r2, #1
  bne 1b
  pop {r4-r8,lr}
  bx lr
