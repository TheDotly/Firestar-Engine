#include "DataTypes/GameInfo.h"

GameInfo::GameInfo(std::string title, int width, int height){
    v_title = title;
    v_width = width;
    v_height = height;
}

GameInfo::GameInfo(std::string title, int width, int height,bool debug) {
    v_debug = debug;
    v_title = title;
    v_width = width;
    v_height = height;
}

std::string GameInfo::getTitle(){
    return v_title;
}

int GameInfo::getWidth() {
    return v_width;
} 

int GameInfo::getHeight(){
    return v_height;
}