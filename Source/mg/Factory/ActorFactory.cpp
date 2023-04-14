
#include "al/Factory/ActorFactory.h"
#include "al/LiveActor/ActorInitUtil.h"
#include "al/Scene/Scene.h"
#include "al/Scene/SceneFunction.h"
#include "al/System/Byaml/ByamlIter.h"
#include "al/Util/StringUtil.h"
#include "hk/hook/BranchHook.h"
#include "mg/Enemy/Gabon.h"
#include "mg/Factory/ActorFactory.h"
#include "mg/MapObj/BouncyCloud.h"
#include "mg/MapObj/ExampleActor.h"
#include "mg/MapObj/FlipBlock.h"

namespace mg {

// put custom actors here
constexpr al::NameToActorCreator sActorFactoryCustomEntries[] {
    { "Gabon", mg::createActorFunction<Gabon> },
    { "ExampleActor", mg::createActorFunction<ExampleActor> },
    { "FlipBlock", mg::createActorFunction<FlipBlock> },
    { "BouncyCloud", mg::createActorFunction<BouncyCloud> }
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

static al::CreateActorFuncPtr getCreatorFromTable(al::ActorFactory* thisPtr, const char* objectName)
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

// replaces al::initPlacementMap
static void initPlacementMapHook(al::Scene* scene, al::Resource* stageArchive, const al::ActorInitInfo& baseInfo, const char* infoIterName)
{
    al::ByamlIter infoIter;
    if (al::tryGetPlacementInfo(&infoIter, stageArchive, infoIterName) && scene->getActorFactory())
        for (int i = 0; i < infoIter.getSize(); i++) {
            al::ByamlIter placement;
            infoIter.tryGetIterByIndex(&placement, i);
            const char* objectName = nullptr;
            const char* className = nullptr;
            placement.tryGetStringByKey(&objectName, "name");
            placement.tryGetStringByKey(&className, "ClassName");
            al::CreateActorFuncPtr create = className != nullptr ? getActorCreatorFromFactory(className) : getCreatorFromTable(scene->getActorFactory(), objectName);
            if (create) {
                al::ActorInitInfo info;
                info.initNew(&placement, baseInfo);
                al::LiveActor* newActor = create(objectName);
                al::initCreateActorWithPlacementInfo(newActor, info);
            }
        }
}

HK_B_HOOK_FUNC(GetCreatorHook, al::initPlacementMap, initPlacementMapHook);

} // namespace mg
