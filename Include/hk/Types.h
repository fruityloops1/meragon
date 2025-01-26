#pragma once

#include <stdint.h>

using s8 = int8_t;
using u8 = uint8_t;
using s16 = int16_t;
using u16 = uint16_t;
using s32 = int32_t;
using u32 = uint32_t;
using s64 = int64_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

#define export __attribute__((section(".text.exported")))

inline u64 constexpr operator"" _ns(unsigned long long ns) { return ns; }
inline u64 constexpr operator"" _us(unsigned long long µs) { return µs * 1000; }
inline u64 constexpr operator"" _ms(unsigned long long ms) { return ms * 1000000; }
inline u64 constexpr operator"" _s(unsigned long long s) { return s * 1000000000; }
inline u64 constexpr operator"" _B(unsigned long long b) { return b; }
inline u64 constexpr operator"" _KB(unsigned long long kb) { return kb * 1024; }
inline u64 constexpr operator"" _MB(unsigned long long mb) { return mb * 1024_KB; }
inline u64 constexpr operator"" _GB(unsigned long long gb) { return gb * 1024_MB; }

#define CUR_THREAD_HANDLE 0xFFFF8000
#define CUR_PROCESS_HANDLE 0xFFFF8001

static inline void __dsb()
{
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c10, 4" ::[val] "r"(0) : "memory");
}

static inline void __dmb()
{
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c10, 5" ::[val] "r"(0) : "memory");
}

static inline void __isb()
{
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c5, 4" ::[val] "r"(0) : "memory");
}

static inline void __clrex()
{
    __asm__ __volatile__("clrex" ::: "memory");
}

/// Structure representing CPU registers
struct CpuRegisters {
    u32 r[13]; ///< r0-r12.
    u32 sp; ///< sp.
    u32 lr; ///< lr.
    u32 pc; ///< pc. May need to be adjusted.
    u32 cpsr; ///< cpsr.
};

/// Structure representing FPU registers
struct FpuRegisters {
    union {
        struct __attribute__((packed)) {
            double d[16];
        }; ///< d0-d15.
        float s[32]; ///< s0-s31.
    };
    u32 fpscr; ///< fpscr.
    u32 fpexc; ///< fpexc.
};

/// Types of errors that can be thrown by err:f.
enum ERRF_ErrType {
    ERRF_ERRTYPE_GENERIC = 0, ///< Generic fatal error. Shows miscellaneous info, including the address of the caller
    ERRF_ERRTYPE_NAND_DAMAGED = 1, ///< Damaged NAND (CC_ERROR after reading CSR)
    ERRF_ERRTYPE_CARD_REMOVED = 2, ///< Game content storage medium (cartridge and/or SD card) ejected. Not logged
    ERRF_ERRTYPE_EXCEPTION = 3, ///< CPU or VFP exception
    ERRF_ERRTYPE_FAILURE = 4, ///< Fatal error with a message instead of the caller's address
    ERRF_ERRTYPE_LOG_ONLY = 5, ///< Log-level failure. Does not display the exception and does not force the system to reboot
};

/// Types of 'Exceptions' thrown for ERRF_ERRTYPE_EXCEPTION
enum ERRF_ExceptionType {
    ERRF_EXCEPTION_PREFETCH_ABORT = 0, ///< Prefetch Abort
    ERRF_EXCEPTION_DATA_ABORT = 1, ///< Data abort
    ERRF_EXCEPTION_UNDEFINED = 2, ///< Undefined instruction
    ERRF_EXCEPTION_VFP = 3, ///< VFP (floating point) exception.
};

struct ERRF_ExceptionInfo {
    ERRF_ExceptionType type; ///< Type of the exception. One of the ERRF_EXCEPTION_* values.
    u8 reserved[3];
    u32 fsr; ///< ifsr (prefetch abort) / dfsr (data abort)
    u32 far; ///< pc = ifar (prefetch abort) / dfar (data abort)
    u32 fpexc;
    u32 fpinst;
    u32 fpinst2;
};

struct ERRF_ExceptionData {
    ERRF_ExceptionInfo excep; ///< Exception info struct
    CpuRegisters regs; ///< CPU register dump.
};

using ExceptionHandler = void (*)(ERRF_ExceptionInfo* excep, CpuRegisters* regs);

struct ThreadLocalStorage {
    u8 _0[0x40];
    ExceptionHandler exceptionHandler;
    void* stackTop;
    ERRF_ExceptionData* exceptionData;
    u8 _4C[0x34];
    u8 ipcCommandBuffer[0x100];
    u8 ipcReceiveBuffer[0x80];
};

static inline ThreadLocalStorage* getThreadLocalStorage()
{
    ThreadLocalStorage* ret;
    __asm__("mrc p15, 0, %[data], c13, c0, 3"
            : [data] "=r"(ret));
    return ret;
}

static inline u32* getThreadCommandBuffer(void)
{
    return (u32*)getThreadLocalStorage()->ipcCommandBuffer;
}

static inline u32* getThreadReceiveBuffer(void)
{
    return (u32*)getThreadLocalStorage()->ipcReceiveBuffer;
}

static inline void setThreadExceptionHandler(ExceptionHandler handler, void* stackTop, ERRF_ExceptionData* exceptionData)
{
    auto* tls = getThreadLocalStorage();

    tls->exceptionHandler = handler;
    tls->stackTop = stackTop;
    tls->exceptionData = exceptionData;

    __dsb();
    __isb();
}
