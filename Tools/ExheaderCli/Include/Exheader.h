#pragma once

#include "Args.h"
#include "Types.h"

struct CodeSetInfo {
    u32 address;
    u32 physicalRegionSize;
    u32 size;
};

struct ACI {
    struct
    {
        u8 data[0x170];
    } arm11systemCaps;

    struct
    {
        u32 descriptors[28];
        u8 reserved[0x10];
    } arm11kernelCaps;

    struct
    {
        u8 data[0x10];
    } arm9accessControl;
};

// stolen from https://github.com/RicBent/Magikoopa/blob/master/MagikoopaUI/exheader.h
struct Exheader {
    struct
    {
        char title[8];
        u8 reserved1[5];

        struct
        {
            bool compressExefsCode : 1;
            bool sdApplication : 1;
            unsigned char : 6;
        } sciFlags;

        u16 remasterVersion;

        CodeSetInfo textCodeSetInfo;
        u32 stackSize;
        CodeSetInfo readOnlyCodeSetInfo;
        u32 reserved2;
        CodeSetInfo dataCodeSetInfo;
        u32 bssSize;

        u64 dependencyModules[48];

        struct
        {
            u64 saveDataSize;
            u64 jumpId;
            u8 reserved[0x30];
        } systemInfo;

    } sci;

    ACI aci1;

    u8 accessDesc[0x100];
    u8 ncchHdr[0x100];

    ACI aci2;

    void applyChanges(const Args& args);
};
