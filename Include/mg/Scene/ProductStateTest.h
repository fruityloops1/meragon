#pragma once

#include "Game/Scene/StageScene.h"
#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Nerve/HostStateBase.h"
#include "mg/Scene/TestScene.h"

class ProductSequence;
class ProductStateTest : public al::HostStateBase<ProductSequence> {
    mg::TestScene* mScene = nullptr;
    ProductStageStartParam* mStartParam = nullptr;

    void startInitScene();

public:
    ProductStateTest(ProductSequence* parent, ProductStageStartParam* startParam);

    void init() override;
    void appear() override;

    void exeLoad();
    void exeWait();
};