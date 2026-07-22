#ifndef _SPRITE_
#define _SPRITE_

#include "raylib.h"

#include <string>

struct Sprite {
    std::string name = "<empty>";
    Texture2D* texture = nullptr;
};

#endif