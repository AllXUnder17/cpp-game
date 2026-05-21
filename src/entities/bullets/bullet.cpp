#include "bullet.h"

#include <raymath.h>

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Bullet::Bullet(const GameObjectConfig& config, const Vector2& velocity) : GameObject(config) {
    this->velocity = velocity;
}

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===



//===MEMBER FUNCTIONS===
void Bullet::OnUpdate() {
    Vector2 timeVel = Vector2Scale(velocity, GetFrameTime());
    Vector2 targPos = Vector2Add(position, velocity);

    SetPosition(targPos);
}