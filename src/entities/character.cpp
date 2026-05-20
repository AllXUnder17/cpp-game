#include "character.h"

Character::Character(const GameObjectConfig& config, float moveSpeed) : GameObject(config) {
    this->moveSpeed = moveSpeed;
}