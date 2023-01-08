#pragma once

#include "types.h"

namespace nn {

struct Handle {
    u32 value;
    Handle()
        : value(0)
    {
    }
    Handle(u32 value)
        : value(value)
    {
    }
};

} // namespace nn
