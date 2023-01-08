#pragma once

#include <nn/svc/svc_Api.h>
#include <stdio.h>
#include <string.h>

namespace hk::dbg {

inline void Log(const char* msg)
{
    nn::svc::OutputDebugString(msg, strlen(msg));
}

template <typename... Args>
void Log(const char* fmt, Args... args)
{
    size_t size = snprintf(nullptr, 0, fmt, args...);
    char data[size + 1];
    snprintf(data, size + 1, fmt, args...);
    nn::svc::OutputDebugString(data, size);
}

} // namespace hk::dbg
