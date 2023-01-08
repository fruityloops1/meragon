#pragma once

#include "hk/Types.h"
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/os/os_Types.h>

namespace hk::sys {

// special svcs for loader
nn::Result OpenProcess(nn::Handle* process, u32 processId);
nn::Result GetProcessId(u32* id, nn::Handle handle);
nn::Result ControlProcessMemory(nn::Handle process, u32 addr0, u32 addr1, u32 size, nn::os::MemoryOperation operation, nn::os::MemoryPermission perm);

void Initialize();
const extern volatile u32 endId;

} // namespace hk::sys
