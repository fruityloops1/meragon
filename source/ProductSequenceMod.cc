#include "al/nerve/NerveKeeper.h"
#include "al/nerve/NerveStateBase.h"
#include "al/util/NerveUtil.h"
#include "game/sequence/ProductSequence.h"
#include "mg/scene/ProductStateTest.h"

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