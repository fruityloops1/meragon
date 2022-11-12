#pragma once

#include "Game/Player/PlayerActor.h"
#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Scene/Scene.h"

class StageScene : public al::Scene {
public:
    StageScene(ProductStageStartParam* stageStartParam);

    ProductStageStartParam* mStageStartParam = nullptr;
    PlayerActor* mPlayerActor = nullptr;
    void* unk[9];
    class StageSceneStateGameOver* mStateGameOver = nullptr;
    void* unk2[14];

    void appear() override;
    void control() override;
};
