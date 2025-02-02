#include "al/Controller/ControllerUtil.h"
#include "font.h"
#include "hk/Types.h"
#include "hk/debug/Log.h"
#include "hk/hook/AsmPatch.h"
#include "hk/hook/BranchHook.h"
#include "mg/Debug/Exit.h"
#include "mg/Debug/Framework.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/applet/applet_Api.h"
#include "nn/err/CTR/err_Api.h"
#include "nn/os/os_CTR.h"
#include "nn/os/os_Types.h"
#include "nn/srv/detail/srv_Service.h"
#include "nn/srv/srv_Api.h"
#include "nn/svc/svc_Api.h"
#include "sead/controller/seadControllerMgr.h"
#include "sead/heap/seadFrameHeap.h"
#include "sead/math/seadMathCalcCommon.h"
#include <string.h>

#define PA_PTR(addr) (void*)((u32)(addr) | 1 << 31)
#define REG32(addr) (*(volatile u32*)(PA_PTR(addr)))
#define GPU_FB_TOP_LEFT_ADDR_1 REG32(0x10400468)
#define GPU_FB_TOP_LEFT_ADDR_2 REG32(0x1040046C)
#define GPU_FB_TOP_FMT REG32(0x10400470)
#define GPU_FB_TOP_SEL REG32(0x10400478)
#define GPU_FB_TOP_COL_LUT_INDEX REG32(0x10400480)
#define GPU_FB_TOP_COL_LUT_ELEM REG32(0x10400484)
#define GPU_FB_TOP_STRIDE REG32(0x10400490)
#define GPU_FB_TOP_RIGHT_ADDR_1 REG32(0x10400494)
#define GPU_FB_TOP_RIGHT_ADDR_2 REG32(0x10400498)

#define GPU_FB_BOTTOM_ADDR_1 REG32(0x10400568)
#define GPU_FB_BOTTOM_ADDR_2 REG32(0x1040056C)
#define GPU_FB_BOTTOM_FMT REG32(0x10400570)
#define GPU_FB_BOTTOM_SEL REG32(0x10400578)
#define GPU_FB_BOTTOM_COL_LUT_INDEX REG32(0x10400580)
#define GPU_FB_BOTTOM_COL_LUT_ELEM REG32(0x10400584)
#define GPU_FB_BOTTOM_STRIDE REG32(0x10400590)

#define GPU_PSC0_CNT REG32(0x1040001C)
#define GPU_PSC1_CNT REG32(0x1040002C)

#define GPU_TRANSFER_CNT REG32(0x10400C18)
#define GPU_CMDLIST_CNT REG32(0x104018F0)

#define LCD_TOP_BRIGHTNESS REG32(0x10202240)
#define LCD_TOP_FILLCOLOR REG32(0x10202204)
#define LCD_BOT_BRIGHTNESS REG32(0x10202A40)
#define LCD_BOT_FILLCOLOR REG32(0x10202A04)

#define LCD_FILLCOLOR_ENABLE (1u << 24)

#define FB_BOTTOM_VRAM_ADDR ((void*)0x1F48F000) // cached
#define FB_BOTTOM_VRAM_PA 0x1848F000
#define FB_BOTTOM_SIZE (320 * 240 * 2)
#define FB_SCREENSHOT_SIZE (52 + 400 * 240 * 3)

constexpr uintptr_t uncachedAddr(uintptr_t addr)
{
    return addr | uintptr_t(1 << 31);
}

class BottomScreen {
public:
    constexpr static int sWidth = 320;
    constexpr static int sHeight = 240;
    constexpr static int sXSpacing = 6;
    constexpr static int sYSpacing = 11;

    BottomScreen()
    {
        init();
    }

