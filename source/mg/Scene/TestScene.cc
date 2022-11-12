#include "mg/Scene/TestScene.h"
#include "al/Nerve/NerveFunction.h"

namespace mg {

namespace NrvTestScene {
    NERVE_DEF(TestScene, Wait);
} // namespace NrvTestScene

TestScene::TestScene()
    : Scene("Test Scene")
{
}

void TestScene::init()
{
    initNerve(&NrvTestScene::Wait);
}

void TestScene::exeWait()
{
}

} // namespace mg