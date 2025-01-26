#pragma once

#include "hk/debug/Log.h"
#include <stdio.h>

namespace mg {

void abortWithMessageImpl(const char* msg);
inline void abortWithMessage(const char* msg)
{
    hk::dbg::Log("mg::abortWithMessage: %s", msg);
    abortWithMessageImpl(msg);
}

template <typename... Args>
void abortWithMessage(const char* fmt, Args... args)
{
    int size = snprintf(nullptr, 0, fmt, args...);
    char buffer[size + 1];
    snprintf(buffer, size + 1, fmt, args...);
    abortWithMessage(buffer);
}

} // namespace mg
