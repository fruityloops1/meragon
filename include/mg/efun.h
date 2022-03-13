#pragma once

#include <stdint.h>

extern void* __addrMain;
#define MAIN_ADDR ((uintptr_t)&__addrMain)

#define ARGS(...) __VA_ARGS__

#define EFUN(ADDR, RET, NAME, ARGS) \
    static const auto NAME = (RET(*const)(ARGS))(MAIN_ADDR + ADDR)