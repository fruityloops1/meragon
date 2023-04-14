#pragma once

#include "Game/Enemy/EnemyStateBlowDown.h"
#include "al/LiveActor/LiveActor.h"

namespace mg {

class GabonThrowObj : public al::LiveActor {
    const char* const mThrowObjModelName { nullptr };
    const sead::Vector3f mDirection;
    sead::Vector3f mSideVec;

public:
    GabonThrowObj(const char* name, const char* throwObjModelName, const sead::Vector3f& direction)
        : LiveActor(name)
        , mThrowObjModelName(throwObjModelName)
        , mDirection(direction)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    void kill() override;
    void attackSensor(al::HitSensor* me, al::HitSensor* other) override;

    void exeGenerate();
    void exeGround();
    void exeBreak();
    friend class Gabon;
};

class Gabon : public al::LiveActor {

    constexpr static int sNeedleRollerAmount = 6;

    int mThrowInterval = 90;
    int mThrowIndex = 0;
    GabonThrowObj* mNeedleRollers[sNeedleRollerAmount] { nullptr };
    GabonThrowObj* mCurRoller = nullptr;
    EnemyStateBlowDown* mStateBlowDown = nullptr;

public:
    Gabon(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    void kill() override;
    void attackSensor(al::HitSensor* me, al::HitSensor* other) override;
    bool receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me) override;
    void control() override;

    void exeWait();
    void exeThrowSign();
    void exeThrow();
    void exeBlowDown();
    void exePressDown();
};

namespace {

    constexpr int sAnimCountThrowSign = 70; // fix with al::isActionEnd
    constexpr int sAnimCountThrow = 21; // "
    constexpr int sAnimCountPressDown = 22; // "
}

} // namespace mg