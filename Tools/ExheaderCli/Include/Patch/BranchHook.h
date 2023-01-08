#pragma once

#include "Patch/PatchBase.h"
#include <stddef.h>

u32 makeBranch(u32 to, u32 at, u8 type);

struct BranchHook : public PatchBase {
    const u32 mReplaceAddress;
    const u32 mMemberFuncFiller;
    const u32 mFunc;
    const u8 mBranchType;

    void apply(std::vector<u8>& data) const;
};

#define HK_BRANCH_HOOK(NAME, ADDR, FUNC, TYPE) \
    ::hk::hook::BranchHook __attribute__((section(".hk.hooks"))) NAME(ADDR, FUNC, TYPE);
