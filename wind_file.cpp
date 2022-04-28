#include "wind_file.h"
//window and renderer function
WindAndRend::WindAndRend(const char* title , int p_width , int p_heigth)
{
    main_window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_width,p_heigth,SDL_WINDOWEVENT_MAXIMIZED|SDL_WINDOW_SHOWN);
    if(main_window == NULL)
    {
        std::cout<<"Fail to create mainWindow" <<SDL_GetError()<<std::endl;
    }
    main_render = SDL_CreateRenderer(main_window, -1 , SDL_RENDERER_ACCELERATED);
    if(main_render == NULL)
    {
        std::cout<<"Fail to create mainRenderer"<<SDL_GetError()<<std::endl;
    }
}
void WindAndRend::CleanUP()
{
    SDL_DestroyWindow(main_window);
}
