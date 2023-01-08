#pragma once

#include "al/layouts/WipeSimpleTopBottom.h"

class StageWipeKeeper {
public:
    al::WipeSimpleTopBottom* mWipes[7];
    void* unk;

    StageWipeKeeper(const al::LayoutInitInfo& info);
};