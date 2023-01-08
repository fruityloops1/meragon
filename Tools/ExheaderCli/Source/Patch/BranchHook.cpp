#include "Patch/BranchHook.h"
#include "Types.h"

u32 makeBranch(u32 to, u32 at, u8 type)
{
    union {
        struct {
            signed int relAddr : 24;
            u8 type : 8;
        };
        u32 data;
    } conv { static_cast<signed int>((to - at - 8) / 4), type };
    return conv.data;
}

void BranchHook::apply(std::vector<u8>& data) const
{
    printf("Placing branch hook to 0x%.8x with type 0x%x at 0x%.8x\n", mFunc, mBranchType, mReplaceAddress);
    *reinterpret_cast<u32*>(&data[mReplaceAddress - sCodeStart]) = makeBranch(mFunc, mReplaceAddress, mBranchType);
}
