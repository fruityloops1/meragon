#include "mg/MapObj/GreenDemon.h"
#include "Game/Player/PlayerActor.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/HitSensorFunction.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include <sead/math/seadVector.h>
#include <stddef.h>

PlayerActionNode* sDeathNode = nullptr;
static mg::GreenDemon* sDemon = nullptr;

static void* newPlayerActionPoisonDeathHook(size_t size)
{
    void* d = new char[size];
    sDeathNode = static_cast<PlayerActionNode*>(d); // yanks the pointer for the PlayerActionPoisonDeath PlayerActionNode so we can use it to kill mario later
    return d;
}
HK_BL_HOOK(NewPlayerActionPoisonDeathHook, 0x001aa3e0, newPlayerActionPoisonDeathHook);

void playerInitHook(PlayerActor* player, const al::ActorInitInfo& info)
{
    al::initActorSRTAndPoseTRSV(player, info);

    // sDemon = new mg::GreenDemon(player);
    // al::initCreateActorNoPlacementInfo(sDemon, info);
}
HK_BL_HOOK(PlayerInitHook, 0x00131adc, playerInitHook);

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
    mPrevPos = al::getTrans(this);

    al::invalidateClipping(this);
    makeActorAppeared();
}

bool GreenDemon::checkForbidden()
{
    // vtables of PlayerActions that will prevent the player from dying
    constexpr uintptr_t forbidden[] = { 0x003cc2bc };

    bool isForbidden = false;
    for (uintptr_t addr : forbidden)
        if (*(uintptr_t*)mPlayer->mPlayer->mActionGraph->mCurrentNode->getAction() == addr)
            isForbidden = true;
    return isForbidden;
}

void GreenDemon::attackSensor(al::HitSensor* me, al::HitSensor* other)
{
    if (!al::isNerve(this, &NrvGreenDemon::Death) && al::isSensorName(me, "Body") && al::isSensorPlayer(other)) {
        PlayerActor* player = static_cast<PlayerActor*>(other->getHost());

        bool isForbidden = checkForbidden();

        if (sDeathNode && !isForbidden) {
            player->mPlayer->mActionGraph->mCurrentNode = sDeathNode;
            sDeathNode->getAction()->setup();
            al::setNerve(this, &NrvGreenDemon::Death);
        }

        if (isForbidden)
            al::setTrans(this, al::getTrans(mPlayer) + sead::Vector3f(0, 1000, 0));
    }
}

void GreenDemon::exeStall()
{
    const sead::Vector3f& playerVel = al::getVelocity(mPlayer);
    float sum = fabs(playerVel.x) + fabs(playerVel.y) + fabs(playerVel.z);

    if (sum > 10)
        al::setNerve(this, &NrvGreenDemon::Follow);
}

static void normalize(sead::Vector3f* vec)
{
    float len = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    if (len > 0.0) {
        len = 1.0 / len;
        *vec *= len;
    }
} // sead function generates infinite loop for some reason

static float calcDistance(const sead::Vector3f& pos1, const sead::Vector3f& pos2)
{
    sead::Vector3f a = pos2 - pos1;
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void GreenDemon::exeFollow()
{ // thanks trippi
    if (checkForbidden()) {
        hk::dbg::Log("GreenDemon::exeFollow paused, forbidden");
        al::setVelocity(this, { 0, 0, 0 });
        return;
    }
    if (mDoTpToPlayerRepeat) {
        al::setTrans(this, al::getTrans(mPlayer) + sead::Vector3f(0, 1000, 0));
        mDoTpToPlayerRepeat = false;
        getLiveActorFlag().isOffCollide = false;
    }

    const sead::Vector3f& thisPos = al::getTrans(this);
    const sead::Vector3f& playerPos = al::getTrans(mPlayer);

    float speed = 30;
    float distanceToMarioWithOffset = calcDistance(thisPos, playerPos) - 20;
    speed += distanceToMarioWithOffset >= 0.f ? sqrtf(distanceToMarioWithOffset) * .1 : -(sqrtf(sqrtf(powf(distanceToMarioWithOffset, 2)))) * .1;

    // stuck checking
    if (calcDistance(thisPos, playerPos) > 10000)
        speed = 5000;
    mAvgCount++;
    mMoveAvg = ((mMoveAvg * mAvgCount - 1) + calcDistance(thisPos, mPrevPos)) / mAvgCount;
    if (mMoveAvg < 30)
        mStuckFrames++;

    if (mAvgCount == 480) {
        mAvgCount = 0;
        mMoveAvg = 0;
    }

    if (mStuckFrames >= 90) {
        mAvgCount = 0;
        mMoveAvg = 0;
        mStuckFrames = 0;
        al::offCollide(this);
        al::setTrans(this, al::getTrans(mPlayer) + sead::Vector3f(0, 1000, 0));
        mDoTpToPlayerRepeat = true;
    }

    hk::dbg::Log("Demon %f %f %f", thisPos.x, thisPos.y, thisPos.z);
    hk::dbg::Log("AvgCount %d MoveAvg %f StuckFrames %d", mAvgCount, mMoveAvg, mStuckFrames);

    sead::Vector3f toPlayerVec = playerPos - thisPos;
    normalize(&toPlayerVec);
    *al::getVelocityPtr(this) = toPlayerVec * speed;
    al::setFront(this, toPlayerVec);
    mPrevPos = thisPos;
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