#pragma once

#include "al/actor/liveactor.h"

namespace al {

/**
 * @brief Calculates the position of the joint relative to the world
 *
 * @param dst Pointer to translation to be set by the function
 * @param actor The actor whose model the joint is taken from
 * @param jointName The joint name in the model skeleton
 */
void calcJointPos(sead::Vector3f* dst, const al::LiveActor* actor, const char* jointName);

} // namespace al