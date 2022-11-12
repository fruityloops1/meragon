#include "Game/Factory/ActorFactory.h"
#include "al/Util/StringUtil.h"
#include "mg/MapObj/Gabon.h"
#include <al/Factory/ActorFactory.h>
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

} // namespace mg