#pragma once

#include "al/nerve/nerve.h"
#include "types.h"

namespace al {

class Nerve;
class IUseNerve;

/**
 * @brief Class that manages the nerve system
 */
class NerveKeeper {
public:
    IUseNerve* mParent;

private:
    const al::Nerve* mEndNerve;
    const al::Nerve* mNerve; // current active nerve
    int mStep; // how many frames the active nerve has been running for
    sfill(0x8, gap);

public:
    /**
     * @brief Activates a nerve and sets the step to 0. Calls executeOnEnd for the previous nerve
     * @param nerve The nerve to be activated
     */
    void setNerve(const al::Nerve* nerve);
    void setNerve(const al::Nerve& nerve) { setNerve(&nerve); } // fake
    inline int getStep() { return mStep; }
};

static_assert(sizeof(NerveKeeper) == 0x18, "");

} // namespace al