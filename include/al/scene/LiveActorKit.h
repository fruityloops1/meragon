#pragma once

#include "al/scene/LiveActorGroup.h"

namespace al {

class LiveActorKit {
    int mAllActorsBufferSize = 0;
    void* unk[14];

    LiveActorGroup* mLiveActorGroup = nullptr;
    void* unk2;

public:
    LiveActorKit(int groupBufSize);
};

} // namespace al