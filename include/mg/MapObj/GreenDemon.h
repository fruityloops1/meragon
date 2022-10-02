#pragma once

#include "al/LiveActor/LiveActor.h"
#include "game/Player/PlayerActor.h"

namespace mg {

class GreenDemon : public al::LiveActor {
    PlayerActor* const mPlayer = nullptr;
    int mStepSinceCaughtPlayer = 0;
    al::HitSensor* mPlayerSensor = nullptr;
    al::HitSensor* mBodySensor = nullptr;

public:
    GreenDemon(PlayerActor* target);

    void init(const al::ActorInitInfo& info) override;
    void attackSensor(al::HitSensor* me, al::HitSensor* other) override;

    void exeStall();
    void exeFollow();
    void exeDeath();

    int stepSinceCaughtPlayer() const { return mStepSinceCaughtPlayer; }
};

} // namespace mg