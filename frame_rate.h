#pragma once
#include"Game_libs.h"
////////CONTROL FRAME RATE ////
namespace utils
{
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks64();
        t *= 0.001f;
        return t;
    }
}
