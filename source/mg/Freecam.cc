#include "mg/Freecam.h"
#include "al/Camera/CameraPoser.h"
#include "al/Util/InputUtil.h"
#include "mg/log.h"

namespace mg {

static sead::Vector3f offset;

const sead::Vector3f& getFreecamOffset()
{
    return offset;
}

void updateFreecam()
{
    if (al::isPadHoldL()) {
        mg::log("Camera offset is: %d %d %d", (int)offset.x, (int)offset.y, (int)offset.z);
        if (al::isPadHoldR())
            offset = { 0, 0, 0 };
        if (al::isPadHoldUp())
            offset.y += 100;
        if (al::isPadHoldDown())
            offset.y -= 100;

        offset.x += al::getLeftStick().x * 100;
        offset.z -= al::getLeftStick().y * 100;
    }
}

} // namespace mg