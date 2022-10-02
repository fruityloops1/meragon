#pragma once

#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/LiveActor.h"
#include "sead/prim/seadSafeString.h"

namespace al {

void initActor(LiveActor* actor, const ActorInitInfo& actorInitInfo);
void initActorWithArchiveName(LiveActor* actor, const ActorInitInfo& actorInitInfo, const sead::SafeString& archiveName, const char* subArchiveName);
void initMapPartsActor(LiveActor* actor, const al::ActorInitInfo& actorInitInfo);
void initCreateActorNoPlacementInfo(LiveActor* actor, const ActorInitInfo& actorInitInfo);
void initCreateActorWithPlacementInfo(LiveActor* actor, const ActorInitInfo& actorInitInfo);

} // namespace al