    void init()
    {
        while ((GPU_PSC0_CNT | GPU_PSC1_CNT | GPU_TRANSFER_CNT | GPU_CMDLIST_CNT) & 1)
            ;

        u32 format = GPU_FB_BOTTOM_FMT;
        format = (format & ~7) | 2 /* RGB565 */;
        format |= 3 << 8; // set VRAM bits

        GPU_FB_BOTTOM_ADDR_1 = FB_BOTTOM_VRAM_PA;
        GPU_FB_BOTTOM_ADDR_2 = FB_BOTTOM_VRAM_PA;
        GPU_FB_BOTTOM_FMT = format;
        GPU_FB_BOTTOM_STRIDE = sHeight * 2;
        LCD_BOT_FILLCOLOR = 0;
    }

    void flush()
    {
        nn::svc::FlushProcessDataCache(CUR_PROCESS_HANDLE, u32(FB_BOTTOM_VRAM_ADDR), FB_BOTTOM_SIZE);
    }

    void clear()
    {
        memset(FB_BOTTOM_VRAM_ADDR, 0x0, FB_BOTTOM_SIZE);
    }

    void drawCharacter(u32 posX, u32 posY, u32 color, char character)
    {
        u16* const fb = (u16*)FB_BOTTOM_VRAM_ADDR;

        s32 y;
        for (y = 0; y < 10; y++) {
            char charPos = font[character * 10 + y];

            s32 x;
            for (x = 6; x >= 1; x--) {
                u32 screenPos = (posX * sHeight * 2 + (sHeight - y - posY - 1) * 2) + (5 - x) * 2 * sHeight;
                u32 pixelColor = ((charPos >> x) & 1) ? color : 0x0;
                fb[screenPos / 2] = pixelColor;
            }
        }
    }

    template <bool Wrap = true>
    u32 drawString(u32 posX, u32 posY, u32 color, const char* string)
    {
        for (u32 i = 0, line_i = 0; i < strlen(string); i++)
            switch (string[i]) {
            case '\n':
                posY += sYSpacing;
                line_i = 0;
                break;

            case '\t':
                line_i += 2;
                break;

            default:
                // Make sure we never get out of the screen
                if (line_i >= ((sWidth)-posX) / sXSpacing) {
                    if (!Wrap)
                        return posY;
                    posY += sYSpacing;
                    line_i = 1; // Little offset so we know the same string continues
                    if (string[i] == ' ')
                        break; // Spaces at the start look weird
                }

                s32 charPosX = posX + line_i * sXSpacing;
                if (charPosX >= 0 && charPosX < BottomScreen::sWidth - BottomScreen::sXSpacing && posY >= 0 && posY < BottomScreen::sHeight - BottomScreen::sYSpacing)
                    drawCharacter(charPosX, posY, color, string[i]);

                line_i++;
                break;
            }

        return posY;
    }

    template <bool Wrap = false, typename... Args>
    u32 drawString(u32 posX, u32 posY, u32 color, const char* fmt, Args... args)
    {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        char data[size + 1];
        snprintf(data, size + 1, fmt, args...);
        return drawString(posX, posY, color, data);
    }
};

static ERRF_ExceptionData sExceptionThreadData;
static __attribute__((aligned(0x1000))) u8 sExceptionThreadStack[0x1000];
static bool sExceptionOccurred = false;
static bool sNeedsRefresh = true;
static int sCurPage = 0;
static int sCurStackPage = 0;
static int sCurHeapTreePage = 0;
static bool sQuit = false;

static char sTitleBuffer[64];
static const char* getTitle(CpuRegisters* regs)
{
    switch (sCurPage) {
    case 0:
        strncpy(sTitleBuffer, "Overview", sizeof(sTitleBuffer));
        break;
    case 1:
        snprintf(sTitleBuffer, sizeof(sTitleBuffer), "Stack %.08X-%.08X", regs->sp + sCurStackPage * 19 * 8, regs->sp + (sCurStackPage + 1) * 19 * 8);
        break;
    case 2:
        strncpy(sTitleBuffer, "HeapTree", sizeof(sTitleBuffer));
        break;
    }

    return sTitleBuffer;
}

