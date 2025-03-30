#include "Renderer/RenderFactory.h"
#include "Debug/Debug.h"

#include <SDL3/SDL.h>

//Renderers
#include "Renderer/Vulkan/VulkanRenderer.h"

RenderFactory::RenderFactory(RenderAPI api){

    fmt::print(fg(fmt::color::ivory), "Selected Render API: ");
    v_api = api;
    switch (api)
    {
    case RenderAPI::Vulkan:
    fmt::print(fg(fmt::rgb(199,37,39)), "Vulkan\n");
    s_renderer = new VulkanRenderer();
    break;

    default:
        break;
    }
}

Throw* RenderFactory::Initialise(GameInfo* info){
    return s_renderer->Initialise(info);
}

uint64_t RenderFactory::getWindowFlags() {
    switch (v_api)
    {
    case RenderAPI::Vulkan: 
        return SDL_WINDOW_VULKAN;
    default:
        return 0;
    }
}

RenderFactory::~RenderFactory() {
}