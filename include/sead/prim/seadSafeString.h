#pragma once

#include "sead/basis/seadRawPrint.h"
#include "sead/basis/seadTypes.h"
#include <stdarg.h>

namespace sead {

template <typename T>
class SafeStringBase {
public:
    SafeStringBase()
        : mStringTop(&cNullChar)
    {
    }
    SafeStringBase(const T* str)
        : mStringTop(str)
    {
        SEAD_ASSERT_MSG(str != nullptr, "str must not be nullptr.");
    }
    SafeStringBase(const SafeStringBase& other) = default;

    inline const T* cstr() const
    {
        return mStringTop;
    }

    virtual void dummy() {};

    static const T cNullChar;
    static const T cLineBreakChar;
    static const SafeStringBase cEmptyString;
    static const s32 cMaximumLength = 0x80000;

protected:
    const T& unsafeAt_(s32 idx) const { return mStringTop[idx]; }

    const T* mStringTop;
};

typedef SafeStringBase<char> SafeString;

} // namespace sead