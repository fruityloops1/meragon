#include "mg/hooks.h"
#include "mg/log.h"

#include "mem.h"

void mMain()
{
    mg::initHooks();
}

void* opNew(size_t size);
void* operator new(size_t size)
{
    return opNew(size);
}