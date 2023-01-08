#include "Game/Player/PlayerActionGraph.h"
#include "al/Factory/ActorFactory.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "mg/DebugMenu.h"
#include "mg/Factory/ActorFactory.h"
#include "mg/ProductSequenceMod.h"

/*HK_PATCH_ASM(ClippingPatch, 0x002795c0, R"(
        ldr r1, [r0]
        ldr r1, [r1, #0x2c]
        bx r1
        )");*/
