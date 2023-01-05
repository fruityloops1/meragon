#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/dbg/dbg_Types.h"
#include "nn/os/os_Types.h"
#include "types.h"

namespace nn {
namespace svc {

    void ExitProcess();
    void SleepThread(u64 nanos);
    nn::Result CreateMemoryBlock(nn::Handle* handleOut, u32 addr, u32 size, u32 myPerm, u32 otherPerm);
    nn::Result ArbitrateAddress(nn::Handle arbiter, uintptr_t addr, nn::os::ArbitrationType type, s32 value, s64 ns);
    nn::Result CloseHandle(nn::Handle handle);
    nn::Result SendSyncRequest(nn::Handle session);

    // Debug
    nn::Result Break(nn::dbg::BreakReason reason);

} // namespace svc
} // namespace nn
