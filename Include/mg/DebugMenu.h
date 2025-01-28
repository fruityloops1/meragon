#pragma once

#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/StageScene.h"
#include <stdio.h>

namespace mg {

#define MG_ENABLE_DEBUG_MENU

class DebugMenu {
    enum Page {
        Page_About,
        Page_Info,
        Page_Misc,
        Page_SceneInfo,
        Page_ActorViewer,
        Page_Options
    };
    union {
        Page mPage;
        int mPageIndex;
    };
    const static int sMaxPages = 6;
    const constexpr static char* sPages[] { "About", "Info", "Misc.", "Scene Info", "Actor Viewer", "Options" };
    constexpr static int sPagesMaxLines[] { 1, 1, 6, 5, 3, 6 };

    const constexpr static char* sPowerupNames[] { "Normal", "Mini", "Fire", "RaccoonDog", "Boomerang", "RaccoonDogSpecial", "RaccoonDogWhite" };

    int mCursorPos = 0;
    int mPrintLine = 0;

    char16_t mWideBuffer[512] { 0 };
    char mBuffer[512] { 0 };
    int mCurBufferPos = 0;

    bool mTeleportEnabled = false;
    bool mAlwaysTanooki = true;
    bool mRestartHotkey = true;
    bool mEnableFreecam = false;

    bool mHideMenu = false;
    sead::Vector3f mSavedPos { 0, 0, 0 };

    int mCurActorIndex = 0;
    int mButtonHoldFrames = 0;

    uintptr_t mCurrentPlayerActionVtablePtr = -1;

public:
    static DebugMenu& instance();

    void setPlayerActionVtablePtr(uintptr_t ptr) { mCurrentPlayerActionVtablePtr = ptr; }

    void update(al::Scene* scene, al::LayoutActor* window);

    void cursor(int at)
    {
        print(mCursorPos == at ? "-" : " ");
    }
    template <typename... Args>
    void print(const char* fmt, Args... args)
    {
        mCurBufferPos += snprintf(mBuffer + mCurBufferPos, sizeof(mBuffer) - mCurBufferPos, fmt, args...);
    }

    bool isFreecamEnabled() const { return mEnableFreecam; }
    bool isAlwaysTanooki() const { return mAlwaysTanooki; }
};

} // namespace mg

void playerActionGraphMoveHook(PlayerActionGraph* graph);
