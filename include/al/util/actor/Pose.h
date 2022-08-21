#pragma once

#include "al/actor/LiveActor.h"
#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"

namespace al {

const sead::Vector3f& getTrans(const al::LiveActor* actor);
const sead::Vector3f& getRotate(const al::LiveActor* actor);
const sead::Vector3f& getScale(const al::LiveActor* actor);
const sead::Vector3f& getVelocity(const al::LiveActor* actor);
const sead::Vector3f& getFront(const al::LiveActor* actor);
const sead::Quatf& getQuat(const al::LiveActor* actor);
const sead::Vector3f& getGravity(const al::LiveActor* actor);

sead::Vector3f* getTransPtr(al::LiveActor* actor);
sead::Vector3f* getRotatePtr(al::LiveActor* actor);
sead::Vector3f* getVelocityPtr(al::LiveActor* actor);
sead::Vector3f* getFrontPtr(al::LiveActor* actor);
sead::Quatf* getQuatPtr(al::LiveActor* actor);

void initActorPoseTRSV(al::LiveActor* actor);
void initActorPoseTFSV(al::LiveActor* actor);
void initActorPoseTFGSV(al::LiveActor* actor);
void initActorPoseTQSV(al::LiveActor* actor);

void invalidateClipping(al::LiveActor* actor); // idk if this belongs here

} // namespace  al