#pragma once

#include "al/Factory/CameraPoserFactory.h"

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

const extern al::NameToCreatorCameraPoser sCameraPoserFactoryEntries[15];