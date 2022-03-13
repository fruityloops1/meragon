#include "mg/actors/testactor.h"
#include "al/util/actor.h"
#include "mg/factory.h"

void mg::TestActor::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "Kuribo", nullptr); // broken
    makeActorAlive();
}