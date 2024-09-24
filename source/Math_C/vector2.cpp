#include "Math_H/vector2.h"
#include "Math_H/vector3.h"
#include <cmath>

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2 &other) 
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) 
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) 
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) 
{
    return Vector2(x / scalar, y / scalar);
}

float Vector2::dot(const Vector2 &other) 
{
    return x * other.x + y * other.y;
}

float Vector2::length() 
{
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() 
{
    float len = length();
    if (len > 0) {
        return (*this) / len;
    }
    return Vector2();
}

Vector3 Vector2::addDim() 
{
    return Vector3(x, y, 1.0f);
}
