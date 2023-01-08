#include "al/Factory/CameraFactory.h"
#include "al/Util/StringUtil.h"
#include "hk/hook/BranchHook.h"
#include "mg/Camera/CameraCustom.h"
#include "mg/Factory/CameraFactory.h"

namespace mg {

constexpr al::NameToCameraCreator sCameraPoserFactoryCustomEntries[] {
    { "Custom", mg::createCameraPoserFunction<CameraCustom> }
};

al::CreateCameraFuncPtr getCameraPoserCreatorFromFactory(const char* className)
{
    for (auto& entry : sCameraPoserFactoryCustomEntries)
        if (al::isEqualString(className, entry.name))
            return entry.creator;
    for (auto& entry : ::sCameraPoserFactoryEntries)
        if (al::isEqualString(className, entry.name))
            return entry.creator;
    return nullptr;
}

HK_B_HOOK(GetCameraCreatorFromFactoryHook, 0x002659a4, getCameraPoserCreatorFromFactory);

} // namespace mg