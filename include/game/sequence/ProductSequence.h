#pragma once

#include "al/sequence/Sequence.h"
#include "game/sequence/ProductStageStartParam.h"
#include "game/sequence/states/ProductStateStage.h"

class ProductSequence : public al::Sequence {
    ProductStageStartParam* mStageStartParam = nullptr;
    void* unk[5];
    class ProductStateTitle* mStateTitle = nullptr;
    class ProductStateOpening* mStateOpening = nullptr;
    class ProductStateCourseSelect* mStateCourseSelect = nullptr;
    ProductStateStage* mStateStage = nullptr;
    class ProductStateKinopioHouse* mStateKinopioHouse = nullptr;
    class ProductStateMysteryBox* mStateMysteryBox = nullptr;
    class ProductStateEnding* mStateEnding = nullptr;
    class ProductStateGameOverRoom* mStateGameOverRoom = nullptr;
    int unk2;
    void* unk3[4];

public:
    ProductSequence(const char* name);

    void init() override;
    void update() override;
    bool isDisposable() const override;
};