#pragma once
#include "Game_libs.h"
#include "wind_file.h"
class player
{

};
class show_text : public player
{
    private:
    TTF_Font* static_FONT = NULL;
    SDL_Surface* static_SURFACE = NULL;
    SDL_Texture* static_Texture = NULL;
    SDL_Rect text_rect = {0,0,0,0};

    public:

    show_text(std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render,int w , int h);///Constructor text
    void text_Renderer(SDL_Renderer* render);///Render text function
    SDL_Texture* loadText(std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render);///Load Texture Function
    ~show_text();

};
