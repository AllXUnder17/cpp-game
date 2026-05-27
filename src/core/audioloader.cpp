#include "audioloader.h"

//===CONSTANTS===

//===STATIC MEMBERS===
std::unordered_map<std::string, Sound> AudioLoader::audioCache = std::unordered_map<std::string, Sound>();

//===CONSTRUCTORS===
void AudioLoader::Init() {
    InitAudioDevice();
}

//===DESTRUCTOR===
void AudioLoader::Uninit() {
    CloseAudioDevice();
}

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
Sound AudioLoader::GetSound(const std::string& targetDir) {
    std::string dir = "../assets/audio/" + targetDir;
    auto it = audioCache.find(targetDir);

    // If it's already loaded, just return it
    if (it != audioCache.end()) {
        return it->second;
    }

    // Otherwise, load it once
    Sound s = LoadSound(dir.c_str());
    audioCache[targetDir] = s;
    return s;
}

void AudioLoader::UnloadAll() {
    for (auto [k, v] : audioCache) {
        UnloadSound(v);
    }

    audioCache.clear();
}