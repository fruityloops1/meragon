#include "al/Factory/CameraPoserFactory.h"
#include "Game/Factory/CameraPoserFactory.h"
#include "al/Util/StringUtil.h"
#include "mg/Camera/CameraPoserCustom.h"
#include "mg/Factory/CameraPoserFactory.h"

namespace mg {

constexpr al::NameToCreatorCameraPoser sCameraPoserFactoryCustomEntries[] {
    { "Custom", mg::createCameraPoserFunction<CameraPoserCustom> }
};

al::CreateCameraPoserFunctionT getCameraPoserCreatorFromFactory(const char* className)
{
    for (auto& entry : sCameraPoserFactoryCustomEntries)
        if (al::isEqualString(className, entry.name))
            return entry.create;
    for (auto& entry : ::sCameraPoserFactoryEntries)
        if (al::isEqualString(className, entry.name))
            return entry.create;
    return nullptr;
}

} // namespace mg