#ifndef GRAPHICS_COMMON_MATH_MATRIX_H__
#define GRAPHICS_COMMON_MATH_MATRIX_H__

namespace graphics::math{

template <typename RealType>
union vec3_t;

template <typename RealType>
union mat4_t;

template <typename RealType = double>
union mat3_t
{
    RealType data[3 * 3];
    struct
    {
        union
        {
            struct
            {
                RealType v11, v12, v13;
            };
            vec3_t<RealType> v1;
        };
        union
        {
            struct
            {
                RealType v21, v22, v23;
            };
            vec3_t<RealType> v2;
        };
        union
        {
            struct
            {
                RealType v31, v32, v33;
            };
            vec3_t<RealType> v3;
        };
    };

    explicit operator mat4_t<RealType>() const noexcept;

    mat3_t operator*(const mat3_t &rhs) const noexcept;
    vec3_t<RealType> operator*(const vec3_t<RealType> &rhs) const noexcept;
    mat3_t operator*(const RealType rhs) const noexcept;
    mat3_t operator/(const RealType rhs) const noexcept;

    mat3_t transpose() const noexcept;
    mat3_t inverse() const noexcept;

    RealType *operator[](int row) noexcept;
    const RealType *operator[](int row) const noexcept;
};

template <typename RealType>
union vec4_t;

template <typename RealType = double>
union mat4_t
{
    RealType data[4 * 4];
    struct
    {
        union
        {
            struct
            {
                RealType v11, v12, v13, v14;
            };
            vec4_t<RealType> v1;
        };
        union
        {
            struct
            {
                RealType v21, v22, v23, v24;
            };
            vec4_t<RealType> v2;
        };
        union
        {
            struct
            {
                RealType v31, v32, v33, v34;
            };
            vec4_t<RealType> v3;
        };
        union
        {
            struct
            {
                RealType v41, v42, v43, v44;
            };
            vec4_t<RealType> v4;
        };
    };

    explicit operator mat3_t<RealType>() const noexcept;

    mat4_t operator*(const mat4_t &rhs) const noexcept;
    vec4_t<RealType> operator*(const vec4_t<RealType> &rhs) const noexcept;
    mat4_t operator*(const RealType rhs) const noexcept;
    mat4_t operator/(const RealType rhs) const noexcept;

    mat4_t transpose() const noexcept;
    mat4_t inverse() const noexcept;

    RealType *operator[](int row) noexcept;
    const RealType *operator[](int row) const noexcept;
};

} // namespace graphics::math

#endif // GRAPHICS_COMMON_MATH_MATRIX_H__
