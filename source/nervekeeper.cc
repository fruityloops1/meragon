#include "al/nerve/nervekeeper.h"
#include "al/nerve/nerve.h"

void al::NerveKeeper::setNerve(const al::Nerve* nerve)
{
    if (mStep > -1 && mEndNerve)
        mEndNerve->executeOnEnd(this);

    mNerve = nerve;
    mStep = -1;
}