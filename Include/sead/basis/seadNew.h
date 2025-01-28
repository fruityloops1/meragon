#pragma once

#include <stddef.h>

void* opNew(size_t size);
void* operator new(size_t size);
void* operator new(size_t size, void*);
void operator delete(void* ptr);
inline void* operator new(size_t size, void* ptr) { return ptr; }