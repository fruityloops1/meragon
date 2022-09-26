#pragma once

#include "al/Factory/Factory.h"
#include "al/System/ByamlIter.h"

namespace al {

class CreatorClassNameTableHolder {
    void* unk = nullptr;
    ByamlIter* mIter = nullptr;

public:
    CreatorClassNameTableHolder() = default;

    CreateActorFunctionT getCreator(const char* objectName) const;
};

} // namespace al