#include "FirestarEngine.h"

#include "Debug/Debug.h"

#define C_FSE_RED fg(fmt::rgb(250,47,47))

#define FSE_LOGO "███████ ██ ██████  ███████ ███████ ████████  █████  ██████      ██████  ██████\n██      ██ ██   ██ ██      ██         ██    ██   ██ ██   ██          ██ ██   ██\n█████   ██ ██████  █████   ███████    ██    ███████ ██████       █████  ██   ██\n██      ██ ██   ██ ██           ██    ██    ██   ██ ██   ██          ██ ██   ██ \n██      ██ ██   ██ ███████ ███████    ██    ██   ██ ██   ██     ██████  ██████\n"                                                                     

// Engine Info
#define ENGINE_VER "0.0.1"
#define ENGINE_COPY "Joshua Gessner 2025"

static FirestarEngine* instance = nullptr;

FirestarEngine::FirestarEngine() {
    fmt::print(C_FSE_RED, FSE_LOGO);
    fmt::print(C_FSE_RED, "---------------------------\n");
    fmt::print(C_FSE_RED, "Version: {}\n", ENGINE_VER);
    fmt::print(C_FSE_RED, "Copyright: {}\n", ENGINE_COPY);
}

void FirestarEngine::Initialise(){
    Throw* error = nullptr;
    fmt::print(C_FSE_RED, "Starting Systems\n");

    s_renderFactory = new RenderFactory(OpenGl);
    s_mainWindow = new Window();

    fmt::print(fg(fmt::color::ivory), "Window: ");
    error = s_mainWindow->Initialise();
    Throw::Check(error);
    fmt::print(fg(fmt::color::green_yellow), "✔\n");
    


    fmt::print(fg(fmt::color::ivory), "Renderer: ");
    error = s_renderFactory->Initialise(i_gameInfo);

    Throw::Check(error);
    fmt::print(fg(fmt::color::green_yellow), "✔\n");

}

void FirestarEngine::StartLoop(){
    bool running = true;
    while (running)
    {
        s_renderFactory->Draw();
    }
    
}

FirestarEngine* FirestarEngine::getInstance(){
    if(instance == nullptr){
        instance = new FirestarEngine();
    }

    return instance;
}

void FirestarEngine::setGameInfo(GameInfo* gameInfo){
    i_gameInfo = gameInfo;
}

GameInfo* FirestarEngine::getGameInfo() {
    return i_gameInfo;
}

RenderFactory* FirestarEngine::getRenderFactory(){
    return s_renderFactory;
}

Window* FirestarEngine::getMainWindow(){
    return s_mainWindow;
}

FirestarEngine::~FirestarEngine(){

}

Platform FirestarEngine::GetPlatform() {
    #ifdef _WIN32
    return WINDOWS;
    #elif UNIX:
        #ifdef APPLE:
            return MACOS;
        #else 
            return LINUX;
        #endif
    #endif
}