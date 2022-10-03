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

void setNerve(IUseNerve* p, const al::Nerve* nerve);
bool isNerve(const IUseNerve* p, const al::Nerve* nerve);

inline void setNerve(IUseNerve* i, const al::Nerve& nerve) { setNerve(i, &nerve); }
inline bool isNerve(IUseNerve* i, const al::Nerve& nerve) { return isNerve(i, &nerve); }
inline int getNerveStep(IUseNerve* i) { return i->getNerveKeeper()->getStep(); }
bool isFirstStep(IUseNerve* i);
inline bool isLessStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() < step; }
inline bool isGreaterStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() > step; }
inline bool isStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() == step; }

} // namespace al