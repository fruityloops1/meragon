#include "mg/ProductSequenceMod.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Controller/ControllerUtil.h"
#include "al/Functor/FunctorV0M.h"
#include "al/Layout/WipeSimpleTopBottom.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveKeeper.h"
#include "al/Nerve/NerveStateBase.h"
#include "al/Nerve/NerveStateCtrl.h"
#include "al/System/AsyncFunctorThread.h"
#include "hk/debug/Log.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "mg/DebugMenu.h"
#include "mg/Freecam.h"
#include <sead/heap/seadHeapMgr.h>

namespace NrvProductSequence {

NERVE_DEF(ProductSequence, Test);

} // namespace

void ProductSequence::exeTest()
{
    if (al::updateNerveState(this)) {
        al::setNerve(this, (const al::Nerve*)0x003ef538);
    }
}

#include <nn/socket/socket.h>

class ServerThread {
    int mSocket = 0;
    nn::socket::SockAddr mHostAddr { 0, 2, nn::socket::Htons(7052), 0 };
    nn::socket::SockAddr mRemoteAddr { 0, 0, 0, 0 };
    al::AsyncFunctorThread* mThread = nullptr;

public:
    ServerThread()
    {
        hk::dbg::Log("Creating AsyncFunctorThread for ServerThread");
        mThread = new al::AsyncFunctorThread("ServerThread", al::FunctorV0M(this, &ServerThread::threadFunc), 0);
        mThread->start();
    }

    void init()
    {
        mSocket = nn::socket::Socket(2, 2, 0);
        hk::dbg::Log("nn::socket::Socket %d", mSocket);
        hk::dbg::Log("nn::socket::Bind %d", nn::socket::Bind(mSocket, &mHostAddr, sizeof(mHostAddr)));
    }

    void threadFunc()
    {
        init();

        u8 buf[0x500];
        size_t len = 0;
        u32 clientSize = sizeof(mRemoteAddr);

        while (true) {
            len = nn::socket::RecvFrom(mSocket, buf, sizeof(buf), 0, &mRemoteAddr, clientSize);
            hk::dbg::Log((char*)buf);
            nn::socket::SendTo(mSocket, buf, len, 0, &mRemoteAddr, clientSize);
        }
    }
};

void testStateNerveHook(ProductSequence* sequence, const al::Nerve* nerve)
{
    al::setNerve(sequence, &NrvProductSequence::Test);
}

// HK_B_HOOK_FUNC(TestStateNerveSetHook, 0x0036030c, testStateNerveHook);

ServerThread* gServerThread;

HK_PATCH_ASM(ProductSequenceSize, 0x0011a698, "mov r0, #0x198"); // size 0x194 -> 0x198

// static char socBuffer[0x1000];
void productSequenceStateInitHook(al::IUseNerve* _sequence, al::NerveStateBase* state, al::Nerve* stateNrv, const char* name)
{
    al::initNerveState(_sequence, state, stateNrv, name);
    ProductSequence* sequence = static_cast<ProductSequence*>(_sequence);

    hk::dbg::Log("Initializing ProductStateTest");
    sequence->mStateTest = new ProductStateTest(sequence, sequence->mStageStartParam);
    al::initNerveState(sequence, sequence->mStateTest, &NrvProductSequence::Test, "Test");

    // auto result = nn::socket::Initialize(nullptr, 0x1000);
    // printHeap(sead::HeapMgr::instance()->getCurrentHeap());
    // hk::dbg::Log("nn::socket::Initialize socBuffer %x Level %d Summary %d ModuleType %d Description %d", nullptr, result.GetLevel(), result.GetSummary(), result.GetModuleType(), result.GetDescription());
    // gServerThread = new ServerThread;
}

HK_BL_HOOK_FUNC(ProductSequenceStateInitHook, 0x00163564, productSequenceStateInitHook);
