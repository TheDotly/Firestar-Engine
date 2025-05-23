#pragma once
#include <string>

#ifdef _DEBUG
    #define DEBUG_MODE true
#else
    #define DEBUG_MODE false
#endif

// v_ stands for value this notion is only for data classes


class GameInfo
{
private:
    std::string v_title = "Firestar Game";
    // standard if debug is setup or not
    bool v_debug = DEBUG_MODE;

    int v_width = 800;
    int v_height = 600;
public:
    /// @brief Information about the Game
    /// @param title Title of the Game and what will Apear in the Bar (WILL BE USED FOR COMPILE NAME)
    GameInfo(std::string title, int width, int height);

    /// @brief Information about the Game
    /// @param title Title of the Game and what will Apear in the Bar (WILL BE USED FOR COMPILE NAME)
    /// @param debug This Enables Debug Features such as Debug Printing even in release mode
    GameInfo(std::string title, int width, int height, bool debug);

    std::string getTitle();
    int getWidth();
    int getHeight();
};
