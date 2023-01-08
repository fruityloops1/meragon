#include <nn/socket/socket.h>
#include <nn/srv/srv_Api.h>
#include <nn/svc/svc_Api.h>

#include <string.h>

static inline void* getThreadLocalStorage()
{
    void* ret;
    __asm__("mrc p15, 0, %[data], c13, c0, 3"
            : [data] "=r"(ret));
    return ret;
}

static inline u32* getThreadCommandBuffer(void)
{
    return (u32*)((u8*)getThreadLocalStorage() + 0x80);
}

static inline u32* getThreadReceiveBuffer(void)
{
    return (u32*)((u8*)getThreadLocalStorage() + 0x180);
}

static inline u32 IPC_MakeHeader(u16 commandId, u32 normalParams, u32 translateParams)
{
    return ((u32)commandId << 16) | (((u32)normalParams & 0x3F) << 6) | (((u32)translateParams & 0x3F) << 0);
}

static inline u32 IPC_Desc_CurProcessId()
{
    return 0x20;
}

static inline u32 IPC_Desc_SharedHandles(u32 number)
{
    return ((u32)(number - 1) << 26);
}

static inline u32 IPC_Desc_StaticBuffer(size_t size, unsigned buffer_id)
{
    return (size << 14) | ((buffer_id & 0xF) << 10) | 0x2;
}

namespace nn {
namespace socket {

    static bool initialized = false;
    static nn::Handle bufferHandle;
    static nn::Handle socuHandle;

    nn::Result Initialize(void* bufferAddress, u32 bufferSize)
    {
        nn::Result r;

        if (initialized)
            return -1;

        r = nn::svc::CreateMemoryBlock(&bufferHandle, (u32)bufferAddress, bufferSize, 0, 3);
        if (r.Failed()) {
            return r;
        }

        r = nn::srv::GetServiceHandle(&socuHandle, "soc:U", 5, 0);
        if (r.Failed()) {
            nn::svc::CloseHandle(bufferHandle);
            bufferHandle = 0;
            return r;
        }

        r = nn::socket::socu::initialize(bufferHandle, bufferSize);
        if (r.Failed()) {
            nn::svc::CloseHandle(bufferHandle);
            bufferHandle = 0;
            nn::svc::CloseHandle(socuHandle);
            socuHandle = 0;
            return r;
        }

        initialized = true;

        return r;
    }

    nn::Result Finalize()
    {
        nn::Result r;

        if (!initialized)
            return -1;

        nn::svc::CloseHandle(bufferHandle);
        bufferHandle = 0;

        r = nn::socket::socu::finalize();

        nn::svc::CloseHandle(socuHandle);
        socuHandle = 0;

        initialized = false;

        return r;
    }

    namespace socu {

        nn::Result initialize(nn::Handle bufferHandle, u32 bufferSize)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0x1, 1, 4); // 0x10044
            cmdbuf[1] = bufferSize;
            cmdbuf[2] = IPC_Desc_CurProcessId();
            cmdbuf[4] = IPC_Desc_SharedHandles(1);
            cmdbuf[5] = bufferHandle.value;

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            return cmdbuf[1];
        }

