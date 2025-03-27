#include "DataTypes/Colour.h"
#include <iostream>
#include <sstream>

int hexToDecimal(const std::string& hex);

int hexToDecimal(const std::string& hex){
    int decimal;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> decimal;
    return decimal;
}

Colour::Colour(int r, int g, int b){
    this->r = r;
    this->a = g;
    this->b = b;
    this->a = 1;
}

Colour::Colour(int r, int g, int b, int a){
    this->r = r;
    this->a = g;
    this->b = b;
    this->a = a;
}

Colour::Colour(const std::string& hex){
    if(hex[0] == '#'){
        std::string red = hex.substr(1, 2);
        std::string green = hex.substr(3, 2);
        std::string blue = hex.substr(5, 2);
        std::string alpha = hex.substr(7, 2);

        r = hexToDecimal(red);
        g = hexToDecimal(green);
        b = hexToDecimal(blue);
        a = hexToDecimal(alpha);
    }
}

Colour::~Colour() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}