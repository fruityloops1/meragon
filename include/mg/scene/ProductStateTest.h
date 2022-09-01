#pragma once

#include "al/nerve/HostStateBase.h"
#include "game/scene/StageScene.h"
#include "game/sequence/ProductStageStartParam.h"
#include "mg/scene/TestScene.h"

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