#pragma once

#include "al/actor/liveactor.h"

namespace al {

template <typename T>
struct NameToCreator {
    const char* name;
    T create;
};

typedef NameToCreator<al::LiveActor* (*)(const char*)> NameToCreatorActor;

template <typename T>
LiveActor* createActorFunction(const char* name);

} // namespace al