#include "mg/actors/testactor.h"
#include "al/util/actor.h"
#include "al/util/nerve.h"
#include "mg/factory.h"

namespace mg {

void TestActor::init(const al::ActorInitInfo& info, uintptr_t r2, uintptr_t r3)
{
    al::initNerve(this, &nrvTestActorWait, 0);
    al::initActorWithArchiveName(this, info, "BlockBrick", nullptr);
    makeActorAlive();
}

void TestActor::exeWait()
{
    if (mMoveFrames >= 60)
        mNerveKeeper->setNerve(&nrvTestActorFlip);
    mMoveFrames++;

    mActorPoseKeeper->getTransPtr()->y += mMoveDir ? 10 : -10;
}

void TestActor::exeFlip()
{
    mMoveFrames = 0;
    mMoveDir = !mMoveDir;
    mNerveKeeper->setNerve(&nrvTestActorWait);
}

void TestActor::control()
{
}

} // namespace mg