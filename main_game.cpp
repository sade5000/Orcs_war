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

    WindAndRend window("Ukraine_vs_Russians_orcs", 800, 600);
    SDL_Texture* first_texture = window.load_Texure("grass_and_dirt3.jpg");
    ////////////////////////OBJ-class

    std::vector<Objects> obj_vec = {Objects(0,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(100,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(200,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(300,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(400,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(500,500,window.load_Texure("grass_and_dirt3.jpg")),
                                    Objects(600,500,window.load_Texure("grass_and_dirt3.jpg"))};
    ////////////////////////add vectors
    {
    Objects obstacle_1(700,500,window.load_Texure("grass_and_dirt3.jpg"));
    obj_vec.push_back(obstacle_1);
    }
    ////////////////////////obstacles life end here

    while(run)//the big main loop
    {

        while(SDL_PollEvent(&event) > 0)//the big event loop
        {
            if(event.type == SDL_QUIT)
            {
                run = false;
            }
            window.clear_scr();
            window.sky(window.GetRenderer(),135,206,235,0);
            //Range based for loop for texture
            for(Objects& obs : obj_vec)
            {
                window.render(obs);
            }
            //
            window.display();
        }
    }
    window.CleanUP();//clean our window
    SDL_Quit();
    return 0;
}
