#pragma once

namespace al {

class HitSensor {
    const char* mName { nullptr };

public:
    inline const char* getName() { return mName; }
};

} // namespace al