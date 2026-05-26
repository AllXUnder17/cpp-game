#ifndef _PLAYER_
#define _PLAYER_

#include "core/gameobject.h"
#include "entities/character.h"

enum MovementDirection {
    IDLE_X, IDLE_Y, UP, RIGHT, DOWN, LEFT
};

class Player : public Character {
public:
    Player(const GameObjectConfig& config, const SpriteSheet& SpriteSheet, float moveSpeed);

    const Vector2& GetVelocity() const; 

    void OnUpdate() override final;
    //void Draw() override;
private:
    //---Input Handling---
    short horizontalStack[2] = {};
    short verticalStack[2] = {};

    void HandleMovement(); 

    void SetDirection(const Vector2& moveDir);
    void SetDirectionX(const float& velX);
    void SetDirectionY(const float& velY);

    //---Input Handling---
    void SetKeybinds();

    void PushInputX(const short& dirX);
    void PopInputX(const short& dirX);

    void PushInputY(const short& dirY);
    void PopInputY(const short& dirY);
};

#endif