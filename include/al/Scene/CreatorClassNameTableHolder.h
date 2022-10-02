#pragma once

#include "al/Factory/ActorFactory.h"
#include "al/System/Byaml/ByamlIter.h"

namespace al {

class CreatorClassNameTableHolder {
    void* unk = nullptr;
    ByamlIter* mTable = nullptr;

public:
    CreatorClassNameTableHolder() = default;

    CreateActorFunctionT getCreator(const char* objectName) const;
};

} // namespace al