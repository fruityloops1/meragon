#include "mg/MapObj/GreenDemon.h"
#include "Game/Player/PlayerActor.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/HitSensorFunction.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"
#include "mg/log.h"
#include <sead/math/seadVector.h>

namespace mg {

namespace NrvGreenDemon {

    NERVE_DEF(GreenDemon, Stall);
    NERVE_DEF(GreenDemon, Follow);
    NERVE_DEF(GreenDemon, Death);

} // namespace NrvGreenDemon

GreenDemon::GreenDemon(PlayerActor* target)
    : LiveActor("Green Demon")
    , mPlayer(target)
{
}

void GreenDemon::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "KinokoOneUp", nullptr);
    al::initNerve(this, &NrvGreenDemon::Stall);

    al::setTrans(this, al::getTrans(mPlayer) + sead::Vector3f(0, 300, 0));

    al::invalidateClipping(this);
    makeActorAppeared();
}

void GreenDemon::attackSensor(al::HitSensor* me, al::HitSensor* other)
{
    if (!al::isNerve(this, &NrvGreenDemon::Death) && al::isSensorName(me, "Body") && al::isSensorPlayer(other)) {
        mBodySensor = me;
        mPlayerSensor = other;
        al::setNerve(this, &NrvGreenDemon::Death);
    }
}

void GreenDemon::exeStall()
{
    const sead::Vector3f& playerVel = al::getVelocity(mPlayer);
    float sum = std::abs(playerVel.x) + std::abs(playerVel.y) + std::abs(playerVel.z);

    if (sum > 10)
        al::setNerve(this, &NrvGreenDemon::Follow);
}

static void normalize(sead::Vector3f* vec)
{
    float len = std::sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    if (len > 0.0) {
        len = 1.0 / len;
        *vec *= len;
    }
} // sead function generates infinite loop for some reason

void GreenDemon::exeFollow()
{
    const sead::Vector3f& thisPos = al::getTrans(this);
    const sead::Vector3f& playerPos = al::getTrans(mPlayer);

    sead::Vector3f toPlayerVec = playerPos - thisPos;
    *al::getTransPtr(this) += toPlayerVec / 32;
    normalize(&toPlayerVec);
    al::setFront(this, toPlayerVec);
}

void GreenDemon::exeDeath()
{
    float s = al::getScale(this).x;
    s /= 1.3;
    al::setScale(this, { s, s, s });
    if (s < 0.05) {
        makeActorDead();
    }
}

} // namespace mg