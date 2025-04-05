#pragma once

#include <cmath>

class Vector2 {
    public:
    float x, y;

    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2 &other);

    float Magnitude() const;
    float MagnitudeSquared() const;
    Vector2 Normalised() const;
    void Normalise();
    float Dot(const Vector2& other) const;
    float Cross(const Vector2& other) const;

    //Operator Overloading
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);
    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    void Print() const;
};