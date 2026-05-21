#include "weapon.h"

#include "raymath.h"

#include "core/managers/gamemanager.h"
#include "core/managers/gfxmanager.h"

#include <core/spriteloader.h>

#include <entities/bullets/bullet.h>

Weapon::Weapon(const GameObjectConfig& config, const Vector2& localTipOffset, int bulletsPerSecond) : GameObject(config) {
    this->localTipOffset = localTipOffset;
    this->bulletsPerSecond = bulletsPerSecond;

    bulletWaitTime = 1.0f / bulletsPerSecond;
}

float elapsedBulletWaitTime = 0.0f;

void Weapon::OnUpdate() {
    GameObject::OnUpdate();

    float cosAuth = cos(rotation * DEG2RAD);
    float sinAuth = sin(rotation * DEG2RAD);

    orientation = { cosAuth, sinAuth };

    Vector2 rotatedOffset;
    rotatedOffset.x = (localTipOffset.x * cosAuth) - (localTipOffset.y * sinAuth);
    rotatedOffset.y = (localTipOffset.x * sinAuth) + (localTipOffset.y * cosAuth);

    this->tipPos = Vector2Add(this->position, rotatedOffset);

    HandleRotation();
    HandleShoot();
}

void Weapon::HandleShoot() {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        elapsedBulletWaitTime += GetFrameTime();

        if (elapsedBulletWaitTime >= bulletWaitTime) {
            Vector2 bulletVelocity = Vector2Scale(orientation, 5);

            Bullet* b = new Bullet(GameObjectConfig{
                .sprite = SpriteLoader::GetSprite("bullet.png"),
                .position = this->tipPos 
            }, bulletVelocity);

            elapsedBulletWaitTime = 0;
        }
    }
}


void Weapon::HandleRotation() {
    Vector2 mousePos = GetMousePosition();

    Vector2 virtualMousePos = {
        mousePos.x / (GameManager::WINDOW_WIDTH / (float)GFXManager::VIRTUAL_WIDTH),
        mousePos.y / (GameManager::WINDOW_HEIGHT / (float)GFXManager::VIRTUAL_HEIGHT)
    };

    Vector2 worldMousePos = GetScreenToWorld2D(virtualMousePos, GFXManager::GetCamera());

    rotation = atan2f(worldMousePos.y - parent->GetPosition().y, worldMousePos.x - parent->GetPosition().x) * RAD2DEG;
}