#include "mg/Scene/ProductStateTest.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveStateCtrl.h"
#include "mg/Scene/TestScene.h"
#include "sead/heap/seadHeapMgr.h"
#include <mg/log.h>

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
    mg::log("ProductStateTest::init");
    initNerve(&NrvProductStateTest::Load);
}

void ProductStateTest::appear() { }

void ProductStateTest::exeLoad()
{
    mg::log("%s", mHost->getNerveKeeper()->getStateCtrl()->getCurrentState()->mName);
    if (al::isFirstStep(this)) {
        mg::log("Creating Scene Heap");
        al::createCourseSelectHeap();
        {
            mg::log("Setting Scene Heap");
            sead::ScopedCurrentHeapSetter setter(al::getCourseSelectHeap());
            mg::log("Creating mg::TestScene");
            mScene = new mg::TestScene();
            mg::log("Initing mg::TestScene");
            mScene->init();
            mg::log("End of scope");
        }
    }
    mg::log("Exiting exeLoad");
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