#pragma once

#include "al/actor/liveactor.h"
#include "al/nerve/nervekeeper.h"

#define NERVE_DEF(CLASS, ACTION)                                    \
    struct CLASS##Nrv##ACTION : public al::Nerve {                  \
        inline void execute(al::NerveKeeper* keeper) const override \
        {                                                           \
            static_cast<CLASS*>(keeper->mParent)->exe##ACTION();    \
        }                                                           \
    };                                                              \
    const CLASS##Nrv##ACTION nrv##CLASS##ACTION;

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

void initNerve(LiveActor*, const al::Nerve*, int);
inline void setNerve(IUseNerve* i, const al::Nerve& nerve) { i->getNerveKeeper()->setNerve(&nerve); }
inline bool isFirstStep(IUseNerve* i) { return i->getNerveKeeper()->getStep() == 0; }
inline bool isStep(IUseNerve* i, int step) { return i->getNerveKeeper()->getStep() == step; }

} // namespace al