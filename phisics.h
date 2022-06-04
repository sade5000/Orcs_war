#pragma once
#include "Game_libs.h"

class get_plr_obj_pos
{
    private:
        float corpX   = 0;
        float corpY   = 0;
        float wide    = 0;
        float heigth  = 0;
        float end_box = 0;
        const int NO_OF_FOUR_POINTS_2D_OBJ  = 4;
        const int NO_OF_FIVE_POINTS_2D_OBJ  = 5;
        const int NO_OF_SIX_POINTS_2D_OBJ   = 6;
        const int NO_OF_SEVEN_POINTS_2D_OBJ = 7;
        bool obj_intersection = false ;

    public:

        get_plr_obj_pos(SDL_Renderer* render ,float angle,int x , int y , int w , int h);
        int three_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,
        Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha);
        int four_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,
        Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha);
        int five_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,float fx , float fy,
        Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha);
        int six_points_2D_OBJ(SDL_Renderer* render , float angle , float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float ex,float ey,float fx , float fy,
        float gx,float gy,Uint8 Red ,Uint8 Green , Uint8 Blue , Uint8 Alpha);




        //~phisics();

};
