#pragma once

#include "al/Camera/CameraPoser.h"
#include "al/Factory/Factory.h"

namespace al {

using CreateCameraPoserFunctionT = al::CameraPoser* (*)(const char*);
using NameToCreatorCameraPoser = NameToCreator<CreateCameraPoserFunctionT>;

template <typename T>
CreateCameraPoserFunctionT* createCameraPoserFunction(const char* name);

} // namespace al