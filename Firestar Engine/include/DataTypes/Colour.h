#pragma once

#include <string>

class Colour
{
private:
    int r,g,b,a;
public:
    Colour(int r, int b, int g);
    Colour(int r, int b, int g, int a);
    Colour(const std::string& hex);

    //Getters
    int getRed(){
        return r;
    }

    int getGreen() {
        return g;
    }

    int getBlue() {
        return b;
    }

    int getAlpha() {
        return a;
    }
    ~Colour();
};