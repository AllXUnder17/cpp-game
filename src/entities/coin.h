#ifndef _COIN_
#define _COIN_

#include "core/icollectable.h"
#include "entity.h"

#include "core/idamagable.h"  // IWYU pragma: keep

class Coin : public Entity, public ICollectable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Coin(const EntityConfig& config);
    Coin(const Coin& other);

    //===DESTRUCTOR===

    //===OPERATORS===
    Coin& operator=(const Coin& other);
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    //void OnTakeDamage(unsigned damage) override final;
    CollectableType OnCollect() override final;
    // void OnUpdate() override {}
    // void Draw() override {}
private:
    
};

#endif