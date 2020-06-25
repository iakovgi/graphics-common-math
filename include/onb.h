#ifndef GRAPHICS_COMMON_MATH_ONB_H__
#define GRAPHICS_COMMON_MATH_ONB_H__

namespace graphics::math {

template <typename RealType>
union vec3_t;

template <typename RealType>
union norm3_t;

template <typename RealType = double>
class OrthoNormalBasis
{
public:
    static norm3_t<RealType> worldX() noexcept;
    static norm3_t<RealType> worldY() noexcept;
    static norm3_t<RealType> worldZ() noexcept;

    OrthoNormalBasis() noexcept;
    OrthoNormalBasis(const norm3_t<RealType> &x, const norm3_t<RealType> &y, const norm3_t<RealType> &z) noexcept;
    static OrthoNormalBasis fromZ(const norm3_t<RealType> &z) noexcept;
    static OrthoNormalBasis fromXY(const norm3_t<RealType> &x, const norm3_t<RealType> &y) noexcept;
    static OrthoNormalBasis fromXZ(const norm3_t<RealType> &x, const norm3_t<RealType> &z) noexcept;
    static OrthoNormalBasis fromYZ(const norm3_t<RealType> &y, const norm3_t<RealType> &z) noexcept;

    vec3_t<RealType> toLocal(const vec3_t<RealType> &world) const noexcept;
    vec3_t<RealType> toWorld(const vec3_t<RealType> &local) const noexcept;

    norm3_t<RealType> &x() noexcept;
    const norm3_t<RealType> &x() const noexcept;

    norm3_t<RealType> &y() noexcept;
    const norm3_t<RealType> &y() const noexcept;

    norm3_t<RealType> &z() noexcept;
    const norm3_t<RealType> &z() const noexcept;

    OrthoNormalBasis(const OrthoNormalBasis& that) noexcept = default;
    OrthoNormalBasis(OrthoNormalBasis&& that) noexcept = default;
    ~OrthoNormalBasis() noexcept = default;

    OrthoNormalBasis& operator=(const OrthoNormalBasis& that) noexcept = default;
    OrthoNormalBasis& operator=(OrthoNormalBasis&& that) noexcept = default;

private:
    norm3_t<RealType> m_x;
    norm3_t<RealType> m_y;
    norm3_t<RealType> m_z;
};

}
#endif // GRAPHICS_COMMON_MATH_ONB_H__
