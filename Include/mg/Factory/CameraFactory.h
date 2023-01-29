#pragma once

#include "al/Camera/Camera.h"
#include "al/Factory/CameraFactory.h"
#include "sead/basis/seadNew.h"
// #include <type_traits>

// Camera stubs

class CameraPoserParallel;
class CameraPoserTower;
class CameraPoserFixAll;
class CameraPoserFixPos;
class CameraPoserFixPosSpot;
class CameraPoserFixAllSpot;
class CameraPoserFollow;
class CameraPoserRail;
class CameraPoserRailTower;
class CameraPoserParallelTarget;
class CameraPoserParallelVersus;
class CameraPoserDemoTarget;
class CameraPoserTowerTarget;
class CameraPoserProgramable;
class CameraPoserAnim;

const extern al::NameToCameraCreator sCameraPoserFactoryEntries[15];

namespace mg {

template <typename T>
al::Camera* createCameraFunction(const char* name)
{
    // static_assert(std::is_base_of<al::Camera, T>::value, "T must derive from al::Camera");
    return new T(name);
}

al::CreateCameraFuncPtr getCameraCreatorFromFactory(const char* className);

} // namespace mg
