#pragma once

#include "hk/Types.h"

namespace nn {
namespace os {

    /// Arbitration modes.
    enum ArbitrationType {
        ArbitrationType_SIGNAL = 0, ///< Signal #value threads for wake-up.
        ArbitrationType_WAIT_IF_LESS_THAN = 1, ///< If the memory at the address is strictly lower than #value, then wait for signal.
        ArbitrationType_DECREMENT_AND_WAIT_IF_LESS_THAN = 2, ///< If the memory at the address is strictly lower than #value, then decrement it and wait for signal.
        ArbitrationType_WAIT_IF_LESS_THAN_TIMEOUT = 3, ///< If the memory at the address is strictly lower than #value, then wait for signal or timeout.
        ArbitrationType_DECREMENT_AND_WAIT_IF_LESS_THAN_TIMEOUT = 4, ///< If the memory at the address is strictly lower than #value, then decrement it and wait for signal or timeout.
    };

    /// Reset Types.
    enum ResetType {
        ResetType_ONESHOT = 0, ///< When the primitive is signaled, it will wake up exactly one thread and will clear itself automatically.
        ResetType_STICKY = 1, ///< When the primitive is signaled, it will wake up all threads and it won't clear itself automatically.
        ResetType_PULSE = 2 ///< Only meaningful for timers: same as ONESHOT but it will periodically signal the timer instead of just once.
    };

    /// Memory Operations
    enum MemoryOperation {
        MemoryOperation_FREE = 1,
        MemoryOperation_RESERVE,
        MemoryOperation_COMMIT,
        MemoryOperation_MAP,
        MemoryOperation_UNMAP,
        MemoryOperation_PROTECT
    };

    /// Memory Permissions
    enum MemoryPermission {
        MemoryPermission_NONE,
        MemoryPermission_R,
        MemoryPermission_W,
        MemoryPermission_RW,
        MemoryPermission_X,
        MemoryPermission_RX,
        MemoryPermission_WX,
        MemoryPermission_RWX,
        MemoryPermission_DONTCARE = 0x10000000
    };

    /// Memory information.
    struct MemInfo {
        u32 base_addr = 0; ///< Base address.
        u32 size = 0; ///< Size.
        u32 perm = 0; ///< Memory permissions. See @ref MemPerm
        u32 state = 0; ///< Memory state. See @ref MemState
    };

    /// Memory page information.
    struct PageInfo {
        u32 flags = 0; ///< Page flags.
    };

} // namespace os
} // namespace nn
