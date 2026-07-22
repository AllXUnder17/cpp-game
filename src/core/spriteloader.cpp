#include "spriteloader.h"

#include "managers/assetmanager.h"

std::unordered_map<std::string, Sprite> SpriteLoader::spriteCache = std::unordered_map<std::string, Sprite>();

Sprite* SpriteLoader::GetSprite(const std::string& fileName) {
    //SetTextureFilter(tex, TEXTURE_FILTER_POINT);
    
    auto it = spriteCache.find(fileName);
    
    if (it != spriteCache.end())
        return &it->second;

    TraceLog(LOG_INFO, "Cache miss. Make new sprite: %s", fileName.c_str());

    Texture2D* tex = AssetManager::GetTexture(fileName);
    Sprite sp = {fileName, tex};
    
    spriteCache[fileName] = sp;
    return &spriteCache[fileName];
}