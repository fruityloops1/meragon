#pragma once

#include "Game/Factory/ActorFactory.h"
#include "al/Factory/ActorFactory.h"
#include "sead/basis/seadNew.h"
// #include <type_traits>

namespace mg {

template <typename T>
al::LiveActor* createActorFunction(const char* name)
{
    // static_assert(std::is_base_of<al::LiveActor, T>::value, "T must derive from al::LiveActor");
    return new T(name);
}

al::CreateActorFuncPtr getActorCreatorFromFactory(const char* className);
al::CreateActorFuncPtr getCreatorHook(al::ActorFactory* thisPtr, const char* objectName);

} // namespace mg