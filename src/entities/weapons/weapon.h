#ifndef _WEAPON_
#define _WEAPON_

#include <iostream>

#include "core\gameobject.h"

class Weapon : public GameObject {
public:
    //===CONSTRUCTORS===
    //add damage, magazine capacity
    Weapon(const GameObjectConfig& config, const Vector2& localTipOffset, int bulletsPerSecond);
    
    //===DESTRUCTOR===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    
    //---Inherited---
    void OnUpdate() override;
    
    protected:
    Vector2 orientation;
    
    Vector2 tipPos;
    Vector2 localTipOffset;
    
    int bulletsPerSecond;
    float bulletWaitTime;
    
    //make it virtual
    void HandleShoot();
    void HandleRotation();
};

#endif