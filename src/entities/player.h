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

    void OnUpdate() override final;
    //void Draw() override;
private:
    //---Input Handling---
    short horizontalStack[2] = {};
    short verticalStack[2] = {};

    void HandleMovement(); 

    void SetDirection(const Vector2& moveDir);
    void SetDirectionX(float velX);
    void SetDirectionY(float velY);

    //---Input Handling---
    void SetKeybinds();

    void PushInputX(short dirX);
    void PopInputX(short dirX);

    void PushInputY(short dirY);
    void PopInputY(short dirY);
};

#endif