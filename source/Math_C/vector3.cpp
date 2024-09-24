#include "Math_H/vector3.h"
#include "Math_H/vector2.h"
#include "Math_H/vector4.h"
#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// Addition
const Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

const Vector3 Vector3::operator-(const Vector3 &other) 
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

const Vector3 Vector3::operator*(float scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

const Vector3 Vector3::operator/(float scalar)
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

const float Vector3::dot(const Vector3 &other)
{
    return x * other.x + y * other.y + z * other.z;
}

const Vector3 Vector3::cross(const Vector3 &other)
{
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

const float Vector3::length()
{
    return std::sqrt(x * x + y * y + z * z);
}

const Vector3 Vector3::normalize()
{
    float len = length();
    if (len > 0) {
        return (*this) / len;
    }
    return Vector3();
}

Vector4 Vector3::addDim() 
{
    return Vector4(x, y, z, 1.0f);
}

Vector2 Vector3::removeDim() 
{
    return Vector2(x, y);
}
