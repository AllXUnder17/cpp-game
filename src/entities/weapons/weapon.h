#ifndef _WEAPON_
#define _WEAPON_

#include <iostream> // IWYU pragma: keep

#include "core\gameobject.h"

class Weapon : public GameObject {
public:
    //===CONSTRUCTORS===
    //add damage, magazine capacity
    Weapon(const GameObjectConfig& config, const Vector2& localTipOffset, const int& bulletsPerSecond, Sound onShootSound);
    
    //===DESTRUCTOR===
    
    //===GETTERS===
    Vector2 GetTipPos() const;

    Vector2 GetOrientation() const;

    Sound GetOnShootSound() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    // virtual void OnShoot();
    void OnShoot();
    
    //---Inherited---
    void OnUpdate() override;
    
protected:
    Sound onShootSound;

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