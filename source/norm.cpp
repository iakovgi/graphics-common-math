#include "norm.h"

#include "vec.h"

namespace graphics::math{

template <typename RealType>
norm2_t<RealType>::norm2_t(const RealType x,
                           const RealType y) noexcept:
    x{ x },
    y{ y }
{}
template norm2_t<float>::norm2_t(const float x, const float y) noexcept;
template norm2_t<double>::norm2_t(const double x, const double y) noexcept;

template <typename RealType>
norm3_t<RealType>::norm3_t(const RealType x,
                           const RealType y,
                           const RealType z) noexcept:
    x{ x },
    y{ y },
    z{ z }
{}
template norm3_t<float>::norm3_t(const float x, const float y, const float z) noexcept;
template norm3_t<double>::norm3_t(const double x, const double y, const double z) noexcept;

template <typename RealType>
norm4_t<RealType>::norm4_t(const RealType x,
                           const RealType y,
                           const RealType z,
                           const RealType w) noexcept:
    x{ x },
    y{ y },
    z{ z },
    w{ w }
{}
template norm4_t<float>::norm4_t(const float x, const float y, const float z, const float w) noexcept;
template norm4_t<double>::norm4_t(const double x, const double y, const double z, const double w) noexcept;


#define $operator_vec(N)                                                            \
    template <typename RealType>                                                    \
    norm##N##_t<RealType>::operator vec##N##_t<RealType>() const noexcept           \
    {                                                                               \
        auto result = vec##N##_t<RealType>{};                                       \
        for(auto i = 0; i < N; ++i) {                                               \
            result[i] = data[i];                                                    \
        }                                                                           \
        return result;                                                              \
    }                                                                               \
    template norm##N##_t<float>::operator vec##N##_t<float>() const noexcept;       \
    template norm##N##_t<double>::operator vec##N##_t<double>() const noexcept;

$operator_vec(2);
$operator_vec(3);
$operator_vec(4);

#undef $operator_vec

#define $dot(N)                                                                             \
    template <typename RealType>                                                            \
    RealType norm##N##_t<RealType>::dot(const vec##N##_t<RealType> &rhs) const noexcept     \
    {                                                                                       \
        RealType result = 0.0;                                                              \
        for(auto i = 0; i < N; ++i) {                                                       \
            result += data[i] * rhs.data[i];                                                \
        }                                                                                   \
        return result;                                                                      \
    }                                                                                       \
    template float norm##N##_t<float>::dot(const vec##N##_t<float> &rhs) const noexcept;    \
    template double norm##N##_t<double>::dot(const vec##N##_t<double> &rhs) const noexcept;

$dot(2)
$dot(3)
$dot(4)

#undef $dot

template <typename RealType>
vec3_t<RealType> norm3_t<RealType>::cross(const vec3_t<RealType> &rhs) const noexcept
{
    return vec3_t<RealType>{
        -z * rhs.y + y * rhs.z,
        -x * rhs.z + z * rhs.x,
        -y * rhs.x + x * rhs.y
    };
}
template vec3_t<float> norm3_t<float>::cross(const vec3_t<float> &rhs) const noexcept;
template vec3_t<double> norm3_t<double>::cross(const vec3_t<double> &rhs) const noexcept;

#define $operator_unary_minus(N)                                                    \
    template <typename RealType>                                                    \
    norm##N##_t<RealType> norm##N##_t<RealType>::operator-() const noexcept         \
    {                                                                               \
        auto result = norm##N##_t<RealType>{};                                      \
        for(auto i = 0; i < N; ++i) {                                               \
            result.data[i] = -data[i];                                              \
        }                                                                           \
        return result;                                                              \
    }                                                                               \
    template norm##N##_t<float> norm##N##_t<float>::operator-() const noexcept;     \
    template norm##N##_t<double> norm##N##_t<double>::operator-() const noexcept;

$operator_unary_minus(2)
$operator_unary_minus(3)
$operator_unary_minus(4)

#undef $operator_unary_minus

#define $operator_binary_vec(N, op)                                                                                 \
    template <typename RealType>                                                                                    \
    vec##N##_t<RealType> norm##N##_t<RealType>::operator op(const vec##N##_t<RealType> &rhs) const noexcept         \
    {                                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                                       \
        for(auto i = 0; i < N; ++i) {                                                                               \
            result.data[i] = data[i] op rhs.data[i];                                                                \
        }                                                                                                           \
        return result;                                                                                              \
    }                                                                                                               \
    template vec##N##_t<float> norm##N##_t<float>::operator op(const vec##N##_t<float> &rhs) const noexcept;        \
    template vec##N##_t<double> norm##N##_t<double>::operator op(const vec##N##_t<double> &rhs) const noexcept;     \
                                                                                                                    \
    template <typename RealType>                                                                                    \
    vec##N##_t<RealType> norm##N##_t<RealType>::operator op(const norm##N##_t<RealType> &rhs) const noexcept        \
    {                                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                                       \
        for(auto i = 0; i < N; ++i) {                                                                               \
            result.data[i] = data[i] op rhs.data[i];                                                                \
        }                                                                                                           \
        return result;                                                                                              \
    }                                                                                                               \
    template vec##N##_t<float> norm##N##_t<float>::operator op(const norm##N##_t<float> &rhs) const noexcept;       \
    template vec##N##_t<double> norm##N##_t<double>::operator op(const norm##N##_t<double> &rhs) const noexcept;    \
                                                                                                                    \
    template <typename RealType>                                                                                    \
    vec##N##_t<RealType> operator op(const vec##N##_t<RealType> &lhs, const norm##N##_t<RealType> &rhs) noexcept    \
    {                                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                                       \
        for(auto i = 0; i < N; ++i) {                                                                               \
            result.data[i] = lhs.data[i] op rhs.data[i];                                                            \
        }                                                                                                           \
        return result;                                                                                              \
    }                                                                                                               \
    template vec##N##_t<float> operator op(const vec##N##_t<float> &lhs, const norm##N##_t<float> &rhs) noexcept;   \
    template vec##N##_t<double> operator op(const vec##N##_t<double> &lhs, const norm##N##_t<double> &rhs) noexcept;

$operator_binary_vec(2, +)
$operator_binary_vec(2, -)

$operator_binary_vec(3, +)
$operator_binary_vec(3, -)

$operator_binary_vec(4, +)
$operator_binary_vec(4, -)

#undef $operator_binary_vec

#define $operator_binary_realtype(N, op)                                                            \
    template <typename RealType>                                                                    \
    vec##N##_t<RealType> norm##N##_t<RealType>::operator op(const RealType rhs) const noexcept      \
    {                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                       \
        for(auto i = 0; i < N; ++i) {                                                               \
            result.data[i] = data[i] op rhs;                                                        \
        }                                                                                           \
        return result;                                                                              \
    }                                                                                               \
    template vec##N##_t<float> norm##N##_t<float>::operator op(const float rhs) const noexcept;     \
    template vec##N##_t<double> norm##N##_t<double>::operator op(const double rhs) const noexcept;

$operator_binary_realtype(2, /)
$operator_binary_realtype(2, *)

$operator_binary_realtype(3, /)
$operator_binary_realtype(3, *)

$operator_binary_realtype(4, /)
$operator_binary_realtype(4, *)

#undef $operator_binary_realtype

#define $operator_realtype_mult(N)                                                                  \
    template <typename RealType>                                                                    \
    vec##N##_t<RealType> operator*(const RealType lhs, const norm##N##_t<RealType> &rhs) noexcept   \
    {                                                                                               \
        auto result = vec##N##_t<RealType>{};                                                       \
        for(auto i = 0; i < N; ++i) {                                                               \
            result.data[i] = lhs * rhs.data[i];                                                     \
        }                                                                                           \
        return result;                                                                              \
    }                                                                                               \
    template vec##N##_t<float> operator*(const float lhs, const norm##N##_t<float> &rhs) noexcept;  \
    template vec##N##_t<double> operator*(const double lhs, const norm##N##_t<double> &rhs) noexcept;

$operator_realtype_mult(2)
$operator_realtype_mult(3)
$operator_realtype_mult(4)

#undef $operator_realtype_mult

#define $operator_sqrbr(N)                                                          \
    template <typename RealType>                                                    \
    RealType &norm##N##_t<RealType>::operator[](int idx) noexcept                   \
    {                                                                               \
        return data[idx];                                                           \
    }                                                                               \
    template float &norm##N##_t<float>::operator[](int idx) noexcept;               \
    template double &norm##N##_t<double>::operator[](int idx) noexcept;             \
                                                                                    \
    template <typename RealType>                                                    \
    const RealType &norm##N##_t<RealType>::operator[](int idx) const noexcept       \
    {                                                                               \
        return data[idx];                                                           \
    }                                                                               \
    template const float &norm##N##_t<float>::operator[](int idx) const noexcept;   \
    template const double &norm##N##_t<double>::operator[](int idx) const noexcept;

$operator_sqrbr(2)
$operator_sqrbr(3)
$operator_sqrbr(4)

#undef $operator_sqrbr

} // namespace graphics::math
