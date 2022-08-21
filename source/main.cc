#include "mg/factory.h"
#include "mg/log.h"
#include "sead/heap/seadNew.h"

void mMain()
{
    mg::log("mMain");
}

void* operator new(size_t size)
{
    return opNew(size);
}