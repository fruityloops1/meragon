#include "Args.h"
#include "Exheader.h"
#include "Patch/AsmPatch.h"
#include "Patch/BranchHook.h"
#include "Patch/PatchBase.h"
#include "Patch/ReplacePatch.h"
#include "PatchHeader.h"
#include "Util.h"

#include <cstring>
#include <stdexcept>

u32 getEnd(const Exheader& exh)
{
    return exh.sci.dataCodeSetInfo.address + (exh.sci.dataCodeSetInfo.physicalRegionSize << 12) + ((exh.sci.bssSize + 0xFFF) & ~0xFFF);
}

std::vector<u8> appendNewCode(const std::vector<u8>& oldCode, const std::vector<u8>& newCode, const Exheader& exh, const std::string mapFile)
{
    const u32 newCodeOffset = getEnd(exh);
    const u32 newCodeEnd = newCodeOffset + newCode.size();
    const u32 binarySize = (newCodeEnd + 0xFFF) & ~0xFFF; // pad to 4096 bytes

    std::vector<u8> newBinary(binarySize - sCodeStart, 0);
    std::copy(newCode.begin(), newCode.end(), &newBinary[newCodeOffset - sCodeStart]);
    std::copy(oldCode.begin(), oldCode.end(), &newBinary[0]);

    const u32 newCodeSize = newCode.size() + 32;
    PatchHeader* header = reinterpret_cast<PatchHeader*>(&newBinary[newCodeOffset - sCodeStart]);
    header->codeSize = newCodeSize;
    header->textOffset = exh.sci.textCodeSetInfo.address;
    header->textSize = exh.sci.textCodeSetInfo.size;
    header->rodataOffset = exh.sci.readOnlyCodeSetInfo.address;
    header->rodataSize = exh.sci.readOnlyCodeSetInfo.size;

    const u32 loaderOffset = (exh.sci.textCodeSetInfo.size + sCodeStart + 0xF) & ~0xF;
    const u32 loaderMaxSize = exh.sci.readOnlyCodeSetInfo.address - loaderOffset;

    // copying initFunc to loader section
    u32* initFunc = reinterpret_cast<u32*>(&newBinary[header->initFunc - sCodeStart]);
    s32 initFuncSize = 0;
    for (; initFunc[initFuncSize] != -1; initFuncSize++)
        if (initFuncSize * sizeof(u32) > 512)
            fail("initFunc too big (0x%.8x)\n", initFuncSize);
    initFuncSize *= sizeof(u32);
    if (initFuncSize > loaderMaxSize)
        throw std::runtime_error("loader too big");

    std::memcpy(&newBinary[loaderOffset - sCodeStart], initFunc, initFuncSize);

    // branching to initFunc
    u32* __ctr_start = reinterpret_cast<u32*>(&newBinary[0]);
    __ctr_start[0] = makeBranch(loaderOffset, sCodeStart, 0xeb /* BranchLink */);
    std::vector<const PatchBase*> patches = collectPatchesFromMap(newBinary, mapFile);

    for (const PatchBase* patch : patches)
        switch (patch->mType) {
        case PatchType::Replace: {
            static_cast<const ReplacePatch*>(patch)->apply(newBinary);
            break;
        }
        case PatchType::Assembly: {
            static_cast<const AsmPatch*>(patch)->apply(newBinary);
            break;
        }
        case PatchType::Branch: {
            static_cast<const BranchHook*>(patch)->apply(newBinary);
            break;
        }
        default:
            break;
        }

    return newBinary;
}

int main(int argc, const char* argv[])
{
    Args args(argc, argv);
    Exheader exh;
    if (!args.patchCode) {
        std::vector<u8> exheaderData = readFile<u8>(args.inFile);
        if (exheaderData.size() != 2048)
            fail("Specified file is not an Exheader (size: 0x%.8zx)\n", exheaderData.size());
        std::memcpy(&exh, exheaderData.data(), 2048);
    }

    std::string outPath = args.outFile.empty() ? "out.bin" : args.outFile;

    if (args.printCodeOffset)
        printf("0x%.8x\n", getEnd(exh));
    else if (args.patchCode) {
        std::vector<u8> oldCode = readFile<u8>(args.inFile);
        Exheader exh;
        std::vector<u8> exheaderData = readFile<u8>(args.inFileExh);
        if (exheaderData.size() != 2048)
            fail("Specified file is not an Exheader (size: 0x%.8zx)\n", exheaderData.size());
        std::memcpy(&exh, exheaderData.data(), 2048);
        std::vector<u8> newCode = readFile<u8>(args.inFileNewCode);

        std::vector<u8> final = appendNewCode(oldCode, newCode, exh, args.inFileMap);
        writeFile(outPath, std::span<u8>(final));
    } else {
        exh.applyChanges(args);
        writeFile(outPath, std::span<u8>((u8*)&exh, 2048));
    }
}
