#pragma once

#include <vector>
#include "Object System/Components/MeshComponent.h"

// THIS ECS SYSTEM IS ONLY FOR FAST Render and processing that are devoid from layout
// use hiracy for scripts
class ECSystem
{

public:
    std::vector<MeshComponent *> allMeshsComponents;
    ECSystem(/* args */) = default;
    void addMeshComponent(MeshComponent* component);
    void removeMeshComponent(MeshComponent* component);
    ~ECSystem();
};
