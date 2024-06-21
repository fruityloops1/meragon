#pragma once

#ifndef SEAD_PRIM_SAFE_STRING_H_
#include <sead/prim/seadSafeString.h>
#endif
#include <string.h>

namespace sead {

template <typename T>
inline s32 BufferedSafeStringBase<T>::copy(const SafeStringBase<T>& src, s32 copyLength)
{
    T* dst = getMutableStringTop_();
    const T* csrc = src.cstr();
    if (dst == csrc)
        return 0;

    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize) {
        SEAD_ASSERT_MSG(false, "Buffer overflow. (Buffer Size: %d, Copy Size: %d)", mBufferSize,
            copyLength);
        copyLength = mBufferSize - 1;
    }

    memcpy(dst, csrc, copyLength * sizeof(T));
    dst[copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

template <typename T>
inline s32 SafeStringBase<T>::calcLength() const
{
    SEAD_ASSERT(mStringTop);
    assureTerminationImpl_();
    s32 length = 0;

    for (;;) {
        if (length > cMaximumLength || mStringTop[length] == cNullChar)
            break;

        length++;
    }

    if (length > cMaximumLength) {
        SEAD_ASSERT_MSG(false, "too long string");
        return 0;
    }

    return length;
}

} // namespace sead
