#include "mg/MapObj/Gabon.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/HitSensorFunction.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/LiveActor/SensorMsg.h"
#include "al/Nerve/NerveFunction.h"
#include "mg/log.h"
#include <sead/math/seadVector.h>

namespace mg {

namespace NrvGabon {
    NERVE_DEF(Gabon, Wait);
    NERVE_DEF(Gabon, ThrowSign);
    NERVE_DEF(Gabon, Throw);
} // namespace NrvGabon

namespace NrvGabonThrowObj {

    NERVE_DEF(GabonThrowObj, Generate);
    NERVE_DEF(GabonThrowObj, Ground);

} // namespace NrvGabonThrowObj

void GabonThrowObj::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, mThrowObjModelName, nullptr);
    al::initNerve(this, &NrvGabonThrowObj::Generate, 0);
}

void GabonThrowObj::exeGenerate()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Generate");
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, &NrvGabonThrowObj::Ground);
}

void GabonThrowObj::exeGround()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Ground");
    mActorPoseKeeper->getTransPtr()->z += 20;
}

void GabonThrowObj::attackSensor(al::HitSensor* source, al::HitSensor* target)
{
    if (al::isSensorName(source, "Damage")
        && !(al::isNerve(this, &NrvGabonThrowObj::Generate) && al::isLessStep(this, sAnimCountThrowSign / 2))
        && al::isHitCylinderSensor(target, source, { 1, 0, 0 }, 30.0))
        al::sendMsgEnemyAttack(target, source);
}

void Gabon::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "Gabon", nullptr);
    al::initNerve(this, &NrvGabon::Wait, 0);
    return;

    for (int i = 0; i < sNeedleRollerAmount; i++) {
        GabonThrowObj* roller = new GabonThrowObj("GabonThrowObj", "NeedleRoller");
        al::initCreateActorNoPlacementInfo(roller, info);
        mNeedleRollers[i] = roller;
    }

    makeActorAppeared();
}

void Gabon::attackSensor(al::HitSensor* source, al::HitSensor* target)
{
    mg::log("%d", al::isSensorPlayer(target));
}

void Gabon::exeWait()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Wait");

    if (al::isStep(this, mThrowInterval))
        al::setNerve(this, &NrvGabon::ThrowSign);
}

void Gabon::exeThrowSign()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "ThrowSign");
        if (mThrowIndex >= sNeedleRollerAmount)
            mThrowIndex = 0;

        GabonThrowObj* roller = mNeedleRollers[mThrowIndex];
        mCurRoller = roller;
        mThrowIndex++;
        roller->makeActorAppeared();

        al::setNerve(roller, &NrvGabonThrowObj::Generate);
    }
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, &NrvGabon::Throw);

    if (mCurRoller) {
        al::calcJointPos(al::getTransPtr(mCurRoller), this, "GeneratorPosition");
        mCurRoller->mActorPoseKeeper->updatePoseQuat(al::getQuat(this));
    }
}

void Gabon::exeThrow()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Throw");
    if (al::isStep(this, sAnimCountThrow))
        al::setNerve(this, &NrvGabon::Wait);
}

} // namespace mg