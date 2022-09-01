#pragma once

#include "sead/container/seadPtrArray.h"

namespace al {

void createSceneHeap(const char* stageName);
void createCourseSelectHeap();
sead::Heap* getCourseSelectHeap();

} // namespace al