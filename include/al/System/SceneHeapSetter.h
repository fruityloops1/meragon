#pragma once

#include "sead/heap/seadHeap.h"

namespace al {

class SceneHeapSetter {
    sead::Heap* mHeaps[2] { nullptr };

public:
    SceneHeapSetter();
};

} // namespace al