#ifndef _COIN_
#define _COIN_

#include "core/icollectable.h"
#include "entity.h"

#include "core/idamagable.h"

class Coin : public Entity, public ICollectable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Coin(const EntityConfig& config);

    //===DESTRUCTOR===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    //void OnTakeDamage(unsigned damage) override final;
    void OnCollect() override final;
    // void OnUpdate() override {}
    // void Draw() override {}
private:
    
};

#endif