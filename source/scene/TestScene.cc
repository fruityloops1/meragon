#include "mg/scene/TestScene.h"
#include "al/util/NerveUtil.h"

namespace mg {

namespace {
    NERVE_DEF(TestScene, Wait);
}

TestScene::TestScene()
    : Scene("Test Scene")
{
}

void TestScene::init()
{
    initNerve(&nrvTestSceneWait);
}

void TestScene::exeWait()
{
}

} // namespace mg