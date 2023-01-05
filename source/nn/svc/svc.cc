#include <nn/svc/svc_Api.h>

namespace nn {
namespace svc {

    nn::Result SendSyncRequest(nn::Handle session)
    {
        __asm("svc #0x32");
        __asm("bx lr");
    }

} // namespace svc
} // namespace nn
