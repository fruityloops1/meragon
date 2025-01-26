.arm
.align 4

.section .text._ZN2mg20abortWithMessageImplEPKc, "ax", %progbits
.global _ZN2mg20abortWithMessageImplEPKc

_ZN2mg20abortWithMessageImplEPKc:
    mov r0, r0
    ldr r1, =0x69696969
    mov r2, #0x0
    str r1, [r2]
