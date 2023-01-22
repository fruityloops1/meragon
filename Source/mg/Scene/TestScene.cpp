#include "mg/Scene/TestScene.h"
#include "Game/Layout/WindowConfirmSingle.h"
#include "al/Layout/LayoutActor.h"
#include "al/Layout/LayoutInitInfo.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/LiveActorKit.h"
#include "al/Math/HashUtil.h"
#include "al/Math/RandomUtil.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/TypePatch.h"

namespace mg {

namespace NrvTestScene {
    NERVE_DEF(TestScene, Wait);
} // namespace NrvTestScene

TestScene::TestScene(ProductStageStartParam* startParam)
    : Scene("Test Scene")
    , mStartParam(startParam)
{
    hk::dbg::Log("TestScene::TestScene");
    mIsAlive = true;
}

void TestScene::init()
{
    hk::dbg::Log("TestScene::init");
    initSceneObjHolder();
    initActorFactory();
    initLiveActorKit();
    initLayoutKit();
    // ((void (*)(al::LayoutKit*))0x002765e8)(mLayoutKit);
    initCameraDirector();
    mLayoutKit->createExecuteDirector(1);
    mLayoutKit->createEffectSystem();

    const char* stageDataName = mStartParam->getStageDataName();
    hk::dbg::Log("Stage: %s", stageDataName);
    hk::dbg::Log("Scenario: %d", mStartParam->getScenario());
    al::initRandomSeed(al::calcHashCode(stageDataName));

    al::LayoutInitInfo baseLayoutInfo;
    al::initLayoutInitInfo(&baseLayoutInfo, mLiveActorKit);
    al::PlacementInfo basePlacementInfo;
    al::ActorInitInfo baseInfo;
    al::initActorInitInfo(&baseInfo, &basePlacementInfo, baseLayoutInfo, mLiveActorKit);

    hk::dbg::Log("Creating WindowConfirmSingle");
    WindowConfirmSingle* window = new WindowConfirmSingle("操作ガイド", baseLayoutInfo);
    window->appear();

    class BallsActor : public al::LayoutActor {
    public:
        BallsActor(const al::LayoutInitInfo& info)
            : LayoutActor("suckmyballs")
        {
            al::initLayoutActor(this, info, "PhotoLuigi");
            al::startAction(this, "Appear");
        }

        void control() override
        {
            hk::dbg::Log("I AM ALIVE");
        }
    };

    BallsActor* actor = new BallsActor(baseLayoutInfo);
    actor->appear();

    endInit(baseInfo);
    mLiveActorKit->endInit();

    initNerve(&NrvTestScene::Wait);
}

void TestScene::drawMain()
{
    Scene::drawMain();
}

void TestScene::control()
{
    mLiveActorKit->update();
    mLayoutKit->update();
}

void TestScene::unk8()
{
    al::executeDraw(mLiveActorKit, "２Ｄベース（上画面）");
}

void TestScene::unk9()
{
    al::executeDrawList(mLiveActorKit, "２Ｄベース（上画面）", "２Ｄ写真");
}

void TestScene::exeWait()
{
    hk::dbg::Log("TestScene::exeWait");
}

} // namespace mg
