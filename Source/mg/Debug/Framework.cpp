#include "mg/Debug/Framework.h"
#include "al/System/GameFrameworkCtrNw4c.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/Debug/Clock.h"
#include "mg/DebugMenu.h"
#include "nn/gx/gx_Api.h"
#include "nn/svc/svc_Api.h"
#include "sead/gfx/seadGraphics.h"

static bool sDoSuspendFramework = false;

void mg::suspendFramework()
{
    sDoSuspendFramework = true;
    nn::svc::SleepThread(200_ms); // could use a mutex for this, but it wouldn't work if the main thread crashed
}

#ifdef MG_ENABLE_DEBUG_MENU
static mg::ProfilingData sProfilingData;
mg::ProfilingData& mg::getProfilingData()
{
    return sProfilingData;
}
#endif

static void frameworkProcFrameHook(al::GameFrameworkCtrNw4c* framework)
{
    if (sDoSuspendFramework) {
        while (true)
            nn::svc::SleepThread(60_s);
    }

    framework->al::GameFrameworkCtrNw4c::procFrame_();

#ifdef MG_ENABLE_DEBUG_MENU
    sProfilingData.lastFrame = sProfilingData.curFrame;
    sProfilingData.curFrame = nn::svc::GetSystemTick();
#endif
}

HK_PATCH(FrameworkProcFrame, 0x003d6780, &frameworkProcFrameHook)

#ifdef MG_ENABLE_DEBUG_MENU

static void waitVBlank(al::GameFrameworkCtrNw4c* framework)
{
    hk::util::Clock<"WaitVBlank"> clock;
    clock.start();

    if (mg::DebugMenu::instance().isFramerateUnlocked()) {
        nn::svc::SleepThread(10_us); // give time for loading threads to lock the mutex
        sead::Graphics::instance()->lockDrawContext();
        nngxSwapBuffers(0x402 /* Both */);
        sead::Graphics::instance()->unlockDrawContext();
    } else
        framework->GameFrameworkCtrNw4c::waitForVBlank_();

    sProfilingData.vblank = clock.count();
}

HK_PATCH(WaitVBlank, 0x003d67a0, &waitVBlank)

static void frameworkProcDrawHook(al::GameFrameworkCtrNw4c* framework)
{
    hk::util::Clock<"Draw"> clock;
    clock.start();

    framework->al::GameFrameworkCtrNw4c::procDraw_();

    sProfilingData.draw = clock.count();
}

HK_PATCH(FrameworkDraw, 0x003d6784, &frameworkProcDrawHook)

static void frameworkProcCalcHook(al::GameFrameworkCtrNw4c* framework)
{
    hk::util::Clock<"Calc"> clock;
    clock.start();

    framework->al::GameFrameworkCtrNw4c::procCalc_();

    sProfilingData.calc = clock.count();
}

HK_PATCH(FrameworkCalc, 0x003d6788, &frameworkProcCalcHook)

#endif
