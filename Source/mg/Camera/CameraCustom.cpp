#include "mg/Camera/CameraCustom.h"

const sead::Vector3f customCameraTrans { 0, 0, 0 };

namespace mg {

void CameraCustom::load(const al::ByamlIter* ticket)
{
    Camera::load(ticket);
}

void CameraCustom::calc()
{
    mTarget = customCameraTrans;
    mPos = customCameraTrans + sead::Vector3f { 0, 1500, -1500 };
}

} // namespace mg