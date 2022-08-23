#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/actor/LiveActor.h"
#include "sead/prim/seadSafeString.h"

namespace al {

void initActor(LiveActor* actor, const ActorInitInfo& actorInitInfo);
void initActorWithArchiveName(LiveActor* actor, const ActorInitInfo& actorInitInfo, const sead::SafeString& archiveName, const char* subArchiveName);
void initMapPartsActor(LiveActor* actor, const al::ActorInitInfo& actorInitInfo);
void initCreateActorNoPlacementInfo(LiveActor* actor, const ActorInitInfo& actorInitInfo);

} // namespace al