#include "Game/Factory/ActorFactory.h"
#include "al/Factory/ActorFactory.h"
#include "al/System/Byaml/ByamlIter.h"
#include "al/Util/StringUtil.h"
#include "hk/hook/BranchHook.h"
#include "mg/Factory/ActorFactory.h"
#include "mg/MapObj/Gabon.h"

namespace mg {

constexpr al::NameToActorCreator sActorFactoryCustomEntries[] {
    { "Kuribo", mg::createActorFunction<Gabon> }
};

al::CreateActorFuncPtr getActorCreatorFromFactory(const char* className)
{
    for (auto& entry : sActorFactoryCustomEntries)
        if (al::isEqualString(className, entry.name))
            return entry.creator;
    for (auto& entry : ::sActorFactoryEntries)
        if (al::isEqualString(className, entry.name))
            return entry.creator;
    return nullptr;
}

al::CreateActorFuncPtr getCreatorHook(al::ActorFactory* thisPtr, const char* objectName)
{
    for (int i = 0; i < thisPtr->mConvertNameData->getSize(); i++) {
        al::ByamlIter entry;
        thisPtr->mConvertNameData->tryGetIterByIndex(&entry, i);
        const char* entryObjectName = nullptr;
        entry.tryGetStringByKey(&entryObjectName, "ObjectName");
        if (objectName && al::isEqualString(objectName, entryObjectName)) {
            const char* className = nullptr;
            entry.tryGetStringByKey(&className, "ClassName");
            if (className)
                return getActorCreatorFromFactory(className);
        }
    }
    return nullptr;
}

HK_B_HOOK_FUNC(GetCreatorHook, &al::ActorFactory::getCreator, getCreatorHook);

} // namespace mg