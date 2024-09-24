#pragma once

struct Vector3;

struct Vector2 
{
    // Data members
    float x, y;

    // Constructors
    Vector2();
    Vector2(float x, float y);

    // Vector operations
    Vector2 operator+(const Vector2 &other);
    Vector2 operator-(const Vector2 &other);
    Vector2 operator*(float scalar);
    Vector2 operator/(float scalar);

    float dot(const Vector2 &other);
    float length();
    Vector2 normalize();

    // Add dimension for homogeneous coordinates
    Vector3 addDim();
};
