#include "al/Audio/AudioKeeper.h"
#include "al/Effect/EffectFunction.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "mg/Abort.h"
#include "nw/font/Font.h"

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
        mg::abortWithMessage("Font attempted to be used with wchar_t, but font does not use Unicode");
    return code;
}

HK_BL_HOOK_FUNC(CheckFontWchar, 0x00343c9c, nwWcharFontCharacterCodeCheck)
