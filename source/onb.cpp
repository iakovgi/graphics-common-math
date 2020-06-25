#include "onb.h"

#include "norm.h"
#include "vec.h"

#include <cmath>

namespace graphics::math{

#define $worldAxis(axis, components...)                                         \
    template <typename RealType>                                                \
    norm3_t<RealType> OrthoNormalBasis<RealType>::world##axis() noexcept        \
    {                                                                           \
        return norm3_t<RealType>{ components };                                 \
    }                                                                           \
    template norm3_t<float> OrthoNormalBasis<float>::world##axis() noexcept;    \
    template norm3_t<double> OrthoNormalBasis<double>::world##axis() noexcept;  \

$worldAxis(X, 1.0, 0.0, 0.0)
$worldAxis(Y, 0.0, 1.0, 0.0)
$worldAxis(Z, 0.0, 0.0, 1.0)

#undef $worldAxis

template <typename RealType>
OrthoNormalBasis<RealType>::OrthoNormalBasis() noexcept:
    m_x{ OrthoNormalBasis<RealType>::worldX() },
    m_y{ OrthoNormalBasis<RealType>::worldY() },
    m_z{ OrthoNormalBasis<RealType>::worldZ() }
{}
template OrthoNormalBasis<float>::OrthoNormalBasis() noexcept;
template OrthoNormalBasis<double>::OrthoNormalBasis() noexcept;

template <typename RealType>
OrthoNormalBasis<RealType>::OrthoNormalBasis(const norm3_t<RealType> &x,
                                             const norm3_t<RealType> &y,
                                             const norm3_t<RealType> &z) noexcept:
    m_x{ x },
    m_y{ y },
    m_z{ z }
{}
template OrthoNormalBasis<float>::OrthoNormalBasis(const norm3_t<float> &x,
                                                   const norm3_t<float> &y,
                                                   const norm3_t<float> &z) noexcept;
template OrthoNormalBasis<double>::OrthoNormalBasis(const norm3_t<double> &x,
                                                    const norm3_t<double> &y,
                                                    const norm3_t<double> &z) noexcept;

template <typename RealType>
OrthoNormalBasis<RealType> OrthoNormalBasis<RealType>::fromZ(const norm3_t<RealType> &z) noexcept
{
    static const auto alike = 0.999;
    const auto xx = (norm3_t<RealType>)(std::abs(z.dot(worldX())) > alike ? worldY() : worldX()).cross(z);
    const auto yy = (norm3_t<RealType>)z.cross(xx);
    return OrthoNormalBasis(xx, yy, z);
}
template OrthoNormalBasis<float> OrthoNormalBasis<float>::fromZ(const norm3_t<float> &z) noexcept;
template OrthoNormalBasis<double> OrthoNormalBasis<double>::fromZ(const norm3_t<double> &z) noexcept;

template <typename RealType>
OrthoNormalBasis<RealType> OrthoNormalBasis<RealType>::fromXY(const norm3_t<RealType> &x,
                                                              const norm3_t<RealType> &y) noexcept
{
    const auto zz = (norm3_t<RealType>)x.cross(y);
    return OrthoNormalBasis(x, y, zz);
}
template OrthoNormalBasis<float> OrthoNormalBasis<float>::fromXY(const norm3_t<float> &x,
                                                                 const norm3_t<float> &y) noexcept;
template OrthoNormalBasis<double> OrthoNormalBasis<double>::fromXY(const norm3_t<double> &x,
                                                                   const norm3_t<double> &y) noexcept;

template <typename RealType>
OrthoNormalBasis<RealType> OrthoNormalBasis<RealType>::fromXZ(const norm3_t<RealType> &x,
                                                              const norm3_t<RealType> &z) noexcept
{
    const auto yy = (norm3_t<RealType>)z.cross(x);
    return OrthoNormalBasis(x, yy, z);
}
template OrthoNormalBasis<float> OrthoNormalBasis<float>::fromXZ(const norm3_t<float> &x,
                                                                 const norm3_t<float> &z) noexcept;
template OrthoNormalBasis<double> OrthoNormalBasis<double>::fromXZ(const norm3_t<double> &x,
                                                                   const norm3_t<double> &z) noexcept;

template <typename RealType>
OrthoNormalBasis<RealType> OrthoNormalBasis<RealType>::fromYZ(const norm3_t<RealType> &y,
                                                              const norm3_t<RealType> &z) noexcept
{
    const auto xx = (norm3_t<RealType>)y.cross(z);
    return OrthoNormalBasis(xx, y, z);
}
template OrthoNormalBasis<float> OrthoNormalBasis<float>::fromYZ(const norm3_t<float> &y,
                                                                 const norm3_t<float> &z) noexcept;
template OrthoNormalBasis<double> OrthoNormalBasis<double>::fromYZ(const norm3_t<double> &y,
                                                                   const norm3_t<double> &z) noexcept;

template <typename RealType>
vec3_t<RealType> OrthoNormalBasis<RealType>::toLocal(const vec3_t<RealType> &world) const noexcept
{
    return vec3_t<RealType>{
        world.dot(m_x),
        world.dot(m_y),
        world.dot(m_z)
    };
}
template vec3_t<float> OrthoNormalBasis<float>::toLocal(const vec3_t<float> &world) const noexcept;
template vec3_t<double> OrthoNormalBasis<double>::toLocal(const vec3_t<double> &world) const noexcept;

template <typename RealType>
vec3_t<RealType> OrthoNormalBasis<RealType>::toWorld(const vec3_t<RealType> &local) const noexcept
{
    return m_x * local.x + m_y * local.y + m_z * local.z;
}
template vec3_t<float> OrthoNormalBasis<float>::toWorld(const vec3_t<float> &local) const noexcept;
template vec3_t<double> OrthoNormalBasis<double>::toWorld(const vec3_t<double> &local) const noexcept;

#define $getter(axis)                                                                   \
    template <typename RealType>                                                        \
    norm3_t<RealType> &OrthoNormalBasis<RealType>::axis() noexcept                      \
    {                                                                                   \
        return m_##axis;                                                                \
    }                                                                                   \
    template norm3_t<float> &OrthoNormalBasis<float>::axis() noexcept;                  \
    template norm3_t<double> &OrthoNormalBasis<double>::axis() noexcept;                \
                                                                                        \
    template <typename RealType>                                                        \
    const norm3_t<RealType> &OrthoNormalBasis<RealType>::axis() const noexcept          \
    {                                                                                   \
        return m_##axis;                                                                \
    }                                                                                   \
    template const norm3_t<float> &OrthoNormalBasis<float>::axis() const noexcept;      \
    template const norm3_t<double> &OrthoNormalBasis<double>::axis() const noexcept;    \

$getter(x)
$getter(y)
$getter(z)

#undef $getter

} // namespace graphics::math