static char sPermBuffer[8];
static const char* getPermStr(u32 addr)
{
    nn::os::MemInfo info;
    nn::os::PageInfo page;

    nn::svc::QueryMemory(&info, &page, addr);

    if (info.perm == 0) {
        strncpy(sPermBuffer, "---", sizeof(sPermBuffer));
        return sPermBuffer;
    }

    int i = 0;
    if (info.perm & nn::os::MemoryPermission_R)
        sPermBuffer[i++] = 'R';
    if (info.perm & nn::os::MemoryPermission_W)
        sPermBuffer[i++] = 'W';
    if (info.perm & nn::os::MemoryPermission_X)
        sPermBuffer[i++] = 'X';
    sPermBuffer[i++] = '\0';

    return sPermBuffer;
}

constexpr u16 rgb565(u8 r, u8 g, u8 b)
{
    u16 rgb565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
    return rgb565;
}

extern "C" uintptr_t __addrCode;
extern "C" uintptr_t __addrCustomCode;

static u32 getAddrColor(u32 addr)
{
    if (addr >= u32(&__addrCode) && addr <= u32(&__addrCustomCode))
        return rgb565(164, 52, 235);
    else if (addr >= u32(&__addrCustomCode) && addr <= 0x00532000) // too lazy to put proper end address
        return rgb565(235, 52, 183);

    nn::os::MemInfo info;
    nn::os::PageInfo page;

    nn::svc::QueryMemory(&info, &page, addr);

    if (!(info.perm & nn::os::MemoryPermission_R))
        return rgb565(255, 0, 0);

    return rgb565(255, 255, 255);
}

static const char* getExceptionType(ERRF_ExceptionType type)
{
    switch (type) {
    case ERRF_EXCEPTION_PREFETCH_ABORT:
        return "Prefetch Abort";
    case ERRF_EXCEPTION_DATA_ABORT:
        return "Data Abort";
    case ERRF_EXCEPTION_UNDEFINED:
        return "Undefined Instruction";
    case ERRF_EXCEPTION_VFP:
        return "VFP Exception";
    default:
        return "Unknown";
    }
}

static constexpr char sErrorFmt[] = R"(Type: %s
An exception has occurred.
Press START to exit.)";
static constexpr char sErrorFmtMgAbort[] = R"(mg::abortWithMessage called.
Press START to exit.
Abort Message:
%s)";

static void drawOverview(BottomScreen& screen, ERRF_ExceptionInfo* excep, CpuRegisters* regs)
{
    for (int i = 0; i < 13; i++) {
        screen.drawString(20, 20 + BottomScreen::sYSpacing * i, getAddrColor(regs->r[i]), "R[%02d]=%.8X [%s]", i, regs->r[i], getPermStr(regs->r[i]));
    }
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 13, getAddrColor(regs->sp), "SP   =%.8X [%s]", regs->sp, getPermStr(regs->sp));
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 14, getAddrColor(regs->lr), "LR   =%.8X [%s]", regs->lr, getPermStr(regs->lr));
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 15, getAddrColor(regs->pc), "PC   =%.8X [%s]", regs->pc, getPermStr(regs->pc));
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 16, getAddrColor(regs->cpsr), "CPSR =%.8X [%s]", regs->cpsr, getPermStr(regs->cpsr));
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 17, getAddrColor(excep->far), "FAR  :%.8X [%s]", excep->far, getPermStr(excep->far));
    screen.drawString(20, 20 + BottomScreen::sYSpacing * 18, getAddrColor(excep->fsr), "FSR  :%.8X [%s]", excep->fsr, getPermStr(excep->fsr));

    if (regs->r[1] == 0x69696969) {
        const char* abortMsg = (const char*)regs->r[0];

        screen.drawString(20 + 21 * BottomScreen::sXSpacing, 20 + BottomScreen::sYSpacing, 0xffff, sErrorFmtMgAbort, abortMsg);
    } else
        screen.drawString(20 + 21 * BottomScreen::sXSpacing, 20 + BottomScreen::sYSpacing, 0xffff, sErrorFmt, getExceptionType(excep->type));
}

