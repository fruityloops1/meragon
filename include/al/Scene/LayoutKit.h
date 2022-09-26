#pragma once

namespace al {

class FontHolder;
class LayoutKit {
    void* unk = nullptr;
    FontHolder* mFontHolder = nullptr;
    void* unk2[4] { nullptr };

public:
    LayoutKit(FontHolder*);
};

} // namespace al