#pragma once

#include "hk/Types.h"
#include "nn/math/math_VEC3.h"
#include "nw/font/DispStringBuffer.h"
#include "nw/font/Font.h"
#include <sead/basis/seadNew.h>

namespace nw::font {

class CharWriter {
    u8 _0[0x2c];
    nn::math::VEC3 mCursorPos;
    f32 _38;
    Font* mFont = nullptr;
    void* _40;
    DispStringBuffer* mDispStringBuffer;
    u8 _48[0x4];

public:
    void StartPrint();

    void SetCursor2D(float x, float y)
    {
        mCursorPos.x = x;
        mCursorPos.y = y;
    }

    static u32 GetDispStringBufferSize(u32 charBufferSize);
    static DispStringBuffer* InitDispStringBuffer(void* buffer, u32 charNum)
    {
        return new (buffer) DispStringBuffer(charNum);
    }

    void SetFont(Font* font) { mFont = font; }
    void SetDispStringBuffer(DispStringBuffer* buffer) { mDispStringBuffer = buffer; }

    void UseCommandBuffer();
};

} // namespace nw::font
