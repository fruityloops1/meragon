#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

class WindowConfirmSingle : public al::LayoutActor {
    void* unk;

public:
    WindowConfirmSingle(const char* name, const al::LayoutInitInfo& info);
    void appear() override;
};