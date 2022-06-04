#include "obj_file.h"
Objects::Objects(float pX , float pY , SDL_Texture* pTexture)
:posX(pX) , posY(pY), Etexture(pTexture)
{
    zeroP.x = 0.0;
    zeroP.y = 0.0;
    zeroP.w = 100.0;
    zeroP.h = 100.0;
}

float Objects::GetX()
{
    return posX;
}

float Objects::GetY()
{
    return posY;
}
SDL_Texture* Objects::GetTexture()
{
    return Etexture;
}
SDL_Rect Objects::GetZeroP()
{
    return zeroP;
}

void global_force::SPEED_PRESSED_ON(float dist)
{
    int time = SDL_GetTicks()/1000;
    if(time > 0)
    {
        speed = (++dist * force_cumulator)/time;
    }
    else
        dist = dist;

}

void global_force::GRAVITY_ACC(float dist)
{
    int time = (SDL_GetTicks()/1000);
    if(time > 0)
    {
        speed = (++dist * force_cumulator)/SQUARE_TIME(time);
    }
    else
        dist = dist;

}
