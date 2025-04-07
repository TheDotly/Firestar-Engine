#pragma once

#include "FileSystem/Object Extention/FSExtention.h"

#include "DataTypes/Objects/Texture.h"

class FSImage : public FSExtention
{
private:
    Texture* tex;
    int desiredChannels = 0;
public:
    FSImage(int desiredChannels = 4);
    ~FSImage();

    bool LoadFile(std::string location) override;
    bool WriteFile(std::string location) override;

    Texture* getTexture();
};
