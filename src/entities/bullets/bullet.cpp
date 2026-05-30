#include "bullet.h"
#include "core/idamagable.h"

#include <raymath.h>

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Bullet::Bullet(const EntityConfig& config, const Vector2& velocity, unsigned damage) : Entity(config) {
    this->velocity = velocity;
    this->damage = damage;
}
Bullet::Bullet(const Bullet& other) : Entity(other) {
    this->velocity = other.velocity;
    this->damage = other.damage;
}

//===DESTRUCTOR===

//===OPERATORS===
Bullet& Bullet::operator=(const Bullet& other) {
    if (this == &other)
        return *this;

    Entity::operator=(other);

    this->velocity = other.velocity;
    this->damage = other.damage;

    return *this;
}

//===GETTERS===

//===SETTERS===
void Bullet::SetVelocity(const Vector2& vel) {
    this->velocity = vel;
}

void Bullet::SetDamage(unsigned damage) {
    this->damage = damage;
}

//===MEMBER FUNCTIONS===
void Bullet::OnUpdate() {
    Entity::OnUpdate();
    
    Vector2 targPos = Vector2Add(position, velocity);

    SetPosition(targPos);

    if (position.x > 500 || position.x < -500 || position.y > 500 || position.y < -500)
        SetIsActive(false);
}

void Bullet::OnCollisionEnter(ICollidable* other) {
    IDamagable* damagable = dynamic_cast<IDamagable*>(other);

    if (damagable != nullptr)
        damagable->OnTakeDamage(damage);

    //recycle the bullet
    SetIsActive(false);
}