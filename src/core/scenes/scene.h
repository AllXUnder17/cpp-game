#ifndef _SCENE_
#define _SCENE_

#include <vector>

class GameObject;

class Scene {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    virtual void OnLoad() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnUnload() = 0;

private:
    std::vector<GameObject*> gameobjects;
};

#endif