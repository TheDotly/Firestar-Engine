#include "FileSystem/FileHandler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"

bool FileHandler::FileExists(const std::string& filePath){
    return std::filesystem::exists(std::filesystem::path(filePath));
}

std::string FileHandler::GetExtention(const std::string& filePath){
    return std::filesystem::path(filePath).extension().string();
}


bool FileHandler::LoadImage(const std::string& filePath, Texture& out, int desiredChannels){
    if(!FileExists(filePath)){
        Throw::Warning("[FileHandler] Image File not Found: " + filePath)->Print();
        return false;
    }

    int w, h, ch;
    unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &ch, desiredChannels);
    if(!data){
        Throw::Warning("[FileHandler] Failed to Load Image: " + filePath)->Print();
        return false;
    }

    out.SetValues(w, h, ch, data, filePath);

    stbi_image_free(data);
    return true;
}