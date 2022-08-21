#pragma once

#include "sead/basis/seadTypes.h"

typedef u8 undefined;
typedef u16 undefined2;
typedef u32 undefined4;
typedef u64 undefined8;

#define sfill(SIZE, NAME) u8 _fill_##SIZE##_##NAME[SIZE];
#define export __attribute__((used))