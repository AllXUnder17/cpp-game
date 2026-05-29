#include "player.h"
#include "raymath.h"

#include "core/managers/inputmanager.h"
#include "core/managers/serializationmanager.h"

#include "core/icollectable.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

Player::Player(const EntityConfig& config, float moveSpeed) : Character(config, moveSpeed) { 
    velocity = {0,0};

    SerializationManager::AddSerializable(this);
    
    SetKeybinds();
}

Player::~Player() {
    SerializationManager::RemoveSerializable(this);
}

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void Player::HandleMovement() {
    Vector2 direction = this->velocity;
    
    if (direction.x != 0.0f && direction.y != 0.0f) {
        direction.x = (direction.x > 0 ? 0.7071f : -0.7071f);
        direction.y = (direction.y > 0 ? 0.7071f : -0.7071f);
    }
    
    Vector2 deltaVelocity = Vector2Scale(direction, moveSpeed * GetFrameTime());
    
    position = Vector2Add(position, deltaVelocity);
}
//---Direction Handling---
void Player::SetDirection(const Vector2& movementDir) {
    velocity = movementDir;
}

void Player::SetDirectionX(float velX) {    
    this->velocity.x = velX;
}

void Player::SetDirectionY(float velY) {
    this->velocity.y = velY;
}

//---Input Handling---
void Player::SetKeybinds() {
    //RIGHT ->
    InputManager::SetKeybind(KEY_D, [this]() {
            PushInputX(1);
        }, ON_KEY_PRESSED);
    InputManager::SetKeybind(KEY_D, [this]() {
            PopInputX(1);
        }, ON_KEY_RELEASED);

    //LEFT <-
    InputManager::SetKeybind(KEY_A, [this]() {
            PushInputX(-1);
        }, ON_KEY_PRESSED);
    InputManager::SetKeybind(KEY_A, [this]() {
            PopInputX(-1);
        }, ON_KEY_RELEASED);

    //UP ↑
    InputManager::SetKeybind(KEY_W, [this]() {
            PushInputY(-1);
        }, ON_KEY_PRESSED);
    InputManager::SetKeybind(KEY_W, [this]() {
            PopInputY(-1);
        }, ON_KEY_RELEASED);

    //DOWN ↓
    InputManager::SetKeybind(KEY_S, [this]() {
            PushInputY(1);
        }, ON_KEY_PRESSED);
    InputManager::SetKeybind(KEY_S, [this]() {
            PopInputY(1);
        }, ON_KEY_RELEASED);
}

void Player::PushInputX(short dirX) {
    horizontalStack[0] = horizontalStack[1];
    horizontalStack[1] = dirX;
    this->velocity.x = horizontalStack[1];
}

void Player::PopInputX(short dirX) {
    if (horizontalStack[1] == dirX) {
        horizontalStack[1] = horizontalStack[0];
        horizontalStack[0] = 0;
    }
    else if (horizontalStack[0] == dirX) {
        horizontalStack[0] = 0;
    }

    this->velocity.x = horizontalStack[1];
}

void Player::PushInputY(short dirY) {
    verticalStack[0] = verticalStack[1];
    verticalStack[1] = dirY;
    this->velocity.y = verticalStack[1];
}

void Player::PopInputY(short dirY) {
    if (verticalStack[1] == dirY) {
        verticalStack[1] = verticalStack[0];
        verticalStack[0] = 0;
    }
    else if (verticalStack[0] == dirY) {
        verticalStack[0] = 0;
    }

    this->velocity.y = verticalStack[1];
}

void Player::OnCollisionEnter(ICollidable* other) {
    ICollectable* collectable = dynamic_cast<ICollectable*>(other);

    if (collectable != nullptr)
        collectable->OnCollect();
}
void Player::OnUpdate() {
    Entity::OnUpdate();
    
    HandleMovement();
}

//---Serialization Handling---
void Player::Serialize(std::ofstream& ofs) {
    ofs.write(reinterpret_cast<char*>(&position.x), sizeof(position.x))
        .write(reinterpret_cast<char*>(&position.y), sizeof(position.y));
}
void Player::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&position.x), sizeof(position.x))
        .read(reinterpret_cast<char*>(&position.y), sizeof(position.y));
}