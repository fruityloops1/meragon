#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/Npc/BreakModel.h"

namespace mg {

class ExampleActor : public al::LiveActor {
    al::BreakModel* mBreakEffectActor = nullptr;

public:
    ExampleActor(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    bool receiveMsg(u32 msg, al::HitSensor* other, al::HitSensor* me) override;

    void exeWait();
    void exeBreak();
};

} // namespace mg
