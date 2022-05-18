#include "Game_libs.h"
#include "wind_file.h"
#include "frame_rate.h"
#include "player.h"
struct frame_coord
{
    int ax;int bx;int cx;int dx;int ex;
    int ay;int by;int cy;int dy;int ey;

};

/////////////////////////////////

////MAIN FUNCTION START HERE///////
int main(int argc , char** args)
{
    ////////////////////CTS//////////////////
    std::array<const char* , 5> Fonts_all = {"AlexBrush-Regular.ttf","Allura-Regular.ttf","ArialTh.ttf","Roboto-Black.ttf","Roboto-Bold.ttf"};
    int speed_get[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int it ; //iterator
    SDL_Color RED = {255,0,0,255};
    SDL_Color BLUE = {0,255,0,255};
    SDL_Color GREEN = {0,0,255,255};
    SDL_Color BLACK = {0,0,0,255};
    frame_coord* frame = new frame_coord;
    std::cout << sizeof(frame_coord)<< " biti struct"<<std::endl;//struct size
    /////////////////////////////////////////
    float speed = 6;   float X_ax = 0;
    float TotalXMove;
    bool run = true;// game on while this is true
    SDL_Event event; // This store all the events in the main func
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) //control flow
    {
        std::cout<<"Initialization Fail "<<SDL_GetError()<<std::endl;
    }
    int flags = IMG_INIT_JPG|IMG_INIT_PNG|SDL_TTF_MAJOR_VERSION;
    if(SDL_Init(flags) != 0)
    {
        std::cout<<"Fail to initiate IMG" << SDL_GetError()<<std::endl;
    }
    if(TTF_Init() == -1)
    {
        std::cout<<"Fail to initiate TTF " << std::endl;
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
    //////////////////////text///
    int Service = sizeof(Fonts_all);
    int Speed = sizeof(speed_get);
    std::cout << Service<<" biti" << std::endl;//size of font array
    std::cout << Speed<<" biti" << std::endl;//size of speed array
    show_text TEXT(Fonts_all[4],120,"progress...",BLACK,window.GetRenderer(),100,100);
    show_text TEXT_SCORE(Fonts_all[4],120,"your score",GREEN,window.GetRenderer(),30,30);
    show_text TEXT_START(Fonts_all[1],100,"Start Game",RED,window.GetRenderer(),60,60);
    ////////////////////Collision class
     player_collision PLAYER_COLLISION(290,95,220,60);


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
                    TEXT.~show_text();
                }

                    //////EVENTS ////
                PLAYER_COLLISION.mouse_state(event);
                    /////KEY EVENT ////
                if(event.type == SDL_KEYDOWN)
                {
                    ///if key down
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        TotalXMove = ++X_ax * speed;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                       TotalXMove = --X_ax * speed;
                    }
                    //std::cout<<"KEY DOWN"<<std::endl;//keydown test
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
        ////////////////////TEXT////////////
        TEXT.text_Renderer(window.GetRenderer(),5,0,100,40);
        TEXT_SCORE.text_Renderer(window.GetRenderer(),110,0,100,40);
        PLAYER_COLLISION.button_rect(window.GetRenderer(),200,200,100,100);

        PLAYER_COLLISION.button_frame(window.GetRenderer(),255,0,0,255,290,95,290,155,510,155,510,95,290,95);
        //PLAYER_COLLISION.button_frame(window.GetRenderer(),255,0,0,255,289,94,289,156,511,156,511,94,289,94);
        //PLAYER_COLLISION.button_frame(window.GetRenderer(),255,0,0,255,288,93,288,157,512,157,512,93,288,93);
        //PLAYER_COLLISION.button_frame(window.GetRenderer(),255,0,0,255,287,92,287,158,513,158,513,92,287,92);

        TEXT_START.text_Renderer(window.GetRenderer(),300,100,200,50);

        //////////////////////////
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
