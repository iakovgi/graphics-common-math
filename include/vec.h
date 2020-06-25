#ifndef GRAPHICS_COMMON_MATH_VEC_H__
#define GRAPHICS_COMMON_MATH_VEC_H__

namespace graphics{ namespace math{

template <typename RealType>
union norm2_t;

template <typename RealType = double>
union vec2_t
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

    vec2_t(const RealType x = 0.0,
           const RealType y = 0.0) noexcept;

    RealType len() const noexcept;
    RealType lenSquared() const noexcept;

    operator norm2_t<RealType>() const noexcept;

    RealType dot(const vec2_t &rhs) const noexcept;

    vec2_t operator-() const noexcept;
    vec2_t operator+(const vec2_t &rhs) const noexcept;
    vec2_t operator-(const vec2_t &rhs) const noexcept;
    vec2_t operator/(const RealType rhs) const noexcept;
    vec2_t operator*(const RealType rhs) const noexcept;
    friend vec2_t operator*(const RealType lhs, const vec2_t &rhs) noexcept;

    RealType &operator[](int idx) noexcept;
    const RealType &operator[](int idx) const noexcept;
};

template <typename RealType>
union norm3_t;

template <typename RealType = double>
union vec3_t
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

    vec3_t(const RealType x = 0.0,
           const RealType y = 0.0,
           const RealType z = 0.0) noexcept;

    RealType len() const noexcept;
    RealType lenSquared() const noexcept;

    operator norm3_t<RealType>() const noexcept;

    RealType dot(const vec3_t &rhs) const noexcept;
    vec3_t cross(const vec3_t &rhs) const noexcept;

    vec3_t operator-() const noexcept;
    vec3_t operator+(const vec3_t &rhs) const noexcept;
    vec3_t operator-(const vec3_t &rhs) const noexcept;
    vec3_t operator/(const RealType rhs) const noexcept;
    vec3_t operator*(const RealType rhs) const noexcept;
    friend vec3_t operator*(const RealType lhs, const vec3_t &rhs) noexcept;

    RealType& operator[](int idx) noexcept;
    const RealType& operator[](int idx) const noexcept;
};

template <typename RealType>
union norm4_t;

template <typename RealType>
union vec4_t
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

    vec4_t(const RealType x = 0.0,
           const RealType y = 0.0,
           const RealType z = 0.0,
           const RealType w = 0.0) noexcept;

    RealType len() const noexcept;
    RealType lenSquared() const noexcept;

    operator norm4_t<RealType>() const noexcept;

    RealType dot(const vec4_t &rhs) const noexcept;

    vec4_t operator-() const noexcept;
    vec4_t operator+(const vec4_t &rhs) const noexcept;
    vec4_t operator-(const vec4_t &rhs) const noexcept;
    vec4_t operator/(const RealType rhs) const noexcept;
    vec4_t operator*(const RealType rhs) const noexcept;
    friend vec4_t operator*(const float &lhs, const vec4_t &rhs) noexcept;

    RealType &operator[](int idx) noexcept;
    const RealType &operator[](int idx) const noexcept;
};

} // namespace math
} // namespace graphics

#endif // GRAPHICS_COMMON_MATH_VEC_H__
