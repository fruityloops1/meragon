#pragma once

#include "types.h"

namespace al {

class ByamlHeader {
public:
    u16 getTag() const;
    bool isInvertOrder() const;
    u16 getVersion() const;
    u32 getHashKeyTableOffset() const;
    u32 getStringTableOffset() const;
    u32 getDataOffset() const;

private:
    union {
        int _0;
        unsigned short mTag, mVersion; // unusable due to different loading mechanisms
    };

    int mHashKeyOffset;
    int mStringTableOffset;
    int mDataOffset;
};

} // namespace al