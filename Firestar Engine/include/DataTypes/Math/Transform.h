#pragma once

#include <cmath>
#include "DataTypes/Math/Vector3.h"

class Transform
{
public:
    Vector3 position;
    Vector3 rotation; // Euler angles Could be Quaternions
    Vector3 scale;

    Transform() : position(0, 0, 0), rotation(0 , 0, 0), scale(1, 1, 1) {}
    Transform(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale) {}

    void Translate(const Vector3& delta);

    void Rotate(const Vector3& delta);

    void Scale(const Vector3& factor);
    
    void Print() const ;
};

