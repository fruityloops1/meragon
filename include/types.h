#pragma once

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef float f32;
typedef double f64;

typedef u8 undefined;
typedef u16 undefined2;
typedef u32 undefined4;
typedef u64 undefined8;

#define sfill(SIZE, NAME) u8 _fill_##SIZE##_##NAME[SIZE];