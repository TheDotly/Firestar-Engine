#include "Window/Window.h"

#include "FirestarEngine.h"
#include "Debug/Debug.h"


Window::Window() {

}

Throw* Window::Initialise() {

    
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        return Throw::ExitError(fmt::format("ERROR: SDL Failed to Initalise: {}\n", SDL_GetError()));
    }

    //SDL_Delay(3000);
    
    return nullptr;
}

Throw* Window::CreateWindow(GameInfo info, RenderAPI api) {
    SDL_WindowFlags flags = 0;

    switch (api)
    {
    case RenderAPI::Vulkan:
        flags |= SDL_WINDOW_VULKAN;
        break;
    case RenderAPI::OpenGl:
        flags |= SDL_WINDOW_OPENGL;
        break;
    default:
        break;
    }

    v_window = new FSE_Window{SDL_CreateWindow(info.getTitle().c_str(), info.getWidth(), info.getHeight(), flags | SDL_WINDOW_HIGH_PIXEL_DENSITY)};

    if(v_window == nullptr){
        return Throw::ExitError(fmt::format("ERROR: SDL window Failed to Initialise: {}\n", SDL_GetError()));
    }

    return nullptr;
}

Window::~Window() {
    SDL_DestroyWindow(v_window->window);

    SDL_Quit();
}

FSE_Window* Window::getWindow(){
    return v_window;
}