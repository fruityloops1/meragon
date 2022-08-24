#pragma once

#include "al/nerve/NerveExecutor.h"
#include "al/scene/LayoutKit.h"
#include "al/scene/LiveActorKit.h"

namespace al {

struct IUseUnknown {
    virtual void* getUnknown() const = 0;
};

class Scene : public NerveExecutor, public IUseUnknown {
    void* mUnknown = nullptr;

public:
    LiveActorKit* mLiveActorKit = nullptr;

private:
    LayoutKit* mLayoutKit = nullptr;
    void* unk[6];
    bool mIsAlive = false;

public:
    Scene(const char* name);

    void* getUnknown() const override;
    virtual void appear();
    virtual void kill();
    virtual void init(/*SceneInitInfo& ?*/);
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