.section .text, "ax", %progbits
.arm
.align 4

.global _ZN2nw4font16DispStringBufferC1Ej
.global _ZN2nw4font16DispStringBuffer25CalcCommandBufferCapacityEj

_ZN2nw4font16DispStringBufferC1Ej:
    push {r4, lr}
    mov r4, r0
    mov r0, r1
    add ip, r1, #7
    add r2, r1, r0, lsl #1
    add r3, r2, r0, lsl #3
    lsr r2, ip, #3
    add ip, r2, #3
    add r3, r4, r3, lsl #2
    add r2, r3, #0x20
    str r1, [r4]
    str r2, [r4, #0xc]
    mov r1, #0
    strh r1, [r4, #4]
    str r1, [r4, #0x14]
    mvn r3, #0
    str r1, [r4, #0x1c]
    bic ip, ip, #3
    strh r3, [r4, #6]
    add r2, r2, ip
    strb r1, [r4, #8]
    str r2, [r4, #0x10]
    bl _ZN2nw4font16DispStringBuffer25CalcCommandBufferCapacityEj
    str r0, [r4, #0x18]
    mov r0, r4
    pop {r4, pc}

_ZN2nw4font16DispStringBuffer25CalcCommandBufferCapacityEj:
    ldr r3, =someShit
    str r4, [sp, #-4]!
    sub ip, r3, #0x18
    ldr r2, [r3]
    ldm ip, {r1, r4}
    ldr ip, [ip, #8]
    cmp r4, r1
    movhi r1, r4
    ldr r4, [r3, #4]
    ldr r3, [r3, #8]
    cmp r4, r2
    movhi r2, r4
    cmp ip, r1
    movhi r1, ip
    cmp r3, r2
    movhi r2, r3
    mov r3, #4
    add r1, r3, r1, lsr #2
    mov ip, #0x2a
    add r1, r1, #0x46
    add r2, ip, r2, lsr #2
    mla r0, r0, r1, r2
    pop {r4}
    bx lr
    
    .word 0x10
    .word 0x10
    .word 0x10
    .word 0x10
    .word 0x10
    .word 0x10
someShit:
    .word 0x30
    .word 0x30
    .word 0x30