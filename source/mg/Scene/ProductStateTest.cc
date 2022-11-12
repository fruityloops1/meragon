#include "mg/Scene/ProductStateTest.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
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
    initNerve(&NrvProductStateTest::Load);
}

void ProductStateTest::appear() { }

void ProductStateTest::exeLoad()
{
    if (al::isFirstStep(this)) {
        al::createSceneHeap("");
        {
            al::SceneHeapSetter setter;
            mScene = new mg::TestScene();
            mScene->init();
        }
    }
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