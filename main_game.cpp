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
    WindAndRend window("Ukraine_vs_Russians_orcs", 800 , 600);
    while(run)//the big main loop
    {
        while(SDL_PollEvent(&event) > 0)//the big event loop
        {
            if(event.type == SDL_QUIT)
            {
                run = false;
            }
        }
        window.CleanUP();
    }

    SDL_Quit();
    return 0;
}
