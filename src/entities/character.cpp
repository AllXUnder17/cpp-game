#include "character.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

Character::Character(const GameObjectConfig& config, 
    const SpriteSheet& spriteSheet, 
    float moveSpeed) : Entity(config, spriteSheet) {
    this->moveSpeed = moveSpeed;
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
const Vector2& Character::GetVelocity() const {
    return velocity;
}

//===SETTERS===
void Character::SetMoveSpeed(float moveSpeed) {
    this->moveSpeed = moveSpeed;
}

//===MEMBER FUNCTIONS===
