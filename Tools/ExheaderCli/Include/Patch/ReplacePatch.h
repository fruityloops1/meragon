#pragma once

#include "Patch/PatchBase.h"
#include <cstddef>
#include <vector>

struct ReplacePatch : public PatchBase {
    const u32 mReplaceAddress;
    const u32 mData;
    const u32 mDataSize;

    void apply(std::vector<u8>& data) const;
};
