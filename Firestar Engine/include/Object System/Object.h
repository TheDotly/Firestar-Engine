#pragma once

#include <string>
#include <vector>

#include "Object System/Components/IComponents.h"

class Object
{
private:
    
public:
    std::string name = "";
    bool isActive = true;
    std::vector<IComponents> components;

    // Functions 
    // - Save to File (including Component states to create prefabs)
    // - Static load from File returns object
    

    Object(std::string name, bool isActive = true, std::vector<IComponents> components);
    Object(std::string name, bool isActive = true);
    
};

