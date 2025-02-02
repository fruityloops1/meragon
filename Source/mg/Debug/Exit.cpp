#include "mg/Debug/Exit.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/srv/srv_Api.h"
#include "nn/svc/svc_Api.h"

namespace mg {

static nn::Result appletCloseApplication(const void* param, size_t paramSize, nn::Handle handle, nn::Handle appletHandle)
{
    nn::Result rc = 0;
    u32* cmdbuf = getThreadCommandBuffer();

    cmdbuf[0] = IPC_MakeHeader(0x27, 1, 4); // 0x270044
    cmdbuf[1] = paramSize;
    cmdbuf[2] = IPC_Desc_SharedHandles(1);
    cmdbuf[3] = handle.value;
    cmdbuf[4] = IPC_Desc_StaticBuffer(cmdbuf[1], 0);
    cmdbuf[5] = (u32)param;

    rc = nn::svc::SendSyncRequest(appletHandle);
    if (rc.Failed())
        return rc;

    return cmdbuf[1];
}

void exitProcess()
{
    nn::Handle appletHandle;
    nn::Result rc = nn::srv::GetServiceHandle(&appletHandle, "APT:U", 5, 0);

    // reckless abandonment
    rc = appletCloseApplication(nullptr, 0, 0, appletHandle);
    nn::svc::ExitProcess();
}

} // namespace mg
