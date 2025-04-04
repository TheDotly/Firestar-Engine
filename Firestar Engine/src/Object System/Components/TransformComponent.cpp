#include "Object System/Components/TransformComponent.h"

void TransformComponent::translate(const Vector3& translation){
    position = position + translation;
}

void TransformComponent::rotate(const Vector3& deltaRotation){
    rotation.x += deltaRotation.x;
    rotation.y += deltaRotation.y;
    rotation.z += deltaRotation.z;
}

void TransformComponent::scaleObject(const Vector3& scalingFactor){
    scale.x = scale.x * scalingFactor.x;
    scale.y = scale.y * scalingFactor.y;
    scale.z = scale.z * scalingFactor.z;
}