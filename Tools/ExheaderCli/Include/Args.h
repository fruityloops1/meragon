#pragma once

#include "Util.h"
#include <filesystem>

struct Args {
    struct SvcMod {
        u8 type;
        bool allowed;
    };

    std::string inFile;
    std::string outFile;
    std::vector<SvcMod> svcMods;
    u32 newSize = -1;
    bool printCodeOffset = false;
    bool patchCode = false;
    std::string inFileExh;
    std::string inFileNewCode;
    std::string inFileMap;

    Args(int argc, const char* argv[])
    {
        for (int i = 1; i < argc; i++) {
            std::string arg(argv[i]);
            if (arg.find("no_svc=") == 0) {
                u8 svcType = std::stoi(arg.substr(7));
                svcMods.push_back({ svcType, false });
            } else if (arg.find("svc=") == 0) {
                u8 svcType = std::stoi(arg.substr(4));
                svcMods.push_back({ svcType, true });
            } else if (arg.find("newSize=") == 0) {
                u32 size = std::stoi(arg.substr(8));
                if (size == -1)
                    fail("Can't use -1 as newSize\n");
                newSize = size;
            } else if (arg.find("printCodeOffset=") == 0)
                printCodeOffset = arg.substr(16) == "true" ? true : false;
            else if (arg.find("patchCode=") == 0)
                patchCode = arg.substr(10) == "true" ? true : false;
            else if (arg.find("out=") == 0)
                outFile = arg.substr(4);
            else if (arg.find("inFileExh=") == 0)
                inFileExh = arg.substr(10);
            else if (arg.find("inFileNewCode=") == 0)
                inFileNewCode = arg.substr(14);
            else if (arg.find("inFileMap=") == 0)
                inFileMap = arg.substr(10);
            else {
                if (!std::filesystem::exists(arg)) {
                    arg.append(" does not exist\n");
                    fail(arg.c_str());
                }
                inFile = arg;
            }
        }

        if (!printCodeOffset && !patchCode)
            if (newSize == -1)
                fail("No newSize specified\n");
        if (inFile.empty())
            fail("No file specified\n");
        if (patchCode) {
            if (inFileExh.empty())
                fail("No exheader file specified\n");
            if (inFileNewCode.empty())
                fail("No new code file specified\n");
            if (inFileMap.empty())
                fail("No symbol map file specified\n");
        }
    }
};