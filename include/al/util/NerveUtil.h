#pragma once

#include "al/actor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

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

void initNerve(LiveActor* actor, const al::Nerve* nerve, int unk);

void setNerve(IUseNerve* p, const al::Nerve* nerve);
bool isNerve(const IUseNerve* p, const al::Nerve* nerve);

inline void setNerve(IUseNerve* i, const al::Nerve& nerve) { setNerve(i, &nerve); }
inline bool isNerve(IUseNerve* i, const al::Nerve& nerve) { return isNerve(i, &nerve); }
inline int getNerveStep(IUseNerve* i) { return i->getNerveKeeper()->getStep(); }
inline bool isFirstStep(IUseNerve* i) { return i->getNerveKeeper()->getStep() == 0; }
inline bool isLessStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() < step; }
inline bool isGreaterStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() > step; }
inline bool isStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() == step; }

} // namespace al