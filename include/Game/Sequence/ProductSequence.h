#pragma once

#include "Game/Sequence/ProductStageStartParam.h"
#include "Game/Sequence/States/ProductStateStage.h"
#include "Game/Stage/StageWipeKeeper.h"
#include "al/Sequence/Sequence.h"
#include "mg/Scene/ProductStateTest.h"

class ProductSequence : public al::Sequence {
    ProductStageStartParam* mStageStartParam = nullptr;
    void* unk[2];

public:
    StageWipeKeeper* mWipeKeeper = nullptr;
    void* unk2[2];
    class ProductStateTitle* mStateTitle = nullptr;
    class ProductStateOpening* mStateOpening = nullptr;
    class ProductStateCourseSelect* mStateCourseSelect = nullptr;
    ProductStateStage* mStateStage = nullptr;
    class ProductStateKinopioHouse* mStateKinopioHouse = nullptr;
    class ProductStateMysteryBox* mStateMysteryBox = nullptr;
    class ProductStateEnding* mStateEnding = nullptr;
    class ProductStateGameOverRoom* mStateGameOverRoom = nullptr;
    int unk3;
    void* unk4[4];

    ProductStateTest* mStateTest = nullptr; // fake

    ProductSequence(const char* name);

    void init() override;
    void update() override;
    bool isDisposable() const override;

    void exeTest(); // fake
};