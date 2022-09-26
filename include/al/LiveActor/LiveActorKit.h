#pragma once

#include "al/LiveActor/LiveActorGroup.h"

namespace al {

class LiveActorKit {
    int mAllActorsBufferSize = 0;
    void* unk[14];

public:
    LiveActorGroup* mLiveActorGroup = nullptr;
    void* unk2;

    LiveActorKit(int groupBufSize);
};

} // namespace al