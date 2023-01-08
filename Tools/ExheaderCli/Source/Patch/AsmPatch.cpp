#include "Patch/AsmPatch.h"
#include <cstring>

void AsmPatch::apply(std::vector<u8>& data) const
{
    printf("Patching %d bytes at 0x%.8x to data at 0x%.8x\n", mAsmEnd - mAsmStart, mReplaceAddress, mAsmStart);
    std::memcpy(&data[mReplaceAddress - sCodeStart], &data[mAsmStart - sCodeStart], mAsmEnd - mAsmStart);
}
