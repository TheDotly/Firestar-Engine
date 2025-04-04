#pragma once

#include "Object System/Component.h"

#include "DataTypes/Objects/Mesh.h"
#include "DataTypes/Objects/Material.h"

class MeshComponent : Component
{
private:
    Mesh* mesh = nullptr;
    Material* material = nullptr;
public:
    MeshComponent() = default;
    
    MeshComponent(Mesh* mesh, Material* material): mesh(mesh), material(material) {};

    void setMesh(Mesh* mesh) {this->mesh = mesh;}
    Mesh* getMesh() {return mesh;}

    void setMaterial(Material* material) {this->material = material;}
    Material* getMaterial() {return material;}
};

