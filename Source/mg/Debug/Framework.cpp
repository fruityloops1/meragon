#include "mg/Debug/Framework.h"
#include "al/System/GameFrameworkCtrNw4c.h"
#include "hk/hook/TypePatch.h"
#include "nn/svc/svc_Api.h"

static bool sDoSuspendFramework = false;

void mg::suspendFramework()
{
    sDoSuspendFramework = true;
    nn::svc::SleepThread(200_ms); // could use a mutex for this, but it wouldn't work if the main thread crashed
}

static void frameworkProcFrameHook(al::GameFrameworkCtrNw4c* framework)
{
    if (sDoSuspendFramework) {
        while (true)
            nn::svc::SleepThread(60_s);
    }

    framework->al::GameFrameworkCtrNw4c::procFrame_();
}

constexpr auto frameworkProcFrameHookVftPtr = frameworkProcFrameHook;
HK_PATCH(FrameworkProcFrame, 0x003d6780, &frameworkProcFrameHook)
