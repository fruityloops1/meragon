#pragma once

#include <new>
#include <stddef.h>

void* opNew(size_t size);
void* operator new(size_t size);