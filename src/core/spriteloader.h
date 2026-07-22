#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include "raylib.h"

#include <string>
#include <unordered_map>

#include "sprite.h"

class SpriteLoader {
public:
    static Sprite* GetSprite(const std::string& fileName);

private:
    static std::unordered_map<std::string, Sprite> spriteCache;
};

#endif