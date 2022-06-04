#include "Game_libs.h"
#include "wind_file.h"
#include "frame_rate.h"
#include "player.h"
#include "phisics.h"

/// Main struct
struct var_strct
{
    int multiply_header        = 0;
    int Xrez                   = 0 ; int Yrez = 0 ; int Zrez = 0 ;///Rezolution
    Uint8 Red                  = 0; Uint8 Green = 0 ; Uint8 Blue = 0 ; Uint8 Alpfa = 0 ;///Utief8 - RGB - collors
    SDL_Color RED              = {255,0,0,255};///SDL_COLOR
    SDL_Color BLUE             = {0,0,255,255};///SDL_COLOR
    SDL_Color GREEN            = {0,255,0,255};///SDL_COLOR
    SDL_Color BLACK            = {0,0,0,255};///SDL_COLOR
    SDL_Color YELLOW           = {250,240,10,255};///SDL_COLOR
    bool START_GAME            = false;///GAME ON AFTER MENU
    bool OPTIONS_GAME          = false; ///OPTIONS AFTER MENU
    bool OPTIONS_GAME_BACK     = false;///BACK AFTER OPTIONS
    float speed                = 6; /* Character speed */  float X_ax = 0; float Y_ay = 450;///Coordonates for move
    float TotalXMove           = 0;/* Total move X - axies*/ float Jump = 0; ///Jump var
    bool run                   = true;///bool running game
    int ax                     = 0; int ay = 0 ; int aw = 0 ; int ah = 0 ;///Collision bounding box
    int text_size_W            = 0 ; int text_size_H = 0; ///text length
    int font_size              = 0 ; ///font size
    const char* message_bot    = "This war will never be forgotten. Neither the heroes of Azovstal.";
    char* game_title           = "Маріуополь";///Game title
    const char* player_texture = "images.png";///Player texture and animation
    const char* ground_texture = "grass_and_dirt3.jpg";///Ground texture
    const char* bkg_options    = "optioons_bkg.jpg";
    const char* header_texture = "Rusty_pins_real.jpg";
    const char* seal_texture   = "UKRAINE_ANTEUM.png";
    const char* wood_pillar    = "Wood_pilllar.png";
    const char* ukraine_map    = "Ukraine_Map.jpg";
    const char* unpress_start  = "button_png.png";
    const char* first_start_pic = "main_image_start.png";
    const char* obs_block1     = "block_1.png";
    int timmer                 = 0;
    clock_t jump_start_time    = 0;
    clock_t jump_end_time      = 0;
    float jump_dif_time        = 0;
    float max_force            = 10;///MAX of force when jump
};
///ENUM REZOLUTION////////////////////////////
enum REZOLUTIN_480 {rez_480p_X = 640, rez_480p_Y = 480, rez_480p_Z = 0};
enum REZOLUTIN_600 {rez_600p_X = 800, rez_600p_Y = 600, rez_600p_Z = 100};
enum REZOLUTIN_720 {rez_720p_X = 1280, rez_720p_Y = 720, rez_720p_Z = 0};
enum REZOLUTIN_1080{rez_1080p_X = 1920, rez_1080p_Y = 1080, rez_1080p_Z = 0};
enum REZOLUTIN_1440_2K{rez_1440_2K_X = 2560, rez_1440_2K_Y = 1440, rez_1440_2K_Z = 0};
enum REZ_CHOSE{REZOLUTIN_480,REZOLUTIN_600,REZOLUTIN_720,REZOLUTIN_1080,REZOLUTIN_1440_2K};///Rezolutin chose in options
////////////////////////////////////////////////////////

