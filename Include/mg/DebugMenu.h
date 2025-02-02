#pragma once

#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/StageScene.h"
#include "al/Controller/ControllerUtil.h"
#include "sead/time/seadTickSpan.h"
#include <stdio.h>

namespace mg {

#define MG_ENABLE_DEBUG_MENU

class DebugMenu {
    enum Page {
        Page_Profiling,
        Page_ExecutorProfiling,
        Page_Info,
        Page_SceneInfo,
        Page_ActorViewer,
        Page_Options,
        Page_Player,
        Page_Misc,

        Page_Max
    };
    union {
        Page mPage;
        int mPageIndex;
    };
    const static int sMaxPages = Page_Max;
    const constexpr static char* cPages[] {
        "Profiling",
        "Executors",
        "Info",
        "Scene Info",
        "Actor Viewer",
        "Options",
        "Player",
        "Misc.",
    };
    constexpr static int cPagesMaxLines[] {
        2,
        3,
        1,
        5,
        3,
        6,
        6,
        2,
    };

    const constexpr static char* cPowerupNames[] { "Normal", "Mini", "Fire", "RaccoonDog", "Boomerang", "RaccoonDogSpecial", "RaccoonDogWhite", "Custom" };

    int mCursorPos = 0;
    int mPrintLine = 0;

    char16_t mWideBuffer[4096] { 0 };
    char mBuffer[4096] { 0 };
    int mCurBufferPos = 0;

    bool mTeleportEnabled = false;
    bool mAlwaysTanooki = true;
    bool mRestartHotkey = true;
    bool mEnableFreecam = false;
    bool mUnlockedFramerate = false;

    bool mHideMenu = false;
    sead::Vector3f mSavedPos { 0, 0, 0 };

    int mCurActorIndex = 0;
    int mButtonHoldFrames = 0;
    int mCurExecuteTable = 0;
    int mCurExecutorListIndex = 0;

    constexpr static int cNumFrameTimes = 14;
    sead::TickSpan mFrameTimes[cNumFrameTimes] {};
    int mCurFrameTimeIdx = 0;

    uintptr_t mCurrentPlayerActionVtablePtr = -1;

    void scrollIntWidget(int at, int* value)
    {
        cursor(at);
        if (mCursorPos == at) {
            if (al::isPadHoldLeft() || al::isPadHoldRight())
                mButtonHoldFrames++;
            else
                mButtonHoldFrames = 0;
            if (mButtonHoldFrames > 20)
                *value += al::isPadHoldRight() ? 1 : al::isPadHoldLeft() ? -1
                                                                         : 0;
            *value += al::isPadTriggerRight() ? 1 : al::isPadTriggerLeft() ? -1
                                                                           : 0;
        }
    }

public:
    static DebugMenu& instance();

    void setPlayerActionVtablePtr(uintptr_t ptr) { mCurrentPlayerActionVtablePtr = ptr; }

    void update(al::Scene* scene, al::LayoutActor* window);
    void collectFrameData();

    void cursor(int at)
    {
        print(mCursorPos == at ? ">" : "");
    }
    template <typename... Args>
    void print(const char* fmt, Args... args)
    {
        mCurBufferPos += snprintf(mBuffer + mCurBufferPos, sizeof(mBuffer) - mCurBufferPos, fmt, args...);
    }

    bool isHidden() const { return mHideMenu; }

    bool isFreecamEnabled() const { return mEnableFreecam; }
    bool isAlwaysTanooki() const { return mAlwaysTanooki; }
    bool isFramerateUnlocked() const { return mUnlockedFramerate; }

    constexpr static bool cEnabled =
#ifdef MG_ENABLE_DEBUG_MENU
        true
#else
        false
#endif
        ;
};

} // namespace mg

void playerActionGraphMoveHook(PlayerActionGraph* graph);
