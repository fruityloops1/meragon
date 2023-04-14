#include "mg/MapObj/FlipBlock.h"
#include "al/Layout/LayoutActor.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"

namespace mg {

namespace NrvFlipBlock {

    NERVE_DEF(FlipBlock, Wait);

} // namespace NrvFlipBlock

void FlipBlock::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "FlipBlock");
    al::initNerve(this, &NrvFlipBlock::Wait);

    makeActorAppeared();
}

void FlipBlock::exeWait()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Wait");
}

} // namespace mg
