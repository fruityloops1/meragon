#pragma once

#include "al/nerve/HostStateBase.h"

class ProductSequence;
class ProductStateStage : public al::HostStateBase<ProductStateStage> {
    u8 unk[0x2c];

public:
    ProductStateStage(ProductSequence* parent /*, ... */);
    void init() override;
    void appear() override;
};