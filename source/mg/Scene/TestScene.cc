#include "mg/Scene/TestScene.h"
#include "al/Util/NerveUtil.h"

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