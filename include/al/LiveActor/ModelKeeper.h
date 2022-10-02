#pragma once

#include "sead/math/seadVector.h"

namespace al {

class LiveActor;

class ModelKeeper { };

void calcJointPos(sead::Vector3f* dst, const al::LiveActor* actor, const char* jointName);

} // namespace al