#pragma once

#include "Game/Sequence/ProductSequence.h"
#include "sead/math/seadVector.h"

namespace mg {

void updateFreecam();
const sead::Vector3f& getFreecamOffset();

} // namespace mg