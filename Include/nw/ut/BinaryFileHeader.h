#pragma once

#include "hk/Types.h"

namespace nw::ut {

struct BinaryFileHeader {
    char magic[4];
    u16 bom;
    u16 headerLen;
    u32 version;
    u32 fileSize;
    u16 numSections;
};

bool IsValidBinaryFile(const nw::ut::BinaryFileHeader* header, u32 magic, u32 version, u16 numSectionsMin);

} // namespace nw::ut
