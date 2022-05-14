#include "Game_libs.h"
#include "wind_file.h"
#include "frame_rate.h"
//#include "player.h"
////MAIN FUNCTION START HERE///////
int main(int argc , char** args)
{
    float speed = 4;
    float X_ax = 50.0;
    float TotalXMove;
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

    WindAndRend window("Ukraine_vs_Russians_orcs", 800, 600);
    //SDL_Texture* first_texture = window.load_Texure("images.png");
    SDL_Texture* PLANE = window.load_Plane("images.png");
    ////////////////////////OBJ-class
    std::vector<Objects> obj_vec = {Objects(0  ,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(100,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(200,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(300,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(400,500,window.load_Texure("grass_and_dirt3.jpg")),

                                    Objects(400,300,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(350,100,window.load_Texure("grass_and_dirt3.jpg")),


                                    Objects(500,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(600,500,window.load_Texure("grass_and_dirt3.jpg"))};
    ////////////////////////add vectors
    {
    Objects obstacle_1(700,500,window.load_Texure("grass_and_dirt3.jpg"));
    obj_vec.push_back(obstacle_1);
    }
    ////////////////////////obstacles life end here
    /////////Refresh rate constant and accumulator for refresh rate GOVSYNC - method
    const float timeStep = 0.01f;
    float acumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();
    std::cout <<"WORKING NOW"<< std::endl;//console test
    //////////////////////
    while(run)//the big main loop
    {
        int startTicks = SDL_GetTicks64() ;//funct serve deleay loop
        ///////////////////////////////////////////
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        acumulator += frameTime;
        while(acumulator >= timeStep)
        {

            while(SDL_PollEvent(&event) > 0)//the big event loop
            {
                if(event.type == SDL_QUIT)//Quit game//X button
                {
                    run = false;
                }
                    //////EVENTS ////

                    /////KEY EVENT ////

                if(event.type == SDL_KEYDOWN)
                {
                    ///if key down
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                      TotalXMove = ++X_ax*speed;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                       TotalXMove = --X_ax*speed;
                    }
                    std::cout<<"KEY DOWN"<<std::endl;//keydown test

                }
                if(event.type == SDL_KEYUP)
                {
                    /// if key up

                }
            }
            acumulator -= timeStep;
        }
        ///////////accumulator go hand in hand with events in this loop
        const float alpha = acumulator/timeStep;
        ///////////OBJECTS RENDER//////////////////////
        window.clear_scr();
        window.sky(window.GetRenderer(),135,206,235,0);
        //Range based for loop for texture
        for(Objects& obs : obj_vec)
        {
            window.render(obs);
        }

        window.render_plr(PLANE,TotalXMove);


        ////////END OF OBJECTS//////////////
        window.display();//show window display
        /////Delay to 60Hz display//////////
        int frameTicks = SDL_GetTicks64() - startTicks;
        if(frameTicks < 1000/window.getRefreshRate())
        {
            SDL_Delay(1000/window.getRefreshRate() - frameTicks);
        }
        //////END GAME LOOP///////
    }
    window.CleanUP();//clean our window
    SDL_Quit();
    return 0;
}
