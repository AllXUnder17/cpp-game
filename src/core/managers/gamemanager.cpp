#include "core\managers\gamemanager.h"
#include "core\spriteloader.h"
#include "gfxmanager.h"

#include <algorithm>

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

std::vector<IUpdatable*> GameManager::updatables = std::vector<IUpdatable*>();

std::unordered_map<std::size_t, GameObject*> GameManager::gameObjects = std::unordered_map<size_t, GameObject*>();

void GameManager::InitGame(
        const unsigned short& windowWidth, 
        const unsigned short& windowHeight, 
        const std::string& windowTitle,
        const unsigned char fps) {
    GameManager::WINDOW_WIDTH = windowWidth;
    GameManager::WINDOW_HEIGHT = windowHeight;
    
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());

    SetTargetFPS(fps);

    GFXManager::Init();
}

void GameManager::UninitGame() {
    for (auto& go : GameManager::GetGameObjects()) {
        delete go.second;
    }

    SpriteLoader::UnloadAll();

    CloseWindow();
}

const std::unordered_map<std::size_t, GameObject*>& GameManager::GetGameObjects() {
    return gameObjects;
}

//---Updatables---

void GameManager::HandleUpdatables() {
    for (IUpdatable* updatable : GameManager::GetUpdatables()) {
        updatable->OnUpdate();
    }
}

void GameManager::AddUpdatable(IUpdatable* updatable) {
    updatables.push_back(updatable);
}

void GameManager::RemoveUpdatable(IUpdatable* updatable) {
    auto it = std::find(updatables.begin(), updatables.end(), updatable);
    if (it != updatables.end()) {
        updatables.erase(it);
    }
}

const std::vector<IUpdatable*>& GameManager::GetUpdatables() {
    return updatables; 
}