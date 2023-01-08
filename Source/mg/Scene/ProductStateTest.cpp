#include "mg/Scene/ProductStateTest.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveStateCtrl.h"
#include "hk/debug/Log.h"
#include "mg/Scene/TestScene.h"
#include "sead/heap/seadHeapMgr.h"

namespace NrvProductStateTest {

NERVE_DEF(ProductStateTest, Load);
NERVE_DEF(ProductStateTest, Wait);

} // namespace NrvProductStateTest

ProductStateTest::ProductStateTest(ProductSequence* parent)
    : HostStateBase(parent, "Product Test State")
{
}

void ProductStateTest::init()
{
    hk::dbg::Log("ProductStateTest::init");
    initNerve(&NrvProductStateTest::Load);
}

void ProductStateTest::appear() { }

void ProductStateTest::exeLoad()
{
    hk::dbg::Log("%s", mHost->getNerveKeeper()->getStateCtrl()->getCurrentState()->mName);
    if (al::isFirstStep(this)) {
        hk::dbg::Log("Creating Scene Heap");
        al::createCourseSelectHeap();
        {
            hk::dbg::Log("Setting Scene Heap");
            sead::ScopedCurrentHeapSetter setter(al::getCourseSelectHeap());
            hk::dbg::Log("Creating mg::TestScene");
            mScene = new mg::TestScene();
            hk::dbg::Log("Initing mg::TestScene");
            mScene->init();
            hk::dbg::Log("End of scope");
        }
    }
    hk::dbg::Log("Exiting exeLoad");
    al::setNerve(this, &NrvProductStateTest::Wait);
}

void ProductStateTest::exeWait()
{
    if (al::isFirstStep(this)) {
        mScene->appear();
        mHost->mCurrentScene = mScene;
    }
    mScene->movement();

    if (!mScene->isAlive())
        kill();
}