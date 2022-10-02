#pragma once

#include "al/System/Byaml/ByamlIter.h"

namespace al {

class ActorInitInfo {
public:
    ByamlIter* mPlacementInfo = nullptr;
    void* unk[5] { nullptr };
};

void initActorInitInfo(ActorInitInfo* info, const ByamlIter* placement, const ActorInitInfo& baseInfo);

} // namespace al