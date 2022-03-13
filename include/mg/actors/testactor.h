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

    void init(const al::ActorInitInfo& info) override;
    void exeWait();
};

namespace {
    NERVE_HEADER(TestActor, Wait);
}

} // namespace mg