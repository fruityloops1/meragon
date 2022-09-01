#pragma once

#include "mg/log.h"

namespace mg {

template <typename... Args>
void assert(bool condition, const char* fmt, Args... args)
{
    if (!condition) {
        mg::log(fmt, args...);
        svcBreak(UserBreakType::USERBREAK_ASSERT);
        *(int*)0x69 = 0x420;
        __builtin_unreachable();
    }
}

} // namespace mg