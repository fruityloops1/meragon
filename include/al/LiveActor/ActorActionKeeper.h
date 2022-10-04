#pragma once

namespace al {

class LiveActor;

class ActorActionKeeper { };

void startAction(LiveActor* actor, const char* actionName);
bool isActionEnd(const LiveActor* actor);
const char* getActionName(const LiveActor* actor);

} // namespace al