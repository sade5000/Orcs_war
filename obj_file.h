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
