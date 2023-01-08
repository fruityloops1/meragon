#pragma once

#include "hk/hook/PatchBase.h"
#include <stddef.h>

namespace hk::hook {

class ReplacePatch : public PatchBase {
    const uintptr_t mReplaceAddress;
    const void* const mData;
    const size_t mDataSize;

public:
    constexpr ReplacePatch(uintptr_t replaceAddress, const void* data, size_t dataSize)
        : PatchBase(PatchType::Replace)
        , mReplaceAddress(replaceAddress)
        , mData(data)
        , mDataSize(dataSize)
    {
    }
};

#define HK_REPLACE_PATCH(NAME, ADDR, DATA, DATASIZE) \
    ::hk::hook::ReplacePatch __attribute__((section(".hk.hooks"))) NAME(ADDR, DATA, DATASIZE);

} // namespace hk::hook
