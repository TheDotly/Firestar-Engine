#pragma once

class Material
{
private:
    bool transparent = false;
    bool emissive = false;
public:
    Material(/* args */);

    bool hasTransparency() const { return transparent;}
    bool isEmissive() const {return emissive;}
    ~Material();
};