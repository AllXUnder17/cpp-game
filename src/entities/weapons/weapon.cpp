#include "weapon.h"

#include "raymath.h"
#include "core/gamemanager.h"

Weapon::Weapon(const GameObjectConfig& config) : GameObject(config) { }

void Weapon::OnUpdate() {
    GameObject::OnUpdate();

    Vector2 mousePos = GetMousePosition();

    // Scale the mouse position down from screen space (1280x720) to virtual canvas space (320x180)
    // Vector2 virtualMousePos = {
    //     mousePos.x / (GameManager::WINDOW_WIDTH / (float)virtualWidth),
    //     mousePos.y / (windowHeight / (float)virtualHeight)
    // };

    Vector2 worldMousePos = GetScreenToWorld2D(mousePos, GameManager::GetCamera());

    // Calculate the angle between the gun pivot and the world mouse position
    rotation = atan2f(worldMousePos.y - position.y, worldMousePos.x - position.x) * RAD2DEG;

    //cam.target = Vector2Lerp(position, worldMousePos, 0.3);
}