        nn::Result finalize()
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0x19, 0, 0); // 0x190000

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            return cmdbuf[1];
        }

        nn::Result socket(int* socketfdOut, int domain, int type, int protocol)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0x2, 3, 2); // 0x200C2
            cmdbuf[1] = domain;
            cmdbuf[2] = type;
            cmdbuf[3] = protocol;
            cmdbuf[4] = IPC_Desc_CurProcessId();

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            *socketfdOut = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result close(int* rval, int socketfd)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0xB, 1, 2); // 0xB0042
            cmdbuf[1] = (u32)socketfd;
            cmdbuf[2] = IPC_Desc_CurProcessId();

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            *rval = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result bind(int* rval, int socketfd, const void* addr, u32 addrlen)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0x5, 2, 4); // 0x50084
            cmdbuf[1] = (u32)socketfd;
            cmdbuf[2] = (u32)addrlen;
            cmdbuf[3] = IPC_Desc_CurProcessId();
            cmdbuf[5] = IPC_Desc_StaticBuffer(addrlen, 0);
            cmdbuf[6] = (u32)addr;

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;
            *rval = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result connect(int* rval, int socketfd, const void* addr, u32 addrlen)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0x6, 2, 4); // 0x60084
            cmdbuf[1] = (u32)socketfd;
            cmdbuf[2] = (u32)addrlen;
            cmdbuf[3] = IPC_Desc_CurProcessId();
            cmdbuf[5] = IPC_Desc_StaticBuffer(addrlen, 0);
            cmdbuf[6] = (u32)addr;

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            *rval = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result sendto(int* rval, int socketfd, const void* buf, u32 len, int flags, const void* addr, u32 addrlen)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();

            cmdbuf[0] = IPC_MakeHeader(0xA, 4, 6); // 0xA0106
            cmdbuf[1] = (u32)socketfd;
            cmdbuf[2] = (u32)len;
            cmdbuf[3] = (u32)flags;
            cmdbuf[4] = (u32)addrlen;
            cmdbuf[5] = IPC_Desc_CurProcessId();
            cmdbuf[7] = IPC_Desc_StaticBuffer(len, 2);
            cmdbuf[8] = (u32)buf;
            cmdbuf[9] = IPC_Desc_StaticBuffer(addrlen, 1);
            cmdbuf[10] = (u32)addr;

            r = nn::svc::SendSyncRequest(socuHandle);
            if (r.Failed())
                return r;

            *rval = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result recvfrom(int* rval, int socketfd, void* buf, u32 len, int flags, void* addr, u32 addrlen)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();
            u32* rcvbuf = getThreadReceiveBuffer();

            u32 rcvbufBak[4];

            cmdbuf[0] = IPC_MakeHeader(0x8, 4, 2); // 0x80102
            cmdbuf[1] = (u32)socketfd;
            cmdbuf[2] = (u32)len;
            cmdbuf[3] = (u32)flags;
            cmdbuf[4] = (u32)addrlen;
            cmdbuf[5] = IPC_Desc_CurProcessId();

            rcvbufBak[0] = rcvbuf[0];
            rcvbufBak[1] = rcvbuf[1];
            rcvbufBak[2] = rcvbuf[2];
            rcvbufBak[3] = rcvbuf[3];

            rcvbuf[0] = (((u32)len) << 14) | 2;
            rcvbuf[1] = (u32)buf;
            rcvbuf[2] = (addrlen << 14) | 2;
            rcvbuf[3] = (u32)addr;

            r = nn::svc::SendSyncRequest(socuHandle);

            rcvbuf[0] = rcvbufBak[0];
            rcvbuf[1] = rcvbufBak[1];
            rcvbuf[2] = rcvbufBak[2];
            rcvbuf[3] = rcvbufBak[3];

            if (r.Failed())
                return r;

            *rval = cmdbuf[2];

            return cmdbuf[1];
        }

        nn::Result getaddrinfo(int* rval, const char* node, const char* service, const void* hints, AddrInfo* buffer, s32 bufferCount, s32* countAvailableOut)
        {
            nn::Result r;
            u32* cmdbuf = getThreadCommandBuffer();
            u32* rcvbuf = getThreadReceiveBuffer();

            u32 rcvbufBak[2];

            cmdbuf[0] = IPC_MakeHeader(0xF, 4, 6); // 0x00F0106
            cmdbuf[1] = node ? strlen(node) + 1 : 0;
            cmdbuf[2] = service ? strlen(service) + 1 : 0;
            cmdbuf[3] = 0; // TODO: hints ? sizeof(*hints) : 0;
            cmdbuf[4] = sizeof(nn::socket::AddrInfo) * bufferCount;
            cmdbuf[5] = IPC_Desc_StaticBuffer(cmdbuf[1], 5);
            cmdbuf[6] = (u32)node;
            cmdbuf[7] = IPC_Desc_StaticBuffer(cmdbuf[2], 6);
            cmdbuf[8] = (u32)service;
            cmdbuf[9] = IPC_Desc_StaticBuffer(cmdbuf[3], 7);
            cmdbuf[10] = (u32)hints;

            rcvbufBak[0] = rcvbuf[0];
            rcvbufBak[1] = rcvbuf[1];

            rcvbuf[0] = IPC_Desc_StaticBuffer(cmdbuf[4], 0);
            rcvbuf[1] = (u32)buffer;

            r = nn::svc::SendSyncRequest(socuHandle);

            rcvbuf[0] = rcvbufBak[0];
            rcvbuf[1] = rcvbufBak[1];

            if (r.Failed())
                return r;

            r = cmdbuf[1];
            if (r.Failed())
                return r;

            *rval = cmdbuf[2];
            *countAvailableOut = cmdbuf[3];

            return r;
        }

    } // namespace socu

} // namespace socket
} // namespace nn
