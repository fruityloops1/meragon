#include "al/Layout/LayoutActor.h"
#include "al/Layout/LayoutInitInfo.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/LiveActor.h"
#include "al/Nerve/Nerve.h"
#include "al/System/Byaml/ByamlIter.h"
#include "al/System/Resource.h"
#include "al/Util/NerveUtil.h"
#include "al/Util/StringUtil.h"
#include "al/Util/actor/Action.h"
#include "al/Util/actor/Init.h"
#include "al/Util/actor/Pose.h"
#include "game/Layout/WindowConfirmSingle.h"
#include "game/Player/PlayerActor.h"
#include "game/Scene/CourseSelectScene.h"
#include "game/Scene/StageScene.h"
#include "game/Sequence/ProductSequence.h"
#include "mg/Factory/ActorFactory.h"
#include "mg/MapObj/GreenDemon.h"
#include "mg/diag.h"
#include "mg/efun.h"
#include "mg/log.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/math/seadMathCalcCommon.h"
#include "sead/math/seadVector.h"
#include "sead/prim/seadSafeString.h"
#include <cmath>

void mMain()
{
    mg::log("mMain");
    mg::log("Initializing Actor Factory");
    mg::initCustomActorFactory();
}

mg::GreenDemon* demon = nullptr;

int tabAmount = 0;
char tabBuffer[256] { 0 };

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
    mg::log("%s%s: ", tabBuffer, heap->getName().cstr());
    mg::log("%s\tSize: %d Bytes (%d KB, %d MB)", tabBuffer, heap->mSize, heap->mSize / 1000, heap->mSize / 1000000);
    // mg::log("%s\tFree: %d Bytes (%d KB, %d MB)", tabBuffer, free, free / 1000, free / 1000000);
    mg::log("%s\tStart: 0x%x End: 0x%x", tabBuffer, heap->mStart, (uintptr_t)heap->mStart + heap->mSize);
    for (sead::Heap& child : heap->mChildren) {
        tabAmount++;
        updateTabs();
        printHeap(&child);
        tabAmount--;
    }
};

void courseSelectSceneControlHook(CourseSelectScene* scene)
{
    scene->al::Scene::control();
}
void stageSceneControlHook(StageScene* scene)
{
    scene->StageScene::control();
    PlayerActor* player = scene->mPlayerActor;
    if (player) {
        /*sead::Vector3f* trans = al::getTransPtr(player);
        static const char* lastAnim = "";
        const char* anim = al::getActionName(player);
        if (!al::isEqualString(lastAnim, anim))
            for (const char* name : { "Jump", "Jump2", "Jump3" })
                if (al::isEqualString(anim, name)) {
                    player->mPlayer->mPlayerProperty->trans.y += 100;
                    break;
                }*/
        // mg::log("%x %d %d %d %s", scene->getNerveKeeper()->getCurrentNerve(), (int)trans.x, (int)trans.y, (int)trans.z, scene->mStageStartParam->getStageDataName());

        // printHeap(sead::HeapMgr::sRootHeaps[0]);
    }
}

void stageSceneInitLayoutHook(al::LayoutInitInfo* infoPtr, al::LiveActorKit* kit)
{
    al::initLayoutInitInfo(infoPtr, kit);
    const al::LayoutInitInfo& info = *infoPtr;

    al::LayoutActor* actor = new al::LayoutActor("操作ガイド");
    al::initLayoutActor(actor, info, "GuidePlay", nullptr);
    al::startAction(actor, "Appear");
    actor->appear();
}

void playerInitHook(PlayerActor* player, const al::ActorInitInfo& info)
{
    al::initActorSRTAndPoseTRSV(player, info);

    /*demon = new mg::GreenDemon(player);
    al::initCreateActorNoPlacementInfo(demon, info);*/
}

// replaces Scene::initPlacement
void sceneInitPlacementHook(al::Scene* scene, al::Resource* stageFile, const al::ActorInitInfo& baseInfo, const char* infoIterName)
{
    if (stageFile) {
        al::ByamlIter stageData(static_cast<u8*>(stageFile->getByml("StageData")));
        al::ByamlIter allInfos;
        if (stageData.tryGetIterByKey(&allInfos, "AllInfos")) {
            al::ByamlIter infoIter;
            if (allInfos.tryGetIterByKey(&infoIter, infoIterName) && scene->mCCNTHolder)
                for (int i = 0; i < infoIter.getSize(); i++) {
                    al::ByamlIter placement;
                    infoIter.tryGetIterByIndex(&placement, i);
                    const char* objectName = nullptr;
                    const char* className = nullptr;
                    placement.tryGetStringByKey(&objectName, "name");
                    placement.tryGetStringByKey(&className, "ClassName");
                    if (className && objectName) {
                        if (auto create = mg::getActorCreatorFromFactory(className)) {
                            al::ActorInitInfo info;
                            al::initActorInitInfo(&info, &placement, baseInfo);
                            al::LiveActor* newActor = create(objectName);
                            al::initCreateActorWithPlacementInfo(newActor, info);
                        }
                    } else if (objectName) {
                        al::ActorInitInfo info;
                        al::initActorInitInfo(&info, &placement, baseInfo);
                        al::LiveActor* newActor = scene->mCCNTHolder->getCreator(objectName)(objectName);
                        al::initCreateActorWithPlacementInfo(newActor, info);
                    }
                }
        }
    }
}

void* operator new(size_t size)
{
    return opNew(size);
}