#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/CourseSelectScene.h"
#include "Game/Scene/StageScene.h"
#include "al/Camera/Camera.h"
#include "al/Controller/ControllerUtil.h"
#include "al/Layout/LayoutInitInfo.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/DebugMenu.h"
#include "mg/Freecam.h"
#include "mg/MapObj/GreenDemon.h"
#include "sead/basis/seadNew.h"
#include <stdarg.h>
#include <string.h>
#include <wchar.h>

extern "C" void hkMain()
{
    hk::dbg::Log("mMain");
}

void courseSelectSceneControlHook(CourseSelectScene* scene)
{
    scene->al::Scene::control();
}

HK_TYPE_PATCH(CourseSelectSceneControlHook, 0x003cd238, void (*)(CourseSelectScene*), courseSelectSceneControlHook);

WindowConfirmSingle* actor = nullptr;

void stageSceneInitLayoutHook(al::LayoutInitInfo* infoPtr, al::LiveActorKit* kit)
{
    al::initLayoutInitInfo(infoPtr, kit);
    const al::LayoutInitInfo& info = *infoPtr;

    // init any layouts
    actor = new WindowConfirmSingle("操作ガイド", info);
    actor->appear();
}

HK_BL_HOOK_FUNC(StageSceneInitLayoutHook, 0x00123708, stageSceneInitLayoutHook);

void stageSceneControlHook(StageScene* scene)
{
    scene->StageScene::control();

    mg::DebugMenu::instance().update(scene, actor);
}

HK_TYPE_PATCH(StageSceneControlHook, 0x003c52e4, void (*)(StageScene*), stageSceneControlHook);

void freecamApplyHook(al::Camera* camera)
{
    camera->calc();
    camera->mTarget += mg::getFreecamOffset();
    camera->mPos += mg::getFreecamOffset();
}

HK_BL_HOOK_FUNC(FreecamApplyHook, 0x002776f8, freecamApplyHook);

static const sead::Vector2f neutral { 0, 0 };
const sead::Vector2f& getLeftStickHook(int port)
{
    // ignore left stick input if L is pressed (freecam is enabled)
    if (al::isPadHoldL())
        return neutral;
    return al::getLeftStick();
}

HK_B_HOOK_FUNC(GetLeftStickHook, 0x0026db4c, getLeftStickHook);

HK_PATCH_ASM(DisableClosingWindowLayout, 0x0036add8, "mov r0, #0");

void* operator new(size_t size)
{
    return opNew(size);
}