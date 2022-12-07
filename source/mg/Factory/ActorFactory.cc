#include "Game/Factory/ActorFactory.h"
#include "al/Util/StringUtil.h"
#include "mg/MapObj/Gabon.h"
#include <al/Factory/ActorFactory.h>
#include <al/System/Byaml/ByamlIter.h>
#include <mg/Factory/ActorFactory.h>

namespace mg {

constexpr al::NameToActorCreator sActorFactoryCustomEntries[] {
    { "Gabon", mg::createActorFunction<Gabon> }
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

export al::CreateActorFuncPtr getCreatorHook(al::ActorFactory* thisPtr, const char* objectName)
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

} // namespace mg