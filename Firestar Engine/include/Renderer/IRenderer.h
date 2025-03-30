#pragma once
/*
    Joshua Gessner 2025 -----------------------------------------------------------------

    Standard Interface for the renderer
    if you want to add a renderer you must follow this convention doing this you are able
    to add any renderer you want 

    you also have to add a renderfactory entry
*/

#include <string>
#include "DataTypes/GameInfo.h"
#include "DataTypes/Throw.h"

class IRenderer
{
public:
    /// @brief Initalise the Renderer
    /// @return true if the renderer Sucessfuly was Instantiated
    virtual Throw* Initialise(GameInfo *info) = 0;
    /// @brief Draw to the Screen Surface
    virtual void Draw() = 0;
    /// @brief Clear the Screen Surface
    virtual void Clear() = 0;
    /// @brief Destroy the Renderer and get ready to close
    virtual void Shutdown() = 0;

    /// @brief Get the Error
    /// @return return and error or just blank
    virtual std::string GetError() = 0;
};

