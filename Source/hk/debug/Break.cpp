#include "hk/debug/Break.h"

namespace hk::dbg {

void Break(u32 dbgvalue1, u32 dbgvalue2)
{
    __asm("mov r12, r2");
    __asm("mov r11, r0");
    __asm("mov r0, #0x1");
    __asm("str r1, [r0, #0x0]");
    __asm("bx lr");
}

} // namespace hk::dbg
