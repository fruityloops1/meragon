#include "mg/DebugMenu.h"
#include "Game/Player/PlayerAnimator.h"
#include "Game/Player/PlayerFigureDirector.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Controller/ControllerUtil.h"
#include "al/Layout/LayoutActor.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveKeeper.h"
#include "al/Scene/SceneStopCtrl.h"
#include "hk/debug/Log.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "mg/Debug/Clock.h"
#include "mg/Debug/Framework.h"
#include "mg/MapObj/GreenDemon.h"
#include "mg/Util/StringTranslation.h"
#include "mg/Util/StringUtil.h"
#include "sead/controller/seadController.h"
#include "sead/controller/seadControllerBase.h"
#include "sead/framework/seadTaskID.h"
#include "sead/time/seadTickSpan.h"
#include <Game/Player/Player.h>
#include <stdio.h>
#include <string.h>

mg::DebugMenu sInstance;
mg::DebugMenu& mg::DebugMenu::instance()
{
    return sInstance;
}

struct VtableEntry {
    uintptr_t addr;
    const char* name;
};

struct Dings {
    float attribut;
};

void penis2(float* penisse)
{
    // penisse[]
}

void arsch()
{
    // penis2(penis);
}

static constexpr VtableEntry actions[] {
    { 0x003cc450, "Wait" },
    { 0x003d045c, "GroundMove" },
    { 0x003cd920, "Turn" },
    { 0x003cd8ec, "Brake" },
    { 0x003cfc20, "Rolling" },
    { 0x003cfc64, "Squat" },
    { 0x003cf1ac, "SquatStandUp" },
    { 0x003cd954, "SquatSlide" },
    { 0x003ce948, "Bonk" },
    { 0x003cc2bc, "somethingidfk" },
    { 0x003cc37c, "AirMove" },
    { 0x003cf24c, "TurnJump" },
    { 0x003d08d8, "TrampleJump" },
    { 0x003cf0b0, "TrampolineJump" },
    { 0x003cc344, "Fall" },
    { 0x003cc3b4, "Land" },
    { 0x003ce8d0, "HipDrop" },
    { 0x003cf120, "LongJump" },
    { 0x003ce914, "?(longjump)" },
    { 0x003d0f34, "LongJumpRolling" },
    { 0x003cc474, "WallSlide" },
    { 0x003cf2a8, "WallJump" },
    { 0x003cfbc4, "DieOver" },
    { 0x003cd8c8, "Abyss" },
    { 0x003cc2bc, "PlayAnim" },
};

static constexpr VtableEntry executorListVtables[] {
    { 0x003d74b0, "ActorCalcAnim" },
    { 0x003d75e0, "ActorExecuteBase" },
    { 0x003d74cc, "ActorMovement" },
    { 0x003d789c, "ActorMovementCalcAnim" },
    { 0x003d741c, "LayoutUpdate" },
    { 0x003d7620, "Execute" },
    { 0x003d6ef4, "Functor" },
    { 0x003d78dc, "ExecutorListActorModelDrawCache" },
    { 0x003d7850, "ExecutorListActorModelDraw" },
};

static bool sEnableLayoutSkip = true;

// makes death go fast
bool layoutSkipHook1(const al::IUseNerve* p) { return sEnableLayoutSkip ? true : al::isGreaterStep(p, 35); }
bool layoutSkipHook2(const al::LayoutActor* layout) { return sEnableLayoutSkip ? true : al::isActionEnd(layout); }
HK_BL_HOOK(LayoutSkipHook1, 0x001226e4, layoutSkipHook1);
HK_BL_HOOK(LayoutSkipHook2, 0x00361748, layoutSkipHook2);

