#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "nn/gx/gx_Api.h"
#include "nn/svc/svc_Api.h"
#include "sead/gfx/seadGraphics.h"

static void noVBlank()
{
    nn::svc::SleepThread(50_us); // give time for loading threads to lock the mutex
    sead::Graphics::instance()->lockDrawContext();
    nngxSwapBuffers(0x402 /* Both */);
    sead::Graphics::instance()->unlockDrawContext();
}

// HK_B_HOOK_FUNC(DontWaitVBlank, 0x001cee50, noVBlank)
//  HK_PATCH_ASM(shit, 0x001cef38, "mov r1, #1");