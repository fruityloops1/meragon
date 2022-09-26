#pragma once

#include "al/Scene/ISceneObj.h"

namespace al {

class SceneObjHolder {
public:
    using CreateFunction = ISceneObj* (*)(int id);

private:
    CreateFunction mCreateFunction = nullptr;
    ISceneObj** mObjs = nullptr;
    int mSize = 0;

public:
    SceneObjHolder(CreateFunction func, int size);
    ISceneObj* getObj(int id);
};

SceneObjHolder* getSceneObjHolder();
ISceneObj* getSceneObj(int id);
void setSceneObj(ISceneObj* obj, int id);

} // namespace al