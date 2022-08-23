#pragma once

extern "C" {
#include "3ds/svc.h"
}
#include <cstdio>

namespace mg {

template <typename... Args>
void log(const char* fmt, Args... args)
{
    size_t size = std::snprintf(nullptr, 0, fmt, args...);
    char data[size + 1];
    std::snprintf(data, size + 1, fmt, args...);
    svcOutputDebugString(data, size);
}

} // namespace mg