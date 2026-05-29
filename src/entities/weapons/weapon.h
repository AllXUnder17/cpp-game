#ifndef _WEAPON_
#define _WEAPON_

#include <iostream> // IWYU pragma: keep

#include "core\gameobject.h"

struct WeaponConfig {
    GameObjectConfig goConfig;
    Vector2 localTipOffset;
    unsigned bulletsPerSecond;
    unsigned damage;
    Sound onShootSound;
};

class Weapon : public GameObject {
public:
    //===CONSTRUCTORS===
    //add damage, magazine capacity
    Weapon(const WeaponConfig& config);
    
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

    unsigned damage;
    unsigned bulletsPerSecond;
    float bulletWaitTime;
    
    //make it virtual
    void HandleShoot();
    void HandleRotation();
};

#endif