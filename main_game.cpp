#include "Game_libs.h"
#include "wind_file.h"
#include "frame_rate.h"
#include "player.h"
/////////////////////////////////

////MAIN FUNCTION START HERE///////
int main(int argc , char** args)
{
    ////////////////////CTS//////////////////
    std::array<const char* , 5> Fonts_all = {"AlexBrush-Regular.ttf","Allura-Regular.ttf","ArialTh.ttf","Roboto-Black.ttf","Roboto-Bold.ttf"};
    //int speed_get[11] = {0,1,2,3,4,5,6,7,8,9,10};
    SDL_Color RED = {255,0,0,255};
    //SDL_Color BLUE = {0,255,0,255};
    SDL_Color GREEN = {0,0,255,255};
    SDL_Color BLACK = {0,0,0,255};
    bool START_GAME = false;//GAME ON AFTER MENU
    bool OPTIONS_GAME = false; //OPTIONS AFTER MENU
    bool OPTIONS_GAME_BACK = false;//BACK AFTER OPTIONS
    /////////////////////////////////////////
    float speed = 6;   float X_ax = 0; float Y_ax = 0;
    float TotalXMove;float Jump;
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
    //int Speed = sizeof(speed_get);
    std::cout << Service<<" biti" << std::endl;//size of font array
    //std::cout << Speed<<" biti" << std::endl;//size of speed array
    show_text TEXT(Fonts_all[4],120,"player sade",BLACK,window.GetRenderer(),100,100);
    show_text TEXT_SCORE(Fonts_all[4],120,"10 points",GREEN,window.GetRenderer(),30,30);
    show_text TEXT_START(Fonts_all[1],100,"Start Game",RED,window.GetRenderer(),60,60);
    show_text TEXT_OPTIONS(Fonts_all[1],100,"Options",RED,window.GetRenderer(),60,60);
    show_text TEXT_OPTIONS_BACK(Fonts_all[1],100,"Back",RED,window.GetRenderer(),60,60);
    show_text TEXT_REZOLUTION(Fonts_all[4],120,"Window rezolution: 800 x 600",BLACK,window.GetRenderer(),100,100);

    ////////////////////Collision class
     player_collision PLAYER_COLLISION(290,95,220,60);
     player_collision PLAYER_COLLISION_OPTIONS(290,195,220,60);
     player_collision PLAYER_COLLISION_OPTIONS_BACK(50,300,220,60);

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
                //PLAYER_COLLISION.check_collision(event);
                PLAYER_COLLISION.mouse_state(event);
                PLAYER_COLLISION_OPTIONS.mouse_state(event);
                PLAYER_COLLISION_OPTIONS_BACK.mouse_state(event);

                /////KEY EVENT ////
                if(event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.clear_scr();
                        OPTIONS_GAME = true;
                    }
                    ///if key down
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        TotalXMove = ++X_ax * speed;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                       TotalXMove = --X_ax * speed;
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {

                        Jump = (--Y_ax + TotalXMove) * speed;
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN)
                    {

                        Jump = Y_ax;
                    }
                    //std::cout<<"KEY DOWN"<<std::endl;//keydown test
                }
                if(event.type == SDL_KEYUP)
                {
                    /// if key up

                }
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION.Get_Collision_flag() == true)///conditon for start btn
                    {
                        START_GAME = true;
                    }
                    else if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION_OPTIONS.Get_Collision_flag() == true)
                    {
                        OPTIONS_GAME = true;
                    }
                    else if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION_OPTIONS_BACK.Get_Collision_flag() == true)
                    {
                        OPTIONS_GAME_BACK = true;
                    }

                    //std::cout << "GAME START IS: "<<START_GAME<<std::endl;
                    /// if mouse btn down
                }
                if(event.type == SDL_MOUSEBUTTONUP)
                {
                    /// if mouse btn up
                }
            }
            acumulator -= timeStep;
        }
        ///////////accumulator go hand in hand with events in this loop
        const float alpha = acumulator/timeStep;
        if(alpha > 999.9f)//always false
            std::cout << alpha <<std::endl;
        ///////////OBJECTS RENDER//////////////////////
        window.clear_scr();

        window.sky(window.GetRenderer(),232,96,118,0);
        //Range based for loop for texture

        ////////////////////TEXT////////////


        ////////////////CHECK COLLISION
        if(PLAYER_COLLISION.Get_Collision_flag() == true)///check start game btn
        {
            PLAYER_COLLISION.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
        }
        else
            PLAYER_COLLISION.button_rect(window.GetRenderer(),0,200,0,100);
        if(PLAYER_COLLISION_OPTIONS.Get_Collision_flag() == true)///check options button
        {
            PLAYER_COLLISION_OPTIONS.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);

        }
        else
           PLAYER_COLLISION_OPTIONS.button_rect(window.GetRenderer(),0,200,0,100);



        ///////////////
        PLAYER_COLLISION.button_frame(window.GetRenderer(),0,128,0,255,289,94,289,155,510,155,510,94,289,94);
        PLAYER_COLLISION_OPTIONS.button_frame(window.GetRenderer(),0,128,0,255,289,194,289,255,510,255,510,194,289,194);
        TEXT_START.text_Renderer(window.GetRenderer(),300,100,200,50);
        TEXT_OPTIONS.text_Renderer(window.GetRenderer(),300,200,200,50);
        ///////////START AFTER MENU///////////////////////
        if(START_GAME == true)
        {
            window.clear_scr();
            window.sky(window.GetRenderer(),135,206,235,0);
            TEXT.text_Renderer(window.GetRenderer(),5,0,150,20);
            TEXT_SCORE.text_Renderer(window.GetRenderer(),300,0,150,20);
            for(Objects& obs : obj_vec)
            {
                window.render(obs);
            }
            window.render_plr(PLANE,TotalXMove,Jump);
        }
        //////////OPTIONS///////////////
        if(OPTIONS_GAME == true)
        {
            window.clear_scr();
            window.sky(window.GetRenderer(),100,100,235,0);
            if(PLAYER_COLLISION_OPTIONS_BACK.Get_Collision_flag() == true)
            {
                PLAYER_COLLISION_OPTIONS_BACK.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
            }
            else
                PLAYER_COLLISION_OPTIONS_BACK.button_rect(window.GetRenderer(),0,200,0,100);
            TEXT_REZOLUTION.text_Renderer(window.GetRenderer(),30,50,300,30);
            TEXT_OPTIONS_BACK.text_Renderer(window.GetRenderer(),110,320,100,30);
            if(OPTIONS_GAME_BACK == true)
            {
                window.clear_scr();

                OPTIONS_GAME = false;
            }
        }
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
