#include "mg/DebugMenu.h"
#include "Game/Player/PlayerAnimator.h"
#include "al/Controller/ControllerUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include <Game/Player/Player.h>
#include <stdio.h>

mg::DebugMenu sInstance;
mg::DebugMenu& mg::DebugMenu::instance()
{
    return sInstance;
}

struct ActionEntry {
    uintptr_t addr;
    const char* name;
};

static ActionEntry actions[] {
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

void mg::DebugMenu::update(StageScene* scene, WindowConfirmSingle* window)
{
    if (al::isPadTriggerLeft() && al::isPadHoldL()) {
        mHideMenu = !mHideMenu;
        if (!mHideMenu)
            window->appear();
        return;
    }
    if (mHideMenu) {
        window->kill();

        if (mTeleportEnabled) {

            if (al::isPadTriggerDown())
                mSavedPos = al::getTrans(scene->mPlayerActor);
            if (al::isPadTriggerUp())
                scene->mPlayerActor->mPlayer->getProperty()->mTrans = mSavedPos;
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

    case Page_About: {
        print("Bla bla bla\n");
        break;
    }

    case Page_Info: {
        const sead::Vector3f& trans = al::getTrans(scene->mPlayerActor);
        const sead::Vector3f& rot = al::getRotate(scene->mPlayerActor);
        const sead::Vector3f& vel = al::getVelocity(scene->mPlayerActor);
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
        break;
    }

    case Page_SceneInfo: {
        sead::PtrArray<al::LiveActor> actors = scene->mLiveActorKit->getAllActors()->getArray<al::LiveActor>();
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
        sead::PtrArray<al::LiveActor> actors = scene->mLiveActorKit->getAllActors()->getArray<al::LiveActor>();

        cursor(1);
        if (mCursorPos == 1) {
            if (al::isPadHoldLeft() || al::isPadHoldRight())
                mButtonHoldFrames++;
            else
                mButtonHoldFrames = 0;
            if (mButtonHoldFrames > 45)
                mCurActorIndex += al::isPadHoldRight() ? 1 : al::isPadHoldLeft() ? -1
                                                                                 : 0;
            mCurActorIndex += al::isPadTriggerRight() ? 1 : al::isPadTriggerLeft() ? -1
                                                                                   : 0;
        }
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

                print("Teleport to\n");
                if (mCursorPos == 2 && al::isPadTriggerRight())
                    scene->mPlayerActor->mPlayer->getProperty()->mTrans = trans;
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
        break;
    }
    default:
        break;
    }

    for (int i = 0; i < sizeof(mBuffer); i++)
        mWideBuffer[i] = mBuffer[i];

    if (window) {
        al::setPaneString(window, "TxtMessage", mWideBuffer);

        al::hidePane(window, "Button");
        al::hidePane(window, "PicBase");
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

void playerActionGraphMoveHook(PlayerActionGraph* graph)
{
    mg::DebugMenu::instance().setPlayerActionVtablePtr(*(uintptr_t*)graph->getCurrentNode()->getAction());
    graph->getCurrentNode()->getAction()->update();
}
HK_B_HOOK_FUNC(PlayerActionGraphMoveHook, &PlayerActionGraph::move, &playerActionGraphMoveHook)