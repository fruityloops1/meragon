#include "mg/actors/testactor.h"
#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "al/util/actor.h"
#include "al/util/nerve.h"

namespace mg {

void MagicBall::init(const al::ActorInitInfo& info, uintptr_t, uintptr_t)
{
    al::initNerve(this, &nrvMagicBallWait, 0);
    al::initActorWithArchiveName(this, info, "KinokoPoison", nullptr);
}

void MagicBall::exeWait()
{
    mActorPoseKeeper->getTransPtr()->y += 4;
    if (al::isStep(this, 120)) {
        makeActorDead();
    }
}

void MagicBall::control()
{
}

void TestActor::init(const al::ActorInitInfo& info, uintptr_t r2, uintptr_t r3)
{
    al::initNerve(this, &nrvTestActorWait, 0);
    al::initActorWithArchiveName(this, info, "Kameck", nullptr);

    for (int i = 0; i < 5; i++) {
        mMagicBalls[i] = new MagicBall("MagicBall");
        al::initCreateActorNoPlacementInfo(mMagicBalls[i], info);
        *mMagicBalls[i]->mActorPoseKeeper->getTransPtr() = *mActorPoseKeeper->getTransPtr();
    }

    makeActorAlive();
}

void TestActor::exeWait()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Wait", nullptr, nullptr);
    if (al::isStep(this, 60))
        al::setNerve(this, &nrvTestActorDrop);
}

void TestActor::exeDrop()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "Attack", nullptr, nullptr);
        mMagicBalls[mDropIndex]->makeActorAlive();
        *mMagicBalls[mDropIndex]->mActorPoseKeeper->getTransPtr() = *mActorPoseKeeper->getTransPtr();
        al::setNerve(mMagicBalls[mDropIndex], nrvMagicBallWait);
        mDropIndex = mDropIndex < 4 ? mDropIndex + 1 : 0;
    }

    if (al::isStep(this, 30))
        al::setNerve(this, nrvTestActorWait);
}

void TestActor::control()
{
}

} // namespace mg
