#pragma once

#include "types.h"

namespace al {

struct Nerve;
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
    const al::Nerve* getCurrentNerve();
    void update();
    void setNerve(const al::Nerve* nerve);
    inline int getStep() { return mStep; }
};

class IUseNerve {
public:
    virtual NerveKeeper* getNerveKeeper() const = 0;
};

static_assert(sizeof(NerveKeeper) == 0x18, "");

} // namespace al