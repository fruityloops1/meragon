#pragma once

namespace nn::math {

struct MTX44 {
    union {
        float m[4][4];
        float a[16];
    };
};

} // namespace nn::math
