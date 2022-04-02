#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/liveactor.h"
#include "sead/prim/seadSafeString.h"

namespace al {

// Actor Init Functions
void initActorWithArchiveName(LiveActor*, const ActorInitInfo&, const sead::SafeString& archiveName, const char*);
void initActor(LiveActor*, const ActorInitInfo&, uintptr_t, uintptr_t);
void initMapPartsActor(LiveActor*, const al::ActorInitInfo&);

void initCreateActorNoPlacementInfo(LiveActor*, const ActorInitInfo&);

void startAction(LiveActor*, const char* actionName, void*, void*);

} // namespace al