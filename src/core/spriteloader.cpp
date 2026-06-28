#include "spriteloader.h"

Texture2D SpriteLoader::GetSprite(const std::string& fileName) {

    Texture2D tex = LoadTexture((fileName).c_str());
    SetTextureFilter(tex, TEXTURE_FILTER_POINT);
    
    return tex;
}