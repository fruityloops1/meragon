#pragma once

#include <nn/svc/svc_Api.h>
#include <stdio.h>
#include <string.h>

namespace hk::dbg {

void Break(u32 dbgvalue1, u32 dbgvalue2 = 0);

#define HK_CHECK_RESULT(RES) \
    if (RES.Failed())        \
    ::hk::dbg::Break(RES.getValue())

} // namespace hk::dbg
