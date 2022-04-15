#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "al/util/nerve.h"

namespace mg {

class GabonThrowObj : public al::LiveActor {

    const char* const mThrowObjModelName { nullptr };

public:
    GabonThrowObj(const char* name, const char* throwObjModelName)
        : LiveActor(name)
        , mThrowObjModelName(throwObjModelName)
    {
    }

    void init(const al::ActorInitInfo& info, uintptr_t, uintptr_t) override;
    void attackSensor(al::HitSensor* source, al::HitSensor* target) override;

    void exeGenerate();
    void exeGround();
    friend class Gabon;
};

class Gabon : public al::LiveActor {

    constexpr static int sNeedleRollerAmount = 6;

    int mThrowInterval = 90;
    int mThrowIndex = 0;
    GabonThrowObj* mNeedleRollers[sNeedleRollerAmount] { nullptr };
    GabonThrowObj* mCurRoller = nullptr;

public:
    Gabon(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info, uintptr_t, uintptr_t) override;
    void attackSensor(al::HitSensor* source, al::HitSensor* target) override;

    void exeWait();
    void exeThrowSign();
    void exeThrow();
};

namespace {

    constexpr int sAnimCountThrowSign = 70; // fix with al::isActionEnd
    constexpr int sAnimCountThrow = 21; // "

    NERVE_DEF(Gabon, Wait);
    NERVE_DEF(Gabon, ThrowSign);
    NERVE_DEF(Gabon, Throw);

    NERVE_DEF(GabonThrowObj, Generate);
    NERVE_DEF(GabonThrowObj, Ground);
}

} // namespace mg