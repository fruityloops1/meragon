#include "mg/MapObj/ExampleActor.h"
#include "al/LiveActor/ActorActionKeeper.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/LiveActor/SensorMsg.h"
#include "al/Nerve/NerveFunction.h"
#include "hk/debug/Log.h"

namespace mg {

// https://redpepper.miraheze.org/wiki/Creating_a_Custom_Actor

namespace NrvExampleActor {

    NERVE_DEF(ExampleActor, Wait)
    NERVE_DEF(ExampleActor, Break)

} // namespace NrvExampleActor

void ExampleActor::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "BlockBrick"); // ObjectData/BlockBrick.szs
    al::initNerve(this, &NrvExampleActor::Wait);

    // actors can only be initialized during scene initialization, so we have to do it here
    mBreakEffectActor = new al::BreakModel(this, "BreakModel for BrickBlock", "BlockBrickBreak" /* ObjectData/BlockBrickBreak.szs */);
    al::initCreateActorNoPlacementInfo(mBreakEffectActor, info); // runs init function for the BreakModel

    makeActorAppeared();
}

bool ExampleActor::receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me) // called every time the actor receives a SensorMsg
{
    if (al::isMsgUpperPunch(msg)) {
        al::setNerve(this, &NrvExampleActor::Break);
        return true;
    }
    return false;
}

void ExampleActor::exeWait() { }
void ExampleActor::exeBreak()
{
    mBreakEffectActor->appear(); // make BreakModel alive, which will make it start the effect

    kill();
}

} // namespace mg
