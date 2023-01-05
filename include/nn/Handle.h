#pragma once

#include "types.h"

namespace nn {

struct Handle {
    u32 value;

    Handle()
        : value(0)
    {
    }

    Handle(int value)
        : value(value)
    {
    }
};

} // namespace nn
