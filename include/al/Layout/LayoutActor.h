#pragma once

#include "al/Layout/LayoutInitInfo.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveKeeper.h"
#include "sead/basis/seadTypes.h"
#include "sead/prim/seadSafeString.h"

namespace al {

class IUseSomething {
    virtual void dummy() {};
    virtual void dummy2() {};

public:
    virtual void* getSomething() const = 0;
};

class LayoutActor : public al::IUseNerve, public al::IUseSomething {
public:
    LayoutActor(const char* name);

    virtual NerveKeeper* getNerveKeeper() const override { return mNerveKeeper; };
    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void calcAnim();

private:
    virtual void gap();

public:
    void* getSomething() const override { return mSomething; };
    virtual void control();

    void initNerve(const al::Nerve* nerve, int);

protected:
    sead::SafeString mName;
    NerveKeeper* mNerveKeeper = nullptr;
    void* _18 = nullptr;
    void* mSomething = nullptr;
    void* _1C = nullptr;
    void* _20 = nullptr;
    void* _24 = nullptr;
    void* _28 = nullptr;
    bool mIsAlive = false;
};

void initLayoutActor(al::LayoutActor* layoutActor, const LayoutInitInfo& info, const char* archiveName, const char*);

void startAction(al::LayoutActor* actor, const sead::SafeString& actionName);

void setPaneString(LayoutActor* actor, const char* paneName, const char16* text);
void hidePane(LayoutActor* actor, const char* paneName);

} // namespace al