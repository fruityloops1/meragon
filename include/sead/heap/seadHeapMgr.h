#ifndef SEAD_HEAPMGR_H_
#define SEAD_HEAPMGR_H_

#include "sead/container/seadPtrArray.h"
#include "sead/heap/seadArena.h"
#include "sead/heap/seadHeap.h"
#include "sead/prim/seadDelegate.h"
#include "sead/prim/seadSafeString.h"
#include "sead/thread/seadAtomic.h"
#include "sead/thread/seadCriticalSection.h"
#include "sead/time/seadTickSpan.h"

namespace sead {
class HeapMgr {
    struct AllocFailedCallbackArg;
    struct AllocCallbackArg;
    struct CreateCallbackArg;
    struct DestroyCallbackArg;
    struct FreeCallbackArg;
    using IAllocFailedCallback = IDelegate1<const AllocFailedCallbackArg*>;
    using IAllocCallback = IDelegate1<const AllocCallbackArg*>;
    using ICreateCallback = IDelegate1<const CreateCallbackArg*>;
    using IDestroyCallback = IDelegate1<const DestroyCallbackArg*>;
    using IFreeCallback = IDelegate1<const FreeCallbackArg*>;

public:
    HeapMgr();
    virtual ~HeapMgr() { }

    static void initialize(size_t size);
    static void initializeImpl_();
    static void initialize(Arena* arena);
    static void createRootHeap_();
    static void destroy();
    void initHostIO();

    Heap* findContainHeap(const void* ptr) const;
    static bool isContainedInAnyHeap(const void* ptr);
    static void dumpTreeYAML(WriteStream& stream);
    void setAllocFromNotSeadThreadHeap(Heap* heap);
    static void removeFromFindContainHeapCache_(Heap* heap);

    Heap* findHeapByName(const SafeString& name, int index) const;
    static Heap* findHeapByName_(Heap*, const SafeString&, int* index);
    Heap* getCurrentHeap() const;

    static void removeRootHeap(Heap*);

    IAllocFailedCallback* setAllocFailedCallback(IAllocFailedCallback* callback);
    IAllocFailedCallback* getAllocFailedCallback() { return mAllocFailedCallback; }

    static HeapMgr* instance() { return sInstancePtr; }
    static s32 getRootHeapNum() { return sRootHeaps.size(); }

    // TODO: these should be private
    static Arena* sArena;
    static HeapMgr sInstance;
    static HeapMgr* sInstancePtr;

    using RootHeaps = FixedPtrArray<Heap, 4>;
    using IndependentHeaps = FixedPtrArray<Heap, 4>;

    sead::Heap* setCurrentHeap_(sead::Heap* heap);

    friend class ScopedCurrentHeapSetter;

    /// Set the current heap to the specified heap and returns the previous "current heap".

    static Arena sDefaultArena;
    static RootHeaps sRootHeaps;
    static IndependentHeaps sIndependentHeaps;
    static CriticalSection sHeapTreeLockCS;
    static TickSpan sSleepSpanAtRemoveCacheFailure;

private:
    /// fallback heap that is returned when getting the current heap outside of an sead::Thread
    Heap* mAllocFromNotSeadThreadHeap = nullptr;
    IAllocFailedCallback* mAllocFailedCallback = nullptr;
};

/// Sets the "current heap" to the specified heap and restores the previous "current heap"
/// when this goes out of scope.
class ScopedCurrentHeapSetter {
public:
    explicit ScopedCurrentHeapSetter(sead::Heap* heap)
    {
        if (heap)
            setPreviousHeap_(HeapMgr::instance()->setCurrentHeap_(heap));
        else
            setPreviousHeapToNone_();
    }

    ~ScopedCurrentHeapSetter()
    {
        if (hasPreviousHeap_())
            HeapMgr::instance()->setCurrentHeap_(getPreviousHeap_());
    }

protected:
    /// @warning Only call this if hasPreviousHeap returns true.
    Heap* getPreviousHeap_() const { return reinterpret_cast<Heap*>(mPreviousHeap); }
    void setPreviousHeap_(Heap* heap) { mPreviousHeap = reinterpret_cast<uintptr_t>(heap); }
    void setPreviousHeapToNone_() { mPreviousHeap = 1; }
    bool hasPreviousHeap_() const
    {
        // XXX: We cannot just do `mPreviousHeap != 1` because that results in different codegen.
        // The cast smells like implementation defined behavior, but 1 should not be a valid
        // pointer on any platform that we support. In practice, this will work correctly.
        return reinterpret_cast<Heap*>(mPreviousHeap) != reinterpret_cast<Heap*>(1);
    }

    uintptr_t mPreviousHeap;
};

class FindContainHeapCache {
public:
    FindContainHeapCache();

    bool tryRemoveHeap(Heap* heap);
    Heap* tryAddHeap()
    {
        mHeap |= 1;
        return reinterpret_cast<Heap*>(mHeap.load());
    }
    Heap* getHeap() const { return reinterpret_cast<Heap*>(mHeap.load()); }
    void setHeap(Heap* heap) { mHeap.storeNonAtomic(uintptr_t(heap)); }
    void resetHeap() { mHeap.fetchAnd(~1LL); }

    Atomic<uintptr_t> mHeap;
};

} // namespace sead

#endif // SEAD_HEAPMGR_H_
