#include "mem.h"

void* opNew(size_t size);
void* operator new(size_t size)
{
    return opNew(size);
}