#pragma once

#include "al/scene/Scene.h"
#include "game/player/PlayerActor.h"
#include "game/sequence/ProductStageStartParam.h"

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