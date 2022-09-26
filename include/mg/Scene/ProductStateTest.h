#pragma once

#include "al/Nerve/HostStateBase.h"
#include "game/Scene/StageScene.h"
#include "game/Sequence/ProductStageStartParam.h"
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