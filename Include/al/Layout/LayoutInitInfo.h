#pragma once

#include "al/Execute/ExecuteDirector.h"
#include "al/LiveActor/LiveActorKit.h"

namespace al {

class LayoutInitInfo {
public:
    ExecuteDirector* mExecuteDirector;
    void* unk[2];

    LayoutInitInfo();
};

void initLayoutInitInfo(LayoutInitInfo* info, LiveActorKit*); // why LiveActorKit ?

} // namespace al
