#include "al/Audio/AudioKeeper.h"
#include "al/Effect/EffectFunction.h"
#include "al/Layout//NarcLayoutResourceAccessor.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include "mg/Abort.h"
#include "nw/font/Font.h"
#include "nw/ut/BinaryFileHeader.h"

/* SoundDataBase/EffectDataBase */

static al::SeUserInfo* checkSeUserName(al::AudioInfoList<al::SeUserInfo>* list, const sead::SafeString& userName)
{
    auto* user = list->tryFindInfo(userName);

    if (user == nullptr)
        mg::abortWithMessage("SeUserName '%s' was not found", userName.cstr());

    return user;
}

HK_BL_HOOK_FUNC(CheckSeUserNameHook, 0x001bf55c, checkSeUserName)

static al::EffectUserInfo* checkEffectUserName(al::EffectSystemInfo* info, const char* userName)
{
    auto* user = alEffectFunction::tryFindEffectUser(info, userName);

    if (user == nullptr)
        hk::dbg::Log("warning: EffectUserName '%s' was not found", userName);

    return user;
}

HK_BL_HOOK_FUNC(CheckEffectUserNameHook, 0x001bfcdc, checkEffectUserName)

/* NW Font */

static nw::font::CharacterCode nwWcharFontCharacterCodeCheck(nw::font::Font* font)
{
    nw::font::CharacterCode code = font->GetCharacterCode();
    if (code != nw::font::CharacterCode_Unicode)
        mg::abortWithMessage("Font attempted to be used with wide characters, but font does not use Unicode (uses %s)", nw::font::GetCharacterCodeName(code));
    return code;
}

HK_BL_HOOK_FUNC(CheckFontWchar, 0x00343c9c, nwWcharFontCharacterCodeCheck)

/* NW Layout */

static void* getLayoutResourceHook(al::NarcLayoutResourceAccessor* accessor, u32 type, const char* name, u32* outSize)
{
    void* data = accessor->NarcLayoutResourceAccessor::GetResource(type, name, outSize);

#ifdef LOG_FILE_ACCESS
    hk::dbg::Log("NarcLayoutResourceAccessor::GetResource(this=%p,%x,%s,%p) = %p", accessor, type, name, outSize, data);
#endif

    if (data == nullptr)
        mg::abortWithMessage("File '%s' of type %08x not found within layout resource", name, type);

    return data;
}

HK_PATCH(CheckLayoutResource, 0x003d6428, &getLayoutResourceHook)

/* NW generic */

template <TemplateString Fmt>
static bool isValidBinaryFileHook(const nw::ut::BinaryFileHeader* header, u32 magic, u32 version, u16 numSectionsMin)
{
    bool valid = nw::ut::IsValidBinaryFile(header, magic, version, numSectionsMin);

    if (!valid) {
        u8 file[0x100];
        memcpy(file, header, sizeof(file));
        (void)file;

        mg::abortWithMessage("NW %s file header not valid\nmagic: %.4s bom: %x headerLen: %x ver: %x size: %x sections: %d", Fmt.value, header->magic, header->bom, header->headerLen, header->version, header->fileSize, header->numSections);
    }

    return valid;
}

HK_BL_HOOK(CheckNwMagicBclyt, 0x002b850c, isValidBinaryFileHook<"layout">)
HK_BL_HOOK(CheckNwMagicBclim, 0x002b5350, isValidBinaryFileHook<"texture">)
HK_BL_HOOK(CheckNwMagicBclan, 0x002b5408, isValidBinaryFileHook<"layout animation">)
HK_BL_HOOK(CheckNwMagicBcfnt, 0x002cc128, isValidBinaryFileHook<"font">)
HK_BL_HOOK(CheckNwMagicBcfnt2, 0x002cc2e8, isValidBinaryFileHook<"font">)
