#pragma once

#include "al/Layout/LayoutActor.h"
#include "al/Layout/LayoutInitInfo.h"

class WindowConfirmSingle : public al::LayoutActor {
    void* unk;

public:
    WindowConfirmSingle(const char* name, const al::LayoutInitInfo& info);
    void appear() override;
};