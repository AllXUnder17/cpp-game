#ifndef _SCENE_
#define _SCENE_

#include <unordered_map>

#include "gameobject.h"
#include <iostream>

class Scene {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Scene() = default;
    Scene(std::string name);

    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    std::vector<GameObject*>& GetGameObjects();
    std::vector<IUpdatable*>& GetUpdatables();
    
    std::string GetName() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void AddGameObject(GameObject* go);

    void Load();   
    void Update();
    void Unload();
private:
    std::string name;

    std::vector<GameObject*> gameObjects;
    std::vector<IUpdatable*> updatables;
};

#endif