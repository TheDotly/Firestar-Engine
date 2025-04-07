#include "FileSystem/FileHandler.h"

bool FileHandler::FileExists(const std::string& filePath){
    return std::filesystem::exists(std::filesystem::path(filePath));
}

std::string FileHandler::GetExtention(const std::string& filePath){
    return std::filesystem::path(filePath).extension().string();
}

// SHOULD MAKE MULTITHREADED TO IMPROVE SPEED
bool FileHandler::LoadFileEXT(const std::string& filePath, FSExtention* extention){
    if(!FileExists(filePath)){
        Throw::Warning("[FileHandler] File not Found: " + filePath)->Print();
        return false;
    }

    return extention->LoadFile(filePath);
}