#include "character.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

Character::Character(const EntityConfig& config, float moveSpeed) : Entity(config) {
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
void Character::OnUpdate() {
    Entity::OnUpdate();
}