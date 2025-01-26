#pragma once

#include "nn/math/math_MTX34.h"
#include "nn/math/math_MTX44.h"
#include "nn/math/math_VEC3.h"
#include "sead/math/seadMathBase.h"

namespace sead {
template <typename T>
struct Policies {
    using Vec2Base = BaseVec2<T>;
    using Vec3Base = BaseVec3<T>;
    using Vec4Base = BaseVec4<T>;
    using QuatBase = BaseQuat<T>;
    using Mtx22Base = BaseMtx22<T>;
    using Mtx33Base = BaseMtx33<T>;
    using Mtx34Base = BaseMtx34<T>;
    using Mtx44Base = BaseMtx44<T>;
};

template <>
struct Policies<float> {
    using Vec2Base = BaseVec2<float>;
    using Vec3Base = nn::math::VEC3;
    using Vec4Base = BaseVec4<float>;
    using QuatBase = BaseQuat<float>;
    using Mtx22Base = BaseMtx22<float>;
    using Mtx33Base = BaseMtx33<float>;
    using Mtx34Base = nn::math::MTX34;
    using Mtx44Base = nn::math::MTX44;
};

} // namespace sead
