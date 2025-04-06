#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include "DataTypes/Objects/Texture.h"
#include "DataTypes/Throw.h"

class FileHandler
{
private:
    /* data */
public:
    static bool FileExists(const std::string& filePath);

    static std::string GetExtention(const std::string& filePath);
    
    static bool LoadImage(const std::string& filePath, Texture& out, int desiredChannels = 4);
};

