#pragma once
#include "Game_libs.h"
#include "obj_file.h"
#include "player.h"
class WindAndRend
{
    private:
        SDL_Window *main_window = nullptr;
        SDL_Renderer* main_render = nullptr;
        SDL_Rect skyR ={0,0,0,0};
        SDL_Event event;//if needed
    public:
        WindAndRend(const char* title , int p_width , int p_heigth);
        void CleanUP();
        SDL_Texture* load_Texure(const char* p_texture);
        SDL_Renderer* GetRenderer();
        SDL_Window* GetWindow();
        void clear_scr();
        void render(class Objects& obj);
        void display();
        void sky(SDL_Renderer* render , Uint8 R , Uint8 G , Uint8 B , Uint8 A);
        int getRefreshRate();
        SDL_Texture* load_Plane(const char* p_texture);
        void render_plr(SDL_Texture* texture,float Xpos);

};


