#pragma once

#include "hk/Types.h"

namespace mg {

extern "C" const u8 cShiftJisConvTable[2 * (256 + 3 * 256 * 16)];

inline void convShiftJisToWide(char16_t* output, const char* input, size_t inputLength)
{
    size_t indexInput = 0, indexOutput = 0;

    while (indexInput < inputLength) {
        char arraySection = ((uint8_t)input[indexInput]) >> 4;

        size_t arrayOffset;
        if (arraySection == 0x8)
            arrayOffset = 0x100; // these are two-byte shiftjis
        else if (arraySection == 0x9)
            arrayOffset = 0x1100;
        else if (arraySection == 0xE)
            arrayOffset = 0x2100;
        else
            arrayOffset = 0; // this is one byte shiftjis

        // determining real array offset
        if (arrayOffset) {
            arrayOffset += (((uint8_t)input[indexInput]) & 0xf) << 8;
            indexInput++;
            if (indexInput >= inputLength)
                break;
        }
        arrayOffset += (uint8_t)input[indexInput++];
        arrayOffset <<= 1;

        // unicode number is...
        char16_t unicodeValue = (cShiftJisConvTable[arrayOffset] << 8) | cShiftJisConvTable[arrayOffset + 1];

        output[indexOutput++] = unicodeValue;
    }
}

} // namespace mg
