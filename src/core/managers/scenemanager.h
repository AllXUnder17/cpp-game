#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include <iostream>
#include <unordered_map>

#include "core/scenes/scene.h"

class SceneManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    static const std::vector<Scene*>& GetLoadedScenes() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static void Update();
    static void LoadScene(const std::string& name, bool add = false);
    static void UnloadScene(const std::string& name);

    static void UpdateLoadedObjectsVector();
private:
    static std::unordered_map<std::string, Scene*> scenes;

    static std::vector<Scene*> loadedScenes;
};

#endif