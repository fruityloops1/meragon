#include "Exheader.h"
#include <cstring>

void Exheader::applyChanges(const Args& args)
{
    sci.textCodeSetInfo.size = sci.textCodeSetInfo.physicalRegionSize << 12;

    sci.dataCodeSetInfo.physicalRegionSize += ((sci.bssSize + 0xFFF) & ~0xFFF) >> 12;
    sci.dataCodeSetInfo.physicalRegionSize += ((args.newSize + 0xFFF) & ~0xFFF) >> 12;
    sci.dataCodeSetInfo.size = sci.dataCodeSetInfo.physicalRegionSize << 12;

    sci.bssSize = 0;

    // Set ARM11 Kernel Caps
    ACI& aci = aci1;

    std::vector<u32> otherCaps;

    bool svcs[0x100];
    memset(&svcs, 0, sizeof(svcs));

    for (int i = 0; i < 28; i++) {
        u32 cap = aci.arm11kernelCaps.descriptors[i].value;

        if ((cap & 0xF8000000) == 0xF0000000) {
            u32 mask = cap & 0x00FFFFFF;
            u32 tableIndex = (cap & 0x03000000) >> 24;

            for (int i = 0; i < 24; i++) {
                if (mask & (1 << i)) {
                    u32 svc = tableIndex * 24 + i;
                    if (svc < 0x100)
                        svcs[svc] = true;
                }
            }
        } else if (cap != 0xFFFFFFFF)
            otherCaps.push_back(cap);
    }

    // Allow SVC 0x70: ControlProcessMemory
    svcs[0x70] = true;
    for (auto& svc : args.svcMods) {
        svcs[svc.type] = svc.allowed;
    }
    std::vector<u32> caps;

    for (int i = 0; i < 8; i++) {
        u32 newCap = 0xF0000000;
        newCap |= i << 24;

        for (int j = 0; j < 24; j++)
            newCap |= svcs[i * 24 + j] << j;

        if (newCap & 0x00FFFFFF)
            caps.push_back(newCap);
    }

    caps.insert(caps.end(), otherCaps.begin(), otherCaps.end());

    if (caps.size() > 28)
        fail("Setting ARM11 LSCs failed\n");

    int i = 0;
    for (; i < caps.size(); i++)
        aci.arm11kernelCaps.descriptors[i].value = caps[i];
    for (; i < caps.size(); i++)
        aci.arm11kernelCaps.descriptors[i].value = 0xFFFFFFFF;

    KernelDescriptor* prevDesc;
    for (int i = 0; i < caps.size(); i++) {
        u32 prefixBits;
        for (prefixBits = 0; prefixBits < 32; prefixBits++) {
            int bitIdx = 31 - prefixBits;
            if (((aci.arm11kernelCaps.descriptors[i].value >> bitIdx) & 1) == 0) {
                break;
            }
        }

        auto* desc = &aci.arm11kernelCaps.descriptors[i];

        if (prefixBits == 9) {
            if (desc->mappingStatic.flag && prevDesc->mappingStatic.page << 12 == 0x1f000000
                && (desc->mappingStatic.page << 12) - 1 == 0x1f5fffff) { // set non-readonly for vram
                prevDesc->mappingStatic.flag = false;
            }
        }

        prevDesc = desc;
    }
}
