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

    s_renderFactory = new RenderFactory(Vulkan);
    s_mainWindow = new Window();

    fmt::print(fg(fmt::color::ivory), "Window: ");
    if(s_mainWindow->Initialise()){
        fmt::print(fg(fmt::color::green_yellow), "✔\n");
    } else {
        fmt::print(fg(fmt::color::orange_red), "✖\n");
        fmt::print(fg(fmt::color::orange_red), s_mainWindow->getError());
        exit(1);
    }


    fmt::print(fg(fmt::color::ivory), "Renderer: ");
    error = s_renderFactory->Initialise(i_gameInfo);

    if(error == nullptr){
        fmt::print(fg(fmt::color::green_yellow), "✔\n");
    } else {
        fmt::print(fg(fmt::color::orange_red), "✖\n");
        error->Print();
        exit(1);
    }

    while (true)
    {
        /* code */
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

FirestarEngine::~FirestarEngine(){

}