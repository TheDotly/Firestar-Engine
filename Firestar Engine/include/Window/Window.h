#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "DataTypes/Throw.h"
#include "DataTypes/GameInfo.h"

#include "Renderer/RenderFactory.h"


class Window
{
private:
    SDL_Window* v_window = nullptr;
public:
    Window();
    Throw* Initialise();
    Throw* CreateWindow(GameInfo info, RenderAPI api);
    ~Window();
};


