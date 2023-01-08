#pragma once

#include "hk/hook/ReplacePatch.h"
#include <stddef.h>

namespace hk::hook {

template <typename T>
class TypePatch : public ReplacePatch {
    const T mInst;

public:
    constexpr TypePatch(uintptr_t replaceAddress, const T& data)
        : mInst(data)
        , ReplacePatch(replaceAddress, &mInst, sizeof(T))
    {
    }
};

#define HK_TYPE_PATCH(NAME, ADDR, TYPE, INST) \
    ::hk::hook::TypePatch<TYPE> __attribute__((section(".hk.hooks"))) NAME(ADDR, INST);

// Tries to infer type automatically
#define HK_PATCH(NAME, ADDR, INST) \
    ::hk::hook::TypePatch __attribute__((section(".hk.hooks"))) NAME(ADDR, INST);

#define HK_PATCH_U8(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, u8, INST)
#define HK_PATCH_S8(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, s8, INST)
#define HK_PATCH_U16(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, u16, INST)
#define HK_PATCH_S16(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, s16, INST)
#define HK_PATCH_U32(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, u32, INST)
#define HK_PATCH_S32(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, s32, INST)
#define HK_PATCH_U64(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, u64, INST)
#define HK_PATCH_S64(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, s64, INST)

#define HK_PATCH_BYTE(NAME, ADDR, INST) HK_PATCH_U8(NAME, ADDR, INST)

#define HK_PATCH_STRINGPTR(NAME, ADDR, INST) HK_TYPE_PATCH(NAME, ADDR, const char*, INST)

#define HK_PATCH_STRING(NAME, ADDR, INST) HK_PATCH(NAME, ADDR, INST)

} // namespace hk::hook
