#pragma once

#include "al/nerve/nerve.h"
#include "al/nerve/nervekeeper.h"
#include "sead/prim/seadSafeString.h"
namespace al {

class LayoutActor : public al::IUseNerve {
public:
    LayoutActor(const char* name);

    virtual NerveKeeper* getNerveKeeper() const override;
    virtual void appear();
    virtual void kill();

protected:
    sead::SafeString mName;
    NerveKeeper* mNerveKeeper = nullptr;
    sfill(0x14, gap);
};

} // namespace al