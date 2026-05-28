#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <unordered_map>
#include <vector>
#include <string>

#include "gfxmanager.h"

#include "core/managers/collisionmanager.h"

#include "core/gameobject.h"
#include "core/iupdatable.h"

class GameManager {
public:
    static unsigned short WINDOW_WIDTH;
    static unsigned short WINDOW_HEIGHT;

    //---Workflow---
    static void InitGame(
        const unsigned short windowWidth, 
        const unsigned short windowHeight, 
        const std::string& windowTitle = "Game",
        const unsigned char fps = 60);
        
    static void UninitGame();

    //===GETTERS===
    //---Game Objects---
    static const std::unordered_map<std::size_t, GameObject*>& GetGameObjects();

    static void AddGameObject(GameObject* gameObject);

    template <typename T, typename... Args>
    static T* InstantiateGameObject(Args&&... args);
    static void Destroy(GameObject* gameObject);
    
    //---Updatables---
    static void HandleUpdatables();

    static void AddUpdatable(IUpdatable* updatable);
    static void RemoveUpdatable(IUpdatable* updatable);

    static const std::vector<IUpdatable*>& GetUpdatables();

    //---Others---
    static void OutputInfo(std::stringstream& ss);
private:
    GameManager() = delete;

    static std::unordered_map<std::size_t, GameObject*> gameObjects;

    static std::vector<IOnStart*> onStartObjects;
    static std::vector<IUpdatable*> updatables;
    static std::vector<IOnEnd*> onEndObjects;

    static void HandleOnStart();
    static void HandleOnEnd();
};

template <typename T, typename... Args>
T* GameManager::InstantiateGameObject(Args&&... args) {
    GameObject* go = new T(std::forward<Args>(args)...);

    AddGameObject(go);
    AddUpdatable(go);

    GFXManager::AddDrawable(go);

    ICollidable* collidable = dynamic_cast<ICollidable*>(go);
    if (collidable != nullptr)
        CollisionManager::AddCollidable(collidable);

    return static_cast<T*>(go);
}

#endif