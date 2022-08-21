#pragma once

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"
#include "sead/prim/seadSafeString.h"

namespace al {

class IUseSomething {
    virtual void dummy() {};
    virtual void dummy2() {};

public:
    virtual void* getSomething() const = 0;
};

class LayoutActor : public al::IUseSomething, public al::IUseNerve {
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
    virtual void* getSomething() const override { return mSomething; };
    virtual void control();

    void initNerve(const al::Nerve* nerve, int);

protected:
    sead::SafeString mName;
    NerveKeeper* mNerveKeeper = nullptr;
    void* _18 = nullptr;
    void* mSomething = nullptr;
    void* _20 = nullptr;
    void* _24 = nullptr;
    void* _28 = nullptr;
    bool mIsAlive = false;
};

} // namespace al