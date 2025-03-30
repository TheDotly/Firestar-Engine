#pragma once

#include <SDL3/SDL.h>
#include <string>



class Window
{
private:
    SDL_Window* v_window = nullptr;
    std::string v_error = "";
public:
    Window();
    bool Initialise();
    std::string getError();
    ~Window();
};


