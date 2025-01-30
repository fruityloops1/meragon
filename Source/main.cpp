#include "Game/Layout/WindowConfirmSingle.h"
#include "Game/Scene/CourseSelectScene.h"
#include "Game/Scene/StageScene.h"
#include "al/Controller/ControllerUtil.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/Debug/Framework.h"
#include "mg/DebugMenu.h"
#include "mg/Freecam.h"
#include "mg/ProductSequenceMod.h"
#include "sead/heap/seadHeapMgr.h"
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

static al::LayoutActor* debugWindow = nullptr;

void productSequenceInitLayoutHook(al::LayoutInitInfo* infoPtr, al::LayoutKit* kit)
{
    al::initLayoutInitInfo(infoPtr, kit);
    const al::LayoutInitInfo& info = *infoPtr;
    // init any layouts

#ifdef MG_ENABLE_DEBUG_MENU
    debugWindow = new al::LayoutActor("操作ガイド");
    al::initLayoutActor(debugWindow, info, "DebugWindow");
    debugWindow->appear();
#endif
}

// HK_PATCH_U32(GraphicsCtr, 0x00276fe4, 0xE12FFF1E);
// HK_TYPE_PATCH(courseballs, 0x001cf4f8, u32, 0xE320F000);

HK_BL_HOOK_FUNC(StageSceneInitLayoutHook, 0x001633c8, productSequenceInitLayoutHook);

static int tabAmount = 0;
static char tabBuffer[256] { 0 };

void updateTabs()
{
    for (int i = 0; i < tabAmount; i++) {
        tabBuffer[i] = '\t';
    }
    tabBuffer[tabAmount] = '\0';
};

void printHeap(sead::Heap* heap)
{
    updateTabs();
    hk::dbg::Log("%s%s: ", tabBuffer, heap->getName().cstr());
    hk::dbg::Log("%s\tSize: %d Bytes (%d KB, %d MB)", tabBuffer, heap->mSize, heap->mSize / 1000, heap->mSize / 1000000);
    // mg::log("%s\tFree: %d Bytes (%d KB, %d MB)", tabBuffer, free, free / 1000, free / 1000000);
    hk::dbg::Log("%s\tStart: 0x%x End: 0x%x", tabBuffer, heap->mStart, (uintptr_t)heap->mStart + heap->mSize);
    for (sead::Heap& child : heap->mChildren) {
        tabAmount++;
        updateTabs();
        printHeap(&child);
        tabAmount--;
    }
}
void productSequenceUpdateHook(ProductSequence* sequence)
{
    sequence->al::Sequence::update();
    mg::updateFreecam();

    if (al::isPadHoldStart() && al::isPadTriggerTouch())
        printHeap(sead::HeapMgr::sRootHeaps[0]);

#ifdef MG_ENABLE_DEBUG_MENU
    mg::DebugMenu::instance().update(sequence->mCurrentScene, debugWindow);

    auto& p = mg::getProfilingData();

    memset(p.executeTableLists, 0, sizeof(p.executeTableLists));
    memset(p.executeDrawTable, 0, sizeof(p.executeDrawTable));
#endif
}

HK_BL_HOOK_FUNC(ProductSequenceUpdateHook, 0x00163818, productSequenceUpdateHook);

void stageSceneControlHook(StageScene* scene)
{
    scene->StageScene::control();
}

HK_TYPE_PATCH(StageSceneControlHook, 0x003c52e4, void (*)(StageScene*), stageSceneControlHook);

void* operator new(size_t size)
{
    return opNew(size);
}
