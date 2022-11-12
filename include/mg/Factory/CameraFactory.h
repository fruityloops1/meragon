#pragma once

#include "Game/Factory/CameraFactory.h"
#include "al/Camera/Camera.h"
#include "al/Factory/CameraFactory.h"
#include "sead/basis/seadNew.h"
#include <type_traits>

namespace mg {

template <typename T>
al::Camera* createCameraPoserFunction(const char* name)
{
    static_assert(std::is_base_of<al::Camera, T>::value, "T must derive from al::CameraPoser");
    return new T(name);
}

al::CreateCameraFuncPtr getCameraPoserCreatorFromFactory(const char* className);

} // namespace mg
