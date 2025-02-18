#pragma once

#include <sead/gfx/seadDrawLockContext.h>
#include <sead/heap/seadDisposer.h>

namespace sead {

class Graphics : public IDisposer {
    using UnknownCallback = void (*)(int);
    static Graphics* sInstance;

public:
    enum DevicePosture {
        cDevicePosture_Same = 0,
        cDevicePosture_RotateRight = 1,
        cDevicePosture_RotateLeft = 2,
        cDevicePosture_RotateHalfAround = 3,
        cDevicePosture_FlipX = 4,
        cDevicePosture_FlipY = 5,
        cDevicePosture_FlipXY = 3,
        cDevicePosture_Invalid = 4,
    };

    void lockDrawContext();
    void unlockDrawContext();
    void initHostIO();
    void initializeDrawLockContext(Heap*);

    static Graphics* instance() { return sInstance; }

private:
    UnknownCallback _20;
    DrawLockContext* mDrawLockContext;
};

} // namespace sead
