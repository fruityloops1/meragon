#pragma once

#include "al/actor/actorinitinfo.h"
#include "al/actor/actorposekeeper.h"
#include "al/audio/audiokeeper.h"
#include "al/effect/effectkeeper.h"
#include "al/nerve/nerve.h"
#include "al/sensor/hitsensorkeeper.h"
#include "mg/efun.h"
#include "types.h"

namespace al {

/**
 * @brief Object in a scene that can move, be animated, be interacted with, etc.
 */
class LiveActor : public al::IUseNerve, public al::IUseEffectKeeper, public al::IUseAudioKeeper {
public:
    virtual NerveKeeper* getNerveKeeper() const override { return mNerveKeeper; };

    /**
     * @brief Called by the engine and manually by parent actors during Scene initialization
     * @param info See ActorInitInfo header
     * @param unk1 Unknown
     * @param unk2 Unknown
     */
    virtual void init(const ActorInitInfo& info, uintptr_t unk1, uintptr_t unk2);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void makeActorAlive();
    virtual void kill();
    virtual void makeActorDead();
    virtual void movement();
    virtual void unk1();
    virtual void gap1();
    virtual void startClipped();
    virtual void endClipped();
    virtual void unk2();
    virtual bool receiveMsg();
    virtual void unk3();
    virtual EffectKeeper* getEffectKeeper() const override { return mEffectKeeper; };
    virtual AudioKeeper* getAudioKeeper() const override { return mAudioKeeper; };
    virtual void gap2();
    virtual void gap3();
    /**
     * @brief Called every frame the actor is alive
     */
    virtual void control();
    virtual void gap4();
    virtual void unk4();

    LiveActor(const char* name);

private:
    sfill(0x4, iusenerve);
    const char* mActorName;

protected:
    ActorPoseKeeperBase* mActorPoseKeeper = nullptr;
    void* keeper18 = nullptr;
    void* mActorActionKeeper = nullptr;
    void* keeper20 = nullptr;
    void* keeper24 = nullptr;
    void* keeper28 = nullptr;
    NerveKeeper* mNerveKeeper = nullptr;
    HitSensorKeeper* mHitSensorKeeper = nullptr;
    EffectKeeper* mEffectKeeper = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    void* keeper3C = nullptr;
    void* keeper40 = nullptr;
    void* keeper44 = nullptr;
    void* keeper48 = nullptr;
    void* keeper4C = nullptr;
    void* keeper50 = nullptr;

private:
    /**
     * @brief Different boolean flags used by the actor internally
     */
    struct LiveActorFlag {
        bool isDead = true;
        bool flag2 = false;
        bool flag3 = true;
        bool flag4 = false;
        bool flag5 = false;
        bool flag6 = false;
        bool flag7 = true;
        bool flag8 = false;
        bool flag9 = false;
    } mLiveActorFlag;
};

static_assert(sizeof(LiveActor) == 0x60, "");

} // namespace al