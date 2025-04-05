#include "FirestarEngine.h"

int main(int argc, char* argv[]) {
    FirestarEngine* engine = FirestarEngine::getInstance();

    // We have true here because the editor should always be in debug mode
    // even in release
    GameInfo* gameInfo = new GameInfo("Firestar Editor", 800, 600, true);
    Slate* slate = new Slate();
    
    Entity* cube = new Entity(0, "Cube");
    MeshComponent * meshComp = new MeshComponent();

    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(Vector3(0.0f, 0.5f, 0.0f), Vector3(0,0,0), Vector2(0,0)));
    vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0,0,0), Vector2(0,0)));
    vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0,0,0), Vector2(0,0)));

    std::vector<uint32_t> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    Mesh* mesh = new Mesh(vertices, indices);

    meshComp->setMesh(mesh);

    cube->addComponent((Component*) meshComp);

    slate->addEntity(cube);

    engine->setGameInfo(gameInfo);

    engine->Initialise();
    engine->StartLoop();
}