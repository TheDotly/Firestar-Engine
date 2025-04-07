#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include "DataTypes/Throw.h"


// File Extentions
#include "FileSystem/Object Extention/FSExtention.h"
#include "FileSystem/Object Extention/FSImage.h"
#include "FileSystem/Object Extention/FSObject.h"

class FileHandler
{
private:
    /* data */
public:
    static bool FileExists(const std::string& filePath);

    static std::string GetExtention(const std::string& filePath);

    static bool LoadFileEXT(const std::string& filePath, FSExtention* extention);

    
};

