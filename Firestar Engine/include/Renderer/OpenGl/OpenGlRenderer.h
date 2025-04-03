#pragma once
#include "Renderer/IRenderer.h"
#include "DataTypes/GameInfo.h"
#include "DataTypes/Throw.h"
#include "glad/glad.h"
#include <SDL3/SDL.h>
#include "FirestarEngine.h"

//OpenGl
class OpenGlRenderer : public IRenderer
{
public:
    OpenGlRenderer(FirestarEngine* engine);
    Throw* Initialise(GameInfo *info) override;
    void Draw() override;
    void Clear() override;
    void Shutdown() override;
    std::string GetError() override;
    ~OpenGlRenderer();
private:
    std::string v_error = ""; 
    SDL_GLContext v_glContex;
    FSE_Window* v_window;
    FirestarEngine* s_engine;
};
