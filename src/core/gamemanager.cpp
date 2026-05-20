#include "gamemanager.h"
#include "spriteloader.h"

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

GameManager& GameManager::GetInstance()  {
    static GameManager instance; 
    return instance;
}

void GameManager::InitGame(
        const unsigned short& windowWidth, 
        const unsigned short& windowHeight, 
        const std::string& windowTitle,
        const unsigned char fps) {
    GameManager::WINDOW_WIDTH = windowWidth;
    GameManager::WINDOW_HEIGHT = windowHeight;
    
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());

    SetTargetFPS(60);
}

void GameManager::UninitGame() {
    for (IDrawable* drawable : GameManager::GetInstance().GetDrawables()) {
        delete drawable;
    } 

    for (IUpdatable* updatable : GameManager::GetInstance().GetUpdatables()) {
        delete updatable;
    } 

    SpriteLoader::UnloadAll();

    CloseWindow();
}

//---Drawables---
void GameManager::HandleDrawables() const {
    for (IDrawable* drawable : GetDrawables()) {
        drawable->Draw();
    } 
}

void GameManager::AddDrawable(IDrawable* drawable) {
    drawables.push_back(drawable);
}

const std::vector<IDrawable*>& GameManager::GetDrawables() const {
    return drawables;
}

//---Updatables---

void GameManager::HandleUpdatables() const {
    for (IUpdatable* updatable : updatables) {
        updatable->OnUpdate();
    }
}

void GameManager::AddUpdatable(IUpdatable* updatable) {
    updatables.push_back(updatable);
}

const std::vector<IUpdatable*>& GameManager::GetUpdatables() const {
    return updatables;
}
