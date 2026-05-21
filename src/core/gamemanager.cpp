#include "gamemanager.h"
#include "spriteloader.h"

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

std::vector<IDrawable*> GameManager::drawables = std::vector<IDrawable*>();
std::vector<IUpdatable*> GameManager::updatables = std::vector<IUpdatable*>();

Camera2D GameManager::camera = {
    //camera.offset = { virtualWidth / 2.0f, virtualHeight / 2.0f };   // Still centers the lens on the screen
    .offset = { 0, 0 },
    .rotation = 0.0f,
    .zoom = 1.0f
};

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

    
}

void GameManager::UninitGame() {
    for (IDrawable* drawable : GetDrawables()) {
        delete drawable;
    } 

    for (IUpdatable* updatable : GetUpdatables()) {
        delete updatable;
    } 

    SpriteLoader::UnloadAll();

    CloseWindow();
}

const Camera2D & GameManager::GetCamera(){    
    return camera;
}

//---Drawables---
void GameManager::HandleDrawables() {
    for (IDrawable* drawable : GameManager::GetDrawables()) {
        drawable->Draw();
    } 
}

void GameManager::AddDrawable(IDrawable* drawable) {
    TraceLog(LOG_WARNING, "Added drawable: %d", drawable);

    drawables.push_back(drawable);
}

const std::vector<IDrawable*>& GameManager::GetDrawables() {
    return drawables;
}

//---Updatables---

void GameManager::HandleUpdatables() {
    for (IUpdatable* updatable : GameManager::GetUpdatables()) {
        updatable->OnUpdate();
        TraceLog(LOG_INFO, "Updated object %d", &updatable);
    }
    TraceLog(LOG_INFO, "==========");
}

void GameManager::AddUpdatable(IUpdatable* updatable) {
    TraceLog(LOG_WARNING, "Added updatable: %d", updatable);


    updatables.push_back(updatable);
}

const std::vector<IUpdatable*>& GameManager::GetUpdatables() {
    return updatables; 
}
