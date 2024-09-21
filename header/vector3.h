#pragma once

struct Vector2;
struct Vector4;

struct Vector3 
{
    // Data members
    float x, y, z;

    // Constructors
    Vector3();
    Vector3(float x, float y, float z);

    // Vector operations
    const Vector3 operator+(const Vector3 &other);
    const Vector3 operator-(const Vector3 &other);
    const Vector3 operator*(float scalar);
    const Vector3 operator/(float scalar);

    const float dot(const Vector3 &other);
    const Vector3 cross(const Vector3 &other);

    const float length();
    const Vector3 normalize();

    // Add and remove dimension for homogeneous coordinates
    Vector4 addDim();
    Vector2 removeDim();
};
