#include "gfxmanager.h"

#include <iomanip> // IWYU pragma: keep
#include <algorithm> // IWYU pragma: keep

#include "gamemanager.h"

#include "core/idrawable.h"

//===STATIC MEMBERS===
Color GFXManager::BACKGROUND_COLOR = MAGENTA;

unsigned short GFXManager::VIRTUAL_WIDTH = 320;
unsigned short GFXManager::VIRTUAL_HEIGHT = 180;

unsigned GFXManager::FRAMES_PER_SECOND = 12;
float GFXManager::FRAME_WAIT_TIME = 0;

std::vector<IDrawable*> GFXManager::drawables = std::vector<IDrawable*>();

RenderTexture2D GFXManager::canvas = { };

Camera2D GFXManager::camera = {
    .offset = { VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f },   // Still centers the lens on the screen
    .rotation = 0.0f,
    .zoom = 1.0f
};

//===CONSTRUCTORS===
void GFXManager::Init(const unsigned animationFramesPerSecond) {
    canvas = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    FRAMES_PER_SECOND = animationFramesPerSecond;
    FRAME_WAIT_TIME = 1.0f / FRAMES_PER_SECOND;
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
    for (IDrawable* drawable : GetDrawables()) {
        if (drawable->IsDrawableActive())
            drawable->Draw();
    } 
}

void GFXManager::AddDrawable(IDrawable* drawable) {
    if (drawable == nullptr) {
        TraceLog(LOG_INFO, "const char *text, ...");
        return;
    }
    drawables.push_back(drawable);
}
void GFXManager::RemoveDrawable(IDrawable* drawable) {
    std::vector<IDrawable*>::iterator it = std::find(drawables.begin(), drawables.end(), drawable);
    
    if (it != drawables.end()) // == myVector.end() means the element was not found
        drawables.erase(it);
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

//---Stuff---
void GFXManager::OutputInfo(std::stringstream& ss) {
    ss << std::fixed << "GFX: [ CNT: " << drawables.size() << " ]\n\n";
}