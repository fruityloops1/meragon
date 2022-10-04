#include "Game/Sequence/ProductSequence.h"
#include "al/Nerve/NerveKeeper.h"
#include "al/Nerve/NerveStateBase.h"
#include "al/Util/InputUtil.h"
#include "al/Util/NerveUtil.h"
#include "mg/Freecam.h"
#include "mg/Scene/ProductStateTest.h"
#include "mg/log.h"
#include "sead/heap/seadHeapMgr.h"

namespace {

NERVE_DEF(ProductSequence, Test);

}

void ProductSequence::exeTest()
{
    if (al::isFirstStep(this))
        for (al::WipeSimpleTopBottom* wipe : mWipeKeeper->mWipes) {
            wipe->getTop()->kill();
            wipe->getBottom()->kill();
        }

    if (al::updateNerveState(this))
        al::setNerve(this, (const al::Nerve*)0x003ef538);
}

export void productSequenceStateInitHook(al::IUseNerve* _sequence, al::NerveStateBase* state, al::Nerve* stateNrv, const char* name)
{
    al::initNerveState(_sequence, state, stateNrv, name);
    ProductSequence* sequence = static_cast<ProductSequence*>(_sequence);

    sequence->mStateTest = new ProductStateTest(sequence);
    al::initNerveState(sequence, sequence->mStateTest, &nrvProductSequenceTest, "Test");
}

export void testStateNerveHook(ProductSequence* sequence, const al::Nerve* nerve)
{
    al::setNerve(sequence, &nrvProductSequenceTest);
}

static int tabAmount = 0;
static char tabBuffer[256] { 0 };

void updateTabs()
{
    for (int i = 0; i < tabAmount; i++) {
        tabBuffer[i] = '\t';
    }
    tabBuffer[tabAmount] = '\0';
};

void printHeap(sead::Heap* heap)
{
    updateTabs();
    mg::log("%s%s: ", tabBuffer, heap->getName().cstr());
    mg::log("%s\tSize: %d Bytes (%d KB, %d MB)", tabBuffer, heap->mSize, heap->mSize / 1000, heap->mSize / 1000000);
    // mg::log("%s\tFree: %d Bytes (%d KB, %d MB)", tabBuffer, free, free / 1000, free / 1000000);
    mg::log("%s\tStart: 0x%x End: 0x%x", tabBuffer, heap->mStart, (uintptr_t)heap->mStart + heap->mSize);
    for (sead::Heap& child : heap->mChildren) {
        tabAmount++;
        updateTabs();
        printHeap(&child);
        tabAmount--;
    }
};

export void productSequenceUpdateHook(ProductSequence* sequence)
{
    sequence->al::Sequence::update();
    mg::updateFreecam();

    if (al::isPadHoldStart() && al::isPadTriggerTouch())
        printHeap(sead::HeapMgr::sRootHeaps[0]);
}