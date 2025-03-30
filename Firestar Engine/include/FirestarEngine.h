#pragma once
/*
    Joshua Gessner
    variable naming convention
    all enigne systems will be prfixed with s_ 
    all information object and storage types are prefixed with i_

    this keeps a clean seperations
    furthermore im using cammelCase for variables and for getters and setters




*/
//Firestar Subsystems
#include "Renderer/RenderFactory.h"
#include "Window/Window.h"

// DataTypes
#include "DataTypes/GameInfo.h"

#include <memory>

class FirestarEngine
{
private:
    FirestarEngine();

    // Game Information
    GameInfo* i_gameInfo = nullptr;

    // Game Systems
    RenderFactory* s_renderFactory = nullptr;
    Window* s_mainWindow = nullptr;
    

public:
    static FirestarEngine* getInstance();

    void Initialise();


    void setGameInfo(GameInfo* info);
    GameInfo* getGameInfo();
    RenderFactory* getRenderFactory();
    ~FirestarEngine();

};