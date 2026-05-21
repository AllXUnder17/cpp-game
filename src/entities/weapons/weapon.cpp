#include "weapon.h"

#include "raymath.h"

#include "core/managers/gamemanager.h"
#include "core/managers/gfxmanager.h"

Weapon::Weapon(const GameObjectConfig& config) : GameObject(config) { }

void Weapon::OnUpdate() {
    GameObject::OnUpdate();

    Vector2 mousePos = GetMousePosition();

    Vector2 virtualMousePos = {
        mousePos.x / (GameManager::WINDOW_WIDTH / (float)GFXManager::VIRTUAL_WIDTH),
        mousePos.y / (GameManager::WINDOW_HEIGHT / (float)GFXManager::VIRTUAL_HEIGHT)
    };

    Vector2 worldMousePos = GetScreenToWorld2D(virtualMousePos, GFXManager::GetCamera());

    // Calculate the angle between the gun pivot and the world mouse position
    rotation = atan2f(worldMousePos.y - parent->GetPosition().y, worldMousePos.x - parent->GetPosition().x) * RAD2DEG;

    //cam.target = Vector2Lerp(position, worldMousePos, 0.3);
}
