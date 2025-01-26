#include "al/Layout/LayoutActor.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Placement/PlacementFunction.h"
#include "mg/MapObj/SnakeBlock.h"

namespace mg {

namespace NrvSnakeBlock {

    NERVE_DEF(SnakeBlock, Wait);
    NERVE_DEF(SnakeBlock, Move);
    NERVE_DEF(SnakeBlock, Stall);

} // namespace NrvSnakeBlock

void SnakeBlock::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "SnakeBlock");
    al::initNerve(this, &NrvSnakeBlock::Wait);

    al::tryGetArg0(&pBlockCount, info);
    al::tryGetArg1(&pMoveSpeed, info);
    al::tryGetArg2(&pGapBetweenBlocks, info);

    if (pBlockCount == 0)
        return;

    {
        SnakeBlock* cur = this;
        for (int i = 0; i < pBlockCount - 1; i++) {
            cur->mNextBlock = new SnakeBlock("SnakeBlock Child");
            cur = cur->mNextBlock;
            cur->mRootBlock = this;
        }
    }

    if (mRootBlock == nullptr)
        makeActorAppeared();
}

void SnakeBlock::exeWait()
{
}

void SnakeBlock::exeMove()
{
}

void SnakeBlock::exeStall()
{
}

} // namespace mg
