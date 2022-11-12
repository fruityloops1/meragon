#include "Game/Scene/CourseSelectScene.h"
#include "Game/Scene/StageScene.h"
#include "al/Camera/Camera.h"
#include "al/Controller/ControllerUtil.h"
#include "al/Layout/LayoutInitInfo.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "mg/Freecam.h"
#include "mg/MapObj/GreenDemon.h"
#include "mg/log.h"
#include "sead/basis/seadNew.h"

void mMain()
{
    mg::log("mMain");
}

mg::GreenDemon* demon = nullptr;

void courseSelectSceneControlHook(CourseSelectScene* scene)
{
    scene->al::Scene::control();
}

void stageSceneControlHook(StageScene* scene)
{
    scene->StageScene::control();
}

void stageSceneInitLayoutHook(al::LayoutInitInfo* infoPtr, al::LiveActorKit* kit)
{
    al::initLayoutInitInfo(infoPtr, kit);
    const al::LayoutInitInfo& info = *infoPtr;

    // init any layouts
    /*al::LayoutActor* actor = new al::LayoutActor("操作ガイド");
    al::initLayoutActor(actor, info, "GuidePlay", nullptr);
    al::startAction(actor, "Appear");
    actor->appear();*/
}

void playerInitHook(PlayerActor* player, const al::ActorInitInfo& info)
{
    al::initActorSRTAndPoseTRSV(player, info);

    /*demon = new mg::GreenDemon(player);
    al::initCreateActorNoPlacementInfo(demon, info);*/
}

void freecamApplyHook(al::Camera* camera)
{
    camera->calc();
    camera->mTarget += mg::getFreecamOffset();
    camera->mPos += mg::getFreecamOffset();
}

static const sead::Vector2f neutral { 0, 0 };
const sead::Vector2f& getLeftStickHook(int port)
{
    // ignore left stick input if L is pressed (freecam is enabled)
    if (al::isPadHoldL())
        return neutral;
    return al::getLeftStick();
}

void* operator new(size_t size)
{
    return opNew(size);
}