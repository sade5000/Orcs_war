#include "player.h"
    // TTF_Font* static_FONT = NULL;
    //  SDL_Surface* static_SURFACE = NULL;
    // SDL_Texture* static_Texture = NULL;
    //SDL_Rect text_rect = {0,0,0,0};



show_text::show_text(std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render,int w , int h)
{
    loadText(static_input_TEXT.c_str(),text_COLOR,render);
    SDL_QueryTexture(static_Texture,NULL,NULL,&w,&h);
    //constructor
}

void show_text::text_Renderer(SDL_Renderer* render)
{
    text_rect = {50,100,300,40};
    SDL_RenderCopy(render,static_Texture,NULL,&text_rect);
}

SDL_Texture* show_text::loadText(std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render)
{
    static_FONT = TTF_OpenFont("ArialTh.ttf" , 80);
    if(!static_FONT)
    {
        std::cout << "Fail to initiate Font on static text %s " << SDL_GetError()<< std::endl;
    }
    static_SURFACE = TTF_RenderText_Solid(static_FONT,static_input_TEXT.c_str(),text_COLOR);
    if(!static_SURFACE)
    {
        std::cout << "Fail to initiate Surface on static text %s" << SDL_GetError() << std::endl;
    }
    static_Texture = SDL_CreateTextureFromSurface(render,static_SURFACE);
    if(!static_SURFACE)
    {
        std::cout << "Fail to create Texture form Surface on static text %s " << SDL_GetError()<<std::endl;
    }
    return static_Texture;

}

show_text::~show_text()
{
    TTF_CloseFont(static_FONT);
    SDL_FreeSurface(static_SURFACE);
    SDL_DestroyTexture(static_Texture);
}
