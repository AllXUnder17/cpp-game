#include "scenemanager.h"

#include <exception>

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
const std::vector<Scene*>& SceneManager::GetLoadedScenes() const {
    return loadedScenes;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
//>---Private---

//>---Public---
void SceneManager::LoadScene(const std::string& name, bool add) {
    Scene* targScene = scenes[name];

    if (targScene == nullptr) {
        // throw std::exception("[SCENE]: Scene " + name + " not found!");
        return;
    }

    if (add)
        loadedScenes.push_back(targScene);
    else {
        loadedScenes.clear();
        loadedScenes.push_back(targScene);
    }

    targScene->OnLoad();
}

void SceneManager::UnloadScene(const std::string& name) {
    Scene* targScene = scenes[name];
    
    if (targScene == nullptr) {
        // throw std::exception("[SCENE]: Scene " + name + " not found!");
        return;
    }

    targScene->OnUnload();

    // loadedScenes.erase()
}

void SceneManager::Update() {
    for (auto& sc : loadedScenes) {
        sc->OnUpdate();
    }
}