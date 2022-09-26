#pragma once

#include "al/LiveActor/LiveActorKit.h"

namespace al {

class LayoutInitInfo {
    void* unk[3];
};

void initLayoutInitInfo(LayoutInitInfo* info, al::LiveActorKit*); // why LiveActorKit ?

} // namespace al