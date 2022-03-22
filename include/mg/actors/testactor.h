#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "al/util/nerve.h"

namespace mg {

class TestActor : public al::LiveActor {
public:
    TestActor(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info, uintptr_t, uintptr_t) override;
    void exeWait();
    void exeFlip();
    void control() override;

    int mMoveFrames = 0;
    bool mMoveDir = true;
};

namespace {
    NERVE_DEF(TestActor, Wait);
    NERVE_DEF(TestActor, Flip);
}

} // namespace mg