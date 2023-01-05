#include "mg/MapObj/Gabon.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/HitSensorFunction.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/LiveActor/SensorMsg.h"
#include "al/Nerve/NerveFunction.h"
#include "mg/log.h"
#include <Game/Enemy/EnemyStateBlowDown.h>
#include <Game/Enemy/EnemyStateBlowDownParam.h>
#include <Game/Enemy/EnemyStateUtil.h>
#include <al/Collision/CollisionUtil.h>
#include <al/Effect/EffectKeeper.h>
#include <al/HitSensor/HitSensor.h>
#include <al/LiveActor/ActorActionKeeper.h>
#include <al/LiveActor/ActorPoseKeeper.h>
#include <sead/math/seadVector.h>

namespace mg {

extern "C" float __hardfp_sinf(float);
extern "C" float __hardfp_cosf(float);

namespace NrvGabon {
    NERVE_DEF(Gabon, Wait);
    NERVE_DEF(Gabon, ThrowSign);
    NERVE_DEF(Gabon, Throw);
    NERVE_DEF(Gabon, BlowDown);
    NERVE_DEF(Gabon, PressDown);
} // namespace NrvGabon

namespace NrvGabonThrowObj {

    NERVE_DEF(GabonThrowObj, Generate);
    NERVE_DEF(GabonThrowObj, Ground);
    NERVE_DEF(GabonThrowObj, Break);

} // namespace NrvGabonThrowObj

void GabonThrowObj::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, mThrowObjModelName);
    al::initNerve(this, &NrvGabonThrowObj::Generate);
    initCollider(50, 0, 0);
}

void GabonThrowObj::kill() { al::setNerve(this, &NrvGabonThrowObj::Break); }

void GabonThrowObj::exeGenerate()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "Generate");
        al::calcQuatSide(&mSideVec, this);
    }
    if (al::isStep(this, sAnimCountThrowSign))
        al::setNerve(this, &NrvGabonThrowObj::Ground);
}

void GabonThrowObj::exeGround()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "Ground");
        al::invalidateClipping(this);
    }

    al::setVelocity(this, mDirection * 15);
    float& yRef = al::getVelocityPtr(this)->y;
    yRef = -15;
    al::rotateQuatXDirDegree(this, al::getQuat(this), 15);

    if (al::isCollidedGround(this))
        al::startHitReactionOnGround(this);

    if (al::isCollidedWall(this)) {
        al::setNerve(this, &NrvGabonThrowObj::Break);
        al::validateClipping(this);
    }
}

void GabonThrowObj::exeBreak()
{
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait");
        al::startHitReactionBreak(this);
        makeActorDead();
    }
}

void GabonThrowObj::attackSensor(al::HitSensor* me, al::HitSensor* other)
{
    if (al::isSensorName(me, "Damage")
        && !(al::isNerve(this, &NrvGabonThrowObj::Generate) && al::isLessStep(this, sAnimCountThrowSign / 2))
        && al::isHitCylinderSensor(other, me, mSideVec, 30.0))
        al::sendMsgEnemyAttack(other, me);
}

void Gabon::init(const al::ActorInitInfo& info)
{
    al::initNerve(this, &NrvGabon::Wait, 1);
    al::initActorWithArchiveName(this, info, "Gabon");

    for (int i = 0; i < sNeedleRollerAmount; i++) {
        GabonThrowObj* roller = new GabonThrowObj("GabonThrowObj", "NeedleRoller", al::getFront(this));
        al::initCreateActorNoPlacementInfo(roller, info);
        mNeedleRollers[i] = roller;
    }

    mStateBlowDown = new EnemyStateBlowDown(this, nullptr, nullptr, 1);
    al::initNerveState(this, mStateBlowDown, &NrvGabon::BlowDown, "state:BlowDown");

    initCollider(80, 80, 0);

    makeActorAppeared();
}

void Gabon::kill()
{
    for (int i = 0; i < sNeedleRollerAmount; i++)
        mNeedleRollers[i]->kill();
    LiveActor::kill();
}

void Gabon::attackSensor(al::HitSensor* me, al::HitSensor* other)
{
    if (me->getType() == al::SensorType_EnemyAttack && al::isSensorPlayer(other)) {
        al::sendMsgEnemyAttack(other, me);
    }
}

bool Gabon::receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me)
{
    if (al::isMsgPlayerKick(msg))
        return false;

    if (al::isSensorEnemy(me) && !al::isNerve(this, &NrvGabon::PressDown) && !al::isNerve(this, &NrvGabon::BlowDown)) {
        if (EnemyStateUtil::tryRequestPressDownAndNextNerve(msg, other, me, this, &NrvGabon::PressDown))
            al::invalidateClipping(this);
        EnemyStateUtil::tryRequestBlowDownAndNextNerve(msg, other, me, mStateBlowDown, &NrvGabon::BlowDown);
        return true;
    }
    return false;
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

void Gabon::exeBlowDown()
{
    if (al::updateNerveState(this))
        kill();
}

void Gabon::exePressDown()
{
    if (al::isFirstStep(this)) {
        al::setVelocityZero(this);
        al::startAction(this, "PressDown");
    }

    if (al::isStep(this, sAnimCountPressDown)) {
        al::validateClipping(this);
        al::startHitReactionDeath(this);
        kill();
    }
}

} // namespace mg