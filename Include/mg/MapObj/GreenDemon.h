#pragma once

#include "Game/Player/PlayerActor.h"
#include "al/LiveActor/LiveActor.h"

namespace mg {

class GreenDemon : public al::LiveActor {
    PlayerActor* const mPlayer = nullptr;
    int mStepSinceCaughtPlayer = 0;
    int mStuckFrames = 0;
    float mMoveAvg = 0;
    int mAvgCount = 0;
    sead::Vector3f mPrevPos;
    bool mDoTpToPlayerRepeat = false;

    bool checkForbidden();

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

extern PlayerActionNode* sDeathNode;
