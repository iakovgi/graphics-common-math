#include "primitive.h"

#include "vec.h"
#include "norm.h"
#include "ray.h"

#include <cmath>

namespace graphics::math{

constexpr double PRIMITIVE_EPSILON = 32 * std::numeric_limits<float>::epsilon();

// SpherePrimitive -----------------------------------------------------------------------------------------------------

template <typename RealType>
std::optional<typename Primitive<RealType>::intersection_t>
        SpherePrimitive<RealType>::intersect(const ray_t<RealType> &ray) const noexcept
{
    const auto radiusSquared = radius * radius;

    const auto op = position - ray.origin;
    const auto b = op.dot(ray.direction);
    const auto opSquared = op.lenSquared();
    const auto dSquared = std::pow(b, 2) - opSquared + radiusSquared;
    if(dSquared < 0) {
        return {};
    }

    const auto d = std::sqrt(dSquared);
    const auto inside = opSquared < radiusSquared;
    const auto t = inside ? b + d : b - d;
    if(t < PRIMITIVE_EPSILON) {
        return {};
    }

    auto result = intersection_t{};

    result.distance = t;
    result.position = ray.origin + ray.direction * result.distance;
    result.normal = (result.position - position) * (inside ? -1.0 : 1.0);

    return result;
}
template std::optional<Primitive<float>::intersection_t>
        SpherePrimitive<float>::intersect(const ray_t<float> &ray) const noexcept;
template std::optional<Primitive<double>::intersection_t>
        SpherePrimitive<double>::intersect(const ray_t<double> &ray) const noexcept;

template <typename RealType>
SpherePrimitive<RealType>::SpherePrimitive(const RealType radius, const vec3_t<RealType> &position) noexcept:
    radius{ radius },
    position{ position }
{}
template SpherePrimitive<float>::SpherePrimitive(const float radius, const vec3_t<float> &position) noexcept;
template SpherePrimitive<double>::SpherePrimitive(const double radius, const vec3_t<double> &position) noexcept;

// ---------------------------------------------------------------------------------------------------------------------

// TrianglePrimitive ---------------------------------------------------------------------------------------------------

template <typename RealType>
std::optional<typename Primitive<RealType>::intersection_t>
    TrianglePrimitive<RealType>::intersect(const ray_t<RealType> &ray) const noexcept
{
    auto result = intersection_t{};

    result.normal = ray.direction.dot(normal) < 0.0 ? normal : -normal;
    const auto dn = ray.direction.dot(result.normal);
    if(std::abs(dn) <= PRIMITIVE_EPSILON) {
        return {};
    }

    result.distance = (v0 - ray.origin).dot(result.normal) / dn;
    if(result.distance <= PRIMITIVE_EPSILON) {
        return {};
    }

    result.position = ray.origin + ray.direction * result.distance;

    const auto p1 = result.position - v0;
    const auto v12 = v2 - v1;
    const auto posDir = normal;
    const auto m = (v1 - v0).cross(p1).dot(posDir);
    const auto n = p1.cross(v2 - v0).dot(posDir);
    const auto k = v12.cross(result.position - v1).dot(posDir);
    if(m <= 0.0 || n <= 0.0 || k <= 0.0) {
        return {};
    }
    return result;
}
template std::optional<Primitive<float>::intersection_t>
        TrianglePrimitive<float>::intersect(const ray_t<float> &ray) const noexcept;
template std::optional<Primitive<double>::intersection_t>
        TrianglePrimitive<double>::intersect(const ray_t<double> &ray) const noexcept;

template <typename RealType>
TrianglePrimitive<RealType>::TrianglePrimitive(const vec3_t<RealType> &v0,
                                               const vec3_t<RealType> &v1,
                                               const vec3_t<RealType> &v2) noexcept:
   v0{ v0 },
   v1{ v1 },
   v2{ v2 },
   normal{ (v1 - v0).cross(v2 - v0) }
{}
template TrianglePrimitive<float>::TrianglePrimitive(const vec3_t<float> &v0,
                                                     const vec3_t<float> &v1,
                                                     const vec3_t<float> &v2) noexcept;
template TrianglePrimitive<double>::TrianglePrimitive(const vec3_t<double> &v0,
                                                      const vec3_t<double> &v1,
                                                      const vec3_t<double> &v2) noexcept;

// ---------------------------------------------------------------------------------------------------------------------

} // namespace graphics::math
