#pragma once

#include "al/MapObj/MapObjActor.h"
#include <sead/math/seadVector.h>

namespace mg {

class SnakeBlock : public al::MapObjActor {
    s32 pBlockCount = 1;
    f32 pMoveSpeed = 10;
    f32 pGapBetweenBlocks = 50;

    SnakeBlock* mRootBlock = nullptr;
    SnakeBlock* mNextBlock = nullptr;

    void notifyEnd();

public:
    SnakeBlock(const sead::SafeString& name)
        : MapObjActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;

    void exeWait();
    void exeMove();
    void exeStall();
};

} // namespace mg
