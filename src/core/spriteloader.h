#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include "raylib.h"
#include <string>
#include <unordered_map>

class SpriteLoader {
public:
    static Texture2D GetSprite(const std::string& fileName);
};

#endif