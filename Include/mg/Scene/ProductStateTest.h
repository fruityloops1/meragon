#pragma once

#include "Game/Scene/StageScene.h"
#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Nerve/HostStateBase.h"
#include "mg/Scene/TestScene.h"

class ProductSequence;
class ProductStateTest : public al::HostStateBase<ProductSequence> {
    mg::TestScene* mScene = nullptr;

public:
    ProductStateTest(ProductSequence* parent);

    void init() override;
    void appear() override;

    void exeLoad();
    void exeWait();
};