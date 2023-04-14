#include "mg/MapObj/BouncyCloud.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/ActorPoseKeeper.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/LiveActor/SensorMsg.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Placement/PlacementFunction.h"
#include "hk/debug/Log.h"

extern "C" float __hardfp_sinf(float);

static float easeInSine(float t) { return 1.5707963 * t; }
static float easeOutSine(float t) { return 1 + sin(1.5707963 * (--t)); }

static float easeOutQuad(float t) { return 1 - (1 - t) * (1 - t); }

static float lerp(float a, float b, float f)
{
    return (a * (1.0 - f)) + (b * f);
}

namespace mg {

namespace NrvBouncyCloud {

    NERVE_DEF(BouncyCloud, Wait);
    NERVE_DEF(BouncyCloud, Reaction);
    NERVE_DEF(BouncyCloud, ReactionMoveDown); // move down
    NERVE_DEF(BouncyCloud, ReactionMoveUp); // move up

} // namespace NrvBouncyCloud

void BouncyCloud::init(const al::ActorInitInfo& info)
{
    al::initActor(this, info);

    mInitialY = al::getTrans(this).y;

    al::tryGetArg(&pWaitRange, info, "WaitRange");
    al::tryGetArg(&pSpeedMultiplier, info, "SpeedMultiplier");
    al::tryGetArg(&pReactionOffset, info, "ReactionOffset");
    al::tryGetArg(&pReactionMoveTime, info, "ReactionMoveTime");

    al::initNerve(this, &NrvBouncyCloud::Wait);
    makeActorAppeared();
}

bool BouncyCloud::receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me)
{
    if (al::isMsgPlayerFloorTouch(msg))
        mIsOnGround = true;

    return false;
}

void BouncyCloud::control()
{
    if (mIsOnGround) {
        if (al::isNerve(this, &NrvBouncyCloud::Wait)) {
            al::setNerve(this, &NrvBouncyCloud::ReactionMoveDown);
        }
    } else if (al::isNerve(this, &NrvBouncyCloud::Reaction)) {
        al::setNerve(this, &NrvBouncyCloud::ReactionMoveUp);
    }

    mIsOnGround = false;
}

void BouncyCloud::exeWait()
{
    calcAndSetBobbing();
}

void BouncyCloud::exeReaction()
{
    calcAndSetBobbing(-pReactionOffset);
}

void BouncyCloud::exeReactionMoveDown()
{
    if (al::isLessStep(this, pReactionMoveTime)) {

        // this
        al::getTransPtr(this)->y = mInitialY - (pReactionOffset * easeOutQuad(al::getNerveStep(this) / pReactionMoveTime));
    } else
        al::setNerve(this, &NrvBouncyCloud::Reaction);
}

void BouncyCloud::exeReactionMoveUp()
{
    if (al::isLessStep(this, pReactionMoveTime)) {

        // this
        al::getTransPtr(this)->y = mInitialY + (pReactionOffset * easeOutQuad(al::getNerveStep(this) / pReactionMoveTime)) - pReactionOffset;
    } else
        al::setNerve(this, &NrvBouncyCloud::Wait);
}

float BouncyCloud::calcBobbing(float offset) const
{
    return mInitialY + __hardfp_sinf(al::getNerveStep(this) * 0.01745 * pSpeedMultiplier) * (pWaitRange / 2) + offset;
}

void BouncyCloud::calcAndSetBobbing(float offset)
{
    al::getTransPtr(this)->y = calcBobbing(offset);
}

} // namespace mg
