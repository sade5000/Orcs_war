#include "Game_libs.h"
#include "wind_file.h"



////MAIN FUNCTION START HERE///////
int main(int argc , char** args)
{
    bool run = true;// game on while this is true
    SDL_Event event; // This store all the events in the main func
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) //control flow
    {
        std::cout<<"Initialization Fail "<<SDL_GetError()<<std::endl;
    }
    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if(SDL_Init(flags) != 0)
    {
     std::cout<<"Fail to initiate IMG" << SDL_GetError()<<std::endl;
    }
    WindAndRend window("Ukraine_vs_Russians_orcs", 1960 , 600);
    SDL_Texture* first_texture = window.load_Texure("//home//sade5000//Pictures//wish.jpg");
    while(run)//the big main loop
    {
        while(SDL_PollEvent(&event) > 0)//the big event loop
        {
            if(event.type == SDL_QUIT)
            {
                run = false;
            }
        }
        window.CleanUP();//clean our window
    }

    SDL_Quit();
    return 0;
}
