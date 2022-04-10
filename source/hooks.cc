#include "mg/hooks.h"
#include "mg/factory.h"
#include "mg/hook.h"
#include "mg/log.h"

void mg::initHooks()
{
    mg::log("[Hook] Loading hooks");

    mg::hookData(0x00268fb4, &mg::actorTable); // replace actor table pointer with ours

    // changes 'cmp r4, 0xe1' to 'cmp r4, actorTableEntryAmount' to change the size
    constexpr u8 actorTableEntryAmount = sizeof(mg::actorTable) / sizeof(mg::actorTable[0]);
    mg::hookData(0x00268f98, actorTableEntryAmount);
}