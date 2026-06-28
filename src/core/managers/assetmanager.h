#ifndef _ASSET_MANAGER_
#define _ASSET_MANAGER_

#include "raylib.h"
#include <string>
#include <unordered_map>

class AssetManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static Texture2D* GetTexture(const std::string& path); 

    static void UnloadAll();
private:
    static std::unordered_map<std::string, Texture2D> textureCache;
};

#endif