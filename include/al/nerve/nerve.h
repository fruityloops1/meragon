#pragma once

#include "al/nerve/nervekeeper.h"

namespace al {

class NerveKeeper;

class IUseNerve {
    virtual NerveKeeper* getNerveKeeper() const = 0;
};

struct Nerve {
    virtual void execute(NerveKeeper*) const = 0;
    virtual void executeOnEnd(NerveKeeper*) const {};
};

} // namespace al