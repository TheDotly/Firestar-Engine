#include "Window/Window.h"

#include "FirestarEngine.h"
#include "Debug/Debug.h"



Window::Window() {

}

bool Window::Initialise() {
    FirestarEngine* engine = FirestarEngine::getInstance();
    GameInfo* info = engine->getGameInfo();
    
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        v_error = fmt::format("ERROR: SDL Failed to Initalise: {}\n", SDL_GetError());
        return false;
    }

    v_window = SDL_CreateWindow(info->getTitle().c_str(), 800, 600,  SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if(v_window == nullptr){
        v_error = fmt::format("ERROR: SDL window Failed to Initialise: {}\n", SDL_GetError());
        return false;
    }

    //SDL_Delay(3000);
    
    return true;
}

std::string Window::getError() {
    return v_error;
}

Window::~Window() {
    SDL_DestroyWindow(v_window);

    SDL_Quit();
}