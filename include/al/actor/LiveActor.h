#pragma once

#include "al/actor/ActorActionKeeper.h"
#include "al/actor/ActorExecuteInfo.h"
#include "al/actor/ActorInitInfo.h"
#include "al/actor/ActorPoseKeeper.h"
#include "al/actor/SubActorKeeper.h"
#include "al/audio/AudioKeeper.h"
#include "al/collision/Collider.h"
#include "al/collision/CollisionParts.h"
#include "al/effect/EffectKeeper.h"
#include "al/model/ModelKeeper.h"
#include "al/nerve/Nerve.h"
#include "al/sensor/HitSensor.h"
#include "al/sensor/HitSensorKeeper.h"
#include "sead/math/seadMatrix.h"
#include "types.h"

namespace al {

class LiveActor : public al::IUseNerve, public al::IUseEffectKeeper, public al::IUseAudioKeeper {
public:
    virtual NerveKeeper* getNerveKeeper() const override { return mNerveKeeper; };

    virtual void init(const ActorInitInfo& info);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void makeActorAppeared();
    virtual void kill();
    virtual void makeActorDead();
    virtual void movement();
    virtual void calcAnim();
    virtual void draw();
    virtual void startClipped();
    virtual void endClipped();
    virtual void attackSensor(HitSensor* target, HitSensor* source);
    virtual bool receiveMsg();
    virtual sead::Matrix34f* getBaseMtx() const;
    virtual EffectKeeper* getEffectKeeper() const override { return mEffectKeeper; };
    virtual AudioKeeper* getAudioKeeper() const override { return mAudioKeeper; };
    virtual void gap2();
    virtual void gap3();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void updateCollider();

    LiveActor(const char* name);

private:
    sfill(0x4, iusenerve);
    const char* mActorName;

protected:
    ActorPoseKeeperBase* mActorPoseKeeper = nullptr;
    ActorExecuteInfo* mActorExecuteInfo = nullptr;
    ActorActionKeeper* mActorActionKeeper = nullptr;
    Collider* mCollider = nullptr;
    CollisionParts* mCollisionParts = nullptr;
    ModelKeeper* mModelKeeper = nullptr;
    NerveKeeper* mNerveKeeper = nullptr;
    HitSensorKeeper* mHitSensorKeeper = nullptr;
    EffectKeeper* mEffectKeeper = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    void* keeper3C = nullptr;
    void* keeper40 = nullptr;
    void* keeper44 = nullptr;
    void* keeper48 = nullptr;
    void* keeper4C = nullptr;
    SubActorKeeper* mSubActorKeeper = nullptr;

private:
    struct LiveActorFlag {
        bool isDead = true;
        bool isClipped = false;
        bool flag3 = true;
        bool flag4 = false;
        bool flag5 = false;
        bool isHideModel = false;
        bool flag7 = true;
        bool flag8 = false;
        bool flag9 = false;
    } mLiveActorFlag;
};

static_assert(sizeof(LiveActor) == 0x60, "");

} // namespace al