#pragma once

#include "Game/Sequence/ProductStageStartParam.h"
#include "al/Scene/Scene.h"

class CourseSelectScene : public al::Scene {
public:
    ProductStageStartParam* mStageStartParam = nullptr;
    u8 unk[0x34];
};
