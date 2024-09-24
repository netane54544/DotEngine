#pragma once

struct Vector3;

struct Vector4 
{
    float x, y, z, h;

    Vector4();
    Vector4(float x, float y, float z, float h);

    // Vector operations
    Vector4 operator+(const Vector4 &other);
    Vector4 operator-(const Vector4 &other);
    Vector4 operator*(float scalar);
    Vector4 operator/(float scalar);

    float dot(const Vector4 &other);
    float length();
    Vector4 normalize();

    // Remove dimension for homogeneous coordinates
    Vector3 removeDim();
};
