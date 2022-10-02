#include "mg/MapObj/GreenDemon.h"
#include "al/Util/NerveUtil.h"
#include "al/Util/actor/Init.h"
#include "al/Util/actor/Pose.h"
#include "al/Util/sensor/HitSensorUtil.h"
#include "al/Util/sensor/MsgUtil.h"
#include "game/Player/PlayerActor.h"
#include "mg/log.h"
#include "sead/math/seadVector.h"

namespace mg {

namespace {

    NERVE_DEF(GreenDemon, Stall);
    NERVE_DEF(GreenDemon, Follow);
    NERVE_DEF(GreenDemon, Death);

} // namespace

GreenDemon::GreenDemon(PlayerActor* target)
    : LiveActor("Green Demon")
    , mPlayer(target)
{
}

void GreenDemon::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "KinokoOneUp", nullptr);
    al::initNerve(this, &nrvGreenDemonStall);

    al::setTrans(this, al::getTrans(mPlayer) + sead::Vector3f(0, 300, 0));

    al::invalidateClipping(this);
    makeActorAppeared();
}

void GreenDemon::attackSensor(al::HitSensor* me, al::HitSensor* other)
{
    if (!al::isNerve(this, &nrvGreenDemonDeath) && al::isSensorName(me, "Body") && al::isSensorPlayer(other)) {
        mBodySensor = me;
        mPlayerSensor = other;
        al::setNerve(this, &nrvGreenDemonDeath);
    }
}

void GreenDemon::exeStall()
{
    const sead::Vector3f& playerVel = al::getVelocity(mPlayer);
    float sum = std::abs(playerVel.x) + std::abs(playerVel.y) + std::abs(playerVel.z);

    if (sum > 10)
        al::setNerve(this, &nrvGreenDemonFollow);
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
    static int i = 0;
    i++;
    if (i == 60) {
        i = 0;
        mStepSinceCaughtPlayer++;
        mPlayer->receiveMsg((al::SensorMsg)mStepSinceCaughtPlayer, mBodySensor, mPlayerSensor);
        mg::log("Sent message %d", mStepSinceCaughtPlayer);
    }

    float s = al::getScale(this).x;
    s /= 1.3;
    al::setScale(this, { s, s, s });
    if (s < 0.05) {
        // makeActorDead();
    }
}

} // namespace mg