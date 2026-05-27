#ifndef _BULLET_
#define _BULLET_

#include "core/gameobject.h"
#include "entities/entity.h"

class Bullet : public Entity {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Bullet(const GameObjectConfig& config, const SpriteSheet& spriteSheet, const Vector2& velocity);
    
    //===DESTRUCTOR===
    
    //===GETTERS===
    
    //===SETTERS===
    void SetVelocity(const Vector2& vel);

    //===MEMBER FUNCTIONS===
    //void Draw() const;
    void OnUpdate() override;
private:
    Vector2 velocity;
};

#endif