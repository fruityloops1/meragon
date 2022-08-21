#pragma once

#include "al/actor/LiveActor.h"

namespace al {

/**
 * @brief Binds a name to a function that returns a pointer to an object. Commonly used in factories
 *
 * @tparam T Function Pointer type of the creation function
 */
template <typename T>
struct NameToCreator {
    const char* name;
    T create;
};

typedef NameToCreator<al::LiveActor* (*)(const char*)> NameToCreatorActor;

/**
 * @brief Allocate and create an actor of type T
 *
 * @tparam T Type of actor. Must be derived from al::LiveActor
 * @param name Actor name passed to its constructor
 * @return LiveActor* Upcasted pointer to the newly created Actor
 */
template <typename T>
LiveActor* createActorFunction(const char* name);

} // namespace al