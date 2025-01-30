#pragma once

namespace nw::font {

enum CharacterCode {
    CharacterCode_Unicode = 1,
    CharacterCode_ShiftJis,
    CharacterCode_ISO8859_1,
};

inline const char* GetCharacterCodeName(CharacterCode code)
{
    switch (code) {
    case CharacterCode_Unicode:
        return "Unicode";
    case CharacterCode_ShiftJis:
        return "ShiftJIS";
    case CharacterCode_ISO8859_1:
        return "ISO-8859-1";
    default:
        return "Unknown";
    }
}

class Font {
public:
    virtual ~Font();
    virtual int GetWidth();
    virtual int GetHeight();
    virtual int GetAscent();
    virtual int GetDescent();
    virtual int GetMaxCharWidth();
    virtual int GetType();
    virtual int GetTextureFormat();
    virtual int GetLineFeed();
    virtual void GetDefaultCharWidths();
    virtual void SetLineFeed(int);
    virtual void SetDefaultCharWidths(void*);
    virtual bool SetAlternateChar();
    virtual int GetCharWidth();
    virtual void GetCharWidths();
    virtual void GetGlyph();
    virtual bool HasGlyph();
    virtual CharacterCode GetCharacterCode();
};

} // namespace nw::font
