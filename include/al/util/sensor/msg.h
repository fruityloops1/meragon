#pragma once

#include "al/sensor/hitsensor.h"

namespace al {

void sendMsgEnemyAttack(HitSensor* source, HitSensor* target);

bool isSensorPlayer(const al::HitSensor* sensor);

} // namespace