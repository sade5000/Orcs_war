#pragma once
#include "Game_libs.h"

class WindAndRend
{
    private:
        SDL_Window *main_window = nullptr;
        SDL_Renderer* main_render = nullptr;

    public:
        WindAndRend(const char* title , int p_width , int p_heigth);
        void CleanUP();
};
