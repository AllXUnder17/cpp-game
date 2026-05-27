#include "bullet.h"

#include <raymath.h>

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Bullet::Bullet(const GameObjectConfig& config, const SpriteSheet& spriteSheet, const Vector2& velocity) : Entity(config, spriteSheet) {
    this->velocity = velocity;
}

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===
void Bullet::SetVelocity(const Vector2& vel) {
    this->velocity = vel;
}

//===MEMBER FUNCTIONS===
void Bullet::OnUpdate() {
    Vector2 targPos = Vector2Add(position, velocity);

    SetPosition(targPos);

    if (position.x > 500 || position.x < -500 || position.y > 500 || position.y < -500)
        SetIsActive(false);
}