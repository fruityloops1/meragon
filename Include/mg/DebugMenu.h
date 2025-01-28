#pragma once

#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/StageScene.h"
#include "sead/time/seadTickSpan.h"
#include <stdio.h>

namespace mg {

#define MG_ENABLE_DEBUG_MENU

class DebugMenu {
    enum Page {
        Page_Profiling,
        Page_Info,
        Page_SceneInfo,
        Page_ActorViewer,
        Page_Options,
        Page_Misc,

        Page_Max
    };
    union {
        Page mPage;
        int mPageIndex;
    };
    const static int sMaxPages = Page_Max;
    const constexpr static char* sPages[] {
        "Profiling",
        "Info",
        "Scene Info",
        "Actor Viewer",
        "Options",
        "Misc.",
    };
    constexpr static int sPagesMaxLines[] {
        2,
        1,
        5,
        3,
        6,
        6,
    };

    const constexpr static char* sPowerupNames[] { "Normal", "Mini", "Fire", "RaccoonDog", "Boomerang", "RaccoonDogSpecial", "RaccoonDogWhite" };

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

    constexpr static int cNumFrameTimes = 14;
    sead::TickSpan mFrameTimes[cNumFrameTimes] {};
    int mCurFrameTimeIdx = 0;

    uintptr_t mCurrentPlayerActionVtablePtr = -1;

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
