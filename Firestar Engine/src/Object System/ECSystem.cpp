#include "Object System/ECSystem.h"
#include <stdint.h>

void ECSystem::addMeshComponent(MeshComponent* component){
    allMeshsComponents.push_back(component);
}

void ECSystem::removeMeshComponent(MeshComponent* component){
    auto it = std::find(allMeshsComponents.begin(), allMeshsComponents.end(), component);
    if(it != allMeshsComponents.end()){
        allMeshsComponents.erase(it);
    }
}