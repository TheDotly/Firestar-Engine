#include "DataTypes/Math/Transform.h"
#include <fmt/base.h>

void Transform::Translate(const Vector3& delta){
    position = position + delta;
}

void Transform::Rotate(const Vector3& delta){
    rotation = rotation + delta;
}

void Transform::Scale(const Vector3& factor){
    scale.x *= factor.x;
    scale.y *= factor.y;
    scale.z *= factor.z;
}

void Transform::Print() const {
    fmt::print("Transform: \nPosition ({}, {}, {})  \nRotation ({}, {}, {}) \nScale ({}, {}, {}) \n", position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z);
}