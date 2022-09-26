#pragma once

#include "al/Scene/Scene.h"
#include "game/Sequence/ProductStageStartParam.h"

class CourseSelectScene : public al::Scene {
public:
    ProductStageStartParam* mStageStartParam = nullptr;
    u8 unk[0x34];
};
