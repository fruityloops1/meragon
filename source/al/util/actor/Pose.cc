#include "al/Util/actor/Pose.h"

namespace al {

void setFront(al::LiveActor* actor, const sead::Vector3f& front)
{
    *getFrontPtr(actor) = front;
}

} // namespace al