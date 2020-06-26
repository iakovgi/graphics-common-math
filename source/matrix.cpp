#include "matrix.h"

#include "vec.h"

namespace graphics::math{

template <typename RealType>
mat3_t<RealType>::operator mat4_t<RealType>() const noexcept
{
    return mat4_t<RealType>{
        v11, v12, v13, 0.0,
        v21, v22, v23, 0.0,
        v31, v32, v33, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
}
template mat3_t<float>::operator mat4_t<float>() const noexcept;
template mat3_t<double>::operator mat4_t<double>() const noexcept;

template <typename RealType>
mat4_t<RealType>::operator mat3_t<RealType>() const noexcept
{
    return mat3_t<RealType>{
        v11, v12, v13,
        v21, v22, v23,
        v31, v32, v33
    };
}
template mat4_t<float>::operator mat3_t<float>() const noexcept;
template mat4_t<double>::operator mat3_t<double>() const noexcept;

#define $matmul(N)                                                                                              \
    template <typename RealType>                                                                                \
    mat##N##_t<RealType> mat##N##_t<RealType>::operator*(const mat##N##_t<RealType> &rhs) const noexcept        \
    {                                                                                                           \
        auto result = mat##N##_t<RealType>{};                                                                   \
        for(auto r = 0; r < N; ++r) {                                                                           \
            for(auto c = 0; c < N; ++c) {                                                                       \
                result.data[r * N + c] = 0.0;                                                                   \
            }                                                                                                   \
            for(auto i = 0; i < N; ++i) {                                                                       \
                for(auto c = 0; c < N; ++c) {                                                                   \
                    result.data[r * N + c] += data[r * N + i] * rhs.data[i * N + c];                            \
                }                                                                                               \
            }                                                                                                   \
        }                                                                                                       \
        return result;                                                                                          \
    }                                                                                                           \
    template mat##N##_t<float> mat##N##_t<float>::operator*(const mat##N##_t<float> &rhs) const noexcept;       \
    template mat##N##_t<double> mat##N##_t<double>::operator*(const mat##N##_t<double> &rhs) const noexcept;

$matmul(3)
$matmul(4)

#undef $matmul

#define $vecmul(N)                                                                                          \
    template <typename RealType>                                                                            \
    vec##N##_t<RealType> mat##N##_t<RealType>::operator*(const vec##N##_t<RealType> &rhs) const noexcept    \
    {                                                                                                       \
        auto result = vec##N##_t<RealType>{};                                                               \
        for(auto i = 0; i < N; ++i) {                                                                       \
            for(auto j = 0; j < N; ++j) {                                                                   \
                result.data[i] += data[j * N + i] * rhs.data[j];                                            \
            }                                                                                               \
        }                                                                                                   \
        return result;                                                                                      \
    }                                                                                                       \
    template vec##N##_t<float> mat##N##_t<float>::operator*(const vec##N##_t<float> &rhs) const noexcept;   \
    template vec##N##_t<double> mat##N##_t<double>::operator*(const vec##N##_t<double> &rhs) const noexcept;

$vecmul(3)
$vecmul(4)

#undef $vecmul

#define $operator_realtype(N, op)\
    template <typename RealType>                                                                            \
    mat##N##_t<RealType> mat##N##_t<RealType>::operator op(const RealType rhs) const noexcept               \
    {                                                                                                       \
        auto result = mat##N##_t<RealType>{};                                                               \
        for(auto r = 0; r < N; ++r) {                                                                       \
            for(auto c = 0; c < N; ++c) {                                                                   \
                result.data[r * N + c] = data[r * N + c] op rhs;                                            \
            }                                                                                               \
        }                                                                                                   \
        return result;                                                                                      \
    }                                                                                                       \
    template mat##N##_t<float> mat##N##_t<float>::operator op(const float rhs) const noexcept;              \
    template mat##N##_t<double> mat##N##_t<double>::operator op(const double rhs) const noexcept;

$operator_realtype(3, *)
$operator_realtype(3, /)

$operator_realtype(4, *)
$operator_realtype(4, /)

#undef $operator_realtype

#define $operator_sqrbr(N)                                                          \
    template <typename RealType>                                                    \
    RealType *mat##N##_t<RealType>::operator[](int row) noexcept                    \
    {                                                                               \
        return data + row * N;                                                      \
    }                                                                               \
    template float *mat##N##_t<float>::operator[](int row) noexcept;                \
    template double *mat##N##_t<double>::operator[](int row) noexcept;              \
                                                                                    \
    template <typename RealType>                                                    \
    const RealType *mat##N##_t<RealType>::operator[](int row) const noexcept        \
    {                                                                               \
        return data + row * N;                                                      \
    }                                                                               \
    template const float *mat##N##_t<float>::operator[](int row) const noexcept;    \
    template const double *mat##N##_t<double>::operator[](int row) const noexcept;

$operator_sqrbr(3)
$operator_sqrbr(4)

#undef $operator_sqrbr

#define $transpose(N)                                                           \
    template <typename RealType>                                                \
    mat##N##_t<RealType> mat##N##_t<RealType>::transpose() const noexcept       \
    {                                                                           \
        auto result = mat##N##_t<RealType>{};                                   \
        for(auto r = 0; r < N; ++r) {                                           \
            for(auto c = 0; c < N; ++c) {                                       \
                result.data[r * N + c] = data[c * N + r];                       \
            }                                                                   \
        }                                                                       \
        return result;                                                          \
    }                                                                           \
    template mat##N##_t<float> mat##N##_t<float>::transpose() const noexcept;   \
    template mat##N##_t<double> mat##N##_t<double>::transpose() const noexcept;

$transpose(3)
$transpose(4)

#undef $transpose

template <typename RealType>
mat3_t<RealType> mat3_t<RealType>::inverse() const noexcept
{
    const auto minors = mat3_t<RealType>{
        v22 * v33 - v23 * v32, v21 * v33 - v23 * v31, v21 * v32 - v22 * v31,
        v12 * v33 - v13 * v32, v11 * v33 - v13 * v31, v11 * v32 - v12 * v31,
        v12 * v23 - v13 * v22, v11 * v23 - v13 * v21, v11 * v22 - v12 * v21
    };
    const auto determinant = v11 * minors.v11 + v12 * minors.v12 + v13 * minors.v13;
    return minors / determinant;
}
template mat3_t<float> mat3_t<float>::inverse() const noexcept;
template mat3_t<double> mat3_t<double>::inverse() const noexcept;

template <typename RealType>
mat4_t<RealType> mat4_t<RealType>::inverse() const noexcept
{
#define $minor(v11, v12, v13, v21, v22, v23, v31, v32, v33)\
    (v11 * (v22 * v33 - v23 * v32) + v12 * (v21 * v33 - v23 * v31) + v13 * (v21 * v32 - v22 * v31))

    const auto minors = mat4_t<RealType>{
        $minor(v22, v23, v24, v32, v33, v34, v42, v43, v44), // m11
        $minor(v21, v23, v24, v31, v33, v34, v41, v43, v44), // m12
        $minor(v21, v22, v24, v31, v32, v34, v41, v42, v44), // m13
        $minor(v21, v22, v23, v31, v32, v33, v41, v42, v43), // m14

        $minor(v12, v13, v14, v32, v33, v34, v42, v43, v44), // m21
        $minor(v11, v13, v14, v31, v33, v34, v41, v43, v44), // m22
        $minor(v11, v12, v14, v31, v32, v34, v41, v42, v44), // m23
        $minor(v11, v12, v13, v31, v32, v33, v41, v42, v43), // m24

        $minor(v12, v13, v14, v22, v23, v24, v42, v43, v44), // m31
        $minor(v11, v13, v14, v21, v23, v24, v41, v43, v44), // m32
        $minor(v11, v12, v14, v21, v22, v24, v41, v42, v44), // m33
        $minor(v11, v12, v13, v21, v22, v23, v41, v42, v43), // m34

        $minor(v12, v13, v14, v22, v23, v24, v32, v33, v34), // m31
        $minor(v11, v13, v14, v21, v23, v24, v31, v33, v34), // m32
        $minor(v11, v12, v14, v21, v22, v24, v31, v32, v34), // m33
        $minor(v11, v12, v13, v21, v22, v23, v31, v32, v33), // m34
    };
#undef $minor

    const auto determinant = v11 * minors.v11 + v12 * minors.v12 + v13 * minors.v13 + v14 * minors.v14;
    return minors / determinant;
}
template mat4_t<float> mat4_t<float>::inverse() const noexcept;
template mat4_t<double> mat4_t<double>::inverse() const noexcept;

} // namespace graphics::math
