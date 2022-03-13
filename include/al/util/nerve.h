#pragma once

#include "al/nerve/nerve.h"
#include "al/nerve/nervekeeper.h"

#define NERVE_HEADER(CLASS, ACTION)               \
    class CLASS##Nrv##ACTION : public al::Nerve { \
        void execute(al::NerveKeeper*) override;  \
    };                                            \
    CLASS##Nrv##ACTION nrv##CLASS##ACTION;

#define NERVE_IMPL(CLASS, ACTION)                             \
    void CLASS##Nrv##ACTION::execute(al::NerveKeeper* keeper) \
    {                                                         \
        static_cast<CLASS*>(keeper->mParent)->exe##ACTION();  \
    }
