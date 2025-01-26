#include "Game/System/GameSystem.h"
#include "al/Memory/MemorySystem.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "nn/math/math_MTX44.h"
#include "nw/font/CharWriter.h"
#include "nw/font/DispStringBuffer.h"
#include "nw/font/Font.h"
#include "nw/font/TextWriterBase.h"
#include "sead/framework/ctr/seadDualScreenMethodMgr.h"
#include "sead/math/seadMatrix.h"

static nw::font::Font* getDebugFont()
{
    return al::getGameSystem()->getFontContainer()->findFontByName("MessageFont18.bcfnt");
}

static nw::font::DispStringBuffer* sDispStringBuffer = nullptr;
static u8 sShitBuffer[0xb300];

inline void MTX44PivotUp(nn::math::MTX44* out)
{
    constexpr f32 sin = -1.0f;
    constexpr f32 cos = 0.0f;

    f32(*m)[4] = out->m;

    if (sin == 0.0f) {
        m[0][0] = cos * m[0][0];
        m[0][1] = cos * m[0][1];
        m[0][2] = cos * m[0][2];
        m[0][3] = cos * m[0][3];

        m[1][0] = cos * m[1][0];
        m[1][1] = cos * m[1][1];
        m[1][2] = cos * m[1][2];
        m[1][3] = cos * m[1][3];
    } else {
        f32 tmp = m[0][0];
        m[0][0] = -sin * m[1][0];
        m[1][0] = sin * tmp;

        tmp = m[0][1];
        m[0][1] = -sin * m[1][1];
        m[1][1] = sin * tmp;

        tmp = m[0][2];
        m[0][2] = -sin * m[1][2];
        m[1][2] = sin * tmp;

        tmp = m[0][3];
        m[0][3] = -sin * m[1][3];
        m[1][3] = sin * tmp;
    }
}

inline void MTX44OrthoC(nn::math::MTX44* out, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    f32(*m)[4] = out->m;
    f32 tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(r + l) * tmp;

    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp;
    m[1][2] = 0.0f;
    m[1][3] = -(t + b) * tmp;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;

    tmp = 1.0f / (f - n);

    m[2][2] = tmp;
    m[2][3] = n * tmp;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

static void testDebugMenu(sead::DualScreenMethodTreeMgr* mgr)
{
    if (false)
        mgr->drawBtm();

    if (sDispStringBuffer == nullptr) {
        size_t size = nw::font::CharWriter::GetDispStringBufferSize(128);
        sDispStringBuffer = nw::font::CharWriter::InitDispStringBuffer(sShitBuffer, 128);
    }

    nw::font::TextWriterBase<wchar_t> textWriter;
    textWriter.SetFont(getDebugFont());
    textWriter.SetDispStringBuffer(sDispStringBuffer);
    textWriter.SetCursor2D(10, 10);
    textWriter.StartPrint();
    textWriter.Print(L"BALLS 123", 9);

    auto* drawer = al::getGameSystem()->getLayoutSystem()->getLayoutDrawer();
    drawer->BuildTextCommand(&textWriter);

    // drawer->DrawBegin();

    nn::math::MTX44 proj;
    MTX44OrthoC(&proj, 0, 320, 240, 0, 0.0f, -1.0f);
    MTX44PivotUp(&proj);
    // drawer->SetProjectionMtx(proj);
    // drawer->SetViewMtxForText(sead::Matrix34f::ident);

    // textWriter.UseCommandBuffer();

    // drawer->DrawEnd();
}

HK_BL_HOOK_FUNC(DebugMenuDraw, 0x001cf4f8, testDebugMenu)