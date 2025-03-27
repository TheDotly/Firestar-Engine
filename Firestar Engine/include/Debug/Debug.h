#pragma once
#include <iostream>
#include "DataTypes/Colour.h"

static class Debug
{
private:
public:
    template <typename first, typename... Args>
    static void println(const first &t, Args... args){
        println(t);
        println(args...);
    }

    template <typename first>
    static void println(const first &t){
        std::cout << t << " ";
    }

};
