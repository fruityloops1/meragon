#pragma once

#include "hk/Types.h"

namespace hk::hook {

enum class PatchType : u8 {
    Replace,
    Assembly,
    Branch
};

class PatchBase {
    const PatchType mType;

protected:
    constexpr PatchBase(PatchType type)
        : mType(type)
    {
    }
};

} // namespace hk::hook
