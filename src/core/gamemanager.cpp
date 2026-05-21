#include "gamemanager.h"
#include "spriteloader.h"

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

unsigned short GameManager::VIRTUAL_WIDTH = 320;
unsigned short GameManager::VIRTUAL_HEIGHT = 180;

std::vector<IDrawable*> GameManager::drawables = std::vector<IDrawable*>();
std::vector<IUpdatable*> GameManager::updatables = std::vector<IUpdatable*>();

RenderTexture2D GameManager::canvas = { };

Camera2D GameManager::camera = {
    .offset = { VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f },   // Still centers the lens on the screen
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

    canvas = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
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

const RenderTexture2D& GameManager::GetCanvas() {
    return canvas;
}

//---Drawables---
void GameManager::HandleDrawables() {
    for (IDrawable* drawable : GameManager::GetDrawables()) {
        drawable->Draw();
    } 
}

void GameManager::AddDrawable(IDrawable* drawable) {
    drawables.push_back(drawable);
}

const std::vector<IDrawable*>& GameManager::GetDrawables() {
    return drawables;
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
