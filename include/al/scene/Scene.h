#pragma once

#include "al/nerve/NerveExecutor.h"
#include "al/scene/CreatorClassNameTableHolder.h"
#include "al/scene/LayoutKit.h"
#include "al/scene/LiveActorKit.h"
#include "al/scene/SceneObjHolder.h"

namespace al {

class Scene : public NerveExecutor {
    void* mUnknown[2] { nullptr };

public:
    LiveActorKit* mLiveActorKit = nullptr;

private:
    LayoutKit* mLayoutKit = nullptr;
    SceneObjHolder* mSceneObjHolder = nullptr;
    CreatorClassNameTableHolder* mCCNTHolder = nullptr;
    void* unk[4];

public:
    bool mIsAlive = false;

    Scene(const char* name);

    virtual void appear();
    virtual void kill();
    virtual void init(/*SceneInitInfo& ?*/) = 0;
    virtual void movement();
    virtual void control();
    virtual void unk1(); // drawMain?
    virtual void unk2(); // drawSub?
    virtual void unk3();
    virtual void unk4();
    virtual void unk5();
    virtual void unk6();
    virtual void unk7();
    virtual void gap1();
    virtual void unk8();
    virtual void unk9(); // does draw/execute stuff
    virtual void unk10();
    virtual void gap2();
    virtual void gap3();
};

} // namespace al