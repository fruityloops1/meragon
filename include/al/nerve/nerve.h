#pragma once

#include "al/nerve/nervekeeper.h"

namespace al {

class NerveKeeper;

/**
 * @brief Interface for classes that use the Nerve system
 */
class IUseNerve {
public:
    virtual NerveKeeper* getNerveKeeper() const = 0;
};

/**
 * @brief Similar to an animation, but instead of Bones moving it's code running
 * Only 1 nerve can be active at once, and it is usually bound to an Action
 * Nerves are practically always made using a macro (NERVE_DEF)
 */
struct Nerve {
    /**
     * @brief Code to be executed every frame this current nerve is active
     */
    virtual void execute(NerveKeeper* nerveKeeper) const = 0;
    /**
     * @brief Code to be executed on the last frame this nerve is run, right when another one is being activated
     */
    virtual void executeOnEnd(NerveKeeper* nerveKeeper) const {};
};

} // namespace al