#pragma once

#include "al/nerve/HostStateBase.h"
#include "game/scene/StageScene.h"
#include "game/sequence/ProductStageStartParam.h"

class ProductSequence;
class ProductStateStage : public al::HostStateBase<ProductSequence> {
    ProductStageStartParam* mStageStartParam = nullptr;
    ProductStageStartParam* mLastStageStartParam = nullptr;
    StageScene* mStageScene = nullptr;
    u8 unk[0x20];

public:
    ProductStateStage(ProductSequence* parent /*, ... */);
    void init() override;
    void appear() override;
};