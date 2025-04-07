#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include "DataTypes/Throw.h"

class FSExtention 
{
public:
    virtual bool LoadFile(std::string location) = 0;
    virtual bool WriteFile(std::string location) = 0;
    
};