void mg::DebugMenu::update(al::Scene* scene, al::LayoutActor* window)
{
    StageScene* stageScene = nullptr;
    if (scene && *(uintptr_t*)scene == 0x003c52c8)
        stageScene = static_cast<StageScene*>(scene);

    if (stageScene && mAlwaysTanooki && stageScene->mPlayerActor->mPlayer->mFigureDirector->getFigure() != EPlayerFigure_RaccoonDog)
        stageScene->mPlayerActor->mPlayer->mFigureDirector->change(EPlayerFigure_RaccoonDog);
    if (mRestartHotkey && al::isPadHoldR() && al::isPadHoldL() && al::isPadTriggerRight())
        al::setNerve(scene, (const al::Nerve*)0x003f1054 /* mario is die */);

    if (al::isPadTriggerLeft() && al::isPadHoldR()) {
        mHideMenu = !mHideMenu;
        if (!mHideMenu)
            window->appear();
        return;
    }
    if (mHideMenu) {
        window->kill();

        if (mTeleportEnabled && stageScene) {

            if (al::isPadTriggerDown())
                mSavedPos = al::getTrans(stageScene->mPlayerActor);
            if (al::isPadTriggerUp())
                stageScene->mPlayerActor->mPlayer->getProperty()->mTrans = mSavedPos;
        }
        return;
    }
    mCurBufferPos = 0;
    mBuffer[0] = '\0';

    if (al::isPadTriggerDown())
        mCursorPos++;
    if (al::isPadTriggerUp())
        mCursorPos--;
    if (mCursorPos < 0)
        mCursorPos = 0;
    if (mCursorPos >= sPagesMaxLines[mPageIndex])
        mCursorPos = sPagesMaxLines[mPageIndex] - 1;

    cursor(0);
    print("%s (%d/%d)\n", sPages[mPageIndex], mPageIndex + 1, sMaxPages);
    if (mCursorPos == 0) {
        if (al::isPadTriggerRight())
            mPageIndex++;
        if (al::isPadTriggerLeft())
            mPageIndex--;
        if (mPageIndex >= sMaxPages)
            mPageIndex = sMaxPages - 1;
        if (mPageIndex < 0)
            mPageIndex = 0;
    }

    switch (mPage) {

    case Page_Profiling: {
        print("Meragon Debug Menu\n------------------\n");

        cursor(1);
        print("Unlock FPS: %s\n", mUnlockedFramerate ? "Yes" : "No");
        if (mCursorPos == 1 && (al::isPadTriggerRight() || al::isPadTriggerLeft()))
            mUnlockedFramerate = !mUnlockedFramerate;
        print("------------------\n");

        char formatted[16];
        auto data = getProfilingData();

        mFrameTimes[mCurFrameTimeIdx++] = data.curFrame - data.lastFrame;
        if (mCurFrameTimeIdx == cNumFrameTimes)
            mCurFrameTimeIdx = 0;

        sead::TickSpan avg = 0;
        for (int i = 0; i < cNumFrameTimes; i++) {
            avg += mFrameTimes[i];
        }
        avg /= float(cNumFrameTimes);

        print("FPS: %2.2f\n", 0.99f / avg.toSeconds<float>());
        hk::util::formatTickSpan(formatted, data.calc + data.draw);
        print("Frame: %s\n", formatted);
        hk::util::formatTickSpan(formatted, data.calc);
        print("Calc: %s\n", formatted);
        hk::util::formatTickSpan(formatted, data.draw);
        print("Draw: %s\n", formatted);
        hk::util::formatTickSpan(formatted, data.vblank);
        print("VBlank: %s\n", formatted);

        break;
    }

    case Page_ExecutorProfiling: {
        auto& p = getProfilingData();
        char formatted[16];
        if (scene == nullptr)
            break;
        al::LiveActorKit* kit = scene->mLiveActorKit;
        if (kit == nullptr)
            break;
        al::ExecuteDirector* director = kit->getExecuteDirector();
        if (director == nullptr)
            break;

        scrollIntWidget(1, &mCurExecuteTable);
        if (mCurExecuteTable < 0)
            mCurExecuteTable = 0;
        if (mCurExecuteTable >= director->getNumDrawTables() + 1)
            mCurExecuteTable = director->getNumDrawTables();
        p.curExecuteTable = mCurExecuteTable;

        int numExecutorLists;
        al::ExecutorListBase** executorLists;
        sead::TickSpan tableElapsed;

        if (mCurExecuteTable == 0) {
            al::ExecuteTableHolderUpdate* table = director->getUpdateTable();
            print("Current Table: Update\n");
            numExecutorLists = table->mNumExecutorLists;
            executorLists = table->mExecutorLists;
            tableElapsed = p.executeUpdateTable;
        } else {
            int drawTableIdx = mCurExecuteTable - 1;
            al::ExecuteTableHolderDraw* table = director->getDrawTable(drawTableIdx);

            numExecutorLists = table->mNumExecutorLists;
            executorLists = table->mExecutorLists;
            tableElapsed = p.executeDrawTable[drawTableIdx];

            const char* translated = tryTranslateString(table->mName);
            print("Current Table: Draw %s/\nDraw %s\n", table->mName, translated);
        }

        hk::util::formatTickSpan(formatted, tableElapsed);
        print("Table Time: %s\n---------------------\n", formatted);

        print("Num Executor Lists: %d\n", numExecutorLists);

        if (numExecutorLists == 0)
            break;

        scrollIntWidget(2, &mCurExecutorListIndex);
        if (mCurExecutorListIndex < 0)
            mCurExecutorListIndex = 0;
        if (mCurExecutorListIndex >= numExecutorLists)
            mCurExecutorListIndex = numExecutorLists - 1;

        print("List index: %d\n", mCurExecutorListIndex);

        al::ExecutorListBase* list = executorLists[mCurExecutorListIndex];

        if (list == nullptr)
            break;
        print("Name: %s\n", list->getName());
        const char* translated = tryTranslateString(list->getName());
        if (translated)
            print("Translated: %s\n", translated);

        const char* listClassName = nullptr;
        for (auto entry : executorListVtables)
            if (entry.addr == *(uintptr_t*)list)
                listClassName = entry.name;

        if (listClassName)
            print("Class: %s\n", listClassName);
        else
            print("vtable: %p\n", *(uintptr_t*)list);
        hk::util::formatTickSpan(formatted, p.executeTableLists[mCurExecutorListIndex]);
        print("Time: %s\n", formatted);

        break;
    }

    case Page_Info: {
        if (stageScene) {
            const sead::Vector3f& trans = al::getTrans(stageScene->mPlayerActor);
            const sead::Vector3f& rot = al::getRotate(stageScene->mPlayerActor);
            const sead::Vector3f& vel = al::getVelocity(stageScene->mPlayerActor);
            print("Trans %.2f %.2f %.2f\n", trans.x, trans.y, trans.z);
            print("Rot %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
            print("Vel %.2f %.2f %.2f\n", vel.x, vel.y, vel.z);

            const char* actionName = nullptr;
            for (auto entry : actions)
                if (entry.addr == mCurrentPlayerActionVtablePtr)
                    actionName = entry.name;

            if (actionName) {
                print("Action: PlayerAction%s\n", actionName);
                hk::dbg::Log("Action: PlayerAction%s", actionName);
            } else {
                print("Action: 0x%.8x\n", mCurrentPlayerActionVtablePtr);
                hk::dbg::Log("Action: 0x%.8x", mCurrentPlayerActionVtablePtr);
            }
        }
        break;
    }

    case Page_SceneInfo: {
        if (scene == nullptr)
            break;
        sead::PtrArray<al::LiveActor> actors = scene->mLiveActorKit->getAllActors()->getArray<al::LiveActor>();

        cursor(1);
        print("Kill Scene\n");
        if (mCursorPos == 1 && al::isPadTriggerRight())
            scene->kill();

        cursor(2);
        print("Restart Scene\n");
        if (mCursorPos == 2 && al::isPadTriggerRight())
            al::setNerve(scene, (const al::Nerve*)0x003f1054 /* mario is die */);

        cursor(3);
        print("Fast restart: %s\n", sEnableLayoutSkip ? "Yes" : "No");
        if (mCursorPos == 3 && (al::isPadTriggerRight() || al::isPadTriggerLeft())) {
            sEnableLayoutSkip = !sEnableLayoutSkip;
        }

        cursor(4);
        print("Stop scene 60f\n");
        if (mCursorPos == 4 && (al::isPadTriggerRight() || al::isPadTriggerLeft())) {
            al::stopScene(60);
        }

        print("Actors: %d\n", actors.capacity());
        int alive = 0;
        int nonClipped = 0;
        for (int i = 0; i < actors.capacity(); i++)
            if (actors[i] && al::isAlive(actors[i]))
                alive++;

        for (int i = 0; i < actors.capacity(); i++)
            if (actors[i] && !actors[i]->getLiveActorFlag().isClipped && al::isAlive(actors[i]))
                nonClipped++;

        print("Actors Alive: %d\n", alive);
        print("Actors Unclipped: %d\n", nonClipped);
        break;
    }

    case Page_ActorViewer: {
        if (scene == nullptr)
            break;
        sead::PtrArray<al::LiveActor> actors = scene->mLiveActorKit->getAllActors()->getArray<al::LiveActor>();

        scrollIntWidget(1, &mCurActorIndex);
        if (mCurActorIndex >= actors.capacity())
            mCurActorIndex = actors.capacity() - 1;
        if (mCurActorIndex < 0)
            mCurActorIndex = 0;
        print("Actor index: %d\n", mCurActorIndex);

        al::LiveActor* actor = actors[mCurActorIndex];
        if (actor) {
            print("Name: %s\n", actor->getName() == nullptr ? "null" : actor->getName());
            cursor(2);
            if (actor->getActorPoseKeeper()) {
                const sead::Vector3f& trans = al::getTrans(actor);
                const sead::Vector3f& rot = al::getRotate(actor);
                const sead::Vector3f& vel = al::getVelocity(actor);

                if (stageScene) {
                    print("Teleport to\n");
                    if (mCursorPos == 2 && al::isPadTriggerRight())
                        stageScene->mPlayerActor->mPlayer->getProperty()->mTrans = trans;
                }
                print("Trans %.2f %.2f %.2f\n", trans.x, trans.y, trans.z);
                print("Rot %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
                print("Vel %.2f %.2f %.2f\n", vel.x, vel.y, vel.z);
            } else
                print("\n");
        }
        break;
    }

    case Page_Options: {
        cursor(1);
        print("Enable Teleport: %s\n", mTeleportEnabled ? "Yes" : "No");
        if (mCursorPos == 1 && (al::isPadTriggerRight() || al::isPadTriggerLeft()))
            mTeleportEnabled = !mTeleportEnabled;

        cursor(2);
        print("State Test\n");
        if (mCursorPos == 2 && al::isPadTriggerRight() && stageScene)
            stageScene->mPlayerActor->mPlayer->mFigureDirector->change((EPlayerFigure)7);

        cursor(3);
        print("Always Tanooki: %s\n", mAlwaysTanooki ? "Yes" : "No");
        if (mCursorPos == 3 && (al::isPadTriggerRight() || al::isPadTriggerLeft()))
            mAlwaysTanooki = !mAlwaysTanooki;

        cursor(4);
        print("L+R+DRight to Restart: %s\n", mRestartHotkey ? "Yes" : "No");
        if (mCursorPos == 4 && (al::isPadTriggerRight() || al::isPadTriggerLeft()))

            mRestartHotkey = !mRestartHotkey;
        cursor(5);
        print("Enable Freecam: %s\n", mEnableFreecam ? "Yes" : "No");
        if (mCursorPos == 5 && (al::isPadTriggerRight() || al::isPadTriggerLeft()))
            mEnableFreecam = !mEnableFreecam;
        break;
    }

    case Page_Misc: {
        if (stageScene == nullptr)
            break;
        cursor(1);
        print("Kill Mario\n");

        if (mCursorPos == 1 && al::isPadTriggerRight() && stageScene) {
            stageScene->mPlayerActor->mPlayer->mActionGraph->mCurrentNode = sDeathNode;
            sDeathNode->getAction()->setup();
        }

        int currentFigure = stageScene->mPlayerActor->mPlayer->mFigureDirector->getFigure();
        cursor(2);
        print("Mario Powerup: %s\n", sPowerupNames[currentFigure]);
        if (mCursorPos == 2) {
            int to = currentFigure + (al::isPadTriggerRight() ? 1 : al::isPadTriggerLeft() ? -1
                                                                                           : 0);
            if (to != currentFigure && to >= 0 && to <= 5)
                stageScene->mPlayerActor->mPlayer->mFigureDirector->change((EPlayerFigure)to);
        }

        cursor(3);
        print("Teleport to Checkpoint\n");
        if (mCursorPos == 3 && al::isPadTriggerRight()) {
            sead::PtrArray<al::LiveActor> actors = scene->mLiveActorKit->getAllActors()->getArray<al::LiveActor>();
            for (int i = 0; i < actors.capacity(); i++) {
                al::LiveActor* actor = actors[i];
                if (actor && *reinterpret_cast<u32*>(actor) == 0x003c5198 /* RestartObj vtable */)
                    stageScene->mPlayerActor->mPlayer->getProperty()->mTrans = al::getTrans(actor);
            }
        }

        cursor(4);
        print("Damage Mario\n");

        if (mCursorPos == 4 && al::isPadTriggerRight())
            stageScene->mPlayerActor->mPlayer->mFigureDirector->lose();

        cursor(5);
        print("Invincibility Leaf\n");
        if (mCursorPos == 5 && al::isPadTriggerRight())
            stageScene->mPlayerActor->mPlayer->mFigureDirector->change(EPlayerFigure_RaccoonDogWhite);

        break;
    }
    default:
        break;
    }

    // for (int i = 0; i < sizeof(mBuffer); i++)
    //     mWideBuffer[i] = mBuffer[i];

    memset(mWideBuffer, 0, sizeof(mWideBuffer));
    convShiftJisToWide(mWideBuffer, mBuffer, strlen(mBuffer));

    if (window) {
        al::setPaneString(window, "TxtMessage", mWideBuffer);

        al::hidePane(window, "Button");
        al::hidePane(window, "ShaWindowUL");
        al::hidePane(window, "ShaWindowUR");
        al::hidePane(window, "ShaWindowDL");
        al::hidePane(window, "ShaWindowDR");
        al::hidePane(window, "PicWindowUL");
        al::hidePane(window, "PicWindowUR");
        al::hidePane(window, "PicWindowDL");
        al::hidePane(window, "PicWindowDR");
    }
}

#ifdef MG_ENABLE_DEBUG_MENU
void playerActionGraphMoveHook(PlayerActionGraph* graph) // gets current PlayerAction
{
    mg::DebugMenu::instance().setPlayerActionVtablePtr(*(uintptr_t*)graph->getCurrentNode()->getAction());
    graph->getCurrentNode()->getAction()->update();
}

HK_B_HOOK_FUNC(PlayerActionGraphMoveHook, &PlayerActionGraph::move, playerActionGraphMoveHook)
HK_PATCH_ASM(DisableClosingWindowLayout, 0x0036add8, "mov r0, #0");

void playerFigureDirectorLose(PlayerFigureDirector* thisPtr)
{
    if (mg::DebugMenu::instance().isAlwaysTanooki()) {
        thisPtr->mFigure = EPlayerFigure_RaccoonDog;
        return;
    }

    thisPtr->lose();
}

void playerFigureDirectorSet(PlayerFigureDirector* thisPtr, const EPlayerFigure& figure)
{
    if (mg::DebugMenu::instance().isAlwaysTanooki()) {
        thisPtr->mFigure = EPlayerFigure_RaccoonDog;
        thisPtr->mHasFigureChanged = true;
        return;
    }

    thisPtr->mFigure = figure;
    thisPtr->mHasFigureChanged = true;
}

void playerFigureDirectorChange(PlayerFigureDirector* thisPtr, const EPlayerFigure& figure)
{
    if (mg::DebugMenu::instance().isAlwaysTanooki()) {
        thisPtr->change(EPlayerFigure_RaccoonDog);
        return;
    }

    thisPtr->change(figure);
}

HK_BL_HOOK_FUNC(PlayerFigureDirectorLoseHook, 0x0018241c, playerFigureDirectorLose)
HK_B_HOOK_FUNC(PlayerFigureDirectorSetHook, 0x001980e8, playerFigureDirectorSet)

HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook1, 0x00277d5c, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook2, 0x002ce818, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook3, 0x002ce84c, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook4, 0x002cf754, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook5, 0x002cf81c, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook6, 0x002cf880, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook7, 0x002cfcd0, playerFigureDirectorChange)
HK_BL_HOOK_FUNC(PlayerFigureDirectorChangeHook8, 0x002d1034, playerFigureDirectorChange)

template <int PadIdx>
bool padTriggerMaskHook(int port)
{
    if (mg::DebugMenu::instance().isHidden())
        return al::isPadTrigger(port, 1 << PadIdx);
    return false;
}
template <int PadIdx>
bool padHoldMaskHook(int port)
{
    if (mg::DebugMenu::instance().isHidden())
        return al::isPadHold(port, 1 << PadIdx);
    return false;
}

HK_B_HOOK_FUNC(IsPadTriggerRight, 0x00263848, padTriggerMaskHook<sead::Controller::cPadIdx_Right>)
HK_B_HOOK_FUNC(IsPadTriggerLeft, 0x00263858, padTriggerMaskHook<sead::Controller::cPadIdx_Left>)
HK_B_HOOK_FUNC(IsPadTriggerUp, 0x00270370, padTriggerMaskHook<sead::Controller::cPadIdx_Up>)
HK_B_HOOK_FUNC(IsPadTriggerDown, 0x00270368, padTriggerMaskHook<sead::Controller::cPadIdx_Down>)
HK_B_HOOK_FUNC(IsPadHoldRight, 0x001c80f8, padHoldMaskHook<sead::Controller::cPadIdx_Right>)
HK_B_HOOK_FUNC(IsPadHoldLeft, 0x00273498, padHoldMaskHook<sead::Controller::cPadIdx_Left>)
HK_B_HOOK_FUNC(IsPadHoldRight2, 0x0027dfa0, padHoldMaskHook<sead::Controller::cPadIdx_Right>)
HK_B_HOOK_FUNC(IsPadHoldLeft2, 0x0027df38, padHoldMaskHook<sead::Controller::cPadIdx_Left>)

#endif
