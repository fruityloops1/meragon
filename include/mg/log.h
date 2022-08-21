#pragma once

extern "C" {
#include "3ds/svc.h"
}
#include <cstdio>

namespace mg {

template <typename... Args>
void log(const char* fmt, Args... args)
{
    size_t size = snprintf(nullptr, 0, fmt, args...);
    char data[size + 1];
    sprintf(data, fmt, args...);
    svcOutputDebugString(data, size);
}

} // namespace mg