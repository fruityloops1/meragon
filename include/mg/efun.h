#pragma once

#include <stdint.h>

extern void* __addrMain;
extern void* __addrCode;
extern void* __addrCustomCode;
#define ADDR_MAIN ((uintptr_t)&__addrMain)
#define ADDR_CODE ((uintptr_t)&__addrCode)
#define ADDR_CUSTOM_CODE ((uintptr_t)&__addrCustomCode)

#define ARGS(...) __VA_ARGS__

#define EFUN(ADDR, RET, NAME, ARGS) \
    static const auto NAME = (RET(*const)(ARGS))(ADDR_MAIN + ADDR)