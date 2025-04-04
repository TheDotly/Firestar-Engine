#pragma once

#include "Object System/Component.h"
#include "DataTypes/Math/Vector.h"

class TransformComponent : Component
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    TransformComponent() : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}
    TransformComponent(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale) {}

    void translate(const Vector3& translation);

    void rotate(const Vector3& deltaRotation);

    void scaleObject(const Vector3& scalingFactor);
};
