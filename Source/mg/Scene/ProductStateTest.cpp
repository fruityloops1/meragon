#include "mg/Scene/ProductStateTest.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Functor/FunctorV0M.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveStateCtrl.h"
#include "al/System/InitializeThread.h"
#include "hk/debug/Log.h"
#include "mg/Scene/TestScene.h"
#include "sead/heap/seadHeapMgr.h"

namespace NrvProductStateTest {

NERVE_DEF(ProductStateTest, Load);
NERVE_DEF(ProductStateTest, Wait);

} // namespace NrvProductStateTest

ProductStateTest::ProductStateTest(ProductSequence* parent, ProductStageStartParam* startParam)
    : HostStateBase(parent, "Product Test State")
    , mStartParam(startParam)
{
}

void ProductStateTest::init()
{
    hk::dbg::Log("ProductStateTest::init");
    initNerve(&NrvProductStateTest::Load);
}

void ProductStateTest::appear() { NerveStateBase::appear(); }

void ProductStateTest::startInitScene()
{
    hk::dbg::Log("Creating Scene Heap");
    al::createCourseSelectHeap();

    hk::dbg::Log("Setting Scene Heap");
    sead::ScopedCurrentHeapSetter setter(al::getCourseSelectHeap());

    hk::dbg::Log("Creating mg::TestScene");
    mScene = new mg::TestScene(mStartParam);

    al::createAndStartInitializeThread(al::getCourseSelectHeap(), 0x12 /* ? */, al::FunctorV0M(mScene, &mg::TestScene::init));

    hk::dbg::Log("End of scope");
}

void ProductStateTest::exeLoad()
{
    if (al::isFirstStep(this))
        startInitScene();

    if (mHost->mWipeKeeper->isAnyWipeCloseEnd()) {
        hk::dbg::Log("Exiting exeLoad");
        al::setNerve(this, &NrvProductStateTest::Wait);
    }
}

void ProductStateTest::exeWait()
{
    if (al::isFirstStep(this)) {
        mScene->appear();
        mHost->mCurrentScene = mScene;

        for (al::WipeSimpleTopBottom* wipe : mHost->mWipeKeeper->mWipes) {
            wipe->getTop()->kill();
            wipe->getBottom()->kill();
        }
    }
    mScene->movement();

    if (!mScene->isAlive())
        kill();
}