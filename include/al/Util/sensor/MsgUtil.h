#pragma once

#include "al/LiveActor/HitSensor.h"

namespace al {

void sendMsgEnemyAttack(HitSensor* source, HitSensor* target);

bool isSensorPlayer(const al::HitSensor* sensor);

} // namespace