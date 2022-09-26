#pragma once

#include "al/Layout/LayoutActor.h"

namespace al {

class WipeSimple : public LayoutActor {
    int unk;

public:
    WipeSimple(const char* name, const char* archive, const LayoutInitInfo& info, const char* subArchive);

    void appear() override;
};

} // namespace al