#include "mg/Freecam.h"
#include "al/Camera/Camera.h"
#include "al/Controller/ControllerUtil.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"
#include "mg/DebugMenu.h"

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

#ifdef MG_ENABLE_DEBUG_MENU
void freecamApplyHook(al::Camera* camera)
{
    camera->calc();

    if (!DebugMenu::instance().isFreecamEnabled())
        return;
    camera->mTarget += mg::getFreecamOffset();
    camera->mPos += mg::getFreecamOffset();
}

HK_BL_HOOK_FUNC(FreecamApplyHook, 0x002776f8, freecamApplyHook);

static const sead::Vector2f neutral { 0, 0 };
const sead::Vector2f& getLeftStickHook(int port)
{
    // ignore left stick input if L is pressed (freecam is enabled)
    if (al::isPadHoldL() && DebugMenu::instance().isFreecamEnabled())
        return neutral;
    return al::getLeftStick();
}

HK_B_HOOK_FUNC(GetLeftStickHook, 0x0026db4c, getLeftStickHook);
#endif

} // namespace mg