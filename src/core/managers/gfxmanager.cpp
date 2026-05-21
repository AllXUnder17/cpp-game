#include "gfxmanager.h"
#include "gamemanager.h"

//===CONSTANTS===
Color GFXManager::BACKGROUND_COLOR = MAGENTA;

unsigned short GFXManager::VIRTUAL_WIDTH = 320;
unsigned short GFXManager::VIRTUAL_HEIGHT = 180;

std::vector<IDrawable*> GFXManager::drawables = std::vector<IDrawable*>();

RenderTexture2D GFXManager::canvas = { };

Camera2D GFXManager::camera = {
    .offset = { VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f },   // Still centers the lens on the screen
    .rotation = 0.0f,
    .zoom = 1.0f
};

//===CONSTRUCTORS===
void GFXManager::Init() {

    canvas = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
}

const Camera2D& GFXManager::GetCamera() {
    return camera;
}

const RenderTexture2D& GFXManager::GetCanvas() {
    return canvas;
}

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
//---Drawables---
void GFXManager::HandleDrawables() {
    for (IDrawable* drawable : GFXManager::GetDrawables()) {
        drawable->Draw();
    } 
}

void GFXManager::AddDrawable(IDrawable* drawable) {
    drawables.push_back(drawable);
}

const std::vector<IDrawable*>& GFXManager::GetDrawables() {
    return drawables;
}

//---Canvas---
void GFXManager::DrawCanvas() {

    BeginMode2D(camera);

        DrawLine(-500, 0, 500, 0, LIGHTGRAY);
    
        GFXManager::HandleDrawables();

    EndMode2D();

}

void GFXManager::RenderCanvas() {
    Rectangle canvasSource = { 0.0f, 0.0f, (float)GFXManager::GetCanvas().texture.width, -(float)GFXManager::GetCanvas().texture.height };
    Rectangle canvasDest = { 0.0f, 0.0f, (float)GameManager::WINDOW_WIDTH, (float)GameManager::WINDOW_HEIGHT };
    Vector2 canvasOrigin = { 0.0f, 0.0f };

    DrawTexturePro(GFXManager::GetCanvas().texture, canvasSource, canvasDest, canvasOrigin, 0.0f, WHITE);
}
