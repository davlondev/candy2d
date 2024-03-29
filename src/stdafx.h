#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
#include <map>
#include <format>



// ECS
#include <unordered_set>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>


#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

//#define CTFS SDL_CreateTextureFromSurface

#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/matrix_transform.hpp"


enum SPRITE_LAYERS {
    SPRITE_LAYER_BACKGROUND,
    SPRITE_LAYER_YSORT,
    SPRITE_LAYER_TOP,
    SPRITE_LAYER_UI
};

