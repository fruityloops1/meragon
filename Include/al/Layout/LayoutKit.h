#pragma once

#include "al/Execute/ExecuteDirector.h"

namespace al {

class LayoutKit {
    void* _0;
    class FontHolder* mFontHolder;

public:
    ExecuteDirector* mExecuteDirector;
    void* _C;
    void* _10;
    void* _14;

    LayoutKit(FontHolder* fontHolder);

    void createExecuteDirector(int p);
    void createEffectSystem();
    void update();
};

} // namespace al
