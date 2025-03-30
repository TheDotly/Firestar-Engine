#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "DataTypes/Throw.h"


class Window
{
private:
    SDL_Window* v_window = nullptr;
public:
    Window();
    Throw* Initialise();
    ~Window();
};


