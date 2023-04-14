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
#include "sead/prim/seadSafeString.h"
#include <stdio.h>

/*HK_PATCH_ASM(ClippingPatch, 0x002795c0, R"(
        ldr r1, [r0]
        ldr r1, [r1, #0x2c]
        bx r1
        )");*/

static constexpr u32 sMaxLives = 1110;

HK_PATCH_U32(MaxLives1, 0x00138c80, sMaxLives);
HK_PATCH_U32(MaxLives2, 0x001623b4, sMaxLives);
HK_PATCH_U32(MaxLives3, 0x001624bc, sMaxLives);
HK_PATCH_U32(MaxLives4, 0x0026c1e8, sMaxLives);
