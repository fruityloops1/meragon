#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "sead/prim/seadSafeString.h"

namespace al {

/**
 * @brief Initializes an actor with a hard archive in ObjectData
 *
 * @param actor The actor to be initialized
 * @param actorInitInfo The ActorInitInfo got in LiveActor::init
 * @param archiveName Name of the archive to init the actor from without a file extension
 * @param subArchiveName If not nullptr, the name of the subactor inside that archive to init from (e.g. "Foo" = InitActor_Foo.byml)
 */
void initActorWithArchiveName(LiveActor* actor, const ActorInitInfo& actorInitInfo, const sead::SafeString& archiveName, const char* subArchiveName);

/**
 * @brief Initializes an actor using the archive bound in the PlacementInfo name
 *
 * @param actor The actor to be initialized
 * @param actorInitInfo The ActorInitInfo got in LiveActor::init
 * @param unk1 Unknown pointer. Can be nullptr
 * @param unk2 Unknown pointer. Can be nullptr
 */
void initActor(LiveActor* actor, const ActorInitInfo& actorInitInfo, uintptr_t unk1, uintptr_t unk2);

/**
 * @brief Like initActor, but optimized to only initialize components importants for MapPart actors
 *
 * @param actor The actor to be initialized
 * @param actorInitInfo The ActorInitInfo got in LiveActor::init
 */
void initMapPartsActor(LiveActor* actor, const al::ActorInitInfo& actorInitInfo);

/**
 * @brief Initializes an actor without assumptions made from its PlacementInfo
 *
 * @param actor The actor to be initialized
 * @param actorInitInfo The ActorInitInfo got in LiveActor::init
 */
void initCreateActorNoPlacementInfo(LiveActor* actor, const ActorInitInfo& actorInitInfo);

} // namespace al