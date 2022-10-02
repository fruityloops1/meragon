#pragma once

#include "types.h"

namespace al {

enum class ByamlDataType : const u8 {
    Invalid = 0,
    String = 0xA0,
    Binary = 0xA1,
    Array = 0xC0,
    Hash = 0xC1,
    StringTable = 0xC2,
    BinaryTable = 0xC3,
    Bool = 0xD0,
    Int = 0xD1,
    Float = 0xD2,
    Null = 0xFF
};

class ByamlData {
    u32 mValue = 0; // should be a union
    ByamlDataType mType = ByamlDataType::Invalid;

public:
    ByamlData();
};

} // namespace al