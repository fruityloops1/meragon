#pragma once

#include "al/Nerve/HostStateBase.h"
#include "game/Scene/StageScene.h"
#include "game/Sequence/ProductStageStartParam.h"

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