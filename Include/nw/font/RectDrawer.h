#pragma once

#include "nn/math/math_MTX34.h"
#include "nn/math/math_MTX44.h"
#include "nw/font/CharWriter.h"

namespace nw::font {

class RectDrawer {
public:
    void BuildTextCommand(CharWriter* writer);
    void DrawBegin(u32 flags = 0);
    void DrawEnd(u32 flags = 0);
    void SetProjectionMtx(const nn::math::MTX44& mtx);
    void SetViewMtxForText(const nn::math::MTX34& mtx);
};

} // namespace nw::font
