#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <typeindex>

#include "Object System/Component.h"

class Entity
{
private:
    /* data */
public:
    uint32_t id;
    std::string name;
    Entity* parent = nullptr;
    std::vector<Entity*> children;
    std::vector<Component*> components;

    Entity(uint32_t entityId, std::string name) : id(entityId), name(name) {}

    
    void addComponent(Component* component);

    
    void addComponent(Component* component, uint32_t order);

    template<typename T>
    T* getComponent();

    void addChild(Entity* child);
    void addChild(Entity* child, uint32_t order);

    void Start();
    void Update(float deltaTime);
    void Shutdown();
};


