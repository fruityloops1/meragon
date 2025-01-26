#pragma once

#include "hk/Types.h"

namespace nn::gr {

class FrameBuffer {
public:
    void* mData;
    u8 _8[0x38];
    int mWidth;
    int mHeight;
};

} // namespace nn::gr
