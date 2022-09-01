#pragma once

#include "al/scene/ISceneObj.h"
namespace al {

class SceneObjHolder {
public:
    SceneObjHolder(ISceneObj* (*createFunction)(int id), int size);
};

} // namespace al