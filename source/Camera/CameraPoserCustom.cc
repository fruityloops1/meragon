#include "mg/Camera/CameraPoserCustom.h"

const sead::Vector3f customCameraTrans { 0, 0, 0 };

namespace mg {

void CameraPoserCustom::load(const al::ByamlIter* ticket)
{
    CameraPoser::load(ticket);
}

void CameraPoserCustom::update()
{
    mCameraTarget = customCameraTrans;
    mCameraAt = customCameraTrans + sead::Vector3f { 0, 1500, -1500 };
}

} // namespace mg