#include "Math_H/mat4.h"

Mat4::Mat4() 
{
    elements = {1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f};
}

Mat4::Mat4(float diagonal) 
{
    elements = {diagonal, 0.0f, 0.0f, 0.0f,
                0.0f, diagonal, 0.0f, 0.0f,
                0.0f, 0.0f, diagonal, 0.0f,
                0.0f, 0.0f, 0.0f, diagonal};
}

Mat4::Mat4(const std::array<float, 16>& elements) : elements(elements) {}

const Mat4 Mat4::identity() 
{
    return Mat4();
}

const Mat4 Mat4::operator*(Mat4& other)
{
    Mat4 result;

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            result.elements[row * 4 + col] =
                elements[row * 4 + 0] * other.elements[0 * 4 + col] +
                elements[row * 4 + 1] * other.elements[1 * 4 + col] +
                elements[row * 4 + 2] * other.elements[2 * 4 + col] +
                elements[row * 4 + 3] * other.elements[3 * 4 + col];
        
    
    return result;
}

const Vector4 Mat4::operator*(Vector4& vec) 
{
    return Vector4(
        elements[0] * vec.x + elements[1] * vec.y + elements[2] * vec.z + elements[3] * vec.h,
        elements[4] * vec.x + elements[5] * vec.y + elements[6] * vec.z + elements[7] * vec.h,
        elements[8] * vec.x + elements[9] * vec.y + elements[10] * vec.z + elements[11] * vec.h,
        elements[12] * vec.x + elements[13] * vec.y + elements[14] * vec.z + elements[15] * vec.h
    );
}

// Transpose
const Mat4 Mat4::transpose() 
{
    Mat4 result;

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            result.elements[row * 4 + col] = elements[col * 4 + row];
        
    
    return result;
}
