#pragma once

#include "sead/math/seadMatrix.h"
#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"

namespace al {

class ActorPoseKeeperBase {
    sead::Vector3f mTrans { 0, 0, 0 };

public:
    inline const sead::Vector3f& getTrans() const { return mTrans; }
    virtual const sead::Vector3f& getRotate() const;
    virtual const sead::Vector3f& getScale() const;
    virtual const sead::Vector3f& getVelocity() const;
    virtual const sead::Vector3f& getFront() const;
    virtual const sead::Quatf& getQuat() const;
    virtual const sead::Vector3f& getGravity() const;

    inline sead::Vector3f* getTransPtr() { return &mTrans; }
    virtual sead::Vector3f* getRotatePtr() { return nullptr; }
    virtual sead::Vector3f* getScalePtr() { return nullptr; }
    virtual sead::Vector3f* getVelocityPtr() { return nullptr; }
    virtual sead::Vector3f* getFrontPtr() { return nullptr; }
    virtual sead::Quatf* getQuatPtr() { return nullptr; }
    virtual sead::Vector3f* getGravityPtr() { return nullptr; }

    virtual void updatePoseRotate(const sead::Vector3f& rot);
    virtual void updatePoseQuat(const sead::Quatf& quat);
    virtual void updatePoseMtx(const sead::Matrix34f* mtx);
    virtual void unk1();
    virtual void unk2();
};

class ActorPoseKeeperTFSV : public ActorPoseKeeperBase {
    sead::Vector3f mFront { 0, 0, 0 };
    sead::Vector3f mScale { 1, 1, 1 };
    sead::Vector3f mVelocity { 0, 0, 0 };

public:
    const sead::Vector3f& getScale() const override { return mScale; };
    const sead::Vector3f& getVelocity() const override { return mVelocity; };
    const sead::Vector3f& getFront() const override { return mFront; };

    sead::Vector3f* getScalePtr() override { return &mScale; }
    sead::Vector3f* getVelocityPtr() override { return &mVelocity; }
    sead::Vector3f* getFrontPtr() override { return &mFront; }
};

class ActorPoseKeeperTFGSV : public ActorPoseKeeperTFSV {
    sead::Vector3f mGravity { 0, -1, 0 };

public:
    const sead::Vector3f& getGravity() const override { return mGravity; }

    sead::Vector3f* getGravityPtr() override { return &mGravity; }
};

class ActorPoseKeeperTQSV : public ActorPoseKeeperBase {
    sead::Quatf mQuat = sead::Quatf::unit;
    sead::Vector3f mScale { 1, 1, 1 };
    sead::Vector3f mVelocity { 0, 0, 0 };

public:
    const sead::Vector3f& getScale() const override { return mScale; };
    const sead::Vector3f& getVelocity() const override { return mVelocity; };
    const sead::Quatf& getQuat() const override { return mQuat; };

    sead::Vector3f* getScalePtr() override { return &mScale; }
    sead::Vector3f* getVelocityPtr() override { return &mVelocity; }
    sead::Quatf* getQuatPtr() override { return &mQuat; }
};

class ActorPoseKeeperTRSV : public ActorPoseKeeperBase {
    sead::Vector3f mRotate { 0, 0, 0 };
    sead::Vector3f mScale { 1, 1, 1 };
    sead::Vector3f mVelocity { 0, 0, 0 };

public:
    const sead::Vector3f& getRotate() const override { return mRotate; };
    const sead::Vector3f& getScale() const override { return mScale; };
    const sead::Vector3f& getVelocity() const override { return mVelocity; };

    sead::Vector3f* getRotatePtr() override { return &mRotate; }
    sead::Vector3f* getScalePtr() override { return &mScale; }
    sead::Vector3f* getVelocityPtr() override { return &mVelocity; }
};

class ActorInitInfo;
class LiveActor;

// wrappers

const sead::Vector3f& getTrans(const LiveActor* actor);
const sead::Vector3f& getRotate(const LiveActor* actor);
const sead::Vector3f& getScale(const LiveActor* actor);
const sead::Vector3f& getVelocity(const LiveActor* actor);
const sead::Vector3f& getFront(const LiveActor* actor);
const sead::Quatf& getQuat(const LiveActor* actor);
const sead::Vector3f& getGravity(const LiveActor* actor);

sead::Vector3f* getTransPtr(LiveActor* actor);
sead::Vector3f* getRotatePtr(LiveActor* actor);
sead::Vector3f* getVelocityPtr(LiveActor* actor);
sead::Vector3f* getFrontPtr(LiveActor* actor);
sead::Quatf* getQuatPtr(LiveActor* actor);

void setTrans(LiveActor* actor, const sead::Vector3f& trans);
void setScale(LiveActor* actor, const sead::Vector3f& scale);
void setFront(LiveActor* actor, const sead::Vector3f& front);

void updatePoseRotate(LiveActor* actor, const sead::Vector3f& rotate);

void initActorPoseTRSV(LiveActor* actor);
void initActorPoseTFSV(LiveActor* actor);
void initActorPoseTFGSV(LiveActor* actor);
void initActorPoseTQSV(LiveActor* actor);

void initActorSRTAndPoseTRSV(LiveActor* actor, const ActorInitInfo& info);

} // namespace al