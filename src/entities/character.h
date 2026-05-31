#ifndef _CHARACTER_
#define _CHARACTER_

#include "core/gameobject.h"  // IWYU pragma: keep
#include "core/spritesheet.h"  // IWYU pragma: keep

#include "entities/entity.h"

class Character : public Entity {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Character(const EntityConfig& config, float moveSpeed);

    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    const Vector2& GetVelocity() const; 

    //===SETTERS===
    void SetMoveSpeed(float moveSpeed);
    
    //===MEMBER FUNCTIONS===
    void OnUpdate() override;

    void MoveTowardsLerp(const Vector2& targetPos, float t);
protected:
    Vector2 velocity;
    Vector2 movementDirection;
    float moveSpeed;
};

#endif