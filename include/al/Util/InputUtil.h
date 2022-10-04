#pragma once

#include "sead/math/seadVector.h"
#include "types.h"

namespace al {

bool isPadTrigger(int port, unsigned int mask);
bool isPadHold(int port, unsigned int mask);
bool isPadRelease(int port, unsigned int mask);

#define _T_BUTTON(BUTTON)                    \
    bool isPadTrigger##BUTTON(int port = 0); \
    bool isPadHold##BUTTON(int port = 0);    \
    bool isPadRelease##BUTTON(int port = 0);

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

#undef _T_BUTTON

const sead::Vector2f& getLeftStick(int port = 0);

} // namespace al