#ifndef GRAPHICS_COMMON_MATH_RAY_H__
#define GRAPHICS_COMMON_MATH_RAY_H__

namespace graphics::math{

template <typename RealType>
union vec3_t;

template <typename RealType>
union norm3_t;

template <typename RealType>
struct ray_t
{
    vec3_t<RealType> origin;
    norm3_t<RealType> direction;

    ray_t(const vec3_t<RealType>& origin, const norm3_t<RealType>& direction) noexcept;
    static ray_t fromTwoPoints(const vec3_t<RealType> &from, const vec3_t<RealType> &to) noexcept;
};

} // namespace graphics::math

#endif // GRAPHICS_COMMON_MATH_RAY_H__
