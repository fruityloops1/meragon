#pragma once

#include "al/Layout/WipeSimple.h"

namespace al {

class WipeSimpleTopBottom {
    WipeSimple* mTop = nullptr;
    WipeSimple* mBottom = nullptr;

public:
    WipeSimpleTopBottom(const char* name, const char* archive, const char*, const LayoutInitInfo& info, const char* subArchive);

    inline WipeSimple* getTop() const { return mTop; }
    inline WipeSimple* getBottom() const { return mBottom; }
};

} // namespace al