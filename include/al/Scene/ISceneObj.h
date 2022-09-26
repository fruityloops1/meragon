#pragma once

namespace al {

class ISceneObj {
public:
    virtual const char* getSceneObjName();
    virtual void initAfterPlacementSceneObj();
    virtual void initSceneObj();
};

} // namespace al