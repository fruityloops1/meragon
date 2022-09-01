#pragma once

#include "al/system/ByamlIter.h"

namespace al {

class CreatorClassNameTableHolder {
    void* unk = nullptr;
    ByamlIter* mIter = nullptr;

public:
    CreatorClassNameTableHolder() = default;
};

} // namespace al