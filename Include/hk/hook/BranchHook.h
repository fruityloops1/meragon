#pragma once

#include "hk/hook/PatchBase.h"
#include <stddef.h>

namespace hk::hook {

enum class BranchType : u8 {
    B = 0xEA,
    BL = 0xEB,
    BEQ = 0x0A,
    BNE = 0x1A,
    BCS = 0x2A,
    BCC = 0x3A,
    BMI = 0x4A,
    BPL = 0x5A,
    BVS = 0x6A,
    BVC = 0x7A,
    BHI = 0x8A,
    BLS = 0x9A,
    BGE = 0xAA,
    BLT = 0xBA,
    BGT = 0xCA,
    BLE = 0xDA,
    BAL = 0xEA,
    BLX = 0xFA,
    BLEQ = 0x0B,
    BLNE = 0x1B,
    BLCS = 0x2B,
    BLCC = 0x3B,
    BLMI = 0x4B,
    BLPL = 0x5B,
    BLVS = 0x6B,
    BLVC = 0x7B,
    BLHI = 0x8B,
    BLLS = 0x9B,
    BLGE = 0xAB,
    BLLT = 0xBB,
    BLGT = 0xCB,
    BLLE = 0xDB,
    BLAL = 0xEB,
};

template <typename F, typename F2 = void*>
class BranchHook : public PatchBase {
    union {
        struct {
            const uintptr_t mReplaceAddress;
            const uintptr_t mFiller; // member function pointers are a disgrace to society
        };
        const F2 mReplaceFunc;
    };
    const F mFunc;
    const BranchType mBranchType;

public:
    constexpr BranchHook(uintptr_t replaceAddress, const F funcPtr, BranchType type)
        : PatchBase(PatchType::Branch)
        , mReplaceAddress(replaceAddress)
        , mFiller(0)
        , mFunc(funcPtr)
        , mBranchType(type)
    {
    }

    constexpr BranchHook(const F funcPtr, BranchType type, F2 replaceAddress)
        : PatchBase(PatchType::Branch)
        , mReplaceFunc(replaceAddress)
        , mFunc(funcPtr)
        , mBranchType(type)
    {
    }
};

#define HK_BRANCH_HOOK(NAME, ADDR, FUNC, TYPE) \
    ::hk::hook::BranchHook __attribute__((section(".hk.hooks"))) NAME(ADDR, FUNC, TYPE);

#define HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, TYPE) \
    ::hk::hook::BranchHook __attribute__((section(".hk.hooks"))) NAME(FUNC, TYPE, ADDR);

#define HK_B_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::B)
#define HK_BL_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BL)
#define HK_BEQ_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BEQ)
#define HK_BNE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BNE)
#define HK_BCS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BCS)
#define HK_BCC_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BCC)
#define HK_BMI_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BMI)
#define HK_BPL_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BPL)
#define HK_BVS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BVS)
#define HK_BVC_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BVC)
#define HK_BHI_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BHI)
#define HK_BLS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLS)
#define HK_BGE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BGE)
#define HK_BLT_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLT)
#define HK_BGT_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BGT)
#define HK_BLE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLE)
#define HK_BAL_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BAL)
#define HK_BLX_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLX)
#define HK_BLEQ_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLEQ)
#define HK_BLNE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLNE)
#define HK_BLCS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLCS)
#define HK_BLCC_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLCC)
#define HK_BLMI_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLMI)
#define HK_BLPL_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLPL)
#define HK_BLVS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLVS)
#define HK_BLVC_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLVC)
#define HK_BLHI_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLHI)
#define HK_BLLS_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLS)
#define HK_BLGE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLGE)
#define HK_BLLT_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLT)
#define HK_BLGT_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLGT)
#define HK_BLLE_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLE)
#define HK_BLAL_HOOK(NAME, ADDR, FUNC) HK_BRANCH_HOOK(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLAL)

#define HK_B_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::B)
#define HK_BL_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BL)
#define HK_BEQ_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BEQ)
#define HK_BNE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BNE)
#define HK_BCS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BCS)
#define HK_BCC_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BCC)
#define HK_BMI_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BMI)
#define HK_BPL_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BPL)
#define HK_BVS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BVS)
#define HK_BVC_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BVC)
#define HK_BHI_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BHI)
#define HK_BLS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLS)
#define HK_BGE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BGE)
#define HK_BLT_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLT)
#define HK_BGT_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BGT)
#define HK_BLE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLE)
#define HK_BAL_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BAL)
#define HK_BLX_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLX)
#define HK_BLEQ_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLEQ)
#define HK_BLNE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLNE)
#define HK_BLCS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLCS)
#define HK_BLCC_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLCC)
#define HK_BLMI_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLMI)
#define HK_BLPL_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLPL)
#define HK_BLVS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLVS)
#define HK_BLVC_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLVC)
#define HK_BLHI_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLHI)
#define HK_BLLS_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLS)
#define HK_BLGE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLGE)
#define HK_BLLT_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLT)
#define HK_BLGT_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLGT)
#define HK_BLLE_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLLE)
#define HK_BLAL_HOOK_FUNC(NAME, ADDR, FUNC) HK_BRANCH_HOOK_FUNC(NAME, ADDR, FUNC, ::hk::hook::BranchType::BLAL)

} // namespace hk::hook
