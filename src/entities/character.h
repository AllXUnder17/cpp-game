#ifndef _CHARACTER_
#define _CHARACTER_

#include "core/gameobject.h"
#include "core/spritesheet.h"

#include "entities/entity.h"

class Character : public Entity {
public:
    Character(const GameObjectConfig& config, const SpriteSheet& spriteSheet, float moveSpeed);

    const Vector2& GetVelocity() const; 

    void OnUpdate() override {};
    //void Draw() override;
protected:
    Vector2 velocity;
    Vector2 movementDirection;
    float moveSpeed;
};

#endif