#pragma once

#include "Game/Factory/CameraPoserFactory.h"
#include "al/Camera/CameraPoser.h"
#include "al/Factory/CameraPoserFactory.h"
#include "sead/basis/seadNew.h"
#include <type_traits>

namespace mg {

template <typename T>
al::CameraPoser* createCameraPoserFunction(const char* name)
{
    static_assert(std::is_base_of<al::CameraPoser, T>::value, "T must derive from al::CameraPoser");
    return new T(name);
}

al::CreateCameraPoserFunctionT getCameraPoserCreatorFromFactory(const char* className);

} // namespace mg
