#pragma once

#include "al/LiveActor/HitSensor.h"
#include "sead/math/seadQuat.h"

namespace al {

bool isSensorName(HitSensor* sensor, const char* name);

bool isHitCylinderSensor(HitSensor*, HitSensor*, const sead::Vector3f&, float);

} // namespace al