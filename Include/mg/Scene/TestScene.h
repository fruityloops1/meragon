#pragma once

#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Scene/Scene.h"

namespace mg {

class TestScene : public al::Scene {
    ProductStageStartParam* mStartParam;

public:
    TestScene(ProductStageStartParam* startParam);

    void init() override;
    void drawMainTop() override;
    void control() override;

    void exeWait();
};

} // namespace mg