#pragma once

#include "types.h"

namespace al {

class ByamlHeader {
    const u16 mTag = 0;
    const u16 mVersion = 0;
    const int mHashKeyOffset = 0;
    const int mStringTableOffset = 0;
    const int mDataOffset = 0;

public:
    u16 getTag() const { return mTag; }
    u16 getVersion() const { return mVersion; }
    u32 getHashKeyTableOffset() const { return mHashKeyOffset; }
    u32 getStringTableOffset() const { return mStringTableOffset; };
    u32 getDataOffset() const { return mDataOffset; };
};

} // namespace al

namespace alByamlLocalUtil {

bool verifiByaml(const u8* data);

} // namespace alByamlLocalUtil
