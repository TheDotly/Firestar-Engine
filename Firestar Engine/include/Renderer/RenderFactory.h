#pragma once
#include "Renderer/IRenderer.h"

enum RenderAPI {
    Vulkan,
    OpenGl
};

class RenderFactory
{
public:
    RenderFactory(enum RenderAPI api);
    ~RenderFactory();

    /// @brief Will Return flags Required by the renderer for window creation
    /// @return FLAGS
    uint64_t getWindowFlags();

    /// @brief Initialise The Renderer 
    /// @return if Renderer Started
    Throw* Initialise(GameInfo* info);

    void Draw();
    void Clear();
    
    std::string getError() { return s_renderer->GetError();}
private:
    enum RenderAPI v_api;
    IRenderer* s_renderer = nullptr;
};
