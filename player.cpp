#include "player.h"

show_text::show_text(const char* font_type,int font_size,std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render,int w , int h)
{
    loadText(font_type,font_size,static_input_TEXT.c_str(),text_COLOR,render);
    SDL_QueryTexture(static_Texture,NULL,NULL,&w,&h);
    //constructor
}

void show_text::text_Renderer(SDL_Renderer* render,int X , int Y, int w , int h)
{
    text_rect = {X,Y,w,h};
    SDL_RenderCopy(render,static_Texture,NULL,&text_rect);
}

SDL_Texture* show_text::loadText(const char* font_type,int font_size,std::string static_input_TEXT,SDL_Color text_COLOR,SDL_Renderer* render)
{
    static_FONT = TTF_OpenFont(font_type , font_size);
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

player_collision::player_collision(int ax, int ay , int aw , int ah)
{
    Collision_a1.x = ax;
    Collision_a1.y = ay;
    Collision_a1.w = aw;
    Collision_a1.h = ah;
    //Constructor
}

void player_collision::button_rect(SDL_Renderer* render , Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha)
{
    Uint8 R = Red;
    Uint8 G = Green;
    Uint8 B = Blue;
    Uint8 A = Alpha;

    ////////////////////////////////////////

    SDL_SetRenderDrawColor(render, R , G , B , A);
    SDL_RenderFillRect(render, &Collision_a1 );

}

int player_collision::mouse_state(SDL_Event event)
{
    if(event.type == SDL_MOUSEMOTION )
    {
    SDL_GetMouseState(&ms_pos_X , &ms_pos_Y);
    /////////////////////////////////////////
    int l1 = ms_pos_X - 1;
    int r1 = ms_pos_X + 1;
    int t1 = ms_pos_Y - 1;
    int b1 = ms_pos_Y + 1;
    ////////////////////////////////////////
    int l2 = Collision_a1.x;
    int r2 = Collision_a1.x + Collision_a1.w;
    int t2 = Collision_a1.y;
    int b2 = Collision_a1.y+Collision_a1.h;
    ////////////////////////////////////////
    std::cout << " x: "<<ms_pos_X<< " Y: "<<ms_pos_Y << std::endl;
        if(!(l1 > r2 || l2 > r1 || t1 > b2 || t2 > b1))
        {
            std::cout << "Collision detected"<<std::endl;
            collision_flag = true;
        }
        else
            collision_flag = false;
    ////////////////////////////////////////
    }
    return ms_pos_X , ms_pos_Y;
}

void player_collision::button_frame(SDL_Renderer* render, Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha,int ax,int ay,int bx,int by, int cx , int cy , int dx , int dy, int ex , int ey)
{

    static SDL_Point points[FRAME_POINT_NO] = {{ax,ay},{bx,by},{cx,cy},{dx,dy},{ex,ey}};
    Uint8 R = Red;
    Uint8 G = Green;
    Uint8 B = Blue;
    Uint8 A = Alpha;
    SDL_SetRenderDrawColor(render, R , G , B , A);
    SDL_RenderDrawLines(render, points, FRAME_POINT_NO);
}



bool player_collision::Get_Collision_flag()
{
    return collision_flag;
}
show_dinamic_text::show_dinamic_text(SDL_Renderer* render,const char* font_path, int font_size,std::string str, SDL_Color Color)
{
    int w = 100; int h = 100;
    //str.append((char)&counter);///transform from int to char
    load_text_texture(render,font_path,font_size,str.c_str(),Color);
    SDL_QueryTexture(dinamic_Texture,NULL,NULL,&w,&h);

}

SDL_Texture* show_dinamic_text::load_text_texture(SDL_Renderer* render,const char* font_path, int font_size,std::string str, SDL_Color Color)
{
    dinamic_FONT = TTF_OpenFont(font_path,font_size);
    dinamic_SURFACE = TTF_RenderText_Solid(dinamic_FONT,str.c_str(),Color);
    dinamic_Texture = SDL_CreateTextureFromSurface(render,dinamic_SURFACE);
    return dinamic_Texture;
}

void show_dinamic_text::dinamic_render(SDL_Renderer* render , int ax , int ay , int aw , int ah)
{
    dinamic_rect = {ax,ay,aw,ah};
    SDL_RenderCopy(render,dinamic_Texture,NULL,&dinamic_rect);
}

show_dinamic_text::~show_dinamic_text()
{
    TTF_CloseFont(dinamic_FONT);
    SDL_FreeSurface(dinamic_SURFACE);
    SDL_DestroyTexture(dinamic_Texture);
}



