#pragma once

#include "Patch/PatchBase.h"
#include <cstddef>
#include <vector>

struct AsmPatch : public PatchBase {
    const u32 mReplaceAddress;
    const u32 mAsmStart;
    const u32 mAsmEnd;

    void apply(std::vector<u8>& data) const;
};
