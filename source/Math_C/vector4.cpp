#include "Math_H/vector4.h"
#include "Math_H/vector3.h"
#include <cmath>

Vector4::Vector4() : x(0), y(0), z(0), h(0) {}

Vector4::Vector4(float x, float y, float z, float h) : x(x), y(y), z(z), h(h) {}

Vector4 Vector4::operator+(const Vector4 &other) 
{
    return Vector4(x + other.x, y + other.y, z + other.z, h + other.h);
}

Vector4 Vector4::operator-(const Vector4 &other) 
{
    return Vector4(x - other.x, y - other.y, z - other.z, h - other.h);
}

Vector4 Vector4::operator*(float scalar) 
{
    return Vector4(x * scalar, y * scalar, z * scalar, h * scalar);
}

Vector4 Vector4::operator/(float scalar) 
{
    return Vector4(x / scalar, y / scalar, z / scalar, h / scalar);
}

float Vector4::dot(const Vector4 &other) 
{
    return x * other.x + y * other.y + z * other.z + h * other.h;
}

float Vector4::length() 
{
    return std::sqrt(x * x + y * y + z * z + h * h);
}

Vector4 Vector4::normalize() 
{
    float len = length();
    if (len > 0) {
        return (*this) / len;
    }
    return Vector4();
}

Vector3 Vector4::removeDim() 
{
    return Vector3(x, y, z);
}
