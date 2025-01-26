#pragma once

#include <sead/thread/seadCriticalSection.h>

namespace sead {
class DrawLockContext {
public:
    DrawLockContext();

    void initialize(Heap* heap);
    void lock();
    void unlock();

private:
    [[maybe_unused]] u32 _8 = 0;
    CriticalSection mCriticalSection {};
};

} // namespace sead
