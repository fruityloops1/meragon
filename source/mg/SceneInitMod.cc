
#include "al/Scene/Scene.h"
#include "al/Util/LiveActorUtil.h"
#include "al/Util/StringUtil.h"
#include "mg/Factory/ActorFactory.h"

static al::CreateActorFunctionT getCreatorFromTable(al::ByamlIter* table, const char* pObjectName)
{
    for (int i = 0; i < table->getSize(); i++) {
        al::ByamlIter entry;
        table->tryGetIterByIndex(&entry, i);
        const char* objectName = nullptr;
        entry.tryGetStringByKey(&objectName, "ObjectName");
        if (objectName && al::isEqualString(objectName, pObjectName)) {
            const char* className = nullptr;
            entry.tryGetStringByKey(&className, "ClassName");
            if (className)
                return mg::getActorCreatorFromFactory(className);
        }
    }
    return nullptr;
}

// replaces Scene::initPlacement
export void sceneInitPlacementHook(al::Scene* scene, al::Resource* stageFile, const al::ActorInitInfo& baseInfo, const char* infoIterName)
{
    if (stageFile) {
        al::ByamlIter stageData(static_cast<u8*>(stageFile->getByml("StageData")));
        al::ByamlIter allInfos;
        if (stageData.tryGetIterByKey(&allInfos, "AllInfos")) {
            al::ByamlIter infoIter;
            if (allInfos.tryGetIterByKey(&infoIter, infoIterName) && scene->mCCNTHolder)
                for (int i = 0; i < infoIter.getSize(); i++) {
                    al::ByamlIter placement;
                    infoIter.tryGetIterByIndex(&placement, i);
                    const char* objectName = nullptr;
                    const char* className = nullptr;
                    placement.tryGetStringByKey(&objectName, "name");
                    placement.tryGetStringByKey(&className, "ClassName");
                    al::CreateActorFunctionT create = className != nullptr ? mg::getActorCreatorFromFactory(className) : getCreatorFromTable(scene->mCCNTHolder->mTable, objectName);
                    if (create) {
                        al::ActorInitInfo info;
                        al::initActorInitInfo(&info, &placement, baseInfo);
                        al::LiveActor* newActor = create(objectName);
                        al::initCreateActorWithPlacementInfo(newActor, info);
                    }
                }
        }
    }
}