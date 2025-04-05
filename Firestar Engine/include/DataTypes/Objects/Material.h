#pragma once
#include "DataTypes/Objects/Texture.h"
#include <string>
#include <memory>
#include <unordered_map>

class Material
{
public:
    enum class ShadingMode {
        Opaque,
        Transparent,
        Emissive
    };
private:
    std::string name;
    std::shared_ptr<Texture> texture;
    ShadingMode shadingMode;
    float specular;
    float transparancy;
    std::unordered_map<std::string, std::string> customProperties;
public:


    Material(const std::string& name) : name(name), shadingMode(ShadingMode::Opaque), specular(32.0f), transparancy(1.0f) {}

    // bool hasTransparency() const { return transparent;}
    // bool isEmissive() const {return emissive;}
    ~Material();
};