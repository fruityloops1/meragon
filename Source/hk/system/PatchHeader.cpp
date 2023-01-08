#include "hk/system/PatchHeader.h"
#include "hk/system/Init.h"

namespace hk::sys {

volatile const PatchHeader __attribute__((section(".hk.header"))) sPatchHeader {
    .codeSize = 0 /* will be changed */,
    .initFunc = &hk::sys::Initialize
};

} // namespace hk::sys
