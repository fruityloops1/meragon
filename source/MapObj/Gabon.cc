#include "mg/actors/Gabon.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/LiveActor.h"
#include "al/Util/NerveUtil.h"
#include "al/Util/actor/Action.h"
#include "al/Util/actor/Init.h"
#include "al/Util/actor/Model.h"
#include "al/Util/actor/Pose.h"
#include "al/Util/sensor/HitSensorUtil.h"
#include "al/Util/sensor/MsgUtil.h"
#include "mg/log.h"
#include "sead/math/seadVector.h"

namespace mg {

namespace {
    NERVE_DEF(Gabon, Wait);
    NERVE_DEF(Gabon, ThrowSign);
    NERVE_DEF(Gabon, Throw);

    NERVE_DEF(GabonThrowObj, Generate);
    NERVE_DEF(GabonThrowObj, Ground);
}

void GabonThrowObj::init(const al::ActorInitInfo& info)
{
    al::initNerve(this, &nrvGabonThrowObjGenerate, 0);
    al::initActorWithArchiveName(this, info, mThrowObjModelName, nullptr);
}

void GabonThrowObj::exeGenerate()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Generate");
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, nrvGabonThrowObjGround);
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
        && !(al::isNerve(this, nrvGabonThrowObjGenerate) && al::isLessStep(this, sAnimCountThrowSign / 2))
        && al::isHitCylinderSensor(target, source, { 1, 0, 0 }, 30.0))
        al::sendMsgEnemyAttack(target, source);
}

void Gabon::init(const al::ActorInitInfo& info)
{
    al::initNerve(this, &nrvGabonWait, 0);
    al::initActorWithArchiveName(this, info, "Gabon", nullptr);

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
        al::setNerve(this, nrvGabonThrowSign);
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
        al::startAction(this, "Throw");
    if (al::isStep(this, sAnimCountThrow))
        al::setNerve(this, nrvGabonWait);
}

} // namespace mg