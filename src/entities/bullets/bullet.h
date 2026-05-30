#ifndef _BULLET_
#define _BULLET_

#include "core/gameobject.h"  // IWYU pragma: keep
#include "entities/entity.h"

class Bullet : public Entity {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Bullet(const EntityConfig& config, const Vector2& velocity, unsigned damage);
    Bullet(const Bullet& other);

    //===DESTRUCTOR===

    //===OPERATORS===
    Bullet& operator=(const Bullet& other);
    
    //===GETTERS===
    
    //===SETTERS===
    void SetVelocity(const Vector2& vel);
    void SetDamage(unsigned damage);

    //===MEMBER FUNCTIONS===
    //void Draw() const;
    void OnUpdate() override;
    void OnCollisionEnter(ICollidable* other) override;
private:
    Vector2 velocity;

    unsigned damage;
};

#endif