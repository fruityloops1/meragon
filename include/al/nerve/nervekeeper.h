#pragma once

#include "al/nerve/nerve.h"
#include "types.h"

namespace al {

class Nerve;
class IUseNerve;

class NerveKeeper {
public:
    IUseNerve* mParent;

private:
    const al::Nerve* mEndNerve;
    const al::Nerve* mNerve;
    int mStep;
    sfill(0x8, gap);

public:
    void setNerve(const al::Nerve* nerve);
    void setNerve(const al::Nerve& nerve) { setNerve(&nerve); }
    inline int getStep() { return mStep; }
};

static_assert(sizeof(NerveKeeper) == 0x18, "");

} // namespace al