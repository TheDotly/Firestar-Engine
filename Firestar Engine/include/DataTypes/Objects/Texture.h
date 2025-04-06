#pragma once

#include <vector>
#include <string>

class Texture
{
private:
    int width = 0;
    int height = 0;
    int channels = 0;
    
    std::vector<unsigned char> pixels;
    std::string filePath = "";

public:

void SetValues(int w, int h, int ch, unsigned char* data, std::string path){
    width = w;
    height = h;
    channels = ch;
    pixels.assign(data, data + w * h * ch);
    filePath = path;
}


bool isValid() const {
    return !pixels.empty();
}

int getWidth() const {
    return width;
}

int getHeight() const {
    return height;
}

int getChannels() const {
    return channels;
}

std::vector<unsigned char> getPixels() {
    return pixels;
}

std::string getFilePath() {
    return filePath;
}
};
