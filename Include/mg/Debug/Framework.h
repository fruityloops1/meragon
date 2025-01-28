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
};

ProfilingData getProfilingData();

} // namespace mg
