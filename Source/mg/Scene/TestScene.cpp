#include "mg/Scene/TestScene.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"

namespace mg {

namespace NrvTestScene {
    NERVE_DEF(TestScene, Wait);
} // namespace NrvTestScene

TestScene::TestScene()
    : Scene("Test Scene")
{
    hk::dbg::Log("TestScene::TestScene");
    mIsAlive = true;
}

void TestScene::init()
{
    hk::dbg::Log("TestScene::init");
    initSceneObjHolder();
    initNerve(&NrvTestScene::Wait);
}

void TestScene::exeWait()
{
    hk::dbg::Log("TestScene::exeWait");
}

} // namespace mg