#include "Game/Player/PlayerFigureDirector.h"
#include "Game/Player/PlayerModelHolder.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"
#include <sead/basis/seadNew.h>

namespace mg {

#define MG_ENABLE_FIGURE_MOD

#ifdef MG_ENABLE_FIGURE_MOD

// PlayerFigureDirector patches

static const EPlayerFigure cPowerDownStates[8] {
    EPlayerFigure_Mini, // EPlayerFigure_Normal
    EPlayerFigure_Mini, // EPlayerFigure_Mini
    EPlayerFigure_Normal, // EPlayerFigure_Fire
    EPlayerFigure_Normal, // EPlayerFigure_RaccoonDog
    EPlayerFigure_Normal, // EPlayerFigure_Boomerang
    EPlayerFigure_Normal, // EPlayerFigure_RaccoonDogSpecial
    EPlayerFigure_RaccoonDogWhite, // EPlayerFigure_RaccoonDogWhite
    EPlayerFigure_Normal, // Custom
};

static void playerFigureLossUpdateHook(EPlayerFigure* out, PlayerFigureLoss* thisPtr, const EPlayerFigure& figure)
{
    *out = cPowerDownStates[(int)figure];
}

HK_B_HOOK_FUNC(PlayerFigureLossUpdate, 0x0036bc2c, playerFigureLossUpdateHook);

static const int cFigureChangedSeTable[8][8] {
    { -1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, -1, 0, 0, 0, 0, 0, 0 },
    { 1, 1, -1, 0, 0, 0, 0, 0 },
    { 1, 1, 0, -1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, -1, 0, 0, 0 },
    { 1, 1, 0, 0, 0, -1, 0, 0 },
    { 1, 1, 1, 1, 1, 1, -1, 0 },
    { 1, 1, 0, 0, 0, 0, 0, -1 }
};

HK_TYPE_PATCH(PlayerFigureDirectorTable, 0x0026e1d8, const int*, reinterpret_cast<const int*>(cFigureChangedSeTable));
HK_PATCH_ASM(PlayerFigureDirectorIndex, 0x0026e188, "mov r1, r1, lsl #0x3"); // (size 7 -> 8)

static int cFigureTransformerTable[8][8] {
    {
        EPlayerFigure_Normal,
        EPlayerFigure_Normal,
        EPlayerFigure_Fire,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_Boomerang,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_Mini,
        EPlayerFigure_Mini,
        EPlayerFigure_Normal,
        EPlayerFigure_Normal,
        EPlayerFigure_Normal,
        EPlayerFigure_Normal,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_Fire,
        EPlayerFigure_Fire,
        EPlayerFigure_Fire,
        EPlayerFigure_Fire,
        EPlayerFigure_Fire,
        EPlayerFigure_Fire,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDog,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_Boomerang,
        EPlayerFigure_Boomerang,
        EPlayerFigure_Boomerang,
        EPlayerFigure_Boomerang,
        EPlayerFigure_Boomerang,
        EPlayerFigure_Boomerang,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogSpecial,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },

    {
        7,
        7,
        7,
        7,
        7,
        7,
        EPlayerFigure_RaccoonDogWhite,
        7,
    },
};

static void playerFigureTransformerUpdateHook(EPlayerFigure* out, PlayerFigureTransformer* thisPtr, const EPlayerFigure& lastFigure, const EPlayerFigure& newFigure)
{
    *out = (EPlayerFigure)cFigureTransformerTable[lastFigure][newFigure];
}

HK_B_HOOK_FUNC(PlayerFigureTransformerUpdate, 0x0036bc44, playerFigureTransformerUpdateHook);

// PlayerModelHolder patches

HK_PATCH_ASM(PlayerModelHolderSize, 0x00131dec, "mov r0, #0x58");

// we are adding an extra entry to mModels, so we have to move mCurrentFigure to the end of the class (0x2c -> 0x54)

// first vtable
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove1, 0x00182624, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove2, 0x0018251c, "ldr r0, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove3, 0x001825b4, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove4, 0x0018268c, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove5, 0x001825f8, "ldr r0, [r4, #0x54]");

// second
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove6, 0x00376210, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove7, 0x003761e0, "ldr r0, [r4, #0x54]");

// fourth
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove8, 0x00375dbc, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove9, 0x00375d8c, "ldr r0, [r4, #0x54]");

