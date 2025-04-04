#pragma once
#include <stdint.h>

class Component
{
private:
    bool active;

public:
    virtual ~Component() = default;
    
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Shutdown();
    virtual bool isActive() const {return active;}
    virtual void setActive(bool active) { this->active = active;
        if(active) {
            Start();
        } else {
            Shutdown();
        }
    }
};
