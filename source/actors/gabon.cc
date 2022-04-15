#include "mg/actors/gabon.h"
#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "al/util/actor/action.h"
#include "al/util/actor/init.h"
#include "al/util/actor/model.h"
#include "al/util/actor/pose.h"
#include "al/util/nerve.h"
#include "al/util/sensor/hitsensor.h"
#include "al/util/sensor/msg.h"
#include "mg/log.h"
#include "sead/math/seadVector.h"

namespace mg {

void GabonThrowObj::init(const al::ActorInitInfo& info, uintptr_t, uintptr_t)
{
    al::initNerve(this, &nrvGabonThrowObjGenerate, 0);
    al::initActorWithArchiveName(this, info, mThrowObjModelName, nullptr);
}

void GabonThrowObj::exeGenerate()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Generate", nullptr, nullptr);
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, nrvGabonThrowObjGround);
}

void GabonThrowObj::exeGround()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Ground", nullptr, nullptr);
    mActorPoseKeeper->getTransPtr()->z += 20;
}

void GabonThrowObj::attackSensor(al::HitSensor* source, al::HitSensor* target)
{
    if (al::isSensorName(source, "Damage")
        && !(al::isNerve(this, nrvGabonThrowObjGenerate) && al::isLessStep(this, sAnimCountThrowSign / 2))
        && al::isHitCylinderSensor(target, source, { 1, 0, 0 }, 30.0))
        al::sendMsgEnemyAttack(target, source);
}

void Gabon::init(const al::ActorInitInfo& info, uintptr_t, uintptr_t)
{
    al::initNerve(this, &nrvGabonWait, 0);
    al::initActorWithArchiveName(this, info, "Gabon", nullptr);

    for (int i = 0; i < sNeedleRollerAmount; i++) {
        GabonThrowObj* roller = new GabonThrowObj("GabonThrowObj", "NeedleRoller");
        al::initCreateActorNoPlacementInfo(roller, info);
        mNeedleRollers[i] = roller;
    }

    makeActorAlive();
}

void Gabon::attackSensor(al::HitSensor* source, al::HitSensor* target)
{
    mg::log("%d", al::isSensorPlayer(target));
}

void Gabon::exeWait()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Wait", nullptr, nullptr);

    if (al::isStep(this, mThrowInterval))
        al::setNerve(this, nrvGabonThrowSign);
}

void Gabon::exeThrowSign()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "ThrowSign", nullptr, nullptr);
        if (mThrowIndex >= sNeedleRollerAmount)
            mThrowIndex = 0;

        GabonThrowObj* roller = mNeedleRollers[mThrowIndex];
        mCurRoller = roller;
        mThrowIndex++;
        roller->makeActorAlive();

        al::setNerve(roller, nrvGabonThrowObjGenerate);
    }
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, nrvGabonThrow);

    if (mCurRoller) {
        sead::Vector3f generatorPos = mActorPoseKeeper->getTrans();
        al::calcJointPos(&generatorPos, this, "GeneratorPosition");
        *mCurRoller->mActorPoseKeeper->getTransPtr() = generatorPos;
        mCurRoller->mActorPoseKeeper->updatePoseQuat(al::getQuat(this));
    }
}

void Gabon::exeThrow()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Throw", nullptr, nullptr);
    if (al::isStep(this, sAnimCountThrow))
        al::setNerve(this, nrvGabonWait);
}

} // namespace mg