// PlayerModelHolder::change
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove10, 0x0018271c, "ldr r0, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove11, 0x0018274c, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove12, 0x00182784, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove13, 0x001827b4, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove14, 0x001827e4, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove15, 0x00182814, "ldr r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove16, 0x00182830, "ldr r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove17, 0x0018284c, "ldr r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove18, 0x00182868, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove19, 0x001828a0, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove20, 0x001828c0, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove21, 0x001828e0, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove22, 0x00182918, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove23, 0x00182950, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove24, 0x00182970, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove25, 0x00182990, "ldr r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove26, 0x00182bcc, "ldr r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove27, 0x00182bfc, "ldr r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove28, 0x00182c10, "str r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove62, 0x00182ba8, "ldr r1, [r4, #0x54]");

// Constructor
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove29, 0x00182c64, "str r1, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove30, 0x00182e34, "str r0, [r4, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove31, 0x00182e38, "ldr r0, [r4, #0x54]");

// PlayerAnimator
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove32, 0x0014f500, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove33, 0x0014f134, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove34, 0x0014f1b4, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove35, 0x0014f304, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove36, 0x0014f250, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove37, 0x0014f064, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove38, 0x0014f0d8, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove39, 0x00327f10, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove40, 0x00327f40, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove41, 0x0014f2dc, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove42, 0x00327f94, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove50, 0x0014f2a4, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove52, 0x0014f3f4, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove53, 0x0014f448, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove54, 0x0014f41c, "ldr r1, [r0, #0x54]");

// Some other class i don't know the name of

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove43, 0x003274e0, "ldr r2, [r0, #0x54]");

// PlayerActor

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove44, 0x001312c4, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove45, 0x001312dc, "ldr r1, [r0, #0x54]");

// random shit (most classes are owned by Player)
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove46, 0x002d41dc, "ldr r1, [r2, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove47, 0x002d41a4, "ldr r1, [r2, #0x54]");

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove48, 0x00132d28, "ldr r1, [r0, #0x54]"); // PlayerAudio::update

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove49, 0x001329f8, "ldr r1, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove51, 0x0026ddb0, "ldr r1, [r0, #0x54]");

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove55, 0x001bb24c, "ldr r1, [r0, #0x54]"); // PlayerMoveActionEffectControl

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove56, 0x0027be84, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove57, 0x002796a8, "ldr r2, [r0, #0x54]");

HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove58, 0x00273b04, "ldr r3, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove59, 0x00326c18, "ldr r3, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove60, 0x00326c34, "ldr r2, [r0, #0x54]");
HK_PATCH_ASM(PlayerModelHolderCurrentFigureMove61, 0x00132c9c, "ldr r2, [r0, #0x54]");

struct FakePlayerModelHolder {
    void* _0[4];

    PlayerModel* mModels[8];
    bool _30;
    bool mIsHidden;
    bool mIsShadowHidden;
    bool mIsSilhouetteHidden;
    void* _34[8];
    EPlayerFigure mCurrentFigure;
};

PlayerModelHolder* playerModelHolderCtorHook(PlayerModelHolder* thisPtr, const al::ActorInitInfo& info, const PlayerActorInitInfo& playerInfo, const sead::Vector3f* transPtr, const sead::Vector3f* rotatePtr, void* a, void** b)
{
    new (thisPtr) PlayerModelHolder(info, playerInfo, transPtr, rotatePtr, a, b);

    FakePlayerModelHolder* instance = reinterpret_cast<FakePlayerModelHolder*>(thisPtr);
    PlayerModel* newModel = PlayerModelHolder::createBoomerangPlayerModel(info, playerInfo, transPtr, rotatePtr, a);
    instance->mModels[7] = newModel;
    newModel->initJoints(instance->mIsShadowHidden);
    instance->_34[7] = newModel->createMtx();
    return thisPtr;
}

HK_BL_HOOK_FUNC(PlayerModelHolderCtor, 0x00131e34, playerModelHolderCtorHook);

#endif

} // namespace mg
