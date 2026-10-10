#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

#include "gfxmanager.h"

#include "core/managers/scenemanager.h"

#include "core/gameobject.h"
#include "core/iupdatable.h"

struct DelayedCallback {
    std::function<void()> callback;
    float delay;
    float elapsedTime = 0;
    bool isRepeated;
};

class GameManager {
public:
    static unsigned short WINDOW_WIDTH;
    static unsigned short WINDOW_HEIGHT;

    GameManager() = delete;

    //---Workflow---
    static void InitGame(
        const unsigned short windowWidth, 
        const unsigned short windowHeight, 
        const std::string& windowTitle = "Game",
        const unsigned char fps = 60);
        
    static void UninitGame();

    //===GETTERS===
    //---Game Objects---
    template <typename T, typename... Args>
    static T* InstantiateGameObject(Args&&... args);

    template <typename T, typename... Args>
    static T* InstantiateGameObjectInSCMain(Args&&... args);

    static void Destroy(GameObject* go);

    static GameObject* GetGameObjectWithTag(const std::string& tag);

    //---Others---
    static void HandleUpdate();
    static void CleanupDeadObjects();

    static void OutputInfo(std::stringstream& ss);

    static void Invoke(std::function<void()> callback, float delay,bool isRepeated = false);
    static void HandleDelayedCallbacks();
private:
    // static std::unordered_map<std::size_t, GameObject*> gameObjects;
    static std::vector<DelayedCallback> delayedCallbacks;

    static std::vector<GameObject*> loadedGameObjects;

    static void HandleOnStart();
    static void HandleOnEnd();
};

template <typename T, typename... Args>
T* GameManager::InstantiateGameObject(Args&&... args) {
    T* go = new T(std::forward<Args>(args)...);

    Scene* scene = SceneManager::GetLoadedScene();
    if (scene != nullptr) 
        scene->AddGameObject(go);
    else 
        throw std::runtime_error("GAME_MANAGER: Failed to instantiate object - Loaded scene is NULL!");

    go->OnAwake();

    return go;
}

template <typename T, typename... Args>
T* GameManager::InstantiateGameObjectInSCMain(Args&&... args) {
    T* go = new T(std::forward<Args>(args)...);

    Scene* mainScene = SceneManager::GetMainScene();
    if (mainScene != nullptr)
        mainScene->AddGameObject(go);
    else
        throw std::runtime_error("GAME_MANAGER: Main scene not found.");
    
    go->OnAwake();

    return go;
}
#endif