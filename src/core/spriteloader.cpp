#include "spriteloader.h"

// Define our static cache container
std::unordered_map<std::string, Texture2D> SpriteLoader::textureCache;

Texture2D* SpriteLoader::GetSprite(const std::string& fileName) {
    auto it = textureCache.find(fileName);
    if (it != textureCache.end()) {
        return &(it->second);
    }

    Texture2D tex = LoadTexture(("../assets/gfx/" + fileName).c_str());
    SetTextureFilter(tex, TEXTURE_FILTER_POINT);
    
    textureCache[fileName] = tex;
    
    return &textureCache[fileName];
}

void SpriteLoader::UnloadAll() {
    for (auto& pair : textureCache) {
        TraceLog(LOG_INFO, ("Unloaded texture: " + pair.first).c_str());
        UnloadTexture(pair.second);
    }
    
    textureCache.clear();
}