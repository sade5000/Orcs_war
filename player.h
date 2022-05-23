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
    SDL_Rect text_rect = {0,0,0,0};//Text render rect
    SDL_Point* frame_Design = NULL;

    public:

    show_text(const char* font_type,int font_size,std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render,int w , int h);///Constructor text
    void text_Renderer(SDL_Renderer* render,int X , int Y,int w , int h);///Render text function
    SDL_Texture* loadText(const char* font_type,int font_size,std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render);///Load Texture Function
    ~show_text();

};

class player_collision : public player
{
    private:
        int ms_pos_X = 0;
        int ms_pos_Y = 0;
        mutable SDL_Rect Collision_a1 = {0,0,0,0};
        bool collision_flag = false;

    public:
        player_collision(int ax,int ay , int aw , int ah);//Collision constructor
        void button_rect(SDL_Renderer* render , Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha);//draw a rect at constructor coordonates
        int mouse_state(SDL_Event event);//Get mouse pos on XY ax -- Gets constructor coordonates
        void button_frame( SDL_Renderer* render , Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha,int ax,int ay,int bx,int by, int cx , int cy , int dx , int dy,int ex, int ey);//draw a frame to your button
        bool Get_Collision_flag();
};

class menu_on :public player_collision
{

    private:

        bool START = false;

    public:

        void start_game(SDL_Event event);
        bool GetSTART();

};
