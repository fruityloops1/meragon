#pragma once

#include "Types.h"
#include <string>
#include <vector>

enum class PatchType : u8 {
    Replace,
    Assembly,
    Branch
};

struct PatchBase {
    const PatchType mType;
};

std::vector<const PatchBase*> collectPatchesFromMap(const std::vector<u8>& data, const std::string& mapFile);
