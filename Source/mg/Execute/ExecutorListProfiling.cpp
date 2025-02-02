#include "al/Execute/ExecuteDirector.h"
#include "al/Execute/ExecuteTableHolderDraw.h"
#include "al/Execute/ExecuteTableHolderUpdate.h"
#include "al/Util/StringUtil.h"
#include "hk/hook/BranchHook.h"
#include "mg/Abort.h"
#include "mg/Debug/Clock.h"
#include "mg/Debug/Framework.h"
#include "mg/DebugMenu.h"

namespace mg {

static void executeUpdateTable(al::ExecuteTableHolderUpdate* table)
{
#ifdef MG_ENABLE_DEBUG_MENU
    auto& p = getProfilingData();

    hk::util::Clock<"ExecuteUpdateTable"> tableClock;
    tableClock.start();
#endif

    for (int i = 0; i < table->mNumExecutorLists; i++) {
#ifdef MG_ENABLE_DEBUG_MENU
        if (i >= sizeof(p.executeTableLists) / sizeof(p.executeTableLists[0]))
            mg::abortWithMessage("soooo many executor lists");
#endif

#ifdef MG_ENABLE_DEBUG_MENU
        hk::util::Clock<"ExecuteList"> listClock;
        listClock.start();
#endif

        table->mExecutorLists[i]->executeList();

#ifdef MG_ENABLE_DEBUG_MENU
        if (p.curExecuteTable == 0)
            p.executeTableLists[i] = listClock.count();
#endif
    }

#ifdef MG_ENABLE_DEBUG_MENU
    p.executeUpdateTable = tableClock.count();
#endif
}

static void executeDrawList(al::ExecuteDirector* director, const char* drawTableName, const char* listName)
{
#ifdef MG_ENABLE_DEBUG_MENU
    auto& p = getProfilingData();
#endif
    for (int i = 0; i < director->getNumDrawTables(); i++) {
        al::ExecuteTableHolderDraw* table = director->getDrawTable(i);
        if (al::isEqualString(drawTableName, table->mName)) {
            for (int j = 0; j < table->mNumExecutorLists; j++) {
                al::ExecutorListBase* list = table->mExecutorLists[j];
                if (al::isEqualString(list->getName(), listName)) {
#ifdef MG_ENABLE_DEBUG_MENU
                    hk::util::Clock<"ExecuteList"> clock;
                    clock.start();
#endif

                    list->executeList();

#ifdef MG_ENABLE_DEBUG_MENU
                    if (p.curExecuteTable - 1 == i) {
                        sead::TickSpan elapsed = clock.count();
                        clock.print();
                        p.executeTableLists[j] = elapsed;
                        p.executeDrawTable[i] += elapsed;
                    }
#endif
                }
            }
            return;
        }
    }
}

static void executeDraw(al::ExecuteDirector* director, const char* drawTableName)
{
#ifdef MG_ENABLE_DEBUG_MENU
    auto& p = getProfilingData();
#endif
    for (int i = 0; i < director->getNumDrawTables(); i++) {
        al::ExecuteTableHolderDraw* table = director->getDrawTable(i);
        if ((i == 0 && drawTableName == nullptr) || al::isEqualString(drawTableName, table->mName)) {
            for (int j = 0; j < table->mNumExecutorLists; j++) {
                al::ExecutorListBase* list = table->mExecutorLists[j];
#ifdef MG_ENABLE_DEBUG_MENU
                hk::util::Clock<"ExecuteList"> clock;
                clock.start();
#endif

                list->executeList();

#ifdef MG_ENABLE_DEBUG_MENU
                if (p.curExecuteTable - 1 == i) {
                    sead::TickSpan elapsed = clock.count();
                    p.executeTableLists[j] = elapsed;
                    p.executeDrawTable[i] += elapsed;
                }
#endif
            }
            return;
        }
    }
}

HK_BL_HOOK_FUNC(ExecuteUpdateTable, 0x001dd974, executeUpdateTable)
HK_B_HOOK_FUNC(ExecuteDrawList, 0x002770bc, executeDrawList)
HK_B_HOOK_FUNC(ExecuteDrawLiveActorKit, 0x00276cfc, executeDraw)
HK_B_HOOK_FUNC(ExecuteDrawLayoutActorKit, 0x0027b298, executeDraw)

} // namespace mg
