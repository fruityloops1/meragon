#pragma once

#include "al/Nerve/NerveExecutor.h"

namespace al {

class NerveStateBase : public NerveExecutor {
    bool mIsDead = true;

public:
    NerveStateBase(const char* name);

    virtual void init();
    virtual void appear();
    virtual void kill();
    virtual bool update();
    virtual void control();
};

void initNerveState(IUseNerve*, NerveStateBase* state, const Nerve* stateNrv, const char* name);
bool updateNerveState(IUseNerve*); // returns if nerve state is dead

} // namespace al