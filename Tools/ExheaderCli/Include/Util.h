#pragma once

#include "Types.h"
#include <filesystem>
#include <fstream>
#include <span>
#include <vector>

template <typename T>
void writeFile(const std::string& filename, std::span<T> data)
{
    std::ofstream fstr(filename, std::ios::binary);
    fstr.unsetf(std::ios::skipws);
    fstr.write((const char*)data.data(), data.size() * sizeof(T));
}

template <typename... Args>
[[noreturn]] void fail(const char* msg, Args... args)
{
    fprintf(stderr, msg, args...);
    exit(1);
}

template <typename T>
std::vector<T> readFile(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
        fail("%s does not exist\n", filename.c_str());

    std::ifstream fstr(filename, std::ios::binary);
    fstr.unsetf(std::ios::skipws);

    std::streampos fileSize;

    fstr.seekg(0, std::ios::end);
    fileSize = fstr.tellg();
    fstr.seekg(0, std::ios::beg);

    std::vector<T> data;
    data.resize(fileSize);
    fstr.read((char*)data.data(), fileSize);

    return data;
}
