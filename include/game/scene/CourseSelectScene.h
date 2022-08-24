#pragma once

#include "al/scene/Scene.h"
#include "game/sequence/ProductStageStartParam.h"

class CourseSelectScene : public al::Scene {
public:
    ProductStageStartParam* mStageStartParam = nullptr;
    u8 unk[0x34];
};
