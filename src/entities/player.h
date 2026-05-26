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
    void SetDirection(const Vector2& moveDir);
};

#endif