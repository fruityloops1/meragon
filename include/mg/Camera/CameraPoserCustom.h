#pragma once

#include "al/Camera/CameraPoser.h"
#include "al/System/Byaml/ByamlIter.h"

namespace mg {

class CameraPoserCustom : public al::CameraPoser {
public:
    CameraPoserCustom(const char* name)
        : CameraPoser(name)
    {
    }

    void load(const al::ByamlIter* ticket) override;
    void update() override;
};

} // namespace mg