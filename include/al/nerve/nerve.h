#pragma once

class NerveKeeper;

namespace al {

class IUseNerve {
public:
    virtual NerveKeeper* getNerveKeeper() const = 0;
};

class Nerve {
    virtual void execute(NerveKeeper*) = 0;
    virtual void executeOnEnd(NerveKeeper*) const;
};

} // namespace al