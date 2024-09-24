#pragma once
#include <array>
#include "vector4.h"

struct Mat4 
{
    std::array<float, 16> elements;

    // Constructors
    Mat4();
    Mat4(float diagonal);
    Mat4(const std::array<float, 16> &elements);

    // Identity matrix
    static const Mat4 identity();

    // Matrix multiplication
    const Mat4 operator*(Mat4& other);

    // Vector multiplication (using Vector4)
    const Vector4 operator*(Vector4& vec);

    // Wrapper methods
    const Mat4 multiplyMat4(Mat4& other) 
    {
        return (*this) * other;
    }

    const Vector4 multiplyVec4(Vector4& vec) 
    {
        return (*this) * vec;
    }

    // Transpose
    const Mat4 transpose();
};
