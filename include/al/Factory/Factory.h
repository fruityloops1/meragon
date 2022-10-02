#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al {

template <typename T>
struct NameToCreator {
    const char* name;
    T create;
};

} // namespace al