#include "Game/Layout/CounterMarioUtil.h"
#include "Game/Player/PlayerActionGraph.h"
#include "al/Factory/ActorFactory.h"
#include "al/Util/StringUtil.h"
#include "hk/debug/Log.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/DebugMenu.h"
#include "mg/Factory/ActorFactory.h"
#include "mg/ProductSequenceMod.h"
#include <stdio.h>

/*HK_PATCH_ASM(ClippingPatch, 0x002795c0, R"(
        ldr r1, [r0]
        ldr r1, [r1, #0x2c]
        bx r1
        )");*/

static constexpr u32 sMaxLives = 6;

HK_PATCH_U32(MaxLives1, 0x00138c80, sMaxLives);
HK_PATCH_U32(MaxLives2, 0x001623b4, sMaxLives);
HK_PATCH_U32(MaxLives3, 0x001624bc, sMaxLives);
HK_PATCH_U32(MaxLives4, 0x0026c1e8, sMaxLives);
HK_PATCH_U32(MaxLives5, 0x00138ccc, sMaxLives);
HK_PATCH_U32(MaxLives6, 0x003201f4, sMaxLives);

static void formatMarioCounter(al::LayoutActor* actor, const char* paneName, int numLife, int playerChar)
{
    if (playerChar == -1)
        playerChar = rp::getPlayerPictureFontIcon();

    // clang-format off
    if (numLife < sMaxLives)
        al::setPaneString(actor, paneName, al::WStringTmp<6>(u"%c%c%d", playerChar, u'@', numLife).cstr());
    else
        al::setPaneString(actor, paneName, al::WStringTmp<6>(u"%c%c%c", playerChar, u'@', u':').cstr());
    // clang-format on
}

HK_B_HOOK_FUNC(FormatMarioCounter, 0x0026c3d4, formatMarioCounter)