#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/CourseSelectScene.h"
#include "Game/Scene/StageScene.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/DebugMenu.h"
#include <sead/basis/seadNew.h>

extern "C" void hkMain()
{
    hk::dbg::Log("hkMain");
}

void courseSelectSceneControlHook(CourseSelectScene* scene)
{
    scene->al::Scene::control();
}

HK_TYPE_PATCH(CourseSelectSceneControlHook, 0x003cd238, void (*)(CourseSelectScene*), courseSelectSceneControlHook);

static WindowConfirmSingle* debugWindow = nullptr;

void stageSceneInitLayoutHook(al::LayoutInitInfo* infoPtr, al::LiveActorKit* kit)
{
    al::initLayoutInitInfo(infoPtr, kit);
    const al::LayoutInitInfo& info = *infoPtr;
    // init any layouts

#ifdef MG_ENABLE_DEBUG_MENU
    debugWindow = new WindowConfirmSingle("操作ガイド", info);
    debugWindow->appear();
#endif
}

// HK_PATCH_U32(GraphicsCtr, 0x00276fe4, 0xE12FFF1E);
// HK_TYPE_PATCH(courseballs, 0x001cf4f8, u32, 0xE320F000);

HK_BL_HOOK_FUNC(StageSceneInitLayoutHook, 0x00123708, stageSceneInitLayoutHook);

void stageSceneControlHook(StageScene* scene)
{
    scene->StageScene::control();

#ifdef MG_ENABLE_DEBUG_MENU
    mg::DebugMenu::instance().update(scene, debugWindow);
#endif
}

HK_TYPE_PATCH(StageSceneControlHook, 0x003c52e4, void (*)(StageScene*), stageSceneControlHook);

void* operator new(size_t size)
{
    return opNew(size);
}
