#ifndef _CHARACTER_
#define _CHARACTER_

#include "core/gameobject.h"

class Character : public GameObject {
public:
    Character(const GameObjectConfig& config, float moveSpeed);

    virtual void OnMove() = 0;
protected:
    Vector2 velocity;
    float moveSpeed;
};

#endif