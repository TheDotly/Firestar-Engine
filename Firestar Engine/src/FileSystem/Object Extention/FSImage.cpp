#include "FileSystem/Object Extention/FSImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"


FSImage::FSImage(int desiredChannels) {
    this->desiredChannels = desiredChannels;
}

bool FSImage::LoadFile(std::string location) {
    this->tex = new Texture();

    int w, h, ch;
    unsigned char* data = stbi_load(location.c_str(), &w, &h, &ch, desiredChannels);
    if(!data){
        Throw::Warning("[FileHandler] Failed to Load Image: " + location)->Print();
        return false;
    }

    this->tex->SetValues(w, h, ch, data, location);

    stbi_image_free(data);
    return true;
}

bool FSImage::WriteFile(std::string location){
    return true;
}

Texture* FSImage::getTexture(){
    if(tex != nullptr){
        return tex;
    }

    return new Texture();
}