#pragma once

#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/StageScene.h"
#include <cstdio>
#include <mg/log.h>

namespace mg {

class DebugMenu {
    enum Page {
        Page_About,
        Page_Info,
        Page_SceneInfo,
        Page_ActorViewer,
        Page_Options
    };
    union {
        Page mPage;
        int mPageIndex;
    };
    const static int sMaxPages = 5;
    constexpr static const char* sPages[] { "About", "Info", "Scene Info", "Actor Viewer", "Options" };
    constexpr static int sPagesMaxLines[] { 1, 1, 1, 3, 2 };

    int mCursorPos = 0;
    int mPrintLine = 0;

    wchar_t mWideBuffer[512] { 0 };
    char mBuffer[512] { 0 };
    int mCurBufferPos = 0;

    bool mTeleportEnabled = false;

    bool mHideMenu = false;
    sead::Vector3f mSavedPos { 0, 0, 0 };

    int mCurActorIndex = 0;
    int mButtonHoldFrames = 0;

public:
    static DebugMenu& instance();

    void update(StageScene* scene, WindowConfirmSingle* window);

    void cursor(int at)
    {
        print(mCursorPos == at ? "-" : " ");
    }
    template <typename... Args>
    void print(const char* fmt, Args... args)
    {
        mCurBufferPos += std::snprintf(mBuffer + mCurBufferPos, sizeof(mBuffer) - mCurBufferPos, fmt, args...);
    }
};

} // namespace mg