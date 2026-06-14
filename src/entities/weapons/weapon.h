#ifndef _WEAPON_
#define _WEAPON_

#include <iostream> // IWYU pragma: keep

#include "core\gameobject.h"

struct WeaponConfig {
    GameObjectConfig goConfig;
    Vector2 localTipOffset;
    unsigned bulletsPerSecond;
    unsigned magazineCapacity;
    unsigned damage;
    Sound onShootSound;
};

class Weapon : public GameObject {
public:
    //===CONSTRUCTORS===
    //add damage, magazine capacity
    Weapon(const WeaponConfig& config);
    Weapon(const Weapon& other) = default;
    
    //===DESTRUCTOR===

    //===OPERATORS===
    Weapon& operator=(const Weapon& other) = default;
    
    //===GETTERS===
    Vector2 GetTipPos() const;

    Vector2 GetOrientation() const;

    Sound GetOnShootSound() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    virtual void OnShoot();
    virtual void OnReload();

    virtual void OutputInfo(std::stringstream& ss);
    
    //---Inherited---
    void OnUpdate() override;
    
protected:
    Sound onShootSound;

    Vector2 orientation;
    
    Vector2 tipPos;
    Vector2 localTipOffset;

    unsigned bulletsPerSecond;
    unsigned magazineCapacity;
    unsigned currBullets;
    unsigned damage;
    float bulletWaitTime;
    
    //make it virtual
    virtual void HandleShoot();
    void HandleRotation();
};

#endif