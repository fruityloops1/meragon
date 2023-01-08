#include "mg/Freecam.h"
#include "al/Camera/Camera.h"
#include "al/Controller/ControllerUtil.h"
#include "hk/debug/Log.h"

namespace mg {

static sead::Vector3f offset;

const sead::Vector3f& getFreecamOffset()
{
    return offset;
}

void updateFreecam()
{
    if (al::isPadHoldL()) {
        hk::dbg::Log("Camera offset is: %.2f %.2f %.2f", offset.x, offset.y, offset.z);
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