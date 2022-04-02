#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "al/util/nerve.h"

namespace mg {

class MagicBall : public al::LiveActor {
public:
    MagicBall(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info, uintptr_t, uintptr_t) override;
    void exeWait();

    void control() override;

    friend class TestActor;
};

class TestActor : public al::LiveActor {
    MagicBall* mMagicBalls[5] { nullptr };
    int mDropIndex = 0;

public:
    TestActor(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info, uintptr_t, uintptr_t) override;
    void exeWait();
    void exeDrop();
    void control() override;
};

namespace {
    NERVE_DEF(TestActor, Wait);
    NERVE_DEF(TestActor, Drop);

    NERVE_DEF(MagicBall, Wait);
}

} // namespace mg