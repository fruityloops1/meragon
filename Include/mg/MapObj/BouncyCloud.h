#pragma once

#include "al/LiveActor/LiveActor.h"

namespace mg {

// credit: trippi
// TODO: groundpound removes cloud temporarily with effect

class BouncyCloud : public al::LiveActor {
    float pWaitRange = 50; // how far to bob up and down
    float pSpeedMultiplier = 3; // how fast
    float pReactionOffset = 80;
    float pReactionMoveTime = 20;

    float mInitialY = 0;
    int mLerpTime = 10;

    bool mIsOnGround = false;

public:
    BouncyCloud(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    bool receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me) override;
    void control() override;

    void exeWait();
    void exeReaction();
    void exeReactionMoveDown();
    void exeReactionMoveUp();

    float calcBobbing(float offset = 0) const;
    void calcAndSetBobbing(float offset = 0);
};

} // namespace mg
