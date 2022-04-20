#include "mg/factory.h"
#include "mg/log.h"

void removeClippingHook(void* info, float* radius, const char* property)
{
    *radius = 9999999;
}