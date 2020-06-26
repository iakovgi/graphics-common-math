#include "vec.h"

#include "norm.h"

#include <cmath>

namespace graphics::math{

template <typename RealType>
vec2_t<RealType>::vec2_t(const RealType x,
                         const RealType y) noexcept:
    x{ x },
    y{ y }
{}
template vec2_t<float>::vec2_t(const float x, const float y) noexcept;
template vec2_t<double>::vec2_t(const double x, const double y) noexcept;

template <typename RealType>
vec3_t<RealType>::vec3_t(const RealType x,
                         const RealType y,
                         const RealType z) noexcept:
    x{ x },
    y{ y },
    z{ z }
{}
template vec3_t<float>::vec3_t(const float x, const float y, const float z) noexcept;
template vec3_t<double>::vec3_t(const double x, const double y, const double z) noexcept;

template <typename RealType>
vec4_t<RealType>::vec4_t(const RealType x,
                         const RealType y,
                         const RealType z,
                         const RealType w) noexcept:
    x{ x },
    y{ y },
    z{ z },
    w{ w }
{}
template vec4_t<float>::vec4_t(const float x, const float y, const float z, const float w) noexcept;
template vec4_t<double>::vec4_t(const double x, const double y, const double z, const double w) noexcept;

#define $len(N)                                                 \
    template <typename RealType>                                \
    RealType vec##N##_t<RealType>::len() const noexcept         \
    {                                                           \
        RealType result = 0.0;                                  \
        for(auto i = 0; i < N; ++i) {                           \
            result += data[i] * data[i];                        \
        }                                                       \
        return std::sqrt(result);                               \
    }                                                           \
    template float vec##N##_t<float>::len() const noexcept;     \
    template double vec##N##_t<double>::len() const noexcept;

$len(2)
$len(3)
$len(4)

#undef $len

#define $lenSquared(N)                                                  \
    template <typename RealType>                                        \
    RealType vec##N##_t<RealType>::lenSquared() const noexcept          \
    {                                                                   \
        RealType result = 0.0;                                          \
        for(auto i = 0; i < N; ++i) {                                   \
            result += data[i] * data[i];                                \
        }                                                               \
        return result;                                                  \
    }                                                                   \
    template float vec##N##_t<float>::lenSquared() const noexcept;      \
    template double vec##N##_t<double>::lenSquared() const noexcept;

$lenSquared(2)
$lenSquared(3)
$lenSquared(4)

#undef $lenSquared

#define $operator_norm(N)                                                           \
    template <typename RealType>                                                    \
    vec##N##_t<RealType>::operator norm##N##_t<RealType>() const noexcept           \
    {                                                                               \
        const auto invLen = 1.0 / len();                                            \
        auto result = norm##N##_t<RealType>{};                                      \
        for(auto i = 0; i < N; ++i) {                                               \
            result[i] = data[i] * invLen;                                           \
        }                                                                           \
        return result;                                                              \
    }                                                                               \
    template vec##N##_t<float>::operator norm##N##_t<float>() const noexcept;       \
    template vec##N##_t<double>::operator norm##N##_t<double>() const noexcept;

$operator_norm(2);
$operator_norm(3);
$operator_norm(4);

#undef $operator_norm

#define $dot(N)                                                                         \
    template <typename RealType>                                                        \
    RealType vec##N##_t<RealType>::dot(const vec##N##_t &rhs) const noexcept            \
    {                                                                                   \
        RealType result = 0.0;                                                          \
        for(auto i = 0; i < N; ++i) {                                                   \
            result += data[i] * rhs.data[i];                                            \
        }                                                                               \
        return result;                                                                  \
    }                                                                                   \
    template float vec##N##_t<float>::dot(const vec##N##_t &rhs) const noexcept;        \
    template double vec##N##_t<double>::dot(const vec##N##_t &rhs) const noexcept;

$dot(2)
$dot(3)
$dot(4)

#undef $dot

template <typename RealType>
vec3_t<RealType> vec3_t<RealType>::cross(const vec3_t<RealType> &rhs) const noexcept
{
    return vec3_t<RealType>{
        -z * rhs.y + y * rhs.z,
        -x * rhs.z + z * rhs.x,
        -y * rhs.x + x * rhs.y
    };
}
template vec3_t<float> vec3_t<float>::cross(const vec3_t &rhs) const noexcept;
template vec3_t<double> vec3_t<double>::cross(const vec3_t &rhs) const noexcept;

#define $operator_unary_minus(N)                                                        \
    template <typename RealType>                                                        \
    vec##N##_t<RealType> vec##N##_t<RealType>::operator-() const noexcept               \
    {                                                                                   \
        auto result = vec##N##_t<RealType>{};                                           \
        for(auto i = 0; i < N; ++i) {                                                   \
            result.data[i] = -data[i];                                                  \
        }                                                                               \
        return result;                                                                  \
    }                                                                                   \
    template vec##N##_t<float> vec##N##_t<float>::operator-() const noexcept;           \
    template vec##N##_t<double> vec##N##_t<double>::operator-() const noexcept;

$operator_unary_minus(2)
$operator_unary_minus(3)
$operator_unary_minus(4)

#undef $operator_unary_minus

#define $operator_binary_vec(N, op)                                                                     \
    template <typename RealType>                                                                        \
    vec##N##_t<RealType> vec##N##_t<RealType>::operator op(const vec##N##_t &rhs) const noexcept        \
    {                                                                                                   \
        auto result = vec##N##_t<RealType>{};                                                           \
        for(auto i = 0; i < N; ++i) {                                                                   \
            result.data[i] = data[i] op rhs.data[i];                                                    \
        }                                                                                               \
        return result;                                                                                  \
    }                                                                                                   \
    template vec##N##_t<float> vec##N##_t<float>::operator op(const vec##N##_t &rhs) const noexcept;    \
    template vec##N##_t<double> vec##N##_t<double>::operator op(const vec##N##_t &rhs) const noexcept;

$operator_binary_vec(2, +)
$operator_binary_vec(2, -)

$operator_binary_vec(3, +)
$operator_binary_vec(3, -)

$operator_binary_vec(4, +)
$operator_binary_vec(4, -)

#undef $operator_binary_vec

#define $operator_binary_realtype(N, op)                                                            \
    template <typename RealType>                                                                    \
    vec##N##_t<RealType> vec##N##_t<RealType>::operator op(const RealType rhs) const noexcept       \
    {                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                       \
        for(auto i = 0; i < N; ++i) {                                                               \
            result.data[i] = data[i] op rhs;                                                        \
        }                                                                                           \
        return result;                                                                              \
    }                                                                                               \
    template vec##N##_t<float> vec##N##_t<float>::operator op(const float rhs) const noexcept;      \
    template vec##N##_t<double> vec##N##_t<double>::operator op(const double rhs) const noexcept;

$operator_binary_realtype(2, /)
$operator_binary_realtype(2, *)

$operator_binary_realtype(3, /)
$operator_binary_realtype(3, *)

$operator_binary_realtype(4, /)
$operator_binary_realtype(4, *)

#undef $operator_binary_realtype

#define $operator_realtype_mult(N)                                                                  \
    template <typename RealType>                                                                    \
    vec##N##_t<RealType> operator*(const RealType lhs, const vec##N##_t<RealType> &rhs) noexcept    \
    {                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                       \
        for(auto i = 0; i < N; ++i) {                                                               \
            result.data[i] = lhs * rhs.data[i];                                                     \
        }                                                                                           \
        return result;                                                                              \
    }                                                                                               \
    template vec##N##_t<float> operator*(const float lhs, const vec##N##_t<float> &rhs) noexcept;   \
    template vec##N##_t<double> operator*(const double lhs, const vec##N##_t<double> &rhs) noexcept;

$operator_realtype_mult(2)
$operator_realtype_mult(3)
$operator_realtype_mult(4)

#undef $operator_realtype_mult

#define $operator_sqrbr(N)                                                          \
    template <typename RealType>                                                    \
    RealType &vec##N##_t<RealType>::operator[](int idx) noexcept                    \
    {                                                                               \
        return data[idx];                                                           \
    }                                                                               \
    template float &vec##N##_t<float>::operator[](int idx) noexcept;                \
    template double &vec##N##_t<double>::operator[](int idx) noexcept;              \
                                                                                    \
    template <typename RealType>                                                    \
    const RealType &vec##N##_t<RealType>::operator[](int idx) const noexcept        \
    {                                                                               \
        return data[idx];                                                           \
    }                                                                               \
    template const float &vec##N##_t<float>::operator[](int idx) const noexcept;    \
    template const double &vec##N##_t<double>::operator[](int idx) const noexcept;

$operator_sqrbr(2)
$operator_sqrbr(3)
$operator_sqrbr(4)

#undef $operator_sqrbr

} // namespace graphics::math
