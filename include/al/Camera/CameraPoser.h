#pragma once

#include "al/System/Byaml/ByamlIter.h"
#include "sead/math/seadVector.h"

namespace al {

class CameraPoser {
    const char* mName = nullptr;
    int unk1[3];
    sead::Vector3f mCameraAt;
    sead::Vector3f mCameraTarget;
    sead::Vector3f unk2;
    int mInterpoleFrame;
    u8 unk3[0x10];

public:
    CameraPoser(const char* name);

    virtual void load(ByamlIter* ticket);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void update();
    virtual void v7();
};

} // namespace al