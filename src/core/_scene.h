#ifndef _SCENE_old_
#define _SCENE_old_

#include <unordered_map>

#include "gameobject.h"
#include <iostream>

class Scene {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Scene() = default;
    Scene(const std::string& name);

    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    std::vector<GameObject*>& GetGameObjects();
    std::vector<IUpdatable*>& GetUpdatables();
    
    const std::string& GetName() const;
    const std::string GetFilePath() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void AddGameObject(GameObject* go);

    void Load();   
    void Update();
    void Unload();

    //---File IO---
    void SaveToFile();
    void LoadFromFile();
private:
    std::string name;

    std::vector<GameObject*> gameObjects;
    std::vector<IUpdatable*> updatables;
};

#endif