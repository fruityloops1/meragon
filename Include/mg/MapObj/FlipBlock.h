#pragma once

#include "al/MapObj/MapObjActor.h"

namespace mg {

class FlipBlock : public al::MapObjActor {
public:
    FlipBlock(const sead::SafeString& name)
        : MapObjActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;

    void exeWait();
};

} // namespace mg
