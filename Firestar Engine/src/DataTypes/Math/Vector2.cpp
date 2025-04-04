#include "DataTypes/Math/Vector2.h"
#include <fmt/base.h>

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::Magnitude() const {
    return std::sqrt(x*x + y*y);
}

float Vector2::MagnitudeSquared() const {
    return x*x + y*y;
}

Vector2 Vector2::Normalised() const {
    float len = Magnitude();
    return (len != 0.0f) ? Vector2(x / len, y/len) : Vector2(0, 0);
}

void Vector2::Normalise() {
    float len = Magnitude();
    if(len != 0.0f) {
        x /= len;
        y /= len;
    }
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return (scalar != 0.0f) ? Vector2(x / scalar, y / scalar) : Vector2(0, 0);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

float Vector2::Dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

float Vector2::Cross(const Vector2& other) const {
    return x * other.y + y * other.x;
}

void Vector2::Print() const{
    fmt::print("Vector3({}, {})\n", x, y);
}