#pragma once
#include "types.h"

namespace al {

enum class SensorType : int {

};

class LiveActor;
class HitSensor {
    const char* mName { nullptr };
    SensorType mSensorType;
    u8 unk[0x20];

public:
    LiveActor* mHostActor = nullptr;

    inline const char* getName() { return mName; }
};

} // namespace al