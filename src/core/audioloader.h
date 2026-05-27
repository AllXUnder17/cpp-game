#ifndef _AUDIO_LOADER_
#define _AUDIO_LOADER_

#include "raylib.h"

#include <string>
#include <unordered_map>

enum SoundType {
    BURST, SPAMMABLE
};

class AudioLoader {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    static void Init();
    
    //===DESTRUCTOR===
    static void Uninit();
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static Sound GetSound(const std::string& targetDir);

    static void UnloadAll();
private:
    static std::unordered_map<std::string, Sound> audioCache;
};

#endif