#pragma once

#include "al/nerve/NerveExecutor.h"

namespace al {

struct IUseUnknown {
    virtual void* getUnknown() const = 0;
};

class Scene : public NerveExecutor, public IUseUnknown {
    void* mUnknown = nullptr;
    void* unk[8];
    bool mIsAlive = false;

public:
    Scene(const char* name);

    void* getUnknown() const override;
    virtual void appear();
    virtual void kill();
    virtual void init(/*SceneInitInfo& ?*/);
    virtual void movement();
    virtual void control();
    virtual void unk1();
    virtual void unk2();
    virtual void unk3();
    virtual void unk4();
    virtual void unk5();
    virtual void unk6();
    virtual void unk7();
    virtual void gap1();
    virtual void unk8();
    virtual void unk9();
    virtual void unk10();
    virtual void gap2();
    virtual void gap3();
};

} // namespace al