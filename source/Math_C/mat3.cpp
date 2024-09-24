#include "Math_H/mat3.h"

Mat3::Mat3() 
{
    elements = {1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f};
}

Mat3::Mat3(float diagonal) 
{
    elements = {diagonal, 0.0f, 0.0f,
                0.0f, diagonal, 0.0f,
                0.0f, 0.0f, diagonal};
}

Mat3::Mat3(const std::array<float, 9>& elements) : elements(elements) {}

const Mat3 Mat3::identity() 
{
    return Mat3();
}

const Mat3 Mat3::operator*(const Mat3& other) 
{
    Mat3 result;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result.elements[row * 3 + col] =
                elements[row * 3 + 0] * other.elements[0 * 3 + col] +
                elements[row * 3 + 1] * other.elements[1 * 3 + col] +
                elements[row * 3 + 2] * other.elements[2 * 3 + col];
        }
    }
    return result;
}

const Vector3 Mat3::operator*(const Vector3& vec) 
{
    return Vector3(
        elements[0] * vec.x + elements[1] * vec.y + elements[2] * vec.z,
        elements[3] * vec.x + elements[4] * vec.y + elements[5] * vec.z,
        elements[6] * vec.x + elements[7] * vec.y + elements[8] * vec.z
    );
}

const Mat3 Mat3::transpose() 
{
    return Mat3({
        elements[0], elements[3], elements[6],
        elements[1], elements[4], elements[7],
        elements[2], elements[5], elements[8]
    });
}
