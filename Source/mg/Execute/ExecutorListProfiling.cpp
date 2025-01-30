#include "al/Execute/ExecuteTableHolderUpdate.h"
#include "hk/hook/BranchHook.h"
#include "mg/Abort.h"
#include "mg/Debug/Clock.h"
#include "mg/Debug/Framework.h"

namespace mg {

static void executeUpdateTable(al::ExecuteTableHolderUpdate* table)
{
    auto& p = getProfilingData();
    for (int i = 0; i < table->mNumExecutorLists; i++) {
        if (i >= sizeof(p.executeTableUpdateLists) / sizeof(p.executeTableUpdateLists[0]))
            mg::abortWithMessage("soooo many executor lists");

        hk::util::Clock<"ExecuteList"> clock;
        clock.start();

        table->mExecutorLists[i]->executeList();

        p.executeTableUpdateLists[i] = clock.count();
    }
}

HK_B_HOOK_FUNC(ExecuteUpdateTable, 0x0033615c, executeUpdateTable)

} // namespace mg
