#include "mg/Scene/TestScene.h"
#include "al/Nerve/NerveFunction.h"
#include <mg/log.h>

namespace mg {

namespace NrvTestScene {
    NERVE_DEF(TestScene, Wait);
} // namespace NrvTestScene

TestScene::TestScene()
    : Scene("Test Scene")
{
    mg::log("TestScene::TestScene");
    mIsAlive = true;
}

void TestScene::init()
{
    mg::log("TestScene::init");
    initSceneObjHolder();
    initNerve(&NrvTestScene::Wait);
}

void TestScene::exeWait()
{
    mg::log("TestScene::exeWait");
}

} // namespace mg