#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al {

using CreateActorFunctionT = al::LiveActor* (*)(const char*);

template <typename T>
struct NameToCreator {
    const char* name;
    T create;
};

typedef NameToCreator<CreateActorFunctionT> NameToCreatorActor;

template <typename T>
LiveActor* createActorFunction(const char* name);

} // namespace al