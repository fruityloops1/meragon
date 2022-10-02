#pragma once

#include "al/Factory/Factory.h"

namespace al {

using CreateActorFunctionT = al::LiveActor* (*)(const char*);
using NameToCreatorActor = NameToCreator<CreateActorFunctionT>;

template <typename T>
LiveActor* createActorFunction(const char* name);

} // namespace al