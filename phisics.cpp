#include "phisics.h"
///
#define PI 3.14159265

get_plr_obj_pos::get_plr_obj_pos(SDL_Renderer* render ,float angle,int x , int y , int w , int h)
{

    SDL_Rect cap_rect = {0,0,0,0};
    SDL_SetRenderDrawColor(render,255,0,0,255);
    cap_rect.x =  x;
    cap_rect.y =  y;
    cap_rect.w = w * (sin(angle * PI/180));
    cap_rect.h = h * (cos(angle * PI/180)) ;
    SDL_RenderDrawRect(render,&cap_rect);


}

int get_plr_obj_pos::three_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,
        Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha)
{
    SDL_Point points[NO_OF_FOUR_POINTS_2D_OBJ] = {{ax,ay},{bx,by},{cx,cy},{dx,dy}};

    SDL_SetRenderDrawColor(render,Red,Green,Blue,Alpha);

    SDL_RenderDrawLines(render,points,NO_OF_FOUR_POINTS_2D_OBJ);

}

int get_plr_obj_pos::four_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,
Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha)
{
   SDL_Point points[NO_OF_FIVE_POINTS_2D_OBJ] = {{ax,ay},{bx,by},{cx,cy},{dx,dy},{ex,ey}};

    SDL_SetRenderDrawColor(render,Red,Green,Blue,Alpha);

    SDL_RenderDrawLines(render,points,NO_OF_FIVE_POINTS_2D_OBJ);

};

int get_plr_obj_pos::five_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,float fx , float fy
,Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha)
{
    SDL_Point points[NO_OF_SIX_POINTS_2D_OBJ] = {{ax,ay},{bx,by},{cx,cy},{dx,dy},{ex,ey},{fx,fy}};

    SDL_SetRenderDrawColor(render,Red,Green,Blue,Alpha);

    SDL_RenderDrawLines(render,points,NO_OF_SIX_POINTS_2D_OBJ);
}

int get_plr_obj_pos::six_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,float fx , float fy,
        float gx,float gy,Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha)
{
    SDL_Point points[NO_OF_SEVEN_POINTS_2D_OBJ] = {{ax,ay},{bx,by},{cx,cy},{dx,dy},{ex,ey},{fx,fy},{gx,gy}};

    SDL_SetRenderDrawColor(render,Red,Green,Blue,Alpha);

    SDL_RenderDrawLines(render,points,NO_OF_SEVEN_POINTS_2D_OBJ);

}



