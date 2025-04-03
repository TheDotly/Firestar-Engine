#pragma once

#include <cmath>

class Vector3 {
    public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(Vector3 &other);

    float Magnitude() const;
    float MagnitudeSquared() const;
    Vector3 Normalised() const;
    void Normalise();
    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;

    //Operator Overloading
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator*=(float scalar);
    Vector3 operator/=(float scalar);
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    void Print() const;
};