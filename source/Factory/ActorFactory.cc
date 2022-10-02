#include "mg/Factory/ActorFactory.h"
#include "Game/Factory/ActorFactory.h"
#include "al/Util/StringUtil.h"

namespace mg {

constexpr al::NameToCreatorActor sActorFactoryCustomEntries[] {
    { "Gabon", mg::createActorFunction<Gabon> }
};

al::CreateActorFunctionT getActorCreatorFromFactory(const char* className)
{
    for (auto& entry : sActorFactoryCustomEntries)
        if (al::isEqualString(className, entry.name))
            return entry.create;
    for (auto& entry : ::sActorFactoryEntries)
        if (al::isEqualString(className, entry.name))
            return entry.create;
    return nullptr;
}

} // namespace mg