static void drawStack(BottomScreen& screen, ERRF_ExceptionInfo* excep, CpuRegisters* regs)
{
    uintptr_t curPageStart = regs->sp + sCurStackPage * 19 * 8;
    for (int i = 0; i < 19; i++) {
        uintptr_t rowAddr = curPageStart + i * 8;
        int yOffs = 20 + BottomScreen::sYSpacing * i;
        screen.drawString(20, yOffs, 0xffff, "%.08X:", curPageStart + i * 8);

        for (int x = 0; x < 8; x++) {
            uintptr_t addr = rowAddr + x;
            nn::os::MemInfo info;
            nn::os::PageInfo page;

            u16 color = 0xffff;
            uintptr_t addrAlign4 = addr & ~(4 - 1);
            nn::svc::QueryMemory(&info, &page, addrAlign4);

            if (info.perm & nn::os::MemoryPermission_R) {
                u32 readAddr = *(u32*)addrAlign4;
                color = getAddrColor(readAddr);
            }

            int xOffs = 20 + BottomScreen::sXSpacing * 10 + x * ((BottomScreen::sXSpacing + 2) * 2);
            nn::svc::QueryMemory(&info, &page, addr);
            if (info.perm & nn::os::MemoryPermission_R) {
                u32 byte = *(u8*)addr;
                screen.drawString(xOffs, 20 + BottomScreen::sYSpacing * i, color, "%02X", byte);
            } else
                screen.drawString(xOffs, 20 + BottomScreen::sYSpacing * i, color, "??");

            xOffs = 20 + BottomScreen::sXSpacing * 12 + 7 * ((BottomScreen::sXSpacing + 3) * 2) + x * (BottomScreen::sXSpacing + 2);
            if (info.perm & nn::os::MemoryPermission_R) {
                char character = *(char*)addr;
                screen.drawCharacter(xOffs, 20 + BottomScreen::sYSpacing * i, color, character >= ' ' && character <= '~' ? character : '.');
            } else
                screen.drawCharacter(xOffs, 20 + BottomScreen::sYSpacing * i, color, '.');
        }
    }
}

extern "C" u32 _ZTVN4sead9FrameHeapE;
extern "C" u32 _ZTVN4sead7ExpHeapE;

static void drawHeapTreeRecursive(sead::Heap& heap, int& y, int indent, BottomScreen& screen)
{
    const char* sizeUnit;
    float displaySize;
    float displayFree;
    size_t size = heap.mSize;
    size_t free = -1;

    char heapType[64];
    if (*(u32*)&heap == u32(&_ZTVN4sead7ExpHeapE) + 8)
        strncpy(heapType, "sead::ExpHeap", sizeof(heapType));
    else if (*(u32*)&heap == u32(&_ZTVN4sead9FrameHeapE) + 8) {
        sead::FrameHeap* frameHeap = static_cast<sead::FrameHeap*>(&heap);
        strncpy(heapType, "sead::FrameHeap", sizeof(heapType));
        free = (uintptr_t(frameHeap->mState.mTailPtr) - uintptr_t(frameHeap->mStart));
    } else
        snprintf(heapType, sizeof(heapType), "vft@%.08X", *(u32*)&heap);

    if (size <= 1024) {
        sizeUnit = "B";
        displaySize = size;
        displayFree = free;
    } else if (size <= 1024 * 1024) {
        sizeUnit = "KB";
        displaySize = size / 1024.f;
        displayFree = free / 1024.f;
    } else {
        sizeUnit = "MB";
        displaySize = size / 1024.f / 1024.f;
        displayFree = free / 1024.f / 1024.f;
    }

    screen.drawString<false>(indent, y, 0xffff, "- %s", heap.getName().cstr());
    y += BottomScreen::sYSpacing;
    screen.drawString<false>(indent, y, 0xffff, " Type: %s", heap.getName().cstr(), heapType);
    y += BottomScreen::sYSpacing;
    screen.drawString<false>(indent, y, 0xffff, " Size: %.2f%s", displaySize, sizeUnit);
    y += BottomScreen::sYSpacing;
    if (free == -1)
        screen.drawString<false>(indent, y, 0xffff, " Free: ?%s", sizeUnit);
    else
        screen.drawString<false>(indent, y, 0xffff, " Free: %.2f%s", displayFree, sizeUnit);
    y += BottomScreen::sYSpacing;

    for (sead::Heap& child : heap.mChildren) {
        drawHeapTreeRecursive(child, y, indent + BottomScreen::sXSpacing * 3, screen);
    }
}

