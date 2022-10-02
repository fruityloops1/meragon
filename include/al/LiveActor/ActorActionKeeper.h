#pragma once

namespace al {

class LiveActor;

class ActorActionKeeper { };

void startAction(LiveActor* actor, const char* actionName);
const char* getActionName(const LiveActor* actor);

} // namespace al