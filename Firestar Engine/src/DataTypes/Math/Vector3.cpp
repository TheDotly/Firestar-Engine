#include "DataTypes/Math/Vector3.h"

#include <fmt/base.h>

// ADD SSE and AVX Support to speed up timeing


Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {}

Vector3::Vector3(Vector3 &other): x(other.x), y(other.y), z(other.z) {}

float Vector3::Magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::MagnitudeSquared() const {
    return x * x + y * y + z * z;
}

Vector3 Vector3::Normalised() const {
    float length = Magnitude();
    return (length != 0) ? Vector3(x / length, y / length, z / length) : Vector3();
}

void Vector3::Normalise() {
    float length = Magnitude();
    if(length != 0) {
        x /= length;
        y /= length;
        z /= length;
    }
}

float Vector3::Dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const {
    return Vector3 (
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// Subtraction
Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// Scalar multiplication
Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// Scalar division
Vector3 Vector3::operator/(float scalar) const {
    return (scalar != 0) ? Vector3(x / scalar, y / scalar, z / scalar) : Vector3();
}

Vector3 Vector3::operator+=(const Vector3& other) {
    x += other.x; y += other.y; z += other.z;
    return *this;
}
Vector3 Vector3::operator-=(const Vector3& other){
    x -= other.x; y -= other.y; z -= other.z;
    return *this;
}
Vector3 Vector3::operator*=(float scalar) {
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
}
Vector3 Vector3::operator/=(float scalar){
    if (scalar != 0) {
        x /= scalar; y /= scalar; z /= scalar;
    }
    return *this;
}


bool Vector3::operator==(const Vector3& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}

bool Vector3::operator!=(const Vector3& other) const {
    return !(*this == other);
}

void Vector3::Print() const {
    fmt::print("Vector3({},{},{})\n", x, y, z);
}