static void drawHeapTree(BottomScreen& screen)
{
    int y = 20 - BottomScreen::sHeight * sCurHeapTreePage;
    drawHeapTreeRecursive(*sead::HeapMgr::sRootHeaps.at(0), y, 20, screen);
}

static void update()
{
    if (al::isPadTriggerRight()) {
        sNeedsRefresh = true;
        sCurPage++;
    } else if (al::isPadTriggerLeft()) {
        sNeedsRefresh = true;
        sCurPage--;
    }

    if (sCurPage == 1) {
        if (al::isPadTriggerDown()) {
            sNeedsRefresh = true;
            sCurStackPage++;
        } else if (al::isPadTriggerUp()) {
            sNeedsRefresh = true;
            sCurStackPage--;
        }

        if (sCurStackPage < 0)
            sCurStackPage = 0;
    } else if (sCurPage == 2) {
        if (al::isPadTriggerDown()) {
            sNeedsRefresh = true;
            sCurHeapTreePage++;
        } else if (al::isPadTriggerUp()) {
            sNeedsRefresh = true;
            sCurHeapTreePage--;
        }

        if (sCurHeapTreePage < 0)
            sCurHeapTreePage = 0;
    }

    if (al::isPadTriggerStart()) {
        sQuit = true;
    }

    sCurPage = sead::Mathi::clamp(sCurPage, 0, 2);
}

static void drawException(BottomScreen& screen, ERRF_ExceptionInfo* excep, CpuRegisters* regs)
{
    if (!(sCurPage == 2 && sCurHeapTreePage > 0))
        screen.drawString(10, 10, 0xffff, "~~~ HakkunException ~~~ [%s]", getTitle(regs));

    switch (sCurPage) {
    case 0:
        drawOverview(screen, excep, regs);
        break;
    case 1:
        drawStack(screen, excep, regs);
        break;
    case 2:
        drawHeapTree(screen);
        break;
    default:
        __builtin_trap();
    }
}

static void exceptionHandler(ERRF_ExceptionInfo* excep, CpuRegisters* regs)
{
    if (sExceptionOccurred)
        return; // dont want to nest
    sExceptionOccurred = true;

    mg::suspendFramework(); // suspend the main thread to prevent framebuffer battle

    BottomScreen screen;
    for (int i = 0; i < 100; i++) { // ????????
        screen.init();
        screen.clear();
        screen.flush();
    }

    while (sQuit == false) {
        sead::ControllerMgr::instance()->calc();

        update();
        if (sNeedsRefresh) {
            screen.clear();
            drawException(screen, excep, regs);
            screen.flush();
            sNeedsRefresh = false;
        }
        nn::svc::SleepThread(16_ms);
    }

    screen.clear();
    screen.drawString(0, 0, 0xffff, "Bye bye!!! :3");

    mg::exitProcess();
}

static void setupExceptionHandler()
{
    nn::os::CTR::SetupThreadCppExceptionEnvironment();

    setThreadExceptionHandler(exceptionHandler, sExceptionThreadStack, &sExceptionThreadData);
}

HK_BL_HOOK_FUNC(SetupExceptionHandlerMainThread, 0x001051f8, setupExceptionHandler)
HK_BL_HOOK_FUNC(SetupExceptionHandlerNnosThread, 0x001073c4, setupExceptionHandler)
