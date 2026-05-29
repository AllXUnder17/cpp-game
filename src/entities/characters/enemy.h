#ifndef _ENEMY_
#define _ENEMY_

#include "core/idamagable.h"

#include "entities/character.h"

class Enemy : public Character, public IDamagable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Enemy(const EntityConfig& config, float moveSpeed, unsigned health);
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    //---Inherited---
    void OnTakeDamage(unsigned damage) override;

private:
    unsigned currHealth;
};

#endif