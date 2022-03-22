#include "mg/actors/testactor.h"
#include "al/util/actor.h"
#include "al/util/nerve.h"
#include "mg/factory.h"

namespace mg {

void TestActor::init(const al::ActorInitInfo& info, uintptr_t r2, uintptr_t r3)
{
    al::initNerve(this, &nrvTestActorWait, 0);
    al::initMapPartsActor(this, info);
    makeActorAlive();
}

void TestActor::exeWait()
{
    if (al::isStep(this, 60))
        al::setNerve(this, nrvTestActorFlip);

    mActorPoseKeeper->getTransPtr()->y += mMoveDir ? 10 : -10;
}

void TestActor::exeFlip()
{
    mMoveDir = !mMoveDir;
    al::setNerve(this, nrvTestActorWait);
}

void TestActor::control()
{
}

} // namespace mg