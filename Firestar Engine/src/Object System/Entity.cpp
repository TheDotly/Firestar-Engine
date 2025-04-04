#include "Object System/Entity.h"


void Entity::addComponent(Component* component){
    uint32_t order = components.size();

    addComponent(component, order);
}


void Entity::addComponent(Component* component, uint32_t order){
    auto it = std::find(components.begin(), components.end(), component);

    if(it != components.end()) {
        components.erase(it);
    }

    components.insert(components.begin() + order, component);
}

void Entity::Update(float deltaTime){
    for(Component* component : components){
        if(component->isActive()){
            component->Update(deltaTime);
        }
    }

    for(Entity* child : children){
        child->Update(deltaTime);
    }
}

void Entity::Start(){
    for(Component* component : components){
        if(component->isActive()){
            component->Start();
        }
    }

    for(Entity* child : children){
        child->Start();
    }
}

void Entity::Shutdown() {
    for(Component* component : components){
        if(component->isActive()){
            component->Shutdown();
        }
    }

    for(Entity* child : children){
        child->Shutdown();
    }
}

template<typename T>
T* Entity::getComponent(){
    auto it = components.find(typeid(T));
    if(it != components.end()){
        return static_cast<T*>(it);
    }
}

void Entity::addChild(Entity* child){
    uint32_t order = children.size();
    addChild(child, order);
}

void Entity::addChild(Entity* child, uint32_t order){
    auto it = std::find(children.begin(), children.end(), child);

    if(it != children.end()){
        children.erase(it);
    }

    child->parent = this;

    children.insert(children.begin() + order, child);

}