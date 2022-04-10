#include "mg/hook.h"
#include "mg/efun.h"
#include "mg/log.h"
extern "C" {
#include <3ds/svc.h>
}
#include <string.h>

Handle
getCurrentProcessHandle()
{
    Handle handle = 0;
    u32 currentPid = 0;
    Result res;

    svcGetProcessId(&currentPid, 0xffff8001);
    res = svcOpenProcess(&handle, currentPid);

    if (res != 0)
        return 0;

    return handle;
}

static bool setCodeRegionPerm(u32 perm)
{
    if (svcControlProcessMemory(getCurrentProcessHandle(),
            ADDR_CODE, ADDR_CODE, ADDR_CUSTOM_CODE - ADDR_CODE,
            MemOp::MEMOP_PROT, perm)
        < 0) {
        mg::log("[Hook] Failed setting memory permissions as %d", perm);
        return false;
    }
    return true;
}

bool mg::tryHookData(u32 address, const void* data, size_t len)
{
    if (!setCodeRegionPerm(MemPerm::MEMPERM_READ | MemPerm::MEMPERM_WRITE | MemPerm::MEMPERM_EXECUTE))
        return false;

    void* const addressPtr = (void*)address;
    mg::log("[Hook] Hooking %zu byte%s at 0x%.8x", len, len == 1 ? "" : "s", addressPtr);
    memcpy(addressPtr, data, len);

    if (!setCodeRegionPerm(MemPerm::MEMPERM_READEXECUTE))
        return false;
    return true;
}

void mg::hookData(u32 address, const void* data, size_t len)
{
    if (!tryHookData(address, data, len))
        svcBreak(UserBreakType::USERBREAK_ASSERT);
}

u32 mg::arm32::makeBranch(u32 to, u32 at, constants::BranchType type)
{
    union {
        struct {
            signed int relAddr : 24;
            u8 type : 8;
        };
        u32 data;
    } conv { static_cast<signed int>((to - at - 8) / 4), (u8)type };
    return conv.data;
}