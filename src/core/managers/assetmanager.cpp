#include "assetmanager.h"

#include "core/spriteloader.h"

//===CONSTANTS===

//===STATIC MEMBERS===
std::unordered_map<std::string, Texture2D> AssetManager::textureCache;

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
Texture2D* AssetManager::GetTexture(const std::string& path) {
    std::string fullPath = "../assets/gfx/" + path;

    auto it = textureCache.find(fullPath);

    if (it != textureCache.end())
        return &it->second;

    TraceLog(LOG_INFO, "Cache miss. Loading asset from disk: %s", fullPath.c_str());
    Texture2D texture = LoadTexture((fullPath).c_str());;

    textureCache[fullPath] = texture;
    return &textureCache[fullPath];
}

void AssetManager::UnloadAll() {
    //---UNLOAD TEXTURES---
    for (auto& pair : textureCache) {
        TraceLog(LOG_INFO, ("Purging texture from VRAM: " + pair.first).c_str());

        UnloadTexture(pair.second);
    }

    textureCache.clear();
}