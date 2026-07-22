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

    static void HandleOnStart();
    static void HandleOnEnd();
};

// Inside GameManager.h (or SceneManager.h)
template <typename T, typename... Args>
T* GameManager::InstantiateGameObject(Args&&... args) {
    T* go = new T(std::forward<Args>(args)...);

    // auto it = std::find_if(SceneManager::GetActiveGameObjects().begin(), SceneManager::GetActiveGameObjects().end(), [](GameObject* go){ ret});

    // TraceLog(LOG_INFO, "INSTANTIATED OBJECT AT ADDRESS: %p", (void*)go);
    SceneManager::GetActiveScene()->AddGameObject(go);

    go->OnAwake();

    return go;
}
#endif