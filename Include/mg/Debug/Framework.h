#pragma once

#include "hk/Types.h"
#include <sead/time/seadTickSpan.h>

namespace mg {

void suspendFramework();

struct ProfilingData {
    sead::TickSpan calc;
    sead::TickSpan draw;
    sead::TickSpan vblank;
    sead::TickSpan lastFrame;
    sead::TickSpan curFrame;

    int curExecuteTable = 0;
    sead::TickSpan executeTableLists[128];
    sead::TickSpan executeUpdateTable;
    sead::TickSpan executeDrawTable[10];
};

ProfilingData& getProfilingData();

} // namespace mg
