#include "Renderer/OpenGl/OpenGlRenderer.h"

OpenGlRenderer::OpenGlRenderer(FirestarEngine* engine){
   s_engine = engine;
}

Throw* OpenGlRenderer::Initialise(GameInfo *info){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Throw* error = s_engine->getMainWindow()->CreateWindow(*info, OpenGl);
    if(!Throw::Check(error)){
       
        return error;
    }

    v_window = s_engine->getMainWindow()->getWindow();

    v_glContex = SDL_GL_CreateContext(v_window->window);
    if(!v_glContex) {
        
        return Throw::ExitError("Failed to Create OpenGL Context");
    }

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        return Throw::ExitError("Failed to Init GLAD");
    }

    // VSYNC SHOULD ADD Effect
    SDL_GL_SetSwapInterval(1);
    return nullptr;
}

void OpenGlRenderer::Draw() {
    



    Clear();
    SDL_GL_SwapWindow(v_window->window);
}

void OpenGlRenderer::Clear() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::Shutdown() {

}

std::string OpenGlRenderer::GetError() {
    return "";
}

OpenGlRenderer::~OpenGlRenderer(){
    SDL_GL_DestroyContext(v_glContex);
}