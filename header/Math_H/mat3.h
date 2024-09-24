#pragma once
#include <array>
#include "vector3.h"

struct Mat3 
{
    std::array<float, 9> elements;

    // Constructors
    Mat3();
    Mat3(float diagonal);
    Mat3(const std::array<float, 9> &elements);

    // Identity matrix
    static const Mat3 identity();

    // Matrix multiplication
    const Mat3 operator*(const Mat3& other);

    // Vector multiplication (using Vector3)
    const Vector3 operator*(const Vector3& vec);

    // Wrapper methods
    const Mat3 multiplyMat3(const Mat3& other) 
    {
        return (*this) * other;
    }

    const Vector3 multiplyVec3(const Vector3& vec) 
    {
        return (*this) * vec;
    }

    // Transpose
    const Mat3 transpose();
};
