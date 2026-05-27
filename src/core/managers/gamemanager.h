#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <unordered_map>
#include <vector>
#include <string>

#include "core/gameobject.h"
#include "core\iupdatable.h"

class GameManager {
public:
    static unsigned short WINDOW_WIDTH;
    static unsigned short WINDOW_HEIGHT;

    //---Workflow---
    static void InitGame(
        const unsigned short& windowWidth, 
        const unsigned short& windowHeight, 
        const std::string& windowTitle = "Game",
        const unsigned char fps = 60);
        
    static void UninitGame();

    
    //===GETTERS===
    //---Game Objects---
    static const std::unordered_map<std::size_t, GameObject*>& GetGameObjects();

    static void AddGameObject(GameObject* gameObject);
    static void Destroy(GameObject& gameObject);
    
    //---Updatables---
    static void HandleUpdatables();

    static void AddUpdatable(IUpdatable* updatable);
    static void RemoveUpdatable(IUpdatable* updatable);

    static const std::vector<IUpdatable*>& GetUpdatables();

    //---Others---
    static void OutputInfo(std::stringstream& ss);
private:
    // GameManager() { 
    //     drawables = std::vector<IDrawable*>(); 
    //     updatables = std::vector<IUpdatable*>();
    // };

    static std::unordered_map<std::size_t, GameObject*> gameObjects;

    GameManager() = delete;

    static std::vector<IUpdatable*> updatables;
};

#endif