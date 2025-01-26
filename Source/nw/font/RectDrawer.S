.section .text, "ax", %progbits
.arm
.align 4

.global _ZN2nw4font10RectDrawer9DrawBeginEj
.global _ZN2nw4font10RectDrawer7DrawEndEj
.global _ZN2nw4font10RectDrawer17SetViewMtxForTextERKN2nn4math5MTX34E

AddJumpCommand:
    push {r3, r4, r5, r6, r7, lr}
    mov r5, r1
    mov r6, r0
    mov r4, #0x18
    mov r1, sp
    mov r0, #0x208
    bl nngxGetCmdlistParameteri
    ldr r2, [sp]
    mov r1, #0
    add r0, r2, #0x18
    tst r0, #0xf
    moveq r0, r2
    beq LAB_0020ffbc
    str r1, [r2]
    add r0, r2, #8
    str r1, [r2, #4]
    mov r4, #0x20
    str r0, [sp]
LAB_0020ffbc:
    lsr r2, r5, #3
    str r2, [r0], #4
    ldr r2, [pc, #0xbc]
    add r5, r0, #4
    str r2, [r0], #4
    str r1, [r0], #4
    str r0, [sp]
    mov r0, r6
    bl nngxGetPhysicalAddr
    mov r1, r0
    ldr r0, [sp]
    lsr r1, r1, #3
    str r1, [r0], #4
    str r0, [sp]
    add r0, r0, #8
    bl nngxGetPhysicalAddr
    ldr r1, [sp]
    ldr r6, [pc, #0x84]
    lsr r3, r0, #3
    mov r2, #1
    str r2, [r1, #4]
    add r0, r1, #8
    str r3, [r1]
    str r0, [sp]
    ldr r1, [r6, #8]
    cmp r1, #0
    beq LAB_0021003c
    ldr r2, [r6, #4]
    sub r0, r0, r2
    lsr r0, r0, #3
    str r0, [r1]
    b LAB_00210070
LAB_0021003c:
    str r0, [r6]
    add r0, r0, #0x170
    bl __rt_memclr_w
    mov r1, r0
    ldr r0, [sp]
    lsr r1, r1, #3
    str r1, [r0, #-8]
    mov r1, #0x170
    bl nngxGetPhysicalAddr
    ldr r0, [sp]
    add r4, r4, #0x170
    add r0, r0, #0x170
    str r0, [sp]
LAB_00210070:
    ldr r0, [sp]
    add r6, r6, #4
    stm r6, {r0, r5}
    mov r0, r4
    bl nngxMoveCommandbufferPointer
    pop {r3, r4, r5, r6, r7, pc}
shitA:
    .word 0x804F0238
shitB:
    .word shits
shits:
    .word 0x0
    .word 0x0
    .word 0x0

_ZN2nw4font10RectDrawer9DrawBeginEj:
    push {r4, r5, r6, r7}
    tst r1, #1
    bne LAB_00255b8c
    ldr r4, [pc, #0x60]
    ldr r3, [pc, #0x60]
    mov ip, #0
    ldr r6, [pc, #0x5c]
    ldr r2, [r4]
    mov r5, #0x1000
    str r3, [r2, #4]
    add r3, r2, #8
    str ip, [r2]
    ldr r2, [pc, #0x48]
    add r1, r3, #0x10
    mov ip, r1
    add r1, r3, #0x18
    vldmia r2, {s0, s1, s2, s3}
    vstmia r3, {s0, s1, s2, s3}
    str r5, [ip]
    str r6, [r3, #0x14]
    str r1, [r4]
    ldr r1, [r0, #8]
    cmp r1, #0x10
    ble #0x6c
    ldr r0, [r0, #4]
    pop {r4, r5, r6, r7}
    b AddJumpCommand
LAB_00255b8c:
    pop {r4, r5, r6, r7}
    bx lr

    .word __cb_current_command_buffer
    .word 0x0002006F
    .word 0x000B0080
    .word shits2
shits2:
    .word 0x0
    .word 0x00200080
    .word 0x0
    .word 0x0
    .word 0x0

_ZN2nw4font10RectDrawer7DrawEndEj:
    tst r1, #1
    bne LAB_00255ad0
    ldr r1, [r0, #0x18]
    cmp r1, #0x10
    ble LAB_00255ad0
    ldr r0, [r0, #0x14]
    b AddJumpCommand
LAB_00255ad0:
    bx lr

_ZN2nw4font10RectDrawer17SetViewMtxForTextERKN2nn4math5MTX34E:
    push {r4, r5, r6, r7, r8, lr}
    mov r4, r0
    add r0, r0, #0x244
    ldr r6, [pc, #0x48]
    ldr r5, [r6]
    bl _ZN2nn4math5ARMv612MTX34CopyAsmEPNS0_5MTX34EPKS2_
    mov r0, #3
    ldr r1, [pc, #0x3c]
    strb r0, [r4, #0x25]
    ldr r3, [r4, #0x244]
    str r1, [r4, #0x244]
    add r0, r4, #0x238
    mov r7, #0
    mov r1, r0
    str r3, [r4, #0x240]
    mov r2, #0x40
    mov r0, r5
    str r7, [r4, #0x274]
    bl __rt_memcpy_w
    add r0, r5, #0x40
    strb r7, [r4, #0x25]
    str r0, [r6]
    pop {r4, r5, r6, r7, r8, pc}

    .word __cb_current_command_buffer
    .word 0x00BF02C1