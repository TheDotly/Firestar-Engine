#include "DataTypes/GameInfo.h"

GameInfo::GameInfo(std::string title){
    v_title = title;
}

GameInfo::GameInfo(std::string title, bool debug) {
    v_debug = debug;
    v_title = title;
}

std::string GameInfo::getTitle(){
    return v_title;
}