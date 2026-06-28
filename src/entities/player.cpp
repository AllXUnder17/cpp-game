#include "player.h"
#include "entities/coin.h"
#include "raymath.h"

#include "core/managers/gamemanager.h"
#include "core/managers/inputmanager.h"
#include "core/managers/serializationmanager.h"

#include "core/icollectable.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

Player::Player(const EntityConfig& config, float moveSpeed) : Character(config, moveSpeed) { 
    velocity = {0,0};
    collectedCoins = 0;
    enemiesKilled = 0;

    tag = "Player";

    //onCollectableEvent = Delegate<ICollectable*>();

    //onCollectableEvent.Add([this](ICollectable* collectable) {this->BroadcastOnCollectableEvent(collectable);});
    
    SetKeybinds();
}

//===DESTRUCTOR===

//===GETTERS===
size_t Player::GetCollectedCoins() const {
    return collectedCoins;
}
size_t Player::GetEnemiesKilled() const {
    return enemiesKilled;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
void Player::OnAwake() {
    Character::OnAwake();

    TraceLog(LOG_INFO, "player awaken");

    SerializationManager::AddSerializable(this);
}
void Player::OnDestroy() {
    Character::OnDestroy();

    SerializationManager::RemoveSerializable(this);
}

void Player::HandleMovement() {
    Vector2 direction = this->velocity;
    
    if (direction.x != 0.0f && direction.y != 0.0f) {
        direction.x = (direction.x > 0 ? 0.7071f : -0.7071f);
        direction.y = (direction.y > 0 ? 0.7071f : -0.7071f);
    }
    
    Vector2 deltaVelocity = Vector2Scale(direction, moveSpeed * GetFrameTime());
    
    position = Vector2Add(position, deltaVelocity);
}
void Player::Dash() {
    moveSpeed *= 2;
    DisableCollider();

    GameManager::Invoke([this](){
        moveSpeed = initMoveSpeed;
        EnableCollider();
    }, 0.1);
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

    //DASH |_|
    InputManager::SetKeybind(KEY_SPACE, [this]() {
        Dash();
    }, ON_KEY_PRESSED);
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

    if (collectable != nullptr) {
        CollectableType ct = collectable->OnCollect();

        switch (ct) {
            case KEY:
                break;
            case AMMO:
                break;
            case COIN:
                ++collectedCoins;
                break;
        }
    }
}
void Player::OnUpdate() {
    Entity::OnUpdate();
    
    HandleMovement();
}

//---Serialization Handling---
void Player::Serialize(std::ofstream& ofs) {
    ofs.write(reinterpret_cast<char*>(&position.x), sizeof(position.x))
        .write(reinterpret_cast<char*>(&position.y), sizeof(position.y))
        .write(reinterpret_cast<char*>(&collectedCoins), sizeof(collectedCoins));

    // ofs.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void Player::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&position.x), sizeof(position.x))
        .read(reinterpret_cast<char*>(&position.y), sizeof(position.y))
        .read(reinterpret_cast<char*>(&collectedCoins), sizeof(collectedCoins));

    // ifs.read(reinterpret_cast<char*>(this), sizeof(*this));
}

//---Events Handling---