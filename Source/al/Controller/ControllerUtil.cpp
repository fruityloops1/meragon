#include "al/Controller/ControllerUtil.h"
#include <sead/controller/seadControllerMgr.h>

namespace al {

#define _T_BUTTON(BUTTON)                                                   \
    bool isPadTrigger##BUTTON(int port)                                     \
    {                                                                       \
        return isPadTrigger(port, 1 << sead::Controller::cPadIdx_##BUTTON); \
    }                                                                       \
    bool isPadHold##BUTTON(int port)                                        \
    {                                                                       \
        return isPadHold(port, 1 << sead::Controller::cPadIdx_##BUTTON);    \
    }                                                                       \
    bool isPadRelease##BUTTON(int port)                                     \
    {                                                                       \
        return isPadRelease(port, 1 << sead::Controller::cPadIdx_##BUTTON); \
    }

_T_BUTTON(A);
_T_BUTTON(B);
_T_BUTTON(X);
_T_BUTTON(Y);
_T_BUTTON(Home);
_T_BUTTON(Minus);
_T_BUTTON(Start);
_T_BUTTON(Select);
_T_BUTTON(L);
_T_BUTTON(R);
_T_BUTTON(Touch);
_T_BUTTON(Up);
_T_BUTTON(Down);
_T_BUTTON(Left);
_T_BUTTON(Right);
_T_BUTTON(LeftStickUp);
_T_BUTTON(LeftStickDown);
_T_BUTTON(LeftStickLeft);
_T_BUTTON(LeftStickRight);

#undef _T_BUTTON

// same
bool isPadRelease(int port, int mask)
{
    return sead::ControllerMgr::instance()->getController(port)->isRelease(mask);
}

const sead::Vector2f& getLeftStick(int port)
{
    return sead::ControllerMgr::instance()->getController(port)->getLeftStick();
}

} // namespace al
