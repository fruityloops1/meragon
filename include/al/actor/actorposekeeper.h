#pragma once

#include "sead/math/seadMatrix.h"
#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"

namespace al {

/**
 * @brief Class that contains a LiveActors properties like Position, Rotation, etc. in the world
 * Only has Translation in the Base class, returns default values for the other components.
 * The components can be:
 * Trans     Vector3f Translation/Position of the actor
 * Rotate    Vector3f Euler rotation
 * Scale     Vector3f Scale of the model and other things
 * Velocity  Vector3f Velocity the actor is moving at
 * Front     Vector3f Vector the actor is facing to
 * Quat      Quatf    Quaternion rotation
 * Gravity   Vector3f Gravity of the actor
 */
class ActorPoseKeeperBase {
    sead::Vector3f mTrans { 0, 0, 0 };

public:
    /**
     * @brief Returns a read-only reference to the Translation of the actor
     * @return const sead::Vector3f& Translation
     */
    inline const sead::Vector3f& getTrans() const { return mTrans; }
    virtual const sead::Vector3f& getRotate() const;
    virtual const sead::Vector3f& getScale() const;
    virtual const sead::Vector3f& getVelocity() const;
    virtual const sead::Vector3f& getFront() const;
    virtual const sead::Quatf& getQuat() const;
    virtual const sead::Vector3f& getGravity() const;

    /**
     * @brief Returns a mutable pointer to the Translation of the actor
     * @return sead::Vector3f* Translation
     */
    inline sead::Vector3f* getTransPtr() { return &mTrans; }
    virtual sead::Vector3f* getRotatePtr() { return nullptr; }
    virtual sead::Vector3f* getScalePtr() { return nullptr; }
    virtual sead::Vector3f* getVelocityPtr() { return nullptr; }
    virtual sead::Vector3f* getFrontPtr() { return nullptr; }
    virtual sead::Quatf* getQuatPtr() { return nullptr; }
    virtual sead::Vector3f* getGravityPtr() { return nullptr; }

    /**
     * @brief If the derivant does not have a Rotate component, the component it uses for Rotation will be set to rot
     * @param rot Rotate rotation to convert
     */
    virtual void updatePoseRotate(const sead::Vector3f& rot);
    virtual void updatePoseQuat(const sead::Quatf& quat);
    virtual void updatePoseMtx(const sead::Matrix34f* mtx);
    virtual void unk1();
    virtual void unk2();
};

/**
 * @brief ActorPoseKeeper with Trans, Front, Scale, Velocity components
 */
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

/**
 * @brief ActorPoseKeeper with Trans, Front, Gravity, Scale, Velocity components
 */
class ActorPoseKeeperTFGSV : public ActorPoseKeeperTFSV {
    sead::Vector3f mGravity { 0, -1, 0 };

public:
    const sead::Vector3f& getGravity() const override { return mGravity; }

    sead::Vector3f* getGravityPtr() override { return &mGravity; }
};

/**
 * @brief ActorPoseKeeper with Trans, Quat, Scale, Velocity components
 */
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

/**
 * @brief ActorPoseKeeper with Trans, Rotate, Scale, Velocity components
 */
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

} // namespace al