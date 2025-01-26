#include "hk/hook/TypePatch.h"

HK_PATCH_FLOAT(WalkSpeed, 0x003efb18, 16.0 /* 14.0 */)
HK_PATCH_FLOAT(RunSpeed, 0x003efb1c, 23.5 /* 22.0 */)
HK_PATCH_FLOAT(TrampleJumpMomentumMultiplier, 0x003efbe8, 1.0 /* 0.1 */)