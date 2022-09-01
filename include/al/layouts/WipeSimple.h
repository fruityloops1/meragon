#pragma once

#include "al/layout/LayoutActor.h"

namespace al {

class WipeSimple : public LayoutActor {
    int unk;

public:
    WipeSimple(const char* name, const char* archive, const LayoutInitInfo& info, const char* subArchive);

    void appear() override;
};

} // namespace al