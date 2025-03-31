#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "DataTypes/Throw.h"
#include "DataTypes/GameInfo.h"

#include "Renderer/RenderFactory.h"

typedef struct {
    SDL_Window* window;
} FSE_Window;


class Window
{
private:
    FSE_Window* v_window = nullptr;
public:
    Window();
    Throw* Initialise();
    Throw* CreateWindow(GameInfo info, RenderAPI api);
    ~Window();

    FSE_Window* getWindow();
};


