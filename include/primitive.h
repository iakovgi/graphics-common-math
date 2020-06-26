#ifndef GRAPHICS_COMMON_MATH_PRIMITIVE_H__
#define GRAPHICS_COMMON_MATH_PRIMITIVE_H__

#include <optional>

namespace graphics::math{

template <typename RealType>
union vec3_t;

template <typename RealType>
union norm3_t;

template <typename RealType>
struct ray_t;

template <typename RealType = double>
class Primitive
{
public:
    struct intersection_t
    {
        RealType distance;
        vec3_t<RealType> position;
        norm3_t<RealType> normal;
    };

    virtual std::optional<intersection_t> intersect(const ray_t<RealType> &ray) const noexcept = 0;
    virtual ~Primitive() noexcept = default;
};

template <typename RealType = double>
class SpherePrimitive final: public Primitive<RealType>
{
public:
    using intersection_t = typename Primitive<RealType>::intersection_t;

public:
    RealType radius;
    vec3_t<RealType> position;

public:
    virtual std::optional<intersection_t> intersect(const ray_t<RealType> &ray) const noexcept override;

    SpherePrimitive(const RealType radius, const vec3_t<RealType> &position) noexcept;
    virtual ~SpherePrimitive() noexcept override = default;

    SpherePrimitive(const SpherePrimitive &that) noexcept = default;
    SpherePrimitive(SpherePrimitive &&that) noexcept = default;

    SpherePrimitive &operator=(const SpherePrimitive &that) noexcept = default;
    SpherePrimitive &operator=(SpherePrimitive &&that) noexcept = default;
};

template <typename RealType = double>
class TrianglePrimitive final: public Primitive<RealType>
{
public:
    using intersection_t = typename Primitive<RealType>::intersection_t;

public:
    vec3_t<RealType> v0;
    vec3_t<RealType> v1;
    vec3_t<RealType> v2;

    norm3_t<RealType> normal;

public:
    virtual std::optional<intersection_t> intersect(const ray_t<RealType> &ray) const noexcept override;

    TrianglePrimitive(const vec3_t<RealType> &v0, const vec3_t<RealType> &v1, const vec3_t<RealType> &v2) noexcept;
    virtual ~TrianglePrimitive() noexcept override = default;

    TrianglePrimitive(const TrianglePrimitive &that) noexcept = default;
    TrianglePrimitive(TrianglePrimitive &&that) noexcept = default;

    TrianglePrimitive &operator=(const TrianglePrimitive &that) noexcept = default;
    TrianglePrimitive &operator=(TrianglePrimitive &&that) noexcept = default;
};

} // namespace graphics::math

#endif // GRAPHICS_COMMON_MATH_PRIMITIVE_H__
