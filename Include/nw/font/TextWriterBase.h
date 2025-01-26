#pragma once

#include "nw/font/CharWriter.h"

namespace nw::font {

template <typename CharType>
class TextWriterBase : public CharWriter {
    u8 _4C[0x1C];

public:
    TextWriterBase();
    ~TextWriterBase();

    void Print(const CharType* str, int);
    void PrintImpl(const CharType* str, int);
};

} // namespace nw::font
