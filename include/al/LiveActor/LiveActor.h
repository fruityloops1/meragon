#pragma once

#include "al/Audio/AudioKeeper.h"
#include "al/Effect/EffectKeeper.h"
#include "al/LiveActor/ActorActionKeeper.h"
#include "al/LiveActor/ActorExecuteInfo.h"
#include "al/LiveActor/ActorInitInfo.h"
#include "al/LiveActor/ActorLightKeeper.h"
#include "al/LiveActor/ActorPoseKeeper.h"
#include "al/LiveActor/Collider.h"
#include "al/LiveActor/HitSensor.h"
#include "al/LiveActor/HitSensorKeeper.h"
#include "al/LiveActor/LiveActorFlag.h"
#include "al/LiveActor/ModelKeeper.h"
#include "al/LiveActor/SensorMsg.h"
#include "al/LiveActor/SubActorKeeper.h"
#include "al/Map/CollisionParts.h"
#include "al/Nerve/Nerve.h"
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
    virtual void attackSensor(HitSensor* me, HitSensor* other);
    virtual bool receiveMsg(SensorMsg msg, HitSensor* other, HitSensor* me);
    virtual sead::Matrix34f* getBaseMtx() const;
    virtual EffectKeeper* getEffectKeeper() const override { return mEffectKeeper; };
    virtual AudioKeeper* getAudioKeeper() const override { return mAudioKeeper; };
    virtual void gap2();
    virtual void gap3();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void updateCollider();

    inline const char* getName() { return mActorName; }

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
    ActorLightKeeper* mActorLightKeeper = nullptr;
    void* keeper4C = nullptr;
    SubActorKeeper* mSubActorKeeper = nullptr;

private:
    LiveActorFlag mLiveActorFlag;
};

void initNerve(LiveActor* actor, const al::Nerve* nerve, int step = 0);

static_assert(sizeof(LiveActor) == 0x60, "");

} // namespace al