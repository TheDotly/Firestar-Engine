#include "FirestarEngine.h"
#include <windows.h>


int main(int argc, char* argv[]) {
    FirestarEngine* engine = FirestarEngine::getInstance();

    // We have true here because the editor should always be in debug mode
    // even in release
    GameInfo* gameInfo = new GameInfo("Firestar Editor", 800, 600, true);
    Slate* slate = new Slate();

    engine->setGameInfo(gameInfo);
    FSImage* image = new FSImage();
    if(FileHandler::LoadFileEXT("C:/Users/joshu/OneDrive/Desktop/Game Engine SDK/Firestar-Engine/dotly.png", image)){
        printf("LOADED IMAGE");
    }

    Texture* tex = image->getTexture();
    

    engine->Initialise();
    engine->StartLoop();
}