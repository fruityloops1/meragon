#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/actorposekeeper.h"
#include "al/nerve/nerve.h"
#include "types.h"

namespace al {

class LiveActor : public al::IUseNerve {
public:
    virtual NerveKeeper* getNerveKeeper() const override { return mNerveKeeper; }
    virtual void init(const ActorInitInfo& info);
    virtual void initAfterPlacement();
    virtual void appear() { makeActorAlive(); }
    virtual void makeActorAlive();
    virtual void kill() { makeActorDead(); }
    virtual void makeActorDead();
    virtual void movement();
    virtual void unk1();
    virtual void gap1();
    virtual void startClipped();
    virtual void endClipped();
    virtual void unk2();
    virtual bool receiveMsg();
    virtual void unk3();
    virtual void* get34() { return _34; }
    virtual void* get38() { return _38; }
    virtual void gap2();
    virtual void gap3();

    LiveActor(const char* name);

private:
    sfill(0xA, gap);
    const char* mActorName;
    ActorPoseKeeperBase* mActorPoseKeeper = nullptr;
    void* _18 = nullptr;
    void* _1C = nullptr;
    void* _20 = nullptr;
    void* _24 = nullptr;
    void* _28 = nullptr;
    NerveKeeper* mNerveKeeper = nullptr;
    void* _30 = nullptr;
    void* _34 = nullptr;
    void* _38 = nullptr;
    void* _3C = nullptr;
    void* _40 = nullptr;
    void* _44 = nullptr;
    void* _48 = nullptr;
    void* _4C = nullptr;
    void* _50 = nullptr;
    sfill(0xC, gap2);
};

static_assert(sizeof(LiveActor) == 0x60, "");

} // namespace al