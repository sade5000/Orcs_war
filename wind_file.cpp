#include "wind_file.h"
//window and renderer function
WindAndRend::WindAndRend(const char* title , int p_width , int p_heigth)
{
    main_window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_width,p_heigth,SDL_WINDOW_SHOWN);
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

SDL_Texture* WindAndRend::load_Texure(const char* p_texture)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(main_render,p_texture);
    if(texture == NULL)
    {
        std::cout<<"Fail to load texture "<<SDL_GetError()<<std::endl;
    }
    return texture;
}

SDL_Renderer* WindAndRend::GetRenderer()
{
    return main_render;
}
SDL_Window* WindAndRend::GetWindow()
{
    return main_window;
}
void WindAndRend::clear_scr()
{
    SDL_RenderClear(main_render);
}
///////RENDER COPY OF LEVEL GROUND////////
void WindAndRend::render(class Objects& obj)
{
    SDL_Rect src;
    src.x = obj.GetZeroP().x;
    src.y = obj.GetZeroP().y;
    src.w = obj.GetZeroP().w;
    src.h = obj.GetZeroP().h;
    SDL_Rect dst;
    dst.x = obj.GetX();
    dst.y = obj.GetY();
    dst.w = obj.GetZeroP().w;
    dst.h = obj.GetZeroP().h;
    SDL_RenderCopy(main_render,obj.GetTexture(),&src,&dst);
}
void WindAndRend::display()
{
    SDL_RenderPresent(main_render);
}
void WindAndRend::sky(SDL_Renderer* render , Uint8 R , Uint8 G , Uint8 B , Uint8 A)
{
    skyR.w = 800;
    skyR.h = 600;
    SDL_SetRenderDrawColor(render,R,G,B,A );
    SDL_RenderFillRect(render,&skyR);
    //SDL_GetRenderDrawColor(0,0,0,0);
}
int WindAndRend::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex( main_window );
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex,0,&mode);
    return mode.refresh_rate;
}

SDL_Texture* WindAndRend::load_Plane(const char* p_texture)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(main_render,p_texture);
    if(texture == NULL)
    {
        std::cout<<"Fail to load texture "<<SDL_GetError()<<std::endl;
    }
    return texture;
}

void WindAndRend::render_plr(SDL_Texture* texture,float Xpos,float Ypos)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 30;
    src.w = 100;
    src.h = 100;
    /////////////////////////////////////////////
    SDL_Rect dst;
    dst.x = Xpos;
    dst.y = 450;
    dst.w = 100.0;
    dst.h = 50;
    SDL_RenderCopy(main_render,texture,&src,&dst);
}
/////RENDER COPY OF PLANE OBJ///////////
//// class player_render start here







