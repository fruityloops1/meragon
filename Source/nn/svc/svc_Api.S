.arm
.align 4

.macro SVC_BEGIN name
    .section .text.\name, "ax", %progbits
    .global \name
    .type \name, %function
    .align 2
    .cfi_startproc
\name:
.endm

.macro SVC_END
    .cfi_endproc
.endm


SVC_BEGIN _ZN2nn3svc11QueryMemoryEPNS_2os7MemInfoEPNS1_8PageInfoEj
	push {r0, r1, r4-r6}
	svc  0x02
	ldr  r6, [sp]
	str  r1, [r6]
	str  r2, [r6, #4]
	str  r3, [r6, #8]
	str  r4, [r6, #0xc]
	ldr  r6, [sp, #4]
	str  r5, [r6]
	add  sp, sp, #8
	pop  {r4-r6}
	bx   lr
SVC_END

SVC_BEGIN _ZN2nn3svc11SleepThreadEy
	svc 0xA
	bx lr
SVC_END

SVC_BEGIN _ZN2nn3svc17CreateMemoryBlockEPNS_6HandleEjjjj
	str r0, [sp, #-4]!
	ldr r0, [sp, #4]
	svc 0x1E
	ldr r2, [sp], #4
	str r1, [r2]
	bx  lr
SVC_END

SVC_BEGIN _ZN2nn3svc13GetSystemTickEv
	svc 0x28
	bx  lr
SVC_END

SVC_BEGIN _ZN2nn3svc15SendSyncRequestENS_6HandleE
	svc 0x32
	bx lr
SVC_END

SVC_BEGIN _ZN2nn3svc11OpenProcessEPNS_6HandleEj
	push {r0}
	svc 0x33
	pop {r2}
	str r1, [r2]
	bx  lr
SVC_END

SVC_BEGIN _ZN2nn3svc12GetProcessIdEPjNS_6HandleE
	str r0, [sp, #-0x4]!
	svc 0x35
	ldr r3, [sp], #4
	str r1, [r3]
	bx  lr
SVC_END

SVC_BEGIN _ZN2nn3svc17OutputDebugStringEPKvi
    svc 0x3d
    bx lr
SVC_END

SVC_BEGIN _ZN2nn3svc21FlushProcessDataCacheENS_6HandleEjj
	svc 0x54
	bx  lr
SVC_END

SVC_BEGIN _ZN2nn3svc20ControlProcessMemoryENS_6HandleEjjjNS_2os15MemoryOperationENS2_16MemoryPermissionE
	push {r4-r5}
	ldr r4, [sp, #0x8]
	ldr r5, [sp, #0xC]
	svc 0x70
	pop {r4-r5}
	bx  lr
SVC_END
