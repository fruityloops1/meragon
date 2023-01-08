.arm
.align 4

.macro SVC_BEGIN name
    .section .hk.init, "ax", %progbits
    .global \name
    .type \name, %function
    .align 2
    .cfi_startproc
\name:
.endm

.macro SVC_END
    .cfi_endproc
.endm

SVC_BEGIN _ZN2hk3sys11OpenProcessEPN2nn6HandleEj
	push {r0}
	svc 0x33
	pop {r2}
	str r1, [r2]
	bx  lr
SVC_END

SVC_BEGIN _ZN2hk3sys12GetProcessIdEPjN2nn6HandleE
	str r0, [sp, #-0x4]!
	svc 0x35
	ldr r3, [sp], #4
	str r1, [r3]
	bx  lr
SVC_END

SVC_BEGIN _ZN2hk3sys20ControlProcessMemoryEN2nn6HandleEjjjNS1_2os15MemoryOperationENS3_16MemoryPermissionE
	push {r4-r5}
	ldr r4, [sp, #0x8]
	ldr r5, [sp, #0xC]
	svc 0x70
	pop {r4-r5}
	bx  lr
SVC_END
