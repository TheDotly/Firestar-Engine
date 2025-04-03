#include "Renderer/RenderFactory.h"
#include "Debug/Debug.h"

#include <SDL3/SDL.h>

//Renderers
#include "Renderer/Vulkan/VulkanRenderer.h"
#include "Renderer/OpenGl/OpenGlRenderer.h"

RenderFactory::RenderFactory(RenderAPI api){

    fmt::print(fg(fmt::color::ivory), "Selected Render API: ");
    FirestarEngine * engine = FirestarEngine::getInstance();
    v_api = api;
    switch (api)
    {
    case RenderAPI::Vulkan:
    fmt::print(fg(fmt::rgb(199,37,39)), "Vulkan\n");
    s_renderer = new VulkanRenderer(engine);
    break;
    case RenderAPI::OpenGl:
    fmt::print(fg(fmt::rgb(85, 133, 163)), "OpenGL\n");
    s_renderer = new OpenGlRenderer(engine);

    default:
        break;
    }
}

Throw* RenderFactory::Initialise(GameInfo* info){
    return s_renderer->Initialise(info);
}

void RenderFactory::Draw(){
    s_renderer->Draw();
}   
void RenderFactory::Clear(){
    s_renderer->Clear();
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