#pragma once

#include "al/Factory/ActorFactory.h"
#include "game/Factory/ActorFactory.h"
#include "mg/MapObj/Gabon.h"
#include "sead/basis/seadNew.h"
#include <type_traits>

namespace mg {

template <typename T>
al::LiveActor* createActorFunction(const char* name)
{
    static_assert(std::is_base_of<al::LiveActor, T>::value, "T must derive from al::LiveActor");
    return new T(name);
}

void initCustomActorFactory();
al::CreateActorFunctionT getActorCreatorFromFactory(const char* className);
} // namespace mg
