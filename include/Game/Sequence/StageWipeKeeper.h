#pragma once

#include "al/Layout/LayoutInitInfo.h"
#include "al/Layout/WipeSimpleTopBottom.h"

class StageWipeKeeper {
public:
    al::WipeSimpleTopBottom* mWipes[7];
    void* unk;

    StageWipeKeeper(const al::LayoutInitInfo& info);
};
