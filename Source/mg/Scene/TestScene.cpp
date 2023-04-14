#include "Game/Layout/WindowConfirmSingle.h"
#include "al/Layout/LayoutActor.h"
#include "al/Layout/LayoutInitInfo.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/LiveActorKit.h"
#include "al/Math/HashUtil.h"
#include "al/Math/RandomUtil.h"
#include "al/Memory//MemorySystem.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/TypePatch.h"
#include "mg/Scene/TestScene.h"

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

    initAndLoadStageResource("KinopioGameOverDashJumpStage", 1, al::getCourseSelectResourceHeap());

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

    class BallsActor : public al::LayoutActor {
    public:
        BallsActor(const al::LayoutInitInfo& info)
            : LayoutActor("suckmyballs")
        {
            al::initLayoutActor(this, info, "PhotoOpening");
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

void TestScene::drawMainTop()
{
    Scene::drawMainTop();

    ((void (*)())0x003267d4)();
    ((void (*)(al::Scene*, int))0x00276ef0)(this, 1);
    ((void (*)(al::LayoutKit*, int, int))0x001d0b6c)(mLayoutKit, 1, 0);
    al::executeDraw(mLiveActorKit, "‚Q‚cƒx[ƒXiã‰æ–Êj");
    al::executeDraw(mLiveActorKit, "‚Q‚ciã‰æ–Êj");
}

void TestScene::control()
{
    mLiveActorKit->update();
    mLayoutKit->update();
}

void TestScene::exeWait()
{
    hk::dbg::Log("TestScene::exeWait");
}

} // namespace mg
