#pragma once

#include "al/Layout/LayoutActor.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "hk/hook/TypePatch.h"

static void appearStub(al::LayoutActor*) { }

HK_BL_HOOK(DisableCounterTimeLimitFirstAppear, 0x00176f04, appearStub);
HK_TYPE_PATCH(DisableCounterTimeLimitAppear, 0x003ccb14, typeof(appearStub)*, appearStub);
