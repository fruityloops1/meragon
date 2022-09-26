#pragma once

#include "al/System/ByamlIter.h"

namespace al {

class CreatorClassNameTableHolder {
    void* unk = nullptr;
    ByamlIter* mIter = nullptr;

public:
    CreatorClassNameTableHolder() = default;
};

} // namespace al