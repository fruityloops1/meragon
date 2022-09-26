#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al {

void startAction(LiveActor* actor, const char* actionName);
const char* getActionName(const LiveActor* actor);

} // namespace al