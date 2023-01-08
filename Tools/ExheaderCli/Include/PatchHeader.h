#pragma once

#include "Types.h"

struct PatchHeader {
    u32 codeSize;
    u32 initFunc;
    u32 textOffset;
    u32 textSize;
    u32 rodataOffset;
    u32 rodataSize;
};
