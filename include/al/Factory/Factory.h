#pragma once

namespace al {

template <typename T>
struct NameToCreator {
    const char* name;
    T create;
};

} // namespace al