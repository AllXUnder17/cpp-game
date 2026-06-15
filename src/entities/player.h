#ifndef _PLAYER_
#define _PLAYER_

#include "core/gameobject.h"
#include "core/icollectable.h"
#include "core/iserializable.h"

#include "core/managers/delegate.h"
#include "entities/character.h"

enum MovementDirection {
    IDLE_X, IDLE_Y, UP, RIGHT, DOWN, LEFT
};

class Player : public Character, public ISerializable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Player(const EntityConfig& config, float moveSpeed);

    //===DESTRUCTOR===
    ~Player() = default;

    //===OPERATORS===
    
    //===GETTERS===
    size_t GetCollectedCoins() const;
    size_t GetEnemiesKilled() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void OnUpdate() override final;

    void OnCollisionEnter(ICollidable* other) override final;

    void Serialize(std::ofstream& ofs) override final;
    void Deserialize(std::ifstream& ifs) override final;
private:

    //---Input Handling---
    short horizontalStack[2] = {};
    short verticalStack[2] = {};

    size_t collectedCoins;
    size_t enemiesKilled;

    Delegate<void(ICollectable*)> onCollectableEvent;

    void HandleMovement(); 

    void Dash();

    void SetDirection(const Vector2& moveDir);
    void SetDirectionX(float velX);
    void SetDirectionY(float velY);

    //---Input Handling---
    void SetKeybinds();

    void PushInputX(short dirX);
    void PopInputX(short dirX);

    void PushInputY(short dirY);
    void PopInputY(short dirY);

    //---Event hanling---
    void BroadcastOnCollectableEvent(ICollectable* collectable);

    //void OnCollectableEvent(ICollectable* collectable);
};

#endif