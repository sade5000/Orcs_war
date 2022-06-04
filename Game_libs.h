///////////////////////////LIBR //////////////////////////////
#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_filesystem.h>
#include <vector>
#include <SDL2/SDL_test_font.h>
#include <array>
#include <math.h>
#include <ostream>
#include <chrono>
/////////////////////////////LIBR_FILES///////////////////////
#define FRAME_POINT_NO 5
#define FRAME_THIKNESS 4
////////////FONT PATH //////////////////////
#define FONT_PATH_CHARACTER "imaeges.png"

/////////////ERROR MSG////////////////////
#define INIT_EVERITHING "Initialization Fail"
#define INIT_RENDERER "Fail to create mainRenderer"
#define INIT_IMAGE "Fail to initiate IMG"
#define INIT_TTF "Fail to initiate TTF"
#define SQUARE_TIME(x)((x) * (x))
