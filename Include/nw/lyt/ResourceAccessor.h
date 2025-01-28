#pragma once

#include "hk/Types.h"
#include "nw/font/Font.h"

namespace nw::lyt {

class ResourceAccessor {
public:
    virtual ~ResourceAccessor();
    virtual void* GetResource(u32 type, const char* name, u32* outSize);
    virtual font::Font* GetFont(const char* name);
    virtual void GetTexture(const char* name);
    virtual void LoadTexture(const char* name);
    virtual font::Font* LoadFont(const char* name);
};

} // namespace nw::lyt
