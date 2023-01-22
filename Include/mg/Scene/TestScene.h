#pragma once

#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Scene/Scene.h"

namespace mg {

class TestScene : public al::Scene {
    ProductStageStartParam* mStartParam;

public:
    TestScene(ProductStageStartParam* startParam);

    void init() override;
    void drawMain() override;
    void control() override;
    void unk8() override;
    void unk9() override;

    void exeWait();
};

} // namespace mg