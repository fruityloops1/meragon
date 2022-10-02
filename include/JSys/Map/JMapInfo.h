#pragma once

#include "JSys/Map/JMapData.h"
#include "types.h"

class JMapInfo {
    JMapData* mData = nullptr;

public:
    bool getValueFast(int, int index, u64* out);
};