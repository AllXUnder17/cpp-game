#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include <iostream>
#include <unordered_map>

#include "core/scenes/scene.h"

class SceneManager {
public:
    //===CONSTANTS===
    
    //===GETTERS===
    static Scene* GetMainScene();
    static Scene* GetLoadedScene();
    
    //===SETTERS===

    //===MEMBER FUNCTIONS===
    static void Init();
    static void Uninit();
    
    static void Update();
    static void LoadScene(const std::string& name);
    static void UnloadScene(const std::string& name);
private:
    static void BuildScenes();
    static std::unordered_map<std::string, Scene*>scenes;

    static Scene* mainScene;
    static Scene* loadedScene;
};

#endif