#include "ray.h"

#include "vec.h"
#include "norm.h"

namespace graphics::math{

template <typename RealType>
ray_t<RealType>::ray_t(const vec3_t<RealType> &origin, const norm3_t<RealType> &direction) noexcept:
    origin{ origin },
    direction{ direction }
{}
template ray_t<float>::ray_t(const vec3_t<float> &origin, const norm3_t<float> &direction) noexcept;
template ray_t<double>::ray_t(const vec3_t<double> &origin, const norm3_t<double> &direction) noexcept;

template <typename RealType>
ray_t<RealType> ray_t<RealType>::fromTwoPoints(const vec3_t<RealType> &from, const vec3_t<RealType> &to) noexcept
{
    return ray_t(from, to - from);
}
template ray_t<float> ray_t<float>::fromTwoPoints(const vec3_t<float> &from, const vec3_t<float> &to) noexcept;
template ray_t<double> ray_t<double>::fromTwoPoints(const vec3_t<double> &from, const vec3_t<double> &to) noexcept;

} // namespace graphics::math
