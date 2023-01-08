#pragma once

#include "al/Scene/Scene.h"

namespace mg {

class TestScene : public al::Scene {
public:
    TestScene();

    void init() override;

    void exeWait();
};

} // namespace mg