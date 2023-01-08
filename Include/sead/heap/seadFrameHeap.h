#pragma once

#include <sead/heap/seadHeap.h>

namespace sead {
class FrameHeap : public Heap {
    SEAD_RTTI_OVERRIDE(FrameHeap, Heap)
public:
    struct State {
        void* mHeadPtr;
        void* mTailPtr;
    };

    static FrameHeap* tryCreate(size_t size, const SafeString& name, Heap* parent, s32,
        HeapDirection direction, bool);
    static FrameHeap* create(size_t size, const SafeString& name, Heap* parent, s32,
        HeapDirection direction, bool);

    static size_t getManagementAreaSize(s32);

    void restoreState(const State& state);
    void freeHead();
    void freeTail();

    virtual void destroy() override;
    virtual size_t adjust() override;
    virtual void* tryAlloc(size_t size, s32 alignment) override;
    virtual void free(void* ptr) override;
    virtual void* resizeFront(void* p_void, size_t size) override;
    virtual void* resizeBack(void* p_void, size_t size) override;
    virtual void freeAll() override;
    virtual uintptr_t getStartAddress() const override;
    virtual uintptr_t getEndAddress() const override;
    virtual size_t getSize() const override;
    virtual size_t getFreeSize() const override;
    virtual size_t getMaxAllocatableSize(int alignment) const override;
    virtual bool isInclude(const void* p_void) const override;
    virtual bool isEmpty() const override;
    virtual bool isFreeable() const override;
    virtual bool isResizable() const override;
    virtual bool isAdjustable() const override;
    virtual void dump() const override;
    virtual void dumpYAML(WriteStream& stream, int i) const override;
    virtual void genInformation_(hostio::Context* context) override;

protected:
    FrameHeap(const SafeString& name, Heap* parent, void* address, size_t size,
        HeapDirection direction, bool);
    virtual ~FrameHeap();

    void initialize_();
    void* getAreaStart_() const;
    void* getAreaEnd_() const;

    State mState;
};
} // namespace sead