////MAIN FUNCTION START HERE///////
int main(int argc , char** args)
{
    std::cout << "size of var_struct: "<<sizeof(var_strct)<<" biti"<<std::endl;///size of structure / just checking / erase this when done!
    var_strct* variable = new var_strct;///pointer to structure
    ////////////////////CTS//////////////////
    std::array<const char* , 5 > Fonts_all = {"AlexBrush-Regular.ttf","Allura-Regular.ttf","ArialTh.ttf","Roboto-Black.ttf","Roboto-Bold.ttf"};
    /////////////////////////////////////////
    float speed = 6;   float X_ax = 5.0f; float Y_ay = 450.0f;
    float TotalXMove;float Jump;

    SDL_Event event; /// This store all the events in the main func
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) //control flow
    {
        std::cout<<INIT_EVERITHING<<SDL_GetError()<<std::endl;
    }
    int flags = IMG_INIT_JPG|IMG_INIT_PNG|SDL_TTF_MAJOR_VERSION;
    if(SDL_Init(flags) != 0)
    {
        std::cout<< INIT_IMAGE << SDL_GetError()<<std::endl;
    }
    if(TTF_Init() == -1)
    {
        std::cout<<INIT_TTF<< std::endl;
    }

    WindAndRend window(variable->game_title, rez_600p_X,rez_600p_Y);///Window name (or game name) , wide , heigth
    SDL_Texture* FIRST_IMG = window.load_bkg_texture(variable->first_start_pic);
    SDL_Texture* PLANE = window.load_Plane(variable->player_texture);
    SDL_Texture* HEAD  = window.load_bkg_texture(variable->header_texture);
    SDL_Texture* SIGLA = window.load_Texure(variable->seal_texture);
    SDL_Texture* WOOD  = window.load_bkg_texture(variable->wood_pillar);
    SDL_Texture* UKRAINE_MAP = window.load_bkg_texture(variable->ukraine_map);
    SDL_Texture* UNPRESS_START_BTN = window.load_bkg_texture(variable->unpress_start);
    SDL_Texture* UNPRESS_OPTIONS_BTN = window.load_bkg_texture(variable->unpress_start);
    SDL_Texture* BKG_OPTIONS = window.load_bkg_texture(variable->bkg_options);

    ///OBJ-class
    std::vector<Objects> obj_vec = {Objects(0  ,500,window.load_Texure(variable->ground_texture)),
                                    Objects(100,500,window.load_Texure(variable->ground_texture)),
                                    Objects(200,500,window.load_Texure(variable->ground_texture)),
                                    Objects(300,500,window.load_Texure(variable->ground_texture)),
                                    Objects(400,500,window.load_Texure(variable->ground_texture)),
                                    Objects(500,500,window.load_Texure(variable->ground_texture)),
                                    Objects(600,500,window.load_Texure(variable->ground_texture))};
    ///add vectors
    {
    Objects obstacle_1(700,500,window.load_Texure(variable->ground_texture));
    obj_vec.push_back(obstacle_1);
    Objects obs_stop_1(400,400,window.load_Texure(variable->obs_block1));
    obj_vec.push_back(obs_stop_1);
    }
    ///obstacles life end here
    ///Refresh rate constant and accumulator for refresh rate GOVSYNC - method
    const float timeStep = 0.01f;
    float acumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();
    std::cout <<"WORKING NOW"<< std::endl;//console test
    ///text///
    int Service = sizeof(Fonts_all);
    std::cout << Service<<" biti" << std::endl;///size of font array
    show_text TEXT(Fonts_all[4],120,"player sade",variable->BLACK,window.GetRenderer(),100,100);
    show_text TEXT_START(Fonts_all[3],100,"Start Game",variable->RED,window.GetRenderer(),20,20);
    show_text TEXT_OPTIONS(Fonts_all[3],100,"Options",variable->RED,window.GetRenderer(),60,60);
    show_text TEXT_EXIT(Fonts_all[3],100,"Exit Game",variable->RED,window.GetRenderer(),60,60);
    show_text TEXT_OPTIONS_BACK(Fonts_all[3],100,"Back",variable->RED,window.GetRenderer(),60,60);
    show_text TEXT_REZOLUTION(Fonts_all[4],120,"Window rezolution: 800 x 600",variable->BLACK,window.GetRenderer(),100,100);
    show_text TEXT_GAME_NAME(Fonts_all[0],120,"Mariuopol",variable->YELLOW,window.GetRenderer(),100,100);
    show_text TEXT_MESSAGE_BOT(Fonts_all[0],120,variable->message_bot,variable->BLUE,window.GetRenderer(),100,100);

    ///Collision class
     player_collision PLAYER_COLLISION(32,82,248,46);
     player_collision PLAYER_COLLISION_OPTIONS(32,182,248,46);
     player_collision PLAYER_COLLISION_EXIT(32,282,248,46);
     player_collision PLAYER_COLLISION_OPTIONS_BACK(32,400,248,46);
    //////////////////////

    while(variable->run)///the big main loop
    {
        int startTicks = SDL_GetTicks64() ;///funct serve deleay loop
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        acumulator += frameTime;
        while(acumulator >= timeStep)
        {
            while(SDL_PollEvent(&event) > 0)///the big event loop
            {
                if(event.type == SDL_QUIT)///Quit game//X button
                {
                    TEXT.~show_text();
                    SDL_Quit();
                }
                ///Get mouse state for collision
                PLAYER_COLLISION.mouse_state(event);
                PLAYER_COLLISION_OPTIONS.mouse_state(event);
                PLAYER_COLLISION_EXIT.mouse_state(event);
                PLAYER_COLLISION_OPTIONS_BACK.mouse_state(event);
                ///KEY EVENT
                if(event.type == SDL_KEYDOWN)
                {
                    int counter_press = SDL_GetTicks()/1000;
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.clear_scr();
                        variable->OPTIONS_GAME = true;
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
                    else if(event.key.keysym.sym == SDLK_SPACE)
                    {
                        variable->jump_start_time = clock();
                        variable->jump_dif_time = (float)(variable->jump_end_time - variable->jump_start_time)/ CLOCKS_PER_SEC;
                        Jump = Y_ay;
                        std::cout << "jump : " << Jump <<std::endl;
                        std::cout << "time : " << variable->jump_dif_time <<std::endl;
                        if(variable->jump_dif_time < 0 && (event.key.keysym.sym != SDLK_RIGHT || event.key.keysym.sym != SDLK_LEFT))
                        {

                                Jump = (--Y_ay) ;

                           std::cout << "jump : " << Jump <<std::endl;
                        }
                    }
                }


                    /// TotalXMove , Jump , TotalXMove , jump+100 , TotalXMove + 100 , Jump + 100 , TotalXMove + 100 , Jump , TotalXMove , Jump


                if(event.type == SDL_KEYUP)
                {
                    /// if key up
                    variable->jump_end_time = clock();
                    //variable->jump_end_time = 0;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION.Get_Collision_flag() == true)///conditon for start btn
                    {
                        variable->START_GAME = true;
                    }
                    else if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION_OPTIONS.Get_Collision_flag() == true)
                    {
                        variable->OPTIONS_GAME = true;
                    }
                    else if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION_EXIT.Get_Collision_flag() == true)
                    {
                        variable->run = false;
                    }
                    else if(event.button.clicks == SDL_BUTTON_LEFT && PLAYER_COLLISION_OPTIONS_BACK.Get_Collision_flag() == true)
                    {
                        variable->OPTIONS_GAME_BACK = true;
                    }
                    /// if mouse btn down
                }

                if(event.type == SDL_MOUSEBUTTONUP)
                {
                    /// if mouse btn up
                }
            }
            acumulator -= timeStep;
        }
        ///accumulator go hand in hand with events in this loop
        const float alpha = acumulator/timeStep;
        if(alpha > 999.9f)//always false
            std::cout << alpha <<std::endl;
         ///OBJECTS RENDER
         window.clear_scr();
         window.sky(window.GetRenderer(),96,96,96,0);///bkg color
         window.render_hdr(window.GetRenderer(),FIRST_IMG,10,10,800,550,0,50,800,500);

         for(int i = 0 ; i < 17 ; i++ )/// Menu - Iron texture
         {
            variable->multiply_header = i*50;
            window.render_hdr(window.GetRenderer(),HEAD,0,0,200,200,0+variable->multiply_header,0,50,50);
         }
        for(int i = 0 ; i < 17 ; i++ )
         {
            variable->multiply_header = i*50;
            window.render_hdr(window.GetRenderer(),HEAD,0,0,200,200,0+variable->multiply_header,550,50,50);
         }

         window.render_hdr(window.GetRenderer(),SIGLA,0,0,800,600,680,440,130,100);/// Ukraine anteum
        /////////////////////////////////////
        if(PLAYER_COLLISION.Get_Collision_flag() == true)///check start game btn
        {
            PLAYER_COLLISION.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
        }
        else
        {
            PLAYER_COLLISION.button_rect(window.GetRenderer(),0,200,0,100);
        }
        window.render_hdr(window.GetRenderer(),UNPRESS_START_BTN,0,0,300,85,30,80,250,50);
        if(PLAYER_COLLISION_OPTIONS.Get_Collision_flag() == true)///check options button
        {
            PLAYER_COLLISION_OPTIONS.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
        }
        else
           PLAYER_COLLISION_OPTIONS.button_rect(window.GetRenderer(),0,200,0,100);
        window.render_hdr(window.GetRenderer(),UNPRESS_OPTIONS_BTN,0,0,300,85,30,180,250,50);

        if(PLAYER_COLLISION_EXIT.Get_Collision_flag() == true)///check options button
        {
            PLAYER_COLLISION_EXIT.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
        }
        else
           PLAYER_COLLISION_EXIT.button_rect(window.GetRenderer(),0,200,0,100);
        window.render_hdr(window.GetRenderer(),UNPRESS_OPTIONS_BTN,0,0,300,85,30,280,250,50);
        /// END of COLLISION
        TEXT_START.text_Renderer(window.GetRenderer(),85,90,150,30);
        TEXT_OPTIONS.text_Renderer(window.GetRenderer(),85,190,150,30);
        TEXT_EXIT.text_Renderer(window.GetRenderer(),85,290,150,30);
        TEXT_GAME_NAME.text_Renderer(window.GetRenderer(),250,400,300,100);
        TEXT_MESSAGE_BOT.text_Renderer(window.GetRenderer(),50,470,600,60);

        ///////////START AFTER MENU///////////////////////
        if(variable->START_GAME == true)
        {
            window.clear_scr();
            window.sky(window.GetRenderer(),135,206,235,0);
            get_plr_obj_pos PLR_POS(window.GetRenderer(),30,300,300,100,100);
            PLR_POS.four_points_2D_OBJ(window.GetRenderer(),0,TotalXMove - 1,Jump -1,TotalXMove -1,Jump + 51,TotalXMove + 101 ,Jump + 51 ,TotalXMove + 51,Jump-1,TotalXMove-1,Jump-1,255,0,255,255);
            PLR_POS.three_points_2D_OBJ(window.GetRenderer(),0,105,120,30,180,180,180,105,120,255,255,0,255);
            variable->timmer = SDL_GetTicks()/1000;
            //TEXT.text_Renderer(window.GetRenderer(),5,0,150,20);
            show_dinamic_text TIME_COUNTER(window.GetRenderer(),Fonts_all[3],180,std::to_string(variable->timmer),variable->RED);///dinamic text count time
            TIME_COUNTER.dinamic_render(window.GetRenderer(),390,0,50,30);///dinamic text count time renderer with unlimited refresh rate
            for(Objects& obs : obj_vec)
            {
                window.render(obs);
            }

            window.render_plr(PLANE,TotalXMove,Jump);///renderer of move char
            if(variable->OPTIONS_GAME == true)
            {
                variable->START_GAME = false;
            }
            //phisics BLOCK(0,400,400,100,100,TotalXMove,Jump);
        }
        ///OPTIONS
        if(variable->OPTIONS_GAME == true)
        {
            window.clear_scr();
            window.render_hdr(window.GetRenderer(),BKG_OPTIONS,0,0,800,600,0,0,800,600);

            if(PLAYER_COLLISION_OPTIONS_BACK.Get_Collision_flag() == true)
            {
                PLAYER_COLLISION_OPTIONS_BACK.button_rect(window.GetRenderer(),200 + 50,200 + 50 ,100,100);
            }
            else
                PLAYER_COLLISION_OPTIONS_BACK.button_rect(window.GetRenderer(),0,200,0,100);
            window.render_hdr(window.GetRenderer(),UNPRESS_OPTIONS_BTN,0,0,300,85,30,398,250,50);
            TEXT_REZOLUTION.text_Renderer(window.GetRenderer(),30,50,300,30);
            TEXT_OPTIONS_BACK.text_Renderer(window.GetRenderer(),110,410,100,30);
            if(variable->OPTIONS_GAME_BACK == true)
            {
                variable->OPTIONS_GAME = false;
            }
        }
        ///END OF OBJECTS
            window.display();///show window display
        ///Delay to 60Hz display
            int frameTicks = SDL_GetTicks64() - startTicks;
            if(frameTicks < 1000/window.getRefreshRate())
            {
                SDL_Delay(1000/window.getRefreshRate() - frameTicks);
            }
        ///END GAME LOOP
    }

    SDL_DestroyTexture(PLANE);
    SDL_DestroyTexture(SIGLA);
    delete variable;
    //TIME_COUNTER.~show_dinamic_text();
    window.CleanUP();///clean our window
    SDL_Quit();
    return 0;
}




