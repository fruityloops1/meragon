#include "Patch/ReplacePatch.h"
#include "Types.h"
#include <cstdio>
#include <cstring>

void ReplacePatch::apply(std::vector<u8>& data) const
{
    printf("Patching %d bytes at 0x%.8x to data at 0x%.8x\n", mDataSize, mReplaceAddress, mData);
    std::memcpy(&data[mReplaceAddress - sCodeStart], &data[mData - sCodeStart], mDataSize);
}
