#include "player.h"
#include "raymath.h"

Player::Player(const GameObjectConfig& config, const SpriteSheet& spriteSheet, float moveSpeed) : Character(config, spriteSheet, moveSpeed) { }

void Player::OnUpdate() {
    Entity::OnUpdate();

    if (IsKeyDown(KEY_W))
        velocity.y = -1;
    else if (IsKeyDown(KEY_S))
        velocity.y = 1;
    else
        velocity.y = 0;
    
    if (IsKeyDown(KEY_A))
        velocity.x = -1;
    else if (IsKeyDown(KEY_D))
        velocity.x = 1;
    else
        velocity.x = 0;
    
    velocity = Vector2Normalize(velocity);
    velocity = Vector2Scale(velocity, moveSpeed * GetFrameTime());

    position = Vector2Add(position, velocity);
}