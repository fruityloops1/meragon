#pragma once

#include "al/nerve/nerve.h"

namespace al {

class Nerve;
class IUseNerve;

class NerveKeeper {
    void setNerve(const al::Nerve*);

public:
    IUseNerve* mParent;
    const al::Nerve* unkNerve;
    const al::Nerve* mNerve;
    int mStep;
};

} // namespace al