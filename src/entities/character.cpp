#include "character.h"

Character::Character(const GameObjectConfig& config, 
    const SpriteSheet& spriteSheet, 
    float moveSpeed) : Entity(config, spriteSheet) {
    this->moveSpeed = moveSpeed;
}