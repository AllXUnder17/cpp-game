#include "player.h"
#include "raymath.h"

#include "core/managers/inputmanager.h"
#include <string>

Player::Player(const GameObjectConfig& config, const SpriteSheet& spriteSheet, float moveSpeed) : Character(config, spriteSheet, moveSpeed) { 
    velocity = {0,0};
    
    InputManager::GetInstance().SetKeybind(KEY_W, [this]() {
        SetDirection({this->velocity.x, -1});
    }, ON_KEY_PRESSED);
    InputManager::GetInstance().SetKeybind(KEY_W, [this]() {
        SetDirection({this->velocity.x, 0});
    }, ON_KEY_RELEASED);

    InputManager::GetInstance().SetKeybind(KEY_S, [this]() {
        SetDirection({this->velocity.x, 1});
    }, ON_KEY_PRESSED);
    InputManager::GetInstance().SetKeybind(KEY_S, [this]() {
        SetDirection({this->velocity.x, 0});
    }, ON_KEY_RELEASED);

    InputManager::GetInstance().SetKeybind(KEY_D, [this]() {
        SetDirection({1, this->velocity.y});
    }, ON_KEY_PRESSED);
        InputManager::GetInstance().SetKeybind(KEY_D, [this]() {
        SetDirection({0, this->velocity.y});
    }, ON_KEY_RELEASED);

    InputManager::GetInstance().SetKeybind(KEY_A, [this]() {
        SetDirection({-1, this->velocity.y});
    }, ON_KEY_PRESSED);
    InputManager::GetInstance().SetKeybind(KEY_A, [this]() {
        SetDirection({0, this->velocity.y});
    }, ON_KEY_RELEASED);
}

void Player::SetDirection(const Vector2& movementDir) {
    velocity = movementDir;
}

void Player::OnUpdate() {
    Entity::OnUpdate();

    velocity = Vector2Normalize(velocity);
    velocity = Vector2Scale(velocity, moveSpeed * GetFrameTime());

    position = Vector2Add(position, velocity);
}