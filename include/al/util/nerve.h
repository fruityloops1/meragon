#pragma once

#include "al/actor/liveactor.h"
#include "al/nerve/nerve.h"
#include "al/nerve/nervekeeper.h"

/**
 * @brief Adds a usable nerve for a LiveActor as a global variable. Always in anonymous namespaces
 * @param CLASS Class the nerve is defined in
 * @param ACTION Name of the execution function suffix (e.g. Wait = void CLASS::exeWait())
 */
#define NERVE_DEF(CLASS, ACTION)                                    \
    struct CLASS##Nrv##ACTION : public al::Nerve {                  \
        inline void execute(al::NerveKeeper* keeper) const override \
        {                                                           \
            static_cast<CLASS*>(keeper->mParent)->exe##ACTION();    \
        }                                                           \
    };                                                              \
    const CLASS##Nrv##ACTION nrv##CLASS##ACTION;

/**
 * @brief Same as NERVE_DEF, but defines the executeOnEnd action too.
 * @param CLASS Class the nerve is defined in
 * @param ACTION Name of the execution function suffix (e.g. Wait = void CLASS::exeWait())
 * @param ENDACTION Name of the end execution function
 */
#define NERVE_DEF_END(CLASS, ACTION, ENDACTION)                          \
    struct CLASS##Nrv##ACTION : public al::Nerve {                       \
        inline void execute(al::NerveKeeper* keeper) const override      \
        {                                                                \
            static_cast<CLASS*>(keeper->mParent)->exe##ACTION();         \
        }                                                                \
        inline void executeOnEnd(al::NerveKeeper* keeper) const override \
        {                                                                \
            static_cast<CLASS*>(keeper->mParent)->exe##ENDACTION();      \
        }                                                                \
    };                                                                   \
    const CLASS##Nrv##ACTION nrv##CLASS##ACTION;

namespace al {

/**
 * @brief Initialize the NerveKeeper of an actor with a nerve
 * @param actor Actor
 * @param nerve Nerve to be initialized with
 * @param unk Initializes NerveStateCtrl if unk > 0
 */
void initNerve(LiveActor* actor, const al::Nerve* nerve, int unk);

/**
 * @brief Calls NerveKeeper::setNerve
 */
void setNerve(IUseNerve* p, const al::Nerve* nerve);
/**
 * @brief Checks if the active of p nerve equals nerve
 *
 * @param p NerveKeeper to check on
 * @param nerve The nerve to check for
 */
bool isNerve(const IUseNerve* p, const al::Nerve* nerve);

inline void setNerve(IUseNerve* i, const al::Nerve& nerve) { setNerve(i, &nerve); }
inline bool isNerve(IUseNerve* i, const al::Nerve& nerve) { return isNerve(i, &nerve); }
inline int getNerveStep(IUseNerve* i) { return i->getNerveKeeper()->getStep(); }
inline bool isFirstStep(IUseNerve* i) { return i->getNerveKeeper()->getStep() == 0; }
inline bool isLessStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() < step; }
inline bool isGreaterStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() > step; }
inline bool isStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() == step; }

} // namespace al