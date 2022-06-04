#pragma once
#include "Game_libs.h"
class Objects
{
private:
    float posX , posY;
    mutable SDL_Rect zeroP;
    SDL_Texture* Etexture;

public:
    Objects(float pX , float pY, SDL_Texture* pTexture);
    float GetX();
    float GetY();
    SDL_Texture* GetTexture();
    SDL_Rect GetZeroP();
};

class global_force
{
    private:

    float speed =  0; /// speed = m/s
    int force_cumulator = 2;
    int time  = SDL_GetTicks()/1000;
    public:

    //force();
    void SPEED_PRESSED_ON(float dist);
    void GRAVITY_ACC(float dist);

    float gravity();

    //~force();

};
