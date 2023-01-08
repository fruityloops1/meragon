#pragma once

#include "Game/Scene/StageScene.h"
#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Nerve/HostStateBase.h"

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