#include "core\managers\gamemanager.h"
#include "core\spriteloader.h"
#include "gfxmanager.h"

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

std::vector<IUpdatable*> GameManager::updatables = std::vector<IUpdatable*>();

// GameManager& GameManager::GetInstance()  {
//     static GameManager instance; 
//     return instance;
// }

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
    // for (IDrawable* drawable : GetDrawables()) {
    //     delete drawable;
    // } 

    // for (IUpdatable* updatable : GetUpdatables()) {
    //     delete updatable;
    // } 

    SpriteLoader::UnloadAll();

    CloseWindow();
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

const std::vector<IUpdatable*>& GameManager::GetUpdatables() {
    return updatables; 
}