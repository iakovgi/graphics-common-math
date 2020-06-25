#ifndef GRAPHICS_COMMON_MATH_NORM_H__
#define GRAPHICS_COMMON_MATH_NORM_H__

namespace graphics::math{

#define $declare_operator_binary_vec(N, op)                                                                     \
    vec##N##_t<RealType> operator op(const norm##N##_t &rhs) const noexcept;                                    \
    vec##N##_t<RealType> operator op(const vec##N##_t<RealType> &rhs) const noexcept;                           \
    friend vec##N##_t<RealType> operator op(const vec##N##_t<RealType> &lhs, const norm##N##_t &rhs) noexcept;

template <typename RealType>
union vec2_t;

template <typename RealType = double>
union norm2_t
{
    RealType data[2];
    struct
    {
        union
        {
            RealType x;
            RealType s;
        };
        union
        {
            RealType y;
            RealType t;
        };
    };

    norm2_t(const RealType x = 0.0,
            const RealType y = 0.0) noexcept;

    operator vec2_t<RealType>() const noexcept;

    RealType dot(const vec2_t<RealType> &rhs) const noexcept;

    norm2_t operator-() const noexcept;

    $declare_operator_binary_vec(2, +)
    $declare_operator_binary_vec(2, -)
    vec2_t<RealType> operator*(const RealType rhs) const noexcept;
    vec2_t<RealType> operator/(const RealType rhs) const noexcept;

    friend vec2_t<RealType> operator*(const RealType lhs, const norm2_t &rhs) noexcept;

    RealType &operator[](int idx) noexcept;
    const RealType &operator[](int idx) const noexcept;
};

template <typename RealType>
union vec3_t;

template <typename RealType = double>
union norm3_t
{
    RealType data[3];
    struct
    {
        union
        {
            RealType x;
            RealType r;
        };
        union
        {
            RealType y;
            RealType g;
        };
        union
        {
            RealType z;
            RealType b;
        };
    };

    norm3_t(const RealType x = 0.0,
            const RealType y = 0.0,
            const RealType z = 0.0) noexcept;

    operator vec3_t<RealType>() const noexcept;

    RealType dot(const vec3_t<RealType> &rhs) const noexcept;
    vec3_t<RealType> cross(const vec3_t<RealType> &rhs) const noexcept;

    norm3_t operator-() const noexcept;

    $declare_operator_binary_vec(3, +)
    $declare_operator_binary_vec(3, -)
    vec3_t<RealType> operator*(const RealType rhs) const noexcept;
    vec3_t<RealType> operator/(const RealType rhs) const noexcept;

    friend vec3_t<RealType> operator*(const RealType lhs, const norm3_t &rhs) noexcept;

    RealType &operator[](int idx) noexcept;
    const RealType &operator[](int idx) const noexcept;
};

template <typename RealType>
union vec4_t;

template <typename RealType = double>
union norm4_t
{
    RealType data[4];
    struct
    {
        union
        {
            RealType x;
            RealType r;
        };
        union
        {
            RealType y;
            RealType g;
        };
        union
        {
            RealType z;
            RealType b;
        };
        union
        {
            RealType w;
            RealType a;
        };
    };

    norm4_t(const RealType x = 0.0,
            const RealType y = 0.0,
            const RealType z = 0.0,
            const RealType w = 0.0) noexcept;

    operator vec4_t<RealType>() const noexcept;

    RealType dot(const vec4_t<RealType> &rhs) const noexcept;

    norm4_t operator-() const noexcept;

    $declare_operator_binary_vec(4, +)
    $declare_operator_binary_vec(4, -)
    vec4_t<RealType> operator*(const RealType rhs) const noexcept;
    vec4_t<RealType> operator/(const RealType rhs) const noexcept;

    friend vec4_t<RealType> operator*(const RealType lhs, const norm4_t &rhs) noexcept;

    RealType &operator[](int idx) noexcept;
    const RealType &operator[](int idx) const noexcept;
};

#undef $declare_operator_binary_vec

} // namespace graphics::math

#endif // GRAPHICS_COMMON_MATH_NORM_H__
