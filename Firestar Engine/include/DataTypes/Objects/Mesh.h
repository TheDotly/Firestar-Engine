#pragma once
#include <vector>
#include "DataTypes/Math/Vector.h"

typedef struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoords;

    Vertex(Vector3 position, Vector3 normal, Vector2 textCoords) : position(position), normal(normal), texCoords(textCoords){} 
} Vertex;

class Mesh
{
private:
    std::vector<Vertex> v_Vertices;
    std::vector<uint32_t> v_Indices;
public:
    Mesh(const std::vector<Vertex>& verticies, const std::vector<uint32_t>& indices);

    const std::vector<Vertex>& getVertices() const {return v_Vertices;}
    const std::vector<uint32_t>& getIndices() const {return v_Indices;} 

    std::vector<float> toFloatArray() const;
};
