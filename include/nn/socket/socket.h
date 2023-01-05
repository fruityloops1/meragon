#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>

// from https://gist.github.com/RicBent/23ea94acb17321714155d22e2f025f4a

namespace nn {
namespace socket {

    struct SockAddr {
        u8 len;
        u8 family;
        u16 port;
        u32 addr;
    };

    struct AddrInfo {
        s32 flags;
        s32 family;
        s32 socktype;
        s32 protocol;
        u32 addrlen;
        char canonname[256];
        SockAddr addr;
    };

    namespace socu {
        nn::Result initialize(nn::Handle bufferHandle, u32 bufferSize);
        nn::Result finalize();
        nn::Result socket(int* socketfdOut, int domain, int type, int protocol);
        nn::Result close(int* rval, int socketfd);
        nn::Result bind(int* rval, int socketfd, const void* addr, u32 addrlen);
        nn::Result connect(int* rval, int socketfd, const void* addr, u32 addrlen);
        nn::Result sendto(int* rval, int socketfd, const void* buf, u32 len, int flags, const void* addr, u32 addrlen);
        nn::Result recvfrom(int* rval, int socketfd, void* buf, u32 len, int flags, void* addr, u32 addrlen);
        nn::Result getaddrinfo(int* rval, const char* node, const char* service, const void* hints, AddrInfo* buffer, s32 bufferCount, s32* countAvailable);
    } // namespace socu

    inline u16 Htons(u16 val)
    {
        return ((val & 0xFF) << 8) | ((val & 0xFF00) >> 8);
    }

    nn::Result Initialize(void* bufferAddress, u32 bufferSize);
    nn::Result Finalize();

    inline int Socket(int domain, int type, int protocol)
    {
        int socketfd;
        nn::Result r = socu::socket(&socketfd, domain, type, protocol);
        if (r.Failed())
            return -1;
        return socketfd;
    }

    inline int Close(int socketfd)
    {
        int rval;
        nn::Result r = socu::close(&rval, socketfd);
        if (r.Failed())
            return -1;
        return rval;
    }

    inline int Bind(int socketfd, const void* addr, u32 addrlen)
    {
        int rval;
        nn::Result r = socu::bind(&rval, socketfd, addr, addrlen);
        if (r.Failed())
            return -1;
        return rval;
    }

    inline int Connect(int socketfd, const void* addr, u32 addrlen)
    {
        int rval;
        nn::Result r = socu::connect(&rval, socketfd, addr, addrlen);
        if (r.Failed())
            return -1;
        return rval;
    }

    inline int SendTo(int socketfd, const void* buf, u32 len, int flags, const void* addr, u32 addrlen)
    {
        int rval;
        nn::Result r = socu::sendto(&rval, socketfd, buf, len, flags, addr, addrlen);
        if (r.Failed())
            return -1;
        return rval;
    }

    inline int Send(int socketfd, const void* buf, u32 len, int flags)
    {
        return SendTo(socketfd, buf, len, flags, NULL, 0);
    }

    inline int RecvFrom(int socketfd, void* buf, u32 len, int flags, void* addr, u32 addrlen)
    {
        int rval;
        nn::Result r = socu::recvfrom(&rval, socketfd, buf, len, flags, addr, addrlen);
        if (r.Failed())
            return -1;
        return rval;
    }

    inline int Recv(int socketfd, void* buf, u32 len, int flags)
    {
        return RecvFrom(socketfd, buf, len, flags, NULL, 0);
    }

    inline int GetAddrInfo(const char* node, const char* service, const void* hints, AddrInfo* buffer, s32 bufferCount, s32* countAvailableOut)
    {
        int rval;
        nn::Result r = socu::getaddrinfo(&rval, node, service, hints, buffer, bufferCount, countAvailableOut);
        if (r.Failed())
            return -1;
        return rval;
    }

} // namespace socket
} // namespace nn
