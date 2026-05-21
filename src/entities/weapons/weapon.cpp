#include "weapon.h"

#include "raymath.h"
#include "core/gamemanager.h"

Weapon::Weapon(const GameObjectConfig& config) : GameObject(config) { }

void Weapon::OnUpdate() {
    GameObject::OnUpdate();

    Vector2 mousePos = GetMousePosition();

    Vector2 virtualMousePos = {
        mousePos.x / (GameManager::WINDOW_WIDTH / (float)GameManager::VIRTUAL_WIDTH),
        mousePos.y / (GameManager::WINDOW_HEIGHT / (float)GameManager::VIRTUAL_HEIGHT)
    };

    Vector2 worldMousePos = GetScreenToWorld2D(virtualMousePos, GameManager::GetCamera());

    // Calculate the angle between the gun pivot and the world mouse position
    rotation = atan2f(worldMousePos.y - position.y, worldMousePos.x - position.x) * RAD2DEG;

    //cam.target = Vector2Lerp(position, worldMousePos, 0.3);
}
