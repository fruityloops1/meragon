#pragma once

namespace nn::math {

struct MTX34 {
    union {
        float m[3][4];
        float a[12];
    };
};

} // namespace nn::math
