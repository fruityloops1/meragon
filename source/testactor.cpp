#include "mg/actors/testactor.h"
#include "al/util/actor.h"
#include "mg/factory.h"

namespace mg {

void TestActor::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "Kuribo", nullptr); // broken
    makeActorAlive();
}

namespace {
    NERVE_IMPL(TestActor, Wait);
}

}