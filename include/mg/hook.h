#pragma once

#include "types.h"

namespace mg {

/**
 * @brief Sets len bytes of data at address in executable memory
 *
 * @param address Address to set the data at
 * @param data Data
 * @param len Length of data
 * @return true Data has been set
 * @return false Data has not been set
 */
bool tryHookData(u32 address, const void* data, size_t len);
void hookData(u32 address, const void* data, size_t len);

template <typename AT, typename T>
bool tryHookData(AT address, const T& data)
{
    union {
        AT addrAT;
        u32 addr;
    } conv { address };
    return tryHookData(conv.addr, &data, sizeof(T));
}

template <typename AT, typename T>
void hookData(AT address, const T& data)
{
    union {
        AT addrAT;
        u32 addr;
    } conv { address };
    hookData(conv.addr, &data, sizeof(T));
}

namespace arm32 {

    namespace constants {

        constexpr u32 instNOP = 0xD503201F; // nop
        constexpr u32 instRET = 0xE12FFF1E; // bx lr

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
            BLAL = 0xEB
        };

    } // namespace constants

    /**
     * @brief Generates an ARM32 branch instruction
     *
     * @param to Where to branch
     * @param at Where the instruction will be located
     * @param type Type of branch instruction
     * @return u32 Instruction data
     */
    u32 makeBranch(u32 to, u32 at, constants::BranchType type);

    template <typename AT, typename T>
    u32 makeBranch(AT to, T at, constants::BranchType type)
    {
        union {
            AT addrAT;
            u32 addr;
        } atconv { to };
        union {
            T addrT;
            u32 addr;
        } tconv { at };

        return makeBranch(atconv.addr, tconv.addr, type);
    }

} // namespace arm32
} // namespace mg