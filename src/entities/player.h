#ifndef _PLAYER_
#define _PLAYER_

#include "core/gameobject.h"
#include "entities/character.h"

class Player : public Character {
public:
    Player(const GameObjectConfig& config, float moveSpeed);

    void OnUpdate() override final;
    void OnMove() override {};
private:
    
};

#endif