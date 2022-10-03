#include "mg/Camera/CameraPoserCustom.h"

extern sead::Vector3f gPlayerTrans;

namespace mg {

void CameraPoserCustom::load(const al::ByamlIter* ticket)
{
    CameraPoser::load(ticket);
}

void CameraPoserCustom::update()
{
    mCameraTarget = gPlayerTrans;
    mCameraAt = gPlayerTrans + sead::Vector3f { 0, 1500, -1500 };
}

} // namespace mg