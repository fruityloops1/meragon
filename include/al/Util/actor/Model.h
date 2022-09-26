#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al {

void calcJointPos(sead::Vector3f* dst, const al::LiveActor* actor, const char* jointName);

} // namespace al