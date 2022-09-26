#include "mg/Scene/ProductStateTest.h"
#include "al/System/MemorySystem.h"
#include "al/System/SceneHeapSetter.h"
#include "al/Util/NerveUtil.h"
#include "game/Sequence/ProductSequence.h"
#include "mg/Scene/TestScene.h"
#include "sead/heap/seadHeapMgr.h"

namespace {

NERVE_DEF(ProductStateTest, Load);
NERVE_DEF(ProductStateTest, Wait);

} // namespace

ProductStateTest::ProductStateTest(ProductSequence* parent)
    : HostStateBase(parent, "Product Test State")
{
}

void ProductStateTest::init()
{
    initNerve(&nrvProductStateTestLoad);
}

void ProductStateTest::appear() { }

void ProductStateTest::exeLoad()
{
    if (al::isFirstStep(this)) {
        al::createCourseSelectHeap();
        // sead::HeapMgr::instance()->setCurrentHeap_(al::getCourseSelectHeap());

        mScene = new mg::TestScene();
        mScene->init();
    }
    al::setNerve(this, &nrvProductStateTestWait);
}

void ProductStateTest::exeWait()
{
    if (al::isFirstStep(this)) {
        mScene->appear();
        mHost->mCurrentScene = mScene;
    }
    mScene->movement();

    if (!mScene->mIsAlive)
        kill();
}