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

//Slate
#include "Slate/Slate.h"

//File System
#include "filesystem/FileHandler.h"

#include <memory>

typedef enum {
    WINDOWS,
    MACOS,
    LINUX
} Platform;

class FirestarEngine
{
private:
    FirestarEngine();

    // Game Information
    GameInfo* i_gameInfo = nullptr;

    // Game Systems
    RenderFactory* s_renderFactory = nullptr;
    Window* s_mainWindow = nullptr;
    
    Slate* s_currentSlate = nullptr;
public:
    static FirestarEngine* getInstance();

    void Initialise();
    void StartLoop();


    void setGameInfo(GameInfo* info);
    GameInfo* getGameInfo();
    // System Getters
    RenderFactory* getRenderFactory();
    Window* getMainWindow();
    ~FirestarEngine();

    static Platform GetPlatform();

    // Slate
    Slate* getCurrentSlate();
    void setCurrentSlate(Slate* slate);
};  