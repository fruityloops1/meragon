#pragma once

#include "al/Camera/Camera.h"
#include "al/System/Byaml/ByamlIter.h"

namespace mg {

class CameraCustom : public al::Camera {
public:
    CameraCustom(const char* name)
        : Camera(name)
    {
    }

    void load(const al::ByamlIter* ticket) override;
    void calc() override;
};

} // namespace mg