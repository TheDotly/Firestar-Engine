#include "FirestarEngine.h"

int main(int argc, char* argv[]) {
    FirestarEngine* engine = FirestarEngine::getInstance();

    // We have true here because the editor should always be in debug mode
    // even in release
    GameInfo* gameInfo = new GameInfo("Firestar Editor", true);

    engine->setGameInfo(gameInfo);

    engine->Initialise();
}