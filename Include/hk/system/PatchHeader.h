#pragma once

#include "hk/Types.h"
#include <stddef.h>

namespace hk::sys {

// Information used by the ExheaderCli tool to apply hooks/patches
struct PatchHeader {
    size_t codeSize;
    void (*initFunc)(); // Hook function that will run in crt0
    uintptr_t textOffset; // .text of original game
    size_t textSize; // size of .text of original game
    uintptr_t rodataOffset; // .rodata of original game
    size_t rodataSize; // .rodata of .text of original game
};

volatile const extern PatchHeader sPatchHeader;

} // namespace hk::sys
