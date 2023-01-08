#pragma once

#include "hk/hook/PatchBase.h"
#include <stddef.h>

namespace hk::hook {

class AsmPatch : public PatchBase {
    const uintptr_t mReplaceAddress;
    const u32* mAsmStart;
    const u32* mAsmEnd;

public:
    constexpr AsmPatch(uintptr_t replaceAddress, const u32* asmStart, const u32* asmEnd)
        : PatchBase(PatchType::Assembly)
        , mReplaceAddress(replaceAddress)
        , mAsmStart(asmStart)
        , mAsmEnd(asmEnd)
    {
    }
};

#define HK_PATCH_ASM(NAME, ADDR, ASSEMBLY)   \
    asm(".global __asm" #NAME "\n"           \
        "__asm" #NAME ":\n" ASSEMBLY);       \
    asm(".global __asm" #NAME "end\n"        \
        "__asm" #NAME "end:\nnop\n");        \
    extern "C" const u32 __asm##NAME[];      \
    extern "C" const u32 __asm##NAME##end[]; \
    ::hk::hook::AsmPatch __attribute__((section(".hk.hooks"))) NAME(ADDR, __asm##NAME, __asm##NAME##end);

} // namespace hk::hook
